#include <Game.hpp>
#include <GitVersion.hpp>
#include <cstring>
#include <cstdio>
#include <GameEntityManager.hpp>
#include <Player.hpp>
#include <Time.hpp>

namespace LD
{
	Game::Game( ) :
		m_pRenderer( LD_NULL ),
		m_pWindow( LD_NULL ),
		m_pGameEntityManager( LD_NULL ),
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
		
		return LD_OK;
	}

	LD_UINT32 Game::Execute( )
	{
		Player Hiro;
		m_pGameEntityManager->AddEntity( &Hiro );

		LD::Time Timer;
		Timer.StartTimer( );

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
					if( Event.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
					{
						m_Run = LD_FALSE;
					}
				}
			}

			this->Update( Timer.GetTimeInMicroseconds( ) );
			this->Render( );
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
