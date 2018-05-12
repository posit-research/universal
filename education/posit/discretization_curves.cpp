// discretization_curves.cpp: generate discretization curves to study how small posits cover the real line
//
// Copyright (C) 2017-2018 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

#include "common.hpp"
#include <posit>

/*
  To study how small posits discretize the real line, this test generates
  curves to compare different posit configurations.
*/
int main(int argc, char** argv)
try {
	using namespace std;

		cout << "Discretization Curves" << endl;

		cout << "TBD" << endl;
		// generate a CSV file for different posit comparisons:
		// compare posits with the same exponent structure but vary nbits = 3 till 12
		// compare posits with the same nbits, but vary es from 0 to 4

	return EXIT_SUCCESS;
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << std::endl;
	return EXIT_FAILURE;
}