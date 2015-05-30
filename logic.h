#ifndef LOGIC_H0.9
#define LOGIC_H


#include <vector>
#include<deque>
#include <math.h>  
#include "GLUT.H"
#include <gl\GL.h>

const int boardWidthTiles = 10;
const int boardHeightTiles = 20;


struct Segment {
	Segment(int index, int color);
	bool down();
	bool left();
	bool right();
	int color;//
	int tile;
	const float * vertices;
};

class Figure {
public:
	Figure();
	int size();
	bool down();
	bool left();
	bool right();
	bool rotate();
	void draw();

	int dx;
	int dy;
	float x, y, angle;
	int color;
	std::vector<Segment*> segments;
	int * occupiedTiles;

protected:
	void generateSegments(int verNum, int segsIndicator, int color);
};




class FigSquare : public Figure{
public:
	FigSquare(int color);
};

class FigS : public Figure{
public:
	FigS(int color);
};

class FigStrip : public Figure{
public:
	FigStrip(int color);
};

class FigT : public Figure{
public:
	FigT(int color);
};

class FigL : public Figure{
public:
	FigL(int color);
};



class FigFactory{
public:
	static Figure* newFigure();
};


class Game{
public:
	static Game& getInstance();
	void drawFigures();
	void addFig(Figure* fig);
	//void start();

	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
private:
	Game(){ gameState = 1; }

	std::deque<Figure*> figures;

	//-1 lost, 0 quit, 1 ongoing
	int gameState;
};



const float SEGS[7][8] = { 
	{ 0.0f, -0.1f, 0.1f, -0.1f, 0.1f, 0.0f, 0.0f, 0.0f }, //A
	{ 0.1f, -0.1f, 0.2f, -0.1f, 0.2f, 0.0f, 0.1f, 0.0f }, //B
	{ 0.0f, -0.2f, 0.1f, -0.2f, 0.1f, -0.1f, 0.0f, -0.1f }, //C
	{ 0.1f, -0.2f, 0.2f, -0.2f, 0.2f, -0.1f, 0.1f, -0.1f }, //D
	{ 0.0f, -0.3f, 0.1f, -0.3f, 0.1f, -0.2f, 0.0f, -0.2f }, //E
	{ 0.1f, -0.3f, 0.2f, -0.3f, 0.2f, -0.2f, 0.1f, -0.2f }, //E
	{ 0.0f, -0.4f, 0.1f, -0.4f, 0.1f, -0.3f, 0.0f, -0.3f } //F
};

//nums of tiles for each segment
//						A  B   C   D  E   F   G
const int tileLUT[] = { 0, 1, 10, 11, 20, 21, 30 };

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
const float A[] = { 0.0f, -0.1f, 0.1f, -0.1f, 0.1f, 0.0f, 0.0f, 0.0f };
const float B[] = { 0.1f, -0.1f, 0.2f, -0.1f, 0.2f, 0.0f, 0.1f, 0.0f };
const float C[] = { 0.0f, -0.2f, 0.1f, -0.2f, 0.1f, -0.1f, 0.0f, -0.1f };
const float D[] = { 0.1f, -0.2f, 0.2f, -0.2f, 0.2f, -0.1f, 0.1f, -0.1f };
const float E[] = { 0.0f, -0.3f, 0.1f, -0.3f, 0.1f, -0.2f, 0.0f, -0.2f };
const float F[] = { 0.1f, -0.3f, 0.2f, -0.3f, 0.2f, -0.2f, 0.1f, -0.2f };
const float G[] = { 0.0f, -0.4f, 0.1f, -0.4f, 0.1f, -0.3f, 0.0f, -0.3f};


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


*/
#endif //LOGIC_H