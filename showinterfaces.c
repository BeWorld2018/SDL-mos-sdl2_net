/*
  showinterfaces: a simple test program to show the network interfaces
  Copyright (C) 1997-2016 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "SDL.h"
#include "SDL_net.h"

#define MAX_ADDRESSES   10

int main(int argc, char *argv[])
{
    IPaddress addresses[MAX_ADDRESSES];
    int i, count;

	
	if (SDL_Init(0) == -1) {
		printf("SDL Init failed\n");
		return 0;
	}
	if (SDLNet_Init() == -1) {
		printf("SDL Init failed\n");
		return 0;
	}
	
	
	
    count = SDLNet_GetLocalAddresses(addresses, MAX_ADDRESSES);
    printf("Found %d local addresses\n", count);
    for ( i = 0; i < count; ++i ) {
        printf("%d: %d.%d.%d.%d - %s", i+1,
            (addresses[i].host >> 0) & 0xFF,
            (addresses[i].host >> 8) & 0xFF,
            (addresses[i].host >> 16) & 0xFF,
            (addresses[i].host >> 24) & 0xFF,
            SDLNet_ResolveIP(&addresses[i]));
    }
	
	SDLNet_Quit();
	SDL_Quit();
	
    return 0;
}
