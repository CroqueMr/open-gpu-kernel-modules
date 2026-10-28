/* SPDX-License-Identifier: MIT */
#ifndef NVKMS_KAPI_VSIF_H
#define NVKMS_KAPI_VSIF_H
#include "nvkms-api.h"
#include "nvkms-cb1-vsif.h"

/* Accepted only from the in-kernel KAPI client, under the native NVKMS lock. */
#define NVKMS_IOCTL_KAPI_SET_MODE_VSIF 0x10000U
struct NvKmsKapiSetModeVsif {
    struct NvKmsSetModeParams mode;
    struct NvKmsCb1Vsif vsif[NVKMS_MAX_SUBDEVICES][NVKMS_MAX_HEADS_PER_DISP];
};
#endif
