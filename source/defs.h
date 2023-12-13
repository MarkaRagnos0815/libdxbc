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

#ifndef _Success_
#define _Success_(a)
#endif

#ifndef _In_reads_
#define _In_reads_(a)
#endif

#ifndef _In_reads_opt_
#define _In_reads_opt_(a)
#endif

#ifndef _In_reads_bytes_
#define _In_reads_bytes_(a)
#endif

#ifndef _In_
#define _In_
#endif

#ifndef _In_opt_
#define _In_opt_
#endif

#ifndef _In_z_
#define _In_z_
#endif

#ifndef _In_range_
#define _In_range_(a, b)
#endif

#ifndef _Out_
#define _Out_
#endif

#ifndef _Out_opt_
#define _Out_opt_
#endif

#ifndef _Out_writes_
#define _Out_writes_(a)
#endif

#ifndef _Out_writes_all_
#define _Out_writes_all_(a)
#endif

#ifndef _Out_writes_opt_
#define _Out_writes_opt_(a)
#endif

#ifndef _Out_writes_bytes_
#define _Out_writes_bytes_(a)
#endif

#ifndef _Inout_
#define _Inout_
#endif

#ifndef _Inout_updates_all_
#define _Inout_updates_all_(a)
#endif

#ifndef _Inout_updates_bytes_all_
#define _Inout_updates_bytes_all_(a)
#endif

#ifndef _Inout_updates_all_opt_
#define _Inout_updates_all_opt_(a)
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
#define S_OK 0
#define S_FALSE 1
#define E_OUTOFMEMORY -1
#define E_UNEXPECTED -2
#define E_INVALIDARG -3
#define E_FAIL -4
#define E_POINTER -5
#define __cdecl

typedef uint32_t HRESULT;

#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)
#define FAILED(hr) (((HRESULT)(hr)) < 0)

#endif

typedef uint16_t HALF;
