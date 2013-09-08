//
// FPEnvironment_DEC.cpp
//
// $Id: //poco/1.4/Foundation/src/FPEnvironment_DEC.cpp#1 $
//
// Library: Foundation
// Package: Core
// Module:  FPEnvironment
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


//
// _XOPEN_SOURCE disables the ieee fp functions
// in <math.h>, therefore we undefine it for this file.
//
#undef _XOPEN_SOURCE


#include <math.h>
#include <fp.h>
#include <fp_class.h>
#if defined(__VMS)
#include <starlet.h>
#endif
#include "Poco/FPEnvironment_DEC.h"


namespace Poco {


FPEnvironmentImpl::FPEnvironmentImpl()
{
#if defined(__VMS)
	#pragma pointer_size save
	#pragma pointer_size 32
	struct _ieee env;
	sys$ieee_set_fp_control(0, 0, &env);
	#pragma pointer_size restore
	_env = env;
#else
	_env = ieee_get_fp_control();
#endif
}


FPEnvironmentImpl::FPEnvironmentImpl(const FPEnvironmentImpl& env)
{
	_env = env._env;
}


FPEnvironmentImpl::~FPEnvironmentImpl()
{
#if defined(__VMS)
	#pragma pointer_size save
	#pragma pointer_size 32
	struct _ieee mask;
	mask.ieee$q_flags = 0xFFFFFFFFFFFFFFFF;
	struct _ieee env = _env;
	sys$ieee_set_fp_control(&mask, &env, 0);
	#pragma pointer_size restore
#else
	ieee_set_fp_control(_env);
#endif
}


FPEnvironmentImpl& FPEnvironmentImpl::operator = (const FPEnvironmentImpl& env)
{
	_env = env._env;
	return *this;
}


bool FPEnvironmentImpl::isInfiniteImpl(float value)
{
	int cls = fp_classf(value);
	return cls == FP_POS_INF || cls == FP_NEG_INF;
}


bool FPEnvironmentImpl::isInfiniteImpl(double value)
{
	int cls = fp_class(value);
	return cls == FP_POS_INF || cls == FP_NEG_INF;
}


bool FPEnvironmentImpl::isInfiniteImpl(long double value)
{
	int cls = fp_classl(value);
	return cls == FP_POS_INF || cls == FP_NEG_INF;
}


bool FPEnvironmentImpl::isNaNImpl(float value)
{
	return isnanf(value) != 0;
}


bool FPEnvironmentImpl::isNaNImpl(double value)
{
	return isnan(value) != 0;
}


bool FPEnvironmentImpl::isNaNImpl(long double value)
{
	return isnanl(value) != 0;
}


float FPEnvironmentImpl::copySignImpl(float target, float source)
{
	return copysignf(target, source);
}


double FPEnvironmentImpl::copySignImpl(double target, double source)
{
	return copysign(target, source);
}


long double FPEnvironmentImpl::copySignImpl(long double target, long double source)
{
	return copysignl(target, source);
}


void FPEnvironmentImpl::keepCurrentImpl()
{
#if defined(__VMS)
	#pragma pointer_size save
	#pragma pointer_size 32
	struct _ieee env;
	sys$ieee_set_fp_control(0, 0, &env);
	#pragma pointer_size restore
	_env = env;
#else
	ieee_set_fp_control(_env);
#endif
}


void FPEnvironmentImpl::clearFlagsImpl()
{
#if defined(__VMS)
	#pragma pointer_size save
	#pragma pointer_size 32
	struct _ieee mask;
	mask.ieee$q_flags = 0xFFFFFFFFFFFFFFFF;
	struct _ieee clr;
	clr.ieee$q_flags  = 0;
	sys$ieee_set_fp_control(&mask, &clr, 0);
	#pragma pointer_size restore
#else
	ieee_set_fp_control(0);
#endif
}


bool FPEnvironmentImpl::isFlagImpl(FlagImpl flag)
{
#if defined(__VMS)
	#pragma pointer_size save
	#pragma pointer_size 32
	struct _ieee flags;
	sys$ieee_set_fp_control(0, 0, &flags);
	return (flags.ieee$q_flags & flag) != 0;
	#pragma pointer_size restore
#else
	return (ieee_get_fp_control() & flag) != 0;
#endif
}


void FPEnvironmentImpl::setRoundingModeImpl(RoundingModeImpl mode)
{
	// not supported
}


FPEnvironmentImpl::RoundingModeImpl FPEnvironmentImpl::getRoundingModeImpl()
{
	// not supported
	return FPEnvironmentImpl::RoundingModeImpl(0);
}


} // namespace Poco
