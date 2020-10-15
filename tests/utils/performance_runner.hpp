//  performance_runner.cpp : functions to aid in performance testing and reporting
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>


// convert a floating point value to a power-of-ten string
template<typename Ty>
std::string toPowerOfTen(Ty value) {
	const char* scales[] = { " ", "K", "M", "G", "T" };
	Ty lower_bound = Ty(1);
	Ty scale_factor = 1.0;
	int integer_value = 0;
	int scale = 0;
	for (unsigned i = 0; i < sizeof(scales); ++i) {
		if (value > lower_bound && value < 1000 * lower_bound) {
			integer_value = int(value / scale_factor);
			scale = i;
			break;
		}
		lower_bound *= 1000;
		scale_factor *= 1000.0;
	}
	std::stringstream ss;
	ss << std::setw(3) << std::right << integer_value << ' ' << scales[scale];
	return ss.str();
}

// generic test runner, takes a function that enumerates an operator NR_OPS time, and measures elapsed time
void PerformanceRunner(const std::string& tag, void (f)(uint64_t), uint64_t NR_OPS) {
	using namespace std;
	using namespace std::chrono;

	steady_clock::time_point begin = steady_clock::now();
		f(NR_OPS);
	steady_clock::time_point end = steady_clock::now();
	duration<double> time_span = duration_cast< duration<double> > (end - begin);
	double elapsed_time = time_span.count();

	cout << tag << ' ' << setw(10) << NR_OPS << " per " << setw(15) << elapsed_time << "sec -> " << toPowerOfTen(double(NR_OPS)/elapsed_time) << "ops/sec" << endl;
}
