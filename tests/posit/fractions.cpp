﻿//  fractions.cpp : tests on posit fractions
//
// Copyright (C) 2017 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

#include "stdafx.h"

#include "../../bitset/bitset_helpers.hpp"
#include "../../posit/posit.hpp"
#include "../../posit/posit_manipulators.hpp"
#include "../tests/test_helpers.hpp"

using namespace std;
using namespace sw::unum;

template<size_t fbits>
void ReportError(std::string test_case, std::string op, double input, double reference, const fraction<fbits>& _fraction) {
	std::cerr << test_case
		<< " " << op << " "
		<< std::setw(10) << input
		<< " did not convert to "
		<< std::setw(10) << reference << " instead it yielded "
		<< std::setw(10) << _fraction.value()
		<< std::endl;
}

template<size_t fbits>
int ValidateFractionValue(std::string tag, bool bReportIndividualTestCases)
{
	const uint64_t NR_OF_FRACTIONS = (uint64_t(1) << fbits);
	int nrOfFailedTests = 0;

	fraction<fbits> _fraction;
	double divisor = uint64_t(1) << fbits;
	for (uint64_t i = 0; i < NR_OF_FRACTIONS; i++) {
		std::bitset<fbits> bits = convert_to_bitset<fbits, uint64_t>(i);
		_fraction.set(bits);  // use default nr of fraction bits to be full size
		// fraction value is the 'fraction' of the operand: (fraction to ull)/2^fbits
		double v = _fraction.value();
		double reference = double(i) / divisor;
		// std::cout << "fraction = " << _fraction << " value " << v << " reference " << reference << std::endl;
		if (std::abs(v - reference) > 0.0000000001) {
			nrOfFailedTests++;
			if (bReportIndividualTestCases)	ReportError("FAIL", "to value", v, reference, _fraction);
		}
	}
	return nrOfFailedTests;
}

template<size_t fbits>
int ValidateFixedPointNumber(std::string tag, bool bReportIndividualTestCases)
{
	const uint64_t NR_OF_FRACTIONS = (uint64_t(1) << fbits);
	int nrOfFailedTests = 0;

	double divisor = uint64_t(1) << fbits;
	fraction<fbits> _fraction;
	std::bitset<fbits + 1> _fixed_point;
	for (uint64_t i = 0; i < NR_OF_FRACTIONS; i++) {
		std::bitset<fbits> bits = convert_to_bitset<fbits, uint64_t>(i);
		_fraction.set(bits);  // use default nr of fraction bits to be full size
							  // fraction value is the 'fraction' of the operand: (fraction to ull)/2^fbits
		double v = 1.0 + _fraction.value();
		double reference = 1.0 + double(i) / divisor;
		_fixed_point = _fraction.get_fixed_point();
		//std::cout << "fixed_point = " << _fixed_point << " value " << v << " reference " << reference << std::endl;
		if (std::abs(v - reference) > 0.0000000001) {
			nrOfFailedTests++;
			if (bReportIndividualTestCases)	ReportError("FAIL", "to value", v, reference, _fraction);
		}
	}
	return nrOfFailedTests;
}

template<size_t fbits>
int ValidateRoundingAssessment(std::string tag, bool bReportIndividualTestCases) {
	int nrOfFailedTests = 0;

	fraction<fbits> _fraction;
	std::bitset<fbits> bits = convert_to_bitset<fbits, uint32_t>(0x50);
	for (unsigned i = 0; i < fbits; i++) {
		bool rb = _fraction.assign2(i, bits);
		cout << "nf = " << i << " " << bits << " fraction " << _fraction << " " << (rb ? "up" : "dn") << endl;
	}

	return nrOfFailedTests;
}

#define MANUAL_TESTING 1
#define STRESS_TESTING 0

int main(int argc, char** argv)
try {
	bool bReportIndividualTestCases = false;
	int nrOfFailedTestCases = 0;


#if MANUAL_TESTING
	// generate individual testcases to hand trace/debug
	ValidateFixedPointNumber<4>("Hello", true);
	ValidateRoundingAssessment<8>("", true);

#else

	cout << "Fraction tests" << endl;

	nrOfFailedTestCases += ReportTestResult(ValidateFixedPointNumber<3>("Fixed point conversion failed: ", bReportIndividualTestCases), "fraction<3>", "get_fixed_point()");
	nrOfFailedTestCases += ReportTestResult(ValidateFixedPointNumber<4>("Fixed point conversion failed: ", bReportIndividualTestCases), "fraction<4>", "get_fixed_point()");
	nrOfFailedTestCases += ReportTestResult(ValidateFixedPointNumber<5>("Fixed point conversion failed: ", bReportIndividualTestCases), "fraction<5>", "get_fixed_point()");
	nrOfFailedTestCases += ReportTestResult(ValidateFixedPointNumber<6>("Fixed point conversion failed: ", bReportIndividualTestCases), "fraction<6>", "get_fixed_point()");
	nrOfFailedTestCases += ReportTestResult(ValidateFixedPointNumber<7>("Fixed point conversion failed: ", bReportIndividualTestCases), "fraction<7>", "get_fixed_point()");
	nrOfFailedTestCases += ReportTestResult(ValidateFixedPointNumber<8>("Fixed point conversion failed: ", bReportIndividualTestCases), "fraction<8>", "get_fixed_point()");

	nrOfFailedTestCases += ReportTestResult(ValidateFractionValue<3>("Value conversion failed: ", bReportIndividualTestCases), "fraction<3>", "value()");
	nrOfFailedTestCases += ReportTestResult(ValidateFractionValue<4>("Value conversion failed: ", bReportIndividualTestCases), "fraction<4>", "value()");
	nrOfFailedTestCases += ReportTestResult(ValidateFractionValue<5>("Value conversion failed: ", bReportIndividualTestCases), "fraction<5>", "value()");
	nrOfFailedTestCases += ReportTestResult(ValidateFractionValue<6>("Value conversion failed: ", bReportIndividualTestCases), "fraction<6>", "value()");
	nrOfFailedTestCases += ReportTestResult(ValidateFractionValue<7>("Value conversion failed: ", bReportIndividualTestCases), "fraction<7>", "value()");
	nrOfFailedTestCases += ReportTestResult(ValidateFractionValue<8>("Value conversion failed: ", bReportIndividualTestCases), "fraction<8>", "value()");
	nrOfFailedTestCases += ReportTestResult(ValidateFractionValue<9>("Value conversion failed: ", bReportIndividualTestCases), "fraction<9>", "value()");
	nrOfFailedTestCases += ReportTestResult(ValidateFractionValue<10>("Value conversion failed: ", bReportIndividualTestCases), "fraction<10>", "value()");
	nrOfFailedTestCases += ReportTestResult(ValidateFractionValue<12>("Value conversion failed: ", bReportIndividualTestCases), "fraction<12>", "value()");
	nrOfFailedTestCases += ReportTestResult(ValidateFractionValue<14>("Value conversion failed: ", bReportIndividualTestCases), "fraction<14>", "value()");
	nrOfFailedTestCases += ReportTestResult(ValidateFractionValue<16>("Value conversion failed: ", bReportIndividualTestCases), "fraction<16>", "value()");
	nrOfFailedTestCases += ReportTestResult(ValidateFractionValue<18>("Value conversion failed: ", bReportIndividualTestCases), "fraction<18>", "value()");

#endif

#if STRESS_TESTING
	nrOfFailedTestCases += ReportTestResult(ValidateFractionValue<24>("Value conversion failed: ", bReportIndividualTestCases), "fraction<24>", "value()");
	nrOfFailedTestCases += ReportTestResult(ValidateFractionValue<28>("Value conversion failed: ", bReportIndividualTestCases), "fraction<28>", "value()");
	//nrOfFailedTestCases += ReportTestResult(ValidateFractionValue<32>("Value conversion failed: ", bReportIndividualTestCases), "fraction<32>", "value()");

#endif


	return (nrOfFailedTestCases > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
catch (char const* msg) {
	cerr << msg << endl;
	return EXIT_FAILURE;
}
catch (...) {
	cerr << "Caught unknown exception" << endl;
	return EXIT_FAILURE;
}