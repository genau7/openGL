/**
* \file statki.cpp
* \brief the C++ file with statki library
*/

#include "logic.h"
#include <iostream>

Figure::Figure(){
	int figureType = 4;

	switch (figureType){
	case 0:
		vertices = SQUARE;
		verticesNum = sizeof(SQUARE) / sizeof(float) / 2;
		break;
	case 1:
		vertices = ZIGZAG;
		verticesNum = sizeof(ZIGZAG) / sizeof(float) / 2;
		break;
	case 2:
		vertices = STRIP;
		verticesNum = sizeof(STRIP) / sizeof(float) / 2;
		break;
	case 3:
		vertices = T;
		verticesNum = sizeof(T) / sizeof(float) / 2;
		break;
	case 4:
		vertices = L;
		verticesNum = sizeof(L) / sizeof(float) / 2;
		break;
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