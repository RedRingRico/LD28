#include <BaseGameEntity.hpp>

namespace LD
{
	void BaseGameEntity::SetID( const LD_UINT32 p_ID )
	{
		m_ID = p_ID;
	}

	LD_UINT32 BaseGameEntity::GetID( ) const
	{
		return m_ID;
	}
}

