#ifndef __LD_COMPILER_GCC_HPP__
#define __LD_COMPILER_GCC_HPP__

#include <stdint.h>
#include <cstddef>

#if LD_PLATFORM_LINUX
#include <linux/types.h>
#endif // LD_PLATFORM_LINUX

#define LD_GCCVER ( __GNUC__ * 10000 + __GNUC_MINOR__ * 100 + \
	__GNUC_PATCHLEVEL__ )

typedef char			LD_CHAR8;
typedef unsigned char	LD_UCHAR8;
typedef signed char		LD_SCHAR8;
typedef LD_UCHAR8		LD_UINT8;
typedef LD_SCHAR8		LD_SINT8;
typedef unsigned short	LD_UINT16;
typedef signed short	LD_SINT16;
typedef unsigned int	LD_UINT32;
typedef signed int		LD_SINT32;
typedef uint64_t		LD_UINT64;
typedef int64_t			LD_SINT64;

#if LD_GCCVER >= 40600
#define LD_NULL nullptr
#define LD_CPPVER_11
#else
#define LD_NULL 0
#define LD_CPPVER_98
#endif // LD_GCCVER

#endif // __LD_COMPILER_GCC_HPP__

