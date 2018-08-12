// gismo_test.cpp example testing cricial features for G+Smo integration
//
// Copyright (C) 2017-2018 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include "common.hpp"

// when you define POSIT_VERBOSE_OUTPUT executing an ADD the code will print intermediate results
//#define POSIT_VERBOSE_OUTPUT
#define POSIT_TRACE_CONVERSION

#include <string>
#include <iostream>
#include <typeinfo>
// enable posit arithmetic exceptions
#define POSIT_THROW_ARITHMETIC_EXCEPTION 1
#include <posit>

typedef sw::unum::posit<32,2> posit_32_2;

template<typename T>
void test(const std::string& message)
{
    std::cout << message << std::endl;

    // Constructor and assignment
    T v = 8;
    posit_32_2 p(v);

    p = v;

#if defined(_MSC_VER)
#pragma warning (disable : 4244)
#endif

    // Basis operators
    p += v;
    p -+ v;
    p *= v;
    p /= v;

    // Logical operators
    bool b(false);
    b = (p == v); 
    b = (p != v);
    b = (p <  v);
    b = (p >  v);
    b = (p <= v);
    b = (p >= v);
    std::cout << "(p >= v) : " << (b ? "true" : "false") << std::endl;

    // pretty print
    std::cout << color_print(p) << std::endl;
}

int main(int argc, char** argv)
try {
    using namespace std;
    using namespace sw::unum;

    test<size_t>("size_t");

    test<signed char>("signed char");
    test<short>("short");
    test<int>("int");
    test<long>("long");
    test<long long>("long long");

    test<char>("char");
    test<unsigned short>("unsigned short");
    test<unsigned int>("unsigned int");
    test<unsigned long>("unsigned long");
    test<unsigned long long>("unsigned long long");
        
    test<float>("float");
    test<double>("double");
    test<long double>("long double");

    return 0;
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
