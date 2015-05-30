#include <Windows.h>
#include <time.h>

#include "logic.h"
#include <iostream>

int flag = true;
Figure * fig;
void keyboard(unsigned char key, int x, int y)
{
	//if (key == 't') vertexArray = !vertexArray;
	glutPostRedisplay();
}

void init(){
	fig = FigFactory::newFigure();
	Game::getInstance().addFig(fig);
}

void board(){
	glPushMatrix();
		//glTranslatef(-0.4, 0, 0);
		//glScalef(scale, scale, 1);
		glColor4f(1, 0, 0, 1);
		glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, BOARD);
			glDrawArrays(GL_QUADS, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

void figures() {
	glPushMatrix();
	//glTranslatef(-0.33, 0, 0);
	//glScalef(scale, scale, 1);
	glColor4f(1, 1, 0, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	for (int i = 0; i < fig->size(); ++i){
		glVertexPointer(2, GL_FLOAT, 0, fig->segments[i]->vertices);
		glDrawArrays(GL_QUADS, 0, 4);
	}
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}
void display() {
	if (fig==NULL){
		fig = FigFactory::newFigure();
		Game::getInstance().addFig(fig);
	}

	glClearColor(0.0, 0.3, 0.3, 0.3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	board();
	Game::getInstance().drawFigures();
	//figures();
	
	glFlush();//
	glutSwapBuffers();
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
		std::cout << "Pressed left key.\n";
		fig->left();
		glutPostRedisplay();
		break;
	
	case(101) ://up key	
		//if (mBoard.isPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.tetroType, mGame.mRotation))
		//	mGame.mPosX--;
		glutPostRedisplay();
		break;
	case(102) ://right key
		//if (mBoard.isPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.tetroType, mGame.mRotation))
		//	mGame.mPosX++;
		std::cout << "Pressed right key.\n";
		fig->right();
		glutPostRedisplay();
		break;
	case(103) ://down key

		//if (mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.tetroType, mGame.mRotation))
		//mGame.mPosY++;
		std::cout << "Pressed down key.\n";
		fig->down();
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
	glutInitWindowSize(800, 800);
	glutCreateWindow("Tetris - GKOM, Katarzyna Stepek");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrowKeyPressed);
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
	return 0;
}