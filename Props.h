#ifndef Props_h_
#define Props_h_

#include <SDL.h>
#include <exception>

#define TILE_SIZE 30
#define GRID_WIDTH 10
#define GRID_HEIGHT 20
#define PROPS_COUNT 7
#define PROP_LAYOUT_SIZE 4

bool operator== (const SDL_Color& l, const SDL_Color& r);

namespace Colors
{
	constexpr SDL_Color RED = { 240, 0, 0, 255 }; // 240 0 0
	constexpr SDL_Color BORDER_RED = { 180, 0, 0, 255 }; // 180 0 0

	constexpr SDL_Color BLUE = { 0, 0, 240, 255 }; // 0 0 240
	constexpr SDL_Color BORDER_BLUE = { 0, 0, 180, 255 }; // 0 0 180

	constexpr SDL_Color LIGHT_BLUE = { 0, 240, 240, 255 }; // 0 240 240
	constexpr SDL_Color BORDER_LIGHT_BLUE = { 0, 180, 180, 255 }; // 0 180 180

	constexpr SDL_Color LIGHT_GREEN = { 0, 240, 0, 255 }; // 0 240 0
	constexpr SDL_Color BORDER_LIGHT_GREEN = { 0, 180, 0, 255 }; // 0 180 0


	constexpr SDL_Color YELLOW = { 240, 240, 0, 255 }; // 240 240 0
	constexpr SDL_Color BORDER_YELLOW = { 180, 180, 0, 255 }; // 180 180 0

	constexpr SDL_Color ORANGE = { 240, 161, 0, 255 }; // 240 161 0
	constexpr SDL_Color BORDER_ORANGE = { 180, 120, 0, 255 }; // 180 120 0

	constexpr SDL_Color PURPLE = { 161, 0, 240, 255 }; // 161 0 240 
	constexpr SDL_Color BORDER_PURPLE = { 120, 0, 180, 255 }; // 120 0 180 

	constexpr SDL_Color GREY = { 120, 120, 120, 255 }; // 120 120 120
	constexpr SDL_Color LIGHT_GREY = { 200, 200, 200, 255 }; // 120 120 120

	constexpr SDL_Color GREEN = { 0, 240, 0, 255 }; // 0 240 0

	constexpr SDL_Color WHITE = { 255, 255, 255, 255 }; // 255 255 255

	constexpr SDL_Color BLACK = { 0, 0, 0, 255 }; // 0 0 0
	
}

int _SDL_SetRenderDrawColor(SDL_Renderer* renderer, SDL_Color color);
void drawThickRectangle(SDL_Renderer* renderer, int x, int y, int w, int h, int thickness);
void drawTile(SDL_Renderer* renderer, int i, int j, SDL_Color tile_color);
void rotate90Clockwise(int a[PROP_LAYOUT_SIZE][PROP_LAYOUT_SIZE], int N);
class Prop;

class Grid
{
public:
	int score;
	Grid(SDL_Renderer* renderer);
	~Grid() = default;
	void paintGrid();
	void clearFilledRows();

	// Return 1 if prop was saved to grid
	int checkPropCollisionDown(Prop& prop);

	// Return 1 if can't move to the LEFT, otherwise 0
	int checkPropCollisionLeft(Prop& prop);

	// Return 1 if can't move to the RIGHT, otherwise 0
	int checkPropCollisionRight(Prop& prop);

	// Return 1 if can't ROTATE, otherwise 0
	int checkPropCollisionRotate(Prop& prop);

	// TODO: make a setter for `grid` ???

private:
	SDL_Color grid[GRID_HEIGHT + 2][GRID_WIDTH + 2];
	SDL_Renderer* renderer;
};

enum PropTypes
{
	I, J, L, O, S, T, Z
};


class Prop
{
public:
	int grid_x;
	int grid_y;
	Prop(SDL_Renderer* renderer, int type);
	~Prop() = default;
	void drawProp();
	void destroy();
	void rotate90();
	friend class Grid;
	int destroyed;
private:
	enum PropTypes prop_type;
	SDL_Color color;
	int layout[PROP_LAYOUT_SIZE][PROP_LAYOUT_SIZE];
	SDL_Renderer* renderer;
};

#endif // !Props_h_



