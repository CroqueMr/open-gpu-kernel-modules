/* SPDX-License-Identifier: MIT */
#ifndef NVKMS_CB1_HDR_H
#define NVKMS_CB1_HDR_H
#include "nvtypes.h"

/* These are private kernel-client intents, not public NVKMS ioctl fields. */
struct NvKmsCb1Hdr {
    NvBool specified, enabled, deepColor;
    NvU8 packet[31];
};
enum {
    NV_CB1_HDR_SLOT_NONE,
    NV_CB1_HDR_SLOT_GENERIC,
    NV_CB1_HDR_SLOT_SHARED2,
    NV_CB1_HDR_SLOT_ADVANCED9
};
struct NvKmsCb1HdrRoute {
    NvBool hdmi, pq, bt2020, primary, receiver;
    NvBool async, threeD, customVsif, vendor, shared, ada, vrr, swAcr;
    NvU32 bpc, version;
};
struct NvKmsCb1HdrLedger {
    NvU32 status; /* 0 disabled, 1 commit-coupled active, 2 sticky fault */
    NvU32 slot, owner, uncertainSlot, uncertainOwner;
};
static inline NvBool nvCb1HdrPacketValid(const NvU8 *p)
{
    NvU32 sum = 0, anchors;
    if (!p || p[0] != 0x81 || p[1] != 1 || p[2] != 27 ||
        p[4] != 0x8b || p[5] != 0x84 || p[6] != 0x90 ||
        (p[7] >> 6) > 1 || (p[7] & 1) || (p[30] & 0x3f) ||
        !(p[30] & 0x40) ||
        ((p[7] >> 6) == 1 && p[11] > 100 && p[11] != 255)) return NV_FALSE;
    anchors = p[18] >> 4;
    if (anchors > 9) return NV_FALSE;
    for (NvU32 i = 1; i < anchors; i++)
        if (p[21+i] < p[20+i]) return NV_FALSE;
    for (NvU32 i = 21+anchors; i < 30; i++)
        if (p[i]) return NV_FALSE;
    for (NvU32 i = 0; i < 31; i++) sum += p[i];
    return (sum & 255) == 0;
}
static inline NvU32 nvCb1HdrSlot(const struct NvKmsCb1HdrRoute *r)
{
    if (r->shared) return NV_CB1_HDR_SLOT_ADVANCED9;
    if (r->ada) return NV_CB1_HDR_SLOT_SHARED2;
    return !r->vrr && !r->swAcr ? NV_CB1_HDR_SLOT_GENERIC : NV_CB1_HDR_SLOT_NONE;
}
static inline NvBool nvCb1HdrRouteValid(const struct NvKmsCb1HdrRoute *r,
                                       const NvU8 *packet)
{
    return r->hdmi && r->pq && r->bt2020 && r->primary && r->receiver &&
        r->bpc >= 10 && !r->async && !r->threeD && !r->customVsif &&
        (r->shared || !r->vendor) && nvCb1HdrSlot(r) &&
        nvCb1HdrPacketValid(packet) && (packet[7] >> 6) <= r->version;
}
static inline void nvCb1HdrResult(struct NvKmsCb1HdrLedger *l,
                                 NvU32 slot, NvU32 owner, NvBool success)
{
    if (!success) {
        l->status = 2;
        if (slot) {
            l->uncertainSlot = slot;
            l->uncertainOwner = owner;
        }
    } else if (slot == 0) {
        l->status = l->slot = l->owner = 0;
        l->uncertainSlot = l->uncertainOwner = 0;
    } else if (l->status != 2) {
        l->slot = slot;
        l->owner = owner;
        l->status = 1;
    }
}
#endif
