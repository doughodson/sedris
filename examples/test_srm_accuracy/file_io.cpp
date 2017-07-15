
#include "file_io.hpp"

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>

#include "BaseSRF.hpp"
#include "srm_types.h"
#include "srf_all.hpp"

#include "types.hpp"
#include "map_data.hpp"
#include "globals.hpp"

void read_gdDatumCoord_CSV(std::FILE* infileSrc, std::FILE* infileTgt, std::vector<gdDatumCoord>* gdCoord)
{
   if (std::feof(infileSrc))
      return;
   if (std::feof(infileTgt))
      return;

   //	declare string buffer
   char srcBuffer[500]{};
   char tgtBuffer[500]{};

   std::fgets(srcBuffer, 500, infileSrc);
   std::fgets(srcBuffer, 500, infileSrc);
   std::fgets(srcBuffer, 500, infileSrc);
   std::fgets(srcBuffer, 500, infileSrc);
   std::fgets(tgtBuffer, 500, infileTgt);
   std::fgets(tgtBuffer, 500, infileTgt);
   std::fgets(tgtBuffer, 500, infileTgt);
   std::fgets(tgtBuffer, 500, infileTgt);

   gdDatumCoord gd;
   while (!std::feof(infileSrc) && !std::feof(infileTgt)) {
      std::strtok(srcBuffer, " ,");
      gd.datum_name_in = std::strtok(NULL, " ,");
      gd.gd_coord_in[0] = std::atof(std::strtok(NULL, " ,"));
      gd.gd_coord_in[1] = std::atof(std::strtok(NULL, " ,"));
      gd.gd_coord_in[2] = std::atof(std::strtok(NULL, " ,"));

      std::strtok(tgtBuffer, " ,");
      gd.datum_name_out = std::strtok(NULL, " ,");
      gd.gd_coord_out[0] = std::atof(std::strtok(NULL, " ,"));
      gd.gd_coord_out[1] = std::atof(std::strtok(NULL, " ,"));
      gd.gd_coord_out[2] = std::atof(std::strtok(NULL, " ,"));

      gdCoord->push_back(gd);

      std::fgets(srcBuffer, 500, infileSrc);
      std::fgets(tgtBuffer, 500, infileTgt);
   }
}

void load_gdDatumCoords(const std::string& src_file_name, const std::string& tgt_file_name, std::vector<gdDatumCoord>* gdCoord)
{
   std::FILE* inFile = std::fopen(src_file_name.c_str(), "r");
   std::FILE* outFile = std::fopen(tgt_file_name.c_str(), "r");

   if (!inFile) {
      std::cout << "Unable to open " << src_file_name << " file";
      std::exit(0);
   }

   if (!outFile) {
      std::cout << "Unable to open " << tgt_file_name << " file";
      std::exit(0);
   }

   read_gdDatumCoord_CSV(inFile, outFile, gdCoord);

   std::fclose(inFile);
   std::fclose(outFile);
}

void read_CSV(std::FILE* infile, srfParams* srf, std::vector<doubleArray3>* inDoubleParam)
{
   if (std::feof(infile))
      return;

   //	declare string buffer
   char buffer[500]{};
   std::fgets(buffer, 500, infile);

   doubleArray3 data{};
   char* pch{};
   while (!std::feof(infile) && std::strstr(buffer, "END OF HEADER") == NULL) {
      if (buffer[0] != '#' && buffer[0] != '\n') {
         pch = std::strtok(buffer, ":");
         if (std::strstr(pch, srfParamName[NO_HEIGHT]) != NULL) {
            srf->floatParam[NO_HEIGHT] = 1.0;
         } else if (std::strstr(pch, srfParamName[ELLIPSOID_HEIGHT]) != NULL) {
            srf->floatParam[ELLIPSOID_HEIGHT] = 1.0;
         } else {
            switch (srfParamMap[pch]) {
            case COORDINATES:
            case PROJECTION:
               srf->type = std::strtok(NULL, ", '\n'");
               break;

            case DATUM:
            {
               srf->datum_name = std::strtok(NULL, ", '\n'");

               srf->orm = ormMap[srf->datum_name];
               srf->rt = rtMap[srf->datum_name];

               break;
            }

            case CENTRAL_MERIDIAN:
            case ORIGIN_LATITUDE:
            case SCALE_FACTOR:
            case STANDARD_PARALLEL_ONE:
            case STANDARD_PARALLEL_TWO:
            case LONGITUDE_DOWN_FROM_POLE:
            case LATITUDE_OF_TRUE_SCALE:
            case FALSE_EASTING:
            case FALSE_NORTHING:
               srf->floatParam[srfParamMap[pch]] = std::atof(std::strtok(NULL, " "));
               break;

            default:
               std::cout << "ERROR: SRF parameter not supported" << std::endl;
               break;
            }
         }
      }

      std::fgets(buffer, 500, infile);
   }

   std::fgets(buffer, 500, infile);

   while (buffer[0] == '\n' || buffer[0] == '#') {
      std::fgets(buffer, 500, infile);
   }

   while (!std::feof(infile)) {
      pch = std::strtok(buffer, " ,");

      int i = 0;
      while (pch != NULL) {
         data.var[i++] = std::atof(pch);
         pch = std::strtok(NULL, " ,");
      }

      // set the 3rd component value (height) to 0.0 if no height data
      if (i == 2)
         data.var[i] = 0.0;

      inDoubleParam->push_back(data);

      std::fgets(buffer, 500, infile);
   }
}

void load_file(const std::string& file_name, srfParams* srf, std::vector<doubleArray3>* doubleParam)
{
   std::FILE* inFile = std::fopen(file_name.c_str(), "r");

   if (!inFile) {
      std::cout << "Unable to open " << file_name << " file";
      std::exit(0);
   }

   read_CSV(inFile, srf, doubleParam);

   std::fclose(inFile);
}

void load_configuration_file(const std::string& file_name, std::vector<configInfo>* config)
{
   std::FILE* file = std::fopen(file_name.c_str(), "r");
   if (!file) {
      std::cout << "Unable to open " << file_name << " file";
      std::exit(0);
      return;
   }

   if (std::feof(file))
      return;

   char buffer[500]{};
   std::fgets(buffer, 500, file);

   configInfo data{};
   while (!std::feof(file)) {
      data.path = std::strtok(buffer, " ,");
      data.file_name_1 = std::strtok(NULL, " ,");
      data.file_name_2 = std::strtok(NULL, " ,'\n'");

      config->push_back(data);

      std::fgets(buffer, 500, file);
   }

   std::fclose(file);
}

