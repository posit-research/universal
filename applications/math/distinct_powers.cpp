// distinct_powers.cpp : algorithm to find all integer combinations of a^b for some range [min, max]
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
// integer number system
#include <universal/integer/integer.hpp>
#include <universal/integer/integer_functions.hpp>
// posit number system
#define POSIT_ENABLE_LITERALS 1
#include <universal/posit/posit.hpp>
#include <universal/posit/posit_functions.hpp>

/*
 * Consider all integer combinations of a^b for lowerbound <= a <= upperbound, lowerbound <= b <= upperbound
 *
 * Sorted, with any repeats removed, we get some sequence. What is the cardinality of that sequence?
 */
template<size_t nbits>
sw::unum::integer<nbits> IntegerPowerCombinationsUsingVector(const sw::unum::integer<nbits>& min, const sw::unum::integer<nbits>& max) {
	using namespace std;
	using namespace sw::unum;
	using Integer = integer<nbits>;

	vector<Integer> combinations;
	for (Integer a = min; a <= max; ++a) {
		for (Integer b = min; b <= max; ++b) {
			combinations.push_back(ipow(a, b));
		}
	}
	sort(combinations.begin(), combinations.end());
	// remove duplicates
	combinations.erase(unique(combinations.begin(), combinations.end()), combinations.end());
	return Integer(combinations.size());
}
	
template<size_t nbits>
sw::unum::integer<nbits> IntegerPowerCombinationsUsingSet(const sw::unum::integer<nbits>& min, const sw::unum::integer<nbits>& max) {
	using namespace std;
	using namespace sw::unum;
	using Integer = integer<nbits>;

	set<Integer> combinations;
	for (Integer a = min; a <= max; ++a) {
		for (Integer b = min; b <= max; ++b) {
			combinations.insert(ipow(a, b));
		}
	}
	return Integer(combinations.size());
}

template<size_t nbits, size_t es>
size_t IntegerPowerCombinationsUsingSet(const sw::unum::posit<nbits, es>& min, const sw::unum::posit<nbits, es>& max) {
	using namespace std;
	using namespace sw::unum;
	using Posit = posit<nbits, es>;

	set<Posit> combinations;
	for (Posit a = min; a <= max; a = a + 1) {
		for (Posit b = min; b <= max; b = b + 1) {
			combinations.insert(ipow(a, b));
		}
	}
	return combinations.size();
}

size_t DistinctPowerCombinations(size_t min, size_t max) {
	using namespace std;

	set<double> combinations;
	for (size_t a = min; a <= max; ++a) {
		for (size_t b = min; b <= max; ++b) {
			combinations.insert(pow(a, b));
		}
	}
	return combinations.size();
}

int main()
try {
	using namespace std;
	using namespace sw::unum;

	goto version_double;
	goto version_integer_vector;
	goto version_integer_set;
	goto version_posit_set;

	// use a set of doubles to generate cardinality of unique power values
version_double:
	{
		size_t min = 2, max = 100;
		size_t cardinality = DistinctPowerCombinations(min, max);

		cout << "cardinality of integer power combinations in the range "
			<< "[" << min << ',' << max << "] = " << cardinality << endl;

		return 0;
	}

	// use a vector to store and post-process to remove duplicates
version_integer_vector:
	{
		constexpr size_t nbits = 1024;
		using Integer = integer<nbits>;

		Integer min = 2, max = 100;
	//	Integer cardinality = IntegerPowerCombinationsUsingSet(min, max);
		Integer cardinality = IntegerPowerCombinationsUsingVector(min, max);

		cout << "cardinality of integer power combinations in the range "
			<< "[" << min << ',' << max << "] = " << cardinality << endl;

		return 0;
	}

	// use a set to remove duplicates during insert
version_integer_set:
	{	
		constexpr size_t nbits = 1024;
		using Integer = integer<nbits>;

		cout << "100^100 = " << ipow(Integer(100), Integer(100)) << endl;

		Integer min = 2;
		for (Integer max = min + 1; max <= 100; ++max) {
			Integer cardinality = IntegerPowerCombinationsUsingSet(min, max);

			cout << "cardinality of integer power combinations in the range "
				 << "[" << min << ',' << max << "] = " << cardinality << endl;
		}
	}

version_posit_set:
	{
		constexpr size_t nbits = 64;
		constexpr size_t es = 3;
		using Posit = posit<nbits, es>;

		cout << "100^100 = " << ipow(Posit(100), Posit(100)) << endl;

		Posit min = 2;
		for (Posit max = min + 1; max <= 100; ++max) {
			size_t cardinality = IntegerPowerCombinationsUsingSet(min, max);

			cout << "cardinality of integer power combinations in the range "
				<< "[" << min << ',' << max << "] = " << cardinality << endl;
		}
	}

	return EXIT_SUCCESS;
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

/*
cardinality of integer power combinations in the range [2,3] = 4
cardinality of integer power combinations in the range [2,4] = 8
cardinality of integer power combinations in the range [2,5] = 15
cardinality of integer power combinations in the range [2,6] = 23
cardinality of integer power combinations in the range [2,7] = 34
cardinality of integer power combinations in the range [2,8] = 44
cardinality of integer power combinations in the range [2,9] = 54
cardinality of integer power combinations in the range [2,10] = 69
cardinality of integer power combinations in the range [2,11] = 88
cardinality of integer power combinations in the range [2,12] = 106
cardinality of integer power combinations in the range [2,13] = 129
cardinality of integer power combinations in the range [2,14] = 152
cardinality of integer power combinations in the range [2,15] = 177
cardinality of integer power combinations in the range [2,16] = 195
cardinality of integer power combinations in the range [2,17] = 226
cardinality of integer power combinations in the range [2,18] = 256
cardinality of integer power combinations in the range [2,19] = 291
cardinality of integer power combinations in the range [2,20] = 324
cardinality of integer power combinations in the range [2,21] = 361
cardinality of integer power combinations in the range [2,22] = 399
cardinality of integer power combinations in the range [2,23] = 442
cardinality of integer power combinations in the range [2,24] = 483
cardinality of integer power combinations in the range [2,25] = 519
cardinality of integer power combinations in the range [2,26] = 564
cardinality of integer power combinations in the range [2,27] = 600
cardinality of integer power combinations in the range [2,28] = 648
cardinality of integer power combinations in the range [2,29] = 703
cardinality of integer power combinations in the range [2,30] = 755
cardinality of integer power combinations in the range [2,31] = 814
cardinality of integer power combinations in the range [2,32] = 856
cardinality of integer power combinations in the range [2,33] = 915
cardinality of integer power combinations in the range [2,34] = 976
cardinality of integer power combinations in the range [2,35] = 1039
cardinality of integer power combinations in the range [2,36] = 1085
cardinality of integer power combinations in the range [2,37] = 1156
cardinality of integer power combinations in the range [2,38] = 1224
cardinality of integer power combinations in the range [2,39] = 1295
cardinality of integer power combinations in the range [2,40] = 1365
cardinality of integer power combinations in the range [2,41] = 1444
cardinality of integer power combinations in the range [2,42] = 1519
cardinality of integer power combinations in the range [2,43] = 1602
cardinality of integer power combinations in the range [2,44] = 1681
cardinality of integer power combinations in the range [2,45] = 1762
cardinality of integer power combinations in the range [2,46] = 1846
cardinality of integer power combinations in the range [2,47] = 1937
cardinality of integer power combinations in the range [2,48] = 2023
cardinality of integer power combinations in the range [2,49] = 2095
cardinality of integer power combinations in the range [2,50] = 2184
cardinality of integer power combinations in the range [2,51] = 2279
cardinality of integer power combinations in the range [2,52] = 2373
cardinality of integer power combinations in the range [2,53] = 2476
cardinality of integer power combinations in the range [2,54] = 2574
cardinality of integer power combinations in the range [2,55] = 2677
cardinality of integer power combinations in the range [2,56] = 2779
cardinality of integer power combinations in the range [2,57] = 2886
cardinality of integer power combinations in the range [2,58] = 2993
cardinality of integer power combinations in the range [2,59] = 3108
cardinality of integer power combinations in the range [2,60] = 3216
cardinality of integer power combinations in the range [2,61] = 3335
cardinality of integer power combinations in the range [2,62] = 3450
cardinality of integer power combinations in the range [2,63] = 3569
cardinality of integer power combinations in the range [2,64] = 3648
cardinality of integer power combinations in the range [2,65] = 3771
cardinality of integer power combinations in the range [2,66] = 3890
cardinality of integer power combinations in the range [2,67] = 4021
cardinality of integer power combinations in the range [2,68] = 4147
cardinality of integer power combinations in the range [2,69] = 4277
cardinality of integer power combinations in the range [2,70] = 4406
cardinality of integer power combinations in the range [2,71] = 4545
cardinality of integer power combinations in the range [2,72] = 4676
cardinality of integer power combinations in the range [2,73] = 4819
cardinality of integer power combinations in the range [2,74] = 4957
cardinality of integer power combinations in the range [2,75] = 5098
cardinality of integer power combinations in the range [2,76] = 5240
cardinality of integer power combinations in the range [2,77] = 5391
cardinality of integer power combinations in the range [2,78] = 5534
cardinality of integer power combinations in the range [2,79] = 5689
cardinality of integer power combinations in the range [2,80] = 5838
cardinality of integer power combinations in the range [2,81] = 5946
cardinality of integer power combinations in the range [2,82] = 6099
cardinality of integer power combinations in the range [2,83] = 6262
cardinality of integer power combinations in the range [2,84] = 6416
cardinality of integer power combinations in the range [2,85] = 6579
cardinality of integer power combinations in the range [2,86] = 6740
cardinality of integer power combinations in the range [2,87] = 6906
cardinality of integer power combinations in the range [2,88] = 7070
cardinality of integer power combinations in the range [2,89] = 7245
cardinality of integer power combinations in the range [2,90] = 7412
cardinality of integer power combinations in the range [2,91] = 7591
cardinality of integer power combinations in the range [2,92] = 7763
cardinality of integer power combinations in the range [2,93] = 7941
cardinality of integer power combinations in the range [2,94] = 8118
cardinality of integer power combinations in the range [2,95] = 8301
cardinality of integer power combinations in the range [2,96] = 8479
cardinality of integer power combinations in the range [2,97] = 8670
cardinality of integer power combinations in the range [2,98] = 8855
cardinality of integer power combinations in the range [2,99] = 9045
cardinality of integer power combinations in the range [2,100] = 9183
 */
