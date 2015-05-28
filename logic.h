#ifndef LOGIC_H0.9
#define LOGIC_H


#include <vector>
#include <math.h>  

struct Segment {
	Segment(int index, int color);
	int color;
	int tile;
	const float * vertices;
};
struct Figure {
	Figure();
	int size();
	std::vector<Segment*> segments;


	int * occupiedTiles;
	//const float * vertices;
	//int verticesNum;
private:
	void generateSegments(int verNum, int segsIndicator, int color);
};

const float A[] = { 0.0f, -0.1f, 0.1f, -0.1f, 0.1f, 0.0f, 0.0f, 0.0f };
const float B[] = { 0.1f, -0.1f, 0.2f, -0.1f, 0.2f, 0.0f, 0.1f, 0.0f };
const float C[] = { 0.0f, -0.2f, 0.1f, -0.2f, 0.1f, -0.1f, 0.0f, -0.1f };
const float D[] = { 0.1f, -0.2f, 0.2f, -0.2f, 0.2f, -0.1f, 0.1f, -0.1f };
const float E[] = { 0.0f, -0.3f, 0.1f, -0.3f, 0.1f, -0.2f, 0.0f, -0.2f };
const float F[] = { 0.1f, -0.3f, 0.2f, -0.3f, 0.2f, -0.2f, 0.1f, -0.2f };
const float G[] = { 0.0f, -0.4f, 0.1f, -0.4f, 0.1f, -0.3f, 0.0f, -0.3f};

const float SEGS[7][8] = { 
	{ 0.0f, -0.1f, 0.1f, -0.1f, 0.1f, 0.0f, 0.0f, 0.0f }, //A
	{ 0.1f, -0.1f, 0.2f, -0.1f, 0.2f, 0.0f, 0.1f, 0.0f }, //B
	{ 0.0f, -0.2f, 0.1f, -0.2f, 0.1f, -0.1f, 0.0f, -0.1f }, //C
	{ 0.1f, -0.2f, 0.2f, -0.2f, 0.2f, -0.1f, 0.1f, -0.1f }, //D
	{ 0.0f, -0.3f, 0.1f, -0.3f, 0.1f, -0.2f, 0.0f, -0.2f }, //E
	{ 0.1f, -0.3f, 0.2f, -0.3f, 0.2f, -0.2f, 0.1f, -0.2f }, //E
	{ 0.0f, -0.4f, 0.1f, -0.4f, 0.1f, -0.3f, 0.0f, -0.3f } //F
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