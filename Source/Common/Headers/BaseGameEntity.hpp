#ifndef __LD_BASEGAMEENTITY_HPP__
#define __LD_BASEGAMEENTITY_HPP__

#include <DataTypes.hpp>

const LD_UINT32 LD_RENDERABLE_2D	=	0x00000001;

namespace LD
{
	class BaseGameEntity
	{
	public:
		virtual ~BaseGameEntity( ){ }

		void SetID( const LD_UINT32 p_ID );
		LD_UINT32 GetID( ) const;

		virtual LD_UINT32 GetType( ) const = 0;

	protected:
		LD_UINT32 m_ID;
	};
}

#endif

