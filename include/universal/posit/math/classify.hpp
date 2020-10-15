#pragma once
// math_classify.hpp: classification functions for posits
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.


namespace sw {
namespace unum {

	// the current shims are NON-COMPLIANT with the posit standard, which says that every function must be
	// correctly rounded for every input value. Anything less sacrifices bitwise reproducibility of results.

	// STD LIB function for IEEE floats: Categorizes floating point value arg into the following categories: zero, subnormal, normal, infinite, NAN, or implementation-defined category.
	template<size_t nbits, size_t es>
	int fpclassify(const posit<nbits,es>& p) {
		return std::fpclassify((long double)(p));
	}
		
	// STD LIB function for IEEE floats: Determines if the given floating point number arg has finite value i.e. it is normal, subnormal or zero, but not infinite or NaN.
	// specialized for posits
	template<size_t nbits, size_t es>
	inline bool isfinite(const posit<nbits,es>& p) {
		return !p.isnar();
	}

	// STD LIB function for IEEE floats: Determines if the given floating point number arg is a positive or negative infinity.
	// specialized for posits
	template<size_t nbits, size_t es>
	inline bool isinf(const posit<nbits, es>& p) {
		return p.isnar();
	}

	// STD LIB function for IEEE floats: Determines if the given floating point number arg is a not-a-number (NaN) value.
	// specialized for posits
	template<size_t nbits, size_t es>
	inline bool isnan(const posit<nbits, es>& p) {
		return p.isnar();
	}

	// STD LIB function for IEEE floats: Determines if the given floating point number arg is normal, i.e. is neither zero, subnormal, infinite, nor NaN.
	// specialized for posits
	template<size_t nbits, size_t es>
	inline bool isnormal(const posit<nbits, es>& p) {
		return std::isnormal((long double)(p));
	}

}  // namespace unum
}  // namespace sw
