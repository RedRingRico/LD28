#include <SDL2/SDL.h>
#include <GitVersion.hpp>

#define LD_NULL NULL

int main( int p_Argc, char **p_ppArgc )
{
	SDL_Window	*pWindow = LD_NULL;
	SDL_Surface	*pScreen = LD_NULL;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		return 1;
	}

	char *pMessage = new char[ 1024 ];
	sprintf( pMessage, "LD28 [%s]\nStarting SDL...", GIT_COMMITHASH );

	SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_INFORMATION, "Ludum Dare #28",
		pMessage, NULL );
	if( pMessage )
	{
		delete [ ] pMessage;
		pMessage = LD_NULL;
	}
	
	pWindow = SDL_CreateWindow( "LD28", 1920, 0, 800, 600, SDL_WINDOW_SHOWN );

	if( pWindow == LD_NULL )
	{
		return 1;
	}

	pScreen = SDL_GetWindowSurface( pWindow );
	SDL_FillRect( pScreen, NULL,
		SDL_MapRGB( pScreen->format, 0x20, 0x00, 0x20 ) );
	SDL_UpdateWindowSurface( pWindow );


	SDL_Delay( 3000 );

	SDL_DestroyWindow( pWindow );
	SDL_Quit( );

	return 0;
}

