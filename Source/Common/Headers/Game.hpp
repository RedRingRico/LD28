#ifndef __LD_GAME_HPP__
#define __LD_GAME_HPP__

#include <DataTypes.hpp>
#include <SDL2/SDL.h>

namespace LD
{
	class GameEntityManager;
	class Game
	{
	public:
		Game( );
		~Game( );

		LD_UINT32 Initialise( );
		LD_UINT32 Execute( );

	private:
		void Update( );
		void Render( );
		
		LD_BOOL	m_Run;

		SDL_Renderer	*m_pRenderer;
		SDL_Window		*m_pWindow;

		GameEntityManager	*m_pGameEntityManager;
	};
}

#endif

