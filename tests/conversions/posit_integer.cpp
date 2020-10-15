//  posit_integer.cpp : test suite for conversions between integers and posits
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <iostream>
#include <string>
// enable conversion between posits and integers
#include <universal/adapters/adapt_integer_and_posit.hpp>
// configure the integer arithmetic class
#define INTEGER_THROW_ARITHMETIC_EXCEPTION 1
#include <universal/integer/integer>
// configure the posit arithmetic class
#define POSIT_THROW_ARITHMETIC_EXCEPTION 1
#include <universal/posit/posit>


// is representable
#include <universal/functions/isrepresentable.hpp>
// test helpers, such as, ReportTestResults
#include "../utils/test_helpers.hpp"

// generate a posit conversion test case
// process to convert an integer to a posit is to
// transform the integer into a 1.####eExp format
// find msb -> scale is msb
// shift all the msb-1 bits into a fraction, making the msb the hidden bit
// round the bits we have with respect to the scale of the number
template<size_t nbits, size_t es, size_t ibits>
void GeneratePositConversionTestCase(sw::unum::posit<nbits, es>& p, const sw::unum::integer<ibits>& w) {
	using namespace std;
	using namespace sw::unum;

	value<ibits> v;

	bool sign = w < 0;
	bool isZero = w == 0;
	bool isInf = false;
	bool isNan = false;
	long _scale = scale(w);
	int msb = findMsb(w);
	bitblock<ibits> fraction_without_hidden_bit;
	int fbit = ibits - 1;
	for (int i = msb - 1; i >= 0; --i) {
		fraction_without_hidden_bit.set(fbit, w.at(i));
		--fbit;
	}
	v.set(sign, _scale, fraction_without_hidden_bit, isZero, isInf, isNan);
	cout << "integer is " << w << endl;
	cout << "value is   " << v << endl;
	p = v;
	cout << "posit is   " << color_print(p) << " " << p << " " << hex_format(p) << endl;
}

template<size_t ibits, size_t pbits, size_t pes>
int VerifyInteger2PositConversion(const std::string& tag, bool bReportIndividualTestCases) {
	using namespace std;
	using namespace sw::unum;
	int nrOfFailedTests = 0;
	posit<pbits, pes> p;
	integer<ibits> i;
	constexpr size_t NR_INTEGERS = (1 << ibits);
	//for (integer<ibits> i = min_int<ibits>(); i <= max_int<ibits>(); ++i) {  // this doesn't work for signed integers
	for (size_t pattern = 0; pattern < NR_INTEGERS; ++pattern) {
		i.set_raw_bits(pattern);
		p = i; 
		// p = i requires ADAPTER_POSIT_AND_INTEGER to be set which is accomplished by
		// #include <universal/adapters/adapt_integer_and_posit.hpp>
		// we need to enhance this with an integer type concept
		long diff = long(p) - long(i);
		cout << setw(ibits) << i << " " << to_binary(i) << " -> " << color_print(p) << setw(ibits) << p << " diff is " << diff << std::endl;
		if (diff != 0) ++nrOfFailedTests;
	}
	return nrOfFailedTests;
}

template<size_t ibits, size_t pbits, size_t pes>
int VerifyPosit2IntegerConversion(const std::string& tag, bool bReportIndividualTestCases) {
	using namespace std;
	using namespace sw::unum;
	int nrOfFailedTests = 0;
	posit<pbits, pes> p;
	integer<ibits> i;
	constexpr size_t NR_POSITS = (1 << pbits);
	for (size_t pattern = 0; pattern < NR_POSITS; ++pattern) {
		p.set_raw_bits(pattern);
		long diff;
		if (p.isnar()) {
			i = 0;
			diff = 0;
		}
		else {
			// i = p requires ADAPTER_POSIT_AND_INTEGER to be set which is accomplished by
			// #include <universal/adapters/adapt_integer_and_posit.hpp>
			// we need to enhance this with an integer type concept	
			diff = long(p) - long(i);
		}
		cout << setw(ibits) << i << " " << to_binary(i) << " <- " << color_print(p) << setw(12) << p << " diff is " << diff << std::endl;
		if (diff != 0) ++nrOfFailedTests;
	}
	return nrOfFailedTests;
}

#define MANUAL_TESTING 0
#define STRESS_TESTING 0

int main()
try {
	using namespace std;
	using namespace sw::unum;

	std::string tag = "Conversion between integer and posit failed";

#if MANUAL_TESTING

	using int128_t = sw::unum::integer<128>;
	using int256_t = sw::unum::integer<256>;
	using posit8_t = sw::unum::posit<8,0>;
	using posit16_t = sw::unum::posit<16,1>;
	using posit32_t = sw::unum::posit<32,2>;
	using posit64_t = sw::unum::posit<64,3>;
	using posit128_t = sw::unum::posit<128,4>;
	using posit256_t = sw::unum::posit<256,5>;


	int128_t int128;
	int256_t int256;
	posit8_t p8;
	posit16_t p16;
	posit32_t p32;
	posit64_t p64;
	posit128_t p128;
	posit256_t p256;

	// decimal
	int128.assign("1234567890");
	cout << to_binary(int128) << " " << int128 << " " << hexfloat << scale(int128) << defaultfloat << endl;

	// octal
	//	int128.assign("01234567");
	//cout << to_binary(int128) << " " << int128 << endl;

	// hex
	int128.assign("0x5555'5555");
	cout << to_binary(int128) << " " << int128 << " " << hexfloat << scale(int128) << defaultfloat << endl;
	int128.assign("0x5555'5555'5555'5555");
	cout << to_binary(int128) << " " << int128 << " " << hexfloat << scale(int128) << defaultfloat << endl;
	int128.assign("0x5555'5555'5555'5555'5555'5555'5555'5555");
	cout << to_binary(int128) << " " << int128 << " " << hexfloat << scale(int128) << defaultfloat << endl;
	int128.assign("0x8000'0000'0000'0000'0000'0000'0000'0000");
	cout << to_binary(int128) << " " << int128 << " " << hexfloat << scale(int128) << defaultfloat << endl;
	int128.assign("0xAAAA'AAAA'AAAA'AAAA'AAAA'AAAA'AAAA'AAAA");
	cout << to_binary(int128) << " " << int128 << " " << hexfloat << scale(int128) << defaultfloat << endl;
	int128.assign("0xffff'ffff'ffff'ffff'ffff'ffff'ffff'ffff");
	cout << to_binary(int128) << " " << int128 << " " << hexfloat << scale(int128) << defaultfloat << endl;

	int128.assign("0x5555'5555'5555'5555'5555'5555'5555'5555");
	posit<32, 5> p;
	GeneratePositConversionTestCase(p, int128);

	int256.assign("0xAAAA'AAAA'AAAA'AAAA'AAAA'AAAA'AAAA'AAAA'AAAA'AAAA'AAAA'AAAA'AAAA'AAAA'AAAA'AAAA");

	integer<5> bla = -15;
	posit<12, 1> p;
	convert_i2p(bla, p);
	cout << color_print(p) << " " << p << endl;

	cout << "done" << endl;

	return EXIT_SUCCESS;
#else
	std::cout << "Integer to posit conversion verfication" << std::endl;

	bool bReportIndividualTestCases = false;
	int nrOfFailedTestCases = 0;

	nrOfFailedTestCases += ReportTestResult(VerifyInteger2PositConversion<5, 5, 1>(tag, bReportIndividualTestCases), "integer<5> -> posit<5,1>", "=");
	nrOfFailedTestCases += ReportTestResult(VerifyInteger2PositConversion<5, 8, 1>(tag, bReportIndividualTestCases), "integer<5> -> posit<8,1>", "=");
	nrOfFailedTestCases += ReportTestResult(VerifyInteger2PositConversion<5, 12, 1>(tag, bReportIndividualTestCases), "integer<5> -> posit<12,1>", "=");

	nrOfFailedTestCases += ReportTestResult(VerifyPosit2IntegerConversion<5, 5, 1>(tag, bReportIndividualTestCases), "posit<5,1> -> integer<5>", "=");
	nrOfFailedTestCases += ReportTestResult(VerifyPosit2IntegerConversion<5, 5, 2>(tag, bReportIndividualTestCases), "posit<5,2> -> integer<5>", "=");

	nrOfFailedTestCases = 0; // TODO: our test plan is not automated yet

#if STRESS_TESTING
	nrOfFailedTestCases += ReportTestResult(VerifyInteger2PositConversion<16, 16, 1>(tag, bReportIndividualTestCases), "integer<16> -> posit<16,1>", "=");

#endif // STRESS_TESTING

	return (nrOfFailedTestCases > 0 ? EXIT_FAILURE : EXIT_SUCCESS);

#endif // MANUAL_TESTING
}
catch (char const* msg) {
	std::cerr << msg << '\n';
	return EXIT_FAILURE;
}
catch (const std::runtime_error& err) {
	std::cerr << "Uncaught runtime exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << '\n';
	return EXIT_FAILURE;
}
