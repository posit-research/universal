// dc.cpp: double components: show the sign/scale/fraction components of a double
//
// Copyright (C) 2017-2018 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

#include "stdafx.h"

#include <value>

using namespace std;
using namespace sw::unum;

// receive a float and print the components of a double representation
int main(int argc, char** argv)
try {
	// double attributes
	constexpr int max_digits10 = std::numeric_limits<double>::max_digits10;
	constexpr int fbits = std::numeric_limits<double>::digits - 1;

	if (argc != 2) {
		cerr << "Show the sign/scale/fraction components of a double." << endl;
		cerr << "Usage: dc double_value" << endl;
		cerr << "Example: dc 0.03124999" << endl;
		cerr << "double: 0.031249989999999998 (+,-6,1111111111111111111101010100001100111000100011101110)" << endl;
		return EXIT_SUCCESS;   // signal successful completion for ctest
	}
	double d = atof(argv[1]);
	value<fbits> v(d);

	cout << "double: " << setprecision(max_digits10) << d << " " << components(v) << endl;
	return EXIT_SUCCESS;
}
catch (char const* msg) {
	cerr << msg << endl;
	return EXIT_FAILURE;
}
catch (...) {
	cerr << "Caught unknown exception" << endl;
	return EXIT_FAILURE;
}
