// common.hpp : include file for standard system include files,
#pragma once

#include <cstdint>	 // uint8_t, etc.
#include <cmath>     // for frexp/frexpf
#include <cfloat>	 // for DBL_EPSILON, etc.
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#if __GNUC__ < 5
#define hexfloat     scientific
#define defaultfloat scientific
#endif

#include <chrono>
#include <vector>


#ifdef WINDOWS
// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#include <SDKDDKVer.h>
#endif // WINDOWS
