// math_functions.cpp example showing the supported math functions
//
// Copyright (C) 2017-2018 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include "common.hpp"
#include <complex>

// when you define POSIT_VERBOSE_OUTPUT executing an ADD the code will print intermediate results
//#define POSIT_VERBOSE_OUTPUT
#define POSIT_TRACE_CONVERSION

#include <posit>

int main(int argc, char** argv)
try {
	using namespace sw::unum;
	bool bSuccess = true;

	posit<32, 2> x(1.0), y(-1.0), p(0);
	std::complex< posit<32, 2> > c(x,y),d;

	// sign and absolute value
	bool s;
	s = sign(x); std::cout << "Sign of " << x << " is " << s << '\n';
	s = sign(y); std::cout << "Sign of " << y << " is " << s << '\n';
	p =  abs(y); std::cout << " abs(" << y << ") = " << p << '\n';
	p = fabs(y); std::cout << "fabs(" << y << ") = " << p << '\n';

	// truncation functions
	x = 1.5;
	p =  ceil(x); std::cout << " ceil(" << x << ") = " << p << '\n';
	p = floor(x); std::cout << "floor(" << x << ") = " << p << '\n';
	p = round(x); std::cout << "round(" << x << ") = " << p << '\n';
	p = trunc(x); std::cout << "trunc(" << x << ") = " << p << '\n';

	// complex functions
	p = real(c); std::cout << "real(" << c << ") = " << p << '\n';
	p = imag(c); std::cout << "imag(" << c << ") = " << p << '\n';
	d = conj(c); std::cout << "conj(" << c << ") = " << d << '\n';
	
	// sqrt and inverse sqrt
	x = m_pi_4;
	p =  sqrt(x); std::cout << " sqrt(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p = rsqrt(x); std::cout << "rsqrt(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';

	// trigonometric functions
	p =  sin(x); std::cout << "  sin(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p = asin(x); std::cout << " asin(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p =  cos(x); std::cout << "  cos(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p = acos(x); std::cout << " acos(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p =  tan(x); std::cout << "  tan(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p = atan(x); std::cout << " atan(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';

	// hyperbolic functions
	p =  sinh(x); std::cout << " sinh(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p = asinh(x); std::cout << "asinh(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p =  cosh(x); std::cout << " cosh(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p = acosh(x); std::cout << "acosh(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p =  tanh(x); std::cout << " tanh(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p = atanh(x); std::cout << "atanh(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';

	// error and gamma functions
	p =  erf(x); std::cout << "  erf(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p = erfc(x); std::cout << " erfc(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';

	// exponential and logarithmic functions

	p =   exp(x); std::cout << "  exp(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p =  exp2(x); std::cout << " exp2(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p = exp10(x); std::cout << "exp10(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p =   log(x); std::cout << "  log(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p =  log2(x); std::cout << " log2(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';
	p = log10(x); std::cout << "log10(" << x << ")    = " << std::setw(10) << p << " " << color_print(p) << '\n';

	p = pow(x, y); std::cout << "  pow(" << x << "," << y << ") = " << std::setw(10) << p << " " << color_print(p) << '\n';

	return (bSuccess ? EXIT_SUCCESS : EXIT_FAILURE);
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << std::endl;
	return EXIT_FAILURE;
}
