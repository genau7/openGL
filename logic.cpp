/**
* \file statki.cpp
* \brief the C++ file with statki library
*/

#include "logic.h"
#include <iostream>
#include <cstdlib>     /* srand, rand */
#include <ctime>

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

Segment::Segment(int index) {
	vertices = SEGS[index];
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
	srand(time(NULL));
	dx = dy = 0; 
	angle = 0.0f;
	dTile = 0;
	colorIndex = rand() % colorsNum;

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
	std::cout << "dTile="<<dTile<<"  dx="<<dx<<", dy="<<dy<<std::endl;
}
void Figure::generateSegments(int segsIndicator){
	Segment * seg;
	int segNum = 4;
	int div = 1000;
	for (int i = 0; i < segNum; i++){
		int index = segsIndicator / div;
		seg = new Segment(index);
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
		segments.pop_front();
		seg = new Segment(index);
		seg->move(dTile);
		segsCode = segsCode%div;
		segments.push_back(seg);
		div /= 10;
	}
}

void Figure::fixRotation(){
	//move to left if out of bounds on right
	if (dTile%boardWidthTiles!=0)
		while (outOfBoundsX(0))
			move(-1);
	
	//move up if out of bounds on the bottom
	while (outOfBoundsY(0))
		move(boardWidthTiles);
	
	bool collision = true;
	int buff = 0;
	while (collision){
		collision = willCollide(0);
		//react to collision down
		if (collision)
			move(boardWidthTiles);
		else
			return;

		//react to collision right
		collision = willCollide(0);
		if (collision)
			move(-1);
		else
			return;
		
		++buff;
		if (buff > 4)
			break;
	}
		//toSide(boardWidthTiles);
	
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
bool Figure::outOfBoundsX(int increment){
	int row = segments[0]->tile / boardWidthTiles;
	for (int i = 0; i < size(); ++i){
		int tile = segments[i]->tile;
		if (increment == 0)
			if (tile % 10 == 0)
				return true;
		if (tile / boardWidthTiles != (tile + increment) / boardWidthTiles)
			return true;
	}
	return false;
}

bool Figure::outOfBoundsY(int increment){
	for (int i = 0; i < size(); ++i){
		int tile = segments[i]->tile;
		if (tile + increment <0) //or >190
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

void Figure::move(int increment){
	for (int i = 0; i < size(); ++i)
		segments[i]->move(increment);
	dTile += increment;
	int row = (initTile + dTile) / boardWidthTiles;
	int col = (initTile + dTile) % boardWidthTiles;
	dx = col*0.1f;

	//19 is tehe index of the upper most lineon board
	dy = (19-row)*-0.1f;
}
void Figure::down(){
	if (willCollide(-boardWidthTiles) || outOfBoundsY(-boardWidthTiles)){
		stopMoving();	
		return;
	}
	move(-boardWidthTiles);

	//dTile += -boardWidthTiles;
	//dy -= 0.1f;
}

void Figure::toSide(int increment){
	if (outOfBoundsX(increment))
		return;
	if (willCollide(increment)){
		stopMoving();
		return;
	}
	move(increment);

	//dTile += increment;
	//dx += increment*0.1f;
}

void Figure::draw(){
	float r = colors[colorIndex][0];
	float g = colors[colorIndex][1];
	float b = colors[colorIndex][2];
	glPushMatrix();
	glTranslatef(dx, dy, 0);
	glTranslatef(-0.5f, 1.0f, 0);
	//glRotatef(angle, 0, 0, 1);
	
	//glColor4f(1, 1, 0, 1);
	glColor3f(r,g,b);

	glEnableClientState(GL_VERTEX_ARRAY);

	for (int i = 0; i < size(); ++i){
		glVertexPointer(2, GL_FLOAT, 0, segments[i]->vertices);
		glDrawArrays(GL_QUADS, 0, 4);

	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}



//-------------------------------------------------Fig Factory------------------------

Figure* FigFactory::newFigure(){
	int figureType = rand() % 5;
	int verticesNum;
	switch (figureType){
	case 0:
		return new FigSquare; 
		break;
	case 1:
		return new FigS; 
		break;
	case 2:
		return new FigStrip;
		break;
	case 3:
		return new FigT; 
		break;
	case 4:
		return new FigL; 
		break;
	}
}

FigSquare::FigSquare( ){
	generateSegments(134);
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

FigS::FigS(){
	generateSegments(1234);
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
	fixRotation();
}

FigStrip::FigStrip(){
	generateSegments(379);
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
	fixRotation();

	/*	bool collsision = Game::getInstance().isTileTaken(tile + increment);
		if (Game::getInstance().isTileTaken(tile + increment))
			return true;*/
	
}

FigT::FigT(){
	generateSegments(124);
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
	fixRotation();
}

FigL::FigL(){
	generateSegments(123);
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
	fixRotation();
}


//----------------------Game-----------------------
Game& Game::getInstance(){
	static Game game;

	return game;
}

Game::Game(){
	gameState = 1; 
	time = 0;
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
