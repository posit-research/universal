// block_add.cpp: functional tests for block binary number addition
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <iostream>
#include <iomanip>

// minimum set of include files to reflect source code dependencies
#include "universal/native/integers.hpp" // for to_binary(int)
#include "universal/native/blockBinaryNumber.hpp"
//#include "universal/native/blockBinaryNumber.hpp"
// test helpers, such as, ReportTestResults
#include "../utils/test_helpers.hpp"

#define COLUMN_WIDTH 20
template<size_t nbits, typename Ty = uint8_t>
void ReportBinaryArithmeticError(std::string test_case, std::string op, const sw::unum::blockBinaryNumber<nbits, Ty>& a, const sw::unum::blockBinaryNumber<nbits, Ty>& b, const sw::unum::blockBinaryNumber<nbits, Ty>& result, int64_t reference) {
	using namespace sw::unum;
	auto old_precision = std::cerr.precision();
	std::cerr << test_case << " "
		<< std::setprecision(20)
		<< std::setw(COLUMN_WIDTH) << to_hex(a, true)
		<< " " << op << " "
		<< std::setw(COLUMN_WIDTH) << to_hex(b, true)
		<< " != "
		<< std::setw(COLUMN_WIDTH) << to_hex(result, true) << " golden reference is "
		<< std::setw(COLUMN_WIDTH) << reference
		<< " " << to_binary(result, true) << " vs " << to_binary(reference, nbits)
		<< std::setprecision(old_precision)
		<< std::endl;
}

template<size_t nbits, typename Ty = uint8_t>
void ReportBinaryArithmeticSuccess(std::string test_case, std::string op, const sw::unum::blockBinaryNumber<nbits, Ty>& a, const sw::unum::blockBinaryNumber<nbits, Ty>& b, const sw::unum::blockBinaryNumber<nbits, Ty>& result, int64_t reference) {
	using namespace sw::unum; 
	auto old_precision = std::cerr.precision();
	std::cerr << test_case << " "
		<< std::setprecision(20)
		<< std::setw(COLUMN_WIDTH) << to_hex(a)
		<< " " << op << " "
		<< std::setw(COLUMN_WIDTH) << to_hex(b)
		<< " == "
		<< std::setw(COLUMN_WIDTH) << to_hex(result) << " matches reference "
		<< std::setw(COLUMN_WIDTH) << reference
		<< " " << to_binary(result, true) << " vs " << to_binary(reference, nbits)
		<< std::setprecision(old_precision)
		<< std::endl;
}


// enumerate all addition cases for an fixpnt<nbits,rbits> configuration
template<size_t nbits, typename StorageBlockType = uint8_t>
int VerifyModularAddition(std::string tag, bool bReportIndividualTestCases) {
	constexpr size_t NR_VALUES = (size_t(1) << nbits);
	using namespace sw::unum;
	
	int nrOfFailedTests = 0;
	blockBinaryNumber<nbits, StorageBlockType> a, b, result, refResult;
	int64_t aref, bref, cref;
	for (size_t i = 0; i < NR_VALUES; i++) {
		a.set_raw_bits(i);
		aref = i;
		for (size_t j = 0; j < NR_VALUES; j++) {
			b.set_raw_bits(j);
			bref = j;
			cref = aref + bref;

			result = a + b;

			refResult.set_raw_bits(cref);
			if (result != refResult) {
				nrOfFailedTests++;
				if (bReportIndividualTestCases)	ReportBinaryArithmeticError("FAIL", "+", a, b, result, cref);
			}
			else {
				// if (bReportIndividualTestCases) ReportBinaryArithmeticSuccess("PASS", "+", a, b, result, cref);
			}
			if (nrOfFailedTests > 100) return nrOfFailedTests;
		}
		if (i % 1024 == 0) std::cout << '.';
	}
	std::cout << std::endl;
	return nrOfFailedTests;
}

// generate specific test case that you can trace with the trace conditions in fixpnt.h
// for most bugs they are traceable with _trace_conversion and _trace_add
template<size_t nbits, typename StorageBlockType = uint8_t>
void GenerateTestCase(int64_t _a, int64_t _b) {
	using namespace sw::unum;
	blockBinaryNumber<nbits, StorageBlockType> a, b, result, reference;

	a.set_raw_bits(uint64_t(_a));
	b.set_raw_bits(uint64_t(_b));
	result = a + b;

	int64_t ref = _a + _b;
	std::streamsize oldPrecision = std::cout.precision();
	std::cout << std::setprecision(nbits - 2);
	std::cout << std::setw(nbits) << _a << " + " << std::setw(nbits) << _b << " = " << std::setw(nbits) << ref << std::endl;
	std::cout << std::hex;
	std::cout << std::setw(nbits) << _a << " + " << std::setw(nbits) << _b << " = " << std::setw(nbits) << ref << std::endl;
	std::cout << std::dec;
	std::cout << to_binary(a) << " + " << to_binary(b) << " = " << to_binary(result) << " (reference: " << to_binary(int(ref)) << ")   " << std::endl;
	std::cout << to_hex(a) << " + " << to_hex(b) << " = " << to_hex(result) << " (reference: " << std::hex << ref << ")   ";
	reference.set_raw_bits(ref);
	std::cout << (result == reference ? "PASS" : "FAIL") << std::endl << std::endl;
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

	// generate individual testcases to hand trace/debug
	GenerateTestCase<18, uint8_t>(12345, 54321); // result is 66,666, thus needs 18 bits to be represented by 2's complement
	GenerateTestCase<18, uint8_t>(66666, -54321); // result is 12,345

	int maxneg = -0x20000;
	GenerateTestCase<18, uint8_t>(maxneg, -1); // result is overflow on the negative side

	GenerateTestCase<12, uint16_t>(0, 0x100);

	unsigned max = (uint64_t(1) << 8) - 1;
	std::cout << "max = " << max << std::endl;
	max = (uint64_t(1) << 16) - 1;
	std::cout << "max = " << max << std::endl;
	max = (uint64_t(1) << 32) - 1;
	std::cout << "max = " << max << std::endl;


	nrOfFailedTestCases += ReportTestResult(VerifyModularAddition<4, uint8_t>("Manual Testing", true), "uint8_t<4>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyModularAddition<4, uint16_t>("Manual Testing", true), "uint16_t<4>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyModularAddition<4, uint32_t>("Manual Testing", true), "uint32_t<4>", "addition");
//	nrOfFailedTestCases += ReportTestResult(VerifyModularAddition<4, uint64_t>("Manual Testing", true), "uint64_t<4>", "addition");


#if STRESS_TESTING

#endif

#else

	cout << "block addition validation" << endl;

	nrOfFailedTestCases += ReportTestResult(VerifyModularAddition<8, uint8_t>("Manual Testing", true), "uint8_t<8>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyModularAddition<8, uint16_t>("Manual Testing", true), "uint16_t<8>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyModularAddition<8, uint32_t>("Manual Testing", true), "uint32_t<8>", "addition");

	nrOfFailedTestCases += ReportTestResult(VerifyModularAddition<12, uint8_t>("Manual Testing", true), "uint8_t<12>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyModularAddition<12, uint16_t>("Manual Testing", true), "uint16_t<12>", "addition");
	nrOfFailedTestCases += ReportTestResult(VerifyModularAddition<12, uint32_t>("Manual Testing", true), "uint32_t<12>", "addition");

#if STRESS_TESTING



#endif  // STRESS_TESTING

#endif  // MANUAL_TESTING

	return (nrOfFailedTestCases > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
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
