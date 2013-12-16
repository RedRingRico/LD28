#include <Player.hpp>
#include <SDL2/SDL.h>

namespace LD
{
	Player::Player( ) :
		BaseGameEntityRenderable2D::BaseGameEntityRenderable2D( ),
		m_PositionX( 0 ),
		m_PositionY( 0 ),
		m_VelocityX( 0 ),
		m_VelocityY( 0 )
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

	void Player::Update( const LD_UINT64 p_ElapsedTime )
	{
		BaseGameEntityRenderable2D::Update( p_ElapsedTime );

		m_PositionX += m_VelocityX;
		m_PositionY += m_VelocityY;

		m_TextureRectangle.x = m_PositionX;
		m_TextureRectangle.y = m_PositionY;
		m_TextureRectangle.w = 64;
		m_TextureRectangle.h = 64;
	}

	void Player::SetVelocity( const LD_SINT32 p_X, const LD_SINT32 p_Y )
	{
	}

	LD_UINT32 Player::LoadContent( )
	{
		BaseGameEntityRenderable2D::LoadTexture( "GameMedia/Sprites/Player.png" );
	}

	void Player::SetVelocityX( const LD_SINT32 p_VelocityX )
	{
		m_VelocityX = p_VelocityX;
	}

	void Player::SetVelocityY( const LD_SINT32 p_VelocityY )
	{
		m_VelocityY = p_VelocityY;
	}

	void Player::ClearVelocity( )
	{
		m_VelocityX = m_VelocityY = 0;
	}

	void Player::SetMaxSpeed( const LD_SINT32 p_MaxSpeed )
	{
		m_MaxSpeed = p_MaxSpeed;
	}

	LD_SINT32 Player::GetMaxSpeed( ) const
	{
		return m_MaxSpeed;
	}
}

