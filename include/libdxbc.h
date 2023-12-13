#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

namespace DxTex {

enum TEX_COMPRESS_FLAGS {
    TEX_COMPRESS_DEFAULT = 0,

    TEX_COMPRESS_RGB_DITHER = 0x10000,
    // Enables dithering RGB colors for BC1-3 compression

    TEX_COMPRESS_A_DITHER = 0x20000,
    // Enables dithering alpha for BC1-3 compression

    TEX_COMPRESS_DITHER = 0x30000,
    // Enables both RGB and alpha dithering for BC1-3 compression

    TEX_COMPRESS_UNIFORM = 0x40000,
    // Uniform color weighting for BC1-3 compression; by default uses perceptual weighting

    TEX_COMPRESS_BC7_USE_3SUBSETS = 0x80000,
    // Enables exhaustive search for BC7 compress for mode 0 and 2; by default skips trying these modes

    TEX_COMPRESS_BC7_QUICK = 0x100000,
    // Minimal modes (usually mode 6) for BC7 compression

    TEX_COMPRESS_SRGB_IN = 0x1000000,
    TEX_COMPRESS_SRGB_OUT = 0x2000000,
    TEX_COMPRESS_SRGB = (TEX_COMPRESS_SRGB_IN | TEX_COMPRESS_SRGB_OUT),
    // if the input format type is IsSRGB(), then SRGB_IN is on by default
    // if the output format type is IsSRGB(), then SRGB_OUT is on by default

    TEX_COMPRESS_PARALLEL = 0x10000000,
    // Compress is free to use multithreading to improve performance (by default it does not use multithreading)
};

struct ColorVec {
    float r;
    float g;
    float b;
    float a;
};

extern "C" {
typedef void (*BC_DECODE)(ColorVec* pColor, const uint8_t* pBC);
typedef void (*BC_ENCODE)(uint8_t* pDXT, const ColorVec* pColor, uint32_t flags);

void BcDecodeBC1(ColorVec* pColor, const uint8_t* pBC);
void BcDecodeBC2(ColorVec* pColor, const uint8_t* pBC);
void BcDecodeBC3(ColorVec* pColor, const uint8_t* pBC);
void BcDecodeBC4U(ColorVec* pColor, const uint8_t* pBC);
void BcDecodeBC4S(ColorVec* pColor, const uint8_t* pBC);
void BcDecodeBC5U(ColorVec* pColor, const uint8_t* pBC);
void BcDecodeBC5S(ColorVec* pColor, const uint8_t* pBC);
void BcDecodeBC6HU(ColorVec* pColor, const uint8_t* pBC);
void BcDecodeBC6HS(ColorVec* pColor, const uint8_t* pBC);
void BcDecodeBC7(ColorVec* pColor, const uint8_t* pBC);

void BcEncodeBC1(uint8_t* pBC, const ColorVec* pColor, float threshold, uint32_t flags);
// BC1 requires one additional parameter, so it doesn't match signature of BC_ENCODE above

void BcEncodeBC2(uint8_t* pBC, const ColorVec* pColor, uint32_t flags);
void BcEncodeBC3(uint8_t* pBC, const ColorVec* pColor, uint32_t flags);
void BcEncodeBC4U(uint8_t* pBC, const ColorVec* pColor, uint32_t flags);
void BcEncodeBC4S(uint8_t* pBC, const ColorVec* pColor, uint32_t flags);
void BcEncodeBC5U(uint8_t* pBC, const ColorVec* pColor, uint32_t flags);
void BcEncodeBC5S(uint8_t* pBC, const ColorVec* pColor, uint32_t flags);
void BcEncodeBC6HU(uint8_t* pBC, const ColorVec* pColor, uint32_t flags);
void BcEncodeBC6HS(uint8_t* pBC, const ColorVec* pColor, uint32_t flags);
void BcEncodeBC7(uint8_t* pBC, const ColorVec* pColor, uint32_t flags);
}
}  // namespace DxTex