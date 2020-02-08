// assignment.cpp: functional tests for fixed-point assignments from native types
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

// Configure the fixpnt template environment
// first: enable general or specialized fixed-point configurations
#define FIXPNT_FAST_SPECIALIZATION
// second: enable/disable fixpnt arithmetic exceptions
#define FIXPNT_THROW_ARITHMETIC_EXCEPTION 0

// minimum set of include files to reflect source code dependencies
#include "universal/fixpnt/fixed_point.hpp"
// fixed-point type manipulators such as pretty printers
#include "universal/fixpnt/fixpnt_manipulators.hpp"
#include "universal/fixpnt/math_functions.hpp"
#include "../utils/fixpnt_test_suite.hpp"

// generate specific test case that you can trace with the trace conditions in fixpnt.h
// for most bugs they are traceable with _trace_conversion and _trace_add
template<size_t nbits, size_t rbits, typename Ty>
void GenerateTestCase(Ty _a, Ty _b) {
	Ty ref;
	sw::unum::fixpnt<nbits, rbits> a, b, cref, result;
	a = _a;
	b = _b;
	result = a + b;
	ref = _a + _b;
	cref = ref;
	std::streamsize oldPrecision = std::cout.precision();
	std::cout << std::setprecision(nbits - 2);
	std::cout << std::setw(nbits) << _a << " + " << std::setw(nbits) << _b << " = " << std::setw(nbits) << ref << std::endl;
	std::cout << a << " + " << b << " = " << result << " (reference: " << cref << ")   " ;
	std::cout << (cref == result ? "PASS" : "FAIL") << std::endl << std::endl;
	std::cout << std::dec << std::setprecision(oldPrecision);
}

// conditional compile flags
#define MANUAL_TESTING 0
#define STRESS_TESTING 0

int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;

	bool bReportIndividualTestCases = false;
	int nrOfFailedTestCases = 0;

	std::string tag = "assignment: ";

#if MANUAL_TESTING

	int x = int(3.7f);
	cout << x << endl;

	fixpnt<5, 1> a, b, c;

	// overflow test
	a = -4; cout << a << endl;  // rounds to 3.5
	b = 4.0f;
	c = a * b;
	cout << to_binary(a) << " * " << to_binary(b) << " = " << to_binary(c) << " " << c << endl;

	// rounding test
	a = 0.5f; cout << a << endl;
	b = 0.5f;
	c = a * b;
	cout << to_binary(a) << " * " << to_binary(b) << " = " << to_binary(c) << " " << c << endl;

	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<4, 0, float>(bReportIndividualTestCases), tag, "posit<4,0>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<4, 1, float>(bReportIndividualTestCases), tag, "posit<4,1>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<4, 2, float>(bReportIndividualTestCases), tag, "posit<4,2>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<4, 3, float>(bReportIndividualTestCases), tag, "posit<4,3>");
	
	// TODO: fixed-point is failing on pure fractional configurations
	//nrOfFailedTestCases = ReportTestResult(ValidateAssignment<4, 4, float>(bReportIndividualTestCases), tag, "posit<4,4>");

#if STRESS_TESTING

	// manual exhaustive test

#endif

#else
	cout << "Fixed-point assignment validation" << endl;

	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<4, 0, float>(bReportIndividualTestCases), tag, "posit<4,0>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<4, 1, float>(bReportIndividualTestCases), tag, "posit<4,1>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<4, 2, float>(bReportIndividualTestCases), tag, "posit<4,2>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<4, 3, float>(bReportIndividualTestCases), tag, "posit<4,3>");

	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<6, 0, float>(bReportIndividualTestCases), tag, "posit<6,0>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<6, 1, float>(bReportIndividualTestCases), tag, "posit<6,1>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<6, 2, float>(bReportIndividualTestCases), tag, "posit<6,2>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<6, 3, float>(bReportIndividualTestCases), tag, "posit<6,3>");

	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<8, 0, float>(bReportIndividualTestCases), tag, "posit<8,0>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<8, 1, float>(bReportIndividualTestCases), tag, "posit<8,1>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<8, 2, float>(bReportIndividualTestCases), tag, "posit<8,2>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<8, 3, float>(bReportIndividualTestCases), tag, "posit<8,3>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<8, 4, float>(bReportIndividualTestCases), tag, "posit<8,4>");

	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<10, 0, float>(bReportIndividualTestCases), tag, "posit<10,0>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<10, 1, float>(bReportIndividualTestCases), tag, "posit<10,1>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<10, 2, float>(bReportIndividualTestCases), tag, "posit<10,2>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<10, 3, float>(bReportIndividualTestCases), tag, "posit<10,3>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<10, 4, float>(bReportIndividualTestCases), tag, "posit<10,4>");
	nrOfFailedTestCases = ReportTestResult(ValidateAssignment<10, 5, float>(bReportIndividualTestCases), tag, "posit<10,5>");

//	nrOfFailedTestCases += ReportTestResult(VerifyAddition<8, 0>(tag, bReportIndividualTestCases), "fixpnt<8,0>", "addition");

#if STRESS_TESTING

#endif  // STRESS_TESTING

#endif  // MANUAL_TESTING

	return (nrOfFailedTestCases > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (const sw::unum::fixpnt_arithmetic_exception& err) {
	std::cerr << "Uncaught fixpnt arithmetic exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const sw::unum::fixpnt_internal_exception& err) {
	std::cerr << "Uncaught fixpnt internal exception: " << err.what() << std::endl;
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
