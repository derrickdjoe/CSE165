#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include "Rect.h"

int width = 800;
int height = 800;
int Rectangles = 5;

std::vector<Rect *> rectangles;

void appDrawScene(){

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for(int i = 0; i < Rectangles; i++){

		glColor3f(rectangles[i]->getRed(), rectangles[i]->getGreen(), rectangles[i]->getBlue());
		glRectf(rectangles[i]->getX(), rectangles[i]->getY(), rectangles[i]->getX() + rectangles[i]->getWidth(), rectangles[i]->getY() - rectangles[i]->getHeight());

	}

	glutSwapBuffers();

}

void appMouseFunc(int b, int s, int x, int y){

	float nx = ((float)x / 400 - 1.0);
	float ny = -((float)y / 400 - 1.0);

	if(b == GLUT_LEFT_BUTTON && s == GLUT_DOWN){

		//for(int i = 0; i <= Rectangles - 1; i++){
		for(int i = Rectangles - 1; i >= 0; i--){

			if(rectangles[i]->contains(nx, ny)){
		
				rectangles[i]->set();
				break;

			}

		}

	glutPostRedisplay();

	}

}

void appKeyboardFunc(unsigned char key, int x, int y) {
	// Define what should happen for a given key press 
	switch (key) {
		// Space was pressed. Erase all points
	/*case ' ':
		points.clear();
		break;*/

		// Escape was pressed. Quit the program
	case 27:
		exit(0);
		break;

		// The "r" key was pressed. Set global color to red
	/*case 'r':
		red = 1.0;
		green = 0.0;
		blue = 0.0;
		break;

		// The "g" key was pressed. Set global color to green
	case 'g':
		red = 0.0;
		green = 1.0;
		blue = 0.0;
		break;

		// The "b" key was pressed. Set global color to blue
	case 'b':
		red = 0.0;
		green = 0.0;
		blue = 1.0;
		break;

		// The "k" key was pressed. Set global color to black
	case 'k':
		red = 0.0;
		green = 0.0;
		blue = 0.0;
		break;

		// The "w" key was pressed. Set global color to white
	case 'w':
		red = 1.0;
		green = 1.0;
		blue = 1.0;
		break;*/
	}

	// After all the state changes, redraw the scene
	glutPostRedisplay();
}

int main(int argc, char** argv){

	srand (static_cast <unsigned> (time(0)));

	for(int i = 0; i < Rectangles; i++){
		
		Rect *R = new Rect();
		rectangles.push_back(R);

	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);

	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width, height);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(appDrawScene);

	glutMouseFunc(appMouseFunc);

	glutKeyboardFunc(appKeyboardFunc);

	glutMainLoop();

	return 0;

}
