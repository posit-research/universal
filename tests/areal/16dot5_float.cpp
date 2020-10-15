// 16dot5_float.cpp: Functionality tests for half precision floats
//
// Copyright (C) 2017-2019 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

// minimum set of include files to reflect source code dependencies
// TODO: the dependencies on posit exceptions and trace_constants needs to be removed
#include "universal/posit/exceptions.hpp"
#include "universal/posit/trace_constants.hpp"
#include "universal/bitblock/bitblock.hpp"
#include "universal/areal/areal.hpp"
// test helpers, such as, ReportTestResults
#include "../utils/test_helpers.hpp"
#include "areal_test_helpers.hpp"

// Standard posit with nbits = 16 have es = 1 exponent bit.

int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;

	//const size_t RND_TEST_CASES = 500000;

	const size_t nbits = 16;
	const size_t es = 5;

	int nrOfFailedTestCases = 0;
	std::string tag = " areal<16,5>";

	cout << "Standard areal<16,5> configuration tests" << endl;

	areal<nbits, es> r;
	r = 1.2345;
	cout << r << endl;

#if 0
	cout << "Arithmetic tests " << RND_TEST_CASES << " randoms each" << endl;
	bool bReportIndividualTestCases = false;

	nrOfFailedTestCases += ReportTestResult(ValidateThroughRandoms<nbits, es>(tag, bReportIndividualTestCases, OPCODE_ADD, RND_TEST_CASES), tag, "addition      ");
	nrOfFailedTestCases += ReportTestResult(ValidateThroughRandoms<nbits, es>(tag, bReportIndividualTestCases, OPCODE_SUB, RND_TEST_CASES), tag, "subtraction   ");
	nrOfFailedTestCases += ReportTestResult(ValidateThroughRandoms<nbits, es>(tag, bReportIndividualTestCases, OPCODE_MUL, RND_TEST_CASES), tag, "multiplication");
	nrOfFailedTestCases += ReportTestResult(ValidateThroughRandoms<nbits, es>(tag, bReportIndividualTestCases, OPCODE_DIV, RND_TEST_CASES), tag, "division      ");
#endif

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
