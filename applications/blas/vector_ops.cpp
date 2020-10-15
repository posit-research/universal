// vector_ops.cpp: example program to show sw::unum::blas::vector operators
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

// enable the following define to show the intermediate steps in the fused-dot product
// #define POSIT_VERBOSE_OUTPUT
#define POSIT_TRACE_MUL
#define QUIRE_TRACE_ADD
// configure posit environment using fast posits
#define POSIT_FAST_POSIT_8_0 1
#define POSIT_FAST_POSIT_16_1 1
#define POSIT_FAST_POSIT_32_2 1
// enable posit arithmetic exceptions
#define POSIT_THROW_ARITHMETIC_EXCEPTION 1
#include <universal/posit/posit>
#include <universal/blas/blas.hpp>

template<size_t nbits, size_t es>
void PrintProducts(const sw::unum::blas::vector<sw::unum::posit<nbits,es>>& a, 
		           const sw::unum::blas::vector<sw::unum::posit<nbits,es>>& b) 
{
	sw::unum::quire<nbits, es> q(0);
	for (size_t i = 0; i < a.size(); ++i) {
		q += sw::unum::quire_mul(a[i], b[i]);
		std::cout << a[i] << " * " << b[i] << " = " << a[i] * b[i] << std::endl << "quire " << q << std::endl;
	}
	sw::unum::posit<nbits,es> sum;
	sw::unum::convert(q.to_value(), sum);     // one and only rounding step of the fused-dot product
	std::cout << "fdp result " << sum << std::endl;
}


int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;
	using namespace sw::unum::blas;

	// set up the properties of the arithmetic system
	constexpr size_t nbits = 32;
	constexpr size_t es = 2;
	using Scalar = sw::unum::posit<nbits, es>;
	using Vector = sw::unum::blas::vector<Scalar>;

	constexpr size_t vectorSize = SIZE_32K + 2;
	Vector a(vectorSize), b(vectorSize);
	Scalar epsilon = numeric_limits<Scalar>::epsilon();
	for (size_t i = 1; i < vectorSize-1; ++i) {
		a[i] = 1;
		b[i] = epsilon;
	}
	a[0] = a[vectorSize - 1] = maxpos<nbits, es>();
	b[0] = -1;  b[vectorSize - 1] = 1;
	if (vectorSize < 10) {
		cout << a << endl;
		cout << b << endl;
		PrintProducts(a, b);
	}
	
	// accumulation of 32K epsilons for a posit<32,2> yields
	// dot: 0
	// fdp: 0.000244141
	cout << "\naccumulation of 32k epsilons (" << hex_format(epsilon) << " = " << epsilon << ") for a " << typeid(Scalar).name() << " yields:\n";
	cout << "dot: " << dot(a, b) << endl;
	cout << "fdp: " << fdp(a, b) << " : " << hex_format(fdp(a,b)) << endl;

	// scale a vector
	cout << "\nscaling a vector\n";
	for (size_t i = 0; i < vectorSize; ++i) {
		a[i] = 1;
		b[i] = epsilon;
	}
	a *= epsilon; // a * epsilon -> b
	bool success = true;
	for (size_t i = 0; i < size(a); ++i) {
		if (a[i] != b[i]) {
			cout << a[i] << " != " << b[i] << '\n';
			success = false;
			break;
		}
	}
	if (success) {
		cout << "PASS: scaling vector a by epsilon yielded vector b\n";
	}
	else {
		cout << "FAIL: scaling vector a by epsilon failed to yield vector b\n";
	}

	// normalize a vector
	cout << "\nnormalizing a vector\n";
	for (size_t i = 0; i < vectorSize; ++i) {
		a[i] = 1;
	}
	b /= epsilon; // b / epsilon -> a
	success = true;
	for (size_t i = 0; i < size(a); ++i) {
		if (a[i] != b[i]) {
			cout << a[i] << " != " << b[i] << '\n';
			success = false;
			break;
		}
	}
	if (success) {
		cout << "PASS: normalizing vector b by epsilon yielded vector a\n";
	}
	else {
		cout << "FAIL: scaling vector b by epsilon failed to yield vector a\n";
	}

	cout << endl;
	return EXIT_SUCCESS;
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (const posit_arithmetic_exception& err) {
	std::cerr << "Uncaught posit arithmetic exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const quire_exception& err) {
	std::cerr << "Uncaught quire exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const posit_internal_exception& err) {
	std::cerr << "Uncaught posit internal exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const std::runtime_error& err) {
	std::cerr << "Uncaught runtime exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << std::endl;
	return EXIT_FAILURE;
}
