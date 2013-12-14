#include <GameEntityManager.hpp>
#include <BaseGameEntity.hpp>
#include <BaseGameEntityRenderable2D.hpp>

namespace LD
{
	GameEntityManager::GameEntityManager( )
	{
	}

	GameEntityManager::~GameEntityManager( )
	{
	}

	LD_UINT32 GameEntityManager::AddEntity( BaseGameEntity *p_pEntity )
	{
		LD_UINT32 Status = p_pEntity->Initialise( );

		if( Status != LD_OK )
		{
			SDL_Log( "Failed to initialse game entity\n" );
			return LD_FAIL;
		}

		m_Entities.push_back( p_pEntity );
		return LD_OK;
	}

	void GameEntityManager::Render( )
	{
		std::vector< BaseGameEntity * >::iterator EntityItr =
			m_Entities.begin( );

		while( EntityItr != m_Entities.end( ) )
		{
			LD_UINT32 Types =( *EntityItr )->GetType( );
			
			if( Types & LD_RENDERABLE_2D )
			{
				BaseGameEntityRenderable2D *pRender =
					dynamic_cast< BaseGameEntityRenderable2D * >(
						( *EntityItr ) );

				pRender->Render( );
			}

			++EntityItr;
		}
	}
}

