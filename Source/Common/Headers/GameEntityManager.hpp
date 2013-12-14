#ifndef __LD_GAMEENTITYMANAGER_HPP__
#define __LD_GAMEENTITYMANAGER_HPP__

#include <DataTypes.hpp>
#include <vector>

namespace LD
{
	class BaseGameEntity;

	class GameEntityManager
	{
	public:
		GameEntityManager( );
		~GameEntityManager( );

		LD_UINT32 AddEntity( BaseGameEntity *p_pEntity );

		void Render( );

	private:
		std::vector< BaseGameEntity * > m_Entities;
	};
}

#endif

