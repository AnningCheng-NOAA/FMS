<<<<<<< HEAD
#ifndef __FMS_PLATFORM_
#define __FMS_PLATFORM_

=======
>>>>>>> 32c2c2c6ccdf1295fb80c3008af3f1919a356c9f
! -*-f90-*-*
!***********************************************************************
!*                   GNU Lesser General Public License
!*
!* This file is part of the GFDL Flexible Modeling System (FMS).
!*
!* FMS is free software: you can redistribute it and/or modify it under
!* the terms of the GNU Lesser General Public License as published by
!* the Free Software Foundation, either version 3 of the License, or (at
!* your option) any later version.
!*
!* FMS is distributed in the hope that it will be useful, but WITHOUT
!* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
!* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
!* for more details.
!*
!* You should have received a copy of the GNU Lesser General Public
!* License along with FMS.  If not, see <http://www.gnu.org/licenses/>.
!***********************************************************************

<<<<<<< HEAD
#ifdef __sgi
#ifdef _COMPILER_VERSION
!the MIPSPro compiler defines _COMPILER_VERSION
#define sgi_mipspro
#else
#define sgi_generic
#endif
#endif

#if defined(_CRAY) || defined(sgi_mipspro)
#define SGICRAY
#endif

!parallel machine types
#if defined(_CRAY) && !defined(_CRAYT3E) && !defined(_CRAYT3D)
#define CRAYPVP
#endif

#if defined(_CRAYT3E) || defined(_CRAYT3D) || defined(sgi_mipspro)
#define SGICRAY_MPP
#endif

!most compilers support Cray pointers
!if you find a compiler that doesnt, #undef this inside a suitable #ifdef
#define use_CRI_pointers

!values of kind: double and long are 8-byte, float and int are 4-byte
!pointer_kind is used for storing addresses as integers
#if defined(SGICRAY)
#define DOUBLE_KIND 8
#define FLOAT_KIND 4
#define LONG_KIND 8
#define INT_KIND 4
#define SHORT_KIND 2
#define POINTER_KIND 8
#else
!these might be different on non-SGICRAY, I believe
! Warning: these numbers may not map to byte sizes for all compilers
=======
#ifndef __FMS_PLATFORM_
#define __FMS_PLATFORM_


!Set type kinds.
#ifdef PORTABLE_KINDS
use,intrinsic :: iso_fortran_env, only: real128
use,intrinsic :: iso_c_binding, only: c_double,c_float,c_int64_t, &
                                      c_int32_t,c_int16_t,c_intptr_t
#define QUAD_KIND real128
#define DOUBLE_KIND c_double
#define FLOAT_KIND c_float
#define LONG_KIND c_int64_t
#define INT_KIND c_int32_t
#define SHORT_KIND c_int16_t
#define POINTER_KIND c_intptr_t
#else
!These values are not necessarily portable.
#define QUAD_KIND 16
>>>>>>> 32c2c2c6ccdf1295fb80c3008af3f1919a356c9f
#define DOUBLE_KIND 8
#define FLOAT_KIND 4
#define LONG_KIND 8
#define INT_KIND 4
#define SHORT_KIND 2
<<<<<<< HEAD
#ifndef _32bits
#define POINTER_KIND 8
!DEC$ MESSAGE:'Using 8-byte addressing'
#else
#define POINTER_KIND 4
!DEC$ MESSAGE:'Using 4-byte addressing'
#endif
#endif

#ifdef sgi_generic
!this is for the Edinburgh n32/o32 compiler, which wont accept 8-byte ints at any price
#define no_8byte_integers
#define LONG_KIND 4
#endif

#ifdef __SXdbl4
!When -A dbl4 is used on NEC-SX both 4-byte reals become 8-byte reals.
!(and 8-byte reals stay 8-byte reals, so they are both the same)
!by forbidding 4-byte reals, 4-byte cmplx is also forbidden
#define no_4byte_reals
!I think by redefining FLOAT_KIND to 8, I no longer need to redefine NF_*
!but I will leave these in for now.
#define FLOAT_KIND 8
#define NF_GET_VAR_REAL nf_get_var_double
#define NF_GET_VARA_REAL nf_get_vara_double
#define NF_GET_ATT_REAL nf_get_att_double
#endif

#if defined __CRAYXT_COMPUTE_LINUX_TARGET || defined __PGI
!Cray XT and PGI compilers do not support real*16 computation
!also known as 128-bit or quad precision
#define NO_QUAD_PRECISION
#endif

#ifdef use_SGI_GSM
!MPI_SGI_Globaltr requires MPI
#define use_libMPI
#endif

#ifdef use_MPI_SMA
!embedded shmem within MPI
#define use_libMPI
#endif

#if defined(__INTEL_COMPILER)
#define _F95
#define _F2000
#endif

#ifdef _F95
!DEC$ MESSAGE:'Using PURE'
#define _PURE PURE
#else
!DEC$ MESSAGE:'Not using PURE'
#define _PURE
#endif

#ifdef _F2000
!DEC$ MESSAGE:'Converting pointers to allocatable components'
#define _ALLOCATABLE ALLOCATABLE
#define _NULL
#define _ALLOCATED ALLOCATED
#else
!DEC$ MESSAGE:'Using pointers'
#define _ALLOCATABLE POINTER
#define _NULL =>NULL()
#define _ALLOCATED ASSOCIATED
#endif

#ifdef no_4byte_reals
=======
#define POINTER_KIND 8
!DEC$ MESSAGE:'Using 8-byte addressing'
#endif


!Control "pure" functions.
#ifdef NO_F95
#define _PURE
!DEC$ MESSAGE:'Not using pure routines.'
#else
#define _PURE pure
!DEC$ MESSAGE:'Using pure routines.'
#endif


!Control array members of derived types.
#ifdef NO_F2000
#define _ALLOCATABLE pointer
#define _NULL =>null()
#define _ALLOCATED associated
!DEC$ MESSAGE:'Using pointer derived type array members.'
#else
#define _ALLOCATABLE allocatable
#define _NULL
#define _ALLOCATED allocated
!DEC$ MESSAGE:'Using allocatable derived type array members.'
#endif


!Control use of cray pointers.
#ifdef NO_CRAY_POINTERS
#undef use_CRI_pointers
!DEC$ MESSAGE:'Not using cray pointers.'
#else
#define use_CRI_pointers
!DEC$ MESSAGE:'Using cray pointers.'
#endif


!Control size of integers that will hold address values.
!Appears for legacy reasons, but seems rather dangerous.
#ifdef _32bits
#define POINTER_KIND 4
!DEC$ MESSAGE:'Using 4-byte addressing'
#endif


!If you do not want to use 64-bit integers.
#ifdef no_8byte_integers
#define LONG_KIND INT_KIND
#endif


!If you do not want to use 32-bit floats.
#ifdef no_4byte_reals
#define FLOAT_KIND DOUBLE_KIND
#define NF_GET_VAR_REAL nf_get_var_double
#define NF_GET_VARA_REAL nf_get_vara_double
#define NF_GET_ATT_REAL nf_get_att_double
>>>>>>> 32c2c2c6ccdf1295fb80c3008af3f1919a356c9f
#undef OVERLOAD_R4
#undef OVERLOAD_C4
#endif

<<<<<<< HEAD
! __FMS_PLATFORM_
=======

!If you want to use quad-precision.
#define NO_QUAD_PRECISION
#ifdef QUAD_PRECISION
#undef NO_QUAD_PRECISION
#else
#define QUAD_KIND DOUBLE_KIND
#endif


>>>>>>> 32c2c2c6ccdf1295fb80c3008af3f1919a356c9f
#endif
