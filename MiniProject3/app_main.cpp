#include <GL/freeglut.h>
#include <vector>
#include <cmath>
#include "Square.h"

#define START 0
#define PLAYING 1
#define END 2

int height = 800;
int width = 800;
int players;
int gameState;

Square one(-0.5, 0.0, 0.5);
Square two(0.5, 0.0, 0.5);

std::vector<Square> board;

char currentPlayer;
char winner;

void drawWinner(){

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	if(winner == 'x'){

		glColor3f(1.0, 1.0, 0.0);
		glLineWidth(5.0);

		glBegin(GL_LINES);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, -0.5);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, -0.5);
		glEnd();

	}else if(winner == 'o'){

		glLineWidth(5.0);
		glColor3f(0.0, 1.0, 1.0);

		glBegin(GL_LINE_LOOP);
		for(int i = 0; i <= 360; i++){

			glVertex2f(0.5 * cos(i * (2.0 * M_PI) / 360), 0.5 * sin(i * (2.0 * M_PI) / 360));

		}

		glEnd();

	}else{

		glColor3f(1.0, 1.0, 1.0);
		glLineWidth(5.0);
	
		glBegin(GL_LINES);
		glVertex2f(-0.9, 0.0);
		glVertex2f(0.9, 0.0);
		glVertex2f(0.0, 0.9);
		glVertex2f(0.0, -0.9);
		glEnd();

	}

	winner = '\0';
	glutSwapBuffers();

}

void drawSquare(Square s){

	glRectf(s.getX() - (0.5 * s.getLength()), s.getY() - (0.5 * s.getLength()), 
		s.getX() + (0.5 * s.getLength()), s.getY() + (0.5 * s.getLength()));

	if(s.getWho() == 'x'){

		glColor3f(1.0, 1.0, 0.0);
		glLineWidth(5.0);

		glBegin(GL_LINES);
		glVertex2f(s.getX() - 0.2, s.getY() + 0.2);
		glVertex2f(s.getX() + 0.2, s.getY() - 0.2);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(s.getX() + 0.2, s.getY() + 0.2);
		glVertex2f(s.getX() - 0.2, s.getY() - 0.2);
		glEnd();

	}else if(s.getWho() == 'o'){

		glColor3f(0.0, 1.0, 1.0);

		glLineWidth(5.0);
		glBegin(GL_LINE_LOOP);

		for(int i = 0; i <= 360; i++){

			glVertex2f(s.getX() + (0.2 * cos(i * (2.0 * M_PI) / 360)), 
				   s.getY() + (0.2 * sin(i * (2.0 * M_PI) / 360)));

		}

		glEnd();

	}

}

void drawBoard(){

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for(size_t i = 0; i < board.size(); i++){
		
		glColor3f(0.0, 0.0, 0.0);
		drawSquare(board[i]);
	
	}

	glutSwapBuffers();

	if(gameState == 2){

		drawWinner();
	}

}

void appDrawScene(){

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 0.0);
	drawSquare(one);
	glColor3f(0.0, 1.0, 1.0);
	drawSquare(two);

	glColor3f(0.0, 0.0, 0.0);

	glRectf(-0.51, 0.2, -0.49, -0.2);

	glRectf(0.3, 0.01, 0.7, -0.01);
	glRectf(0.3, -0.01, 0.32, -0.2);
	glRectf(0.32, -0.18, 0.7, -0.2);
	glRectf(0.7, 0.01, 0.68, 0.2);
	glRectf(0.68, 0.2, 0.3, 0.18);
	
	glutSwapBuffers();

}

void gameOverCheck(){

	if(board[0].getWho() != '\0'){

		if(board[0].getWho() == board[1].getWho() && board[0].getWho() == board[2].getWho()){

			gameState = 2;
			winner = board[0].getWho();

		}else if(board[0].getWho() == board[3].getWho() && board[0].getWho() == board[6].getWho()){

			gameState = 2;
			winner = board[0].getWho();

		}else if(board[0].getWho() == board[4].getWho() && board[0].getWho() == board[8].getWho()){

			gameState = 2;
			winner = board[0].getWho();

		}

	}

	if(board[1].getWho() != '\0'){

		if(board[1].getWho() == board[4].getWho() && board[1].getWho() == board[7].getWho()){

			gameState = 2;
			winner = board[1].getWho();

		}

	}

	if(board[2].getWho() != '\0'){

		if(board[2].getWho() == board[5].getWho() && board[2].getWho() == board[8].getWho()){

			gameState = 2;
			winner = board[2].getWho();

		}else if(board[2].getWho() == board[4].getWho() && board[2].getWho() == board[6].getWho()){
		
			gameState = 2;
			winner = board[2].getWho();
	

		}

	}

	if(board[3].getWho() != '\0'){

		if(board[3].getWho() == board[4].getWho() && board[3].getWho() == board[5].getWho()){

			gameState = 2;
			winner = board[3].getWho();

		}

	}

	if(board[6].getWho() != '\0'){

		if(board[6].getWho() == board[7].getWho() && board[6].getWho() == board[8].getWho()){

			gameState = 2;
			winner = board[3].getWho();

		}

	}

}
void appMouseFunc(int button, int state, int x, int y){

	float mx = ((float)x / 400 - 1.0);
	float my = -((float)y / 400 - 1.0);

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

		bool moved = false;

		switch(gameState){

			case START:

				if(one.contains(mx, my)){
                    
					players = 1;
					gameState = PLAYING;
					drawBoard();
	
				}else if(two.contains(mx, my)){
                    
					players = 2;
					gameState = PLAYING;
					drawBoard();
				}

				break;

			case PLAYING:

				for(size_t i = 0; i < board.size(); i++){

					if(board[i].contains(mx, my) && !board[i].getIn()){
                        
						board[i].setWho(currentPlayer);

						if(currentPlayer == 'x'){
                            
							currentPlayer = 'o';
                        
						}else{
                            
							currentPlayer = 'x';
			
						}
						
						moved = true;

					}
				}

				gameState = END;

				for(size_t i = 0; i < board.size(); i++){

					if(!board[i].getIn()){
                       
						 gameState = PLAYING;
			
					}
                
				}


				gameOverCheck();

				if(players == 1 && moved && gameState != END){
                
					for(size_t i = 0; i < board.size(); i++){

						if(!board[i].getIn()){

							board[i].setWho(currentPlayer);

							if(currentPlayer == 'x'){
                                
								currentPlayer = 'o';
                            
							}else{
                                
								currentPlayer = 'x';
				
							}
							
							break;

						}
					}
				}


				gameState = END;

				for(size_t i = 0; i < board.size(); i++){
                   
					if(!board[i].getIn()){

						gameState = PLAYING;
					}

				}


				gameOverCheck();
				drawBoard();
				break;

			case END:

				currentPlayer = 'x';
				gameState = START;
				board.clear();

				float x = -1.32;
				float y = 0.66;
				
				for(int i = 0; i < 9; i++){

					if(i == 3 || i == 6){
					
						board.emplace_back(-0.66, y - 0.66, 0.64);
						x = -0.66;
						y = y - 0.66;

					}else{
					
						board.emplace_back(x + 0.66, y, 0.64);
						x = x + 0.66;
						y = y;
					}
				}

				appDrawScene();
				break;

		}
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
		break;
	}

	// After all the state changes, redraw the scene
	glutPostRedisplay();*/
	}
}

int main(int argc, char** argv){

	float x = -1.32;
	float y = 0.66;

	for(int i = 0; i < 9; i++){

		if(i == 3 || i == 6){

			board.emplace_back(-0.66, y - 0.66, 0.64);
			x = -0.66;
			y = y - 0.66;

		}else{

			board.emplace_back(x + 0.66, y, 0.64);
			x = x + 0.66;
			y = y;

		}

	}

	gameState = 0;
	currentPlayer = 'x';
	winner = '\0';

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);

	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width, height);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(appDrawScene);

	glutMouseFunc(appMouseFunc);

	glutKeyboardFunc(appKeyboardFunc);

	glutMainLoop();

	return 0;

}

