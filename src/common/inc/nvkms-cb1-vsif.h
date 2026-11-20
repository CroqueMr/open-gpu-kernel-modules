/* SPDX-License-Identifier: MIT */
#ifndef NVKMS_CB1_VSIF_H
#define NVKMS_CB1_VSIF_H
#include "nvtypes.h"

/* Kernel-private metadata; the R580 userspace ioctl layouts stay unchanged. */
struct NvKmsCb1Vsif {
    NvU32 payloadSize;
    NvU8 payload[27];
    NvBool disableDithering;
};

static inline NvBool nvCb1VsifValid(const struct NvKmsCb1Vsif *p)
{
    return p && (p->payloadSize == 0 ||
                 (p->payloadSize >= 3 && p->payloadSize <= 27));
}
#endif
