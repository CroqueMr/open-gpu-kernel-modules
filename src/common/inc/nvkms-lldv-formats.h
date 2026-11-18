/* SPDX-License-Identifier: MIT */
#ifndef NVKMS_LLDV_FORMATS_H
#define NVKMS_LLDV_FORMATS_H

/* CB1_LLDV_FORMAT is a wire ABI shared with userspace. Keep old values. */
enum {
    NV_LLDV_422_12 = 3,
    NV_LLDV_RGB_12 = 4,
    NV_LLDV_444_10 = 5,
    NV_LLDV_444_12 = 6,
    NV_LLDV_422_10 = 7,
    NV_LLDV_RGB_10 = 8,
    NV_LLDV_LAST = NV_LLDV_RGB_10
};

static inline unsigned nvLldvNativeBpc(unsigned format)
{
    switch (format) {
    case NV_LLDV_422_12: case NV_LLDV_RGB_12: case NV_LLDV_444_12: return 12;
    case NV_LLDV_422_10: case NV_LLDV_RGB_10: case NV_LLDV_444_10: return 10;
    default: return 0;
    }
}
static inline unsigned nvLldvRgb(unsigned format)
{
    return format == NV_LLDV_RGB_10 || format == NV_LLDV_RGB_12;
}
static inline unsigned nvLldv444(unsigned format)
{
    return format == NV_LLDV_444_10 || format == NV_LLDV_444_12;
}
#endif
