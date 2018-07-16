// enumeration.cpp: examples of enumerating the posit state space
//
// Copyright (C) 2017-2018 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

#include "common.hpp"
#include <posit>

// example of enumerating the state space of a posit configuration
int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;

	cout << "State space enumeration" << endl;

	constexpr int nbits = 5;
	constexpr int es = 0;	

	cout << "Increment-based ascention from 0 to NaR and back to 0\n";
	posit<nbits, es> p(0);
	for (size_t i = 0; i <= (size_t(1) << nbits); ++i) {
		cout << components_to_string(p++) << '\n';
	}

	// reverse enumeration from NaR to 0
	cout << "Decrement-based descention from NaR to 0 and back to NaR\n";
	p.setToNaR();
	for (long i = (size_t(1) << nbits); i >= 0; --i) {
		cout << components_to_string(p--) << '\n';
	}
	cout << endl;

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
