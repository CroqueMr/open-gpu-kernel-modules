/* SPDX-License-Identifier: MIT */
#ifndef NVKMS_KAPI_CB1_H
#define NVKMS_KAPI_CB1_H
#include "nvkms-api.h"
#include "nvkms-cb1-hdr.h"
#define NVKMS_IOCTL_KAPI_CB1_HDR 0x10000U
#define NVKMS_IOCTL_KAPI_CB1_HDR_FAULT 0x10001U
struct NvKmsCb1FaultParams {
    NvKmsDeviceHandle device;
    NvKmsDispHandle disp;
    NVDpyId dpy;
    NvU32 head;
};
#define NVKMS_IOCTL_KAPI_NATIVE_LLDV_ACTIVE 0x10002U
struct NvKmsNativeLldvQueryParams {
    struct NvKmsCb1FaultParams display;
    NvU32 active;
    NvU32 formats;
};
enum {NV_CB1_SET_MODE, NV_CB1_FLIP, NV_CB1_QUERY};
struct NvKmsCb1KapiParams {
    union {
        struct NvKmsSetModeParams mode;
        struct NvKmsFlipParams flip;
    } u;
    NvU32 operation;
    struct NvKmsCb1Hdr hdr[NVKMS_MAX_SUBDEVICES][NVKMS_MAX_HEADS_PER_DISP];
    struct {
        NvKmsDeviceHandle device;
        NvKmsDispHandle disp;
        NVDpyId dpy;
        NvU32 head, status, potential;
    } query;
};
#endif
