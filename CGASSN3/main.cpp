#include <time.h>
#include <stdlib.h>
#include "lion.h"
#include "firepot.h"
#include "fireloop.h"
#include "stage.h"
#include "ObjLoader.h"

float mapsize;
float bottom = 20.0;
int jumplength = 80; // ���ڰ� 1ȸ ������ �� �����̴� �Ÿ�
int xposition = 0.0;
int BackgroundChange = 0;
int translateLoop;
int stage=1;
int startfresh;
int view;
Lion my_lion;
Background my_bg;
Firepot my_pot(jumplength);
Fireloop my_loop(jumplength);
//Model_OBJ rockloader; // loader

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
	view = 0;
	srand((unsigned int)time(NULL));
	
	// 1000���� 2000 ������ mapsize ����
	mapsize = rand()%1000+1000;
//	mapsize = 200;
	my_bg.init(mapsize,bottom,stage);
	my_pot.init(jumplength,mapsize,stage);
	my_loop.init(jumplength,mapsize,stage);
	// load model
	//rockloader.Load("tri_rock.obj");

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

// �ð��� ������ �ӵ��� �ڵ����� 0�� �ǰԲ� �ϴ� �Լ�
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
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable( GL_DEPTH_TEST );
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	switch(view){
		case 0:	
			gluLookAt(40, 0, 40.0, 0, 0, 0.0, 0.0, 1.0, 0.0);
			//gluLookAt(my_lion.x+5, my_lion.y, 0.0, my_lion.x+10, my_lion.y-10, 0.0, 0.0, 1.0, 0.0); 
			break;
		case 1: gluLookAt(-50, -50, 0.0, 0, 0, 0.0, 0.0, 1.0, 0.0);
			break;
		case 2:
			//gluLookAt(0, 200, 0.0, 0, 0, 0.0, 1.0, 0.0, 0.0);
			gluLookAt(0, 500, 0.0, 0, 0.0, 0.0, 1.0, 0.0, 0.0);
			break;
		case 3: glOrtho(-50+my_lion.x, 150+my_lion.x, 0, 100, -50, 50);
			break;
	}

	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1000, 0, 0);
	glVertex3f(1000, 0, 0);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, -1000, 0);
	glVertex3f(0, 1000, 0);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, -1000);
	glVertex3f(0, 0, 1000);
	glEnd();


	
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

		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity();

	switch(view){
		case 0:	
			gluLookAt(40, 0, 40.0, 0, 0, 0.0, 0.0, 1.0, 0.0);
			//gluLookAt(my_lion.x+5, my_lion.y, 0.0, my_lion.x+10, my_lion.y-10, 0.0, 0.0, 1.0, 0.0); 
			break;
		case 1: gluLookAt(-50, -50, 0.0, 0, 0, 0.0, 0.0, 1.0, 0.0);
			break;
		case 2:
			//gluLookAt(0, 200, 0.0, 0, 0, 0.0, 1.0, 0.0, 0.0);
			gluLookAt(0, 500, 0.0, 0, 0.0, 0.0, 1.0, 0.0, 0.0);
			break;
		case 3: glOrtho(-50+my_lion.x, 150+my_lion.x, 0, 100, -50, 50);
			break;
	}
		glutPostRedisplay();

		//translate Loop and draw 3D fireloop
		glPushMatrix();
		glTranslatef(translateLoop,0,0);
		my_loop.display_3d_fireloop(my_lion.x, translateLoop);
		glPopMatrix();

	
		//draw lion
		glPushMatrix();
		glTranslatef(my_lion.x,my_lion.y,0);

		
		my_lion.drawLion();
		
		
		glPopMatrix();



		// draw rock
		glPushMatrix();
		glTranslatef(my_pot.PotList[0],bottom,0);
		glScalef(10.0,10.0,10.0);
//		rockloader.Draw();
		glPopMatrix();

		glFlush();
	}
	
	else {
		my_lion.drawDeath(my_lion);
		glFlush();
		glutSwapBuffers();
		Sleep(2000);
		exit(1);
	}

	
	glutSwapBuffers();
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
//	glOrtho(-50+my_lion.x, 150+my_lion.x, 0, 100, -50, 50);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();	
	//gluLookAt(0.0, 0.0, 100.0, my_lion.x, my_lion.y, 0.0, 0.0, 1.0, 0.0);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	switch(view){
		case 0:	
			gluLookAt(40, 0, 40.0, 0, 0, 0.0, 0.0, 1.0, 0.0);
			//gluLookAt(my_lion.x+5, my_lion.y, 0.0, my_lion.x+10, my_lion.y-10, 0.0, 0.0, 1.0, 0.0); 
			break;
		case 1: gluLookAt(-50, -50, 0.0, 0, 0, 0.0, 0.0, 1.0, 0.0);
			break;
		case 2:
			//gluLookAt(0, 200, 0.0, 0, 0, 0.0, 1.0, 0.0, 0.0);
			gluLookAt(0, 500, 0.0, 0, 0.0, 0.0, 1.0, 0.0, 0.0);
			break;
		case 3: glOrtho(-50+my_lion.x, 150+my_lion.x, 0, 100, -50, 50);
			break;
	}


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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
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
	case GLUT_KEY_DOWN:
		if(view>=4)
			view=0;
		else
			view++;
		break;

	}
	//gluOrtho2D(-50+my_lion.x, 150+my_lion.x, 0, 100);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(0.0, 0.0, 100.0, 0.0, 5.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(0.0, 0.0, 100.0, my_lion.x, my_lion.y, 0.0, 0.0, 1.0, 0.0);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	switch(view){
		case 0:	
			gluLookAt(40, 0, 40.0, 0, 0, 0.0, 0.0, 1.0, 0.0);
			//gluLookAt(my_lion.x+5, my_lion.y, 0.0, my_lion.x+10, my_lion.y-10, 0.0, 0.0, 1.0, 0.0); 
			break;
		case 1: gluLookAt(-50, -50, 0.0, 0, 0, 0.0, 0.0, 1.0, 0.0);
			break;
		case 2:
			//gluLookAt(0, 200, 0.0, 0, 0, 0.0, 1.0, 0.0, 0.0);
			gluLookAt(0, 500, 0.0, 0, 0.0, 0.0, 1.0, 0.0, 0.0);
			break;
		case 3: glOrtho(-50+my_lion.x, 150+my_lion.x, 0, 100, -50, 50);
			break;
	}


	glutPostRedisplay();
}

void reshape(int w, int h)
{
	// TODO
	// gluOrtho2D update
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	switch(view){
	case 0:	gluPerspective(60.0,2.0,1.0,1000.0);
		printf("return to 0!\n");
		break;
	case 1: gluPerspective(60.0,2.0,1.0,1000.0);
		break;
	case 2: gluPerspective(60.0,2.0,1.0,1000.0);
		break;
	case 3: glOrtho(-50+my_lion.x, 150+my_lion.x, 0, 100, -50, 50);\
		break;
	}
//	glOrtho(-50+my_lion.x, 150+my_lion.x, 0, 100, -50, 50);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
