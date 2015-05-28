#include <Windows.h>
#include <time.h>
#include "GLUT.H"
#include <gl\GL.h>
#include "logic.h"

Figure * fig;
void keyboard(unsigned char key, int x, int y)
{
	//if (key == 't') vertexArray = !vertexArray;
	glutPostRedisplay();
}

void init(){
	fig = new Figure;
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

void figure() {
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
	glClearColor(0.0, 0.3, 0.3, 0.3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	board();
	figure();
	
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
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
	return 0;
}