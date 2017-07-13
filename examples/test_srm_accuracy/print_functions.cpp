
#include "print_functions.hpp"

#include "srm_types.h"
#include "srf_all.hpp"

#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>

void printData(const std::vector<doubleArray3>& inDoubleParam, const int length)
{
   doubleArray3 data{};

   for (int i = 0; i < static_cast<int>(inDoubleParam.size()); i++) {
      data = inDoubleParam.at(i);
      std::cout << i + 1 << " ";
      for (int j = 0; j < length; j++)
         std::cout << data.var[j] << ", ";
      std::cout << std::endl;
   }
}

void printData(const gdDatumCoord& gdCoord)
{
   std::cout << "CD DT Coord=> " << gdCoord.datum_name_in << ", ";
   std::cout << gdCoord.datum_name_out << ", ";
   std::cout << "( " << gdCoord.gd_coord_in[0] << ", " << gdCoord.gd_coord_in[1] << ", " << gdCoord.gd_coord_in[2] << " )" << std::endl;
   std::cout << "( " << gdCoord.gd_coord_out[0] << ", " << gdCoord.gd_coord_out[1] << ", " << gdCoord.gd_coord_out[2] << " )" << std::endl;
   std::cout << "( " << gdCoord.comp_coord_out[0] << ", " << gdCoord.comp_coord_out[1] << ", " << gdCoord.comp_coord_out[2] << " )" << std::endl;
}

void printData(const std::vector<configInfo>& config)
{
   for (int i = 0; i < static_cast<int>(config.size()); i++) {
      configInfo data = config.at(i);
      std::cout << data.path << ", " << data.file_name_1 << ", " << data.file_name_2 << std::endl;
   }
}

void printData(const statInfo& results)
{
   std::cout << "Count => "  << results.count << std::endl;
   std::cout << "Min   => "  << results.min << std::endl;
   std::cout << "Max   => "  << results.max << std::endl;
   std::cout << "Mean  => "  << results.mean << std::endl;
   std::cout << "StdDev=> "  << results.stdDev << std::endl;
   std::cout << "Message=> " << results.message << std::endl;
}

void printData(const srm::Coord3D* coord)
{
   std::cout << "[ ";
   std::cout << coord->getValues()[0] << ", ";
   std::cout << coord->getValues()[1] << ", ";
   std::cout << coord->getValues()[2] << " ]";
   std::cout << std::endl;
}

void printData(const doubleArray3& coord)
{
   std::cout << "[ " << coord.var[0] * toRad;
   std::cout << ", ";
   std::cout << coord.var[1] * toRad << ", ";
   std::cout << coord.var[2] << " ]" << std::endl;
}

void printData(const std::vector<diffInfo>& diffs)
{
   for (int i = 0; i < diffs.size(); i++) {
      std::cout << i << ", ";
      std::cout << diffs[i].compOut.var[0] << ", ";
      std::cout << diffs[i].compOut.var[1] << ", ";
      std::cout << diffs[i].compOut.var[2] << ", ";
      std::cout << diffs[i].diff << std::endl;
   }
}

void printData(const srfParams& srfParam)
{
   std::cout << "srfParam.orm=> " << srfParam.orm << std::endl;
   std::cout << "srfParam.rt=> " << srfParam.rt << std::endl;
   std::cout << "srfParam.type=> " << srfParam.type << std::endl;
   std::cout << "srfParam.floatParam => " << std::endl;
   for (int i = 0; i < 8; i++)
      std::cout << "srf param [" << i << "]=SRM_ORMCOD_> " << srfParam.floatParam[i] << std::endl;
}

void printRecord(std::ofstream& outStr, const int num, const statInfo& results)
{
   outStr << "Coordinate " << num << ", ";
   outStr << std::endl;
}

void printConvHeader(std::ofstream& outStr, const bool more)
{
   std::time_t date;  // Make a time_t object that'll hold the date
   time(&date);       //  Set the date variable to the current date

   outStr << "Coordinate conversion accuracy assessment for SRM C++" << std::endl;
   outStr << "(The results are given as the Euclidean distance (in meters) between the ";
   outStr << "computed coordinate and the golden data)" << std::endl << std::endl;
   outStr << "Test conducted: " << ctime(&date) << std::endl;
   outStr << "ORM/RT, Conversion, Count, MIN (m), MAX (m)";
   if (more)
      outStr << ", # > 0.001, max #, g_in1, g_in2, g_out1, g_out2, c_out1, c_out2, #";
   outStr << std::endl << std::endl;
}

void printDatumHeader(std::ofstream& outStr, const bool more)
{
   time_t date; // Make a time_t object that'll hold the date
   time(&date); //  Set the date variable to the current date

   outStr << "Datum conversion accuracy assessment for SRM C++ 4.3" << std::endl;
   outStr << "(The results are given as the Euclidean distance (in meters) between the ";
   outStr << "computed coordinate and the golden data)" << std::endl << std::endl;
   outStr << "Test conducted: " << ctime(&date) << std::endl;
   outStr << "Src ORM, Tgt ORM, Count, MIN (m), MAX (m)";
   if (more)
      outStr << ", MAX_DIFF > 0.001";
   outStr << std::endl << std::endl;
}

void printData(std::ofstream& outStr,
   std::vector<doubleArray3>& srcDoubleParam,
   std::vector<doubleArray3>& tgtDoubleParam,
   std::vector<doubleArray3>& compDoubleParam,
   char* datum,
   std::vector<bool>& exceeded,
   const char* source_file_name,
   const char* target_file_name,
   statInfo& results,
   bool more)
{
   double toRadConv{ 1.0 };

   if (results.isCD)
      toRadConv = toRad;

   outStr << datum << ", ";
   outStr << source_file_name << " to ";
   outStr << target_file_name << ", ";

   if (results.message[0] == '\0') {
      outStr << results.count << ", ";
      outStr << results.min << ", ";
      outStr << results.max;
      if (more) {
         outStr << ", ";
         outStr << results.num_exceeded << ", ";
         outStr << results.dataPoint << ", ";
         outStr << srcDoubleParam[results.dataPoint].var[0] << ", ";
         outStr << srcDoubleParam[results.dataPoint].var[1] << ", ";
         outStr << tgtDoubleParam[results.dataPoint].var[0] * toRadConv << ", ";
         outStr << tgtDoubleParam[results.dataPoint].var[1] * toRadConv << ", ";
         outStr << compDoubleParam[results.dataPoint].var[0] << ", ";
         outStr << compDoubleParam[results.dataPoint].var[1] << std::endl;

         for (int i = 0; i < srcDoubleParam.size(); i++) {
            outStr << ",,,,,,";
            if (i == results.dataPoint)
               outStr << "MAX =>,";
            else
               outStr << ",";
            outStr << srcDoubleParam[i].var[0] << ", ";
            outStr << srcDoubleParam[i].var[1] << ", ";
            outStr << tgtDoubleParam[i].var[0] * toRadConv << ", ";
            outStr << tgtDoubleParam[i].var[1] * toRadConv << ", ";
            outStr << compDoubleParam[i].var[0] << ", ";
            outStr << compDoubleParam[i].var[1] << ", ";
            outStr << i << std::endl;
         }
      } else {
         outStr << std::endl;
      }
   } else {
      outStr << results.message << std::endl;
   }
}

void printData(std::ofstream& outStr, std::vector<gdDatumStat>& gdCoord, const bool more)
{
   for (int i = 0; i < gdCoord.size(); i++) {
      outStr << gdCoord[i].datum_name_in << ", ";
      outStr << gdCoord[i].datum_name_out << ", ";
      outStr << gdCoord[i].count << ", ";
      outStr << gdCoord[i].min << ", ";
      outStr << gdCoord[i].max;
      if (more) {
         if (gdCoord[i].max > 0.001)
            outStr << ", " << 1;
         else
            outStr << ", " << 0;
      }
      outStr << std::endl;
   }
}


