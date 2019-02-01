#ifndef IMG_H
#define IMG_H

#include <fstream>
#include "GlutApp.h"
#include <GL/glut.h>
#include <GL/freeglut.h>

using namespace std;

#define MUSH_SIZE 0.05
#define MUSH_WIDTH 400
#define MUSH_HEIGHT 400
#define FIRE_WIDTH 1024
#define FIRE_HEIGHT 1024
#define FIRE_COL 6
#define FIRE_FRAME 36
#define ANIMATE 500

class pose2D{

	public:

		float x;
		float y;

		pose2D();
		pose2D(float xx, float yy);
	

};

class Img{

	private:

		pose2D pos;
		bool stateChanging;
		bool stateDone;
		GLuint texMush, texFire;
		double curTime;
		int curFrame;

	public:

		Img();
		void loadTextures();
		void setPos(pose2D n);
		void display();
		void changeState();
		void animate();
		bool isIn(pose2D n);
		bool isFinished();

};

#endif
