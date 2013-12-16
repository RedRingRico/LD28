#include <EventManager.hpp>
#include <cstring>
#include <SDL2/SDL.h>

namespace LD
{
	EventManager::EventManager( const LD_UINT32 p_BufferCount )
	{
		if( p_BufferCount > 2 )
		{
			m_BufferCount = p_BufferCount;
		}
		else
		{
			m_BufferCount = 2;
		}

		m_pQueue = new EventQueue[ m_BufferCount ];
	}

	EventManager::~EventManager( )
	{
		ldSafeDeleteArray( m_pQueue );
	}

	LD_UINT32 EventManager::AddListener(
		EventListener * const &p_pEventListener,
		const EventType &p_EventType )
	{
		LD_UINT32 Information = 0;

		if( this->ValidateEventType( p_EventType, &Information ) != LD_OK )
		{
			SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,
				"[LD::EventManager::AddListener] Failed to verify event type "
				"\"%s\" [ %d ]\n", p_EventType.GetName( ),
				p_EventType.GetID( ) );

			return LD_FAIL;
		}

		// Add the event type if it isn't already
		EventTypeSet::iterator EventTypeItr;

		if( Information != EVENT_ALREADYINSET )
		{
			EventTypeSetInsertResult Insert =
				m_EventTypes.insert( p_EventType );

			if( Insert.second == false )
			{
				return LD_FAIL;
			}

			if( Insert.first == m_EventTypes.end( ) )
			{
				return LD_FAIL;
			}

			EventTypeItr = Insert.first;
		}

		// See if there's a listener map entry for this type
		EventIDEventListenerMap::iterator IDListenerItr =
			m_EventRegistry.find( p_EventType.GetID( ) );
		
		if( IDListenerItr == m_EventRegistry.end( ) )
		{
			EventIDEventListenerMapInsertResult IDListenerInsert =
				m_EventRegistry.insert(
					EventIDEventListenerEntry( p_EventType.GetID( ),
					EventListenerList( ) ) );

			if( IDListenerInsert.second == false )
			{
				return LD_FAIL;
			}

			if( IDListenerInsert.first == m_EventRegistry.end( ) )
			{
				return LD_FAIL;
			}

			IDListenerItr = IDListenerInsert.first;
		}

		EventListenerList &EventListeners = ( *IDListenerItr ).second;
		EventListenerList::iterator EventListenerItr = EventListeners.begin( );
		for( ; EventListenerItr != EventListeners.end( ); ++EventListenerItr )
		{
			bool Match = ( *EventListenerItr == p_pEventListener );

			if( Match )
			{
				return LD_FAIL;
			}
		}

		EventListeners.push_back( p_pEventListener );

		return LD_OK;
	}

	LD_UINT32 EventManager::SendEvent( const Event &p_Event )
	{
		LD_UINT32 Information = 0;

		if( this->ValidateEventType( p_Event.GetEventType( ), &Information ) !=
			LD_OK )
		{
			return LD_FAIL;
		}

		EventIDEventListenerMap::const_iterator IDListenerItr =
			m_EventRegistry.find( LD::WildCardEvent.GetID( ) );

		if( IDListenerItr != m_EventRegistry.end( ) )
		{
			const EventListenerList &ListenerList = IDListenerItr->second;
			EventListenerList::const_iterator ListenerListItr =
				ListenerList.begin( );

			for( ; ListenerListItr != ListenerList.end( ); ++ListenerListItr )
			{
				( *ListenerListItr )->HandleEvent( p_Event );
			}
		}

		IDListenerItr = m_EventRegistry.find(
			p_Event.GetEventType( ).GetID( ) );

		if( IDListenerItr == m_EventRegistry.end( ) )
		{
			return LD_FAIL;
		}

		const EventListenerList &ListenerList = IDListenerItr->second;

		LD_BOOL EventProcessed = LD_FALSE;

		EventListenerList::const_iterator IDListenerItr2 =
			ListenerList.begin( );

		for( ; IDListenerItr2 != ListenerList.end( ); ++IDListenerItr2 )
		{
			if( ( *IDListenerItr2 )->HandleEvent( p_Event ) == LD_TRUE )
			{
				EventProcessed = LD_TRUE;
			}
		}

		return ( EventProcessed ? LD_OK : LD_FAIL );
	}


	LD_UINT32 EventManager::ValidateEventType( const EventType &p_EventType,
		LD_UINT32 *p_pInformation ) const
	{
		if( p_EventType.GetName( ) == LD_NULL )
		{
			SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,
				"[LD::EventManager::ValidateEventType] Invalid name for "
				"event\n" );

			( *p_pInformation ) = EVENT_INVALIDNAME;

			return LD_FAIL;
		}

		if( ( p_EventType.GetID( ) == LD::WildCardEvent.GetID( ) ) &&
			( strcmp( p_EventType.GetName( ), LD::WildCardEvent.GetName( ) )
				!= 0 ) )
		{
			SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,
				"[LD::EventManager::Validatetype] EventType ID is zero and it "
				"is not a wildcard event\n" );

			( *p_pInformation ) = EVENT_WILDCARDMISMATCH;

			return LD_FAIL;
		}

		EventTypeSet::const_iterator EventTypeItr =
			m_EventTypes.find( p_EventType );

		if( EventTypeItr != m_EventTypes.end( ) )
		{
			EventType OtherEvent = *EventTypeItr;

			if( strcmp( p_EventType.GetName( ), OtherEvent.GetName( ) ) != 0 )
			{
				SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,
					"[LD::EventManager::ValidateEventType] Name collision "
					"between stored event: \"%s\" [ %d ] and "
					"event being validated: "
					"\"%s\" [ %d ]\n",
					OtherEvent.GetName( ), OtherEvent.GetID( ),
					p_EventType.GetName( ), p_EventType.GetID( ) );

				( *p_pInformation ) = EVENT_NAMECOLLISION;

				return LD_FAIL;
			}
		}
		else
		{
			( *p_pInformation ) = EVENT_ALREADYINSET;
		}

		return LD_OK;
	}
}

