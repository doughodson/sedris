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

#include <cstdlib>
#include <cmath>
#include <cstring>

#include <time.h>

#define ITERATIONS 10000000

#define FACTOR        (1000000.0 / ITERATIONS)
#define RATIO         (1.0 / CLOCKS_PER_SEC)
#define START_CLOCK   start_time = clock()
#define SHOW_CLOCK    end_time = clock(); \
	                    mean_time = (RATIO * (long)end_time - RATIO * (long)start_time) * FACTOR

#define toRad std::atan(1.0) / 45.0

#define SHOW_CD     std::cout << "  CD 3D coordinate=> " \
            << "[ " << CD_Coord.get_longitude() << ", " << CD_Coord.get_latitude() \
            << ", " << CD_Coord.get_ellipsoidal_height() << " ]" << std::endl
#define SHOW_UTM    std::cout << "  UTM 3D coordinate=> " \
            << "[ " << UTM_Coord.get_easting() << ", " << UTM_Coord.get_northing() \
            << ", " << UTM_Coord.get_ellipsoidal_height() << " ]" << std::endl
#define SHOW_CC     std::cout << "  CC 3D coordinate=> " \
            << "[ " << CC_Coord.get_u() << ", " << CC_Coord.get_v() \
            << ", " << CC_Coord.get_w() << " ]" << std::endl

struct doubleArray3
{
   double var[3]{};
};

struct doubleArray6
{
   double var[6]{};
};

void readCSV(std::FILE* infile, std::vector<doubleArray3>* inDoubleParam)
{
   //	declare string buffer
   char buffer[500]{};
   doubleArray3 data{};

   if (std::feof(infile))
      return;

   std::fgets(buffer, 500, infile);

   if (!(std::strstr(buffer, "lon,") != NULL))
      return;

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
      inDoubleParam->push_back(data);
      j++;
   }

   return;
}

void load_file(std::FILE* inFile, const std::string file_name, std::vector<doubleArray3>* doubleParam)
{
   inFile = std::fopen(file_name.c_str(), "r");

   if (!inFile) {
      std::cout << "Unable to open " << file_name << " file";
      std::exit(0);
   }

   readCSV(inFile, doubleParam);

   std::fclose(inFile);

   return;
}

void printRecord(const char* message, const doubleArray3& record, const int length)
{
   std::cout << message << "=> ";
   for (int i = 0; i < length; i++)
      std::cout << record.var[i] << ", ";
   std::cout << std::endl;
}

int processTiming(const doubleArray3 in_coord, doubleArray6* results, const int iterations, const bool validation)
{
   std::cout.precision(15);

   srm::SRF_Celestiocentric* CC_SRF{};
   srm::SRF_Celestiodetic* CD_SRF{};
   try {
      // create SRFs and coords
      CD_SRF = srm::SRF_Celestiodetic::create(SRM_ORMCOD_WGS_1984, SRM_RTCOD_WGS_1984_IDENTITY);
      CC_SRF = srm::SRF_Celestiocentric::create(SRM_ORMCOD_WGS_1984, SRM_RTCOD_WGS_1984_IDENTITY);

      std::cout << "CD SRF parameters: " << std::endl;
      std::cout << CD_SRF->toString()    << std::endl;
      std::cout << "CC SRF parameters: " << std::endl;
      std::cout << CC_SRF->toString()    << std::endl;
   } catch (srm::Exception(ex)) {
      std::cout << "Exception creating SRFs: " << ex.getWhat() << std::endl;
      return 0;
   }

   // create CD and CC 3D coordinate
   srm::Coord3D_Celestiodetic CD_Coord(CD_SRF, in_coord.var[0] * toRad, in_coord.var[1] * toRad, 0.0);
   srm::Coord3D_Celestiocentric CC_Coord(CC_SRF);

   srm::SRF_TransverseMercator* UTM_SRF{};
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

      UTM_SRF->getCodes(srft_code, srf_code, srfs_code_info);
      std::cout << "UTM Zone: " << srfs_code_info.value.srfsm_utm << std::endl;
      std::cout << "UTM SRF parameters: " << std::endl;
      std::cout << UTM_SRF->toString() << std::endl;

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

   clock_t start_time{};
   clock_t end_time{};
   double mean_time{};

   // CD => UTM
   {
      std::cout << "CD=>UTM x " << iterations << ":" << std::endl;

      START_CLOCK;

      try {
         for (int i = 0; i < iterations; i++) {
            UTM_SRF->changeCoordinate3DSRF(CD_Coord, UTM_Coord);
         }
      } catch (srm::Exception& ex) {
         std::cout << "Caught an exception=> " << ex.getWhat() << std::endl;
         return 0;
      }

      SHOW_CLOCK;
      results->var[0] = mean_time;
      SHOW_CD;
      SHOW_UTM;
      std::cout << std::endl;
   }

   // CD => CC
   {
      std::cout << "CD=>CC x " << iterations << ":" << std::endl;

      START_CLOCK;

      try {
         for (int i = 0; i < iterations; i++)
            CC_SRF->changeCoordinate3DSRF(CD_Coord, CC_Coord);
      } catch (srm::Exception& ex) {
         std::cout << "Caught an exception=> " << ex.getWhat() << std::endl;
         return 0;
      }

      SHOW_CLOCK;
      results->var[4] = mean_time;
      SHOW_CD;
      SHOW_CC;
      std::cout << std::endl;
   }

   // UTM => CD
   {
      std::cout << "UTM=>CD x " << iterations << ":" << std::endl;

      START_CLOCK;

      try {
         for (int i = 0; i < iterations; i++)
            CD_SRF->changeCoordinate3DSRF(UTM_Coord, CD_Coord);
      } catch (srm::Exception& ex) {
         std::cout << "Caught an exception=> " << ex.getWhat() << std::endl;
         return 0;
      }

      SHOW_CLOCK;
      results->var[1] = mean_time;
      SHOW_UTM;
      SHOW_CD;
      std::cout << std::endl;
   }

   // UTM => CC
   {
      std::cout << "UTM=>CC x " << iterations << ":" << std::endl;

      START_CLOCK;

      try {
         for (int i = 0; i < iterations; i++)
            CC_SRF->changeCoordinate3DSRF(UTM_Coord, CC_Coord);
      } catch (srm::Exception& ex) {
         std::cout << "Caught an exception=> " << ex.getWhat() << std::endl;
         return 0;
      }

      SHOW_CLOCK;
      results->var[3] = mean_time;
      SHOW_UTM;
      SHOW_CC;
      std::cout << std::endl;
   }

   // CC => CD
   {
      std::cout << "CC=>CD x " << iterations << ":" << std::endl;

      START_CLOCK;

      try {
         for (int i = 0; i < iterations; i++)
            CD_SRF->changeCoordinate3DSRF(CC_Coord, CD_Coord);
      } catch (srm::Exception& ex) {
         std::cout << "Caught an exception=> " << ex.getWhat() << std::endl;
         return 0;
      }

      SHOW_CLOCK;
      results->var[5] = mean_time;
      SHOW_CC;
      SHOW_CD;
      std::cout << std::endl;
   }

   //CC => UTM
   {
      std::cout << "CC=>UTM x " << iterations << ":" << std::endl;

      START_CLOCK;

      try {
         for (int i = 0; i < iterations; i++)
            UTM_SRF->changeCoordinate3DSRF(CC_Coord, UTM_Coord);
      } catch (srm::Exception& ex) {
         std::cout << "Caught an exception=> " << ex.getWhat() << std::endl;
         return 0;
      }

      SHOW_CLOCK;
      results->var[2] = mean_time;
      SHOW_CC;
      SHOW_UTM;
      std::cout << std::endl;
   }

   try {
      CC_SRF->release();
      std::cout << "Released CC SRF" << std::endl;
      CD_SRF->release();
      std::cout << "Released CD SRF" << std::endl;
      UTM_SRF->release();
      std::cout << "Released UTM SRF" << std::endl;
      std::cout << std::endl;
   } catch (srm::Exception(ex)) {
      std::cout << "Exception releasing SRFs: " << ex.getWhat() << std::endl;
      return 0;
   }

   return 1;
}

void printRecord(std::ofstream &outStr, const int num, const doubleArray6 record)
{
   outStr << "Coordinate " << num << ", ";
   for (int i = 0; i < 6; i++)
      outStr << record.var[i] << ", ";
   outStr << std::endl;
}

void printRecord(std::ofstream& outStr, const std::string text, const doubleArray6& record)
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

void runTest(std::vector<doubleArray3>* inDoubleParam, doubleArray6* results, const int iterations, const bool validation,
   std::ofstream& outStr)
{
   doubleArray6 min{};
   doubleArray6 max{};
   doubleArray6 mean{};

   printHeader(outStr, validation);

   for (int i = 0; i < inDoubleParam->size(); i++) {
      if (i == 0) {
         processTiming(inDoubleParam->at(i), results, iterations, validation);
         for (int j = 0; j < 6; j++) {
            min.var[j] = results->var[j];
            max.var[j] = results->var[j];
            mean.var[j] = results->var[j];
         }
      } else {
         processTiming(inDoubleParam->at(i), results, iterations, validation);
         for (int j = 0; j < 6; j++) {
            if (min.var[j] > results->var[j])
               min.var[j] = results->var[j];
            if (max.var[j] < results->var[j])
               max.var[j] = results->var[j];
            mean.var[j] += results->var[j];
         }
      }
      printRecord(outStr, i + 1, *results);
   }
   for (int i = 0; i < 6; i++) {
      mean.var[i] /= inDoubleParam->size();
   }
   printLines(outStr, 1);
   printRecord(outStr, "MIN", min);
   printRecord(outStr, "MAX", max);
   printRecord(outStr, "MEAN", mean);
}

int main(int argc, char* argv[])
{
   if (argc < 3) {
      std::cout << "Usage is: test_srm_timing <input coord file name> <resulting timing file name>\n";
      std::cout << std::endl;
      std::exit(0);
   }

   std::string source_file_name{argv[1]};
   std::string result_file_name{argv[2]};

   std::FILE* inFile{};
   std::vector<doubleArray3> inDoubleParam{};
   load_file(inFile, source_file_name, &inDoubleParam);

   std::ofstream outStr{};
   outStr.open(result_file_name, std::ios::out);
   if (!outStr) {
      std::cout << "Cannot open output file " << result_file_name << "\n";
      std::exit(0);
   }

   std::cout << std::endl;
   std::cout << "Started SRM Timing..." << std::endl;
   std::cout << "# of iterations = " << ITERATIONS << std::endl;
   std::cout << std::endl;

   std::cout.precision(15);
   doubleArray6 results;
   runTest(&inDoubleParam, &results, ITERATIONS, true, outStr);
   printLines(outStr, 2);
   runTest(&inDoubleParam, &results, ITERATIONS, false, outStr);
   outStr.close();
   std::cout << "Completed SRM Timing!" << std::endl;

   return 0;
}
