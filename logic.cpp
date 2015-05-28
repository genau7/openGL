/**
* \file statki.cpp
* \brief the C++ file with statki library
*/

#include "logic.h"
#include <iostream>

Segment::Segment(int index, int color) {
	vertices = SEGS[index];
	this->color = color;
}

Figure::Figure(){
	int figureType = 2; //random here
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

int Figure::size(){
	return segments.size();
}

void Figure::generateSegments(int verNum, int segsIndicator,int color){
	Segment * seg;
	int div = pow(10, verNum-1);
	for (int i = 0; i < verNum; i++){
		int index = segsIndicator / div;	
		seg = new Segment(segsIndicator/div, color);
		segsIndicator = segsIndicator%div;
		segments.push_back(seg);
		div /= 10;
	}

}


/*
const int FigStripe::rVertices[2][4] = { { 0, 1, 1, 0 }, { 0, 0, 4, 4 } };

Figure* FigFactory::createFig(int type, int color){
	if (type == 0)
		return new FigStripe(color);
}

Game& Game::getInstance(){
	static Game game;
	
	return game;
}

void Game::start(){
	while (gameState == 1){
		std::cout << "I'm playing\t";
	}
}*/