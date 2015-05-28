#ifndef LOGIC_H0.9
#define LOGIC_H


#include <vector>

struct Figure {
	Figure();

	int * occupiedTiles;
	const float * vertices;
	int verticesNum;
};

const float A[] = { 0.0f, -0.1f, 0.1f, -0.1f, 0.1f, 0.0f, 0.0f, 0.0f };
const float B[] = { 0.1f, -0.1f, 0.2f, -0.1f, 0.2f, 0.0f, 0.1f, 0.0f };
const float C[] = { 0.0f, -0.2f, 0.1f, -0.2f, 0.1f, -0.1f, 0.0f, -0.1f };
const float D[] = { 0.1f, -0.2f, 0.2f, -0.2f, 0.2f, -0.1f, 0.1f, -0.1f };
const float E[] = { 0.0f, -0.3f, 0.1f, -0.3f, 0.1f, -0.2f, 0.0f, -0.2f };
const float F[] = { 0.1f, -0.3f, 0.2f, -0.3f, 0.2f, -0.2f, 0.1f, -0.2f };
const float G[] = { 0.0f, -0.4f, 0.1f, -0.4f, 0.1f, -0.3f, 0.0f, -0.3f};

const float ZIGZAG[] = {
	0.0f, -0.3f, 0.1f, -0.3f, 0.1f, -0.2f, 0.0f, -0.2f,
	0.0f, -0.2f, 0.1f, -0.2f, 0.1f, -0.1f, 0.0f, -0.1f,
	0.1f, -0.2f, 0.2f, -0.2f, 0.2f, -0.1f, 0.1f, -0.1f,
	0.1f, -0.1f, 0.2f, -0.1f, 0.2f, 0.0f, 0.1f, 0.0f
};
const float STRIP[] = {
	0.0f, -0.3f, 0.1f, -0.3f, 0.1f, -0.2f, 0.0f, -0.2f,
	0.0f, -0.2f, 0.1f, -0.2f, 0.1f, -0.1f, 0.0f, -0.1f,
	0.1f, -0.2f, 0.2f, -0.2f, 0.2f, -0.1f, 0.1f, -0.1f,
	0.0f, -0.1f, 0.1f, -0.1f, 0.1f, 0.0f, 0.0f, 0.0f
};

const float T[] = {
	0.0f, -0.3f, 0.1f, -0.3f, 0.1f, -0.2f, 0.0f, -0.2f,
	0.0f, -0.2f, 0.1f, -0.2f, 0.1f, -0.1f, 0.0f, -0.1f,
	0.1f, -0.2f, 0.2f, -0.2f, 0.2f, -0.1f, 0.1f, -0.1f,
	0.0f, -0.1f, 0.1f, -0.1f, 0.1f, 0.0f, 0.0f, 0.0f
};

const float L[] = {
	0.0f, -0.2f, 0.1f, -0.2f, 0.1f, -0.1f, 0.0f, -0.1f,
	0.0f, -0.1f, 0.1f, -0.1f, 0.1f, 0.0f, 0.0f, 0.0f,
	0.1f, -0.1f, 0.2f, -0.1f, 0.2f, 0.0f, 0.1f, 0.0f
};


const float SQUARE[] = {
	0.0f, -0.3f, 0.1f, -0.3f, 0.1f, -0.2f, 0.0f, -0.2f,
	0.0f, -0.2f, 0.1f, -0.2f, 0.1f, -0.1f, 0.0f, -0.1f,
	0.1f, -0.2f, 0.2f, -0.2f, 0.2f, -0.1f, 0.1f, -0.1f,
	0.0f, -0.1f, 0.1f, -0.1f, 0.1f, 0.0f, 0.0f, 0.0f
};

const float SQUARE0[] = {
	0.05f, 0.05f,
	-0.05f, 0.05f,
	-0.05f, -0.05f,
	0.05f, -0.05f
};

const float BOARD[]{
	-0.5f, 1,
	-0.5f, -1,
	 0.5f, -1,
	 0.5f, 1
};

const float BOARD_tex[]{
	0.0, 0.0,
		0.0, 1.0, 
		1.0, 1.0,
		1.0, 0,0
};



/*


const float BOARD[]{
-0.3f, 0.3f,
-0.3f, -0.3f,
0.3f, -0.3f,
0.3f, 0.3f
};


class FigStripe : public Figure{
public:
	FigStripe(int color) : color(color){}
private:
	int color;
	static const std::vector<int> vertices;
	static const int rVertices[2][4];
};


class FigSquare : public Figure{
public:
	static const std::vector<int> vertices;
};

class FigL : public Figure{
public:
	static const std::vector<int> vertices;
};


class FigT : public Figure{
public:
	static const std::vector<int> vertices;
};

class FigS : public Figure{
public:
	static const std::vector<int> vertices;
};




//singleton
class FigFactory{
public:
	Figure* createFig(int type, int color);
};
class Game{
public:
	static Game& getInstance();
	void start();

	FigFactory figFactory;
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
private:
	Game(){ gameState = 1; }

	//-1 lost, 0 quit, 1 ongoing
	int gameState;
};

*/
#endif //LOGIC_H