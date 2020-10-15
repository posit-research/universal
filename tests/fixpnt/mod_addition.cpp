// mod_addition.cpp: functional tests for arbitrary configuration fixed-point modulo addition
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

// Configure the fixpnt template environment
// first: enable general or specialized fixed-point configurations
#define FIXPNT_FAST_SPECIALIZATION
// second: enable/disable fixpnt arithmetic exceptions
#define FIXPNT_THROW_ARITHMETIC_EXCEPTION 1

// minimum set of include files to reflect source code dependencies
#include <universal/fixpnt/fixed_point.hpp>
// fixed-point type manipulators such as pretty printers
#include <universal/fixpnt/fixpnt_manipulators.hpp>
#include <universal/fixpnt/math_functions.hpp>
#include "../utils/fixpnt_test_suite.hpp"

// generate specific test case that you can trace with the trace conditions in fixed_point.hpp
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

	std::string tag = "modular addition failed: ";

#if MANUAL_TESTING

	fixpnt<8, 4> f;
	f = 3.5f;
	bitset<8> bs(f.getbb().block(0));
	cout << bs << endl;
	cout << f << endl;

	// generate individual testcases to hand trace/debug
	GenerateTestCase<8, 4>(0.5f, 1.0f);

	{
		fixpnt<8, 0> fp;
		fp = 4;
		cout << fp << endl;
	}

	{
		fixpnt<8, 4> fp;
		fp = 4.125f;
		cout << fp << endl;
	}

	{
		fixpnt<4, 1> a, b, c;
		a = 0;
		b = 2;
		c = a + b;
		cout << a << " + " << b << " = " << c << endl;
	}

	bReportIndividualTestCases = true;
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<4, 1, Modulo, uint8_t>("Manual Testing", bReportIndividualTestCases), "fixpnt<4,1,Modulo,uint8_t>", "addition");


#if STRESS_TESTING
	// manual exhaustive test
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<4, 0, Modulo, uint8_t>("Manual Testing", bReportIndividualTestCases), "fixpnt<4,0,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<4, 1, Modulo, uint8_t>("Manual Testing", bReportIndividualTestCases), "fixpnt<4,1,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<4, 2, Modulo, uint8_t>("Manual Testing", bReportIndividualTestCases), "fixpnt<4,2,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<4, 3, Modulo, uint8_t>("Manual Testing", bReportIndividualTestCases), "fixpnt<4,3,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<4, 4, Modulo, uint8_t>("Manual Testing", bReportIndividualTestCases), "fixpnt<4,4,Modulo,uint8_t>", "addition");
#endif

#else

	cout << "Fixed-point modular addition validation" << endl;

	nrOfFailedTestCases += ReportTestResult(VerifyAddition<4, 0, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<4,0,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<4, 1, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<4,1,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<4, 2, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<4,2,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<4, 3, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<4,3,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<4, 4, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<4,4,Modulo,uint8_t>", "addition");

	nrOfFailedTestCases += ReportTestResult(VerifyAddition<8, 0, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<8,0,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<8, 1, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<8,1,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<8, 2, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<8,2,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<8, 3, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<8,3,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<8, 4, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<8,4,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<8, 5, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<8,5,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<8, 6, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<8,6,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<8, 7, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<8,7,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<8, 8, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<8,8,Modulo,uint8_t>", "addition");

	nrOfFailedTestCases += ReportTestResult(VerifyAddition<10, 3, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<10,3,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<10, 5, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<10,5,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<10, 7, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<10,7,Modulo,uint8_t>", "addition");

#if STRESS_TESTING

	nrOfFailedTestCases += ReportTestResult(VerifyAddition<11, 3, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<11,3,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<11, 5, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<11,5,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<11, 7, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<11,7,Modulo,uint8_t>", "addition");

	nrOfFailedTestCases += ReportTestResult(VerifyAddition<12, 0, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<12,0,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<12, 4, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<12,4,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<12, 8, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<12,8,Modulo,uint8_t>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyAddition<12, 12, Modulo, uint8_t>(tag, bReportIndividualTestCases), "fixpnt<12,12,Modulo,uint8_t>", "addition");

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
