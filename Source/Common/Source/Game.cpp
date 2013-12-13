#include <Game.hpp>

namespace LD
{
	Game::Game( ) :
		m_pRenderer( LD_NULL ),
		m_pWindow( LD_NULL ),
		m_Run( LD_TRUE )
	{
	}

	Game::~Game( )
	{
		SDL_DestroyRenderer( m_pRenderer );
		SDL_DestroyWindow( m_pWindow );
	}

	LD_UINT32 Game::Initialise( )
	{
		m_pWindow = SDL_CreateWindow( "Red Ring Rico's Ludum Dare #28 Entry",
			0, 0, 800, 600, 0 );
		m_pRenderer = SDL_CreateRenderer( m_pWindow, -1,
			SDL_RENDERER_ACCELERATED );

		SDL_SetRenderDrawColor( m_pRenderer, 0x20, 0x00, 0x20, 0xFF );
		
		return LD_OK;
	}

	LD_UINT32 Game::Execute( )
	{
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

			this->Update( );
			this->Render( );
		}

		return LD_OK;
	}

	void Game::Update( )
	{
	}

	void Game::Render( )
	{
		SDL_RenderClear( m_pRenderer );
		SDL_RenderPresent( m_pRenderer );
	}
}
