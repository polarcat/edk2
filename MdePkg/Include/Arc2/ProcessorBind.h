/** @file
  Processor and compiler specific defines and types for ARC

  Copyright (c) 2023 Basemark Oy

  Author: Aliaksei Katovich @ basemark.com

  Released under the BSD-2-Clause License
**/

#ifndef PROCESSOR_BIND_H_
#define PROCESSOR_BIND_H_

static inline void CpuPause(void)
{
  asm("nop_s\nsleep");
}

//
// The processor type is defined via compiler flag, e.g. -DMDE_CPU_ARC2
//

#define EFIAPI

//
// Make sure we are using the correct packing rules per EFI specification
//
#ifndef __GNUC__
#pragma pack()
#endif

typedef unsigned long long UINT64 __attribute__((aligned(8)));
typedef long long INT64 __attribute__((aligned(8)));

typedef unsigned int UINT32;
typedef int INT32;

typedef unsigned short UINT16;
typedef short INT16;
typedef unsigned short CHAR16;

typedef unsigned char BOOLEAN;
typedef unsigned char UINT8;
typedef char CHAR8;
typedef char INT8;

//
// Unsigned value of native width (4 bytes on supported 32-bit processor instructions,
// 8 bytes on supported 64-bit processor instructions).
//

#if defined(MDE_CPU_ARC2)
typedef UINT32 UINTN;
#else
typedef UINT64 UINTN;
#endif

//
// Signed value of native width (4 bytes on supported 32-bit processor instructions,
// 8 bytes on supported 64-bit processor instructions).
//
#if defined(MDE_CPU_ARC2)
typedef INT32 INTN;
#else
typedef INT64 INTN;
#endif

//
// Processor specific defines
//

//
// A value of native width with the highest bit set.
//
#define MAX_BIT 0x80000000
//
// A value of native width with the two highest bits set.
//
#define MAX_2_BITS 0xc0000000

//
// Maximum legal Arc address
// NOTE: 0xf0000000 and above may be reserved for peripherals in ARC HS4xD
//
#define MAX_ADDRESS 0xefffffff

//
// Maximum usable address at boot time (48 bits using 4KB pages).
//
#define MAX_ALLOC_ADDRESS MAX_ADDRESS

//
// Maximum legal Arc INTN and UINTN values.
//
#define MAX_INTN ((INTN) 0x7fffffff)
#define MAX_UINTN ((UINTN) 0xffffffff)

//
// Page allocation granularity for Arc
//
#define DEFAULT_PAGE_ALLOCATION_GRANULARITY 0x2000
#define RUNTIME_PAGE_ALLOCATION_GRANULARITY 0x2000

#if defined (__GNUC__)
//
// For GNU assembly code, .global or .globl can declare global symbols.
// Define this macro to unify the usage.
//
#define ASM_GLOBAL .globl
#endif

//
// The stack alignment required for Arc
//
#define CPU_STACK_ALIGNMENT sizeof(UINTN)

/**
  Return the pointer to the first instruction of a function given a function pointer.
  On LOONGARCH CPU architectures, these two pointer values are the same,
  so the implementation of this macro is very simple.

  @param FunctionPointer A pointer to a function.

  @return The pointer to the first instruction of a function given a function pointer.

**/
#define FUNCTION_ENTRY_POINT(FunctionPointer) (VOID *)(UINTN)(FunctionPointer)

typedef struct {
  UINT32    R13;
  UINT32    R14;
  UINT32    R15;
  UINT32    R16;
  UINT32    R17;
  UINT32    R18;
  UINT32    R19;
  UINT32    R20;
  UINT32    R21;
  UINT32    R22;
  UINT32    R23;
  UINT32    R24;
  UINT32    R25;
  UINT32    FP;
  UINT32    SP;
} BASE_LIBRARY_JUMP_BUFFER;

#define BASE_LIBRARY_JUMP_BUFFER_ALIGNMENT  4

#ifndef __USER_LABEL_PREFIX__
#define __USER_LABEL_PREFIX__
#endif

#endif
