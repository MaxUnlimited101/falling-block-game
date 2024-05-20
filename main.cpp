#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_test_font.h>
#include "Props.h"


int main(int argc, char** argv)
{
	// init SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		TILE_SIZE * (GRID_WIDTH + 2) + 100, TILE_SIZE * (GRID_HEIGHT + 2), SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_RenderSetVSync(renderer, 1);
	atexit(SDL_Quit);

	// init props and other stuff
	srand((unsigned int)time(NULL));
	Grid grid(renderer);
	Prop prop(renderer, rand() % PROPS_COUNT);

	// game loop
	int frame = 0;
	int game_end = 0;
	while (1)
	{
		grid.checkPropCollisionDown(prop);
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type)
			{
			case SDL_QUIT:
				exit(EXIT_SUCCESS);
				break;
			case SDL_EventType::SDL_KEYDOWN:
				if (!game_end)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_s:
					case SDLK_DOWN:
						prop.grid_y++;
						break;
					case SDLK_d:
					case SDLK_RIGHT:
						if (!grid.checkPropCollisionRight(prop))
							prop.grid_x++;
						break;
					case SDLK_a:
					case SDLK_LEFT:
						if (!grid.checkPropCollisionLeft(prop))
							prop.grid_x--;
						break;
					case SDLK_r:
						if (!grid.checkPropCollisionRotate(prop))
							prop.rotate90();
					default:
						break;
					}
					grid.checkPropCollisionDown(prop);
					prop.drawProp();
					SDL_RenderPresent(renderer);
					break;
			default:
				break;
				}
			}
		}

		if (prop.destroyed && !game_end)
			prop = Prop(renderer, rand() % PROPS_COUNT);

		if (frame == 60)
		{
			if (grid.checkPropCollisionDown(prop))
				game_end = 1;
			if (!game_end)
				prop.grid_y++;
			frame = 0;
		}
		else
			frame++;

		grid.clearFilledRows();
		grid.paintGrid();
		prop.drawProp();

		_SDL_SetRenderDrawColor(renderer, Colors::RED);
		SDLTest_DrawString(renderer, TILE_SIZE * (GRID_WIDTH + 2) + 10, 10, "Score: ");
		SDLTest_DrawString(renderer, TILE_SIZE * (GRID_WIDTH + 2) + 10, 20, std::to_string(grid.score).c_str());

		if (game_end)
			SDLTest_DrawString(renderer, TILE_SIZE * (GRID_WIDTH + 2) + 10, 30, "Game over!");

		SDL_Delay(50/3);
		SDL_RenderPresent(renderer);
	}
	return 0;
}