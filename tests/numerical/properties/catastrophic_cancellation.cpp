﻿// catastrophic_cancellation.cpp: examples of catastrophic cancellation
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the UNIVERSAL project, which is released under an MIT Open Source license.
#include "common.hpp"
#include "universal/posit/posit"
// test helpers, such as, ReportTestResults
#include "../tests/utils/test_helpers.hpp"
#include "../tests/utils/posit_test_helpers.hpp"

// example of catastrophic cancellation if the number representation doesn't have enough precision bits
template<typename Scalar>
Scalar GenerateTestCase(Scalar e, Scalar x, Scalar origin) {
	Scalar y = origin + x;
	Scalar more = y + e;
	Scalar diff_e = more - y;
	Scalar diff_0 = diff_e - e;
	Scalar zero = diff_0 + diff_0;
	Scalar result = 2 * zero;
	return result;
}

int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;

	// print detailed bit-level computational intermediate results
	// bool verbose = false;

	int nrOfFailedTestCases = 0;
	// bool bReportIndividualTestCases = true;
	std::string tag = "Catastrophic Cancellation: ";

	// preserve the existing ostream precision
	auto precision = cout.precision();
	cout << setprecision(12);

	cout << "Catastrophic Cancellation Experiment" << endl;

	cout << "IEEE Float single precision  : " << GenerateTestCase(0.00000006f, 0.5f, 1.0f) << endl;
	cout << "IEEE Float double precision  : " << GenerateTestCase<double>(0.00000006f, 0.5, 1.0) << endl;
	if (sizeof(long double) == 16) {
		cout << "IEEE Float quad precision  : " << GenerateTestCase(0.00000006l, 0.5l, 1.0l) << endl;
	}

	{
		constexpr size_t nbits = 56;
		constexpr size_t es = 2;
		posit<nbits, es> peps, px, porigin;
		peps = 0.00000006f;
		px = 0.5;
		porigin = 1.0;
		cout << "posit<56,2>                  : " << GenerateTestCase(peps, px, porigin) << endl;
	}

	{
		constexpr size_t nbits = 64;
		constexpr size_t es = 3;
		posit<nbits, es> peps, px, porigin;
		peps = 0.00000006f;
		px = 0.5;
		porigin = 1.0;
		cout << "posit<64,3>                  : " << GenerateTestCase(peps, px, porigin) << endl;
	}

	{
		constexpr size_t nbits = 80;
		constexpr size_t es = 3;
		posit<nbits, es> peps, px, porigin;
		peps = 0.00000006f;
		px = 0.5;
		porigin = 1.0;
		cout << "posit<80,3>                  : " << GenerateTestCase(peps, px, porigin) << endl;
	}

	{
		constexpr size_t nbits = 88;
		constexpr size_t es = 3;
		posit<nbits, es> peps, px, porigin;
		peps = 0.00000006f;
		px = 0.5;
		porigin = 1.0;
		cout << "posit<88,3>                  : " << GenerateTestCase(peps, px, porigin) << endl;
	}

	{
		constexpr size_t nbits = 96;
		constexpr size_t es = 3;
		posit<nbits, es> peps, px, porigin;
		peps = 0.00000006;
		px = 0.5;
		porigin = 1.0;
		cout << "posit<96,3>                  : " << GenerateTestCase(peps, px, porigin) << endl;
	}

	{
		constexpr size_t nbits = 100;
		constexpr size_t es = 3;
		posit<nbits, es> peps, px, porigin;
		peps = 0.00000006;
		px = 0.5;
		porigin = 1.0;
		cout << "posit<100,3>                 : " << GenerateTestCase(peps, px, porigin) << endl;
	}



	// restore the previous ostream precision
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
catch (std::runtime_error& err) {
	std::cerr << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << std::endl;
	return EXIT_FAILURE;
}
