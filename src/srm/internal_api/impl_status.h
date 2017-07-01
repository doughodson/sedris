
#ifndef _IMPL_STATUS
#define _IMPL_STATUS

#include "srm_stds.h"

typedef SRM_Integer_Unsigned Impl_Status;

#define  IMPL_VALID 0x1   // maps to SRM_STATCOD_SUCCESS
/*!< The tgt object of conversion or solitary org object is valid   */
#define  IMPL_EXTENDED 0x2   // maps to Valid_Region = Extended
/*!< The tgt object of conversion or solitary org object is extended*/
#define  IMPL_INVALID 0x4   // maps to SRM_STATCOD_INVALID_INPUT
/*!< The tgt object of conversion or solitary org object is invalid */
#define  IMPL_UNIMPLEM 0x8  // maps to SRM_STATCOD_NOT_IMPLEMENTED
/*!< The requested operation is unimplemented in this software version   */
#define  IMPL_INACTBLE 0x10  // maps to SRM_STATCOD_INACTIONABLE
/*!< An unspecified internal failure has occurred                   */
#define  IMPL_MEMALLOC 0x20  // maps to SRM_STATCOD_MEMORY_ALLOCATION_ERROR
/*!< Insufficient memory was available to perform the operation     */
#define  IMPL_SRFSRC 0x40   // maps to SRM_STATCOD_INVALID_SOURCE_SRF
/*!< The source SRF has a parameter which is inconsistent with the defintion*/
#define  IMPL_SRFTGT 0x80   // maps to SRM_STATCOD_INVALID_SRF
/*!< The target SRF has a parameter which is inconsistent with the defintion*/
#define  IMPL_CRDORG 0x100  // maps to SRM_STATCOD_INVALID_SOURCE_COORDINATE
/*!< The origin coordinate is bad */
#define  IMPL_CRDDST 0x200  // maps to SRM_STATCOD_INVALID_TARGET_COORDINATE
/*!< The destination coordinate is bad*/
#define  IMPL_ILLEGL 0x400  // maps to SRM_STATCOD_OPERATION_UNSUPPORTED
/*!< A semantically impossible operation has been requested.*/
#define  IMPL_BADORM 0x800  // maps to SRM_STATCOD_INVALID_CODE
/*!< The ORM passed doesn't make sense for the operation*/
#define  IMPL_DEFINED 0x1000 // maps to Valid_Region = Defined
/*!< The value is defined but neither valid, extended nor invalid*/
#define  IMPL_OBJSRC 0x2000 // maps to SRM_STATCOD_INVALID_SOURCE_DIRECTION
                            //         SRM_STATCOD_INVALID_TARGET_DIRECTION
/*!<malformed source coordinate, vector, direction*/
#define  IMPL_FPE 0x4000   // maps to SRM_STATCOD_FLOATING_OVERFLOW
                           //         SRM_STATCOD_FLOATING_UNDERFLOW
/*!<Implementation detected floating point error*/


extern SRM_Integer_Unsigned IMPL_GOODSTAT;
extern SRM_Integer_Unsigned IMPL_BADSTAT;

#define SIMPLIFY_STATUS(status)		\
  do{							\
  if( !(status& IMPL_BADSTAT) )		\
  {							\
      if(status&IMPL_EXTENDED)		\
          status=IMPL_EXTENDED;	    	\
      else if(status&IMPL_DEFINED)		\
          status=IMPL_DEFINED;		\
      else if(status&IMPL_VALID)		\
          status=IMPL_VALID;			\
  }							\
  else						\
  {							\
      if(status&IMPL_FPE)			\
          status=IMPL_FPE;			\
      else if(status&IMPL_ILLEGL)		\
          status=IMPL_ILLEGL;			\
	else if(status&IMPL_INACTBLE)		\
          status=IMPL_INACTBLE;		\
	else if(status&IMPL_UNIMPLEM)		\
	    status=IMPL_UNIMPLEM;		\
	else if(status&IMPL_MEMALLOC)		\
	    status=IMPL_MEMALLOC;		\
      else if(status&IMPL_SRFSRC)		\
	    status=IMPL_SRFSRC;			\
	else if(status&IMPL_SRFTGT)		\
	    status=IMPL_SRFTGT;			\
	else if(status&IMPL_OBJSRC)		\
	    status=IMPL_OBJSRC;			\
	else if(status&IMPL_BADORM)		\
	    status=IMPL_BADORM;			\
	else if(status&IMPL_CRDORG)		\
	    status=IMPL_CRDORG;			\
	else if(status&IMPL_CRDDST)		\
	    status=IMPL_CRDDST;			\
	else if(status&IMPL_INVALID)		\
	    status=IMPL_INVALID;		\
    }							\
  } while(0);

#endif
