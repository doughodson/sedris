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
#include <fstream>
#include <ctime>
#include <cstring>
#include <vector>
#include <map>
#include <cmath>
#include <cstdio>

#define MAX_DIFF 0.001

#define toRad std::atan(1.0)/45.0
#define toDeg 45.0/std::atan(1.0)

#define PI_OVER_4 std::atan(1.0)
#define PI_OVER_2 std::atan(1.0)*2.0
#define PI        std::atan(1.0)*4.0
#define TWO_PI    std::atan(1.0)*8.0

#define WGS84_A    6.3781370000000e6
#define WGS84_F    1.0/2.9825722356300e2
#define WGS84_e    std::sqrt(2*WGS84_F - WGS84_F*WGS84_F)
#define MAX_A      6400000.0
#define MAX_F      1.0/150.0
#define MAX_e      std::sqrt(2*MAX_F - MAX_F*MAX_F)
#define SPHR_A     20000000.0/PI
#define SPHR_F     0.0
#define SPHR_e     0.0

#define NEY_P1     70.*toRad
#define NEY_P2     (89.0+(59.0/60.0)+(58.0/3600.0))*toRad 

#define CENTRAL_MERIDIAN 0
#define ORIGIN_LATITUDE 1
#define SCALE_FACTOR 2
#define STANDARD_PARALLEL_ONE 3
#define STANDARD_PARALLEL_TWO 4
#define LONGITUDE_DOWN_FROM_POLE 5
#define LATITUDE_OF_TRUE_SCALE 6
#define FALSE_EASTING 7
#define FALSE_NORTHING 8
#define NO_HEIGHT 9
#define ELLIPSOID_HEIGHT 10
#define DATUM 11
#define COORDINATES 12
#define PROJECTION 13

const char* datum[] = { "WGE",
"Test_SRMmax",
"Test_sphere" };

const char* srfParamName[] = { "CENTRAL MERIDIAN",
"ORIGIN LATITUDE",
"SCALE FACTOR",
"STANDARD PARALLEL ONE",
"STANDARD PARALLEL TWO",
"LONGITUDE DOWN FROM POLE",
"LATITUDE OF TRUE SCALE",
"FALSE EASTING",
"FALSE NORTHING",
"NO HEIGHT",
"ELLIPSOID HEIGHT",
"DATUM",
"COORDINATES",
"PROJECTION" };

typedef struct
{
   SRM_Vector_3D var;
} doubleArray3;

typedef struct
{
   char path[100];
   char file_name_1[50];
   char file_name_2[50];
} configInfo;

typedef struct
{
   char           type[50];
   char           datum_name[20];
   SRM_ORM_Code   orm;
   SRM_RT_Code    rt;
   double         floatParam[DATUM];
} srfParams;

typedef struct
{
   char           datum_name_in[20];
   char           datum_name_out[20];
   double         gd_coord_in[3];
   double         gd_coord_out[3];
   double         comp_coord_out[3];
   double         diff;
} gdDatumCoord;

typedef struct
{
   char           datum_name_in[20];
   char           datum_name_out[20];
   int            count;
   double         min;
   double         max;
} gdDatumStat;

typedef struct
{
   double diff;
   int    dataPoint;
   doubleArray3 compOut;
} diffInfo;

typedef struct
{
   int count;
   double min;
   double max;
   double mean;
   double stdDev;
   bool exceededThreshold;
   int num_exceeded;
   char message[500];
   // other data
   doubleArray3 compOut;
   int dataPoint;
   bool isCD;
} statInfo;

struct strCmp {
   bool operator()(const char* s1, const char* s2) const {
      return std::strcmp(s1, s2) < 0;
   }
};

std::map<const char*, int, strCmp> srfParamMap{};
std::map<const char*, int, strCmp> srfTypeMap{};
std::map<const char*, int, strCmp> ormMap{};
std::map<const char*, int, strCmp> rtMap{};

#define TRANSVERSE_MARCATOR 0
#define MERCATOR 1
#define POLAR_STEREOGRAPHIC 2
#define NEY 3
#define GEODETIC 4
#define LAMBERT_COMFORMAL_CONIC 5
#define GEOCENTRIC 6
#define SPHERICAL 7
#define ELLIPSOIDAL 8

const char* srfName[] = { "Transverse Mercator",
"Mercator",
"Polar Stereographic",
"Ney's (Modified Lambert Conformal Conic)",
"Geodetic",
"Lambert Conformal Conic (1 parallel)",
"Geocentric",
"Spherical",
"Ellipsoidal" };

std::ofstream srfs{};

void initializeMaps()
{
   srfParamMap["CENTRAL MERIDIAN"] = CENTRAL_MERIDIAN;
   srfParamMap["ORIGIN LATITUDE"] = ORIGIN_LATITUDE;
   srfParamMap["SCALE FACTOR"] = SCALE_FACTOR;
   srfParamMap["STANDARD PARALLEL ONE"] = STANDARD_PARALLEL_ONE;
   srfParamMap["STANDARD PARALLEL TWO"] = STANDARD_PARALLEL_TWO;
   srfParamMap["LONGITUDE DOWN FROM POLE"] = LONGITUDE_DOWN_FROM_POLE;
   srfParamMap["LATITUDE OF TRUE SCALE"] = LATITUDE_OF_TRUE_SCALE;
   srfParamMap["FALSE EASTING"] = FALSE_EASTING;
   srfParamMap["FALSE NORTHING"] = FALSE_NORTHING;
   srfParamMap["NO HEIGHT"] = NO_HEIGHT;
   srfParamMap["ELLIPSOID HEIGHT"] = ELLIPSOID_HEIGHT;
   srfParamMap["DATUM"] = DATUM;
   srfParamMap["COORDINATES"] = COORDINATES;
   srfParamMap["PROJECTION"] = PROJECTION;

   srfTypeMap["Transverse"] = TRANSVERSE_MARCATOR;
   srfTypeMap["Mercator"] = MERCATOR;
   srfTypeMap["Polar"] = POLAR_STEREOGRAPHIC;
   srfTypeMap["Ney"] = NEY;
   srfTypeMap["Geodetic"] = GEODETIC;
   srfTypeMap["Lambert"] = LAMBERT_COMFORMAL_CONIC;
   srfTypeMap["Geocentric"] = GEOCENTRIC;
   srfTypeMap["Spherical"] = SPHERICAL;
   srfTypeMap["Ellipsoidal"] = ELLIPSOIDAL;

   ormMap["ADI-M"] = SRM_ORMCOD_ADINDAN_1991;
   ormMap["ADI-A"] = SRM_ORMCOD_ADINDAN_1991;
   ormMap["ADI-B"] = SRM_ORMCOD_ADINDAN_1991;
   ormMap["ADI-C"] = SRM_ORMCOD_ADINDAN_1991;
   ormMap["ADI-D"] = SRM_ORMCOD_ADINDAN_1991;
   ormMap["ADI-E"] = SRM_ORMCOD_ADINDAN_1991;
   ormMap["ADI-F"] = SRM_ORMCOD_ADINDAN_1991;
   ormMap["AFG"] = SRM_ORMCOD_AFGOOYE_1987;
   ormMap["AIA"] = SRM_ORMCOD_ANTIGUA_1943;
   ormMap["AIN-A"] = SRM_ORMCOD_AIN_EL_ABD_1970;
   ormMap["AIN-B"] = SRM_ORMCOD_AIN_EL_ABD_1970;
   ormMap["AMA"] = SRM_ORMCOD_AMERICAN_SAMOA_1962;
   ormMap["ANO"] = SRM_ORMCOD_ANNA_1_1965;
   ormMap["ARF-M"] = SRM_ORMCOD_ARC_1950;
   ormMap["ARF-A"] = SRM_ORMCOD_ARC_1950;
   ormMap["ARF-B"] = SRM_ORMCOD_ARC_1950;
   ormMap["ARF-C"] = SRM_ORMCOD_ARC_1950;
   ormMap["ARF-D"] = SRM_ORMCOD_ARC_1950;
   ormMap["ARF-E"] = SRM_ORMCOD_ARC_1950;
   ormMap["ARF-F"] = SRM_ORMCOD_ARC_1950;
   ormMap["ARF-G"] = SRM_ORMCOD_ARC_1950;
   ormMap["ARF-H"] = SRM_ORMCOD_ARC_1950;
   ormMap["ARS-M"] = SRM_ORMCOD_ARC_1960;
   ormMap["ARS-A"] = SRM_ORMCOD_ARC_1960;
   ormMap["ARS-B"] = SRM_ORMCOD_ARC_1960;
   ormMap["ASC"] = SRM_ORMCOD_ASCENSION_1958;
   ormMap["ASM"] = SRM_ORMCOD_MONTSERRAT_1958;
   ormMap["ASQ"] = SRM_ORMCOD_MARCUS_STATION_1952;
   ormMap["ATF"] = SRM_ORMCOD_BEACON_E_1945;
   ormMap["AUA"] = SRM_ORMCOD_AUSTRALIAN_GEOD_1966;
   ormMap["AUG"] = SRM_ORMCOD_AUSTRALIAN_GEOD_1984;
   ormMap["BAT"] = SRM_ORMCOD_DJAKARTA_1987;
   ormMap["BID"] = SRM_ORMCOD_BISSAU_1991;
   ormMap["BER"] = SRM_ORMCOD_BERMUDA_1957;
   ormMap["BOO"] = SRM_ORMCOD_BOGOTA_OBS_1987;
   ormMap["BUR"] = SRM_ORMCOD_BUKIT_RIMPAH_1987;
   ormMap["CAC"] = SRM_ORMCOD_CAPE_CANAVERAL_1991;
   ormMap["CAI"] = SRM_ORMCOD_CAMPO_INCHAUSPE_1969;
   ormMap["CAO"] = SRM_ORMCOD_CANTON_1966;
   ormMap["CAP"] = SRM_ORMCOD_CAPE_1987;
   ormMap["CAZ"] = SRM_ORMCOD_CAMP_AREA_1987;
   ormMap["CCD"] = SRM_ORMCOD_S_JTSK_1993;
   ormMap["CGE"] = SRM_ORMCOD_CARTHAGE_1987;
   ormMap["CHI"] = SRM_ORMCOD_CHATHAM_1971;
   ormMap["CHU"] = SRM_ORMCOD_CHUA_1987;
   ormMap["COA"] = SRM_ORMCOD_CORREGO_ALEGRE_1987;
   ormMap["DAL"] = SRM_ORMCOD_DABOLA_1991;
   ormMap["DID"] = SRM_ORMCOD_DECEPTION_1993;
   ormMap["DOB"] = SRM_ORMCOD_GUX_1_1987;
   ormMap["EAS"] = SRM_ORMCOD_EASTER_1967;
   ormMap["ENW"] = SRM_ORMCOD_WAKE_ENIWETOK_1960;
   ormMap["EST"] = SRM_ORMCOD_ESTONIA_1937;
   ormMap["EUR-M"] = SRM_ORMCOD_EUROPE_1950;
   ormMap["EUR-A"] = SRM_ORMCOD_EUROPE_1950;
   ormMap["EUR-B"] = SRM_ORMCOD_EUROPE_1950;
   ormMap["EUR-C"] = SRM_ORMCOD_EUROPE_1950;
   ormMap["EUR-D"] = SRM_ORMCOD_EUROPE_1950;
   ormMap["EUR-E"] = SRM_ORMCOD_EUROPE_1950;
   ormMap["EUR-F"] = SRM_ORMCOD_EUROPE_1950;
   ormMap["EUR-G"] = SRM_ORMCOD_EUROPE_1950;
   ormMap["EUR-H"] = SRM_ORMCOD_EUROPE_1950;
   ormMap["EUR-I"] = SRM_ORMCOD_EUROPE_1950;
   ormMap["EUR-J"] = SRM_ORMCOD_EUROPE_1950;
   ormMap["EUR-K"] = SRM_ORMCOD_EUROPE_1950;
   ormMap["EUR-L"] = SRM_ORMCOD_EUROPE_1950;
   ormMap["EUR-S"] = SRM_ORMCOD_EUROPE_1950;
   ormMap["EUR-T"] = SRM_ORMCOD_EUROPE_1950;
   ormMap["EUS"] = SRM_ORMCOD_EUROPE_1979;
   ormMap["FAH"] = SRM_ORMCOD_FAHUD_1987;
   ormMap["FLO"] = SRM_ORMCOD_OBSERV_METEORO_1939;
   ormMap["FOT"] = SRM_ORMCOD_FORT_THOMAS_1955;
   ormMap["GAA"] = SRM_ORMCOD_GAN_1970;
   ormMap["GEO"] = SRM_ORMCOD_GEODETIC_DATUM_1949;
   ormMap["GIZ"] = SRM_ORMCOD_DOS_1968;
   ormMap["GRA"] = SRM_ORMCOD_GRACIOSA_BASE_SW_1948;
   ormMap["GUA"] = SRM_ORMCOD_GUAM_1963;
   ormMap["GSE"] = SRM_ORMCOD_GUNONG_SEGARA_1987;
   ormMap["HEN"] = SRM_ORMCOD_HERAT_NORTH_1987;
   ormMap["HER"] = SRM_ORMCOD_HERMANNSKOGEL_1871;
   ormMap["HIT"] = SRM_ORMCOD_PROV_S_CHILEAN_1963;
   ormMap["HJO"] = SRM_ORMCOD_HJORSEY_1955;
   ormMap["HKD"] = SRM_ORMCOD_HONG_KONG_1963;
   ormMap["HTN"] = SRM_ORMCOD_HU_TZU_SHAN_1991;
   ormMap["IBE"] = SRM_ORMCOD_BELLEVUE_IGN_1987;
   ormMap["IDN"] = SRM_ORMCOD_INDONESIAN_1974;
   ormMap["IND-B"] = SRM_ORMCOD_INDIAN_1916;
   ormMap["IND-I"] = SRM_ORMCOD_INDIAN_1956;
   ormMap["IND-P"] = SRM_ORMCOD_INDIAN_1962;
   ormMap["INF-A"] = SRM_ORMCOD_INDIAN_1954;
   ormMap["ING-A"] = SRM_ORMCOD_INDIAN_1960;
   ormMap["ING-B"] = SRM_ORMCOD_INDIAN_1960;
   ormMap["INH-A"] = SRM_ORMCOD_INDIAN_1975;
   ormMap["INH-A1"] = SRM_ORMCOD_INDIAN_1975;
   ormMap["IRL"] = SRM_ORMCOD_IRELAND_1965;
   ormMap["ISG"] = SRM_ORMCOD_ISTS_061_1968;
   ormMap["IST"] = SRM_ORMCOD_ISTS_073_1969;
   ormMap["JOH"] = SRM_ORMCOD_JOHNSTON_1961;
   ormMap["KAN"] = SRM_ORMCOD_KANDAWALA_1987;
   ormMap["KEG"] = SRM_ORMCOD_KERGUELEN_1949;
   ormMap["KEA"] = SRM_ORMCOD_KERTAU_1948;
   ormMap["KUS"] = SRM_ORMCOD_KUSAIE_1951;
   ormMap["LCF"] = SRM_ORMCOD_LC5_1961;
   ormMap["LEH"] = SRM_ORMCOD_LEIGON_1991;
   ormMap["LIB"] = SRM_ORMCOD_LIBERIA_1964;
   ormMap["LUZ-A"] = SRM_ORMCOD_LUZON_1987;
   ormMap["LUZ-B"] = SRM_ORMCOD_LUZON_1987;
   ormMap["MAS"] = SRM_ORMCOD_MASSAWA_1987;
   ormMap["MER"] = SRM_ORMCOD_MERCHICH_1987;
   ormMap["MID"] = SRM_ORMCOD_MIDWAY_1961;
   ormMap["MIK"] = SRM_ORMCOD_MAHE_1971;
   ormMap["MIN-A"] = SRM_ORMCOD_MINNA_1991;
   ormMap["MIN-B"] = SRM_ORMCOD_MINNA_1991;
   ormMap["MOD"] = SRM_ORMCOD_ROME_1940;
   ormMap["MPO"] = SRM_ORMCOD_M_PORALOKO_1991;
   ormMap["MVS"] = SRM_ORMCOD_VITI_LEVU_1916;
   ormMap["NAH-A"] = SRM_ORMCOD_NAHRWAN_1987;
   ormMap["NAH-B"] = SRM_ORMCOD_NAHRWAN_1987;
   ormMap["NAH-C"] = SRM_ORMCOD_NAHRWAN_1987;
   ormMap["NAP"] = SRM_ORMCOD_NAPARIMA_1991;
   ormMap["NAR-A"] = SRM_ORMCOD_N_AM_1983;
   ormMap["NAR-B"] = SRM_ORMCOD_N_AM_1983;
   ormMap["NAR-C"] = SRM_ORMCOD_N_AM_1983;
   ormMap["NAR-D"] = SRM_ORMCOD_N_AM_1983;
   ormMap["NAR-E"] = SRM_ORMCOD_N_AM_1983;
   ormMap["NAR-H"] = SRM_ORMCOD_N_AM_1983;
   ormMap["NAS-A"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-B"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-C"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-D"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-E"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-F"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-G"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-H"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-I"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-J"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-L"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-N"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-O"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-P"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-Q"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-R"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-T"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-U"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-V"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NAS-W"] = SRM_ORMCOD_N_AM_1927;
   ormMap["NSD"] = SRM_ORMCOD_N_SAHARA_1959;
   ormMap["OEG"] = SRM_ORMCOD_OLD_EGYPTIAN_1907;
   ormMap["OGB-M"] = SRM_ORMCOD_OSGB_1936;
   ormMap["OGB-A"] = SRM_ORMCOD_OSGB_1936;
   ormMap["OGB-B"] = SRM_ORMCOD_OSGB_1936;
   ormMap["OGB-C"] = SRM_ORMCOD_OSGB_1936;
   ormMap["OGB-D"] = SRM_ORMCOD_OSGB_1936;
   ormMap["OHA-M"] = SRM_ORMCOD_OLD_HAWAIIAN_CLARKE_1987;
   ormMap["OHA-A"] = SRM_ORMCOD_OLD_HAWAIIAN_CLARKE_1987;
   ormMap["OHA-B"] = SRM_ORMCOD_OLD_HAWAIIAN_CLARKE_1987;
   ormMap["OHA-C"] = SRM_ORMCOD_OLD_HAWAIIAN_CLARKE_1987;
   ormMap["OHA-D"] = SRM_ORMCOD_OLD_HAWAIIAN_CLARKE_1987;
   ormMap["OHI-M"] = SRM_ORMCOD_OLD_HAWAIIAN_INT_1987;
   ormMap["OHI-A"] = SRM_ORMCOD_OLD_HAWAIIAN_INT_1987;
   ormMap["OHI-B"] = SRM_ORMCOD_OLD_HAWAIIAN_INT_1987;
   ormMap["OHI-C"] = SRM_ORMCOD_OLD_HAWAIIAN_INT_1987;
   ormMap["OHI-D"] = SRM_ORMCOD_OLD_HAWAIIAN_INT_1987;
   ormMap["PHA"] = SRM_ORMCOD_AYABELLE_LIGHTHOUSE_1991;
   ormMap["PIT"] = SRM_ORMCOD_PITCAIRN_1967;
   ormMap["PLN"] = SRM_ORMCOD_PICO_DE_LAS_NIEVES_1987;
   ormMap["POS"] = SRM_ORMCOD_PORTO_SANTO_1936;
   ormMap["PRP-A"] = SRM_ORMCOD_PROV_S_AM_1956;
   ormMap["PRP-B"] = SRM_ORMCOD_PROV_S_AM_1956;
   ormMap["PRP-C"] = SRM_ORMCOD_PROV_S_AM_1956;
   ormMap["PRP-D"] = SRM_ORMCOD_PROV_S_AM_1956;
   ormMap["PRP-E"] = SRM_ORMCOD_PROV_S_AM_1956;
   ormMap["PRP-F"] = SRM_ORMCOD_PROV_S_AM_1956;
   ormMap["PRP-G"] = SRM_ORMCOD_PROV_S_AM_1956;
   ormMap["PRP-H"] = SRM_ORMCOD_PROV_S_AM_1956;
   ormMap["PRP-M"] = SRM_ORMCOD_PROV_S_AM_1956;
   ormMap["PTB"] = SRM_ORMCOD_POINT_58_1991;
   ormMap["PTN"] = SRM_ORMCOD_POINTE_NOIRE_1948;
   ormMap["PUK"] = SRM_ORMCOD_PULKOVO_1942;
   ormMap["PUR"] = SRM_ORMCOD_PUERTO_RICO_1987;
   ormMap["QAT"] = SRM_ORMCOD_QATAR_NATIONAL_1974;
   ormMap["QUO"] = SRM_ORMCOD_QORNOQ_1987;
   ormMap["REU"] = SRM_ORMCOD_REUNION_1947;
   ormMap["SAE"] = SRM_ORMCOD_SANTO_DOS_1965;
   ormMap["SAO"] = SRM_ORMCOD_SAO_BRAZ_1987;
   ormMap["SAP"] = SRM_ORMCOD_SAPPER_HILL_1943;
   ormMap["SAN-M"] = SRM_ORMCOD_S_AM_1969;
   ormMap["SAN-A"] = SRM_ORMCOD_S_AM_1969;
   ormMap["SAN-B"] = SRM_ORMCOD_S_AM_1969;
   ormMap["SAN-C"] = SRM_ORMCOD_S_AM_1969;
   ormMap["SAN-D"] = SRM_ORMCOD_S_AM_1969;
   ormMap["SAN-E"] = SRM_ORMCOD_S_AM_1969;
   ormMap["SAN-F"] = SRM_ORMCOD_S_AM_1969;
   ormMap["SAN-G"] = SRM_ORMCOD_S_AM_1969;
   ormMap["SAN-H"] = SRM_ORMCOD_S_AM_1969;
   ormMap["SAN-I"] = SRM_ORMCOD_S_AM_1969;
   ormMap["SAN-J"] = SRM_ORMCOD_S_AM_1969;
   ormMap["SAN-K"] = SRM_ORMCOD_S_AM_1969;
   ormMap["SAN-L"] = SRM_ORMCOD_S_AM_1969;
   ormMap["SCK"] = SRM_ORMCOD_SCHWARZECK_1991;
   ormMap["SGM"] = SRM_ORMCOD_SELVAGEM_GRANDE_1938;
   ormMap["SHB"] = SRM_ORMCOD_DOS_71_4_1987;
   ormMap["SOA"] = SRM_ORMCOD_S_ASIA_1987;
   ormMap["SPK-A"] = SRM_ORMCOD_S42_PULKOVO;
   ormMap["SPK-B"] = SRM_ORMCOD_S42_PULKOVO;
   ormMap["SPK-C"] = SRM_ORMCOD_S42_PULKOVO;
   ormMap["SPK-D"] = SRM_ORMCOD_S42_PULKOVO;
   ormMap["SPK-E"] = SRM_ORMCOD_S42_PULKOVO;
   ormMap["SPK-F"] = SRM_ORMCOD_S42_PULKOVO;
   ormMap["SPK-G"] = SRM_ORMCOD_S42_PULKOVO;
   ormMap["SRL"] = SRM_ORMCOD_SIERRA_LEONE_1960;
   ormMap["TAN"] = SRM_ORMCOD_TANANARIVE_OBS_1925;
   ormMap["TDC"] = SRM_ORMCOD_TRISTAN_1968;
   ormMap["TIL"] = SRM_ORMCOD_TIMBALAI_EVEREST_1948;
   ormMap["TOY-A"] = SRM_ORMCOD_TOKYO_1991;
   ormMap["TOY-B"] = SRM_ORMCOD_TOKYO_1991;
   ormMap["TOY-B1"] = SRM_ORMCOD_TOKYO_1991;
   ormMap["TOY-C"] = SRM_ORMCOD_TOKYO_1991;
   ormMap["TOY-M"] = SRM_ORMCOD_TOKYO_1991;
   ormMap["TRN"] = SRM_ORMCOD_TERN_1961;
   ormMap["VOI"] = SRM_ORMCOD_VOIROL_1874;
   ormMap["VOR"] = SRM_ORMCOD_VOIROL_1960;
   ormMap["WAK"] = SRM_ORMCOD_WAKE_1952;
   ormMap["WGE"] = SRM_ORMCOD_WGS_1984;
   ormMap["YAC"] = SRM_ORMCOD_YACARE_1987;
   ormMap["ZAN"] = SRM_ORMCOD_ZANDERIJ_1987;
   ormMap["KGS"] = SRM_ORMCOD_KOREAN_GEODETIC_1995;
   ormMap["SIR"] = SRM_ORMCOD_SIRGAS_2000;
   ormMap["Test_SRMmax"] = SRM_ORMCOD_EXPERIMENTAL_NGA_MAX;
   ormMap["Test_sphere"] = SRM_ORMCOD_EXPERIMENTAL_NGA_SPHERE;

   rtMap["ADI-M"] = SRM_RTCOD_ADINDAN_1991_MEAN_SOLUTION;
   rtMap["ADI-A"] = SRM_RTCOD_ADINDAN_1991_ETHIOPIA;
   rtMap["ADI-B"] = SRM_RTCOD_ADINDAN_1991_SUDAN;
   rtMap["ADI-C"] = SRM_RTCOD_ADINDAN_1991_MALI;
   rtMap["ADI-D"] = SRM_RTCOD_ADINDAN_1991_SENEGAL;
   rtMap["ADI-E"] = SRM_RTCOD_ADINDAN_1991_BURKINA_FASO;
   rtMap["ADI-F"] = SRM_RTCOD_ADINDAN_1991_CAMEROON;
   rtMap["AFG"] = SRM_RTCOD_AFGOOYE_1987_SOMALIA;
   rtMap["AIA"] = SRM_RTCOD_ANTIGUA_1943_ANTIGUA_LEEWARD_ISLANDS;
   rtMap["AIN-A"] = SRM_RTCOD_AIN_EL_ABD_1970_BAHRAIN_ISLAND;
   rtMap["AIN-B"] = SRM_RTCOD_AIN_EL_ABD_1970_SAUDI_ARABIA;
   rtMap["AMA"] = SRM_RTCOD_AMERICAN_SAMOA_1962_AMERICAN_SAMOA_ISLANDS;
   rtMap["ANO"] = SRM_RTCOD_ANNA_1_1965_COCOS_ISLANDS;
   rtMap["ARF-M"] = SRM_RTCOD_ARC_1950_MEAN_SOLUTION;
   rtMap["ARF-A"] = SRM_RTCOD_ARC_1950_BOTSWANA;
   rtMap["ARF-B"] = SRM_RTCOD_ARC_1950_LESOTHO;
   rtMap["ARF-C"] = SRM_RTCOD_ARC_1950_MALAWI;
   rtMap["ARF-D"] = SRM_RTCOD_ARC_1950_SWAZILAND;
   rtMap["ARF-E"] = SRM_RTCOD_ARC_1950_ZAIRE;
   rtMap["ARF-F"] = SRM_RTCOD_ARC_1950_ZAMBIA;
   rtMap["ARF-G"] = SRM_RTCOD_ARC_1950_3_ZIMBABWE;
   rtMap["ARF-H"] = SRM_RTCOD_ARC_1950_BURUNDI;
   rtMap["ARS-M"] = SRM_RTCOD_ARC_1960_MEAN_SOLUTION;
   rtMap["ARS-A"] = SRM_RTCOD_ARC_1960_3_KENYA;
   rtMap["ARS-B"] = SRM_RTCOD_ARC_1960_TANZANIA;
   rtMap["ASC"] = SRM_RTCOD_ASCENSION_1958_ASCENSION_ISLAND;
   rtMap["ASM"] = SRM_RTCOD_MONTSERRAT_1958_MONTSERRAT_LEEWARD_ISLANDS;
   rtMap["ASQ"] = SRM_RTCOD_MARCUS_STATION_1952_MARCUS_ISLANDS;
   rtMap["ATF"] = SRM_RTCOD_BEACON_E_1945_IWO_JIMA_ISLAND;
   rtMap["AUA"] = SRM_RTCOD_AUSTRALIAN_GEOD_1966_AUSTRALIA_TASMANIA;
   rtMap["AUG"] = SRM_RTCOD_AUSTRALIAN_GEOD_1984_3_AUSTRALIA_TASMANIA;
   rtMap["BAT"] = SRM_RTCOD_DJAKARTA_1987_SUMATRA;
   rtMap["BID"] = SRM_RTCOD_BISSAU_1991_GUINEA_BISSAU;
   rtMap["BER"] = SRM_RTCOD_BERMUDA_1957_BERMUDA;
   rtMap["BOO"] = SRM_RTCOD_BOGOTA_OBS_1987_COLOMBIA;
   rtMap["BUR"] = SRM_RTCOD_BUKIT_RIMPAH_1987_BANGKA_BELITUNG_ISLANDS;
   rtMap["CAC"] = SRM_RTCOD_CAPE_CANAVERAL_1991_MEAN_SOLUTION;
   rtMap["CAI"] = SRM_RTCOD_CAMPO_INCHAUSPE_1969_ARGENTINA;
   rtMap["CAO"] = SRM_RTCOD_CANTON_1966_PHOENIX_ISLANDS;
   rtMap["CAP"] = SRM_RTCOD_CAPE_1987_SOUTH_AFRICA;
   rtMap["CAZ"] = SRM_RTCOD_CAMP_AREA_1987_MCMURDO_CAMP;
   rtMap["CCD"] = SRM_RTCOD_S_JTSK_1993_CZECH_REP_SLOVAKIA;
   rtMap["CGE"] = SRM_RTCOD_CARTHAGE_1987_TUNISIA;
   rtMap["CHI"] = SRM_RTCOD_CHATHAM_1971_CHATHAM_ISLANDS;
   rtMap["CHU"] = SRM_RTCOD_CHUA_1987_PARAGUAY;
   rtMap["COA"] = SRM_RTCOD_CORREGO_ALEGRE_1987_BRAZIL;
   rtMap["DAL"] = SRM_RTCOD_DABOLA_1991_GUINEA;
   rtMap["DID"] = SRM_RTCOD_DECEPTION_1993_DECEPTION_ISLAND;
   rtMap["DOB"] = SRM_RTCOD_GUX_1_1987_GUADALCANAL_ISLAND;
   rtMap["EAS"] = SRM_RTCOD_EASTER_1967_EASTER_ISLAND;
   rtMap["ENW"] = SRM_RTCOD_WAKE_ENIWETOK_1960_MARSHALL_ISLANDS;
   rtMap["EST"] = SRM_RTCOD_ESTONIA_1937_ESTONIA;
   rtMap["EUR-M"] = SRM_RTCOD_EUROPE_1950_MEAN_SOLUTION;
   rtMap["EUR-A"] = SRM_RTCOD_EUROPE_1950_W_EUROPE_MEAN_SOLUTION;
   rtMap["EUR-B"] = SRM_RTCOD_EUROPE_1950_GREECE;
   rtMap["EUR-C"] = SRM_RTCOD_EUROPE_1950_NORWAY;
   rtMap["EUR-D"] = SRM_RTCOD_EUROPE_1950_PORTUGAL_SPAIN;
   rtMap["EUR-E"] = SRM_RTCOD_EUROPE_1950_3_CYPRUS;
   rtMap["EUR-F"] = SRM_RTCOD_EUROPE_1950_EGYPT;
   rtMap["EUR-G"] = SRM_RTCOD_EUROPE_1950_ENGLAND_SCOTLAND;
   rtMap["EUR-H"] = SRM_RTCOD_EUROPE_1950_IRAN;
   rtMap["EUR-I"] = SRM_RTCOD_EUROPE_1950_SARDINIA;
   rtMap["EUR-J"] = SRM_RTCOD_EUROPE_1950_SICILY;
   rtMap["EUR-K"] = SRM_RTCOD_EUROPE_1950_IRELAND;
   rtMap["EUR-L"] = SRM_RTCOD_EUROPE_1950_MALTA;
   rtMap["EUR-S"] = SRM_RTCOD_EUROPE_1950_IRAQ;
   rtMap["EUR-T"] = SRM_RTCOD_EUROPE_1950_TUNISIA;
   rtMap["EUS"] = SRM_RTCOD_EUROPE_1979_MEAN_SOLUTION;
   rtMap["FAH"] = SRM_RTCOD_FAHUD_1987_3_OMAN;
   rtMap["FLO"] = SRM_RTCOD_OBSERV_METEORO_1939_CORVO_FLORES_ISLANDS;
   rtMap["FOT"] = SRM_RTCOD_FORT_THOMAS_1955_ST_KITTS_NEVIS_LEEWARD_ISLANDS;
   rtMap["GAA"] = SRM_RTCOD_GAN_1970_MALDIVES;
   rtMap["GEO"] = SRM_RTCOD_GEODETIC_DATUM_1949_3_NEW_ZEALAND;
   rtMap["GIZ"] = SRM_RTCOD_DOS_1968_GIZO_ISLAND;
   rtMap["GRA"] = SRM_RTCOD_GRACIOSA_BASE_SW_1948_CENTRAL_AZORES;
   rtMap["GUA"] = SRM_RTCOD_GUAM_1963_GUAM;
   rtMap["GSE"] = SRM_RTCOD_GUNONG_SEGARA_1987_KALIMANTAN_ISLAND;
   rtMap["HEN"] = SRM_RTCOD_HERAT_NORTH_1987_AFGHANISTAN;
   rtMap["HER"] = SRM_RTCOD_HERMANNSKOGEL_1871_3_YUGOSLAVIA;
   rtMap["HIT"] = SRM_RTCOD_PROV_S_CHILEAN_1963_SOUTH_CHILE;
   rtMap["HJO"] = SRM_RTCOD_HJORSEY_1955_ICELAND;
   rtMap["HKD"] = SRM_RTCOD_HONG_KONG_1963_HONG_KONG;
   rtMap["HTN"] = SRM_RTCOD_HU_TZU_SHAN_1991_TAIWAN;
   rtMap["IBE"] = SRM_RTCOD_BELLEVUE_IGN_1987_EFATE_ERROMANGO_ISLANDS;
   rtMap["IDN"] = SRM_RTCOD_INDONESIAN_1974_INDONESIA;
   rtMap["IND-B"] = SRM_RTCOD_INDIAN_1916_3_BANGLADESH;
   rtMap["IND-I"] = SRM_RTCOD_INDIAN_1956_INDIA_NEPAL;
   rtMap["IND-P"] = SRM_RTCOD_INDIAN_1962_PAKISTAN;
   rtMap["INF-A"] = SRM_RTCOD_INDIAN_1954_THAILAND;
   rtMap["ING-A"] = SRM_RTCOD_INDIAN_1960_VIETNAM_16_N;
   rtMap["ING-B"] = SRM_RTCOD_INDIAN_1960_CON_SON_ISLAND;
   rtMap["INH-A"] = SRM_RTCOD_INDIAN_1975_1991_THAILAND;
   rtMap["INH-A1"] = SRM_RTCOD_INDIAN_1975_1997_THAILAND;
   rtMap["IRL"] = SRM_RTCOD_IRELAND_1965_3_IRELAND;
   rtMap["ISG"] = SRM_RTCOD_ISTS_061_1968_SOUTH_GEORGIA_ISLAND;
   rtMap["IST"] = SRM_RTCOD_ISTS_073_1969_DIEGO_GARCIA;
   rtMap["JOH"] = SRM_RTCOD_JOHNSTON_1961_JOHNSTON_ISLAND;
   rtMap["KAN"] = SRM_RTCOD_KANDAWALA_1987_3_SRI_LANKA;
   rtMap["KEG"] = SRM_RTCOD_KERGUELEN_1949_KERGUELEN_ISLAND;
   rtMap["KEA"] = SRM_RTCOD_KERTAU_1948_3_W_MALAYSIA_SINGAPORE;
   rtMap["KUS"] = SRM_RTCOD_KUSAIE_1951_CAROLINE_ISLANDS;
   rtMap["LCF"] = SRM_RTCOD_LC5_1961_CAYMAN_BRAC_ISLAND;
   rtMap["LEH"] = SRM_RTCOD_LEIGON_1991_3_GHANA;
   rtMap["LIB"] = SRM_RTCOD_LIBERIA_1964_LIBERIA;
   rtMap["LUZ-A"] = SRM_RTCOD_LUZON_1987_PHILIPPINES_EXCLUDING_MINDANAO_ISLAND;
   rtMap["LUZ-B"] = SRM_RTCOD_LUZON_1987_MINDANAO_ISLAND;
   rtMap["MAS"] = SRM_RTCOD_MASSAWA_1987_ERITREA_ETHIOPIA;
   rtMap["MER"] = SRM_RTCOD_MERCHICH_1987_MOROCCO;
   rtMap["MID"] = SRM_RTCOD_MIDWAY_1961_MIDWAY_ISLANDS;
   rtMap["MIK"] = SRM_RTCOD_MAHE_1971_MAHE_ISLAND;
   rtMap["MIN-A"] = SRM_RTCOD_MINNA_1991_CAMEROON;
   rtMap["MIN-B"] = SRM_RTCOD_MINNA_1991_NIGERIA;
   rtMap["MOD"] = SRM_RTCOD_ROME_1940_SARDINIA;
   rtMap["MPO"] = SRM_RTCOD_M_PORALOKO_1991_GABON;
   rtMap["MVS"] = SRM_RTCOD_VITI_LEVU_1916_VITI_LEVU_ISLANDS;
   rtMap["NAH-A"] = SRM_RTCOD_NAHRWAN_1987_MASIRAH_ISLAND;
   rtMap["NAH-B"] = SRM_RTCOD_NAHRWAN_1987_UNITED_ARAB_EMIRATES;
   rtMap["NAH-C"] = SRM_RTCOD_NAHRWAN_1987_SAUDI_ARABIA;
   rtMap["NAP"] = SRM_RTCOD_NAPARIMA_1991_TRINIDAD_TOBAGO;
   rtMap["NAR-A"] = SRM_RTCOD_N_AM_1983_ALASKA_EXCLUDING_ALEUTIAN_ISLANDS;
   rtMap["NAR-B"] = SRM_RTCOD_N_AM_1983_CANADA;
   rtMap["NAR-C"] = SRM_RTCOD_N_AM_1983_CONTINENTAL_US;
   rtMap["NAR-D"] = SRM_RTCOD_N_AM_1983_MEXICO_CENTRAL_AMERICA;
   rtMap["NAR-E"] = SRM_RTCOD_N_AM_1983_ALEUTIAN_ISLANDS;
   rtMap["NAR-H"] = SRM_RTCOD_N_AM_1983_HAWAII;
   rtMap["NAS-A"] = SRM_RTCOD_N_AM_1927_EASTERN_US;
   rtMap["NAS-B"] = SRM_RTCOD_N_AM_1927_WESTERN_US;
   rtMap["NAS-C"] = SRM_RTCOD_N_AM_1927_CONTINENTAL_US;
   rtMap["NAS-D"] = SRM_RTCOD_N_AM_1927_ALASKA_EXCLUDING_ALEUTIAN_ISLANDS;
   rtMap["NAS-E"] = SRM_RTCOD_N_AM_1927_CANADA;
   rtMap["NAS-F"] = SRM_RTCOD_N_AM_1927_ALBERTA_BRITISH_COLUMBIA;
   rtMap["NAS-G"] = SRM_RTCOD_N_AM_1927_EASTERN_CANADA;
   rtMap["NAS-H"] = SRM_RTCOD_N_AM_1927_MANITOBA_ONTARIO;
   rtMap["NAS-I"] = SRM_RTCOD_N_AM_1927_NORTHWEST_TERRITORIES_SASKATCHEWAN;
   rtMap["NAS-J"] = SRM_RTCOD_N_AM_1927_YUKON;
   rtMap["NAS-L"] = SRM_RTCOD_N_AM_1927_MEXICO;
   rtMap["NAS-N"] = SRM_RTCOD_N_AM_1927_CENTRAL_AMERICA;
   rtMap["NAS-O"] = SRM_RTCOD_N_AM_1927_CANAL_ZONE;
   rtMap["NAS-P"] = SRM_RTCOD_N_AM_1927_CARIBBEAN;
   rtMap["NAS-Q"] = SRM_RTCOD_N_AM_1927_BAHAMAS_EXCLUDING_SAN_SALVADOR_ISLAND;
   rtMap["NAS-R"] = SRM_RTCOD_N_AM_1927_SAN_SALVADOR_ISLAND;
   rtMap["NAS-T"] = SRM_RTCOD_N_AM_1927_CUBA;
   rtMap["NAS-U"] = SRM_RTCOD_N_AM_1927_HAYES_PENINSULA;
   rtMap["NAS-V"] = SRM_RTCOD_N_AM_1927_EAST_ALEUTIAN_ISLANDS;
   rtMap["NAS-W"] = SRM_RTCOD_N_AM_1927_WEST_ALEUTIAN_ISLANDS;
   rtMap["NSD"] = SRM_RTCOD_N_SAHARA_1959_ALGERIA;
   rtMap["OEG"] = SRM_RTCOD_OLD_EGYPTIAN_1907_EGYPT;
   rtMap["OGB-M"] = SRM_RTCOD_OSGB_1936_3_MEAN_SOLUTION;
   rtMap["OGB-A"] = SRM_RTCOD_OSGB_1936_ENGLAND;
   rtMap["OGB-B"] = SRM_RTCOD_OSGB_1936_ENGLAND_ISLE_OF_MAN_WALES;
   rtMap["OGB-C"] = SRM_RTCOD_OSGB_1936_SCOTLAND_SHETLAND_ISLANDS;
   rtMap["OGB-D"] = SRM_RTCOD_OSGB_1936_WALES;
   rtMap["OHA-M"] = SRM_RTCOD_OLD_HAWAIIAN_INT_1987_MEAN_SOLUTION;
   rtMap["OHA-A"] = SRM_RTCOD_OLD_HAWAIIAN_INT_1987_HAWAII;
   rtMap["OHA-B"] = SRM_RTCOD_OLD_HAWAIIAN_INT_1987_KAUAI;
   rtMap["OHA-C"] = SRM_RTCOD_OLD_HAWAIIAN_INT_1987_MAUI;
   rtMap["OHA-D"] = SRM_RTCOD_OLD_HAWAIIAN_INT_1987_OAHU;
   rtMap["OHI-M"] = SRM_RTCOD_OLD_HAWAIIAN_INT_1987_MEAN_SOLUTION;
   rtMap["OHI-A"] = SRM_RTCOD_OLD_HAWAIIAN_INT_1987_HAWAII;
   rtMap["OHI-B"] = SRM_RTCOD_OLD_HAWAIIAN_INT_1987_KAUAI;
   rtMap["OHI-C"] = SRM_RTCOD_OLD_HAWAIIAN_INT_1987_MAUI;
   rtMap["OHI-D"] = SRM_RTCOD_OLD_HAWAIIAN_INT_1987_OAHU;
   rtMap["PHA"] = SRM_RTCOD_AYABELLE_LIGHTHOUSE_1991_DJIBOUTI;
   rtMap["PIT"] = SRM_RTCOD_PITCAIRN_1967_PITCAIRN_ISLAND;
   rtMap["PLN"] = SRM_RTCOD_PICO_DE_LAS_NIEVES_1987_CANARY_ISLANDS;
   rtMap["POS"] = SRM_RTCOD_PORTO_SANTO_1936_PORTO_SANTO_MADEIRA_ISLANDS;
   rtMap["PRP-A"] = SRM_RTCOD_PROV_S_AM_1956_BOLIVIA;
   rtMap["PRP-B"] = SRM_RTCOD_PROV_S_AM_1956_N_CHILE_19_S;
   rtMap["PRP-C"] = SRM_RTCOD_PROV_S_AM_1956_S_CHILE_43_S;
   rtMap["PRP-D"] = SRM_RTCOD_PROV_S_AM_1956_COLOMBIA;
   rtMap["PRP-E"] = SRM_RTCOD_PROV_S_AM_1956_ECUADOR;
   rtMap["PRP-F"] = SRM_RTCOD_PROV_S_AM_1956_GUYANA;
   rtMap["PRP-G"] = SRM_RTCOD_PROV_S_AM_1956_PERU;
   rtMap["PRP-H"] = SRM_RTCOD_PROV_S_AM_1956_3_VENEZUELA;
   rtMap["PRP-M"] = SRM_RTCOD_PROV_S_AM_1956_MEAN_SOLUTION;
   rtMap["PTB"] = SRM_RTCOD_POINT_58_1991_MEAN_SOLUTION;
   rtMap["PTN"] = SRM_RTCOD_POINTE_NOIRE_1948_CONGO;
   rtMap["PUK"] = SRM_RTCOD_PULKOVO_1942_RUSSIA;
   rtMap["PUR"] = SRM_RTCOD_PUERTO_RICO_1987_PUERTO_RICO_VIRGIN_ISLANDS;
   rtMap["QAT"] = SRM_RTCOD_QATAR_NATIONAL_1974_3_QATAR;
   rtMap["QUO"] = SRM_RTCOD_QORNOQ_1987_SOUTH_GREENLAND;
   rtMap["REU"] = SRM_RTCOD_REUNION_1947_MASCARENE_ISLANDS;
   rtMap["SAE"] = SRM_RTCOD_SANTO_DOS_1965_ESPIRITO_SANTO_ISLAND;
   rtMap["SAO"] = SRM_RTCOD_SAO_BRAZ_1987_SAO_MIGUEL_SANTA_MARIA_ISLANDS;
   rtMap["SAP"] = SRM_RTCOD_SAPPER_HILL_1943_3_E_FALKLAND_ISLANDS;
   rtMap["SAN-M"] = SRM_RTCOD_S_AM_1969_MEAN_SOLUTION;
   rtMap["SAN-A"] = SRM_RTCOD_S_AM_1969_ARGENTINA;
   rtMap["SAN-B"] = SRM_RTCOD_S_AM_1969_BOLIVIA;
   rtMap["SAN-C"] = SRM_RTCOD_S_AM_1969_BRAZIL;
   rtMap["SAN-D"] = SRM_RTCOD_S_AM_1969_CHILE;
   rtMap["SAN-E"] = SRM_RTCOD_S_AM_1969_COLOMBIA;
   rtMap["SAN-F"] = SRM_RTCOD_S_AM_1969_ECUADOR_EXCLUDING_GALAPAGOS_ISLANDS;
   rtMap["SAN-G"] = SRM_RTCOD_S_AM_1969_GUYANA;
   rtMap["SAN-H"] = SRM_RTCOD_S_AM_1969_PARAGUAY;
   rtMap["SAN-I"] = SRM_RTCOD_S_AM_1969_PERU;
   rtMap["SAN-J"] = SRM_RTCOD_S_AM_1969_BALTRA_GALAPAGOS_ISLANDS;
   rtMap["SAN-K"] = SRM_RTCOD_S_AM_1969_TRINIDAD_TOBAGO;
   rtMap["SAN-L"] = SRM_RTCOD_S_AM_1969_VENEZUELA;
   rtMap["SCK"] = SRM_RTCOD_SCHWARZECK_1991_NAMIBIA;
   rtMap["SGM"] = SRM_RTCOD_SELVAGEM_GRANDE_1938_SALVAGE_ISLANDS;
   rtMap["SHB"] = SRM_RTCOD_DOS_71_4_1987_ST_HELENA_ISLAND;
   rtMap["SOA"] = SRM_RTCOD_S_ASIA_1987_SINGAPORE;
   rtMap["SPK-A"] = SRM_RTCOD_S42_PULKOVO_HUNGARY;
   rtMap["SPK-B"] = SRM_RTCOD_S42_PULKOVO_3_POLAND;
   rtMap["SPK-C"] = SRM_RTCOD_S42_PULKOVO_CZECH_REPUBLIC_SLOVAKIA;
   rtMap["SPK-D"] = SRM_RTCOD_S42_PULKOVO_LATVIA;
   rtMap["SPK-E"] = SRM_RTCOD_S42_PULKOVO_KAZAKHSTAN;
   rtMap["SPK-F"] = SRM_RTCOD_S42_PULKOVO_ALBANIA;
   rtMap["SPK-G"] = SRM_RTCOD_S42_PULKOVO_G_ROMANIA;
   rtMap["SRL"] = SRM_RTCOD_SIERRA_LEONE_1960_SIERRA_LEONE;
   rtMap["TAN"] = SRM_RTCOD_TANANARIVE_OBS_1925_3_MADAGASCAR;
   rtMap["TDC"] = SRM_RTCOD_TRISTAN_1968_TRISTAN_DA_CUNHA;
   rtMap["TIL"] = SRM_RTCOD_TIMBALAI_EVEREST_1948_3_BRUNEI_E_MALAYSIA;
   rtMap["TOY-A"] = SRM_RTCOD_TOKYO_1991_JAPAN;
   rtMap["TOY-B"] = SRM_RTCOD_TOKYO_1991_1991_SOUTH_KOREA;
   rtMap["TOY-B1"] = SRM_RTCOD_TOKYO_1991_1997_SOUTH_KOREA;
   rtMap["TOY-C"] = SRM_RTCOD_TOKYO_1991_OKINAWA;
   rtMap["TOY-M"] = SRM_RTCOD_TOKYO_1991_MEAN_SOLUTION;
   rtMap["TRN"] = SRM_RTCOD_TERN_1961_TERN_ISLAND;
   rtMap["VOI"] = SRM_RTCOD_VOIROL_1874_ALGERIA;
   rtMap["VOR"] = SRM_RTCOD_VOIROL_1960_ALGERIA;
   rtMap["WAK"] = SRM_RTCOD_WAKE_1952_WAKE_ATOLL;
   rtMap["WGE"] = SRM_RTCOD_WGS_1984_IDENTITY;
   rtMap["YAC"] = SRM_RTCOD_YACARE_1987_URUGUAY;
   rtMap["ZAN"] = SRM_RTCOD_ZANDERIJ_1987_SURINAME;
   rtMap["KGS"] = SRM_RTCOD_KOREAN_GEODETIC_1995_SOUTH_KOREA;
   rtMap["SIR"] = SRM_RTCOD_SIRGAS_2000_IDENTITY_BY_MEASUREMENT;
   rtMap["Test_SRMmax"] = SRM_RTCOD_EXPERIMENTAL_NGA_MAX_IDENTITY_BY_DEFAULT;
   rtMap["Test_sphere"] = SRM_RTCOD_EXPERIMENTAL_NGA_SPHERE_IDENTITY_BY_DEFAULT;
}

void printData(std::vector<doubleArray3>& inDoubleParam, const int length)
{
   doubleArray3 data{};

   for (int i = 0; i < (int)inDoubleParam.size(); i++) {
      data = inDoubleParam.at(i);
      std::cout << i + 1 << " ";
      for (int j = 0; j < length; j++)
         std::cout << data.var[j] << ", ";
      std::cout << std::endl;
   }
}

void printData(gdDatumCoord& gdCoord)
{
   std::cout << "CD DT Coord=> " << gdCoord.datum_name_in << ", ";
   std::cout << gdCoord.datum_name_out << ", ";
   std::cout << "( " << gdCoord.gd_coord_in[0] << ", " << gdCoord.gd_coord_in[1] << ", " << gdCoord.gd_coord_in[2] << " )" << std::endl;
   std::cout << "( " << gdCoord.gd_coord_out[0] << ", " << gdCoord.gd_coord_out[1] << ", " << gdCoord.gd_coord_out[2] << " )" << std::endl;
   std::cout << "( " << gdCoord.comp_coord_out[0] << ", " << gdCoord.comp_coord_out[1] << ", " << gdCoord.comp_coord_out[2] << " )" << std::endl;
}

void printData(std::vector<configInfo>& config)
{
   configInfo data{};

   for (int i = 0; i < (int)config.size(); i++) {
      data = config.at(i);
      std::cout << data.path << ", " << data.file_name_1 << ", " << data.file_name_2 << std::endl;
   }
}

void printData(statInfo& results)
{
   std::cout << "Count => " << results.count << std::endl;
   std::cout << "Min   => " << results.min << std::endl;
   std::cout << "Max   => " << results.max << std::endl;
   std::cout << "Mean  => " << results.mean << std::endl;
   std::cout << "StdDev=> " << results.stdDev << std::endl;
   std::cout << "Message=> " << results.message << std::endl;
}

void printData(srm::Coord3D* coord)
{
   std::cout << "[ ";
   std::cout << coord->getValues()[0] << ", ";
   std::cout << coord->getValues()[1] << ", ";
   std::cout << coord->getValues()[2] << " ]";
   std::cout << std::endl;
}

void printData(doubleArray3& coord)
{
   std::cout << "[ " << coord.var[0] * toRad;
   std::cout << ", ";
   std::cout << coord.var[1] * toRad << ", ";
   std::cout << coord.var[2] << " ]" << std::endl;
}

void printData(std::vector<diffInfo>& diffs)
{
   for (int i = 0; i < diffs.size(); i++) {
      std::cout << i << ", ";
      std::cout << diffs[i].compOut.var[0] << ", ";
      std::cout << diffs[i].compOut.var[1] << ", ";
      std::cout << diffs[i].compOut.var[2] << ", ";
      std::cout << diffs[i].diff << std::endl;
   }
}

void printData(srfParams& srfParam)
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
   time_t date; // Make a time_t object that'll hold the date
   time(&date); //  Set the date variable to the current date

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
   char* source_file_name,
   char* target_file_name,
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

bool load_file(const char* file_name, std::vector<configInfo>& config)
{
   std::FILE* inFile = std::fopen(file_name, "r");

   if (!inFile) {
      std::cout << "Unable to open " << file_name << " file";
      return false; // terminate with error
   }

   readCSV(inFile, config);

   std::fclose(inFile);

   return true;
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
