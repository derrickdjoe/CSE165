#include "GlutApp.h"
#include "Img.h"
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

Img objArr[10];
int Width = 800;
int Height = 600;

// Make this static so that it will not be accessible in other source files
static GlutApp* app;

GlutApp::GlutApp(const char* label, int x, int y, int w, int h) {
    // Set app pointer to be the current object
    app = this;
    
    // Setup window position, size, and title
    glutInitWindowPosition(x, y);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Proj 4");
    
	srand(time(NULL));
	
	for(int i = 0; i < 10; i++){

		objArr[i].setPos(pose2D(rand() % 100 / (float)100, rand() % 100 / (float)100));
		objArr[i].loadTextures();

	}

    
    // Setup GLUT callbacks for different events
    glutDisplayFunc(displayCB);
    glutMouseFunc(mouseCB);
    glutKeyboardFunc(keyboardCB);
    glutIdleFunc(idleCB);
    glutReshapeFunc(reshapeCB);
    glutPassiveMotionFunc(passiveCB);
	run();
}

void GlutApp::windowToScene ( float& x, float &y )
{
    // Converting window coordinates [0..width] x [0..height] to [-1..1] x [-1..1]
    x = (2.0f*(x/float(width))) - 1.0f;
    y = 1.0f - (2.0f*(y/float(height)));
	// Take care of issue in Windows where y coordinate is a little off
	#if defined WIN32
	y -= 0.03;
	#endif
}

void GlutApp::draw(){

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(int i = 0; i < 10; i++){

		objArr[i].display();

	}

	glutSwapBuffers();

}

void GlutApp::resize ( int w, int h ) {
  	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0, 1, 0 , 1);
	glMatrixMode(GL_MODELVIEW);

}

void GlutApp::keyPress(unsigned char key){
    // Exit the application when any key is pressed
    exit(0);
}

void GlutApp::run() {
    // Run the main loop
    glutMainLoop();
}

void GlutApp::redraw() {
    // Redraw the display
    glutPostRedisplay();
}


void GlutApp::displayCB(){
    // When GLUT needs to redraw itself, call our draw method
    app->draw();
}

void GlutApp::reshapeCB(int w, int h){
    // When the window is resized, call our resize method
    app->resize(w, h);
}

void GlutApp::idleCB(){

	glutPostRedisplay();

	for(int i = 0; i < 10; i++){

		objArr[i].animate();

	}
}


void GlutApp::mouseCB(int b, int s, int x, int y){

	if(b == GLUT_LEFT_BUTTON && s == GLUT_UP){

		for(int i = 10; i >= 0; i--){

			if(!objArr[i].isFinished() && objArr[i].isIn(pose2D(float(x)/Width, float(1.0) - float(y)/Height))){

				objArr[i].changeState();
				break;

			}

		}

	}

}

void GlutApp::motionCB(int x, int y){
    // Convert mouse position to scene coordinates
    float mx = (float) x;
    float my = (float) y;
    app->windowToScene(mx, my);
    
    // Call drag handler
    app->mouseDrag(mx, my);
}

void GlutApp::passiveCB (int x, int y){
    // Convert mouse position to scene coordinates
    float mx = (float) x;
    float my = (float) y;
    app->windowToScene(mx, my);
    
    // Call mouse motion handler
    app->mouseMove(mx, my);
}

void GlutApp::keyboardCB(unsigned char key, int x, int y){
    // When a key is pressed, call our keypress handler
    app->keyPress(key);
}

void GlutApp::specialCB(int key, int x, int y){
    // When a special key is pressed, call our handler for special keys
    app->specialKeyPress(key);
}
