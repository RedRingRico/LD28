#include <GameplayEvents.hpp>
#include <Player.hpp>

namespace LD
{
	KeyboardInputEventData::KeyboardInputEventData( ) :
		m_Key( SDL_SCANCODE_UNKNOWN ),
		m_State( 0 )
	{
	}

	KeyboardInputEventData::~KeyboardInputEventData( )
	{
	}

	void KeyboardInputEventData::SetKeyScanCode(
		const SDL_Scancode p_ScanCode )
	{
		SDL_Log( "KEY: %d\n", p_ScanCode );
		m_Key = p_ScanCode;
	}

	void KeyboardInputEventData::SetKeyRepeat( )
	{
		m_State |= KEY_REPEAT;
	}

	void KeyboardInputEventData::SetKeyDown( )
	{
		m_State |= KEY_PRESSED;
	}

	void KeyboardInputEventData::SetKeyUp( )
	{
		m_State &= ~( KEY_RELEASED );
	}

	SDL_Scancode KeyboardInputEventData::GetKeyScanCode( ) const
	{
		return m_Key;
	}

	LD_UINT32 KeyboardInputEventData::GetKeyState( ) const
	{
		return m_State;
	}

	KeyboardInputEvent::KeyboardInputEvent(
		KeyboardInputEventData * const &p_pKeyboardData ) :
		Event::Event( KeyboardInputEventType.GetName( ), p_pKeyboardData,
			0ULL )
	{
	}

	KeyboardInputEvent::~KeyboardInputEvent( )
	{
	}

	InputListener::InputListener( ) :
		m_pPlayer( LD_NULL )
	{
	}

	InputListener::~InputListener( )
	{
	}

	LD_BOOL InputListener::HandleEvent( const Event &p_Event )
	{
		LD_UINT32 EventID = p_Event.GetEventType( ).GetID( );

		if( EventID == KeyboardInputEventType.GetID( ) )
		{
			KeyboardInputEventData *pKeyboardData =
				p_Event.GetData< KeyboardInputEventData >( );

			if( m_pPlayer )
			{
				if( pKeyboardData->GetKeyState( ) == KEY_RELEASED )
				{
					if( pKeyboardData->GetKeyScanCode( ) == SDL_SCANCODE_W )
					{
						m_pPlayer->SetVelocityY( 0 );
					}
					if( pKeyboardData->GetKeyScanCode( ) == SDL_SCANCODE_S )
					{
						m_pPlayer->SetVelocityY( 0 );
					}

					if( pKeyboardData->GetKeyScanCode( ) == SDL_SCANCODE_A )
					{
						m_pPlayer->SetVelocityX( 0 );
					}
					if( pKeyboardData->GetKeyScanCode( ) == SDL_SCANCODE_D )
					{
						m_pPlayer->SetVelocityX( 0 );
					}
				}

				if( pKeyboardData->GetKeyState( ) & KEY_PRESSED ||
					pKeyboardData->GetKeyState( ) & KEY_REPEAT )
				{
					if( pKeyboardData->GetKeyScanCode( ) == SDL_SCANCODE_W )
					{
						m_pPlayer->SetVelocityY( -m_pPlayer->GetMaxSpeed( ) );
					}
					if( pKeyboardData->GetKeyScanCode( ) == SDL_SCANCODE_S )
					{
						m_pPlayer->SetVelocityY( m_pPlayer->GetMaxSpeed( ) );
					}

					if( pKeyboardData->GetKeyScanCode( ) == SDL_SCANCODE_A )
					{
						m_pPlayer->SetVelocityX( -m_pPlayer->GetMaxSpeed( ) );
					}
					if( pKeyboardData->GetKeyScanCode( ) == SDL_SCANCODE_D )
					{
						m_pPlayer->SetVelocityX( m_pPlayer->GetMaxSpeed( ) );
					}
				}
			}

			return LD_TRUE;
		}

		return LD_FALSE;
	}

	LD_CHAR8 *InputListener::GetName( ) const
	{
		return "Input Listener";
	}

	LD_UINT32 InputListener::SetPlayer( Player * const &p_pPlayer )
	{
		m_pPlayer = p_pPlayer;
	}
}

