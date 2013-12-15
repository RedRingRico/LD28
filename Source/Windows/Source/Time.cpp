#include <Time.hpp>
#include <windows.h>
#include <SDL2/SDL.h>
namespace LD
{
	Time::Time( ) :
		m_StartTime( 0ULL ),
		m_SecondsFrequency( 0ULL ),
		m_MillisecondsFrequency( 0ULL ),
		m_MicrosecondsFrequency( 0.0d )
	{
	}

	Time::~Time( )
	{
	}

	LD_BOOL Time::StartTimer( )
	{
		LD_UINT64 Frequency = 0ULL;

		QueryPerformanceCounter( ( LARGE_INTEGER * )&m_StartTime );
		QueryPerformanceFrequency( ( LARGE_INTEGER * )&Frequency );

		m_SecondsFrequency = Frequency;
		m_MillisecondsFrequency = Frequency / 1000ULL;
		m_MicrosecondsFrequency = LD_FLOAT64( Frequency / 1000000.0d );


		SDL_Log( "Seconds freq.: %llu\n", m_SecondsFrequency );
		SDL_Log( "Millisec: %llu\n", m_MillisecondsFrequency );
		SDL_Log( "Micro: %llu\n", m_MicrosecondsFrequency );

		LD_FLOAT64 Microseconds = LD_FLOAT64( m_SecondsFrequency / 1000000.0d );
		SDL_Log( "Micro (F): %lf\n", Microseconds );

		return LD_TRUE;
	}

	LD_UINT64 Time::GetTimeInSeconds( )
	{
		LD_UINT64 Counter = 0ULL;
		QueryPerformanceCounter( ( LARGE_INTEGER * )&Counter );

		return ( Counter - m_StartTime ) / m_SecondsFrequency;
	}

	LD_UINT64 Time::GetTimeInMilliseconds( )
	{
		LD_UINT64 Counter = 0ULL;
		QueryPerformanceCounter( ( LARGE_INTEGER * )&Counter );

		return ( Counter - m_StartTime ) / m_MillisecondsFrequency;
	}

	LD_UINT64 Time::GetTimeInMicroseconds( )
	{
		LD_UINT64 Counter = 0ULL;
		QueryPerformanceCounter( ( LARGE_INTEGER * )&Counter );

		LD_FLOAT64 Microseconds =
			( ( LD_FLOAT64 )Counter - ( LD_FLOAT64 )m_StartTime ) /
			m_MicrosecondsFrequency;

		return ( LD_UINT64 )Microseconds;
	}
}

