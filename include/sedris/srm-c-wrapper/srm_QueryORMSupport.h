
#ifndef __SRM_QUERYORMSUPPORT_H_INCLUDED__
#define __SRM_QUERYORMSUPPORT_H_INCLUDED__

#include "srm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Queries for the ORM/RT pair support by the implementation.
    @param orm_code in: the object reference model code
    @param rt_code in: the reference transformation code
    @param supported out: return true if the ORM/RT pair is supported by this implementation
    @returns a status code
*/
extern SRM_Status_Code
SRM_QueryORMSupport
(
    SRM_ORM_Code  orm_code,
    SRM_RT_Code   rt_code,
    SRM_Boolean  *supported /* OUT */
);

#ifdef __cplusplus
}
#endif
#endif
