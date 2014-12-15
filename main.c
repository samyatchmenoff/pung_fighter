#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL.h>
#include <SDL_opengl.h>
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
	int currentFrame = 0;

	struct Character p1 = balrog;
	struct Character p2 = balrog;
	int p1AnimationCounter = 0;
	int p2AnimationCounter = 0;
	int neutralCounter = 1;

	//initialize to neutral
	p1.animation = copyMove(p1.moves[0].animation);

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
					//TODO repeat event should work for directions
					case SDLK_UP:
						addInput(p1.inputs, UP);
						neutralCounter = 0;
						break;
					case SDLK_RIGHT:
						addInput(p1.inputs, RIGHT);
						neutralCounter = 0;
						break;
					case SDLK_DOWN:
						addInput(p1.inputs, DOWN);
						neutralCounter = 0;
						break;
					case SDLK_LEFT:
						addInput(p1.inputs, LEFT);
						neutralCounter = 0;
						break;
					case SDLK_4:
						addInput(p1.inputs, LP);
						neutralCounter = 0;
						break;
					case SDLK_5:
						addInput(p1.inputs, MP);
						neutralCounter = 0;
						break;
					case SDLK_6:
						addInput(p1.inputs, HP);
						neutralCounter = 0;
						break;
					case SDLK_1:
						addInput(p1.inputs, LK);
						neutralCounter = 0;
						break;
					case SDLK_2:
						addInput(p1.inputs, MK);
						neutralCounter = 0;
						break;
					case SDLK_3:
						addInput(p1.inputs, HK);
						neutralCounter = 0;
						break;
				}
			}
		}

		//clear inputs if we've been neutral too long
		//dont want to keep finding old inputs
		if (neutralCounter > NEUTRAL_LIMIT) {
			clearInput(p1.inputs);
			neutralCounter = 1;
		} else if (neutralCounter > 0) {
			addInput(p1.inputs, NEUTRAL);
			neutralCounter += 1;
		} else {
			neutralCounter = 1;
		}

		if (pause) {
			continue;
		}

		struct Move p1Move = *findMove(p1.inputs, p1.moves);
		struct MoveFrame p1State = p1.animation[p1AnimationCounter];
		int cancellable = isCancellable(p1Move.id, &p1State);

		p1.x += p1State.x;
		p1.y += p1State.y;

		for (int i = 0; i < OVERRIDES_LENGTH; i++) {
			printf("%d, ", p1State.overrideMoveIds[i]);
		}

		printf("\n");

		for (int i = 0; i < INPUTS_LENGTH; i++) {
			printf("%d, ", p1.inputs[i]);
		}

		printf("\n");
		printf("lol %d %d\n", p1AnimationCounter, p1State.moveId);

		if (cancellable) {
			printf("omg\n");
			free(p1.animation);
			p1.animation = copyMove(p1Move.animation);
			p1AnimationCounter = 0;
			p1State = p1.animation[p1AnimationCounter];
		} else {
			printf("hrm\n");
			p1AnimationCounter += 1;
			p1State = p1.animation[p1AnimationCounter];

			//if our animation is over, revert back to neutral
			if (p1State.moveId == 0) {
				free(p1.animation);
				p1.animation = copyMove(p1.moves[0].animation);
				p1AnimationCounter = 0;
				p1State = p1.animation[p1AnimationCounter];
			}
		}

		printf("lol %d %d\n", p1AnimationCounter, p1State.moveId);
		printf("\n\n");

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0, 0.0, 0.0);
		glRectf(p1.x + p1State.attbox.x1, p1.y + p1State.attbox.y1, p1.x + p1State.attbox.x2, p1.y + p1State.attbox.y2);

		glColor3f(0.0, 0.0, 1.0);
		glRectf(p1.x + p1State.hitbox.x1, p1.y + p1State.hitbox.y1, p1.x + p1State.hitbox.x2, p1.y + p1State.hitbox.y2);

		SDL_GL_SwapWindow(window);

		sleep(1);
	}

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
