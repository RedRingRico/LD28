#ifndef __LD_GAMEPLAYEVENTS_HPP__
#define __LD_GAMEPLAYEVENTS_HPP__

#include <Events.hpp>
#include <SDL2/SDL.h>

namespace LD
{
	class Player;
	const LD_UINT32 KEY_PRESSED		= 1 << 0;
	const LD_UINT32 KEY_RELEASED	= 0 << 0;
	const LD_UINT32 KEY_REPEAT		= 1 << 1;
	const LD_UINT32 KEY_NOREPEAT	= 0 << 1;

	static EventType KeyboardInputEventType( "Keyboard Input" );

	class KeyboardInputEventData : public EventData
	{
	public:
		KeyboardInputEventData( );
		virtual ~KeyboardInputEventData( );

		void SetKeyScanCode( const SDL_Scancode p_ScanCode );
		void SetKeyRepeat( );
		void SetKeyDown( );
		void SetKeyUp( );

		SDL_Scancode GetKeyScanCode( ) const;
		LD_UINT32 GetKeyState( ) const;

	private:
		SDL_Scancode	m_Key;
		// 1 << 0 == Pressed
		// 1 << 1 == Repeat
		LD_UINT32		m_State;
	};

	class KeyboardInputEvent : public Event
	{
	public:
		LD_EXPLICIT KeyboardInputEvent(
			KeyboardInputEventData * const &p_pKeyboardData );
		virtual ~KeyboardInputEvent( );

	private:
	};

	class InputListener : public EventListener
	{
	public:
		InputListener( );
		virtual ~InputListener( );

		virtual LD_BOOL HandleEvent( const Event &p_Event );

		virtual LD_CHAR8 *GetName( ) const;

		LD_UINT32 SetPlayer( Player * const &p_pPlayer );

	private:
		Player	*m_pPlayer;
	};
}

#endif

