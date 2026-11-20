/* SPDX-License-Identifier: MIT */
#ifndef NVKMS_DV_VSIF_H
#define NVKMS_DV_VSIF_H
#include "nvtypes.h"

/* Legacy DV reserves a 24-byte HDMI-OUI payload. Ordinary HDMI/3D and
 * modern Dolby packets must never enter this timing rewrite. */
static inline NvBool nvDoviLegacy(const NvU8 *p, NvU32 size)
{
    NvU32 i;
    if (size != 24 || p[0] != 3 || p[1] != 12 || p[2] ||
        (p[3] != 0 && p[3] != 32) || p[4] > 3 ||
        ((p[3] == 0) != (p[4] == 0)))
        return NV_FALSE;
    for (i = 5; i < 24; i++)
        if (p[i])
            return NV_FALSE;
    return NV_TRUE;
}

static inline NvU8 nvDoviHdmiVic(NvU32 ceaVic, NvU32 hdmiVic)
{
    if (ceaVic >= 93 && ceaVic <= 95)
        return 96 - ceaVic;
    /* HDMI_EXT timings keep their VIC exclusively in the vendor control. */
    return ceaVic == 0 && hdmiVic >= 1 && hdmiVic <= 3 ? hdmiVic : 0;
}

static inline void nvDoviTiming(NvU8 *p, NvU32 size, NvU32 ceaVic, NvU32 hdmiVic)
{
    if (nvDoviLegacy(p, size)) {
        NvU8 vic = nvDoviHdmiVic(ceaVic, hdmiVic);
        p[3] = vic ? 32 : 0;
        p[4] = vic;
    }
}
#endif
