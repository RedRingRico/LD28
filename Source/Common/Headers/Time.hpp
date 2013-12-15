#ifndef __LD_TIME_HPP__
#define __LD_TIME_HPP__

#include <DataTypes.hpp>

namespace LD
{
	class Time
	{
	public:
		Time( );
		~Time( );

		LD_BOOL StartTimer( );

		LD_UINT64 GetTimeInSeconds( );

		LD_UINT64 GetTimeInMilliseconds( );

		LD_UINT64 GetTimeInMicroseconds( );

	private:
		LD_UINT64 m_StartTime;
		LD_UINT64 m_SecondsFrequency;
		LD_UINT64 m_MillisecondsFrequency;
		LD_FLOAT64 m_MicrosecondsFrequency;
	};
}

#endif

