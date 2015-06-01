/**
* \file statki.cpp
* \brief the C++ file with statki library
*/

#include "logic.h"
#include <iostream>

void Segment::getName(int index){
	if (index == 0)
		name = 'A';
	else if (index == 1)
		name = 'B';
	else if (index == 2)
		name = 'C';
	else if (index == 3)
		name = 'D';
	else if (index == 4)
		name = 'E';
	else if (index == 5)
		name = 'F';
	else if (index == 6)
		name = 'G';
	else if (index == 7)
		name = 'H';
	else if (index == 8)
		name = 'I';
	else if (index == 9)
		name = 'J';
	else if (index == 10)
		name = 'K';
	else
		name = 'X';
}

Segment::Segment(int index, int color) {
	vertices = SEGS[index];
	this->color = color;
	this->tile = tileLUT[index];
	getName(index);
	
}

void Segment::move(int increment){
	tile += increment;
}

void Segment::down(){
	tile = tile - boardWidthTiles;		
}

void Segment::toSide(int increment){
	tile += increment;
}

//-------------------------------------Figure--------------------------------

Figure::Figure(){
	dx = dy = 0; 
	angle = 0.0f;
	dTile = 0;
}
int Figure::size(){
	return segments.size();
}

void Figure::printPos(){
	for (int i = 0; i < size(); ++i){
		Segment* seg = segments[i];
		int row = seg->tile / boardWidthTiles;
		int col = seg->tile%boardWidthTiles;
		std::cout << seg->name << "(" << seg->tile / boardWidthTiles << "," << seg->tile%boardWidthTiles << "), ";
	}
	std::cout << std::endl;
}
void Figure::generateSegments(int segsIndicator, int color){
	Segment * seg;
	int segNum = 4;
	int div = 1000;
	for (int i = 0; i < segNum; i++){
		int index = segsIndicator / div;
		seg = new Segment(index, color);
		segsIndicator = segsIndicator%div;
		segments.push_back(seg);
		div /= 10;
	}
}

void Figure::rotateSegments(int segsCode){
	int div = 1000;
	for (int i = 0; i < size(); i++){
		int index = segsCode / div;
		Segment * seg = segments[i];
		int color = seg->color;
		segments.pop_front();
		//delete seg;
		seg = new Segment(index, color);
		seg->move(dTile);
		segsCode = segsCode%div;
		segments.push_back(seg);
		div /= 10;
	}
}

bool Figure::willCollide(int increment){
	for (int i = 0; i < size(); ++i){
		int tile = segments[i]->tile;
		bool collsision = Game::getInstance().isTileTaken(tile + increment);
		if (Game::getInstance().isTileTaken(tile+increment))
			return true;
	}
	return false;
}

bool Figure::willBeOutOfBounds(int increment){
	for (int i = 0; i < size(); ++i){
		int tile = segments[i]->tile;
		//for moving left or right
		if (increment >= -1)
			if (tile / boardWidthTiles != (tile + increment) / boardWidthTiles)
				return true;

		//for moving down
		if (tile + increment <0)
			return true;
	}
	return false;
}

void Figure::stopMoving(){
	Game::getInstance().timeForNewFigure = true;
	for (int i = 0; i < size(); ++i){
		int tile = segments[i]->tile;
		Game::getInstance().occupyTile(tile);
	}
}
void Figure::down(){
	if (willCollide(-boardWidthTiles) || willBeOutOfBounds(-boardWidthTiles)){
		stopMoving();	
		return;
	}

	for (int i = 0; i < size(); ++i)
		segments[i]->move(-boardWidthTiles);
	dTile += -boardWidthTiles;
	dy -= 0.1f;
	
}

void Figure::toSide(int increment){
	if (willBeOutOfBounds(increment))
		return;
	if (willCollide(increment)){
		stopMoving();
		return;
	}

	for (int i = 0; i < size(); ++i)
		segments[i]->move(increment);
	
	dTile += increment;
	dx += increment*0.1f;
}

/*
void Figure::rotate(){
	bool noCollision = true;
//	for (int i = 0; i < size(); ++i){
//		Segment* seg = segments[i];
//		noCollision = noCollision && seg->right();
//	}
	if (noCollision){
		angle=(angle+90)%360;
		//x = dx*0.1f;
	}
}*/

void Figure::draw(){
	glPushMatrix();
	glTranslatef(dx, dy, 0);
	glTranslatef(-0.5f, 1.0f, 0);
	//glRotatef(angle, 0, 0, 1);
	
	glColor4f(1, 1, 0, 1);
	glEnableClientState(GL_VERTEX_ARRAY);

	for (int i = 0; i < size(); ++i){
		glVertexPointer(2, GL_FLOAT, 0, segments[i]->vertices);
		glDrawArrays(GL_QUADS, 0, 4);

	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

void Figure::rotate(){

}

//-------------------------------------------------Fig Factory------------------------

Figure* FigFactory::newFigure(){
	int figureType = 1; //random here
	int color = 1; //random here
	int verticesNum;
	switch (figureType){
	case 0:
		return new FigSquare(color); 
		break;
	case 1:
		return new FigS(color); 
		break;
	case 2:
		return new FigStrip(color);
		break;
	case 3:
		return new FigT(color); 
		break;
	case 4:
		return new FigL(color); 
		break;
	}
}

FigSquare::FigSquare(int color){
	generateSegments(134, color);
}

void FigSquare::rotate(){
	if (angle == 0)
		rotateSegments(4013);
	else if (angle == 90)
		rotateSegments(3401);
	else if (angle == 180)
		rotateSegments(1340);
	else if (angle == 270)
		rotateSegments(134);
	angle = (angle + 90) % 360;
}

FigS::FigS(int color){
	generateSegments(1234, color);
}

void FigS::rotate(){
	if (angle == 0)
		rotateSegments(348);
	else if (angle == 90)
		rotateSegments(4321);
	else if (angle == 180)
		rotateSegments(843);
	else if (angle == 270)
		rotateSegments(1234);
	angle = (angle + 90) % 360;
}

FigStrip::FigStrip(int color){
	generateSegments(379, color);
}

void FigStrip::rotate(){
	if (angle == 0)
		rotateSegments(3456);
	else if (angle == 90)
		rotateSegments(9730);
	else if (angle == 180)
		rotateSegments(6543);
	else if (angle == 270)
		rotateSegments(379);
	angle = (angle + 90) % 360;

	/*	bool collsision = Game::getInstance().isTileTaken(tile + increment);
		if (Game::getInstance().isTileTaken(tile + increment))
			return true;*/
	
}

FigT::FigT(int color){
	generateSegments(124, color);
}

void FigT::rotate(){
	if (angle == 0)
		rotateSegments(1348);
	else if (angle == 90)
		rotateSegments(1345);
	else if (angle == 180)
		rotateSegments(347);
	else if (angle == 270)
		rotateSegments(124);
	angle = (angle + 90) % 360;
}

FigL::FigL(int color){
	generateSegments(123, color);
	//angle
}

void FigL::rotate(){
	if (angle == 0)
		rotateSegments(148);
	else if (angle == 90)
		rotateSegments(345);
	else if (angle == 180)
		rotateSegments(378);
	else if (angle == 270)
		rotateSegments(123);
	angle = (angle + 90) % 360;
}


//----------------------Game-----------------------
Game& Game::getInstance(){
	static Game game;

	return game;
}

Game::Game(){
	gameState = 1; 
	timeForNewFigure = true;
	for (int i = 0; i < boardHeightTiles; ++i){
		for (int j = 0; j < boardWidthTiles; ++j)
			tiles[i][j] = 0;
	}
}

void Game::drawFigures(){
	bool noCollision = true;
	for (int i = 0; i < figures.size(); ++i){
		Figure * fig = figures[i];
		fig->draw();
	}
}

void Game::addFig(Figure* fig){
	figures.push_back(fig);
	timeForNewFigure = false;
}

bool Game::isTileTaken(int tileNum){
	int row = tileNum / boardWidthTiles;
	int col = tileNum%boardWidthTiles;
	int val = tiles[row][col];//
	bool ret = (val == 1);//
	return tiles[row][col]==1;
}

void Game::occupyTile(int tileNum){
	int row = tileNum / boardWidthTiles;
	int col = tileNum%boardWidthTiles;
	tiles[row][col] = 1;
}
/*
const int FigStripe::rVertices[2][4] = { { 0, 1, 1, 0 }, { 0, 0, 4, 4 } };

Figure* FigFactory::createFig(int type, int color){
	if (type == 0)
		return new FigStripe(color);
}



void Game::start(){
	while (gameState == 1){
		std::cout << "I'm playing\t";
	}
}*/