#include <Windows.h>
#include <time.h>

#include "logic.h"
#include <iostream>
#include <string>
//#include <GL/freeglut.h>

GLuint tex;


//Screen constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int SCREEN_FPS = 60;

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

void board(){
	glPushMatrix();
		glColor4f(0, 0, 0, 0);
		glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, BOARD);
			glDrawArrays(GL_QUADS, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

void BitmapText(char *str, float wcx, float wcy){
	glRasterPos2f(wcx, wcy);
	for (int i = 0; str[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
	}
}

void printStats(){
	Game &game = Game::getInstance();
	glColor3f(1, 0, 0);
	char msg[100];
	int level = game.score / 50;
	sprintf_s(msg, "Level: %d", level);
	BitmapText(msg, 0.5, 0.3);

	sprintf_s(msg, "Score: %d", game.score);
	BitmapText(msg, 0.5, 0.2);
}
void display() {	
	Game &game = Game::getInstance();
	if (game.gameOver){
		BitmapText("Game Over", 0.5, 0.5);

	}
	else {
		if (game.timeForNewFigure){
			fig = FigFactory::newFigure();
			game.addFig(fig);
		}

		glClearColor(0.0, 0.3, 0.3, 0.3);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(-0.3f, 0.0f, 0);

		board();

		glEnable(GL_TEXTURE_2D);
			game.drawFigures();
		glDisable(GL_TEXTURE_2D);

		printStats();

		
		game.refreshLines();


		if (game.timeToMove()){
			fig->down();
		}
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
	switch (_key)	{
	case(100) ://left key	
		//if (mBoard.isPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.tetroType, mGame.mRotation))
		//mGame.mPosX--;
		fig->toSide(-1);
		//fig->printPos();
		glutPostRedisplay();
		break;
	
	case(101) ://up key	
		//if (mBoard.isPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.tetroType, mGame.mRotation))
		//	mGame.mPosX--;
		fig->rotate();
		fig->printPos();
		glutPostRedisplay();
		break;
	case(102) ://right key
		//if (mBoard.isPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.tetroType, mGame.mRotation))
		//	mGame.mPosX++;
		fig->toSide(1);
		//fig->printPos();

		glutPostRedisplay();
		break;
	case(103) ://down key

		//if (mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.tetroType, mGame.mRotation))
		//mGame.mPosY++;
		fig->down();
		fig->printPos();
		glutPostRedisplay();
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);//alpha
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Tetris - GKOM, Katarzyna Stepek");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrowKeyPressed);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	loadMedia(Game::getInstance().myTex);
	init();
	glutMainLoop();
	return 0;
}