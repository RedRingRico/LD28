#ifndef __LD_BASEGAMEENTITY2D_HPP__
#define __LD_BASEGAMEENTITY2D_HPP__

#include <BaseGameEntity.hpp>
#include <SDL2/SDL.h>

namespace LD
{
	// This is a pretty long class name...
	class BaseGameEntityRenderable2D : public BaseGameEntity
	{
	public:
		virtual ~BaseGameEntityRenderable2D( ){ }

		LD_UINT32 LoadTexture( const LD_CHAR8 *p_pFileName );

		LD_UINT32 SetRenderer( SDL_Renderer *p_pRenderer );

		void Render( );

	protected:
		SDL_Texture		*m_pTexture;
		SDL_Renderer	*m_pRenderer;
		LD_SINT32		m_TextureWidth;
		LD_SINT32		m_TextureHeight;
		SDL_Rect		m_TextureRectangle;
	};
}

#endif

