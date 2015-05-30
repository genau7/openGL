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
}

bool Segment::down(){
	//TODO check collisions
	if (tile + 1 < 190){
		tile = tile + boardWidthTiles;
		return true;
	}
	return false;
}

bool Segment::left(){
	//TODO check collisions
	if (tile / boardWidthTiles == (tile - 1) / boardWidthTiles){
		tile = tile - 1;
		return true;
	}
	return false;
}

bool Segment::right(){
	//TODO check collisions
	if (tile / boardWidthTiles == (tile + 1) / boardWidthTiles){
		tile = tile + 1;
		return true;
	}
	return false;
}



//-------------------------------------Figure--------------------------------

Figure::Figure(){
	dx = dy = 0; 
	y = x = 0.0f;
	angle = 10.0f;
}
int Figure::size(){
	return segments.size();
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

bool Figure::down(){
	bool noCollision = true;
	for (int i = 0; i < size(); ++i){
		Segment* seg = segments[i];
		noCollision = noCollision && seg->down();
	}
	if (noCollision){
		dy += 1;
		y = -0.1f*dy;
	}
	return noCollision;
	//dy+=1;
}

bool Figure::left(){
	bool noCollision = true;
	for (int i = 0; i < size(); ++i){
		Segment* seg = segments[i];
		noCollision = noCollision && seg->left();
	}

	if (noCollision){
		dx -= 1;
		x = 0.1f*dx;		
	}

	return noCollision;
}

bool Figure::right(){
	bool noCollision = true;
	for (int i = 0; i < size(); ++i){
		Segment* seg = segments[i];
		noCollision = noCollision && seg->right();
	}

	if (noCollision){
		dx += 1;
		x = dx*0.1f;
	}

	return noCollision;
}

void Figure::draw(){
	glPushMatrix();
	//glTranslatef(-0.33, 0, 0);
	//x = -0.5;
	glTranslatef(x, y, 0);
	glTranslatef(-0.5f, 1.0f, 0);
	//glRotatef(angle, 0, 0, 1);
	//glScalef(1, 2, 3);
	glColor4f(1, 1, 0, 1);
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
	int figureType = 3; //random here
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

FigS::FigS(int color){
	generateSegments(4, 1234, color);
}

FigStrip::FigStrip(int color){
	generateSegments(4, 246, color);
}

FigT::FigT(int color){
	generateSegments(4, 234, color);
}

FigL::FigL(int color){
	generateSegments(3, 12, color);
}



//----------------------Game-----------------------
Game& Game::getInstance(){
	static Game game;

	return game;
}

void Game::drawFigures(){
	for (int i = 0; i < figures.size(); ++i){
		Figure * fig = figures[i];
		fig->draw();
	}
}

void Game::addFig(Figure* fig){
	figures.push_back(fig);
}
/*

Figure::Figure(){
int figureType = 3; //random here
int color = 1; //random here
int verticesNum;
switch (figureType){
case 0:
generateSegments(4, 123, color); //ABCD square
break;
case 1:
generateSegments(4, 1234, color); //BCDE zigzag
break;
case 2:
generateSegments(4, 246, color); //ACEG strip
break;
case 3:
generateSegments(4, 234, color); //ACDE T shape
break;
case 4:
generateSegments(3, 12, color); //ABC L shape
break;
}
}


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