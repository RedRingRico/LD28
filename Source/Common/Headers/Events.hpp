#ifndef __LD_EVENTS_HPP__
#define __LD_EVENTS_HPP__

#include <DataTypes.hpp>

namespace LD
{
	class EventType
	{
	public:
		EventType( const LD_CHAR8 *p_pName );
		virtual ~EventType( );

		LD_UINT32 GetID( ) const;
		char *GetName( ) const;

	protected:
		LD_UINT32	m_ID;
		LD_CHAR8	*m_pName;
	};

	class EventData
	{
	public:
		virtual ~EventData( );

		void SetDispatchTime( const LD_UINT64 p_DispatchTime = 0ULL );
		LD_UINT64 GetDispatchTime( ) const;

	protected:
		LD_UINT64	m_DispatchTime;
	};
	
	class Event
	{
	public:
		Event( const LD_CHAR8 *p_EventName , const LD_UINT64 p_DispatchTime );
		virtual ~Event( );

	protected:
	};
}

#endif // __LD_EVENTS_HPP__

