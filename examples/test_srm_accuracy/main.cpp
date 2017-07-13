//
// DESCRIPTION:
//     This program computes coordinate conversions and compare their results
//     against the NGA golden data whose paths are listed in the command line argument
//     configuration file.
//
// Dependency: SRM C/C++ SDK
//

#include "BaseSRF.hpp"
#include "srf_all.hpp"
#include "srm_types.h"
#include "Exception.hpp"

#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>

#include "types.hpp"
#include "print_functions.hpp"
#include "map_data.hpp"
#include "file_io.hpp"
#include "globals.hpp"

double computeRn(const double a, const double e, const double phi)
{
   const double sphi{std::sin(phi)};
   return (a / (std::sqrt(1 - e*e*sphi*sphi)));
}

double computeRm(const double a, const double e, const double Rn)
{
   return ((1.0 - e*e) * (Rn*Rn*Rn) / (a*a));
}

double computeK0(SRM_ORM_Code orm, const double phi)
{
   double a{};
   double f{};
   double e{};

   switch (orm) {
   case SRM_ORMCOD_WGS_1984:
      a = WGS84_A;
      f = WGS84_F;
      e = WGS84_e;
      break;

   case SRM_ORMCOD_EXPERIMENTAL_NGA_MAX:
      a = MAX_A;
      f = MAX_F;
      e = MAX_e;
      break;

   case SRM_ORMCOD_EXPERIMENTAL_NGA_SPHERE:
      a = SPHR_A;
      f = SPHR_F;
      e = SPHR_e;
      break;

   default:
      std::cout << "ERROR: ORM not supported" << std::endl;
   }

   return ((computeRn(a, e, phi) * std::cos(phi)) / a);
}

double computeE(const double f, const double e)
{
   return (std::pow((1.0 - e) / (1.0 + e), e / 2.0) / (1 - f));
}

double computeTau(const double e, const double phi)
{
   return (std::tan(PI_OVER_4 - (std::fabs(phi) / 2.0)) *
      std::pow((1.0 + e * std::sin(std::fabs(phi))) / (1.0 - e * std::sin(std::fabs(phi))), e / 2.0));
}

double computePsK0(SRM_ORM_Code orm, const double phi)
{
   double a{};
   double f{};
   double e{};

   switch (orm) {
   case SRM_ORMCOD_WGS_1984:
      a = WGS84_A;
      f = WGS84_F;
      e = WGS84_e;
      break;

   case SRM_ORMCOD_EXPERIMENTAL_NGA_MAX:
      a = MAX_A;
      f = MAX_F;
      e = MAX_e;
      break;

   case SRM_ORMCOD_EXPERIMENTAL_NGA_SPHERE:
      a = SPHR_A;
      f = SPHR_F;
      e = SPHR_e;
      break;

   default:
      std::cout << "ERROR: ORM not supported" << std::endl;
   }

   return ((computeRn(a, e, phi) * std::cos(phi)) /
      (2 * a * computeE(f, e) * computeTau(e, phi)));
}

double computeError(srm::Coord3D* tgtCoordHandle, SRM_Vector_3D& CoordVal, SRM_Long_Float a, SRM_Long_Float e)
{
   const double phi{tgtCoordHandle->getValues()[1]};
   const double Rn{computeRn(a, e, phi)};
   const double Rm{computeRn(a, e, Rn)};

   double corrected_angle{};
   if (std::fabs(tgtCoordHandle->getValues()[0] - CoordVal[0] * toRad) > PI)
      corrected_angle = TWO_PI - std::fabs(tgtCoordHandle->getValues()[0] - CoordVal[0] * toRad);
   else
      corrected_angle = tgtCoordHandle->getValues()[0] - CoordVal[0] * toRad;

   double sumSq = std::pow((CoordVal[2] + Rn) * std::cos(phi) * corrected_angle, 2.0);
   sumSq += std::pow((CoordVal[2] + Rm) * (tgtCoordHandle->getValues()[1] - CoordVal[1] * toRad), 2.0);
   sumSq += std::pow(tgtCoordHandle->getValues()[2] - CoordVal[2], 2.0);
   const double error{std::sqrt(sumSq)};

   return error;
}

double computeError(srm::Coord3D* tgtCoordHandle, doubleArray3& CoordVal, const int length, const int method)
{
   srm::Coord::Coord_ClassType coordType = tgtCoordHandle->getClassType();

   SRM_Long_Float a = tgtCoordHandle->getSRF()->getA();
   SRM_Long_Float f = tgtCoordHandle->getSRF()->getF();
   SRM_Long_Float e = std::sqrt(2 * f - f * f);

   double error{};
   switch (coordType) {
   case srm::Coord::COORD_TYP_CC:
   {
      double sumSq = std::pow((tgtCoordHandle->getValues())[0] - CoordVal.var[0], 2.0);
      sumSq += std::pow((tgtCoordHandle->getValues())[1] - CoordVal.var[1], 2.0);
      sumSq += std::pow((tgtCoordHandle->getValues())[2] - CoordVal.var[2], 2.0);
      error = std::sqrt(sumSq);
      break;
   }
   case srm::Coord::COORD_TYP_CD:
   {
      switch (method) {
      case 0: // SRM spec - Paul's formulation
      {
         const double phi = tgtCoordHandle->getValues()[1];
         const double Rn = computeRn(a, e, phi);
         const double Rm = computeRm(a, e, Rn);
         const double h = tgtCoordHandle->getValues()[2];

         double sumSq = std::pow((Rn + h) * std::cos(phi) * std::fmod(tgtCoordHandle->getValues()[0] - CoordVal.var[0] * toRad, TWO_PI), 2.0);
         sumSq += std::pow((Rm + h)*(tgtCoordHandle->getValues()[1] - CoordVal.var[1] * toRad), 2.0);
         sumSq += std::pow(tgtCoordHandle->getValues()[2] - CoordVal.var[2], 2.0);

         error = std::sqrt(sumSq);

         break;
      }
      case 1: // SRM spec - Ralph's formulation
      {
         const double phi = tgtCoordHandle->getValues()[1];
         const double h = tgtCoordHandle->getValues()[2];
         const double ha = CoordVal.var[2];
         const double Rn = computeRn(a, e, phi);
         const double Rm = computeRm(a, e, Rn);

         //				printData(coordHandle);
         //				printData(CoordVal);

         double sumSq = std::pow((Rn + h) * std::cos(phi) * std::fmod(tgtCoordHandle->getValues()[0] - CoordVal.var[0] * toRad, TWO_PI), 2);
         sumSq += std::pow((Rm + h) * (tgtCoordHandle->getValues()[1] - CoordVal.var[1] * toRad), 2);
         sumSq += std::pow(h - ha, 2);
         error = std::sqrt(sumSq);

         break;
      }
      case 2: // Farid's method 1
      {
         const double lambda1 = CoordVal.var[0] * toRad;
         const double phi1 = CoordVal.var[1] * toRad;
         const double h1 = CoordVal.var[2];
         const double lambda2 = tgtCoordHandle->getValues()[0];
         const double phi2 = tgtCoordHandle->getValues()[1];
         const double h2 = tgtCoordHandle->getValues()[2];
         const double R1n = computeRn(a, e, phi1);
         const double R2n = computeRn(a, e, phi2);

         const double D1_sq = std::pow(std::sin(phi1) * (R1n + h1) + std::sin(phi2) * (R2n + h2), 2) +
            std::pow(std::cos(phi1) * (R1n + h1) - std::cos(phi2) * (R2n + h2), 2);
         const double D2_sq = std::pow(std::sin(lambda1) * (R1n + h1) + std::sin(lambda2) * (R2n + h2), 2) +
            std::pow(std::cos(lambda1) * (R1n + h1) - std::cos(lambda2) * (R2n + h2), 2);
         error = std::sqrt(D1_sq + D2_sq);

         break;
      }
      case 3: // Farid's method 2
      {
         const double lambda1 = CoordVal.var[0] * toRad;
         const double phi1 = CoordVal.var[1] * toRad;
         const double h1 = CoordVal.var[2];
         const double lambda2 = tgtCoordHandle->getValues()[0];
         const double phi2 = tgtCoordHandle->getValues()[1];
         const double h2 = tgtCoordHandle->getValues()[2];
         const double R1n = computeRn(a, e, phi1);
         const double R2n = computeRn(a, e, phi2);
         const double E = 1.0 - e*e;
         const double Esq = E * E;
         const double sphi1 = std::sin(phi1);
         const double sphi2 = std::sin(phi2);
         const double cphi1 = std::cos(phi1);
         const double cphi2 = std::cos(phi2);

         const double S1 = std::pow(R1n + h1, 2) * cphi1 * cphi1 + std::pow(R2n + h2, 2) * cphi2 * cphi2;
         const double S2 = -2.0 * (cphi1 * (R1n + h1) * cphi2 * (R2n + h2) * std::cos(lambda1 - lambda2));
         const double S3 = -2.0 * sphi1 * sphi2 * (Esq * R1n * R2n + h1 * h2 + E * R1n * h2 + E * R2n * h1) +
            sphi1 * sphi1 * (Esq * R1n * R1n + h1 * h1 + 2.0 * E * R1n *h1) +
            sphi2 * sphi2 * (Esq * R2n * R2n + h2 * h2 + 2.0 * E * R2n *h2);

         error = std::sqrt(S1 + S2 + S3);

         break;
      }
      case 4: // Farid's method 3 - simple formulation using (x, y, z)
      {
         const double lambda1 = CoordVal.var[0] * toRad;
         const double phi1 = CoordVal.var[1] * toRad;
         const double h1 = CoordVal.var[2];
         const double lambda2 = tgtCoordHandle->getValues()[0];
         const double phi2 = tgtCoordHandle->getValues()[1];
         const double h2 = tgtCoordHandle->getValues()[2];
         const double R1n = computeRn(a, e, phi1);
         const double R2n = computeRn(a, e, phi2);

         const double x1 = (R1n + h1) * std::cos(phi1) * std::cos(lambda1);
         const double y1 = (R1n + h1) * std::cos(phi1) * std::sin(lambda1);
         const double z1 = ((1 - e * e) * R1n + h1) * std::sin(phi1);
         const double x2 = (R2n + h2) * std::cos(phi2) * std::cos(lambda2);
         const double y2 = (R2n + h2) * std::cos(phi2) * std::sin(lambda2);
         const double z2 = ((1 - e * e) * R2n + h2) * std::sin(phi2);

         error = std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2) + std::pow(z1 - z2, 2));

         break;
      }
      }
      break;
   }
   case srm::Coord::COORD_TYP_M:
   case srm::Coord::COORD_TYP_TM:
   case srm::Coord::COORD_TYP_PS:
   case srm::Coord::COORD_TYP_LCC:
   {
      double sumSq = std::pow((tgtCoordHandle->getValues())[0] - CoordVal.var[0], 2.0);
      sumSq += std::pow((tgtCoordHandle->getValues())[1] - CoordVal.var[1], 2.0);
      sumSq += std::pow((tgtCoordHandle->getValues())[2] - CoordVal.var[2], 2.0);
      error = std::sqrt(sumSq);
      break;
   }
   default:
      std::cout << "ERROR: Coordinate type not supported" << std::endl;
   }

   return error;
}

void computeStat(std::vector<diffInfo>& diffs, std::vector<bool>& exceeded, const bool isCD, statInfo& results)
{
   results.count = diffs.size();
   results.max = 0.0;
   results.min = 999999999999.99;
   results.num_exceeded = 0;
   results.isCD = isCD;

   double corrected_denom{};
   if (results.count == 0) {
      corrected_denom = 1.0;
      results.dataPoint = 0;
      results.compOut.var[0] = 0.0;
      results.compOut.var[1] = 0.0;
      results.compOut.var[2] = 0.0;
   } else {
      corrected_denom = results.count;
      results.dataPoint = diffs[0].dataPoint;
      results.compOut = diffs[0].compOut;
   }

   double sum{};
   for (int i = 0; i < diffs.size(); i++) {
      if (diffs[i].diff > MAX_DIFF) {
         results.num_exceeded += 1;
         exceeded.push_back(true);
      } else
         exceeded.push_back(false);

      if (diffs[i].diff > results.max) {
         results.max = diffs[i].diff;
         results.dataPoint = diffs[i].dataPoint;
         results.compOut = diffs[i].compOut;
      }

      if (diffs[i].diff < results.min)
         results.min = diffs[i].diff;

      sum += diffs[i].diff;
   }

   if (results.max > MAX_DIFF)
      results.exceededThreshold = true;
   else
      results.exceededThreshold = false;

   results.mean = sum / corrected_denom;

   double sumSq{};
   for (int j = 0; j < diffs.size(); j++) {
      const double mDiff = diffs[j].diff - results.mean;
      sumSq += mDiff * mDiff;
   }

   results.stdDev = std::sqrt(sumSq / corrected_denom);
}

void computeStat(std::vector<gdDatumCoord>& gdCoord, std::vector<gdDatumStat>& results)
{
   int i{};
   int j{};
   gdDatumStat tmpStat{};
   gdDatumCoord thisDatum = gdCoord[i];
   while (i < gdCoord.size()) {
      std::strcpy(tmpStat.datum_name_in, thisDatum.datum_name_in);
      std::strcpy(tmpStat.datum_name_out, thisDatum.datum_name_out);
      tmpStat.min = thisDatum.diff;
      tmpStat.max = thisDatum.diff;
      tmpStat.count = 1;
      gdDatumCoord nextDatum = gdCoord[++i];

      while (std::strcmp(thisDatum.datum_name_in, nextDatum.datum_name_in) == 0 &&
         std::strcmp(thisDatum.datum_name_out, nextDatum.datum_name_out) == 0 &&
         i < gdCoord.size())
      {
         tmpStat.count++;

         if (nextDatum.diff > tmpStat.max)
            tmpStat.max = nextDatum.diff;
         else if (nextDatum.diff < tmpStat.min)
            tmpStat.min = nextDatum.diff;

         thisDatum = nextDatum;
         nextDatum = gdCoord[++i];
      }

      results.push_back(tmpStat);
      thisDatum = nextDatum;
   }
}

int createSRF(srfParams& srf, srm::BaseSRF_3D** srfHandle, statInfo& results)
{
   try {

      switch (srfTypeMap[srf.type]) {
      case TRANSVERSE_MARCATOR:
         *srfHandle = static_cast<srm::BaseSRF_3D*>(srm::SRF_TransverseMercator::create(srf.orm,
            srf.rt,
            srf.floatParam[CENTRAL_MERIDIAN] * toRad,
            srf.floatParam[ORIGIN_LATITUDE] * toRad,
            srf.floatParam[SCALE_FACTOR],
            srf.floatParam[FALSE_EASTING],
            srf.floatParam[FALSE_NORTHING]));
         break;

      case MERCATOR:
      {
         if (srf.floatParam[SCALE_FACTOR] == 1234.4321)
            srf.floatParam[SCALE_FACTOR] =
            computeK0(srf.orm, srf.floatParam[ORIGIN_LATITUDE] * toRad);

         *srfHandle = static_cast<srm::BaseSRF_3D*>(srm::SRF_Mercator::create(srf.orm,
            srf.rt,
            srf.floatParam[CENTRAL_MERIDIAN] * toRad,
            srf.floatParam[SCALE_FACTOR],
            srf.floatParam[FALSE_EASTING],
            srf.floatParam[FALSE_NORTHING]));
         break;
      }

      case LAMBERT_COMFORMAL_CONIC:
      {
         if (srf.floatParam[STANDARD_PARALLEL_ONE] == 1234.4321 ||
            srf.floatParam[STANDARD_PARALLEL_TWO] == 1234.4321) {
            if (srf.floatParam[SCALE_FACTOR] == 1.0) {
               srf.floatParam[STANDARD_PARALLEL_ONE] = srf.floatParam[ORIGIN_LATITUDE];
               srf.floatParam[STANDARD_PARALLEL_TWO] = srf.floatParam[ORIGIN_LATITUDE];
            } else {
               std::strcpy(results.message, "Exception: Incompatible SRF Parameter Set");
               return 0;
            }
         }

         *srfHandle = static_cast<srm::BaseSRF_3D*>(srm::SRF_LambertConformalConic::create(srf.orm,
            srf.rt,
            srf.floatParam[CENTRAL_MERIDIAN] * toRad,
            srf.floatParam[ORIGIN_LATITUDE] * toRad,
            srf.floatParam[STANDARD_PARALLEL_ONE] * toRad,
            srf.floatParam[STANDARD_PARALLEL_TWO] * toRad,
            srf.floatParam[FALSE_EASTING],
            srf.floatParam[FALSE_NORTHING]));
         break;
      }

      case NEY:
         std::strcpy(results.message, "Ney SRF not supported");
         return 0;
         break;

      case POLAR_STEREOGRAPHIC:
      {
         SRM_Polar_Aspect polarAspect;

         if (srf.floatParam[LATITUDE_OF_TRUE_SCALE] >= 0.0)
            polarAspect = SRM_PLRASP_NORTH;
         else
            polarAspect = SRM_PLRASP_SOUTH;

         if (srf.floatParam[SCALE_FACTOR] == 1234.4321) {
            if (srf.floatParam[LATITUDE_OF_TRUE_SCALE] * toRad == PI_OVER_2 ||
               srf.floatParam[LATITUDE_OF_TRUE_SCALE] * toRad == -PI_OVER_2)
               srf.floatParam[SCALE_FACTOR] = 1.0;
            else
               //					srf.floatParam[SCALE_FACTOR] = 0.933033984222640;
               srf.floatParam[SCALE_FACTOR] = computePsK0(srf.orm, srf.floatParam[LATITUDE_OF_TRUE_SCALE] * toRad);
         }

         *srfHandle = static_cast<srm::BaseSRF_3D*>(srm::SRF_PolarStereographic::create(srf.orm,
            srf.rt,
            polarAspect,
            srf.floatParam[LONGITUDE_DOWN_FROM_POLE] * toRad,
            srf.floatParam[SCALE_FACTOR],
            srf.floatParam[FALSE_EASTING],
            srf.floatParam[FALSE_NORTHING]));
         break;
      }
      case GEODETIC:
         *srfHandle = static_cast<srm::BaseSRF_3D*>(srm::SRF_Celestiodetic::create(srf.orm, srf.rt));
         break;

      case SPHERICAL:  // using Inertial ORM/RT
         std::strcpy(results.message, "Spherical SRF not supported");
         return 0;
         break;

      case GEOCENTRIC:
         *srfHandle = static_cast<srm::BaseSRF_3D*>(srm::SRF_Celestiocentric::create(srf.orm, srf.rt));
         break;

      case ELLIPSOIDAL:
         std::strcpy(results.message, "Ellipsoidal SRF not supported");
         return 0;
         break;

      default:
         std::strcpy(results.message, "SRF not supported");
         return 0;
         break;
      }

   }
   catch (srm::Exception(ex)) {
      std::strcpy(results.message, "Exception: ");
      std::strcat(results.message, ex.getWhat());
      return 0;
   }

   return 1;
}

int createCoord(srm::BaseSRF_3D* srfHandle, srm::Coord3D** coordHandle)
{
   *coordHandle = static_cast<srm::Coord3D*>(srfHandle->createCoordinate3D(1.0, 1.0, 1.0));

   return 1;
}

int testConversion(std::vector<gdDatumCoord>& gdCoord)
{
   srm::BaseSRF_3D* srcSrfHandle{};
   srm::BaseSRF_3D* tgtSrfHandle{};

   srm::Coord3D* srcCoordHandle{};
   srm::Coord3D* tgtCoordHandle{};
   SRM_Coordinate_Valid_Region vRegion{};
   SRM_Vector_3D coord{};

   for (int i = 0; i < gdCoord.size(); i++) {
      try {
         srcSrfHandle = static_cast<srm::BaseSRF_3D*>(srm::SRF_Celestiodetic::create
            (ormMap[gdCoord[i].datum_name_in],
            rtMap[gdCoord[i].datum_name_in]));
      } catch (srm::Exception(ex)) {
         std::cout << "Error SRF creation: ORM/RT not supported=> " << gdCoord[i].datum_name_in << std::endl;
      }

      try {
         tgtSrfHandle = static_cast<srm::BaseSRF_3D*>(srm::SRF_Celestiodetic::create
            (ormMap[gdCoord[i].datum_name_out],
            rtMap[gdCoord[i].datum_name_out]));
      } catch (srm::Exception(ex)) {
         std::cout << "Error SRF creation: ORM/RT not supported=> " << gdCoord[i].datum_name_out << std::endl;
      }

      createCoord(srcSrfHandle, &srcCoordHandle);
      createCoord(tgtSrfHandle, &tgtCoordHandle);

      coord[0] = gdCoord[i].gd_coord_in[0] * toRad;
      coord[1] = gdCoord[i].gd_coord_in[1] * toRad;
      coord[2] = gdCoord[i].gd_coord_in[2];

      srcCoordHandle->setValues(coord);

      try {
         vRegion = tgtSrfHandle->changeCoordinate3DSRF(*srcCoordHandle, *tgtCoordHandle);

         if (vRegion != SRM_COORDVALRGN_VALID)
            std::cout << "Invalid region" << std::endl;

         gdCoord[i].comp_coord_out[0] = tgtCoordHandle->getValues()[0];
         gdCoord[i].comp_coord_out[1] = tgtCoordHandle->getValues()[1];
         gdCoord[i].comp_coord_out[2] = tgtCoordHandle->getValues()[2];

         gdCoord[i].diff = computeError
            (tgtCoordHandle,
            gdCoord[i].gd_coord_out,
            tgtCoordHandle->getSRF()->getA(),
            tgtCoordHandle->getSRF()->getF());

      } catch (srm::Exception(ex)) {
         gdCoord[i].comp_coord_out[0] = 1234.4321;
         gdCoord[i].comp_coord_out[1] = 1234.4321;
         gdCoord[i].comp_coord_out[2] = 1234.4321;
         gdCoord[i].diff = 0.0;
      }

      // free the memory
      srcSrfHandle->freeCoordinate(srcCoordHandle);
      tgtSrfHandle->freeCoordinate(tgtCoordHandle);
      srcSrfHandle->release();
      tgtSrfHandle->release();
   }

   return 1;
}

int testConversion(srfParams& srcSrf,
   srfParams& tgtSrf,
   std::vector<doubleArray3>& srcCoordVal,
   std::vector<doubleArray3>& tgtCoordVal,
   std::vector<doubleArray3>& compCoordVal,
   statInfo& results,
   std::vector<bool>& exceeded,
   char* srfName)
{
   srm::BaseSRF_3D* srcSrfHandle{};
   srm::BaseSRF_3D* tgtSrfHandle{};
   srm::Coord3D* srcCoordHandle{};
   srm::Coord3D* tgtCoordHandle{};
   srm::Coord3D* goldCoordHandle{};
   bool isCD{};
   std::vector<diffInfo> diffs{};
   SRM_Vector_3D coordVal{};
   double toRadConv{1.0};
   SRM_Coordinate_Valid_Region vRegion{};
   doubleArray3 compOut{};
   SRM_ORM_Transformation_3D_Parameters ident_hst = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
   double radFactor{1.0};

   results.message[0] = '\0';

   if (!createSRF(srcSrf, &srcSrfHandle, results))
      return 0;

   if (!createSRF(tgtSrf, &tgtSrfHandle, results)) {
      srcSrfHandle->release();
      return 0;
   }

   createCoord(srcSrfHandle, &srcCoordHandle);
   createCoord(tgtSrfHandle, &tgtCoordHandle);
   createCoord(tgtSrfHandle, &goldCoordHandle);

   if (srfTypeMap[srcSrf.type] == GEODETIC || srfTypeMap[srcSrf.type] == SPHERICAL)
      toRadConv = toRad;

   if (srfTypeMap[tgtSrf.type] == GEODETIC)
      radFactor = toRad;

   if (srfTypeMap[tgtSrf.type] == GEODETIC || srfTypeMap[srcSrf.type] == SPHERICAL)
      isCD = true;

   for (int i = 0; i<srcCoordVal.size(); i++) {
      coordVal[0] = srcCoordVal[i].var[0] * toRadConv; // correct if lon
      coordVal[1] = srcCoordVal[i].var[1] * toRadConv; // correct if lat
      coordVal[2] = srcCoordVal[i].var[2];

      srcCoordHandle->setValues(coordVal);

      try {
         if (srcCoordHandle->getClassType() == srm::Coord::COORD_TYP_EI ||
            tgtCoordHandle->getClassType() == srm::Coord::COORD_TYP_EI) {
            vRegion = tgtSrfHandle->changeCoordinate3DSRFObject
               (*srcCoordHandle, ident_hst, *tgtCoordHandle);
         } else {
            // Eliminate TM lambda > 3.5 deg from the central meridian
            if ((srfTypeMap[srcSrf.type] == TRANSVERSE_MARCATOR &&
               std::fabs(tgtCoordVal[i].var[0] - srcSrf.floatParam[0]) > 3.5) ||
               (srfTypeMap[tgtSrf.type] == TRANSVERSE_MARCATOR &&
               std::fabs(srcCoordVal[i].var[0] - tgtSrf.floatParam[0]) > 3.5)) {
               //Indication of coordinate outside the +-3.5 deg from the central meridian.
               vRegion = SRM_COORDVALRGN_DEFINED;
            } else
               vRegion = tgtSrfHandle->changeCoordinate3DSRF(*srcCoordHandle, *tgtCoordHandle);
         }

         diffInfo diffData{};

         if (vRegion == SRM_COORDVALRGN_VALID ||
            vRegion == SRM_COORDVALRGN_EXTENDED_VALID) {
            compOut.var[0] = tgtCoordHandle->getValues()[0];
            compOut.var[1] = tgtCoordHandle->getValues()[1];
            compOut.var[2] = tgtCoordHandle->getValues()[2];
            compCoordVal.push_back(compOut);

            diffData.compOut.var[0] = tgtCoordHandle->getValues()[0];
            diffData.compOut.var[1] = tgtCoordHandle->getValues()[1];
            diffData.compOut.var[2] = tgtCoordHandle->getValues()[2];
            diffData.dataPoint = i;

            diffData.diff = computeError(tgtCoordHandle, tgtCoordVal[i], 3, 0);

            diffs.push_back(diffData);
         } else { // DEFINED valid region
            compOut.var[0] = 1.2345;
            compOut.var[1] = 1.2345;
            compOut.var[2] = 1.2345;
            compCoordVal.push_back(compOut);
         }

      } catch (srm::Exception(ex)) {
         compOut.var[0] = 1.2345;
         compOut.var[1] = 1.2345;
         compOut.var[2] = 1.2345;
         compCoordVal.push_back(compOut);
         // coordinate outside the SRM valid ragion for the SRF
         // cout << ".";
      }
   }

   //	  printData( diffs );

   computeStat(diffs, exceeded, isCD, results);

   srfs << srfName << std::endl;
   srfs << srcSrfHandle->toString() << std::endl;
   srfs << "#######################################################" << std::endl;

   // free the memory
   srcSrfHandle->freeCoordinate(srcCoordHandle);
   tgtSrfHandle->freeCoordinate(tgtCoordHandle);
   srcSrfHandle->release();
   tgtSrfHandle->release();

   return 1;
}

void print_error(const char* name)
{
   std::fprintf(stderr, "\n%s version 0.1\n", name);
   std::fprintf(stderr, "  Usage: %s <test config file>\n", name);
}

static void process_arguments(int argc, char* argv[], char* config_file_name, bool& more)
{
   if (argc < 2) {
      print_error(argv[0]);
      std::exit(0);
   }

   std::memcpy(config_file_name, argv[1], std::strlen(argv[1]) + 1);
   //	memcpy( output_file_name, argv[2], strlen(argv[2])+1 );

   if (argc == 3) {
      if (*(argv[2]) == 't')
         more = true;
      else
         more = false;
   }
}

int main(int argc, char* argv[])
{
   char config_file_name[500]{};
   char full_file_name_1[500]{};
   char full_file_name_2[500]{};
   bool more{};

   std::ofstream convResStr{};
   std::ofstream datumResStr{};

   std::vector<configInfo> config;

   std::cout.precision(15);

   //  freopen( "srm_out_052808.txt", "w", stdout );

   initializeMaps();
   process_arguments(argc, argv, config_file_name, more);

   convResStr.open("srm_conv_accuracy_results.csv", std::ios::out);
   if (!convResStr) {
      std::cout << "Cannot create output file srm_conv_accuracy_results.csv" << std::endl;
      std::exit(0);
   }
   datumResStr.open("srm_datum_accuracy_results.csv", std::ios::out);
   if (!datumResStr) {
      std::cout << "Cannot create output file srm_datum_accuracy_results.csv" << std::endl;
      std::exit(0);
   }

   convResStr.precision(15);
   datumResStr.precision(15);

   printConvHeader(convResStr, more);
   printDatumHeader(datumResStr, more);

   if (!load_file(config_file_name, config))
      std::exit(0);

   // printData( config );

   std::cout << "Running SRM accuracy test... \n" << std::endl;

   for (int test_case = 0; test_case < config.size(); test_case++) {
      std::strcpy(full_file_name_1, config[test_case].path);
      std::strcpy(full_file_name_2, config[test_case].path);
      std::strcat(full_file_name_1, config[test_case].file_name_1);
      std::strcat(full_file_name_2, config[test_case].file_name_2);

      if (std::strstr(full_file_name_1, "NGA_3parDT")) {
            std::vector<gdDatumCoord> gdCoord{};
            std::vector<gdDatumStat> datumStat{};

            if (!load_file(full_file_name_1, full_file_name_2, gdCoord))
               exit(0);

            testConversion(gdCoord);
            computeStat(gdCoord, datumStat);
            printData(datumResStr, datumStat, more);
      } else { // this is not the datun shift case
         std::vector<doubleArray3> srcDoubleParam{};
         std::vector<doubleArray3> tgtDoubleParam{};
         srfParams srcSrf{};
         srfParams tgtSrf{};

         // fill in the magic numbers to detect a SRF parameter was set
         for (int i = 0; i < DATUM; i++) {
            srcSrf.floatParam[i] = 1234.4321;
            tgtSrf.floatParam[i] = 1234.4321;
         }

         if (!load_file(full_file_name_1, srcSrf, srcDoubleParam))
            std::exit(0);

         if (!load_file(full_file_name_2, tgtSrf, tgtDoubleParam))
            std::exit(0);

         {
            statInfo results{};
            std::vector<bool> exceeded{};
            std::vector<doubleArray3> compDoubleParamSt{};

            testConversion(srcSrf, tgtSrf, srcDoubleParam, tgtDoubleParam, compDoubleParamSt,
              results, exceeded, config[test_case].file_name_1);
            printData(convResStr, srcDoubleParam, tgtDoubleParam, compDoubleParamSt, srcSrf.datum_name,
              exceeded, config[test_case].file_name_1, config[test_case].file_name_2,
              results, more);
         }
 
         {
            statInfo results{};
            std::vector<bool> exceeded{};
            std::vector<doubleArray3> compDoubleParamTs{};

            testConversion(tgtSrf, srcSrf, tgtDoubleParam, srcDoubleParam, compDoubleParamTs,
              results, exceeded, config[test_case].file_name_2);
            printData(convResStr, tgtDoubleParam, srcDoubleParam, compDoubleParamTs, tgtSrf.datum_name,
              exceeded, config[test_case].file_name_2, config[test_case].file_name_1,
              results, more);
         }
      }
   }

   convResStr.close();
   datumResStr.close();

   std::cout << "Completed accuracy test!" << std::endl;

   return 0;
}
