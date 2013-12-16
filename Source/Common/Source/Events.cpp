#include <Events.hpp>
#include <Hash.hpp>
#include <cstring>

namespace LD
{
	EventType::EventType( const LD_CHAR8 *p_pName )
	{
		LD_MEMSIZE NameLength = strlen( p_pName );
		m_pName = new LD_CHAR8[ NameLength + 1 ];
		strncpy( m_pName, p_pName, NameLength );
		m_pName[ NameLength ] = '\0';

		SetID( p_pName );
	}

	EventType::~EventType( )
	{
		ldSafeDeleteArray( m_pName );
	}

	void EventType::SetID( const LD_CHAR8 *p_pName )
	{
		m_ID = HashString( p_pName );
	}

	LD_UINT32 EventType::GetID( ) const
	{
		return m_ID;
	}

	LD_CHAR8 *EventType::GetName( ) const
	{
		return m_pName;
	}

	bool EventType::operator<( const EventType &p_Other ) const
	{
		return ( m_ID < p_Other.m_ID );
	}

	bool EventType::operator==( const EventType &p_Other ) const
	{
		return ( m_ID == p_Other.m_ID );
	}

	EventData::~EventData( )
	{
	}

	Event::Event( const LD_CHAR8 *p_pEventName,
		EventData * const &p_pEventData,
		const LD_UINT64 p_DispatchTime ) :
		m_EventType( p_pEventName ),
		m_pData( p_pEventData ),
		m_DispatchTime( p_DispatchTime )
	{
	}

	Event::~Event( )
	{
	}

	EventType Event::GetEventType( ) const
	{
		return m_EventType;
	}

	bool Event::operator<( const Event &p_Event ) const
	{
		return ( m_DispatchTime > p_Event.m_DispatchTime );
	}

	EventListener::~EventListener( )
	{
	}
}

