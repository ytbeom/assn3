#include <time.h>
#include <stdlib.h>
#include "lion.h"
#include "firepot.h"
#include "fireloop.h"
#include "stage.h"

float mapsize;
float bottom = 20.0;
int jumplength = 80; // 사자가 1회 점프할 때 움직이는 거리
int xposition = 0.0;
int BackgroundChange = 0;
int translateLoop;
int stage=1;
int startfresh;
Lion my_lion;
Background my_bg;
Firepot my_pot(jumplength);
Fireloop my_loop(jumplength);

void init(void)
{
	my_lion.x = 0;
	my_lion.y = bottom;
	my_lion.size = 20;
	my_lion.c_state = 0;
	my_lion.state = 2;
	my_lion.jump_state = 0;
	translateLoop=0;
	startfresh=0;
	srand((unsigned int)time(NULL));
	
	// 1000에서 2000 사이의 mapsize 생성
	mapsize = rand()%1000+1000;
//	mapsize = 200;
	my_bg.init(mapsize,bottom,stage);
	my_pot.init(jumplength,mapsize,stage);
	my_loop.init(jumplength,mapsize,stage);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

int collision(){
/*	for(int i = 0; i < my_pot.NumofPot; i++){
		if(my_lion.IsCollisionPot(my_pot.PotList[i]/2, (my_pot.BottomofPot + my_pot.TopofFire)/2, my_pot.RadiusofFire/2))
			return true;
	}
	
	for(int i = 0; i < my_loop.NumofLoop; i++){
		if(my_lion.IsCollisionLoop(my_loop.LoopList[i]+translateLoop, my_loop.top - my_loop.RadiusofLoop, my_loop.RadiusofLoop))
			return true;
	}*/
	return false;
}

// 시간이 지나면 속도가 자동으로 0이 되게끔 하는 함수
void Stop(int value){
	int keep;
	if(my_lion.y!=bottom)
		keep=0;
	else{
		if(my_lion.velocity<0.005 && my_lion.velocity>-0.005){
			my_lion.velocity=0;
			//my_lion.state=2;
			keep=0;
		}
		else if(my_lion.velocity>0){
			keep=1;
			my_lion.velocity -= 0.005;
		}
		else{
			keep=1;
			my_lion.velocity += 0.005;
		}
	}
	if(keep)
		glutTimerFunc(100, Stop, 1);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (BackgroundChange < 9) 
		BackgroundChange++;
	else
		BackgroundChange=0;

	if (!collision() && my_lion.x > mapsize && my_bg.season<4) {
		my_lion.drawClear(my_lion);
		glFlush();
		glutSwapBuffers();
		Sleep(2000);
		stage++;
		init();
		//exit(1);
	}
	else if (!collision() && my_lion.x > mapsize && my_bg.season==4) {
		my_lion.drawClear(my_lion);
		glFlush();
		glutSwapBuffers();
		Sleep(2000);
		exit(1);
	}
	else if(!collision()) {		
		my_bg.draw(BackgroundChange);
		my_bg.info(my_lion.x);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		startfresh=1;
		bool right = ((GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000);
		bool left = ((GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000);
		if(right) {
			if (my_lion.y==bottom) {
				my_lion.x += 1;
				my_lion.velocity += 0.05;

				if(my_lion.velocity<0)
					my_lion.velocity=0;

				// state change
				if (my_lion.c_state == 3) {
					my_lion.state = (my_lion.state+1)%8;
					my_lion.c_state = 0;
				}
				else 
					my_lion.c_state++;

				glutTimerFunc(100, Stop, 1);
			}	
		}
		if (left) {
			if(my_lion.y==bottom){
				my_lion.x -= 1;
				my_lion.velocity -= 0.05;
				if(my_lion.velocity>0)
					my_lion.velocity=0;
				// state change
				if (my_lion.c_state == 3) {
					my_lion.state = (my_lion.state+1)%8;
					my_lion.c_state = 0;
				}
				else 
					my_lion.c_state++;
				glutTimerFunc(100, Stop, 1);
			}
		}

		gluOrtho2D(-50+my_lion.x, 150+my_lion.x, 0, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();	
		glutPostRedisplay();

		//translate Loop
		glPushMatrix();
		glTranslatef(translateLoop,0,0);
		my_loop.display_fireloop_front(BackgroundChange, my_lion.x, translateLoop);
		glPopMatrix();

		//draw lion
		//my_lion.drawLeg();
		glPushMatrix();
		glTranslatef(my_lion.x,my_lion.y,0);
		my_lion.drawLion();
		glPopMatrix();

		//translate Loop
		glPushMatrix();
		glTranslatef(translateLoop,0,0);
		my_loop.display_fireloop_back(BackgroundChange, my_lion.x, translateLoop);
		glPopMatrix();

		//draw firepot
		glPushMatrix();
		glScalef(0.5f,0.5f,1.0f);
		my_pot.display_firepot(BackgroundChange);
		glPopMatrix();

		glFlush();
		glutSwapBuffers();
	}
	
	else {
		my_lion.drawDeath(my_lion);
		glFlush();
		glutSwapBuffers();
		Sleep(2000);
		exit(1);
	}
}

float jump_initX = 0;
float jump_upX = 0;
void Jump(int jump_direction){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int keep = 1;
	float print_x;

	//jump forward
	if(jump_direction == 1){
		my_lion.jump_state=1;
		print_x = my_lion.x-jump_initX;
		my_lion.x += 1;
	}
	//jumb backward
	else if(jump_direction == -1){
		my_lion.jump_state=1;
		print_x = jump_initX-my_lion.x;
		my_lion.x -= 1;
	}
	//jump up
	else{
		my_lion.jump_state=1;
		if(jump_upX<81)
			jump_upX+=1;
		print_x = jump_upX;
	}
	gluOrtho2D(-50+my_lion.x, 150+my_lion.x, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	glutPostRedisplay();

	my_lion.y = bottom + 60 - 0.066*(print_x-30)*(print_x-30);

	if (my_lion.y<bottom) {
		keep=0;
		my_lion.state=2;
		my_lion.jump_state = 0;
		my_lion.y=bottom;
		jump_upX=0;
		glutTimerFunc(1, Stop, 1);
	}
	if(keep)
		glutTimerFunc(700/60, Jump, jump_direction);
}

void specialkeyboard(int key, int x, int y)
{
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	switch (key) {
	case GLUT_KEY_UP:
		if(my_lion.y==bottom&&startfresh==1) {
			jump_initX = my_lion.x;
			bool right = ((GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000);
			bool left = ((GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000);
			if (right)
				glutTimerFunc(700/60,Jump,1);
			else if (left)
				glutTimerFunc(700/60,Jump,-1);
			else
				glutTimerFunc(700/60,Jump,0);
		}
		break;
	}
	//gluOrtho2D(-50+my_lion.x, 150+my_lion.x, 0, 100);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();	
	//glutPostRedisplay();
}

void reshape(int w, int h)
{
	// TODO
	// gluOrtho2D update
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-50+my_lion.x, 150+my_lion.x, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void moveObjects(int) {
	if(stage<3)
		translateLoop-=1;
	else
		translateLoop-=(float)stage/2+(float)(stage%2)/2;
	glutPostRedisplay();
	
//	glutSpecialFunc(specialkeyboard);
	glutTimerFunc(2000/60,moveObjects,1);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Circus Charlie");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(specialkeyboard);

	glutTimerFunc(2000/60,moveObjects,1);
	glutMainLoop();
}
