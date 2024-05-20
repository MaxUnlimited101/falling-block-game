#include "Props.h"

Grid::Grid(SDL_Renderer* renderer)
{
	score = 0;
	this->renderer = renderer;
	for (size_t i = 0; i < GRID_WIDTH + 2; i++)
	{
		grid[0][i] = Colors::LIGHT_GREY;
		grid[GRID_HEIGHT + 1][i] = Colors::LIGHT_GREY;
	}
	for (size_t i = 0; i < GRID_HEIGHT + 2; i++)
	{
		grid[i][0] = Colors::LIGHT_GREY;
		grid[i][GRID_WIDTH + 1] = Colors::LIGHT_GREY;
	}
	for (size_t i = 1; i < GRID_HEIGHT + 1; i++)
	{
		for (size_t j = 1; j < GRID_WIDTH + 1; j++)
		{
			grid[i][j] = SDL_Color();
			grid[i][j] = Colors::BLACK;
		}
	}
}

void Grid::paintGrid()
{
	//background 
	_SDL_SetRenderDrawColor(renderer, Colors::BLACK);
	SDL_RenderClear(renderer);

	// grid drawing
	for (size_t i = 0; i < GRID_HEIGHT + 2; i++)
	{
		for (size_t j = 0; j < GRID_WIDTH + 2; j++)
		{
			drawTile(renderer, (int)i, (int)j, grid[i][j]);
		}
	}
}

int _SDL_SetRenderDrawColor(SDL_Renderer* renderer, SDL_Color color)
{
	return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

bool operator==(const SDL_Color& l, const SDL_Color& r)
{
	return l.r == r.r && l.g == r.g && l.b == r.b && l.a == r.a;
}

void drawThickRectangle(SDL_Renderer* renderer, int x, int y, int w, int h, int thickness)
{
	SDL_Rect rect;
	// thick upper line
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = thickness;
	SDL_RenderFillRect(renderer, &rect);
	// thick lower line
	rect.x = x;
	rect.y = y + h - thickness;
	rect.w = w;
	rect.h = thickness;
	SDL_RenderFillRect(renderer, &rect);
	// thick left line
	rect.x = x;
	rect.y = y;
	rect.w = thickness;
	rect.h = h;
	SDL_RenderFillRect(renderer, &rect);
	// thick right line
	rect.x = x + w - thickness;
	rect.y = y;
	rect.w = thickness;
	rect.h = h;
	SDL_RenderFillRect(renderer, &rect);
}

Prop::Prop(SDL_Renderer* renderer, int type) // TODO: fix mess with grid_x and grid_y
{
	destroyed = 0;
	this->renderer = renderer;
	for (size_t i = 0; i < PROP_LAYOUT_SIZE; i++)
		for (size_t j = 0; j < PROP_LAYOUT_SIZE; j++)
			layout[i][j] = 0;
	prop_type = (PropTypes)type;
	switch (prop_type)
	{
	case I:
		layout[1][0] = 1;
		layout[1][1] = 1;
		layout[1][2] = 1;
		layout[1][3] = 1;
		color = Colors::LIGHT_BLUE; 
		grid_x = 0;
		grid_y = 1;
		break;
	case J:
		layout[0][0] = 1;
		layout[1][0] = 1;
		layout[1][1] = 1;
		layout[1][2] = 1;
		color = Colors::BLUE;
		grid_x = 0;
		grid_y = 0;
		break;
	case L:
		layout[0][2] = 1;
		layout[1][0] = 1;
		layout[1][1] = 1;
		layout[1][2] = 1;
		color = Colors::ORANGE;
		grid_x = 0;
		grid_y = 0;
		break;
	case O:
		layout[0][1] = 1;
		layout[0][2] = 1;
		layout[1][1] = 1;
		layout[1][2] = 1;
		color = Colors::YELLOW;
		grid_x = 1;
		grid_y = 0;
		break;
	case S:
		layout[0][1] = 1;
		layout[0][2] = 1;
		layout[1][0] = 1;
		layout[1][1] = 1;
		color = Colors::LIGHT_GREEN;
		grid_x = 0;
		grid_y = 0;
		break;
	case T:
		layout[0][1] = 1;
		layout[1][0] = 1;
		layout[1][1] = 1;
		layout[1][2] = 1;
		color = Colors::PURPLE;
		grid_x = 0;
		grid_y = 0;
		break;
	case Z:
		layout[0][0] = 1;
		layout[0][1] = 1;
		layout[1][1] = 1;
		layout[1][2] = 1;
		color = Colors::RED;
		grid_x = 0;
		grid_y = 0;
		break;
	default:
		throw std::exception("Unknown layout of a prop!");
		break;
	}
	grid_x = 0;
	grid_y = 0;
}

void Prop::drawProp()
{
	for (size_t i = 0; i < PROP_LAYOUT_SIZE; i++)
	{
		for (size_t j = 0; j < PROP_LAYOUT_SIZE; j++)
		{
			if (layout[i][j])
			{
				drawTile(renderer, grid_y + (int)i + 1, grid_x + (int)j + 1, color);
			}
		}
	}
}

void drawTile(SDL_Renderer* renderer, int i, int j, SDL_Color tile_color)
{
	SDL_Rect tile{};
	tile.x = (int)j * TILE_SIZE;
	tile.y = (int)i * TILE_SIZE;
	tile.w = TILE_SIZE;
	tile.h = TILE_SIZE;
	_SDL_SetRenderDrawColor(renderer, tile_color);
	SDL_RenderFillRect(renderer, &tile);
	if (tile_color == Colors::LIGHT_GREY)
		_SDL_SetRenderDrawColor(renderer, Colors::GREY);
	else if (tile_color == Colors::LIGHT_BLUE)
		_SDL_SetRenderDrawColor(renderer, Colors::BORDER_LIGHT_BLUE);
	else if (tile_color == Colors::BLUE)
		_SDL_SetRenderDrawColor(renderer, Colors::BORDER_BLUE);
	else if (tile_color == Colors::ORANGE)
		_SDL_SetRenderDrawColor(renderer, Colors::BORDER_ORANGE);
	else if (tile_color == Colors::YELLOW)
		_SDL_SetRenderDrawColor(renderer, Colors::BORDER_YELLOW);
	else if (tile_color == Colors::LIGHT_GREEN)
		_SDL_SetRenderDrawColor(renderer, Colors::BORDER_LIGHT_GREEN);
	else if (tile_color == Colors::PURPLE)
		_SDL_SetRenderDrawColor(renderer, Colors::BORDER_PURPLE);
	else if (tile_color == Colors::RED)
		_SDL_SetRenderDrawColor(renderer, Colors::BORDER_RED);
	else
		_SDL_SetRenderDrawColor(renderer, Colors::BLACK);
	drawThickRectangle(renderer, tile.x, tile.y, tile.w, tile.h, 5);
}

void Prop::destroy()
{
	destroyed = 1;
	for (size_t i = 0; i < PROP_LAYOUT_SIZE; i++)
		for (size_t j = 0; j < PROP_LAYOUT_SIZE; j++)
			layout[i][j] = 0;
}

void Prop::rotate90()
{
	if (prop_type == O)
		return;
	if (prop_type == I)
	{
		rotate90Clockwise(layout, PROP_LAYOUT_SIZE);
		return;
	}
	rotate90Clockwise(layout, PROP_LAYOUT_SIZE - 1);
}

// Function to rotate the matrix 90 degree clockwise
void rotate90Clockwise(int a[PROP_LAYOUT_SIZE][PROP_LAYOUT_SIZE], int N)
{

	// Traverse each cycle
	for (int i = 0; i < N / 2; i++) {
		for (int j = i; j < N - i - 1; j++) {

			// Swap elements of each cycle
			// in clockwise direction
			int temp = a[i][j];
			a[i][j] = a[N - 1 - j][i];
			a[N - 1 - j][i] = a[N - 1 - i][N - 1 - j];
			a[N - 1 - i][N - 1 - j] = a[j][N - 1 - i];
			a[j][N - 1 - i] = temp;
		}
	}
}

int Grid::checkPropCollisionDown(Prop& prop)
{
	int res = 0;
	int save_to_grid = 0;
	int exit_loop = 0;
	for (size_t i = 0; (i < PROP_LAYOUT_SIZE) && !exit_loop; i++)
	{
		for (size_t j = 0; j < PROP_LAYOUT_SIZE; j++)
		{
			if (prop.layout[i][j])
			{
				if (!(grid[i + prop.grid_y + 2][j + prop.grid_x + 1] == Colors::BLACK))
				{
					// prop can't go further down
					// we have to save it to the grid
					save_to_grid = 1;
					exit_loop = 1;
					res = 1;
					break;
				}
			}
		}
	}
	if (!save_to_grid)
		return res;
	for (size_t i = 0; (i < PROP_LAYOUT_SIZE); i++)
	{
		for (size_t j = 0; j < PROP_LAYOUT_SIZE; j++)
		{
			if (prop.layout[i][j])
			{
				grid[i + prop.grid_y + 1][j + prop.grid_x + 1] = prop.color;
			}
		}
	}
	prop.destroy();
	return res;
}

int Grid::checkPropCollisionLeft(Prop& prop)
{
	for (size_t i = 0; (i < PROP_LAYOUT_SIZE); i++)
	{
		for (size_t j = 0; j < PROP_LAYOUT_SIZE; j++)
		{
			if (prop.layout[i][j])
			{
				if (!(grid[i + prop.grid_y + 1][j + prop.grid_x] == Colors::BLACK))
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

int Grid::checkPropCollisionRight(Prop& prop)
{
	for (size_t i = 0; (i < PROP_LAYOUT_SIZE); i++)
	{
		for (size_t j = 0; j < PROP_LAYOUT_SIZE; j++)
		{
			if (prop.layout[i][j])
			{
				if (!(grid[i + prop.grid_y + 1][j + prop.grid_x + 2] == Colors::BLACK))
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

void Grid::clearFilledRows()
{
	int should_clear = 1;
	for (size_t i = 1; i < GRID_HEIGHT + 1; i++)
	{
		for (size_t j = 1; j < GRID_WIDTH + 1; j++)
		{
			if (grid[i][j] == Colors::BLACK)
			{
				should_clear = 0;
				break;
			}
		}
		// clear the row
		if (should_clear)
		{
			score++;
			for (size_t k = i; k > 1; k--)
			{
				for (size_t j = 1; j < GRID_WIDTH + 1; j++)
				{
					if (!(grid[k - 1][j] == Colors::GREY))
					{
						grid[k][j] = grid[k - 1][j];
					}
					else
					{
						grid[k][j] = Colors::BLACK;
					}
				}
			}
		}
		should_clear = 1;
	}
}

int Grid::checkPropCollisionRotate(Prop& prop)
{
	if (prop.prop_type == O)
		return 0;
	int rotated_matrix[PROP_LAYOUT_SIZE][PROP_LAYOUT_SIZE];
	for (size_t i = 0; i < PROP_LAYOUT_SIZE; i++)
	{
		for (size_t j = 0; j < PROP_LAYOUT_SIZE; j++)
		{
			rotated_matrix[i][j] = prop.layout[i][j];
		}
	}
	if (prop.prop_type == I)
		rotate90Clockwise(rotated_matrix, PROP_LAYOUT_SIZE);
	else
		rotate90Clockwise(rotated_matrix, PROP_LAYOUT_SIZE - 1);

	for (size_t i = 0; (i < PROP_LAYOUT_SIZE); i++)
	{
		for (size_t j = 0; j < PROP_LAYOUT_SIZE; j++)
		{
			if (rotated_matrix[i][j])
			{
				if ((j + prop.grid_x + 1 <= 0) || (j + prop.grid_x + 1 >= GRID_WIDTH + 1))
					return 1;
				if ((i + prop.grid_y + 1 <= 0) || (i + prop.grid_y + 1 >= GRID_HEIGHT + 1))
					return 1;
			}
		}
	}
	return 0;
}