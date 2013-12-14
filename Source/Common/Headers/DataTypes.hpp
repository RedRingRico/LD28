#ifndef __LD_DATATYPES_HPP__
#define __LD_DATATYPES_HPP__

#if LD_BITSIZE_32
#define LD_32BIT
#elif LD_BITSIZE_64
#define LD_64BIT
#else
#error Unknown bit size for processor
#endif // LD_BITSIZE

#ifdef LD_ARCH_X86
#define LD_LITTLE_ENDIAN
#else
#error Unknown architecture
#endif // LD_ARCH_X86

#include <Compiler.hpp>

#define ldSafeDelete( Pointer )\
	{ if( Pointer )\
		{ delete Pointer; Pointer = LD_NULL; } }

typedef LD_UINT32	LD_BOOL;

typedef float	LD_FLOAT32;
typedef double	LD_FLOAT64;

typedef size_t	LD_MEMSIZE;

const LD_BOOL LD_TRUE	= 1;
const LD_BOOL LD_FALSE	= 0;

const LD_UINT32	LD_OK	= 0x00000000;
const LD_UINT32 LD_FAIL = 0xFFFFFFFF;

const LD_UINT32 LD_MAXPATH	= 256;

#endif // __LD_DATATYPES_HPP__

