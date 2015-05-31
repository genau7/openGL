/**
* \file statki.cpp
* \brief the C++ file with statki library
*/

#include "logic.h"
#include <iostream>

Segment::Segment(int index, int color) {
	vertices = SEGS[index];
	this->color = color;
	this->tile = tileLUT[index];
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
	
}

void Segment::down(){
	tile = tile + boardWidthTiles;		
}

void Segment::toSide(int increment){
	tile += increment;
}

//-------------------------------------Figure--------------------------------

Figure::Figure(){
	dx = dy = 0; 
	angle = 0.0f;
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
void Figure::generateSegments(int verNum, int segsIndicator,int color){
	Segment * seg;
	int div = pow(10, verNum-1);
	for (int i = 0; i < verNum; i++){
		int index = segsIndicator / div;	
		seg = new Segment(index, color);
		segsIndicator = segsIndicator%div;
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
		if (increment < boardWidthTiles)
			if (tile / boardWidthTiles != (tile + increment) / boardWidthTiles)
				return true;

		//for moving down
		if (tile + increment >= 200)
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
	if (willCollide(boardWidthTiles) || willBeOutOfBounds(boardWidthTiles)){
		stopMoving();	
		return;
	}

	for (int i = 0; i < size(); ++i)
		segments[i]->down();
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
		segments[i]->toSide(increment);
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
	glRotatef(angle, 0, 0, 1);
	
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
	int figureType = 2; //random here
	int color = 1; //random here
	int verticesNum;
	switch (figureType){
	case 0:
		return new FigSquare(color); //ABCD square
		break;
	case 1:
		return new FigS(color); //BCDE zigzag
		break;
	case 2:
		return new FigStrip(color); //ACEG strip
		break;
	case 3:
		return new FigT(color); //ACDE T shape
		break;
	case 4:
		return new FigL(color); //ABC L shape
		break;
	}
}

FigSquare::FigSquare(int color){
	generateSegments(4, 123, color);
}

void FigSquare::rotate(){

}

FigS::FigS(int color){
	generateSegments(4, 1234, color);
}

void FigS::rotate(){

}

FigStrip::FigStrip(int color){
	generateSegments(4, 246, color);
}

void FigStrip::rotate(){
	int adjust;
	if (angle == 0){
		xDirRot = 1;
		yDirRot = -10;
		adjust = -1;
	}
	else if (angle == 90){
		xDirRot = -1;
		yDirRot = -10;
		adjust = boardWidthTiles;
	}
	else if (angle == 180){
		xDirRot = -1;
		yDirRot = 10;
		adjust =1;
	}
	else if (angle == 270){
		xDirRot = 1;
		yDirRot = 10;
		adjust = -boardWidthTiles;
	}


	//basic rotate
	for (int i = 1; i <= size(); ++i){
		int & tile = segments[i-1]->tile;
		tile = tile + xDirRot*i + yDirRot*i+adjust;
	}
	angle = (angle + 90) % 360;
	

	/*	bool collsision = Game::getInstance().isTileTaken(tile + increment);
		if (Game::getInstance().isTileTaken(tile + increment))
			return true;*/
	


}

FigT::FigT(int color){
	generateSegments(4, 234, color);
}

void FigT::rotate(){

}

FigL::FigL(int color){
	generateSegments(3, 12, color);
}

void FigL::rotate(){

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