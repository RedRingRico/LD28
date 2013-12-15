#include <GameEntityManager.hpp>
#include <BaseGameEntity.hpp>
#include <BaseGameEntityRenderable2D.hpp>
#include <SDL2/SDL_render.h>

namespace LD
{
	GameEntityManager::GameEntityManager( )
	{
	}

	GameEntityManager::~GameEntityManager( )
	{
	}

	LD_UINT32 GameEntityManager::SetRenderer( SDL_Renderer *p_pRenderer )
	{
		m_pRenderer = p_pRenderer;

		return LD_OK;
	}

	LD_UINT32 GameEntityManager::AddEntity( BaseGameEntity *p_pEntity )
	{
		LD_UINT32 Status = p_pEntity->Initialise( );

		if( Status != LD_OK )
		{
			SDL_Log( "Failed to initialse game entity\n" );
			return LD_FAIL;
		}
		LD_UINT32 Types = p_pEntity->GetType( );
		
		if( Types & LD_RENDERABLE_2D )
		{
			BaseGameEntityRenderable2D *pRender =
				dynamic_cast< BaseGameEntityRenderable2D * >( ( p_pEntity ) );

			pRender->SetRenderer( m_pRenderer );
			pRender->LoadContent( );
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
			LD_UINT32 Types = ( *EntityItr )->GetType( );
			
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

	void GameEntityManager::Update( const LD_UINT64 p_ElapsedTime )
	{
		std::vector< BaseGameEntity * >::iterator EntityItr =
			m_Entities.begin( );

		while( EntityItr != m_Entities.end( ) )
		{
			( *EntityItr )->Update( p_ElapsedTime );
			++EntityItr;
		}
	}
}

