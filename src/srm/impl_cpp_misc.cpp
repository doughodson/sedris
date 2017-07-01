
#include "impl_cpp_misc.h"
#include "Exception.h"
#include "string.h"

bool srm::isLegalSRFTCode (SRM_SRFT_Code srft_code)
{
    return (srft_code > 0 && srft_code <= SRM_SRFT_CODE_UBOUND);
}

bool srm::isLegalSRFCode (SRM_SRF_Code srf_code)
{
    return (srf_code > 0 && srf_code <= SRM_SRF_CODE_UBOUND);
}

bool srm::isLegalSRFSetCode (SRM_SRFS_Code srfs_code)
{
    return (srfs_code > 0 && srfs_code <= SRM_SRFS_CODE_UBOUND);
}

bool srm::isLegalORMCode (SRM_ORM_Code orm_code, SRM_RT_Code rt_code)
{
    return Impl_wellFormedRTCode(orm_code, rt_code);
}

bool srm::isLegalRTCode (SRM_SRF_Code srf_code, SRM_RT_Code rt_code)
{
    switch (srf_code)
    {
    case SRM_SRFCOD_BRITISH_NATIONAL_GRID_AIRY: //TM
      return Impl_wellFormedRTCode(SRM_ORMCOD_OSGB_1936, rt_code);
      break;
    case SRM_SRFCOD_BRITISH_OSGRS80_GRID: //TM
      return Impl_wellFormedRTCode(SRM_ORMCOD_ETRS_1989, rt_code);
      break;
    case SRM_SRFCOD_DELAWARE_SPCS_1983: //TM
      return Impl_wellFormedRTCode(SRM_ORMCOD_N_AM_1983, rt_code);
      break;
    case SRM_SRFCOD_GEOCENTRIC_WGS_1984: //CC
      return Impl_wellFormedRTCode(SRM_ORMCOD_WGS_1984, rt_code);
      break;
    case SRM_SRFCOD_GEODETIC_AUSTRALIA_1984: //CD
      return Impl_wellFormedRTCode(SRM_ORMCOD_AUSTRALIAN_GEOD_1984, rt_code);
      break;
    case SRM_SRFCOD_GEODETIC_WGS_1984: //CD
      return Impl_wellFormedRTCode(SRM_ORMCOD_WGS_1984, rt_code);
      break;
    case SRM_SRFCOD_GEODETIC_N_AMERICAN_1983: //CD
      return Impl_wellFormedRTCode(SRM_ORMCOD_N_AM_1983, rt_code);
      break;
    case SRM_SRFCOD_IRISH_GRID_1965: //TM
      return Impl_wellFormedRTCode(SRM_ORMCOD_IRELAND_1965, rt_code);
      break;
    case SRM_SRFCOD_IRISH_TRANSVERSE_MERCATOR_1989: //TM
      return Impl_wellFormedRTCode(SRM_ORMCOD_ETRS_1989, rt_code);
      break;
    case SRM_SRFCOD_LAMBERT_93: //LCC
      return Impl_wellFormedRTCode(SRM_ORMCOD_RGF_1993, rt_code);
      break;
    case SRM_SRFCOD_LAMBERT_II_WIDE: //LCC
      return Impl_wellFormedRTCode(SRM_ORMCOD_NTF_1896_PM_PARIS, rt_code);
      break;
    case SRM_SRFCOD_MARS_PLANETOCENTRIC_2000:
      return Impl_wellFormedRTCode(SRM_ORMCOD_MARS_SPHERE_2000, rt_code);
      break;
    case SRM_SRFCOD_MARS_PLANETOGRAPHIC_2000:
      return Impl_wellFormedRTCode(SRM_ORMCOD_MARS_2000, rt_code);
      break;
    case SRM_SRFCOD_MARYLAND_SPCS_1983: //LCC
      return Impl_wellFormedRTCode(SRM_ORMCOD_N_AM_1983, rt_code);
      break;
    default:
      // this should never be reached
      throw Exception(SRM_STATCOD_INVALID_CODE, "createStandardSRF: Invalid RT with standard ORM");
    }
}

bool srm::isEqualVec3
(
    const SRM_Vector_3D vec1,
    const SRM_Vector_3D vec2
)
{
    return (vec1[0]==vec2[0] &&
            vec1[1]==vec2[1] &&
            vec1[2]==vec2[2]);
}

bool srm::isEqualVec2
(
    const SRM_Vector_2D vec1,
    const SRM_Vector_2D vec2
)
{
    return (vec1[0]==vec2[0] &&
            vec1[1]==vec2[1]);
}

bool srm::isEqualMat
(
    const SRM_Matrix_3x3 mat1,
    const SRM_Matrix_3x3 mat2
)
{
    return (mat1[0][0]== mat2[0][0] &&
            mat1[0][1]== mat2[0][1] &&
            mat1[0][2]== mat2[0][2] &&
            mat1[1][0]== mat2[1][0] &&
            mat1[1][1]== mat2[1][1] &&
            mat1[1][2]== mat2[1][2] &&
            mat1[2][0]== mat2[2][0] &&
            mat1[2][1]== mat2[2][1] &&
            mat1[2][2]== mat2[2][2]);
}


void srm::processStatus
(
          Impl_Status  status,
    const char        *method_name,
          objSrcType   objSrc,
          memAllocType memAlloc
)
{
    static char message[500];
    strcpy(message, method_name);

    if (!(status == IMPL_VALID || status == IMPL_EXTENDED || status == IMPL_DEFINED))
    {
        switch (status)
        {
        case IMPL_OBJSRC:
          if (objSrc == SRF)
          {
              throw Exception(SRM_STATCOD_INVALID_SOURCE_SRF,
                              strcat(message, ": Invalid Source SRF"));
          }
          else if (objSrc  == COORD)
              throw Exception(SRM_STATCOD_INVALID_SOURCE_COORDINATE,
                              strcat(message, ": Invalid Source Coordinate"));
          else if (objSrc == DIR)
          {
              throw Exception(SRM_STATCOD_INVALID_SOURCE_DIRECTION,
                              strcat(message, ": Invalid Source Direction"));
          }
          else
          { // must be orientation (ORI)
            throw Exception(SRM_STATCOD_INVALID_SOURCE_ORIENTATION,
                            strcat(message, ": Invalid Source Orientation"));
          }
          break;
        case IMPL_INVALID:
          if (objSrc == SRF)
          {
            throw Exception(SRM_STATCOD_INVALID_SRF,
                            strcat(message, ": Invalid SRF"));
          }
          else if (objSrc == COORD)
          {
            throw Exception(SRM_STATCOD_INVALID_TARGET_COORDINATE,
                            strcat(message, ": Invalid Coordinate"));
          }
          else if (objSrc == DIR)
          {
            throw Exception(SRM_STATCOD_INVALID_TARGET_DIRECTION,
                            strcat(message, ": Invalid Direction"));
          }
          else
          { // must be orientation (ORI)
            throw Exception(SRM_STATCOD_INVALID_TARGET_ORIENTATION,
                            strcat(message, ": Invalid Orientation"));
          }
          break;
        case IMPL_SRFSRC:
          throw Exception(SRM_STATCOD_INVALID_SOURCE_SRF,
                          strcat(message, ": Invalid Source SRF"));
          break;
        case IMPL_SRFTGT:
          throw Exception(SRM_STATCOD_INVALID_SRF,
                          strcat(message, ": Invalid Target SRF"));
          break;
        case IMPL_CRDORG:
          throw Exception(SRM_STATCOD_INVALID_SOURCE_COORDINATE,
                          strcat(message, ": Invalid Source Coordinate"));
          break;
        case IMPL_CRDDST:
          throw Exception(SRM_STATCOD_INVALID_TARGET_COORDINATE,
                          strcat(message, ": Invalid Target Coordinate"));
          break;
        case IMPL_BADORM:
          throw Exception(SRM_STATCOD_INVALID_CODE,
                          strcat(message, ": Invalid ORM Code"));
          break;
        case IMPL_ILLEGL:
          throw Exception(SRM_STATCOD_OPERATION_UNSUPPORTED,
                          strcat(message, ": Unsupported Operation"));
          break;
        case IMPL_FPE:
          throw Exception(SRM_STATCOD_FLOATING_POINT_ERROR,
                          strcat(message, ": Floating Point Error"));
          break;
        case IMPL_MEMALLOC:
          if (memAlloc == CREATE)
          {
            throw Exception(SRM_STATCOD_CREATION_FAILURE,
                            strcat(message, ": Creation Failure"));
          }
          else if (memAlloc == DESTROY)
          {
            throw Exception(SRM_STATCOD_DESTRUCTION_FAILURE,
                            strcat(message, ": Destruction Failure"));
          }
          else
          { // must be general out of memory error (MEM)
            throw Exception(SRM_STATCOD_MEMORY_ALLOCATION_ERROR,
                            strcat(message, ": Out of Memory"));
          }
          break;
        case IMPL_UNIMPLEM:
          throw Exception(SRM_STATCOD_NOT_IMPLEMENTED,
                          strcat(message, ": Method is not Implemented"));
          break;
        case IMPL_INACTBLE:
          throw Exception(SRM_STATCOD_INACTIONABLE,
                          strcat(message, ": Inactionable Failure"));
          break;
        default:
        // throw Inactionable anyway for any other unhandled exceptions.
          throw Exception(SRM_STATCOD_INACTIONABLE,
                          strcat(message, ": Inactionable Failure"));
          break;
        }
    }
}
