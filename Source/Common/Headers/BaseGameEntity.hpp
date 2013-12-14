#ifndef __LD_BASEGAMEENTITY_HPP__
#define __LD_BASEGAMEENTITY_HPP__

#include <DataTypes.hpp>

namespace LD
{
	class BaseGameEntity
	{
	public:
		virtual ~BaseGameEntity( ){ }

		void SetID( const LD_UINT32 p_ID );
		LD_UINT32 GetID( ) const;

	protected:
		LD_UINT32 m_ID;
	};
}

#endif

