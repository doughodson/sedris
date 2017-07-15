
#ifndef __file_io_HPP__
#define __file_io_HPP__

#include <cstdio>
#include <vector>
#include <string>

#include "srm_types.h"

#include "types.hpp"

void load_gdDatumCoords(const std::string& src_file_name, const std::string& tgt_file_name, std::vector<gdDatumCoord>*);

void load_file(const std::string& file_name, srfParams*, std::vector<doubleArray3>*);

void load_configuration_file(const std::string& file_name, std::vector<configInfo>* config);

#endif

