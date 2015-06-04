#include <Windows.h>
#include <time.h>

#include "logic.h"
#include <iostream>
//#include <GL/freeglut.h>
Texture myTex;

//Screen constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int SCREEN_FPS = 60;

int flag = true;
Figure * fig = NULL;
void keyboard(unsigned char key, int x, int y)
{
	//if (key == 't') vertexArray = !vertexArray;
	glutPostRedisplay();
}

void init(){
	glEnable(GL_TEXTURE_2D);
	//Create OpenGL 2.1 context
	//glutInitContextVersion(2, 1);
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

void display() {
	if (Game::getInstance().timeForNewFigure){
		fig = FigFactory::newFigure();
		Game::getInstance().addFig(fig);
	}

	glClearColor(0.0, 0.3, 0.3, 0.3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	board();


	//glPushMatrix();
	//Render checkerboard texture
	//myTex.render(-0.2, -1);
	//glPopMatrix();



	glLoadIdentity();

	//Move to rendering point
	glTranslatef(-0.2, -1, 0.f);

	//Set texture ID
	int i = myTex.getTextureID();
	//glBindTexture(GL_TEXTURE_2D, myTex.getTextureID());

	


	Game::getInstance().drawFigures();


	

	




	
	glFlush();//
	glutSwapBuffers();
	//std::cout << "\ttime to move\n";
	if (Game::getInstance().timeToMove()){
		//std::cout << "\ttime to move\n";
		Game::getInstance().refreshLines();
		fig->down();
		
	}
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
	loadMedia(myTex);
	init();
	glutMainLoop();
	return 0;
}