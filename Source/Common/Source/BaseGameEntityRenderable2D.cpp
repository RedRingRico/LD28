#include <BaseGameEntityRenderable2D.hpp>
#include <SDL2/SDL_image.h>

namespace LD
{
	BaseGameEntityRenderable2D::BaseGameEntityRenderable2D( ) :
		m_pTexture( LD_NULL ),
		m_pRenderer( LD_NULL ),
		BaseGameEntity::BaseGameEntity( )
	{
	}

	BaseGameEntityRenderable2D::~BaseGameEntityRenderable2D( )
	{
		SDL_DestroyTexture( m_pTexture );
	}

	LD_UINT32 BaseGameEntityRenderable2D::Initialise( )
	{
		m_Types |= LD_RENDERABLE_2D;

		return LD_OK;
	}

	void BaseGameEntityRenderable2D::Update( const LD_UINT64 p_ElapsedTime )
	{
	}

	LD_UINT32 BaseGameEntityRenderable2D::LoadTexture(
		const LD_CHAR8 *p_pFileName )
	{
		if( m_pRenderer == LD_NULL )
		{
			return LD_FAIL;
		}

		m_pTexture = IMG_LoadTexture( m_pRenderer, p_pFileName );
		SDL_QueryTexture( m_pTexture, LD_NULL, LD_NULL, &m_TextureWidth,
			&m_TextureHeight );
		m_TextureRectangle.x = 0;
		m_TextureRectangle.y = 0;
		m_TextureRectangle.w = m_TextureWidth;
		m_TextureRectangle.h = m_TextureHeight;
		
		return LD_OK;
	}

	LD_UINT32 BaseGameEntityRenderable2D::SetRenderer(
		SDL_Renderer *p_pRenderer )
	{
		if( p_pRenderer == LD_NULL )
		{
			return LD_FAIL;
		}

		m_pRenderer = p_pRenderer;
 
		return LD_OK;
	}

	void BaseGameEntityRenderable2D::Render( )
	{
		if( m_pTexture )
		{
			SDL_Rect Middle;
			Middle.x = 640-32;
			Middle.y = 320-32;
			Middle.w = 64;
			Middle.h = 64;
			SDL_RenderCopy( m_pRenderer, m_pTexture, &m_TextureRectangle,
				&Middle );
		}
	}
}

