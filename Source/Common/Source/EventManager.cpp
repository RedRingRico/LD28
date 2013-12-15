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

		if( this->ValidateType( p_EventType, &Information ) != LD_OK )
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

	LD_UINT32 EventManager::ValidateType( const EventType &p_EventType,
		LD_UINT32 *p_pInformation ) const
	{
		if( p_EventType.GetName( ) == LD_NULL )
		{
			SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,
				"[LD::EventManager::ValidateType] Invalid name for event\n" );

			( *p_pInformation ) = EVENT_INVALIDNAME;

			return LD_FAIL;
		}

		if( ( p_EventType.GetID( ) == 0 ) &&
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
					"[LD::EventManager::ValidateType] Name collision between "
					"stored event: \"%s\" [ %d ] and event being validated: "
					"\"%s\" [ %d ]\n",
					OtherEvent.GetName( ), OtherEvent.GetID( ),
					p_EventType.GetName( ), p_EventType.GetID( ) );

				( *p_pInformation ) = EVENT_NAMECOLLISION;

				return LD_FAIL;
			}
		}
		else
		{
			SDL_LogWarn( SDL_LOG_CATEGORY_APPLICATION,
				"[LD::EventManager::ValidateType] Type \"%s\" [ %d ] already "
				"in the set\n", p_EventType.GetName( ), p_EventType.GetID( ) );

			( *p_pInformation ) = EVENT_ALREADYINSET;
		}

		return LD_OK;
	}
}

