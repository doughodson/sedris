
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

void load_gdDatumCoords(const std::string& src_file_name, const std::string& tgt_file_name, std::vector<gdDatumCoord>* gdCoord)
{
   std::FILE* inFile = std::fopen(src_file_name.c_str(), "r");
   if (!inFile) {
      std::cout << "Unable to open " << src_file_name << " file";
      std::exit(0);
   }

   std::FILE* outFile = std::fopen(tgt_file_name.c_str(), "r");
   if (!outFile) {
      std::cout << "Unable to open " << tgt_file_name << " file";
      std::exit(0);
   }

   if (std::feof(inFile))
      return;

   if (std::feof(outFile))
      return;

   char srcBuffer[500]{};
   std::fgets(srcBuffer, 500, inFile);
   std::fgets(srcBuffer, 500, inFile);
   std::fgets(srcBuffer, 500, inFile);
   std::fgets(srcBuffer, 500, inFile);

   char tgtBuffer[500]{};
   std::fgets(tgtBuffer, 500, outFile);
   std::fgets(tgtBuffer, 500, outFile);
   std::fgets(tgtBuffer, 500, outFile);
   std::fgets(tgtBuffer, 500, outFile);

   gdDatumCoord gd;
   while (!std::feof(inFile) && !std::feof(outFile)) {
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

      std::fgets(srcBuffer, 500, inFile);
      std::fgets(tgtBuffer, 500, outFile);
   }
   std::fclose(inFile);
   std::fclose(outFile);
}

void load_file(const std::string& file_name, srfParams* srf, std::vector<doubleArray3>* doubleParam)
{
   //std::cout << "filename to parse: " << file_name << std::endl;

   std::FILE* file = std::fopen(file_name.c_str(), "r");

   if (!file) {
      std::cout << "Unable to open " << file_name << " file";
      std::exit(0);
   }

   if (std::feof(file))
      return;

   char buffer[500]{};
   std::fgets(buffer, 500, file);

   // read header section
   while (!std::feof(file) && std::strstr(buffer, "END OF HEADER") == NULL) {
      if (buffer[0] != '#' && buffer[0] != '\n') {
         const char* const pch = std::strtok(buffer, ":");
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
                  srf->datum_name = std::strtok(NULL, ", '\n'");
                  srf->orm = ormMap[srf->datum_name];
                  srf->rt = rtMap[srf->datum_name];
                  break;

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

      std::fgets(buffer, 500, file);
   }

   std::fgets(buffer, 500, file);

   // read past any blank or comment lines
   while (buffer[0] == '\n' || buffer[0] == '#') {
      std::fgets(buffer, 500, file);
   }

   // read main data section
   while (!std::feof(file)) {
      doubleArray3 data{};
      const char* pch = std::strtok(buffer, " ,");

      int i{};
      while (pch != NULL) {
         data.var[i++] = std::atof(pch);
         pch = std::strtok(NULL, " ,");
      }

      // set the 3rd component value (height) to 0.0 if no height data
      if (i == 2)
         data.var[i] = 0.0;

      doubleParam->push_back(data);

      std::fgets(buffer, 500, file);
   }

   std::fclose(file);
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

