#include <Player.hpp>
#include <SDL2/SDL.h>

namespace LD
{
	Player::Player( ) :
		BaseGameEntityRenderable2D::BaseGameEntityRenderable2D( )
	{
	}

	Player::~Player( )
	{
	}

	LD_UINT32 Player::Initialise( )
	{
		if( BaseGameEntityRenderable2D::Initialise( ) != LD_OK )
		{
			SDL_Log( "Failed to create an instance of the Player class\n" );
			return LD_FAIL;
		}

		return LD_OK;
	}

	void Player::SetVelocity( const LD_SINT32 p_X, const LD_SINT32 p_Y )
	{
	}

	LD_UINT32 Player::LoadContent( )
	{
		BaseGameEntityRenderable2D::LoadTexture( "GameMedia/Sprites/Player.png" );
	}
}

