/* SPDX-License-Identifier: MIT */
#ifndef NVKMS_KAPI_VSIF_H
#define NVKMS_KAPI_VSIF_H
#include "nvkms-api.h"
#include "nvkms-cb1-vsif.h"
#include "nvkms-cb1-hdr10plus.h"

/* Accepted only from the in-kernel KAPI client, under the native NVKMS lock. */
#define NVKMS_IOCTL_KAPI_SET_MODE_VSIF 0x10000U
struct NvKmsKapiSetModeVsif {
    struct NvKmsSetModeParams mode;
    struct NvKmsCb1Vsif vsif[NVKMS_MAX_SUBDEVICES][NVKMS_MAX_HEADS_PER_DISP];
    struct NvKmsCb1Hdr10plus hdr10plus[NVKMS_MAX_SUBDEVICES][NVKMS_MAX_HEADS_PER_DISP];
};
#define NVKMS_IOCTL_KAPI_FLIP_HDR10PLUS 0x10001U
#define NVKMS_IOCTL_KAPI_HDR10PLUS_STATUS 0x10002U
struct NvKmsKapiFlipHdr10plus {
    struct NvKmsFlipParams flip;
    struct NvKmsCb1Hdr10plus hdr10plus[NVKMS_MAX_SUBDEVICES][NVKMS_MAX_HEADS_PER_DISP];
};
struct NvKmsKapiHdr10plusStatus {
    NvU32 deviceHandle, disp, head, rmId, status;
    NvBool latchFault;
};
#endif
