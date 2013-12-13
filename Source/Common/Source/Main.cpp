#include <GitVersion.hpp>
#include <Game.hpp>

int main( int p_Argc, char **p_ppArgc )
{
	LD::Game TheGame;

	if( TheGame.Initialise( ) != LD_OK )
	{
		return LD_FAIL;
	}

	return TheGame.Execute( );
}

