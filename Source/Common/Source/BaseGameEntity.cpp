#include <BaseGameEntity.hpp>

namespace LD
{
	BaseGameEntity::BaseGameEntity( )
	{
		m_Types = 0;
	}

	BaseGameEntity::~BaseGameEntity( )
	{
	}

	LD_UINT32 BaseGameEntity::GetType( ) const
	{
		return m_Types;
	}

	void BaseGameEntity::SetID( const LD_UINT32 p_ID )
	{
		m_ID = p_ID;
	}

	LD_UINT32 BaseGameEntity::GetID( ) const
	{
		return m_ID;
	}
}

