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
	class EventManager
	{
	public:
		LD_EXPLICIT EventManager( const LD_UINT32 p_BufferCount = 2 );
		~EventManager( );

		LD_UINT32 AddListener( EventListener * const &p_pEventListener,
			const EventType &p_EventType );
		LD_UINT32 RemoveListener( EventListener * const &p_pListener );

		LD_UINT32 SendEvent( const Event &p_pEvent );

		void ProcessEvents( );

		LD_BOOL ValidateType( const EventType &p_Type,
			LD_UINT32 *p_pError ) const;

	private:
		typedef std::priority_queue< Event * > EventQueue;
		typedef std::set< EventType > EventTypeSet;
		typedef std::pair< EventTypeSet::iterator, bool >
			EventTypeSetInsertResult;
		typedef std::list< EventListener * > EventListenerList;
		typedef std::map< LD_UINT32, EventListenerList >
			EventIDEventListenerMap;
		typedef std::pair< LD_UINT32, EventListenerList >
			EventIDEventListenerMapInsertResult;

		EventTypeSet			m_Types;
		EventIDEventListenerMap	m_EventRegistry;
		EventQueue				*m_pQueue;

		LD_UINT32	m_BufferCount;
		LD_UINT32	m_ActiveBuffer;
	};
}

#endif // __LD_EVENTMANAGER_HPP__

