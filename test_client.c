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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL_net.h"
int main(int argc, char **argv) { 
	
	IPaddress ip;	 /* Server address */ 
	TCPsocket sd;	 /* Socket descriptor */
	int quit, len; char buffer[512];

/* Simple parameter checking */ 
	if (argc < 3) {
		fprintf(stderr, "Usage: %s host port\n", argv[0]); exit(EXIT_FAILURE);
	}

	if (SDLNet_Init() < 0) { 
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError()); exit(EXIT_FAILURE); 
	}

	/* Resolve the host we are connecting to */ 
	if (SDLNet_ResolveHost(&ip, argv[1], atoi(argv[2])) < 0) { fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError()); exit(EXIT_FAILURE); }

	/* Open a connection with the IP provided (listen on the host's port) */
	if (!(sd = SDLNet_TCP_Open(&ip))) { fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError()); exit(EXIT_FAILURE); }

	/* Send messages */ quit = 0; 
	while (!quit) { 
		printf("Write something:\n>"); 
		scanf("%s", buffer);
		len = strlen(buffer) + 1; 
		if (SDLNet_TCP_Send(sd, (void *)buffer, len) < len) { 
			fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError()); exit(EXIT_FAILURE); 
		}
		if(strcmp(buffer, "exit") == 0) quit = 1; 
		if(strcmp(buffer, "quit") == 0) quit = 1; 
	}

	SDLNet_TCP_Close(sd); 
	
	SDLNet_Quit();

	return EXIT_SUCCESS; 
}