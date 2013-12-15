#ifndef __LD_EVENTMANAGER_HPP__
#define __LD_EVENTMANAGER_HPP__

#include <DataTypes.hpp>
#include <Events.hpp>
#include <map>
#include <queue>
#include <set>
#include <list>

namespace LD
{
	const LD_UINT32 EVENT_ALREADYINSET		= 0x00000001;
	const LD_UINT32 EVENT_INVALIDNAME		= 0x00000010;
	const LD_UINT32 EVENT_NAMECOLLISION		= 0x00000100;
	const LD_UINT32 EVENT_WILDCARDMISMATCH	= 0x00001000;

	class EventManager
	{
	public:
		LD_EXPLICIT EventManager( const LD_UINT32 p_BufferCount );
		~EventManager( );

		LD_UINT32 AddListener( EventListener * const &p_pEventListener,
			const EventType &p_EventType );
		LD_UINT32 RemoveListener( EventListener * const &p_pListener );

		LD_UINT32 SendEvent( const Event &p_Event );

		void ProcessEvents( );

		LD_UINT32 ValidateEventType( const EventType &p_EventType,
			LD_UINT32 *p_pInformation ) const;

	private:
		typedef std::priority_queue< Event * > EventQueue;
		typedef std::set< EventType > EventTypeSet;
		typedef std::pair< EventTypeSet::iterator, bool >
			EventTypeSetInsertResult;
		typedef std::list< EventListener * > EventListenerList;
		typedef std::map< LD_UINT32, EventListenerList >
			EventIDEventListenerMap;
		typedef std::pair< LD_UINT32, EventListenerList >
			EventIDEventListenerEntry;
		typedef std::pair< EventIDEventListenerMap::iterator, bool >
			EventIDEventListenerMapInsertResult;

		EventTypeSet			m_EventTypes;
		EventIDEventListenerMap	m_EventRegistry;
		EventQueue				*m_pQueue;

		LD_UINT32	m_BufferCount;
		LD_UINT32	m_ActiveBuffer;
	};
}

#endif // __LD_EVENTMANAGER_HPP__

