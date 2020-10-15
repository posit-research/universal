// posit_8b.cpp: performance characterization of standard posit<8,0> configuration
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

// enable fast specialized posit<4,0>
//#define POSIT_FAST_SPECIALIZATION
#define POSIT_FAST_POSIT_4_0 1
// enable/disable posit arithmetic exceptions
#define POSIT_THROW_ARITHMETIC_EXCEPTION 1
#include <universal/posit/posit>
#include "posit_performance.hpp"

int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;

	constexpr size_t nbits = 4;
	constexpr size_t es = 0;

#if defined(POSIT_FAST_POSIT_4_0)
	cout << "Fast specialization posit<4,0> configuration performance tests" << endl;
#else
	cout << "Reference posit<4,0> configuration performance tests" << endl;
#endif

	OperatorPerformance perfReport;
	GeneratePerformanceReport<nbits, es>(perfReport);
	ReportPerformance<nbits, es>(cout, "posit<4,0>", perfReport);

	return EXIT_SUCCESS;
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (const posit_arithmetic_exception& err) {
	std::cerr << "Uncaught posit arithmetic exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const quire_exception& err) {
	std::cerr << "Uncaught quire exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const posit_internal_exception& err) {
	std::cerr << "Uncaught posit internal exception: " << err.what() << std::endl;
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
