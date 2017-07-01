
#ifndef __SRM_SRFP_H__
#define __SRM_SRFP_H__

// Prototypes for functions to manage SRFP structures associated with srfts.

/*These functions determine the size of the SRFP struct for a for a given SRFT*/
extern SRM_Integer Impl_sizeofNULL();
extern SRM_Integer Impl_sizeofCELESTIOCENTRIC();
extern SRM_Integer Impl_sizeofLOC_SPACE_RECT_3D();
extern SRM_Integer Impl_sizeofLOC_SPACE_RECT_2D();
extern SRM_Integer Impl_sizeofCELESTIODETIC();
extern SRM_Integer Impl_sizeofPLANETODETIC();
extern SRM_Integer Impl_sizeofLOC_TAN_EUCLIDEAN();
extern SRM_Integer Impl_sizeofLOC_TAN_AZ_SPHER();
extern SRM_Integer Impl_sizeofAZIMUTHAL();
extern SRM_Integer Impl_sizeofLOC_TAN_CYL();
extern SRM_Integer Impl_sizeofPOLAR();
extern SRM_Integer Impl_sizeofCELESTIOMAGNETIC();
extern SRM_Integer Impl_sizeofEQUATORIAL_INERTIAL();
extern SRM_Integer Impl_sizeofSOLAR_ECLIPTIC();
extern SRM_Integer Impl_sizeofSOLAR_EQUATORIAL();
extern SRM_Integer Impl_sizeofSOLAR_MAGNETIC_ECLIPTIC();
extern SRM_Integer Impl_sizeofSOLAR_MAGNETIC_DIPOLE();
extern SRM_Integer Impl_sizeofHELIO_ARIES_ECLIPTIC();
extern SRM_Integer Impl_sizeofHELIO_EARTH_ECLIPTIC();
extern SRM_Integer Impl_sizeofHELIO_EARTH_EQUAT();
extern SRM_Integer Impl_sizeofMERCATOR();
extern SRM_Integer Impl_sizeofOBLIQUE_MERCATOR();
extern SRM_Integer Impl_sizeofTRANSVERSE_MERCATOR();
extern SRM_Integer Impl_sizeofLAMBERT_CONF_CONIC();
extern SRM_Integer Impl_sizeofPOLAR_STEREOGRAPHIC();
extern SRM_Integer Impl_sizeofEQUIDISTANT_CYL();
extern SRM_Integer Impl_sizeofLOCOCENTRIC_EUCLIDEAN();

/*The following group of functions allocates SRF's given a void pointer
to the necessary parameter structure.  Each function assumes that it
receives a correctly typed parameters structure and this is guaranteed
by indexing the array with the proper template code below.
*/

extern void* Impl_allocsrfNULL(SRM_ORM_Code orm, SRM_RT_Code rt, void* api_templ_param_struct_ptr);
extern void* Impl_allocsrfNOPARAMS(SRM_ORM_Code orm, SRM_RT_Code rt, void* api_templ_param_struct_ptr);
extern void* Impl_allocsrfLOC_SPACE_RECT_3D(SRM_ORM_Code orm, SRM_RT_Code rt, void* api_templ_param_struct_ptr);
extern void* Impl_allocsrfLOC_SPACE_RECT_2D(SRM_ORM_Code orm, SRM_RT_Code rt,void* api_templ_param_struct_ptr);
extern void* Impl_allocsrfLOC_TAN_EUCLIDEAN(SRM_ORM_Code orm, SRM_RT_Code rt,void* api_templ_param_struct_ptr);
extern void* Impl_allocsrfLOC_TAN_AZ_SPHER(SRM_ORM_Code orm, SRM_RT_Code rt, void* api_templ_param_struct_ptr);
extern void* Impl_allocsrfLOC_TAN_CYL(SRM_ORM_Code orm, SRM_RT_Code rt,void* api_templ_param_struct_ptr);
extern void* Impl_allocsrfMERCATOR(SRM_ORM_Code orm, SRM_RT_Code rt,void* api_templ_param_struct_ptr);
extern void* Impl_allocsrfOBLIQUE_MERCATOR(SRM_ORM_Code orm, SRM_RT_Code rt,void* api_templ_param_struct_ptr);
extern void* Impl_allocsrfTRANSVERSE_MERCATOR(SRM_ORM_Code orm, SRM_RT_Code rt,void* api_templ_param_struct_ptr);
extern void* Impl_allocsrfLAMBERT_CONF_CONIC(SRM_ORM_Code orm, SRM_RT_Code rt,void* api_templ_param_struct_ptr);
extern void* Impl_allocsrfPOLAR_STEREOGRAPHIC(SRM_ORM_Code orm, SRM_RT_Code rt,void* api_templ_param_struct_ptr);
extern void* Impl_allocsrfEQUIDISTANT_CYL(SRM_ORM_Code orm, SRM_RT_Code rt, void* api_templ_param_struct_ptr);
extern void* Impl_allocsrfLOCOCENTRIC_EUCLIDEAN(SRM_ORM_Code orm, SRM_RT_Code rt, void* api_templ_param_struct_ptr);



/*!<An array of functions that accept properly typed API parameters
  structures as a void pointer and return API SRF structure's with
  all of the memory holes zeroed as a void pointer.  The array is indexed
  by SRFT code.
*/


#define Impl_allocsrfCELESTIOCENTRIC( a, b, c)\
Impl_allocsrfNOPARAMS(a, b, c)

#define Impl_allocsrfCELESTIODETIC( a, b, c)\
Impl_allocsrfNOPARAMS(a, b, c)

#define Impl_allocsrfPLANETODETIC( a, b, c)\
Impl_allocsrfNOPARAMS(a, b, c)

#define Impl_allocsrfAZIMUTHAL( a, b, c)\
Impl_allocsrfNOPARAMS(a, b, c)

#define Impl_allocsrfPOLAR( a, b, c)\
Impl_allocsrfNOPARAMS(a, b, c)

#define Impl_allocsrfCELESTIOMAGNETIC( a, b, c)\
Impl_allocsrfNOPARAMS(a, b, c)

#define Impl_allocsrfEQUATORIAL_INERTIAL( a, b, c)\
Impl_allocsrfNOPARAMS(a, b, c)

#define Impl_allocsrfSOLAR_ECLIPTIC( a, b, c)\
Impl_allocsrfNOPARAMS(a, b, c)

#define Impl_allocsrfSOLAR_EQUATORIAL( a, b, c)\
Impl_allocsrfNOPARAMS(a, b, c)

#define Impl_allocsrfSOLAR_MAGNETIC_ECLIPTIC( a, b, c)\
Impl_allocsrfNOPARAMS(a, b, c)

#define Impl_allocsrfSOLAR_MAGNETIC_DIPOLE( a, b, c)\
Impl_allocsrfNOPARAMS(a, b, c)

#define Impl_allocsrfHELIO_ARIES_ECLIPTIC( a, b, c)\
Impl_allocsrfNOPARAMS(a, b, c)

#define Impl_allocsrfHELIO_EARTH_ECLIPTIC( a, b, c)\
Impl_allocsrfNOPARAMS(a, b, c)


#define Impl_allocsrfHELIO_EARTH_EQUATORIAL( a, b, c)\
Impl_allocsrfNOPARAMS(a, b, c)

#endif
