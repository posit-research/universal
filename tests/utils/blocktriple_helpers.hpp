//  blocktriple_helpers.cpp : functions to aid in testing and test reporting block triple numbers
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

#include <universal/native/integers.hpp> // for to_binary(int)
#include <universal/blockbin/blockbinary.hpp>

#define COLUMN_WIDTH 20
template<size_t ebits, size_t fbits, typename Ty = uint8_t>
void ReportBinaryArithmeticError(const std::string& test_case, const std::string& op, const sw::unum::blocktriple<ebits,fbits,Ty>& a, const sw::unum::blocktriple<ebits,fbits, Ty>& b, const sw::unum::blocktriple<ebits,fbits, Ty>& result, long double reference) {
	using namespace sw::unum;
	auto old_precision = std::cerr.precision();
	std::cerr << test_case << " "
		<< std::setprecision(20)
		<< std::setw(COLUMN_WIDTH) << a    // to_hex(a, true)
		<< " " << op << " "
		<< std::setw(COLUMN_WIDTH) << b    // to_hex(b, true)
		<< " != "
		<< std::setw(COLUMN_WIDTH) << result // to_hex(result, true) 
		<< " golden reference is "
		<< std::setw(COLUMN_WIDTH) << reference
//		<< " " << to_binary(result, true) << " vs " << to_binary(reference, nbits)
		<< std::setprecision(old_precision)
		<< std::endl;
}

template<size_t ebits, size_t fbits, typename Ty = uint8_t>
void ReportBinaryArithmeticSuccess(const std::string& test_case, const std::string& op, const sw::unum::blocktriple<ebits,fbits, Ty>& a, const sw::unum::blocktriple<ebits,fbits, Ty>& b, const sw::unum::blocktriple<ebits,fbits, Ty>& result, long double reference) {
	using namespace sw::unum;
	auto old_precision = std::cerr.precision();
	std::cerr << test_case << " "
		<< std::setprecision(20)
		<< std::setw(COLUMN_WIDTH) << (long long)a    // to_hex(a, true)
		<< " " << op << " "
		<< std::setw(COLUMN_WIDTH) << (long long)b    // to_hex(b, true)
		<< " == "
		<< std::setw(COLUMN_WIDTH) << (long long)result // to_hex(result, true) 
		<< " matches reference "
		<< std::setw(COLUMN_WIDTH) << reference
//		<< " " << to_binary(result, true) << " vs " << to_binary(reference, nbits)
		<< std::setprecision(old_precision)
		<< std::endl;
}


