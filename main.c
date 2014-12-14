#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <unistd.h>
#include "config.h"
#include "moves.h"
#include "balrog.h"

int main(int argc, char* args[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow(
		"pung fighter",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);

	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 2;
	}

	SDL_Event keyEvent;
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	/* Request opengl 3.2 context.
	 * SDL doesn't have the ability to choose which profile at this time of writing,
	 * but it should default to the core profile */
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	/* Turn on double buffering with a 24bit Z buffer.
	 * You may need to change this to 16 or 32 for your system */
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetSwapInterval(1);
	glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, -1.0, 1.0);

	int quit = 0;
	int pause = 0;

	SDL_DisplayMode target;
	SDL_DisplayMode closest;

	// Set the desired resolution, etc.
	target.w = SCREEN_WIDTH;
	target.h = SCREEN_HEIGHT;
	target.format = 0;  // don't care
	target.refresh_rate = REFRESH_RATE; // don't care
	target.driverdata   = 0; // initialize to 0
	printf("Requesting: \t%dx%dpx @ %dhz \n", target.w, target.h, target.refresh_rate);

	// Pass the display mode structures by reference to SDL_GetClosestDisplay
	// and check whether the result is a null pointer.
	if (SDL_GetClosestDisplayMode(0, &target, &closest) == NULL) {
		// If the returned pointer is null, no match was found.
		printf("\nNo suitable display mode was found!\n\n");
		return 3;
	}

	// Otherwise, a display mode close to the target is available.
	// Access the SDL_DisplayMode structure to see what was received.
	printf("  Received: \t%dx%dpx @ %dhz \n", closest.w, closest.h, closest.refresh_rate);

	int skip = closest.refresh_rate / REFRESH_RATE;
	const int FRAME_SKIP = skip > 0 ? skip : 1;
	printf("%d\n", FRAME_SKIP);
	int currentFrame = 0;

	struct Character p1 = balrog;
	struct Character p2 = balrog;

	while (!quit) {
		currentFrame += 1;

		if (currentFrame % FRAME_SKIP != 0) {
			continue;
		}

		currentFrame = 0;

		while (SDL_PollEvent(&keyEvent) != 0) {
			if (keyEvent.type == SDL_QUIT) {
				quit = 1;
			} else if (keyEvent.type == SDL_KEYDOWN && keyEvent.key.repeat == 0) {
				switch (keyEvent.key.keysym.sym) {
					case SDLK_q:
						quit = 1;
						break;
					case SDLK_p:
						pause = !pause;
						break;
					case SDLK_UP:
						characterInputUnshift(p1.inputs, UP);
						break;
					case SDLK_RIGHT:
						characterInputUnshift(p1.inputs, RIGHT);
						break;
					case SDLK_DOWN:
						characterInputUnshift(p1.inputs, DOWN);
						break;
					case SDLK_LEFT:
						characterInputUnshift(p1.inputs, LEFT);
						break;
					case SDLK_4:
						characterInputUnshift(p1.inputs, LP);
						break;
					case SDLK_5:
						characterInputUnshift(p1.inputs, MP);
						break;
					case SDLK_6:
						characterInputUnshift(p1.inputs, HP);
						break;
					case SDLK_1:
						characterInputUnshift(p1.inputs, LK);
						break;
					case SDLK_2:
						characterInputUnshift(p1.inputs, MK);
						break;
					case SDLK_3:
						characterInputUnshift(p1.inputs, HK);
						break;

				}
			}
		}

		if (pause) {
			continue;
		}

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0, 0.0, 0.0);
		//glRectf(player1.x, player1.y, player1.x + player1.w, player1.y + player1.h);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
