
#ifndef __file_io_HPP__
#define __file_io_HPP__

#include <cstdio>
#include <vector>

#include "srm_types.h"

#include "types.hpp"

int readCSV(std::FILE* infileSrc, std::FILE* infileTgt, std::vector<gdDatumCoord>& gdCoord);
int readCSV(std::FILE* infile, std::vector<configInfo>& config);
int readCSV(std::FILE* infile, srfParams& srf, std::vector<doubleArray3>& inDoubleParam);

bool load_file(char* src_file_name, char* tgt_file_name, std::vector<gdDatumCoord>& gdCoord);
bool load_file(const char* file_name, srfParams& srf, std::vector<doubleArray3>& doubleParam);
bool load_file(const char* file_name, std::vector<configInfo>& config);

#endif

