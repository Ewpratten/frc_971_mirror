#include "motors/fet12/motor_controls.h"

#include "motors/peripheral/configuration.h"

namespace frc971 {
namespace motors {
namespace {

template <int kRows, int kCols>
using ComplexMatrix = MotorControlsImplementation::ComplexMatrix<kRows, kCols>;

using Complex = ::std::complex<float>;

constexpr int kCountsPerRevolution =
    MotorControlsImplementation::constant_counts_per_revolution();

#if 1
constexpr double kMaxDutyCycle = 0.98;
#elif 1
constexpr double kMaxDutyCycle = 0.6;
#elif 0
constexpr double kMaxDutyCycle = 0.2;
#endif

constexpr int kPhaseBOffset = kCountsPerRevolution / 3;
constexpr int kPhaseCOffset = 2 * kCountsPerRevolution / 3;

constexpr double K1_unscaled = 1.0;
constexpr double K2_unscaled = 1.0 / -6.4786;

// Make the amplitude of the fundamental 1 for ease of math.
constexpr double K2 = K2_unscaled / K1_unscaled;
constexpr double K1 = 1.0;

// volts
constexpr double kVcc = 31.5;

// 3.6 and 1.15 are adjustments from calibrations.
constexpr double Kv = 22000.0 * 2.0 * M_PI / 60.0 / 30.0 * 3.6 * 1.15;

constexpr double kL = 5e-06;
constexpr double kM = 0;
constexpr double kR = 0.0079;
constexpr float kAdiscrete_diagonal = 0.92404f;
constexpr float kAdiscrete_offdiagonal = 0.0f;
constexpr float kBdiscrete_inv_diagonal = 0.104002f;
constexpr float kBdiscrete_inv_offdiagonal = 0.0f;
constexpr double kOneAmpScalar = 1.46785;
constexpr double kMaxOneAmpDrivingVoltage = 0.0434948;

::Eigen::Matrix<float, 3, 3> A_discrete() {
  ::Eigen::Matrix<float, 3, 3> r;
  r << kAdiscrete_diagonal, kAdiscrete_offdiagonal, kAdiscrete_offdiagonal,
      kAdiscrete_offdiagonal, kAdiscrete_diagonal, kAdiscrete_offdiagonal,
      kAdiscrete_offdiagonal, kAdiscrete_offdiagonal, kAdiscrete_diagonal;
  return r;
}

::Eigen::Matrix<float, 3, 3> B_discrete_inverse() {
  return ::Eigen::Matrix<float, 1, 3>::Constant(kBdiscrete_inv_diagonal)
      .asDiagonal();
}

// Use FluxLinkageTable() to access this with a const so you don't accidentally
// modify it.
float flux_linkage_table[kCountsPerRevolution];

void MakeFluxLinkageTable() {
  for (int i = 0; i < kCountsPerRevolution; ++i) {
    const double theta = static_cast<double>(i) /
                         static_cast<double>(kCountsPerRevolution) * 2.0 * M_PI;
    flux_linkage_table[i] = K1 * sin(theta) - K2 * sin(theta * 5);
  }
}

// theta doesn't have to be less than kCountsPerRevolution.
::Eigen::Matrix<float, 3, 1> FluxLinkageAt(uint32_t theta) {
  ::Eigen::Matrix<float, 3, 1> r;
  r(0) = flux_linkage_table[theta % kCountsPerRevolution];
  r(1) = flux_linkage_table[(theta + kPhaseBOffset) % kCountsPerRevolution];
  r(2) = flux_linkage_table[(theta + kPhaseCOffset) % kCountsPerRevolution];
  return r;
}

::Eigen::Matrix<float, 3, 3> MakeK() {
  ::Eigen::Matrix<float, 3, 3> Vconv;
  Vconv << 2.0f, -1.0f, -1.0f, -1.0f, 2.0f, -1.0f, -1.0f, -1.0f, 2.0f;
  static constexpr float kControllerGain = 0.05f;
  return kControllerGain * (Vconv / 3.0f);
}

ComplexMatrix<3, 1> MakeE1Unrotated() {
  ComplexMatrix<3, 1> rotation;
  rotation << Complex(0, -1), Complex(::std::sqrt(3) / 2, 0.5),
      Complex(-::std::sqrt(3) / 2, 0.5);
  return K1 * rotation;
}

ComplexMatrix<3, 1> MakeE2Unrotated() {
  ComplexMatrix<3, 1> rotation;
  rotation << Complex(0, -1), Complex(-::std::sqrt(3) / 2, 0.5),
      Complex(::std::sqrt(3) / 2, 0.5);
  return K2 * rotation;
}

ComplexMatrix<3, 3> Hn(float omega, int scalar) {
  const Complex a(static_cast<float>(kR),
                  omega * static_cast<float>(scalar * kL));
  const Complex b(0, omega * static_cast<float>(scalar * kM));
  const Complex temp1 = a + b;
  const Complex temp2 = -b;
  ComplexMatrix<3, 3> matrix;
  matrix << temp1, temp2, temp2, temp2, temp1, temp2, temp2, temp2, temp1;
  return matrix *
         -(omega / static_cast<float>(Kv) / (a * a + a * b - 2.0f * b * b));
}

}  // namespace

MotorControlsImplementation::MotorControlsImplementation()
    : E1Unrotated_(MakeE1Unrotated()), E2Unrotated_(MakeE2Unrotated()) {
  MakeFluxLinkageTable();
}

::std::array<float, 3> MotorControlsImplementation::DoIteration(
    const float raw_currents[3], const uint32_t theta_in,
    const float command_current) {
  static constexpr float kCurrentSlewRate = 0.10f;
  if (command_current > filtered_current_ + kCurrentSlewRate) {
    filtered_current_ += kCurrentSlewRate;
  } else if (command_current < filtered_current_ - kCurrentSlewRate) {
    filtered_current_ -= kCurrentSlewRate;
  } else {
    filtered_current_ = command_current;
  }
  const float goal_current_in = filtered_current_;
  const float max_current =
      (static_cast<float>(kVcc * kMaxDutyCycle) -
       estimated_velocity_ / static_cast<float>(Kv / 2.0)) /
      static_cast<float>(kMaxOneAmpDrivingVoltage);
  const float min_current =
      (-static_cast<float>(kVcc * kMaxDutyCycle) -
       estimated_velocity_ / static_cast<float>(Kv / 2.0)) /
      static_cast<float>(kMaxOneAmpDrivingVoltage);
  const float goal_current =
      ::std::max(min_current, ::std::min(max_current, goal_current_in));

#if 0
  const uint32_t theta =
      (theta_in + static_cast<uint32_t>(estimated_velocity_ * 1.0f)) % 1024;
#elif 0
  const uint32_t theta =
      (theta_in + kCountsPerRevolution - 160u) % kCountsPerRevolution;
#elif 0
  const uint32_t theta =
      (theta_in + kCountsPerRevolution +
       ((estimated_velocity_ > 0) ? (kCountsPerRevolution - 10u) : 60u)) %
      kCountsPerRevolution;
#elif 1
  const uint32_t theta = theta_in;
#endif

  const ::Eigen::Matrix<float, 3, 1> measured_current =
      (::Eigen::Matrix<float, 3, 1>() << scale_current_reading(raw_currents[0]),
       scale_current_reading(raw_currents[1]),
       scale_current_reading(raw_currents[2])).finished();

  const ComplexMatrix<3, 1> E1 =
      E1Unrotated_ *
      ImaginaryExpInt<::std::ratio<1, constant_counts_per_revolution()>>(theta);
  const ComplexMatrix<3, 1> E2 =
      E2Unrotated_ *
      ImaginaryExpInt<::std::ratio<5, constant_counts_per_revolution()>>(theta);

  const float overall_measured_current =
      ((E1 + E2).real().transpose() * measured_current /
       static_cast<float>(kOneAmpScalar))(0);
  overall_measured_current_ = overall_measured_current;
  const float current_error = goal_current - overall_measured_current;
  estimated_velocity_ += current_error * 0.1f;
  debug_[3] = theta;
  const float omega = estimated_velocity_;

  debug_[4] = max_current * 10;

  const ::Eigen::Matrix<float, 3, 1> I_now = I_last_;
  const ::Eigen::Matrix<float, 3, 1> I_next =
      FluxLinkageAt(theta +
                    static_cast<int32_t>(
                        2.0f * omega * kCountsPerRevolution /
                        static_cast<float>(2.0 * M_PI * SWITCHING_FREQUENCY))) *
      goal_current;

  const ComplexMatrix<3, 3> H1 = Hn(omega, 1);
  const ComplexMatrix<3, 3> H2 = Hn(omega, 5);

  const ::std::complex<float> first_speed_delay =
      ImaginaryExpFloat(omega / SWITCHING_FREQUENCY);
  const ::std::complex<float> fifth_speed_delay =
      ImaginaryExpFloat(omega * 5.0f / SWITCHING_FREQUENCY);
  const ComplexMatrix<3, 1> H1E1 = first_speed_delay * H1 * E1;
  const ComplexMatrix<3, 1> H2E2 = fifth_speed_delay * H2 * E2;
  const ComplexMatrix<3, 1> p_imaginary = H1E1 + H2E2;
  const ComplexMatrix<3, 1> p_next_imaginary =
      first_speed_delay * H1E1 + fifth_speed_delay * H2E2;
  const ::Eigen::Matrix<float, 3, 1> p = p_imaginary.real();
  const ::Eigen::Matrix<float, 3, 1> p_next = p_next_imaginary.real();

  const ::Eigen::Matrix<float, 3, 1> Vn_ff =
      B_discrete_inverse() * (I_next - A_discrete() * (I_now - p) - p_next);
  const ::Eigen::Matrix<float, 3, 1> Vn =
      Vn_ff + MakeK() * (I_prev_ - measured_current);

  debug_[0] = (I_next)(0) * 100;
  debug_[1] = (I_next)(1) * 100;
  debug_[2] = (I_next)(2) * 100;

  debug_[5] = Vn(0) * 100;
  debug_[6] = Vn(1) * 100;
  debug_[7] = Vn(2) * 100;

  ::Eigen::Matrix<float, 3, 1> times = Vn / kVcc;
  {
    const float min_time = times.minCoeff();
    times -= ::Eigen::Matrix<float, 3, 1>::Constant(min_time);
  }
  {
    const float max_time = times.maxCoeff();
    const float scalar =
        static_cast<float>(kMaxDutyCycle) /
        ::std::max(static_cast<float>(kMaxDutyCycle), max_time);
    times *= scalar;
  }

  I_prev_ = I_now;
  I_last_ = I_next;

  // TODO(Austin): Figure out why we need the min here.
  return {::std::max(0.0f, times(0)), ::std::max(0.0f, times(1)),
          ::std::max(0.0f, times(2))};
}

int16_t MotorControlsImplementation::Debug(uint32_t theta) {
  return debug_[theta];
}

}  // namespace motors
}  // namespace frc971
