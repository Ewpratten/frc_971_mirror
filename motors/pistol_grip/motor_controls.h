#ifndef MOTORS_PISTOL_GRIP_MOTOR_CONTROLS_H_
#define MOTORS_PISTOL_GRIP_MOTOR_CONTROLS_H_

#include <array>
#include <complex>

#include "motors/math.h"
#include "motors/motor.h"

#include "Eigen/Dense"

namespace frc971 {
namespace motors {

class LittleMotorControlsImplementation : public MotorControls {
 public:
  template <int kRows, int kCols>
  using ComplexMatrix = ::Eigen::Matrix<::std::complex<float>, kRows, kCols>;

  LittleMotorControlsImplementation();
  ~LittleMotorControlsImplementation() override = default;

  void Reset() override {}

  static constexpr int constant_counts_per_revolution() { return 4096; }
  static constexpr int poles_per_revolution() { return 7; }

  int mechanical_counts_per_revolution() const override {
    return constant_counts_per_revolution();
  }
  int electrical_counts_per_revolution() const override {
    return constant_counts_per_revolution() / poles_per_revolution();
  }

  float scale_current_reading(float reading) const override {
    return reading *
           static_cast<float>(1.0 / 4096.0 /* Full-scale ADC reading */ *
                              3.3 /* ADC reference voltage */ /
                              (18.0 / (10.8 + 18.0)) /* 5V -> 3.3V divider */ /
                              0.195 /* V/A */);
  }

  ::std::array<float, 3> DoIteration(const float raw_currents[3],
                                        uint32_t theta,
                                        const float command_current) override;

  int16_t Debug(uint32_t theta) override;

  float estimated_velocity() const override { return estimated_velocity_; }

  int16_t i_goal(size_t ii) const override {
    return static_cast<int16_t>(I_last_[ii] * 10.0f);
  }

  float overall_measured_current() const override {
    return overall_measured_current_;
  }

 private:
  const ComplexMatrix<3, 1> E1Unrotated_;

  float estimated_velocity_ = 0;
  float filtered_current_ = 0;
  float overall_measured_current_ = 0;

  ::Eigen::Matrix<float, 3, 1> I_last_ = ::Eigen::Matrix<float, 3, 1>::Zero();

  int16_t debug_[9];
};

}  // namespace motors
}  // namespace frc971

#endif  // MOTORS_PISTOL_GRIP_MOTOR_CONTROLS_H_
