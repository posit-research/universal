#pragma once
// trace_constants.hpp: definition of constants that direct intermediate result reporting
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

namespace sw {
namespace unum {


# ifndef BLOCKTRIPLE_VERBOSE_OUTPUT
// blocktriple decode and conversion
constexpr bool _trace_decode      = false;
constexpr bool _trace_conversion  = false;
constexpr bool _trace_rounding    = false;

// arithmetic operator tracing
constexpr bool _trace_add         = false;
constexpr bool _trace_sub         = false;
constexpr bool _trace_mul         = false;
constexpr bool _trace_div         = false;
constexpr bool _trace_reciprocate = false;
constexpr bool _trace_sqrt        = false;

// quire update tracing
constexpr bool _trace_quire_add   = false;

# else // !BLOCKTRIPLE_VERBOSE_OUTPUT

#ifdef BLOCKTRIPLE_TRACE_ALL
#define BLOCKTRIPLE_TRACE_DECODE
#define BLOCKTRIPLE_TRACE_CONVERSION
#define BLOCKTRIPLE_TRACE_ROUNDING
#define BLOCKTRIPLE_TRACE_ADD
#define BLOCKTRIPLE_TRACE_SUB
#define BLOCKTRIPLE_TRACE_MUL
#define BLOCKTRIPLE_TRACE_DIV
#define BLOCKTRIPLE_TRACE_RECIPROCATE
#define BLOCKTRIPLE_TRACE_SQRT
#endif

#ifdef QUIRE_TRACE_ALL
#define QUIRE_TRACE_ADD
#endif

// blocktriple decode and conversion

#ifndef BLOCKTRIPLE_TRACE_DECODE
constexpr bool _trace_decode = false;
#else
constexpr bool _trace_decode = true;
#endif

#ifndef BLOCKTRIPLE_TRACE_CONVERSION
constexpr bool _trace_conversion = false;
#else
constexpr bool _trace_conversion = true;
#endif

#ifndef BLOCKTRIPLE_TRACE_ROUNDING
constexpr bool _trace_rounding = false;
#else
constexpr bool _trace_rounding = true;
#endif

// arithmetic operator tracing
#ifndef BLOCKTRIPLE_TRACE_ADD
constexpr bool _trace_add = false;
#else
constexpr bool _trace_add = true;
#endif

#ifndef BLOCKTRIPLE_TRACE_SUB
constexpr bool _trace_sub = false;
#else
constexpr bool _trace_sub = true;
#endif

#ifndef BLOCKTRIPLE_TRACE_MUL
constexpr bool _trace_mul = false;
#else
constexpr bool _trace_mul = true;
#endif

#ifndef BLOCKTRIPLE_TRACE_DIV
constexpr bool _trace_div = false;
#else
constexpr bool _trace_div = true;
#endif

#ifndef BLOCKTRIPLE_TRACE_RECIPROCATE
constexpr bool _trace_reciprocate = false;
#else
constexpr bool _trace_reciprocate = true;
#endif

#ifndef BLOCKTRIPLE_TRACE_SQRT
constexpr bool _trace_sqrt = false;
#else
constexpr bool _trace_sqrt = true;
#endif

// QUIRE tracing
#ifndef QUIRE_TRACE_ADD
constexpr bool _trace_quire_add = false;
#else
constexpr bool _trace_quire_add = true;
#endif

# endif


}  // namespace unum

}  // namespace sw

