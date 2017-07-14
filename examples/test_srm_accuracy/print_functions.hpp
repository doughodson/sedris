
#ifndef __print_functions_HPP__
#define __print_functions_HPP__

#include <vector>
#include <iostream>
#include <string>

#include "types.hpp"

void print_configuration_data(const std::vector<configInfo>& config);

void printData(const std::vector<doubleArray3>& inDoubleParam, const int length);
void printData(const gdDatumCoord& gdCoord);
void printData(const statInfo& results);
void printData(const doubleArray3& coord);
void printData(const std::vector<diffInfo>& diffs);
void printData(const srfParams& srfParam);

void printRecord(std::ofstream& outStr, const int num, const statInfo& results);

void printConvHeader(std::ofstream& outStr, const bool more);

void printDatumHeader(std::ofstream& outStr, const bool more);

void printData(std::ofstream& outStr,
   std::vector<doubleArray3>& srcDoubleParam,
   std::vector<doubleArray3>& tgtDoubleParam,
   std::vector<doubleArray3>& compDoubleParam,
   std::string& datum,
   std::vector<bool>& exceeded,
   const std::string& source_file_name,
   const std::string& target_file_name,
   statInfo& results,
   bool more);

void printData(std::ofstream& outStr, std::vector<gdDatumStat>& gdCoord, const bool more);

#endif
