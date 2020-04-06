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
#include "SDL.h"
#include "SDL_net.h"

int main(int argc, char **argv) {

	TCPsocket sd, csd; /* Socket descriptor, Client socket descriptor */ 
	IPaddress ip, *remoteIP; int quit, quit2; char buffer[512];

	if (SDLNet_Init() < 0) { 
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError()); 
		exit(EXIT_FAILURE); 
	}

/* Resolving the host using NULL make network interface to listen */ 
	if (SDLNet_ResolveHost(&ip, NULL, 2000) < 0) { 
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError()); 
		SDLNet_Quit();
		exit(EXIT_FAILURE); 
		
	}

/* Open a connection with the IP provided (listen on the host's port) */ 
	if (!(sd = SDLNet_TCP_Open(&ip))) {
		
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError()); 
		SDLNet_Quit(); 
		exit(EXIT_FAILURE);
		
	}

/* Wait for a connection, send data and term */ 
	quit = 0; 
	while (!quit) { 
		/* This check the sd if there is a pending connection. * If there is one, accept that, and open a new socket for communicating */ 
		if ((csd = SDLNet_TCP_Accept(sd))) { 
			/* Now we can communicate with the client using csd socket * sd will remain opened waiting other connections */

			/* Get the remote address */ 
			if ((remoteIP = SDLNet_TCP_GetPeerAddress(csd))) 	/* Print the address, converting in the host format */ 
			printf("Host connected: %x %d\n", SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port)); 
			else
			fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());

			quit2 = 0; 
			
			while (!quit2) { 
				if (SDLNet_TCP_Recv(csd, buffer, 512) > 0) { 
					printf("Client say: %s\n", buffer);
					if(strcmp(buffer, "exit") == 0)	/* Terminate this connection */ 
						{ 
							quit2 = 1;
							printf("Terminate connection\n");
						} 
						if(strcmp(buffer, "quit") == 0)	/* Quit the program */ { 
							quit2 = 1; quit = 1; printf("Quit program\n"); 
						} 
				} 
			}

			/* Close the client socket */
			SDLNet_TCP_Close(csd);
		} 
	}
	SDLNet_TCP_Close(sd); 
	SDLNet_Quit();
	return EXIT_SUCCESS;
}
