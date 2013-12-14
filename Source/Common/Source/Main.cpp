#include <GitVersion.hpp>
#include <Game.hpp>
#if defined LD_PLATFORM_WINDOWS
#include <windows.h>
#endif // LD_PLATFORM_WINDOWS

#if defined LD_PLATFORM_WINDOWS
WINAPI INT WinMain( HINSTANCE p_ThisInst, HINSTANCE p_PrevInstance,
	LPSTR p_pCmdLine, INT p_CmdShow )
#elif LD_PLATFORM_LINUX
int main( int p_Argc, char **p_ppArgc )
#else
#error Unknown platform
#endif // LD_PLATFORM_WINDOWS
{
	LD::Game TheGame;

	if( TheGame.Initialise( ) != LD_OK )
	{
		return LD_FAIL;
	}

	return TheGame.Execute( );
}

