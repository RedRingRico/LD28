#ifndef __LD_PLAYER_HPP__
#define __LD_PLAYER_HPP__

#include <BaseGameEntityRenderable2D.hpp>

namespace LD
{
	class Player : public BaseGameEntityRenderable2D
	{
	public:
		Player( );
		virtual ~Player( );

		virtual LD_UINT32 Initialise( );

		virtual void Update( const LD_UINT64 p_ElapsedTime );

		void SetVelocity( const LD_SINT32 p_X, const LD_SINT32 p_Y );

		virtual LD_UINT32 LoadContent( );

		void SetVelocityX( const LD_SINT32 p_VelocityX );
		void SetVelocityY( const LD_SINT32 p_VelocityY );
		void ClearVelocity( );

		void SetMaxSpeed( const LD_SINT32 );
		LD_SINT32 GetMaxSpeed( ) const;

	private:
		LD_SINT32 m_MaxSpeed;

		LD_SINT32 m_VelocityY;
		LD_SINT32 m_VelocityX;

		LD_SINT32 m_PositionX;
		LD_SINT32 m_PositionY;
	};
}

#endif // __LD_PLAYER_HPP__

