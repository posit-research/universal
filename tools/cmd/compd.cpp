// compd.cpp: components of a double: cli to show the sign/scale/fraction components of a double
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <universal/value/value>

// receive a float and print the components of a double representation
int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;

	// double attributes
	constexpr int max_digits10 = std::numeric_limits<double>::max_digits10;
	constexpr int fbits = std::numeric_limits<double>::digits - 1;

	if (argc != 2) {
		cerr << "compd : components of an IEEE double-precision float\n";
		cerr << "Show the sign/scale/fraction components of an IEEE double.\n";
		cerr << "Usage: compf double_value\n";
		cerr << "Example: compd 0.03124999\n";
		cerr << "double: 0.031249989999999998 (+,-6,1111111111111111111101010100001100111000100011101110)" << endl;
		return EXIT_SUCCESS;   // signal successful completion for ctest
	}
	double d = atof(argv[1]);
	value<fbits> v(d);

	cout << "double: " << setprecision(max_digits10) << d << " " << components(v) << endl;
	return EXIT_SUCCESS;
}
catch (const char* const msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "caught unknown exception" << std::endl;
	return EXIT_FAILURE;
}
