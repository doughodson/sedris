
#include "srm.h"
#include "cimpl_DestroySRF.hpp"
#include "srm_level_0_int_types.hpp"

extern "C"
{

SRM_Status_Code
cimpl_SRM_DestroySRF
(
   SRM_Object_Reference object,
   int                  class_type
)
{
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    switch(class_type)
    {
        case (BaseSRF::SRF_TYP_CC):
        {
             delete ((SRM_Celestiocentric *)object)->methods;
             ((SRM_Celestiocentric *)object)->methods = 0;
             ((SRM_Celestiocentric *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_CD):
        {
             delete ((SRM_Celestiodetic *)object)->methods;
             ((SRM_Celestiodetic *)object)->methods = 0;
             ((SRM_Celestiodetic *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_CM):
        {
             delete ((SRM_Celestiomagnetic *)object)->methods;
             ((SRM_Celestiomagnetic *)object)->methods = 0;
             ((SRM_Celestiomagnetic *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_EC):
        {
             delete ((SRM_EquidistantCylindrical *)object)->methods;
             ((SRM_EquidistantCylindrical *)object)->methods = 0;
             ((SRM_EquidistantCylindrical *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_EI):
        {
             delete ((SRM_EquatorialInertial *)object)->methods;
             ((SRM_EquatorialInertial *)object)->methods = 0;
             ((SRM_EquatorialInertial *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_HAEC):
        {
             delete ((SRM_HeliosphericAriesEcliptic *)object)->methods;
             ((SRM_HeliosphericAriesEcliptic *)object)->methods = 0;
             ((SRM_HeliosphericAriesEcliptic *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_HEEC):
        {
             delete ((SRM_HeliosphericEarthEcliptic *)object)->methods;
             ((SRM_HeliosphericEarthEcliptic *)object)->methods = 0;
             ((SRM_HeliosphericEarthEcliptic *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_HEEQ):
        {
             delete ((SRM_HeliosphericEarthEquatorial *)object)->methods;
             ((SRM_HeliosphericEarthEquatorial *)object)->methods = 0;
             ((SRM_HeliosphericEarthEquatorial *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_LCC):
        {
             delete ((SRM_LambertConformalConic *)object)->methods;
             ((SRM_LambertConformalConic *)object)->methods = 0;
             ((SRM_LambertConformalConic *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_LCE_3D):
        {
             delete ((SRM_LococentricEuclidean3D *)object)->methods;
             ((SRM_LococentricEuclidean3D *)object)->methods = 0;
             ((SRM_LococentricEuclidean3D *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_LSA):
        {
             delete ((SRM_LocalSpaceAzimuthal *)object)->methods;
             ((SRM_LocalSpaceAzimuthal *)object)->methods = 0;
             ((SRM_LocalSpaceAzimuthal *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_LSP):
        {
             delete ((SRM_LocalSpacePolar *)object)->methods;
             ((SRM_LocalSpacePolar *)object)->methods = 0;
             ((SRM_LocalSpacePolar *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_LSR_2D):
        {
             delete ((SRM_LocalSpaceRectangular2D *)object)->methods;
             ((SRM_LocalSpaceRectangular2D *)object)->methods = 0;
             ((SRM_LocalSpaceRectangular2D *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_LSR_3D):
        {
             delete ((SRM_LocalSpaceRectangular3D *)object)->methods;
             ((SRM_LocalSpaceRectangular3D *)object)->methods = 0;
             ((SRM_LocalSpaceRectangular3D *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_LTSAS):
        {
             delete ((SRM_LocalTangentSpaceAzimuthalSpherical *)object)->methods;
             ((SRM_LocalTangentSpaceAzimuthalSpherical *)object)->methods = 0;
             ((SRM_LocalTangentSpaceAzimuthalSpherical *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_LTSC):
        {
             delete ((SRM_LocalTangentSpaceCylindrical *)object)->methods;
             ((SRM_LocalTangentSpaceCylindrical *)object)->methods = 0;
             ((SRM_LocalTangentSpaceCylindrical *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_LTSE):
        {
             delete ((SRM_LocalTangentSpaceEuclidean *)object)->methods;
             ((SRM_LocalTangentSpaceEuclidean *)object)->methods = 0;
             ((SRM_LocalTangentSpaceEuclidean *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_M):
        {
             delete ((SRM_Mercator *)object)->methods;
             ((SRM_Mercator *)object)->methods = 0;
             ((SRM_Mercator *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_OMS):
        {
             delete ((SRM_ObliqueMercatorSpherical *)object)->methods;
             ((SRM_ObliqueMercatorSpherical *)object)->methods = 0;
             ((SRM_ObliqueMercatorSpherical *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_PD):
        {
             delete ((SRM_Planetodetic *)object)->methods;
             ((SRM_Planetodetic *)object)->methods = 0;
             ((SRM_Planetodetic *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_PS):
        {
             delete ((SRM_PolarStereographic *)object)->methods;
             ((SRM_PolarStereographic *)object)->methods = 0;
             ((SRM_PolarStereographic *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_SEC):
        {
             delete ((SRM_SolarEcliptic *)object)->methods;
             ((SRM_SolarEcliptic *)object)->methods = 0;
             ((SRM_SolarEcliptic *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_SEQ):
        {
             delete ((SRM_SolarEquatorial *)object)->methods;
             ((SRM_SolarEquatorial *)object)->methods = 0;
             ((SRM_SolarEquatorial *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_SME):
        {
             delete ((SRM_SolarMagneticEcliptic *)object)->methods;
             ((SRM_SolarMagneticEcliptic *)object)->methods = 0;
             ((SRM_SolarMagneticEcliptic *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_SMD):
        {
             delete ((SRM_SolarMagneticDipole *)object)->methods;
             ((SRM_SolarMagneticDipole *)object)->methods = 0;
             ((SRM_SolarMagneticDipole *)object)->state   = 0;
             break;
        }
        case (BaseSRF::SRF_TYP_TM):
        {
             delete ((SRM_TransverseMercator *)object)->methods;
             ((SRM_TransverseMercator *)object)->methods = 0;
             ((SRM_TransverseMercator *)object)->state   = 0;
             break;
        }
        default:
        {
             status = SRM_STATCOD_INVALID_INPUT;
             break;
        }
    }
    return status;
}

} /* end extern 'C' */
