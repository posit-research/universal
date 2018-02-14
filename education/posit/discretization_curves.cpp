// discretization_curves.cpp: generate discretization curves to study how small posits cover the real line
//
// Copyright (C) 2017 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

#include "stdafx.h"
#include <sstream>
#include "../../posit/posit.hpp"

using namespace std;

/*
  To study how small posits discretize the real line, this test generates
  curves to compare different posit configurations.
*/


int main(int argc, char** argv)
try {
	int nrOfFailedTestCases = 0;

		cout << "Discretization Curves" << endl;

		// generate a CSV file for different posit comparisons:
		// compare posits with the same exponent structure but vary nbits = 3 till 12
		// compare posits with the same nbits, but vary es from 0 to 4

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