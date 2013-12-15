#ifndef __LD_EVENTS_HPP__
#define __LD_EVENTS_HPP__

#include <DataTypes.hpp>

namespace LD
{
	class EventType
	{
	public:
		LD_EXPLICIT EventType( const LD_CHAR8 *p_pName );
		~EventType( );

		void SetID( const LD_CHAR8 *p_pName );

		LD_UINT32 GetID( ) const;
		char *GetName( ) const;

		bool operator<( const EventType &p_Other ) const;
		bool operator==( const EventType &p_Other ) const;

	private:
		LD_UINT32	m_ID;
		LD_CHAR8	*m_pName;
	};

	class EventData
	{
	public:
		virtual ~EventData( );

	protected:
	};
	
	class Event
	{
	public:
		LD_EXPLICIT Event( const LD_CHAR8 *p_EventName,
			EventData *p_pEventData = LD_NULL,
			const LD_UINT64 p_DispatchTime = 0ULL );
		virtual ~Event( );

		EventType GetEventType( ) const;

		LD_UINT64 GetDispatchTime( ) const;

		template< typename T > T* GetData( ) const
			{ return reinterpret_cast < T* >( m_pData ); }

		bool operator<( const Event &p_Event ) const;

	protected:
		EventType	m_Type;
		EventData	*m_pData;
		LD_UINT64	m_DispatchTime;
	};

	class EventListener
	{
	public:
		virtual ~EventListener( );

		virtual LD_BOOL HandleEvent( Event *p_pData ) = 0;

	protected:
	};

	const EventType WildCardEvent( "*" );
}

#endif // __LD_EVENTS_HPP__

