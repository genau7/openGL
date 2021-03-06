﻿#include <Windows.h>
#include <time.h>

#include "logic.h"
#include "UIclasses.h"
#include <iostream>
#include <string>
//#include <GL/freeglut.h>

GLuint tex;


//Screen constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int SCREEN_FPS = 60;

Button MyButton = { 5, 5, 100, 25, "Button"};
int flag = true;
Figure * fig = NULL;
int temp = 0;

float pixels[] = {
	0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
};
float texi2[] = {
	0.f, 0.f,
	1.f, 0.f,
	1.f, 1.f,
	0.f, 1.f,
};

float  const vers[] = {
	-0.5f, 0.5f,  // Top-left
	0.5f, 0.5f, // Top-right
	0.5f, -0.5f,// Bottom-right
	-0.5f, -0.5f
};

float vertices[] = {
	//  Position      Color             Texcoords
	-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
	-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
};


void keyboard(unsigned char key, int x, int y)
{
	//if (key == 't') vertexArray = !vertexArray;
	glutPostRedisplay();
}

void init(){
	glClearColor(0.0, 0.3, 0.3, 0.3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}

void Font(void *font, char *text, int x, int y) {
	glRasterPos2i(x, y);
	while (*text != '\0')	{
		glutBitmapCharacter(font, *text);
		++text;
	}
}

void board(){
	glTranslatef(-0.3f, 0.0f, 0);
	glColor4f(0, 0, 0, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, BOARD);
		glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void ButtonDraw(Button *b) {
	int fontx = 100;
	int fonty=200;

	if (b)	{
		glColor3f(0.6f, 0.6f, 0.6f);

		/*
		*	draw background for the button.
		*/
		glBegin(GL_QUADS);
		glVertex2i(b->x, b->y);
		glVertex2i(b->x, b->y + b->h);
		glVertex2i(b->x + b->w, b->y + b->h);
		glVertex2i(b->x + b->w, b->y);
		glEnd();

		/*
		*	Draw an outline around the button with width 3
		*/
		glLineWidth(3);

		glColor3f(0.8f, 0.8f, 0.8f);

		glBegin(GL_LINE_STRIP);
		glVertex2i(b->x + b->w, b->y);
		glVertex2i(b->x, b->y);
		glVertex2i(b->x, b->y + b->h);
		glEnd();

		glColor3f(0.4f, 0.4f, 0.4f);

		glBegin(GL_LINE_STRIP);
		glVertex2i(b->x, b->y + b->h);
		glVertex2i(b->x + b->w, b->y + b->h);
		glVertex2i(b->x + b->w, b->y);
		glEnd();
		glLineWidth(1);
		//glColor3f(1, 1, 1);
		//Font(GLUT_BITMAP_HELVETICA_10, b->label, fontx, fonty);
	}
}

void BitmapText(char *str, float wcx, float wcy){
	glRasterPos2f(wcx, wcy);
	for (int i = 0; str[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
}


void printGameOver(float wcx, float wcy){
	char* str = "GAME OVER";

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.0f,0.75f);

	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(0, SCREEN_HEIGHT);
	glVertex2i(SCREEN_WIDTH, SCREEN_HEIGHT);
	glVertex2i(SCREEN_WIDTH, 0);
	glEnd();

	glPopMatrix();
	glDisable(GL_BLEND);
	
	glColor3f(1, 1, 1);

	Font(GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER", 400-60, 400-70);
	
}

void printStats(){
	Game &game = Game::getInstance();
	glColor3f(1, 1, 1);
	char msg[100];

	sprintf_s(msg, " Level: %d", game.level);
	BitmapText(msg, 0.5, 0.85);

	sprintf_s(msg, "Score: %d", game.score);
	BitmapText(msg, 0.5, 0.75);

	//sprintf_s(msg, "Nest Figure:");
	BitmapText("Next Figure:", 0.47, 0.57);
}

void printNext(){
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.35, 0.52, 0);
	glColor4f(0, 0, 0, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, NEXT);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();

	glTranslatef(1, -0.55, 0);
	Game::getInstance().nextFig->draw();
}
void printInfo(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
	glPushMatrix();
	glScalef(0.6, 0.5, 0);
	glTranslatef(1, 0.95, 0);
	glColor4f(0, 0, 0, 0.3);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, BOARD);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
	glDisable(GL_BLEND);
	printStats();
	printNext();
}

void display() {
	Game &game = Game::getInstance();
	bool canMove = !game.gameOver;
	


	if (game.timeForNewFigure){

		//game.addFig(fig);
		game.switchToNewFig();


	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(0.98, 0.98, 0);
	board();

	glEnable(GL_TEXTURE_2D);
	game.drawFigures();


	printInfo();
	glDisable(GL_TEXTURE_2D);

	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	ButtonDraw(&MyButton);*/

	if (canMove){
		game.refresh();
		if (game.timeToMove())
			game.currentFig->down();
		
	}

	if (!canMove){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		printGameOver(0.5, 0.85);
	}

	glFlush();//
	glutSwapBuffers();
	glutPostRedisplay();//
	
}

void reshape(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;
	GLfloat aspect = (GLfloat)w / (GLfloat)h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);  //
	glLoadIdentity();

	if (w >= h) 
		// aspect >= 1, set the height from -1 to 1, with larger width
		gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);	
	else 
		// aspect < 1, set the width to -1 to 1, with larger height
		gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
	
}


void arrowKeyPressed(int _key, int x, int y) {
	fig = Game::getInstance().currentFig;
	switch (_key)	{
	case(100) ://left key	
		fig->toSide(-1);
		glutPostRedisplay();
		break;
	
	case(101) ://up key	
		fig->rotate();
		glutPostRedisplay();
		break;
	case(102) ://right key
		fig->toSide(1);

		glutPostRedisplay();
		break;
	case(103) ://down key
		fig->down();
		glutPostRedisplay();
		break;
	}
}


void MouseButton(int button, int state, int x, int y) {
	
	//has the button been pressed or released?
	if (state == GLUT_DOWN)	{
		switch (button)		{
		case GLUT_LEFT_BUTTON:
			//printf("left ");
			break;
		case GLUT_MIDDLE_BUTTON:
			//printf("middle ");
			break;
		case GLUT_RIGHT_BUTTON:
			//printf("right ");
			break;
		}
		//printf("button pressed at (%d,%d)\n", x, y);
	}
	else{
		switch (button) 		{
		case GLUT_LEFT_BUTTON:
			//printf("left ");
			break;
		case GLUT_MIDDLE_BUTTON:
			//printf("middle ");
			break;
		case GLUT_RIGHT_BUTTON:
			//printf("right ");
			break;
		}
		//printf("button released at (%d,%d)\n", x, y);
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);//alpha
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Tetris - GKOM, Katarzyna Stepek");
	glutDisplayFunc(display);
	glutMouseFunc(MouseButton);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrowKeyPressed);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	loadMedia(Game::getInstance().myTex);
	init();
	glutMainLoop();
	return 0;
}