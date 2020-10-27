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

#include "../include/blasfeo_common.h"
#include "../include/blasfeo_d_kernel.h"



/****************************
* old interface
****************************/

void dgemm_diag_left_lib(int m, int n, double alpha, double *dA, double *pB, int sdb, double beta, double *pC, int sdc, double *pD, int sdd)
	{

	if(m<=0 || n<=0)
		return;

	const int bs = 4;

	int ii;

	ii = 0;
	if(beta==0.0)
		{
		for( ; ii<m-3; ii+=4)
			{
			kernel_dgemm_diag_left_4_a0_lib4(n, &alpha, &dA[ii], &pB[ii*sdb], &pD[ii*sdd]);
			}
		}
	else
		{
		for( ; ii<m-3; ii+=4)
			{
			kernel_dgemm_diag_left_4_lib4(n, &alpha, &dA[ii], &pB[ii*sdb], &beta, &pC[ii*sdc], &pD[ii*sdd]);
			}
		}
	if(m-ii>0)
		{
		if(m-ii==1)
			kernel_dgemm_diag_left_1_lib4(n, &alpha, &dA[ii], &pB[ii*sdb], &beta, &pC[ii*sdc], &pD[ii*sdd]);
		else if(m-ii==2)
			kernel_dgemm_diag_left_2_lib4(n, &alpha, &dA[ii], &pB[ii*sdb], &beta, &pC[ii*sdc], &pD[ii*sdd]);
		else // if(m-ii==3)
			kernel_dgemm_diag_left_3_lib4(n, &alpha, &dA[ii], &pB[ii*sdb], &beta, &pC[ii*sdc], &pD[ii*sdd]);
		}
	
	}



void dgemm_diag_right_lib(int m, int n, double alpha, double *pA, int sda, double *dB, double beta, double *pC, int sdc, double *pD, int sdd)
	{

	if(m<=0 || n<=0)
		return;

	const int bs = 4;

	int ii;

	ii = 0;
	if(beta==0.0)
		{
		for( ; ii<n-3; ii+=4)
			{
			kernel_dgemm_diag_right_4_a0_lib4(m, &alpha, &pA[ii*bs], sda, &dB[ii], &pD[ii*bs], sdd);
			}
		}
	else
		{
		for( ; ii<n-3; ii+=4)
			{
			kernel_dgemm_diag_right_4_lib4(m, &alpha, &pA[ii*bs], sda, &dB[ii], &beta, &pC[ii*bs], sdc, &pD[ii*bs], sdd);
			}
		}
	if(n-ii>0)
		{
		if(n-ii==1)
			kernel_dgemm_diag_right_1_lib4(m, &alpha, &pA[ii*bs], sda, &dB[ii], &beta, &pC[ii*bs], sdc, &pD[ii*bs], sdd);
		else if(n-ii==2)
			kernel_dgemm_diag_right_2_lib4(m, &alpha, &pA[ii*bs], sda, &dB[ii], &beta, &pC[ii*bs], sdc, &pD[ii*bs], sdd);
		else // if(n-ii==3)
			kernel_dgemm_diag_right_3_lib4(m, &alpha, &pA[ii*bs], sda, &dB[ii], &beta, &pC[ii*bs], sdc, &pD[ii*bs], sdd);
		}
	
	}



/****************************
* new interface
****************************/



#if defined(LA_HIGH_PERFORMANCE)



// dgemm with A diagonal matrix (stored as strvec)
void dgemm_l_diag_libstr(int m, int n, double alpha, struct d_strvec *sA, int ai, struct d_strmat *sB, int bi, int bj, double beta, struct d_strmat *sC, int ci, int cj, struct d_strmat *sD, int di, int dj)
	{
	if(m<=0 | n<=0)
		return;
	if(bi!=0 | ci!=0 | di!=0)
		{
		printf("\ndgemm_l_diag_libstr: feature not implemented yet: bi=%d, ci=%d, di=%d\n", bi, ci, di);
		exit(1);
		}
	const int bs = 4;
	int sdb = sB->cn;
	int sdc = sC->cn;
	int sdd = sD->cn;
	double *dA = sA->pa + ai;
	double *pB = sB->pA + bj*bs;
	double *pC = sC->pA + cj*bs;
	double *pD = sD->pA + dj*bs;
	dgemm_diag_left_lib(m, n, alpha, dA, pB, sdb, beta, pC, sdc, pD, sdd);
	return;
	}



// dgemm with B diagonal matrix (stored as strvec)
void dgemm_r_diag_libstr(int m, int n, double alpha, struct d_strmat *sA, int ai, int aj, struct d_strvec *sB, int bi, double beta, struct d_strmat *sC, int ci, int cj, struct d_strmat *sD, int di, int dj)
	{
	if(m<=0 | n<=0)
		return;
	if(ai!=0 | ci!=0 | di!=0)
		{
		printf("\ndgemm_r_diag_libstr: feature not implemented yet: ai=%d, ci=%d, di=%d\n", ai, ci, di);
		exit(1);
		}
	const int bs = 4;
	int sda = sA->cn;
	int sdc = sC->cn;
	int sdd = sD->cn;
	double *pA = sA->pA + aj*bs;
	double *dB = sB->pa + bi;
	double *pC = sC->pA + cj*bs;
	double *pD = sD->pA + dj*bs;
	dgemm_diag_right_lib(m, n, alpha, pA, sda, dB, beta, pC, sdc, pD, sdd);
	return;
	}



#else

#error : wrong LA choice

#endif



