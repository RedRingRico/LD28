#include <Game.hpp>
#include <GitVersion.hpp>
#include <cstring>
#include <cstdio>
#include <GameEntityManager.hpp>
#include <EventManager.hpp>
#include <Player.hpp>
#include <Time.hpp>
#include <GameplayEvents.hpp>

namespace LD
{
	Game::Game( ) :
		m_pRenderer( LD_NULL ),
		m_pWindow( LD_NULL ),
		m_pGameEntityManager( LD_NULL ),
		m_pEventManager( LD_NULL ),
		m_Run( LD_TRUE )
	{
	}

	Game::~Game( )
	{
		ldSafeDelete( m_pGameEntityManager );

		SDL_DestroyRenderer( m_pRenderer );
		SDL_DestroyWindow( m_pWindow );

		SDL_Quit( );
	}

	LD_UINT32 Game::Initialise( )
	{
		SDL_SetMainReady( );
		SDL_Init( SDL_INIT_EVERYTHING );
		char Title[ 1024 ];
		memset( Title, '\0', sizeof( Title ) );
		sprintf( Title, "Red Ring Rico's Ludum Dare #28 Entry "
			"[Build: %s]", GIT_COMMITHASH );

		m_pWindow = SDL_CreateWindow( Title,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720,
			SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_GRABBED |
			SDL_WINDOW_MAXIMIZED );
		m_pRenderer = SDL_CreateRenderer( m_pWindow, -1,
			SDL_RENDERER_ACCELERATED );

		SDL_SetRenderDrawColor( m_pRenderer, 0x20, 0x00, 0x20, 0xFF );

		m_pGameEntityManager = new GameEntityManager( );
		m_pGameEntityManager->SetRenderer( m_pRenderer );

		m_pEventManager = new EventManager( 2 );

		m_pInputListener = new InputListener( );

		m_pEventManager->AddListener( m_pInputListener,
			KeyboardInputEventType );
		
		return LD_OK;
	}

	LD_UINT32 Game::Execute( )
	{
		Player Hiro;
		m_pGameEntityManager->AddEntity( &Hiro );
		m_pInputListener->SetPlayer( &Hiro );
		Hiro.SetMaxSpeed( 8 );

		LD::Time Timer;
		Timer.StartTimer( );

		LD_UINT64 ElapsedTime = 0ULL;
		LD_UINT64 TimeStep = 16667ULL;
		LD_UINT64 PreviousTime = Timer.GetTimeInMicroseconds( );
		LD_UINT64 FrameTime = PreviousTime;
		LD_UINT32 FrameRate = 0;
		LD_UINT64 Accumulator = 0ULL;
/*		Uint8 *pPreviousKeys = new Uint8[ SDL_NUM_SCANCODES ];
		memset( pPreviousKeys, 0, sizeof( Uint8 ) * SDL_NUM_SCANCODES );
*/
		while( m_Run )
		{
			SDL_Event Event;
			if( SDL_PollEvent( &Event ) )
			{
				if( Event.type == SDL_QUIT )
				{
					m_Run = LD_FALSE;
				}
				if( Event.type == SDL_KEYDOWN )
				{
					KeyboardInputEventData KeyboardData;
					KeyboardData.SetKeyScanCode( Event.key.keysym.scancode );
					KeyboardData.SetKeyDown( );
					if( Event.key.repeat )
					{
						SDL_Log( "KEY REPEATED\n" );
						KeyboardData.SetKeyRepeat( );
					}
					KeyboardInputEvent Keyboard( &KeyboardData );

					m_pEventManager->SendEvent( Keyboard );
					if( Event.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
					{
						m_Run = LD_FALSE;
					}
				}
				if( Event.type == SDL_KEYUP )
				{
					KeyboardInputEventData KeyboardData;
					KeyboardData.SetKeyScanCode( Event.key.keysym.scancode );
					KeyboardData.SetKeyUp( );
					KeyboardInputEvent Keyboard( &KeyboardData );

					m_pEventManager->SendEvent( Keyboard );
				}
			}
/*			SDL_PumpEvents( );
			const Uint8 *pCurrentKeys = SDL_GetKeyboardState( NULL );

			for( size_t i = 0; i < SDL_NUM_SCANCODES; ++i )
			{
				if( pCurrentKeys[ i ] != pPreviousKeys[ i ] )
				{
					KeyboardInputEventData KeyboardData;
					SDL_Scancode Scan = ( SDL_Scancode )i;
					KeyboardData.SetKeyScanCode( Scan );
					if( pCurrentKeys[ i ] )
					{
						KeyboardData.SetKeyUp( );
					}
					else
					{
						KeyboardData.SetKeyDown( );
					}
					KeyboardInputEvent Keyboard( &KeyboardData );

					m_pEventManager->SendEvent( Keyboard );				
				}
			}

			memcpy( pPreviousKeys, pCurrentKeys,
				sizeof( Uint8 ) * SDL_NUM_SCANCODES );*/

			const LD_UINT64 NewTime = Timer.GetTimeInMicroseconds( );
			LD_UINT64 DeltaTime = NewTime - PreviousTime;

			if( DeltaTime > 250000ULL )
			{
				DeltaTime = 250000ULL;
			}

			PreviousTime = NewTime;

			Accumulator += DeltaTime;

			while( Accumulator >= TimeStep )
			{
				this->Update( TimeStep );
				ElapsedTime += TimeStep;
				Accumulator -= TimeStep;
			}

			this->Render( );

			++FrameRate;

			if( ( NewTime - FrameTime ) >= 1000000ULL )
			{
				SDL_Log( "FPS: %d\n", FrameRate );
				FrameTime = Timer.GetTimeInMicroseconds( );
				FrameRate = 0;
			}
		}

		return LD_OK;
	}

	void Game::Update( const LD_UINT64 p_ElapsedTime )
	{
		m_pGameEntityManager->Update( p_ElapsedTime );
	}

	void Game::Render( )
	{
		SDL_RenderClear( m_pRenderer );
		m_pGameEntityManager->Render( );
		SDL_RenderPresent( m_pRenderer );
	}
}
