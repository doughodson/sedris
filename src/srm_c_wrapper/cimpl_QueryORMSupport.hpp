
#ifndef CIMPL_QUERYORMSUPPORT_HPP_INCLUDED
#define CIMPL_QUERYORMSUPPORT_HPP_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "srm.h"

#ifdef _WIN32
#pragma warning(disable: 4786)
#endif

SRM_Status_Code cimpl_SRM_QueryORMSupport
(
    SRM_ORM_Code  orm_code,
    SRM_RT_Code   rt_code,
    SRM_Boolean  *supported  /* OUT */
);

#ifdef __cplusplus
}
#endif
#endif
