//
// DESCRIPTION:
//     This program performance the SRM conversion timing assessment between
//     CC, CD and UTM SRFs.  The input and output files are comma separated values
//     (.csv) formatted
//
// Usage:
//     srm_timing <input coord file> <resulting timing file>
//
// Options: none
//
// Examples:
//     srm_timing source_file.csv results_file.csv
//

#include "BaseSRF.hpp"
#include "srf_all.hpp"
#include "Exception.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cmath>

#include <time.h>

#define DISPLAY false

#define ITERATIONS 10000000

#define FACTOR        (1000000.0/ITERATIONS)          
#define RATIO         (1.0/CLOCKS_PER_SEC)
#define START_CLOCK   start_time = clock()
#define SHOW_CLOCK    end_time = clock(); \
	                    mean_time = (RATIO*(long)end_time - RATIO*(long)start_time)*FACTOR

#define toRad std::atan(1.0)/45.0

#define LINEF       std::cout << std::endl

#define SHOW_CD     std::cout << "  CD 3D coordinate=> " \
            << "[ " << CD_Coord.get_longitude() << ", " << CD_Coord.get_latitude() \
            << ", " << CD_Coord.get_ellipsoidal_height() << " ]" << std::endl
#define SHOW_UTM    std::cout << "  UTM 3D coordinate=> " \
            << "[ " << UTM_Coord.get_easting() << ", " << UTM_Coord.get_northing() \
            << ", " << UTM_Coord.get_ellipsoidal_height() << " ]" << std::endl
#define SHOW_CC     std::cout << "  CC 3D coordinate=> " \
            << "[ " << CC_Coord.get_u() << ", " << CC_Coord.get_v() \
            << ", " << CC_Coord.get_w() << " ]" << std::endl

typedef struct
{
   double var[3];
} doubleArray3;

typedef struct
{
   double var[6];
} doubleArray6;

int readCSV(FILE* infile, std::vector<doubleArray3>& inDoubleParam)
{
   //	declare string buffer
   char buffer[500]{};
   doubleArray3 data{};

   int ret_code{};

   if (std::feof(infile))
      return ret_code;

   std::fgets(buffer, 500, infile);

   if (!(std::strstr(buffer, "lon,") != NULL))
      return ret_code;

   while (buffer[0] != '\n') {
      std::fgets(buffer, 500, infile);
   }

   int j{ 1 };

   while (!std::feof(infile)) {

      std::fgets(buffer, 500, infile);
      //cout << "line=> " << buffer << endl;

      char* pch = std::strtok(buffer, ",");
      int i{};
      while (pch != nullptr) {
         // skip the item number column
         pch = std::strtok(NULL, ",");

         while (pch != NULL) {
            data.var[i++] = std::atof(pch);
            pch = std::strtok(NULL, ",");
         }

      }
      inDoubleParam.push_back(data);
      j++;
   }

   return 1;
}

void printRecord(const char* message, doubleArray3 record, int length)
{
   std::cout << message << "=> ";
   for (int i = 0; i < length; i++)
      std::cout << record.var[i] << ", ";
   std::cout << std::endl;
}

int load_file(FILE* inFile, const char* file_name, std::vector<doubleArray3>& doubleParam)
{
   inFile = std::fopen(file_name, "r");

   if (!inFile) {
      std::cout << "Unable to open " << file_name << " file";
      return false; // terminate with error
   }

   int ret_code = readCSV(inFile, doubleParam);

   std::fclose(inFile);

   return ret_code;
}

int processTiming(doubleArray3 in_coord, doubleArray6& results, const int iterations, const bool validation)
{
   clock_t start_time{}, end_time{};
   double mean_time{};
   srm::SRF_Celestiocentric* CC_SRF{};
   srm::SRF_Celestiodetic* CD_SRF{};
   srm::SRF_TransverseMercator* UTM_SRF{};

   std::cout.precision(15);

   try {
      // create SRFs and coords
      CD_SRF = srm::SRF_Celestiodetic::create(SRM_ORMCOD_WGS_1984, SRM_RTCOD_WGS_1984_IDENTITY);

      CC_SRF = srm::SRF_Celestiocentric::create(SRM_ORMCOD_WGS_1984, SRM_RTCOD_WGS_1984_IDENTITY);

      if (DISPLAY) {
         std::cout << "CD SRF parameters: " << std::endl;
         std::cout << CD_SRF->toString()    << std::endl;
         std::cout << "CC SRF parameters: " << std::endl;
         std::cout << CC_SRF->toString()    << std::endl;
      }
   } catch (srm::Exception(ex)) {
      std::cout << "Exception creating SRFs: " << ex.getWhat() << std::endl;
      return 0;
   }

   // create CD and CC 3D coordinate
   srm::Coord3D_Celestiodetic CD_Coord(CD_SRF, in_coord.var[0] * toRad, in_coord.var[1] * toRad, 0.0);
   srm::Coord3D_Celestiocentric CC_Coord(CC_SRF);

   try {
      // create SRFs and coords
      SRM_SRFT_Code srft_code;
      SRM_SRF_Code srf_code;
      SRM_SRFS_Code_Info srfs_code_info;
      UTM_SRF = static_cast<srm::SRF_TransverseMercator*>
         (srm::BaseSRF_3D::getNaturalSRFSetMember(CD_Coord,
         SRM_ORMCOD_WGS_1984,
         SRM_RTCOD_WGS_1984_IDENTITY,
         SRM_SRFSCOD_UNIVERSAL_TRANSVERSE_MERCATOR));
      if (DISPLAY) {
         UTM_SRF->getCodes(srft_code, srf_code, srfs_code_info);
         std::cout << "UTM Zone: " << srfs_code_info.value.srfsm_utm << std::endl;
         std::cout << "UTM SRF parameters: " << std::endl;
         std::cout << UTM_SRF->toString() << std::endl;
      }
   } catch (srm::Exception(ex)) {
      std::cout << "Exception creating UTM SRF: " << ex.getWhat() << std::endl;
      return 0;
   }

   srm::Coord3D_TransverseMercator UTM_Coord(UTM_SRF);

   if (validation) {
      CC_SRF->setCoordinateValidationOn();
      CD_SRF->setCoordinateValidationOn();
      UTM_SRF->setCoordinateValidationOn();
   } else {
      CC_SRF->setCoordinateValidationOff();
      CD_SRF->setCoordinateValidationOff();
      UTM_SRF->setCoordinateValidationOff();
   }

   // CD => UTM
   {
      if (DISPLAY) {
         std::cout << "CD=>UTM x " << iterations << ":" << std::endl;
      }

      START_CLOCK;

      try {
         for (int i = 0; i < iterations; i++)
            UTM_SRF->changeCoordinate3DSRF(CD_Coord, UTM_Coord);
      } catch (srm::Exception& ex) {
         std::cout << "Caught an exception=> " << ex.getWhat() << std::endl;
         return 0;
      }

      SHOW_CLOCK;
      results.var[0] = mean_time;
      if (DISPLAY) {
         SHOW_CD;
         SHOW_UTM;
         LINEF;
      }
   }

   // CD => CC
   {
      if (DISPLAY) {
         std::cout << "CD=>CC x " << iterations << ":" << std::endl;
      }

      START_CLOCK;

      try {
         for (int i = 0; i < iterations; i++)
            CC_SRF->changeCoordinate3DSRF(CD_Coord, CC_Coord);
      } catch (srm::Exception& ex) {
         std::cout << "Caught an exception=> " << ex.getWhat() << std::endl;
         return 0;
      }

      SHOW_CLOCK;
      results.var[4] = mean_time;
      if (DISPLAY) {
         SHOW_CD;
         SHOW_CC;
         LINEF;
      }
   }

   // UTM => CD
   {
      if (DISPLAY) {
         std::cout << "UTM=>CD x " << iterations << ":" << std::endl;
      }

      START_CLOCK;

      try {
         for (int i = 0; i < iterations; i++)
            CD_SRF->changeCoordinate3DSRF(UTM_Coord, CD_Coord);
      } catch (srm::Exception& ex) {
         std::cout << "Caught an exception=> " << ex.getWhat() << std::endl;
         return 0;
      }

      SHOW_CLOCK;
      results.var[1] = mean_time;
      if (DISPLAY) {
         SHOW_UTM;
         SHOW_CD;
         LINEF;
      }
   }

   // UTM => CC
   {
      if (DISPLAY) {
         std::cout << "UTM=>CC x " << iterations << ":" << std::endl;
      }

      START_CLOCK;

      try {
         for (int i = 0; i < iterations; i++)
            CC_SRF->changeCoordinate3DSRF(UTM_Coord, CC_Coord);
      } catch (srm::Exception& ex) {
         std::cout << "Caught an exception=> " << ex.getWhat() << std::endl;
         return 0;
      }

      SHOW_CLOCK;
      results.var[3] = mean_time;
      if (DISPLAY) {
         SHOW_UTM;
         SHOW_CC;
         LINEF;
      }
   }

   // CC => CD
   {
      if (DISPLAY) {
         std::cout << "CC=>CD x " << iterations << ":" << std::endl;
      }

      START_CLOCK;

      try {
         for (int i = 0; i < iterations; i++)
            CD_SRF->changeCoordinate3DSRF(CC_Coord, CD_Coord);
      } catch (srm::Exception& ex) {
         std::cout << "Caught an exception=> " << ex.getWhat() << std::endl;
         return 0;
      }

      SHOW_CLOCK;
      results.var[5] = mean_time;
      if (DISPLAY) {
         SHOW_CC;
         SHOW_CD;
         LINEF;
      }
   }

   //CC => UTM
   {
      if (DISPLAY) {
         std::cout << "CC=>UTM x " << iterations << ":" << std::endl;
      }

      START_CLOCK;

      try {
         for (int i = 0; i < iterations; i++)
            UTM_SRF->changeCoordinate3DSRF(CC_Coord, UTM_Coord);
      } catch (srm::Exception& ex) {
         std::cout << "Caught an exception=> " << ex.getWhat() << std::endl;
         return 0;
      }

      SHOW_CLOCK;
      results.var[2] = mean_time;
      if (DISPLAY) {
         SHOW_CC;
         SHOW_UTM;
         LINEF;
      }
   }

   try {
      if (DISPLAY) {
         CC_SRF->release();
         std::cout << "Released CC SRF" << std::endl;
         CD_SRF->release();
         std::cout << "Released CD SRF" << std::endl;
         UTM_SRF->release();
         std::cout << "Released UTM SRF" << std::endl;
         LINEF;
      }
   } catch (srm::Exception(ex)) {
      std::cout << "Exception releasing SRFs: " << ex.getWhat() << std::endl;
      return 0;
   }

   return 1;
}

void printRecord(std::ofstream &outStr, int num, doubleArray6 record)
{
   outStr << "Coordinate " << num << ", ";
   for (int i = 0; i < 6; i++)
      outStr << record.var[i] << ", ";
   outStr << std::endl;
}

void printRecord(std::ofstream& outStr, const char* text, const doubleArray6 record)
{
   outStr << text << ", ";
   for (int i = 0; i < 6; i++)
      outStr << record.var[i] << ", ";
   outStr << std::endl;
}

void printLines(std::ofstream& outStr, const int lines)
{
   for (int i = 0; i < lines; i++)
      outStr << std::endl;
}

void printHeader(std::ofstream& outStr, const bool validation)
{
   if (validation)
      outStr << "Timing For One Coordinate Conversion With Validation (in micro-seconds) - SRM C++";
   else
      outStr << "Timing for One Coordinate Conversion Without Validation (in micro-seconds) - SRM C++";
   outStr << std::endl << std::endl;
   outStr << "Test coord,CD to UTM,UTM to CD,CC to UTM,UTM to CC,CD to CC,CC to CD";
   outStr << std::endl << std::endl;
}

void runTest(std::vector<doubleArray3>& inDoubleParam, doubleArray6 results, const int iterations, const bool validation,
   std::ofstream& outStr)
{
   doubleArray6 min{}, max{}, mean{};

   printHeader(outStr, validation);

   for (int i = 0; i < inDoubleParam.size(); i++) {
      if (i == 0) {
         processTiming(inDoubleParam.at(i), results, iterations, validation);
         for (int j = 0; j < 6; j++) {
            min.var[j] = results.var[j];
            max.var[j] = results.var[j];
            mean.var[j] = results.var[j];
         }
      } else {
         processTiming(inDoubleParam.at(i), results, iterations, validation);
         for (int j = 0; j < 6; j++) {
            if (min.var[j] > results.var[j])
               min.var[j] = results.var[j];
            if (max.var[j] < results.var[j])
               max.var[j] = results.var[j];
            mean.var[j] += results.var[j];
         }
      }
      printRecord(outStr, i + 1, results);
   }
   for (int i = 0; i < 6; i++)
      mean.var[i] /= inDoubleParam.size();
   printLines(outStr, 1);
   printRecord(outStr, "MIN", min);
   printRecord(outStr, "MAX", max);
   printRecord(outStr, "MEAN", mean);
}

void process_arguments(int argc, char* argv[], char* source_file_name, char* target_file_name)
{
   if (argc < 3) {
      std::fprintf(stderr, "\n%s version 0.9\n", argv[0]);
      std::fprintf(stderr, "  Usage is: "
         "%s <input coord file name> <resulting timing file name>\n",
         argv[0]);
      std::exit(0);
   }

   std::memcpy(source_file_name, argv[1], std::strlen(argv[1]) + 1);
   std::memcpy(target_file_name, argv[2], std::strlen(argv[2]) + 1);
}

int main(int argc, char* argv[])
{
   std::cout.precision(15);

   LINEF;
   std::cout << "Started SRM Timing..." << std::endl;
   if (DISPLAY) {
      std::cout << "# of iterations = " << ITERATIONS << std::endl;
   }
   LINEF;

   char source_file_name[500]{};
   char result_file_name[500]{};
   process_arguments(argc, argv, source_file_name, result_file_name);

   std::FILE* inFile{};
   std::vector<doubleArray3> inDoubleParam{};
   if (!load_file(inFile, source_file_name, inDoubleParam))
      std::exit(0);

   std::ofstream outStr{};
   outStr.open(result_file_name, std::ios::out);
   if (!outStr) {
      std::cout << "Cannot open output file " << result_file_name << "\n";
      std::exit(0);
   }

   doubleArray6 results{};
   runTest(inDoubleParam, results, ITERATIONS, true, outStr);
   printLines(outStr, 2);
   runTest(inDoubleParam, results, ITERATIONS, false, outStr);
   outStr.close();
   std::cout << "Completed SRM Timing!" << std::endl;

   return 0;
}
