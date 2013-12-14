#ifndef __LD_GAMEENTITYMANAGER_HPP__
#define __LD_GAMEENTITYMANAGER_HPP__

#include <DataTypes.hpp>
#include <vector>

struct SDL_Renderer;

namespace LD
{
	class BaseGameEntity;

	class GameEntityManager
	{
	public:
		GameEntityManager( );
		~GameEntityManager( );

		LD_UINT32 SetRenderer( SDL_Renderer *p_pRenderer );

		LD_UINT32 AddEntity( BaseGameEntity *p_pEntity );

		void Render( );

	private:
		std::vector< BaseGameEntity * > m_Entities;
		SDL_Renderer *m_pRenderer;
	};
}

#endif // __LD_GAMEENTITYMANAGER_HPP__

