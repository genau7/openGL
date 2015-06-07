/**
* \file statki.cpp
* \brief the C++ file with statki library
*/

#include "logic.h"
#include <iostream>
#include <cstdlib>     /* srand, rand */
#include <ctime>

static int id = 0;


float texi[] = {
	0.f, 0.f,
	1.f, 0.f,
	1.f, 1.f,
	0.f, 1.f,
};



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
	if (Game::getInstance().isTileTaken(tile))
		Game::getInstance().gameOver = true;
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

void Segment::draw(float r, float g, float b){
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, Game::getInstance().myTex.getTextureID());
	//glRotatef(angle, 0, 0, 1);
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glTranslatef(dx, dy, 0);
	//glTranslatef(-0.500005f, 1.0f, 0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);//
			glColor3f(r, g, b);
			glVertexPointer(2, GL_FLOAT, 0, vertices);
			glTexCoordPointer(2, GL_FLOAT, 0, texi);
			glDrawArrays(GL_QUADS, 0, 4);
		
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//glDisableClientState(GL_VERTEX_ARRAY);

	glBindTexture(GL_TEXTURE_2D, NULL);

	glLineWidth(2.50);
	glColor3f(r*1.2, g*1.2, b*1.2);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);//
	glPopMatrix();
}

void Segment::drawBorder(float r, float g, float b){
	glPushMatrix();//
	glEnableClientState(GL_VERTEX_ARRAY);//
	glLineWidth(3.0);
	glColor3f(r*0.8, g*0.8, b*0.8);

	int indices[] = {0,1,2,3,4,5 };
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawElements(GL_LINE_STRIP, 3, GL_UNSIGNED_INT, indices);
	glDisableClientState(GL_VERTEX_ARRAY);//
	glPopMatrix();//

}
//-------------------------------------Figure--------------------------------

Figure::Figure(){
	nr = id;
	id++;
	srand(time(NULL));
	dx = dy = 0; 
	angle = 0.0f;
	dTile = 0;
	colorIndex = rand() % colorsNum;

}
int Figure::size(){
	if (segments.empty())
		return 0;
	return segments.size();
}

void Figure::printPos(){
	for (int i = 0; i < size(); ++i){
		Segment* seg = segments[i];
		int row = seg->tile / boardWidthTiles;
		int col = seg->tile%boardWidthTiles;
		std::cout << seg->name << "(" << seg->tile / boardWidthTiles << "," << seg->tile%boardWidthTiles << "), ";
	}
	std::cout << "dTile="<<dTile<<"  dx="<<dx<<", dy="<<dy<<" Id="<<nr<<std::endl;
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
void Figure::occupyTiles(){
	for (int i = 0; i < size(); ++i){
		int tile = segments[i]->tile;
		Game::getInstance().occupyTile(tile);
	}
}

void Figure::stopMoving(){
	Game::getInstance().timeForNewFigure = true;
	for (int i = 0; i < size(); ++i){
		int tile = segments[i]->tile;
		Game::getInstance().occupyTile(tile);
	}
	//Game::getInstance().refreshLines();
}



void Figure::move(int increment){
	for (int i = 0; i < size(); ++i)
		segments[i]->move(increment);
	dTile += increment;
	int row = (initTile + dTile) / boardWidthTiles;
	int col = (initTile + dTile) % boardWidthTiles;

	//19 is the index of the upper most lineon board
	dy = (19-row)*-0.1f;
	dx = col*0.1f;
	//printPos();
}
void Figure::down(bool isCollapising){
	//bool collision = willCollide(-boardWidthTiles);
	//bool bounds = outOfBoundsY(-boardWidthTiles);
	if (willCollide(-boardWidthTiles) || outOfBoundsY(-boardWidthTiles)){
		if (!isCollapising)
			Game::getInstance().timeForNewFigure = true;
		occupyTiles();
		return;

	}
	move(-boardWidthTiles);
}

void Figure::toSide(int increment){
	if (outOfBoundsX(increment))
		return;
	if (willCollide(increment))
		return;
	move(increment);

	//dTile += increment;
	//dx += increment*0.1f;
}

void Figure::clearLine(int row){
	bool erase = false;
	for (int i = 0; i < size(); ++i){
		Segment * seg = segments[i];
		if (seg->tile / boardWidthTiles == row){
			erase = true;
			//del seg
			Game::getInstance().tiles[row][seg->tile%boardWidthTiles] = 0;
			segments.erase(segments.begin() + i);
			--i;
		}
	}
}

void Figure::draw(){
	float r = colors[colorIndex][0];
	float g = colors[colorIndex][1];
	float b = colors[colorIndex][2];
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, Game::getInstance().myTex.getTextureID());	
			glEnableClientState(GL_VERTEX_ARRAY);
				glTranslatef(dx, dy, 0);
				glTranslatef(-0.500005f, 1.0f, 0);

				for (int i = 0; i < size(); ++i)	
					segments[i]->draw(r,g,b);
				for (int i = 0; i <size(); ++i)
					segments[i]->drawBorder(r, g, b);

			glDisableClientState(GL_VERTEX_ARRAY);
		glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();

}



//-------------------------------------------------Fig Factory------------------------

Figure* FigFactory::newFigure(bool constructor){
	int figureType = rand() % 5;
	if (constructor)
		figureType = (figureType + 1) % 5;
	int verticesNum;
	switch (figureType){
	case 0:
		return new FigSquare; 
		break;
	case 1:
		return  new FigS;
		break;
	case 2:
		return  new FigStrip;
		break;
	case 3:
		return  new FigT;
		break;
	case 4:
		return  new FigL;
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
		rotateSegments(2345);
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

void Game::switchToNewFig(){
	printf("\nentered switch to new field\n");
	if (currentFig!=NULL)
		currentFig->printPos();
	if (nextFig!=NULL)
		nextFig->printPos();

	//nextFig = FigFactory::newFigure();
	//printf("\ngenerated next\n");
	//currentFig->printPos();
	//nextFig->printPos();

	printf("\ncurrent=new\n");
	currentFig = nextFig;
	currentFig->printPos();
	nextFig->printPos();

	printf("\ngenerated next\n");
	figures.push_back(currentFig);
	timeForNewFigure = false;
	nextFig = FigFactory::newFigure();
	currentFig->printPos();
	nextFig->printPos();
	
}

Game::Game(){
	gameState = 1; 
	gameOver = false;
	score = 0;
	level = 1;
	time = 0;
	cycle = 150;


	nextFig = FigFactory::newFigure(true);
	currentFig = FigFactory::newFigure();
	printf("===============================\n");
	printf("Current:"); 	currentFig->printPos(); 

	printf("\nNext:"); 	nextFig->printPos();
	printf("===============================\n");
	figures.push_back(currentFig);


	nextFig = FigFactory::newFigure(true);
	
	//printf("\Constructor:\n");
	//currentFig = nextFig;
	//printf("Current:"); 	currentFig->printPos(); currentFig->printPos();
	//nextFig->printPos();
	//printf("===============================\n");


	timeForNewFigure = false;
	for (int i = 0; i < boardHeightTiles; ++i){
		for (int j = 0; j < boardWidthTiles; ++j)
			tiles[i][j] = 0;
	}
}
void Game::refresh(){
	refreshLines();
	refreshSpeed();
}

void Game::refreshSpeed(){
	if (cycle > 10){
		int newLevel = score / 50 + 1;
		if (level < newLevel){
			level = newLevel;
			cycle -= 10;
		}
		
	}
	
}

void Game::refreshLines(){
	int n = 0;
	for (int row = 0; row < boardHeightTiles; ++row){
		int sum = 0;
		for (int col = 0; col < boardWidthTiles; ++col)
			sum += tiles[row][col];

		//check if a line was formed
		if (sum == boardWidthTiles){
			score += 10;
			n++;//
			if (n == 2)//
				n++;//
			clearLine(row);
			sum = 0;
			lowerFiguresAfterLinesDisappeared(row);
		}
		
	}
}
void Game::clearLine(int row) {
	for (int i = 0; i < figures.size(); ++i){
		figures[i]->clearLine(row);

	}
}
void Game::clearRowsAbove(int r){
	for (int row = r; row < boardHeightTiles; ++row){
		for (int col = 0; col < boardWidthTiles; ++col)
			tiles[row][col] = 0;
	}
}

void Game::lowerFiguresAfterLinesDisappeared(int r){
	clearRowsAbove(r);
	for (int i = 0; i < figures.size(); ++i){
		Figure* fig = figures[i];
		if (fig != currentFig){
			figures[i]->down(true);
			figures[i]->occupyTiles();
		}
		//figures[i]->stopMoving();
	}
}

void Game::drawFigures(){
	//increase time
	if (++time > cycle)
		time = 0;

	bool noCollision = true;
	for (int i = 0; i < figures.size(); ++i){
		Figure * fig = figures[i];
		fig->draw();
	}
}

bool Game::timeToMove(){
	return time == cycle;
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
