#pragma once
// vector.hpp: super-simple vector class
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <iostream>
#include <iomanip>
#include <vector>
#include <initializer_list>
#include <cmath>  // for std::sqrt

#if defined(__clang__)
/* Clang/LLVM. ---------------------------------------------- */
#define _HAS_NODISCARD 1

#elif defined(__ICC) || defined(__INTEL_COMPILER)
/* Intel ICC/ICPC. ------------------------------------------ */
#define _HAS_NODISCARD 1

#elif defined(__GNUC__) || defined(__GNUG__)
/* GNU GCC/G++. --------------------------------------------- */
#define _HAS_NODISCARD 1

#elif defined(__HP_cc) || defined(__HP_aCC)
/* Hewlett-Packard C/aC++. ---------------------------------- */
#define _HAS_NODISCARD 1

#elif defined(__IBMC__) || defined(__IBMCPP__)
/* IBM XL C/C++. -------------------------------------------- */
#define _HAS_NODISCARD 1

#elif defined(_MSC_VER)
/* Microsoft Visual Studio. --------------------------------- */
// already defineds _NODISCARD

#elif defined(__PGI)
/* Portland Group PGCC/PGCPP. ------------------------------- */
#define _HAS_NODISCARD 1

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
/* Oracle Solaris Studio. ----------------------------------- */
#define _HAS_NODISCARD 1

#endif

#if _HAS_NODISCARD
#define _NODISCARD [[nodiscard]]
#else // ^^^ CAN HAZ [[nodiscard]] / NO CAN HAZ [[nodiscard]] vvv
#define _NODISCARD
#endif // _HAS_NODISCARD

namespace sw { namespace unum { namespace blas {

template<typename Scalar>
class vector {
public:
	typedef Scalar                            value_type;
	typedef const value_type&                 const_reference;
	typedef value_type&                       reference;
	typedef const value_type*                 const_pointer_type;
	typedef typename std::vector<Scalar>::iterator     iterator;
	typedef typename std::vector<Scalar>::const_iterator const_iterator;
	typedef typename std::vector<Scalar>::reverse_iterator reverse_iterator;
	typedef typename std::vector<Scalar>::const_reverse_iterator const_reverse_iterator;


	vector() : data(0) {}
	vector(size_t N) : data(N) {}
	vector(size_t N, const Scalar& val) : data(N, val) {}
	vector(std::initializer_list<Scalar> iList) : data(iList) {}
	vector(const vector& v) = default;
	vector(vector&& v) = default;

	vector& operator=(const vector& v) = default;
	vector& operator=(vector&& v) = default;

// operators
	vector& operator=(const Scalar& val) {
		for (auto& v : data) v = val;
		return *this;
	}
	value_type operator[](size_t index) const { return data[index]; }
	value_type& operator[](size_t index) { return data[index]; }
	value_type operator()(size_t index) const { return data[index]; }
	value_type& operator()(size_t index) { return data[index]; }

	// prefix operator
	vector operator-() {
		vector<value_type> n(*this);
		for (auto& v : n.data) v = -v;
		return n;
	}

	/// vector-wide operators
	//
	// vector-wide add
	vector& operator+=(const Scalar& offset) {
		for (auto& e : data) e += offset;
		return *this;
	}
	// vector-wide subtract
	vector& operator-=(const Scalar& offset) {
		for (auto& e : data) e -= offset;
		return *this;
	}
	// vector-wide multiply
	vector& operator*=(const Scalar& scaler) {
		for (auto& e : data) e *= scaler;
		return *this;
	}
	// vector-wide divide
	vector& operator/=(const Scalar& normalizer) {
		for (auto& e : data) e /= normalizer;
		return *this;
	}

	// element-wise add
	vector& operator+=(const vector<Scalar>& offset) {
		for (size_t i = 0; i < size(); ++i) {
			data[i] += offset[i];
		}
		return *this;
	}
	// element-wise subtract
	vector& operator-=(const vector<Scalar>& offset) {
		for (size_t i = 0; i < size(); ++i) {
			data[i] -= offset[i];
		}
		return *this;
	}
	// element-wise multiply
	vector& operator*=(const vector<Scalar>& scaler) {
		for (size_t i = 0; i < size(); ++i) {
			data[i] *= scaler[i];
		}
		return *this;
	}
	// element-wise divide
	vector& operator/=(const vector<Scalar>& normalizer) {
		for (size_t i = 0; i < size(); ++i) {
			data[i] /= normalizer[i];
		}
		return *this;
	}

	// non-reproducible sum
	Scalar sum() const {
		Scalar sum(0);  // should we do this with a quire?
		for (auto v : data) sum += v;
		return sum;
	}
	// two-norm of a vector
	Scalar norm() const {  // default is 2-norm
		using std::sqrt;
		Scalar twoNorm = 0;
		for (auto v : data) twoNorm += v * v;
		return sqrt(twoNorm);
	}

// modifiers
	vector& assign(const Scalar& val) {
		for (auto& v : data) v = val;
		return *this;
	}
	value_type& head(size_t index) { return data[index]; }
	value_type  tail(size_t index) const { return data[index]; }
	value_type& tail(size_t index) { return data[index]; }
	void push_back(const value_type& e) { data.push_back(e); }
	void resize(size_t N) {
		data.resize(N);
	}

// selectors
	size_t size() const { return data.size(); }

	// Eigen operators I need to reverse engineer
	vector& array() {
		return *this;
	}
	vector& log() {
		return *this;
	}
	vector& matrix() {
		return *this;
	}

// iterators
	_NODISCARD iterator begin() noexcept {
		return data.begin();
	}

	_NODISCARD const_iterator begin() const noexcept {
		return data.begin();
	}

	_NODISCARD iterator end() noexcept {
		return data.end();
	}

	_NODISCARD const_iterator end() const noexcept {
		return data.end();
	}

	_NODISCARD reverse_iterator rbegin() noexcept {
		return reverse_iterator(end());
	}

	_NODISCARD const_reverse_iterator rbegin() const noexcept {
		return const_reverse_iterator(end());
	}

	_NODISCARD reverse_iterator rend() noexcept {
		return reverse_iterator(begin());
	}

	_NODISCARD const_reverse_iterator rend() const noexcept {
		return const_reverse_iterator(begin());
	}
private:
	std::vector<Scalar> data;
};

template<typename Scalar>
std::ostream& operator<<(std::ostream& ostr, const vector<Scalar>& v) {
	auto width = ostr.precision() + 2;
	for (size_t j = 0; j < size(v); ++j) ostr << std::setw(width) << v[j] << " ";
	return ostr;
}

template<typename Scalar>
vector<Scalar> operator+(const vector<Scalar>& lhs, const vector<Scalar>& rhs) {
	vector<Scalar> sum(lhs);
	return sum += rhs;
}

template<typename Scalar>
vector<Scalar> operator-(const vector<Scalar>& lhs, const vector<Scalar>& rhs) {
	vector<Scalar> difference(lhs);
	return difference -= rhs;
}

template<typename Scalar>
vector<Scalar> operator*(double scalar, const vector<Scalar>& v) {
	vector<Scalar> scaledVector(v);
	return scaledVector *= scalar;
}

template<typename Scalar>
vector<Scalar> operator/(const vector<Scalar>& v, double normalizer) {
	vector<Scalar> normalizedVector(v);
	return normalizedVector /= normalizer;
}

template<typename Scalar> auto size(const vector<Scalar>& v) { return v.size(); }

}}}  // namespace sw::unum::blas
