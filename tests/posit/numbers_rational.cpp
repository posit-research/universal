// numbers_rational.cpp: experiments with rational numbers and their approximations
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

#include "universal/posit/posit.hpp"
#include "universal/posit/posit_manipulators.hpp"
#include "universal/sequences/sequences.hpp"
// test helpers, such as, ReportTestResults
#include "../utils/test_helpers.hpp"
#include "../utils/posit_test_helpers.hpp"

/*
phi at 156 digits
1.61803398874989484820458683436563811772030917980576286213544862270526046281890244970720720418939113748475408807538689175212663386222353693179318006076672635
*/

template<typename Ty>
Ty PhiThroughFibonacciSequence(unsigned terms) {
	std::pair<Ty, Ty> fib = sw::sequences::Fibonacci<Ty>(unsigned(terms));
	return fib.second / fib.first;
}


int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;
	using namespace sw::sequences;

	//bool bReportIndividualTestCases = false;
	int nrOfFailedTestCases = 0;

	//using Scalar = uint64_t;

	streamsize precision = cout.precision();
	for (unsigned i = 40; i < 50; i++) {
		cout << "approximation to golden ratio: " << setprecision(27) << PhiThroughFibonacciSequence<uint64_t>(i) << endl;
		cout << "approximation to golden ratio: " << setprecision(27) << PhiThroughFibonacciSequence<float>(i) << endl;
		cout << "approximation to golden ratio: " << setprecision(27) << PhiThroughFibonacciSequence<double>(i) << endl;
		cout << "approximation to golden ratio: " << setprecision(27) << PhiThroughFibonacciSequence< posit<32, 2> >(i) << endl;
		cout << "approximation to golden ratio: " << setprecision(27) << PhiThroughFibonacciSequence< posit<64, 3> >(i) << endl;
	}
	cout << setprecision(precision);

	return (nrOfFailedTestCases > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
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
