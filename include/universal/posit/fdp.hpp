#pragma once
// fdp.hpp :  include file containing templated C++ interfaces to fused dot product
//
// Copyright (C) 2017-2019 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <iostream>
#include <vector>
#include <universal/traits/posit_traits.hpp>

namespace sw { namespace unum {

/// //////////////////////////////////////////////////////////////////
/// fused dot product operators
/// fdp_qc         fused dot product with quire continuation
/// fdp_stride     fused dot product with non-negative stride
/// fdp            fused dot product of two vectors

// Fused dot product with quire continuation
template<typename Qy, typename Vector>
void fdp_qc(Qy& sum_of_products, size_t n, const Vector& x, size_t incx, const Vector& y, size_t incy) {
	size_t ix, iy;
	for (ix = 0, iy = 0; ix < n && iy < n; ix = ix + incx, iy = iy + incy) {
		sum_of_products += sw::unum::quire_mul(x[ix], y[iy]);
	}
}

// Resolved fused dot product, with the option to control capacity bits in the quire
template<typename Vector>
enable_if_posit<value_type<Vector>, value_type<Vector> > // as return type
fdp_stride(size_t n, const Vector& x, size_t incx, const Vector& y, size_t incy) {
	constexpr size_t nbits = Vector::value_type::nbits;
	constexpr size_t es = Vector::value_type::es;
	constexpr size_t capacity = 20; // support vectors up to 1M elements
	quire<nbits, es, capacity> q = 0;
	size_t ix, iy;
	for (ix = 0, iy = 0; ix < n && iy < n; ix = ix + incx, iy = iy + incy) {
		q += sw::unum::quire_mul(x[ix], y[iy]);
		if (sw::unum::_trace_quire_add) std::cout << q << '\n';
	}
	typename Vector::value_type sum;
	convert(q.to_value(), sum);     // one and only rounding step of the fused-dot product
	return sum;
}

#if defined(_MSC_VER)
/* Microsoft Visual Studio. --------------------------------- */
// Specialized resolved fused dot product that assumes unit stride and a standard vector
template<typename Vector>
enable_if_posit<value_type<Vector>, value_type<Vector> > // as return type
fdp(const Vector& x, const Vector& y) {
	constexpr size_t nbits = Vector::value_type::nbits;
	constexpr size_t es = Vector::value_type::es;
	constexpr size_t capacity = 20; // support vectors up to 1M elements
	quire<nbits, es, capacity> q(0);
	size_t ix, iy, n = size(x);
	for (ix = 0, iy = 0; ix < n && iy < n; ++ix, ++iy) {
		q += sw::unum::quire_mul(x[ix], y[iy]);
	}
	typename Vector::value_type sum;
	convert(q.to_value(), sum);     // one and only rounding step of the fused-dot product
	return sum;
}
#else
template<typename Scalar>
constexpr auto size(const std::vector<Scalar>& v) -> decltype(v.size())
{
	return (v.size());
}

// Specialized resolved fused dot product that assumes unit stride and a standard vector
template<typename Vector>
enable_if_posit<value_type<Vector>, value_type<Vector> > // as return type
fdp(const Vector& x, const Vector& y) {
	constexpr size_t nbits = Vector::value_type::nbits;
	constexpr size_t es = Vector::value_type::es;
	constexpr size_t capacity = 20; // support vectors up to 1M elements
	quire<nbits, es, capacity> q(0);
	size_t ix, iy, n = size(x);
	for (ix = 0, iy = 0; ix < n && iy < n; ++ix, ++iy) {
		q += sw::unum::quire_mul(x[ix], y[iy]);
	}
	typename Vector::value_type sum;
	convert(q.to_value(), sum);     // one and only rounding step of the fused-dot product
	return sum;
}
#endif

}} // namespace sw::unum

