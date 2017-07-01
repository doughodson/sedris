
#include <math.h>
#include <signal.h>

#include "../support/srm_validcoord.h"

#include "impl_private.h"
#include "impl_alloc.h"
#include "impl_change.h"
#include "impl_srf_params.h"
#include "impl_vos.h"
#include "impl_generated.h"

Impl_Status Impl_releasePrivateData(Impl_Private_Data* pdat)
{
    static const Impl_Private_Data pdat_blank={0,0,0};
    Impl_Status status = IMPL_VALID;

    if((pdat->e_constants)!= (&e_constants_invalid))
        free(pdat->e_constants);
    else
        status=IMPL_MEMALLOC;

    if(pdat->impl_SRFP_struct!=NULL)
        free(pdat->impl_SRFP_struct);
    else
        status|=IMPL_MEMALLOC;

    if (pdat->impl_SRF_data!=NULL &&
        pdat->impl_SRF_data!= Impl_allocsrf_specific_data[0](0))
        free(pdat->impl_SRF_data);
    else
        status|=IMPL_MEMALLOC;

    *pdat=pdat_blank;

    return status;
}

Impl_Status Impl_releaseVMprogram(std::vector<CCSRFOp>* vmprogram)
{
    Impl_Status status=IMPL_VALID;

    std::vector<CCSRFOp>::iterator cleanup_op;
    cleanup_op=vmprogram->begin();
    while (cleanup_op!=vmprogram->end())
    {
        status|=Impl_releasePrivateData(&(cleanup_op->ipd[0]));
        status|=Impl_releasePrivateData(&(cleanup_op->ipd[1]));
        cleanup_op->ops.dealloc(cleanup_op->conversion_specific_constants);
        ++cleanup_op;
    }
    delete(vmprogram);
    vmprogram=NULL;
    return status;
}
