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

		void SetVelocity( const LD_SINT32 p_X, const LD_SINT32 p_Y );

	private:
	};
}

#endif // __LD_PLAYER_HPP__

