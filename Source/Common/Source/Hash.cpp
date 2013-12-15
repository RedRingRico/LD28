#include <Hash.hpp>
#include <cstring>
#include <ctype.h>

namespace LD
{
	LD_UINT32 HashString( const LD_CHAR8 *p_pString )
	{
		if( p_pString == LD_NULL )
		{
			return LD_FAIL;
		}

		const LD_UINT32 Base = 65521;
		const LD_UINT32 Max = 5552;

		LD_UINT32 Str1 = 0, Str2 = 0;

#define DO1( Buff, i ){ Str1 += tolower( Buff[ i ] ); Str2 += Str1; }
#define DO2( Buff, i ){ DO1( Buff, i ); DO1( Buff, i+1 ); }
#define DO4( Buff, i ){ DO2( Buff, i ); DO2( Buff, i+2 ); }
#define DO8( Buff, i ){ DO4( Buff, i ); DO4( Buff, i+4 ); }
#define DO16( Buff ){ DO8( Buff, 0 ); DO8( Buff, 0 ); }
		
		for( LD_MEMSIZE i = strlen( p_pString ); i > 0; )
		{
			LD_UINT32 K = i < Max ? i : Max;

			i -= K;

			while( K >= 16 )
			{
				DO16( p_pString );
				p_pString += 16;
				K -= 16;
			}

			if( K != 0 )
			{
				do
				{
					Str1 += *p_pString++;
					Str2 += Str1;
				}while( --K );
			}

			Str1 %= Base;
			Str2 %= Base;
		}

		return ( ( Str2 << 16 ) | Str1 );
#undef DO1
#undef DO2
#undef DO4
#undef DO8
#undef DO16
	}
}

