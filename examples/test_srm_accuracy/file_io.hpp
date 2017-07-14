
#ifndef __file_io_HPP__
#define __file_io_HPP__

#include <cstdio>
#include <vector>
#include <string>

#include "srm_types.h"

#include "types.hpp"

bool load_file(const std::string& src_file_name, const std::string& tgt_file_name, std::vector<gdDatumCoord>& gdCoord);

bool load_file(const std::string& file_name, srfParams& srf, std::vector<doubleArray3>& doubleParam);

void load_configuration_file(const std::string& file_name, std::vector<configInfo>* config);

#endif

