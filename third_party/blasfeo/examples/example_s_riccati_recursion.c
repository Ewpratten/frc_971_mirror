/**************************************************************************************************
*                                                                                                 *
* This file is part of BLASFEO.                                                                   *
*                                                                                                 *
* BLASFEO -- BLAS For Embedded Optimization.                                                      *
* Copyright (C) 2016-2017 by Gianluca Frison.                                                     *
* Developed at IMTEK (University of Freiburg) under the supervision of Moritz Diehl.              *
* All rights reserved.                                                                            *
*                                                                                                 *
* HPMPC is free software; you can redistribute it and/or                                          *
* modify it under the terms of the GNU Lesser General Public                                      *
* License as published by the Free Software Foundation; either                                    *
* version 2.1 of the License, or (at your option) any later version.                              *
*                                                                                                 *
* HPMPC is distributed in the hope that it will be useful,                                        *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                                  *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                                            *
* See the GNU Lesser General Public License for more details.                                     *
*                                                                                                 *
* You should have received a copy of the GNU Lesser General Public                                *
* License along with HPMPC; if not, write to the Free Software                                    *
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA                  *
*                                                                                                 *
* Author: Gianluca Frison, giaf (at) dtu.dk                                                       *
*                          gianluca.frison (at) imtek.uni-freiburg.de                             *
*                                                                                                 *
**************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "tools.h"

#include "../include/blasfeo_common.h"
#include "../include/blasfeo_i_aux_ext_dep.h"
#include "../include/blasfeo_s_aux_ext_dep.h"
#include "../include/blasfeo_s_aux.h"
#include "../include/blasfeo_s_kernel.h"
#include "../include/blasfeo_s_blas.h"



static void s_back_ric_sv_libstr(int N, int *nx, int *nu, struct s_strmat *hsBAbt, struct s_strmat *hsRSQrq, struct s_strmat *hsL, struct s_strvec *hsux, struct s_strvec *hspi, struct s_strmat *hswork_mat, struct s_strvec *hswork_vec)
	{

	int nn;

	// factorization and backward substitution

	// last stage
	spotrf_l_libstr(nx[N]+1, nx[N], &hsRSQrq[N], 0, 0, &hsL[N], 0, 0);

	// middle stages
	for(nn=0; nn<N; nn++)
		{
		strmm_rlnn_libstr(nu[N-nn-1]+nx[N-nn-1]+1, nx[N-nn], 1.0, &hsL[N-nn], nu[N-nn], nu[N-nn], &hsBAbt[N-nn-1], 0, 0, &hswork_mat[0], 0, 0);
		sgead_libstr(1, nx[N-nn], 1.0, &hsL[N-nn], nu[N-nn]+nx[N-nn], nu[N-nn], &hswork_mat[0], nu[N-nn-1]+nx[N-nn-1], 0);
#if 1
		ssyrk_spotrf_ln_libstr(nu[N-nn-1]+nx[N-nn-1]+1, nu[N-nn-1]+nx[N-nn-1], nx[N-nn], &hswork_mat[0], 0, 0, &hswork_mat[0], 0, 0, &hsRSQrq[N-nn-1], 0, 0, &hsL[N-nn-1], 0, 0);
#else
		ssyrk_ln_libstr(nu[N-nn-1]+nx[N-nn-1]+1, nu[N-nn-1]+nx[N-nn-1], nx[N-nn], 1.0, &hswork_mat[0], 0, 0, &hswork_mat[0], 0, 0, 1.0, &hsRSQrq[N-nn-1], 0, 0, &hsL[N-nn-1], 0, 0);
		spotrf_l_libstr(nu[N-nn-1]+nx[N-nn-1]+1, nu[N-nn-1]+nx[N-nn-1], &hsL[N-nn-1], 0, 0, &hsL[N-nn-1], 0, 0);
#endif
		}
	
	// forward substitution

	// first stage
	nn = 0;
	srowex_libstr(nu[nn]+nx[nn], -1.0, &hsL[nn], nu[nn]+nx[nn], 0, &hsux[nn], 0);
	strsv_ltn_libstr(nu[nn]+nx[nn], nu[nn]+nx[nn], &hsL[nn], 0, 0, &hsux[nn], 0, &hsux[nn], 0);
	srowex_libstr(nx[nn+1], 1.0, &hsBAbt[nn], nu[nn]+nx[nn], 0, &hsux[nn+1], nu[nn+1]);
	sgemv_t_libstr(nu[nn]+nx[nn], nx[nn+1], 1.0, &hsBAbt[nn], 0, 0, &hsux[nn], 0, 1.0, &hsux[nn+1], nu[nn+1], &hsux[nn+1], nu[nn+1]);
	sveccp_libstr(nx[nn+1], 1.0, &hsux[nn+1], nu[nn+1], &hspi[nn], 0);
	srowex_libstr(nx[nn+1], 1.0, &hsL[nn+1], nu[nn+1]+nx[nn+1], nu[nn+1], &hswork_vec[0], 0);
	strmv_ltn_libstr(nx[nn+1], nx[nn+1], &hsL[nn+1], nu[nn+1], nu[nn+1], &hspi[nn], 0, &hspi[nn], 0);
	saxpy_libstr(nx[nn+1], 1.0, &hswork_vec[0], 0, &hspi[nn], 0);
	strmv_lnn_libstr(nx[nn+1], nx[nn+1], &hsL[nn+1], nu[nn+1], nu[nn+1], &hspi[nn], 0, &hspi[nn], 0);

	// middle stages
	for(nn=1; nn<N; nn++)
		{
		srowex_libstr(nu[nn], -1.0, &hsL[nn], nu[nn]+nx[nn], 0, &hsux[nn], 0);
		strsv_ltn_libstr(nu[nn]+nx[nn], nu[nn], &hsL[nn], 0, 0, &hsux[nn], 0, &hsux[nn], 0);
		srowex_libstr(nx[nn+1], 1.0, &hsBAbt[nn], nu[nn]+nx[nn], 0, &hsux[nn+1], nu[nn+1]);
		sgemv_t_libstr(nu[nn]+nx[nn], nx[nn+1], 1.0, &hsBAbt[nn], 0, 0, &hsux[nn], 0, 1.0, &hsux[nn+1], nu[nn+1], &hsux[nn+1], nu[nn+1]);
		sveccp_libstr(nx[nn+1], 1.0, &hsux[nn+1], nu[nn+1], &hspi[nn], 0);
		srowex_libstr(nx[nn+1], 1.0, &hsL[nn+1], nu[nn+1]+nx[nn+1], nu[nn+1], &hswork_vec[0], 0);
		strmv_ltn_libstr(nx[nn+1], nx[nn+1], &hsL[nn+1], nu[nn+1], nu[nn+1], &hspi[nn], 0, &hspi[nn], 0);
		saxpy_libstr(nx[nn+1], 1.0, &hswork_vec[0], 0, &hspi[nn], 0);
		strmv_lnn_libstr(nx[nn+1], nx[nn+1], &hsL[nn+1], nu[nn+1], nu[nn+1], &hspi[nn], 0, &hspi[nn], 0);
		}

	return;

	}



static void s_back_ric_trf_libstr(int N, int *nx, int *nu, struct s_strmat *hsBAbt, struct s_strmat *hsRSQrq, struct s_strmat *hsL, struct s_strmat *hswork_mat)
	{

	int nn;

	// factorization

	// last stage
	spotrf_l_libstr(nx[N], nx[N], &hsRSQrq[N], 0, 0, &hsL[N], 0, 0);

	// middle stages
	for(nn=0; nn<N; nn++)
		{
		strmm_rlnn_libstr(nu[N-nn-1]+nx[N-nn-1], nx[N-nn], 1.0, &hsL[N-nn], nu[N-nn], nu[N-nn], &hsBAbt[N-nn-1], 0, 0, &hswork_mat[0], 0, 0);
#if 1
		ssyrk_spotrf_ln_libstr(nu[N-nn-1]+nx[N-nn-1], nu[N-nn-1]+nx[N-nn-1], nx[N-nn], &hswork_mat[0], 0, 0, &hswork_mat[0], 0, 0, &hsRSQrq[N-nn-1], 0, 0, &hsL[N-nn-1], 0, 0);
#else
		ssyrk_ln_libstr(nu[N-nn-1]+nx[N-nn-1], nu[N-nn-1]+nx[N-nn-1], nx[N-nn], 1.0, &hswork_mat[0], 0, 0, &hswork_mat[0], 0, 0, 1.0, &hsRSQrq[N-nn-1], 0, 0, &hsL[N-nn-1], 0, 0);
		spotrf_l_libstr(nu[N-nn-1]+nx[N-nn-1], nu[N-nn-1]+nx[N-nn-1], &hsL[N-nn-1], 0, 0, &hsL[N-nn-1], 0, 0);
#endif
		}
	
	return;

	}



static void s_back_ric_trs_libstr(int N, int *nx, int *nu, struct s_strmat *hsBAbt, struct s_strvec *hsb, struct s_strvec *hsrq, struct s_strmat *hsL, struct s_strvec *hsPb, struct s_strvec *hsux, struct s_strvec *hspi, struct s_strvec *hswork_vec)
	{

	int nn;

	// backward substitution

	// last stage
	sveccp_libstr(nu[N]+nx[N], 1.0, &hsrq[N], 0, &hsux[N], 0);

	// middle stages
	for(nn=0; nn<N-1; nn++)
		{
		// compute Pb
		strmv_ltn_libstr(nx[N-nn], nx[N-nn], &hsL[N-nn], nu[N-nn], nu[N-nn], &hsb[N-nn-1], 0, &hsPb[N-nn-1], 0);
		strmv_lnn_libstr(nx[N-nn], nx[N-nn], &hsL[N-nn], nu[N-nn], nu[N-nn], &hsPb[N-nn-1], 0, &hsPb[N-nn-1], 0);
		sveccp_libstr(nu[N-nn-1]+nx[N-nn-1], 1.0, &hsrq[N-nn-1], 0, &hsux[N-nn-1], 0);
		sveccp_libstr(nx[N-nn], 1.0, &hsPb[N-nn-1], 0, &hswork_vec[0], 0);
		saxpy_libstr(nx[N-nn], 1.0, &hsux[N-nn], nu[N-nn], &hswork_vec[0], 0);
		sgemv_n_libstr(nu[N-nn-1]+nx[N-nn-1], nx[N-nn], 1.0, &hsBAbt[N-nn-1], 0, 0, &hswork_vec[0], 0, 1.0, &hsux[N-nn-1], 0, &hsux[N-nn-1], 0);
		strsv_lnn_libstr(nu[N-nn-1]+nx[N-nn-1], nu[N-nn-1], &hsL[N-nn-1], 0, 0, &hsux[N-nn-1], 0, &hsux[N-nn-1], 0);
		}

	// first stage
	nn = N-1;
	strmv_ltn_libstr(nx[N-nn], nx[N-nn], &hsL[N-nn], nu[N-nn], nu[N-nn], &hsb[N-nn-1], 0, &hsPb[N-nn-1], 0);
	strmv_lnn_libstr(nx[N-nn], nx[N-nn], &hsL[N-nn], nu[N-nn], nu[N-nn], &hsPb[N-nn-1], 0, &hsPb[N-nn-1], 0);
	sveccp_libstr(nu[N-nn-1]+nx[N-nn-1], 1.0, &hsrq[N-nn-1], 0, &hsux[N-nn-1], 0);
	sveccp_libstr(nx[N-nn], 1.0, &hsPb[N-nn-1], 0, &hswork_vec[0], 0);
	saxpy_libstr(nx[N-nn], 1.0, &hsux[N-nn], nu[N-nn], &hswork_vec[0], 0);
	sgemv_n_libstr(nu[N-nn-1]+nx[N-nn-1], nx[N-nn], 1.0, &hsBAbt[N-nn-1], 0, 0, &hswork_vec[0], 0, 1.0, &hsux[N-nn-1], 0, &hsux[N-nn-1], 0);
	strsv_lnn_libstr(nu[N-nn-1]+nx[N-nn-1], nu[N-nn-1]+nx[N-nn-1], &hsL[N-nn-1], 0, 0, &hsux[N-nn-1], 0, &hsux[N-nn-1], 0);

	// forward substitution

	// first stage
	nn = 0;
	sveccp_libstr(nx[nn+1], 1.0, &hsux[nn+1], nu[nn+1], &hspi[nn], 0);
	sveccp_libstr(nu[nn]+nx[nn], -1.0, &hsux[nn], 0, &hsux[nn], 0);
	strsv_ltn_libstr(nu[nn]+nx[nn], nu[nn]+nx[nn], &hsL[nn], 0, 0, &hsux[nn], 0, &hsux[nn], 0);
	sgemv_t_libstr(nu[nn]+nx[nn], nx[nn+1], 1.0, &hsBAbt[nn], 0, 0, &hsux[nn], 0, 1.0, &hsb[nn], 0, &hsux[nn+1], nu[nn+1]);
	sveccp_libstr(nx[nn+1], 1.0, &hsux[nn+1], nu[nn+1], &hswork_vec[0], 0);
	strmv_ltn_libstr(nx[nn+1], nx[nn+1], &hsL[nn+1], nu[nn+1], nu[nn+1], &hswork_vec[0], 0, &hswork_vec[0], 0);
	strmv_lnn_libstr(nx[nn+1], nx[nn+1], &hsL[nn+1], nu[nn+1], nu[nn+1], &hswork_vec[0], 0, &hswork_vec[0], 0);
	saxpy_libstr(nx[nn+1], 1.0, &hswork_vec[0], 0, &hspi[nn], 0);

	// middle stages
	for(nn=1; nn<N; nn++)
		{
		sveccp_libstr(nx[nn+1], 1.0, &hsux[nn+1], nu[nn+1], &hspi[nn], 0);
		sveccp_libstr(nu[nn], -1.0, &hsux[nn], 0, &hsux[nn], 0);
		strsv_ltn_libstr(nu[nn]+nx[nn], nu[nn], &hsL[nn], 0, 0, &hsux[nn], 0, &hsux[nn], 0);
		sgemv_t_libstr(nu[nn]+nx[nn], nx[nn+1], 1.0, &hsBAbt[nn], 0, 0, &hsux[nn], 0, 1.0, &hsb[nn], 0, &hsux[nn+1], nu[nn+1]);
		sveccp_libstr(nx[nn+1], 1.0, &hsux[nn+1], nu[nn+1], &hswork_vec[0], 0);
		strmv_ltn_libstr(nx[nn+1], nx[nn+1], &hsL[nn+1], nu[nn+1], nu[nn+1], &hswork_vec[0], 0, &hswork_vec[0], 0);
		strmv_lnn_libstr(nx[nn+1], nx[nn+1], &hsL[nn+1], nu[nn+1], nu[nn+1], &hswork_vec[0], 0, &hswork_vec[0], 0);
		saxpy_libstr(nx[nn+1], 1.0, &hswork_vec[0], 0, &hspi[nn], 0);
		}

	return;

	}



/************************************************ 
Mass-spring system: nx/2 masses connected each other with springs (in a row), and the first and the last one to walls. nu (<=nx) controls act on the first nu masses. The system is sampled with sampling time Ts. 
************************************************/
static void d_mass_spring_system(double Ts, int nx, int nu, int N, double *A, double *B, double *b, double *x0)
	{

	int nx2 = nx*nx;

	int info = 0;

	int pp = nx/2; // number of masses
	
/************************************************
* build the continuous time system 
************************************************/
	
	double *T; d_zeros(&T, pp, pp);
	int ii;
	for(ii=0; ii<pp; ii++) T[ii*(pp+1)] = -2;
	for(ii=0; ii<pp-1; ii++) T[ii*(pp+1)+1] = 1;
	for(ii=1; ii<pp; ii++) T[ii*(pp+1)-1] = 1;

	double *Z; d_zeros(&Z, pp, pp);
	double *I; d_zeros(&I, pp, pp); for(ii=0; ii<pp; ii++) I[ii*(pp+1)]=1.0; // = eye(pp);
	double *Ac; d_zeros(&Ac, nx, nx);
	dmcopy(pp, pp, Z, pp, Ac, nx);
	dmcopy(pp, pp, T, pp, Ac+pp, nx);
	dmcopy(pp, pp, I, pp, Ac+pp*nx, nx);
	dmcopy(pp, pp, Z, pp, Ac+pp*(nx+1), nx); 
	free(T);
	free(Z);
	free(I);
	
	d_zeros(&I, nu, nu); for(ii=0; ii<nu; ii++) I[ii*(nu+1)]=1.0; //I = eye(nu);
	double *Bc; d_zeros(&Bc, nx, nu);
	dmcopy(nu, nu, I, nu, Bc+pp, nx);
	free(I);
	
/************************************************
* compute the discrete time system 
************************************************/

	double *bb; d_zeros(&bb, nx, 1);
	dmcopy(nx, 1, bb, nx, b, nx);
		
	dmcopy(nx, nx, Ac, nx, A, nx);
	dscal_3l(nx2, Ts, A);
	expm(nx, A);
	
	d_zeros(&T, nx, nx);
	d_zeros(&I, nx, nx); for(ii=0; ii<nx; ii++) I[ii*(nx+1)]=1.0; //I = eye(nx);
	dmcopy(nx, nx, A, nx, T, nx);
	daxpy_3l(nx2, -1.0, I, T);
	dgemm_nn_3l(nx, nu, nx, T, nx, Bc, nx, B, nx);
	free(T);
	free(I);
	
	int *ipiv = (int *) malloc(nx*sizeof(int));
	dgesv_3l(nx, nu, Ac, nx, ipiv, B, nx, &info);
	free(ipiv);

	free(Ac);
	free(Bc);
	free(bb);
	
			
/************************************************
* initial state 
************************************************/
	
	if(nx==4)
		{
		x0[0] = 5;
		x0[1] = 10;
		x0[2] = 15;
		x0[3] = 20;
		}
	else
		{
		int jj;
		for(jj=0; jj<nx; jj++)
			x0[jj] = 1;
		}

	}



int main()
	{

	printf("\nExample of LU factorization and backsolve\n\n");

#if defined(LA_HIGH_PERFORMANCE)

	printf("\nLA provided by BLASFEO\n\n");

#elif defined(LA_BLAS)

	printf("\nLA provided by BLAS\n\n");

#elif defined(LA_REFERENCE)

	printf("\nLA provided by REFERENCE\n\n");

#else

	printf("\nLA provided by ???\n\n");
	exit(2);

#endif

	// loop index
	int ii;

/************************************************
* problem size
************************************************/	

	// problem size
	int N = 4;
	int nx_ = 4;
	int nu_ = 1;

	// stage-wise variant size
	int nx[N+1];
	nx[0] = 0;
	for(ii=1; ii<=N; ii++)
		nx[ii] = nx_;
	nx[N] = nx_;

	int nu[N+1];
	for(ii=0; ii<N; ii++)
		nu[ii] = nu_;
	nu[N] = 0;

/************************************************
* dynamical system
************************************************/	

	double *Ad; d_zeros(&Ad, nx_, nx_); // states update matrix

	double *Bd; d_zeros(&Bd, nx_, nu_); // inputs matrix

	double *bd; d_zeros(&bd, nx_, 1); // states offset
	double *x0d; d_zeros(&x0d, nx_, 1); // initial state

	double Ts = 0.5; // sampling time
	d_mass_spring_system(Ts, nx_, nu_, N, Ad, Bd, bd, x0d);

	float *A; s_zeros(&A, nx_, nx_); for(ii=0; ii<nx_*nx_; ii++) A[ii] = (float) Ad[ii];
	float *B; s_zeros(&B, nx_, nu_); for(ii=0; ii<nx_*nu_; ii++) B[ii] = (float) Bd[ii];
	float *b; s_zeros(&b, nx_, 1); for(ii=0; ii<nx_; ii++) b[ii] = (float) bd[ii];
	float *x0; s_zeros(&x0, nx_, 1); for(ii=0; ii<nx_; ii++) x0[ii] = (float) x0d[ii];
	
	for(ii=0; ii<nx_; ii++)
		b[ii] = 0.1;
	
	for(ii=0; ii<nx_; ii++)
		x0[ii] = 0;
	x0[0] = 2.5;
	x0[1] = 2.5;

	s_print_mat(nx_, nx_, A, nx_);
	s_print_mat(nx_, nu_, B, nx_);
	s_print_mat(1, nx_, b, 1);
	s_print_mat(1, nx_, x0, 1);

/************************************************
* cost function
************************************************/	

	float *R; s_zeros(&R, nu_, nu_);
	for(ii=0; ii<nu_; ii++) R[ii*(nu_+1)] = 2.0;

	float *S; s_zeros(&S, nu_, nx_);

	float *Q; s_zeros(&Q, nx_, nx_);
	for(ii=0; ii<nx_; ii++) Q[ii*(nx_+1)] = 1.0;

	float *r; s_zeros(&r, nu_, 1);
	for(ii=0; ii<nu_; ii++) r[ii] = 0.2;

	float *q; s_zeros(&q, nx_, 1);
	for(ii=0; ii<nx_; ii++) q[ii] = 0.1;

	s_print_mat(nu_, nu_, R, nu_);
	s_print_mat(nu_, nx_, S, nu_);
	s_print_mat(nx_, nx_, Q, nx_);
	s_print_mat(1, nu_, r, 1);
	s_print_mat(1, nx_, q, 1);

/************************************************
* matrices as strmat
************************************************/	

	struct s_strmat sA;
	s_allocate_strmat(nx_, nx_, &sA);
	s_cvt_mat2strmat(nx_, nx_, A, nx_, &sA, 0, 0);
	struct s_strvec sb;
	s_allocate_strvec(nx_, &sb);
	s_cvt_vec2strvec(nx_, b, &sb, 0);
	struct s_strvec sx0;
	s_allocate_strvec(nx_, &sx0);
	s_cvt_vec2strvec(nx_, x0, &sx0, 0);
	struct s_strvec sb0;
	s_allocate_strvec(nx_, &sb0);
	float *b0; d_zeros(&b0, nx_, 1); // states offset
	sgemv_n_libstr(nx_, nx_, 1.0, &sA, 0, 0, &sx0, 0, 1.0, &sb, 0, &sb0, 0);
	s_print_tran_strvec(nx_, &sb0, 0);

	struct s_strmat sBbt0;
	s_allocate_strmat(nu_+nx_+1, nx_, &sBbt0);
	s_cvt_tran_mat2strmat(nx_, nx_, B, nx_, &sBbt0, 0, 0);
	srowin_libstr(nx_, 1.0, &sb0, 0, &sBbt0, nu_, 0);
	s_print_strmat(nu_+1, nx_, &sBbt0, 0, 0);

	struct s_strmat sBAbt1;
	s_allocate_strmat(nu_+nx_+1, nx_, &sBAbt1);
	s_cvt_tran_mat2strmat(nx_, nu_, B, nx_, &sBAbt1, 0, 0);
	s_cvt_tran_mat2strmat(nx_, nx_, A, nx_, &sBAbt1, nu_, 0);
	s_cvt_tran_mat2strmat(nx_, 1, b, nx_, &sBAbt1, nu_+nx_, 0);
	s_print_strmat(nu_+nx_+1, nx_, &sBAbt1, 0, 0);

	struct s_strvec sr0; // XXX no need to update r0 since S=0
	s_allocate_strvec(nu_, &sr0);
	s_cvt_vec2strvec(nu_, r, &sr0, 0);

	struct s_strmat sRr0;
	s_allocate_strmat(nu_+1, nu_, &sRr0);
	s_cvt_mat2strmat(nu_, nu_, R, nu_, &sRr0, 0, 0);
	srowin_libstr(nu_, 1.0, &sr0, 0, &sRr0, nu_, 0);
	s_print_strmat(nu_+1, nu_, &sRr0, 0, 0);

	struct s_strvec srq1;
	s_allocate_strvec(nu_+nx_, &srq1);
	s_cvt_vec2strvec(nu_, r, &srq1, 0);
	s_cvt_vec2strvec(nx_, q, &srq1, nu_);

	struct s_strmat sRSQrq1;
	s_allocate_strmat(nu_+nx_+1, nu_+nx_, &sRSQrq1);
	s_cvt_mat2strmat(nu_, nu_, R, nu_, &sRSQrq1, 0, 0);
	s_cvt_tran_mat2strmat(nu_, nx_, S, nu_, &sRSQrq1, nu_, 0);
	s_cvt_mat2strmat(nx_, nx_, Q, nx_, &sRSQrq1, nu_, nu_);
	srowin_libstr(nu_+nx_, 1.0, &srq1, 0, &sRSQrq1, nu_+nx_, 0);
	s_print_strmat(nu_+nx_+1, nu_+nx_, &sRSQrq1, 0, 0);

	struct s_strvec sqN;
	s_allocate_strvec(nx_, &sqN);
	s_cvt_vec2strvec(nx_, q, &sqN, 0);

	struct s_strmat sQqN;
	s_allocate_strmat(nx_+1, nx_, &sQqN);
	s_cvt_mat2strmat(nx_, nx_, Q, nx_, &sQqN, 0, 0);
	srowin_libstr(nx_, 1.0, &sqN, 0, &sQqN, nx_, 0);
	s_print_strmat(nx_+1, nx_, &sQqN, 0, 0);

/************************************************
* array of matrices
************************************************/	
	
	struct s_strmat hsBAbt[N];
	struct s_strvec hsb[N];
	struct s_strmat hsRSQrq[N+1];
	struct s_strvec hsrq[N+1];
	struct s_strmat hsL[N+1];
	struct s_strvec hsPb[N];
	struct s_strvec hsux[N+1];
	struct s_strvec hspi[N];
	struct s_strmat hswork_mat[1];
	struct s_strvec hswork_vec[1];

	hsBAbt[0] = sBbt0;
	hsb[0] = sb0;
	hsRSQrq[0] = sRr0;
	hsrq[0] = sr0;
	s_allocate_strmat(nu_+1, nu_, &hsL[0]);
	s_allocate_strvec(nx_, &hsPb[0]);
	s_allocate_strvec(nx_+nu_+1, &hsux[0]);
	s_allocate_strvec(nx_, &hspi[0]);
	for(ii=1; ii<N; ii++)
		{
		hsBAbt[ii] = sBAbt1;
		hsb[ii] = sb;
		hsRSQrq[ii] = sRSQrq1;
		hsrq[ii] = srq1;
		s_allocate_strmat(nu_+nx_+1, nu_+nx_, &hsL[ii]);
		s_allocate_strvec(nx_, &hsPb[ii]);
		s_allocate_strvec(nx_+nu_+1, &hsux[ii]);
		s_allocate_strvec(nx_, &hspi[ii]);
		}
	hsRSQrq[N] = sQqN;
	hsrq[N] = sqN;
	s_allocate_strmat(nx_+1, nx_, &hsL[N]);
	s_allocate_strvec(nx_+nu_+1, &hsux[N]);
	s_allocate_strmat(nu_+nx_+1, nx_, &hswork_mat[0]);
	s_allocate_strvec(nx_, &hswork_vec[0]);

//	for(ii=0; ii<N; ii++)
//		d_print_strmat(nu[ii]+nx[ii]+1, nx[ii+1], &hsBAbt[ii], 0, 0);
//	return 0;

/************************************************
* call Riccati solver
************************************************/	
	
	// timing 
	struct timeval tv0, tv1, tv2, tv3;
	int nrep = 1000;
	int rep;

	gettimeofday(&tv0, NULL); // time

	for(rep=0; rep<nrep; rep++)
		{
		s_back_ric_sv_libstr(N, nx, nu, hsBAbt, hsRSQrq, hsL, hsux, hspi, hswork_mat, hswork_vec);
		}

	gettimeofday(&tv1, NULL); // time

	for(rep=0; rep<nrep; rep++)
		{
		s_back_ric_trf_libstr(N, nx, nu, hsBAbt, hsRSQrq, hsL, hswork_mat);
		}

	gettimeofday(&tv2, NULL); // time

	for(rep=0; rep<nrep; rep++)
		{
		s_back_ric_trs_libstr(N, nx, nu, hsBAbt, hsb, hsrq, hsL, hsPb, hsux, hspi, hswork_vec);
		}

	gettimeofday(&tv3, NULL); // time

	float time_sv  = (float) (tv1.tv_sec-tv0.tv_sec)/(nrep+0.0)+(tv1.tv_usec-tv0.tv_usec)/(nrep*1e6);
	float time_trf = (float) (tv2.tv_sec-tv1.tv_sec)/(nrep+0.0)+(tv2.tv_usec-tv1.tv_usec)/(nrep*1e6);
	float time_trs = (float) (tv3.tv_sec-tv2.tv_sec)/(nrep+0.0)+(tv3.tv_usec-tv2.tv_usec)/(nrep*1e6);

	// print sol
	printf("\nux = \n\n");
	for(ii=0; ii<=N; ii++)
		s_print_tran_strvec(nu[ii]+nx[ii], &hsux[ii], 0);

	printf("\npi = \n\n");
	for(ii=0; ii<N; ii++)
		s_print_tran_strvec(nx[ii+1], &hspi[ii], 0);

//	printf("\nL = \n\n");
//	for(ii=0; ii<=N; ii++)
//		s_print_strmat(nu[ii]+nx[ii]+1, nu[ii]+nx[ii], &hsL[ii], 0, 0);

	printf("\ntime sv\t\ttime trf\t\ttime trs\n");
	printf("\n%e\t%e\t%e\n", time_sv, time_trf, time_trs);
	printf("\n");

/************************************************
* free memory
************************************************/	

	d_free(Ad);
	d_free(Bd);
	d_free(bd);
	d_free(x0d);
	s_free(A);
	s_free(B);
	s_free(b);
	s_free(x0);
	s_free(R);
	s_free(S);
	s_free(Q);
	s_free(r);
	s_free(q);
	s_free(b0);
	s_free_strmat(&sA);
	s_free_strvec(&sb);
	s_free_strmat(&sBbt0);
	s_free_strvec(&sb0);
	s_free_strmat(&sBAbt1);
	s_free_strmat(&sRr0);
	s_free_strvec(&sr0);
	s_free_strmat(&sRSQrq1);
	s_free_strvec(&srq1);
	s_free_strmat(&sQqN);
	s_free_strvec(&sqN);
	s_free_strmat(&hsL[0]);
	s_free_strvec(&hsPb[0]);
	s_free_strvec(&hsux[0]);
	s_free_strvec(&hspi[0]);
	for(ii=1; ii<N; ii++)
		{
		s_free_strmat(&hsL[ii]);
		s_free_strvec(&hsPb[ii]);
		s_free_strvec(&hsux[ii]);
		s_free_strvec(&hspi[ii]);
		}
	s_free_strmat(&hsL[N]);
	s_free_strvec(&hsux[N]);
	s_free_strmat(&hswork_mat[0]);
	s_free_strvec(&hswork_vec[0]);


/************************************************
* return
************************************************/	

	return 0;

	}




