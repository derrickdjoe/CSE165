#include "Img.h"

pose2D::pose2D(){

	x = 0;
	y = 0;

}

pose2D::pose2D(float xx, float yy){

	x = xx;
	y = yy;

}

Img::Img(){

	stateChanging = false;
	stateDone = false;

}

void Img::loadTextures(){

	{
		ifstream mushfile("mushroom.raw", ios::in | ios::binary);

		unsigned int size = MUSH_WIDTH * MUSH_HEIGHT * 3;
		char *data = new char[size];
		mushfile.read(data, size);

		glGenTextures(1, &texMush);

		glBindTexture(GL_TEXTURE_2D, texMush);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, MUSH_WIDTH, MUSH_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		glBindTexture(GL_TEXTURE_2D, 0);


		delete[] data;
	}

	{
		ifstream fireFile("fireball.raw", ios::in | ios::binary);

		unsigned int size = FIRE_WIDTH * FIRE_HEIGHT * 3;
		char *data = new char[size];
		fireFile.read(data, size);

		glGenTextures(1, &texFire);

		glBindTexture(GL_TEXTURE_2D, texFire);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, FIRE_WIDTH, FIRE_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		glBindTexture(GL_TEXTURE_2D, 0);


		delete[] data;
	}
}

void Img::setPos(pose2D n){

	pos.x = n.x;
	pos.y = n.y;

}

void Img::display(){

	glEnable(GL_TEXTURE_2D);

	if (!stateDone) {

		if (stateChanging) {

			glBindTexture(GL_TEXTURE_2D, texFire);


			float x = float(curFrame % FIRE_COL) / FIRE_COL;
			float y = float(curFrame / FIRE_COL) / FIRE_COL;


			float dt = 1.0 / FIRE_COL;

			glBegin(GL_QUADS);
			glTexCoord2d(x, y + dt);
			glVertex2f(pos.x - MUSH_SIZE, pos.y - MUSH_SIZE);
			glTexCoord2d(x + dt, y + dt);
			glVertex2f(pos.x + MUSH_SIZE, pos.y - MUSH_SIZE);
			glTexCoord2d(x + dt, y);
			glVertex2f(pos.x + MUSH_SIZE, pos.y + MUSH_SIZE);
			glTexCoord2d(x, y);
			glVertex2f(pos.x - MUSH_SIZE, pos.y + MUSH_SIZE);
			glEnd();

		}else{

			glBindTexture(GL_TEXTURE_2D, texMush);

			glBegin(GL_QUADS);
			glTexCoord2d(0, 1);
			glVertex2f(pos.x - MUSH_SIZE, pos.y - MUSH_SIZE);
			glTexCoord2d(1, 1);
			glVertex2f(pos.x + MUSH_SIZE, pos.y - MUSH_SIZE);
			glTexCoord2d(1, 0);
			glVertex2f(pos.x + MUSH_SIZE, pos.y + MUSH_SIZE);
			glTexCoord2d(0, 0);
			glVertex2f(pos.x - MUSH_SIZE, pos.y + MUSH_SIZE);
			glEnd();
		}
	}
}

bool Img::isIn(pose2D n){

	return (pos.x - MUSH_SIZE < n.x && n.x < pos.x + MUSH_SIZE) && (pos.y - MUSH_SIZE < n.y && n.y < pos.y + MUSH_SIZE);

}

bool Img::isFinished(){

	return stateChanging || stateDone;

}

void Img::changeState(){

	stateChanging = true;

	curTime = glutGet(GLUT_ELAPSED_TIME);
	curFrame = 0;

}

void Img::animate(){

	if(stateChanging){

		double timeNow = glutGet(GLUT_ELAPSED_TIME);
		double dt = timeNow - curTime;

		curFrame = int(FIRE_COL * dt / ANIMATE);

		if(FIRE_COL <= curFrame){

			stateDone = true;
			stateChanging = false;

		}

	}

}
