
#include "globals.hpp"

#include <fstream>

const char* datum[] = { "WGE",
"Test_SRMmax",
"Test_sphere" };

const char* srfParamName[] = { "CENTRAL MERIDIAN",
"ORIGIN LATITUDE",
"SCALE FACTOR",
"STANDARD PARALLEL ONE",
"STANDARD PARALLEL TWO",
"LONGITUDE DOWN FROM POLE",
"LATITUDE OF TRUE SCALE",
"FALSE EASTING",
"FALSE NORTHING",
"NO HEIGHT",
"ELLIPSOID HEIGHT",
"DATUM",
"COORDINATES",
"PROJECTION" };

const char* srfName[] = { "Transverse Mercator",
"Mercator",
"Polar Stereographic",
"Ney's (Modified Lambert Conformal Conic)",
"Geodetic",
"Lambert Conformal Conic (1 parallel)",
"Geocentric",
"Spherical",
"Ellipsoidal" };

std::ofstream srfs;
