
#include "file_io.hpp"

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

#include "BaseSRF.hpp"
#include "srm_types.h"
#include "srf_all.hpp"

#include "types.hpp"
#include "map_data.hpp"
#include "globals.hpp"

int readCSV(std::FILE* infileSrc, std::FILE* infileTgt, std::vector<gdDatumCoord>& gdCoord)
{
   //	declare string buffer
   char srcBuffer[500]{};
   char tgtBuffer[500]{};
   gdDatumCoord gd{};

   if (std::feof(infileSrc))
      return 0;
   if (std::feof(infileTgt))
      return 0;

   std::fgets(srcBuffer, 500, infileSrc);
   std::fgets(srcBuffer, 500, infileSrc);
   std::fgets(srcBuffer, 500, infileSrc);
   std::fgets(srcBuffer, 500, infileSrc);
   std::fgets(tgtBuffer, 500, infileTgt);
   std::fgets(tgtBuffer, 500, infileTgt);
   std::fgets(tgtBuffer, 500, infileTgt);
   std::fgets(tgtBuffer, 500, infileTgt);

   while (!std::feof(infileSrc) && !std::feof(infileTgt)) {
      std::strtok(srcBuffer, " ,");
      std::strcpy(gd.datum_name_in, std::strtok(NULL, " ,"));
      gd.gd_coord_in[0] = std::atof(std::strtok(NULL, " ,"));
      gd.gd_coord_in[1] = std::atof(std::strtok(NULL, " ,"));
      gd.gd_coord_in[2] = std::atof(std::strtok(NULL, " ,"));

      std::strtok(tgtBuffer, " ,");
      std::strcpy(gd.datum_name_out, std::strtok(NULL, " ,"));
      gd.gd_coord_out[0] = std::atof(std::strtok(NULL, " ,"));
      gd.gd_coord_out[1] = std::atof(std::strtok(NULL, " ,"));
      gd.gd_coord_out[2] = std::atof(std::strtok(NULL, " ,"));

      gdCoord.push_back(gd);

      std::fgets(srcBuffer, 500, infileSrc);
      std::fgets(tgtBuffer, 500, infileTgt);
   }

   return 1;
}

int readCSV(std::FILE* infile, std::vector<configInfo>& config)
{
   //	declare string buffer
   char buffer[500]{};
   configInfo data{};

   if (std::feof(infile))
      return 0;

   std::fgets(buffer, 500, infile);

   while (!std::feof(infile)) {
      std::strcpy(data.path, std::strtok(buffer, " ,"));
      std::strcpy(data.file_name_1, std::strtok(NULL, " ,"));
      std::strcpy(data.file_name_2, std::strtok(NULL, " ,'\n'"));

      config.push_back(data);

      std::fgets(buffer, 500, infile);
   }

   return 1;
}

int readCSV(std::FILE* infile, srfParams& srf, std::vector<doubleArray3>& inDoubleParam)
{
   //	declare string buffer
   char buffer[500]{};
   doubleArray3 data{};
   char* pch{};

   if (std::feof(infile))
      return 0;

   std::fgets(buffer, 500, infile);

   while (!std::feof(infile) && std::strstr(buffer, "END OF HEADER") == NULL) {
      if (buffer[0] != '#' && buffer[0] != '\n') {
         pch = std::strtok(buffer, ":");
         if (std::strstr(pch, srfParamName[NO_HEIGHT]) != NULL) {
            srf.floatParam[NO_HEIGHT] = 1.0;
         } else if (std::strstr(pch, srfParamName[ELLIPSOID_HEIGHT]) != NULL) {
            srf.floatParam[ELLIPSOID_HEIGHT] = 1.0;
         } else {
            switch (srfParamMap[pch])
            {
            case COORDINATES:
            case PROJECTION:
               std::strcpy(srf.type, std::strtok(NULL, ", '\n'"));
               break;

            case DATUM:
            {
               std::strcpy(srf.datum_name, std::strtok(NULL, ", '\n'"));

               srf.orm = ormMap[srf.datum_name];
               srf.rt = rtMap[srf.datum_name];

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
               srf.floatParam[srfParamMap[pch]] = std::atof(std::strtok(NULL, " "));
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

      inDoubleParam.push_back(data);

      std::fgets(buffer, 500, infile);
   }

   return 1;
}

bool load_file(char* src_file_name, char* tgt_file_name, std::vector<gdDatumCoord>& gdCoord)
{
   std::FILE* inFile = std::fopen(src_file_name, "r");
   std::FILE* outFile = std::fopen(tgt_file_name, "r");

   if (!inFile) {
      std::cout << "Unable to open " << src_file_name << " file";
      return false; // terminate with error
   }

   if (!outFile) {
      std::cout << "Unable to open " << tgt_file_name << " file";
      return false; // terminate with error
   }

   readCSV(inFile, outFile, gdCoord);

   std::fclose(inFile);
   std::fclose(outFile);

   return true;
}

bool load_file(const char* file_name, srfParams& srf, std::vector<doubleArray3>& doubleParam)
{
   std::FILE* inFile = std::fopen(file_name, "r");

   if (!inFile) {
      std::cout << "Unable to open " << file_name << " file";
      return false; // terminate with error
   }

   readCSV(inFile, srf, doubleParam);

   std::fclose(inFile);

   return true;
}

void load_configuration_file(const std::string& file_name, std::vector<configInfo>& config)
{
   std::FILE* inFile = std::fopen(file_name.c_str(), "r");
   if (!inFile) {
      std::cout << "Unable to open " << file_name << " file";
      std::exit(0);
      return;
   }
   readCSV(inFile, config);
   std::fclose(inFile);
}
