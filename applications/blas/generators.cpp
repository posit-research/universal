// generators.cpp: matrix generator examples
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#ifdef _MSC_VER
#pragma warning(disable : 4100) // argc/argv unreferenced formal parameter
#pragma warning(disable : 4514 4571)
#pragma warning(disable : 4625 4626) // 4625: copy constructor was implicitly defined as deleted, 4626: assignment operator was implicitely defined as deleted
#pragma warning(disable : 5025 5026 5027)
#pragma warning(disable : 4710 4774)
#pragma warning(disable : 4820)
#endif
// enable the following define to show the intermediate steps in the fused-dot product
// #define POSIT_VERBOSE_OUTPUT
#define POSIT_TRACE_MUL
#define QUIRE_TRACE_ADD
// configure posit environment
#define POSIT_FAST_POSIT_8_0 1
#define POSIT_FAST_POSIT_16_1 1
#define POSIT_FAST_POSIT_32_2 1
// enable posit arithmetic exceptions
#define POSIT_THROW_ARITHMETIC_EXCEPTION 1
#include <universal/posit/posit>
#define BLAS_TRACE_ROUNDING_EVENTS 1
#include <universal/blas/blas.hpp>
#include <universal/blas/generators.hpp>

template<typename Scalar>
void generateMatrices() {
	using namespace std;
	using Matrix = sw::unum::blas::matrix<Scalar>;

	Matrix A(5, 5);
	// create an Identity matrix
	A = 1;
	std::cout << A << std::endl;

	// create a 2D Laplacian
	sw::unum::blas::laplace2D(A, 5, 5);
	cout << A << endl;

	// create a row order index matrix
	Matrix roi = sw::unum::blas::row_order_index<Scalar>(5, 6);
	cout << roi << endl;

	// create a column order index matrix
	Matrix coi = sw::unum::blas::column_order_index<Scalar>(6,5);
	cout << coi << endl;

	// create a magic square matrix
	Matrix ms = sw::unum::blas::magic<Scalar>(5);
	cout << ms << endl;

	// create a uniform random matrix
	Matrix B(10, 10);
	sw::unum::blas::uniform_rand(B, -1.0, 1.0);
	cout << setprecision(5) << setw(10) << B << endl;
}

int main(int argc, char* argv[])
try {
	using namespace std;
	using namespace sw::unum::blas;

	if (argc > 0) cout << argv[0] << endl;

	generateMatrices< sw::unum::posit< 8, 0> >();
	generateMatrices< sw::unum::posit<16, 1> >();
	generateMatrices< sw::unum::posit<32, 2> >();

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
