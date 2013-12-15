#ifndef __LD_BASEGAMEENTITY_HPP__
#define __LD_BASEGAMEENTITY_HPP__

#include <DataTypes.hpp>

const LD_UINT32 LD_RENDERABLE_2D	=	0x00000001;

namespace LD
{
	class BaseGameEntity
	{
	public:
		BaseGameEntity( );
		virtual ~BaseGameEntity( );

		virtual LD_UINT32 Initialise( ) = 0;
		virtual void Update( LD_UINT64 p_ElapsedTime ) = 0;

		LD_UINT32 GetType( ) const;

		void SetID( const LD_UINT32 p_ID );
		LD_UINT32 GetID( ) const;

	protected:
		LD_UINT32 m_ID;
		LD_UINT32 m_Types;
	};
}

#endif // __LD_BASEGAMEENTITY_HPP__

