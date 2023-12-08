//-------------------------------------------------------------------------------------
// BC.h
//  
// Block-compression (BC) functionality
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkId=248926
//-------------------------------------------------------------------------------------

#pragma once


#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <float.h>
#include <ctype.h>
#include <sys/stat.h>
#include <wctype.h>
#include <locale.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#if defined(WIN32)
#include <Windows.h>
#endif

#include <algorithm>

#ifndef _Out_writes_
#define _Out_writes_(a)
#endif

#ifndef _In_reads_
#define _In_reads_(a)
#endif

#ifndef _Out_
#define _Out_
#endif

#ifndef _In_
#define _In_
#endif

#ifndef _Inout_
#define _Inout_
#endif

#ifndef _Out_opt_
#define _Out_opt_
#endif

#ifndef _In_range_
#define _In_range_(a,b)
#endif

#ifndef _Out_writes_all_
#define _Out_writes_all_(a)
#endif

#ifndef _Inout_updates_all_
#define _Inout_updates_all_(a)
#endif

#ifndef _Analysis_assume_
#define _Analysis_assume_(a)
#endif

#ifndef _Use_decl_annotations_
#define _Use_decl_annotations_
#endif

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(a)
#endif

#if !defined(WIN32)
#define OutputDebugStringA(a)
#endif


typedef uint16_t HALF;


struct XMVECTOR {
    union
    {
        float       vector4_f32[4];
        uint32_t    vector4_u32[4];
    };
};

struct XMVECTORF32 {
    union
    {
        float f[4];
        XMVECTOR v;
    };

    inline operator XMVECTOR() const {
        return v;
    }
};


struct XMVECTORU32
{
    union
    {
        uint32_t u[4];
        XMVECTOR v;
    };

    inline operator XMVECTOR() const {
        return v;
    }
};

struct XMU565
{
    union
    {
        struct
        {
            uint16_t x : 5;    // 0 to 31
            uint16_t y : 6;    // 0 to 63
            uint16_t z : 5;    // 0 to 31
        };
        uint16_t v;
    };
};

struct XMUBYTE4
{
    union
    {
        struct
        {
            uint8_t x;
            uint8_t y;
            uint8_t z;
            uint8_t w;
        };
        uint32_t v;
    };
};

struct XMHALF4
{
    union
    {
        struct
        {
            HALF x;
            HALF y;
            HALF z;
            HALF w;
        };
        uint64_t v;
    };
};


struct XMFLOAT4
{
    float x;
    float y;
    float z;
    float w;
};


struct XMFLOAT4A : public XMFLOAT4 {};

struct XMINT4
{
    int32_t x;
    int32_t y;
    int32_t z;
    int32_t w;
};



static const uint32_t XM_SELECT_0 = 0x00000000;
static const uint32_t XM_SELECT_1 = 0xFFFFFFFF;
static const XMVECTORF32 g_XMIdentityR3 = { { { 0.0f, 0.0f, 0.0f, 1.0f } } };
static const XMVECTORU32 g_XMSelect1110 = { { { XM_SELECT_1, XM_SELECT_1, XM_SELECT_1, XM_SELECT_0 } } };


inline static HALF XMConvertFloatToHalf(float aValue) {
    uint32_t Result{};

    union {
        float f;
        uint32_t i;
    } IValue;

    IValue.f = aValue;
    const uint32_t Sign = (IValue.i & 0x80000000U) >> 16U;
    IValue.i = IValue.i & 0x7FFFFFFFU;  // Hack off the sign

    if (IValue.i > 0x477FE000U) {
        // The number is too large to be represented as a half.  Saturate to
        // infinity.
        if (((IValue.i & 0x7F800000) == 0x7F800000) && ((IValue.i & 0x7FFFFF) != 0)) {
            Result = 0x7FFF;  // NAN
        } else {
            Result = 0x7C00U;  // INF
        }
    } else {
        if (IValue.i < 0x38800000U) {
            // The number is too small to be represented as a normalized half.
            // Convert it to a denormalized mValue.
            const uint32_t Shift = 113U - (IValue.i >> 23U);
            IValue.i = (0x800000U | (IValue.i & 0x7FFFFFU)) >> Shift;
        } else {
            // Rebias the exponent to represent the mValue as a normalized half.
            IValue.i += 0xC8000000U;
        }

        Result = ((IValue.i + 0x0FFFU + ((IValue.i >> 13U) & 1U)) >> 13U) & 0x7FFFU;
    }

    return (HALF)(Result | Sign);
}

inline static float XMConvertHalfToFloat(HALF aValue) {
    uint32_t Mantissa = aValue & 0x03FF;
    uint32_t Exponent = aValue & 0x7C00;
    // INF/NAN
    if (Exponent == 0x7C00) {
        Exponent = 0x8f;
        // The mValue is normalized
    } else if (Exponent != 0) {
        Exponent = (aValue >> 10) & 0x1F;
        // The mValue is denormalized
    } else if (Mantissa != 0) {
        // Normalize the mValue in the resulting float
        Exponent = 1;

        do {
            Exponent--;
            Mantissa <<= 1;
        } while ((Mantissa & 0x0400) == 0);

        Mantissa &= 0x03FF;
    } else  // The mValue is zero
    {
        Exponent = (uint32_t)-112;
    }

    const uint32_t Result = ((aValue & 0x8000) << 16) |  // Sign
        ((Exponent + 112) << 23) |          // Exponent
        (Mantissa << 13);                   // Mantissa

    union {
        float f;
        uint32_t i;
    } IValue;
    IValue.i = Result;
    return IValue.f;
}


inline XMVECTOR XMLoadU565(const XMU565* aSrc) {
    XMVECTOR Result;
    Result.vector4_f32[0] = aSrc->x;
    Result.vector4_f32[1] = aSrc->y;
    Result.vector4_f32[2] = aSrc->z;
    Result.vector4_f32[3] = 0;
    return Result;
}

inline XMVECTOR XMLoadUByte4(const XMUBYTE4* aSrc) {
    XMVECTOR Result;
    Result.vector4_f32[0] = aSrc->x;
    Result.vector4_f32[1] = aSrc->y;
    Result.vector4_f32[2] = aSrc->z;
    Result.vector4_f32[3] = aSrc->w;
    return Result;
}

inline XMVECTOR XMLoadSInt4(const XMINT4* aSrc) {
    XMVECTOR Result;
    Result.vector4_f32[0] = aSrc->x;
    Result.vector4_f32[1] = aSrc->y;
    Result.vector4_f32[2] = aSrc->z;
    Result.vector4_f32[3] = aSrc->w;
    return Result;
}

inline XMVECTOR XMLoadFloat4(const XMFLOAT4* aSrc) {
    XMVECTOR Result;
    Result.vector4_f32[0] = aSrc->x;
    Result.vector4_f32[1] = aSrc->y;
    Result.vector4_f32[2] = aSrc->z;
    Result.vector4_f32[3] = aSrc->w;
    return Result;
}



inline XMVECTOR XMVectorZero() {
    return XMVECTOR{ {0, 0, 0, 0} };
}

inline XMVECTOR XMVectorMultiply(const XMVECTOR& a, const XMVECTOR& b) {
    return XMVECTOR{ {a.vector4_f32[0] * b.vector4_f32[0],
                      a.vector4_f32[1] * b.vector4_f32[1],
                      a.vector4_f32[2] * b.vector4_f32[2],
                      a.vector4_f32[3] * b.vector4_f32[3]} };
}

inline XMVECTOR XMVectorSubtract(const XMVECTOR& a, const XMVECTOR& b) {
    return XMVECTOR{ {a.vector4_f32[0] - b.vector4_f32[0],
                      a.vector4_f32[1] - b.vector4_f32[1],
                      a.vector4_f32[2] - b.vector4_f32[2],
                      a.vector4_f32[3] - b.vector4_f32[3]} };
}

inline XMVECTOR XMVector3Dot(const XMVECTOR& a, const XMVECTOR& b) {
    float dot =
        (a.vector4_f32[0] * b.vector4_f32[0])
        + (a.vector4_f32[1] * b.vector4_f32[1])
        + (a.vector4_f32[2] * b.vector4_f32[2]);

    return XMVECTOR{ {dot, dot, dot, dot} };
}

inline XMVECTOR XMVector4Dot(const XMVECTOR& a, const XMVECTOR& b) {
    float dot =
        (a.vector4_f32[0] * b.vector4_f32[0])
        + (a.vector4_f32[1] * b.vector4_f32[1])
        + (a.vector4_f32[2] * b.vector4_f32[2])
        + (a.vector4_f32[3] * b.vector4_f32[3]);

    return XMVECTOR{ {dot, dot, dot, dot} };
}

template<uint32_t SwizzleX, uint32_t SwizzleY, uint32_t SwizzleZ, uint32_t SwizzleW>
inline XMVECTOR XMVectorSwizzle(const XMVECTOR& a)
{
    static_assert(SwizzleX <= 3, "SwizzleX template parameter out of range");
    static_assert(SwizzleY <= 3, "SwizzleY template parameter out of range");
    static_assert(SwizzleZ <= 3, "SwizzleZ template parameter out of range");
    static_assert(SwizzleW <= 3, "SwizzleW template parameter out of range");

    return XMVECTOR{ {  a.vector4_f32[SwizzleX],
                        a.vector4_f32[SwizzleY],
                        a.vector4_f32[SwizzleZ],
                        a.vector4_f32[SwizzleW]} };
}


inline XMVECTOR XMVectorSelect(const XMVECTOR& V1, const XMVECTOR& V2, const XMVECTORU32& Control) {
    XMVECTOR Result;

    Result.vector4_u32[0] = (V1.vector4_u32[0] & ~Control.u[0]) | (V2.vector4_u32[0] & Control.u[0]);
    Result.vector4_u32[1] = (V1.vector4_u32[1] & ~Control.u[1]) | (V2.vector4_u32[1] & Control.u[1]);
    Result.vector4_u32[2] = (V1.vector4_u32[2] & ~Control.u[2]) | (V2.vector4_u32[2] & Control.u[2]);
    Result.vector4_u32[3] = (V1.vector4_u32[3] & ~Control.u[3]) | (V2.vector4_u32[3] & Control.u[3]);

    return Result;
}

inline XMVECTOR XMVectorLerp(const XMVECTOR& v1, const XMVECTOR& v2, float t) {
    return XMVECTOR{ {
        v1.vector4_f32[0] + t * (v2.vector4_f32[0] - v1.vector4_f32[0]),
        v1.vector4_f32[1] + t * (v2.vector4_f32[1] - v1.vector4_f32[1]),
        v1.vector4_f32[2] + t * (v2.vector4_f32[2] - v1.vector4_f32[2]),
        v1.vector4_f32[3] + t * (v2.vector4_f32[3] - v1.vector4_f32[3])
    } };
}

inline void XMStoreFloat4A(XMFLOAT4A* pDestination, const XMVECTOR& V) {
    pDestination->x = V.vector4_f32[0];
    pDestination->y = V.vector4_f32[1];
    pDestination->z = V.vector4_f32[2];
    pDestination->w = V.vector4_f32[3];
}

inline void XMStoreFloat4(XMFLOAT4* pDestination, const XMVECTOR& V) {
    pDestination->x = V.vector4_f32[0];
    pDestination->y = V.vector4_f32[1];
    pDestination->z = V.vector4_f32[2];
    pDestination->w = V.vector4_f32[3];
}

inline void XMStoreHalf4(_Out_ XMHALF4* pDestination, _In_ const XMVECTOR& V) {
    pDestination->x = XMConvertFloatToHalf(V.vector4_f32[0]);
    pDestination->y = XMConvertFloatToHalf(V.vector4_f32[1]);
    pDestination->z = XMConvertFloatToHalf(V.vector4_f32[2]);
    pDestination->w = XMConvertFloatToHalf(V.vector4_f32[3]);
}


inline XMVECTOR XMVectorSetW(XMVECTOR& V, float W) {
    XMVECTOR Result;

    Result.vector4_f32[0] = V.vector4_f32[0];
    Result.vector4_f32[1] = V.vector4_f32[1];
    Result.vector4_f32[2] = V.vector4_f32[2];
    Result.vector4_f32[3] = W;

    return Result;
}

inline XMVECTOR XMVectorSet(float X, float Y, float Z, float W) {
    XMVECTOR Result;

    Result.vector4_f32[0] = X;
    Result.vector4_f32[1] = Y;
    Result.vector4_f32[2] = Z;
    Result.vector4_f32[3] = W;

    return Result;
}

inline float XMVectorGetX(const XMVECTOR& V) {
    return V.vector4_f32[0];
}
