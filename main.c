#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int REFRESH_RATE = 60;

struct Player {
	int health;
	char* character;
	struct MoveFrame* moves[];
};

struct Box {
	double x1;
	double y1;
	double x2;
	double y2;
};

struct MoveFrame {
	int id;
	int damage;
	int priority;
	char* command;
	struct Box hitbox;
	struct Box movebox;
	int* overrides;
};

const struct Player BALROG = {
	.health = 15000,
	.character = "Balrog",
	.moves = {
		{
			.id = 1,
			.damage = 1200,
			.priority = 100,
			.command = "HP",
			.hitbox = {
			},
			.movebox = {
			},
			.overrides = {
			}
		}
	}
};

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
	int frameRotation = 0;

	char* player1Inputs[REFRESH_RATE * 2];
	MoveFrame* player1State;
	char* player2Inputs[REFRESH_RATE * 2];
	MoveFrame* player2State;

	while (!quit) {
		frameRotation += 1;

		if (frameRotation % FRAME_SKIP != 0) {
			continue;
		}

		frameRotation = 0;

		while (SDL_PollEvent(&keyEvent) != 0) {
			if (keyEvent.type == SDL_QUIT) {
				quit = 1;
			} else if (keyEvent.type == SDL_KEYUP) {
				switch (keyEvent.key.keysym.sym) {
					case SDLK_q:
						quit = 1;
						break;
					case SDLK_p:
						pause = !pause;
						break;
				}
			}
		}

		if (pause) {
			continue;
		}

		const uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		if (currentKeyStates[SDL_SCANCODE_UP]) {
		}
		if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		}
		if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		}
		if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		}

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0, 0.0, 0.0);
		glRectf(player1.x, player1.y, player1.x + player1.w, player1.y + player1.h);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
