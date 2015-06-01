#ifndef LOGIC_H0.9
#define LOGIC_H


#include <vector>
#include<list>
#include<deque>
#include <math.h>  
#include "GLUT.H"
#include <gl\GL.h>
#include "Segment.h"

const int boardWidthTiles = 10;
const int boardHeightTiles = 20;
const int COLLISION = -1;
const int OUT_OF_BOUNDS = 0;
const int OK = 1;


struct Segment {
	Segment(int index, int color);
	void down();
	void toSide(int increment);
	void getName(int index);
	int color;//
	int tile;
	const float * vertices;
	char name;
};

class Figure {
public:
	Figure();
	int size();
	void down();
	void toSide(int increment);
	void left();
	void right();
	virtual void rotate();
	void draw();
	bool willCollide(int increment);
	bool willBeOutOfBounds(int increment);
	void stopMoving();
	void printPos();

	float dx, dy;
	int angle;
	int color;
	std::vector<Segment*> segments;
	//int * occupiedTiles;

protected:
	void generateSegments(int segsIndicator, int color);
	int xDirRot;
	int yDirRot;
};




class FigSquare : public Figure{
public:
	FigSquare(int color);
	virtual void rotate();
};

class FigS : public Figure{
public:
	FigS(int color);
	virtual void rotate();
};

class FigStrip : public Figure{
public:
	FigStrip(int color);
	virtual void rotate();
	
};

class FigT : public Figure{
public:
	FigT(int color);
	virtual void rotate();
};

class FigL : public Figure{
public:
	FigL(int color);
	virtual void rotate();
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
	bool isTileTaken(int tileNum);
	bool timeForNewFigure;
	void occupyTile(int tileNum);
	
	

	int tiles[boardHeightTiles][boardWidthTiles];
	std::list<int>takenTiles;
	//void start();

	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
private:
	Game();

	std::deque<Figure*> figures;

	//-1 lost, 0 quit, 1 ongoing
	int gameState;
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