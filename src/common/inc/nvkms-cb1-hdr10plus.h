/* SPDX-License-Identifier: MIT */
#ifndef NVKMS_CB1_HDR10PLUS_H
#define NVKMS_CB1_HDR10PLUS_H
#include "nvtypes.h"

/* Private kernel-client intent. Not part of the proprietary ioctl ABI. */
struct NvKmsCb1Hdr10plus {
    NvBool specified;
    NvBool enabled;
    NvBool strictDeepOutput;
    NvU8 packet[31];
};

static inline NvBool nvCb1NeedsDeepRoute(const struct NvKmsCb1Hdr10plus *intent)
{
    return intent->specified && (intent->enabled || intent->strictDeepOutput);
}

struct NvKmsCb1Hdr10plusOwner {
    NvU32 rmId;
    NvU32 status; /* 0 disabled, 1 commit-coupled, 2 fault */
    NvBool occupied;
};
#endif
