#include "lion.h"

extern float WidthofLoop;
extern float mapsize;

Lion::Lion() {
	x = 0; 
	y = 0; 
	size = 1; 
	state = 0; 
	c_state = 0; 
	jump_state = 0;
	// angle list initialize
	thigh_angle_list[0] = -30.0;
	thigh_angle_list[1] = -15.0;
	thigh_angle_list[2] = 0.0;
	thigh_angle_list[3] = 15.0;
	thigh_angle_list[4] = 30.0;
	thigh_angle_list[5] = 15.0;
	thigh_angle_list[6] = 0;
	thigh_angle_list[7] = -15.0;
	// knee list initialize
	knee_angle_list[0] = -20.0;
	knee_angle_list[1] = -15.0;
	knee_angle_list[2] = 0.0;
	knee_angle_list[3] = 0.0;
	knee_angle_list[4] = 0.0;
	knee_angle_list[5] = 0.0;
	knee_angle_list[6] = 0.0;
	knee_angle_list[7] = -15.0;
}

int Lion::IsCollisionPot(float _x, float _y, float _radius){
	if(_x-_radius < x+0.2*size && _x+_radius > x-0.8*size) {
		if(y-0.7*size < _y)
			return true;
	}
	return false;
}

int Lion::IsCollisionLoop(float _x, float _y, float _radius){
	if(_x < x+0.3*size && x-0.7*size < _x){
		if(!(y-0.7*size>_y-_radius&&y+0.5*size<_y+_radius))
			return true;
	}
	return false;
}

void Lion::drawDeath(Lion my_lion){
	glClear(GL_COLOR_BUFFER_BIT);

	void *font = GLUT_BITMAP_TIMES_ROMAN_24;
	char string[] ="GAME OVER";
	glColor3f(1.0,1.0,1.0);
	glRasterPos2f(my_lion.x,50);
	int len = 9;
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string[i]);
}

void Lion::drawClear(Lion my_lion){
	glClear(GL_COLOR_BUFFER_BIT);

	void *font = GLUT_BITMAP_TIMES_ROMAN_24;
	char string[] ="STAGE CLEAR";
	glColor3f(1.0,1.0,1.0);
	glRasterPos2f(my_lion.x+15,50);
	int len = 11;
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string[i]);
}

void Lion::drawLeg(){
	
}

void Lion::drawLion(){


	// assignment2 drawLion function

	// 시작은 Torso의 기준점, 겹치는 문제 때문에 다리를 먼저그림

	if (jump_state == 0) {
		// 앞쪽 왼다리
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.23*size,-0.30*size,0);
		glRotatef(thigh_angle_list[state],0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(knee_angle_list[state%8],0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();	

		// 앞쪽 오른다리
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.1*size,-0.30*size,0);
		glRotatef(thigh_angle_list[state],0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(knee_angle_list[state%8],0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();

		// 뒷쪽 왼다리
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.9*size,-0.30*size,0);
		glRotatef(thigh_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(knee_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();

		// 뒷쪽 오른다리
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.77*size,-0.30*size,0);
		glRotatef(thigh_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(knee_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();
	}
	else {
		// 앞쪽 왼다리
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.23*size,-0.30*size,0);
		glRotatef(45,0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(45,0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();	

		// 앞쪽 오른다리
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.1*size,-0.30*size,0);
		glRotatef(45,0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(45,0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();

		// 뒷쪽 왼다리
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.9*size,-0.30*size,0);
		glRotatef(-45,0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(-45,0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();

		// 뒷쪽 오른다리
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.77*size,-0.30*size,0);
		glRotatef(-45,0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(-45,0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(-3,-1,0);
	glRotatef(270,0,1,0);
	glRotatef(90,0,0,1);
	glScalef(8,8,8);
	
	drawTorso();
	glPopMatrix();
	glPushMatrix();
	glRotatef(90,0,1,0);
	glScalef(4,4,4);
	drawHead();
	glPopMatrix();


}

// 시작 좌표를 (0,0)으로 해 몸통을 그림
void Lion::drawTorso() {
	glColor3f(1.0,1.0,0.0);
	glPushMatrix();
	//glRotatef(90,1,0,0);
	glutWireCylinder(0.5,2,20,20);
	glPushMatrix();
	glRotatef(180,0,1,0);
	
	glutWireCone(0.5,0.5,10,10);
	glPopMatrix();
	glPushMatrix();
	glScalef(1,1,0.4);
	glutWireSphere(0.5,20,20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0,2);
	glScalef(1,1,0.4);
	glutWireSphere(0.5,20,20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0,2);
	glRotatef(45,0,1,0);
	glutWireCylinder(0.05,2,10,10);
	glPushMatrix();
	glColor3f(1.0,0.5,0.0);
	glTranslatef(0,0,2);
	glutWireSphere(0.1,10,10);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

// 시작 좌표를 (0,0)으로 해 머리를 그림
void Lion::drawHead() {
	//head
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	glutWireSphere(1,20,20);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(-0.4,0.01,0.8399);
	glutSolidSphere(0.05,10,10);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(0.4,0.01,0.8399);
	glutSolidSphere(0.05,10,10);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(0,-0.25,0.9375);
	glutSolidSphere(0.05,10,10);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1,1,0);
	glTranslatef(-0.2,-0.4,0.8);
	glutWireSphere(0.2,10,10);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1,1,0);
	glTranslatef(0.2,-0.4,0.8);
	glutWireSphere(0.2,10,10);
	glPopMatrix();
		
	
	glPushMatrix();
	glTranslatef(cos(0.0)*1.7,sin(0.0)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(cos(PI/2)*1.7,sin(PI/2)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(cos(PI)*1.7,sin(PI)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(cos(PI*3/2)*1.7,sin(PI*3/2)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cos(PI/4)*1.7,sin(PI/4)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(cos(PI*3/4)*1.7,sin(PI*3/4)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(cos(PI*5/4)*1.7,sin(PI*5/4)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(cos(PI*7/4)*1.7,sin(PI*7/4)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();
	//head end
}

// (x-0.93*size, y-0.09*size)을 새로운 원점 기준으로 꼬리를 그림
void Lion::drawTail() {
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
//	glVertex3f(x-0.93*size, y-0.09*size,0.0);
	glVertex3f(0,0,0);
//	glVertex3f(x-1.2*size, y+0.3*size,0.0);
	glVertex3f(-0.27*size, 0.39*size, 0);
//	glVertex3f(x-1.23*size, y+0.3*size,0.0);
	glVertex3f(-0.3*size, 0.39*size, 0);
//	glVertex3f(x-0.95*size, y-0.09*size,0.0);
	glVertex3f(-0.02*size,0,0);
	glEnd();
	glColor3f(1.0,0.5,0.0);
	glBegin(GL_POLYGON);
	for (int i=0;i<36;i++) {
		// float x1 = x-1.19*size+(float)cos(i*PI/18)*0.025*size;
		float x1 = -0.26*size+(float)cos(i*PI/18)*0.025*size;
		// float y1 = y+0.3*size+(float)sin(i*PI/18)*0.025*size;
		float y1 = 0.39*size+(float)sin(i*PI/18)*0.025*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i=0;i<36;i++) {
		// float x1 = x-1.22*size+(float)cos(i*PI/18)*0.025*size;
		float x1 = -0.29*size+(float)cos(i*PI/18)*0.025*size;
		// float y1 = y+0.3*size+(float)sin(i*PI/18)*0.025*size;
		float y1 = 0.39*size+(float)sin(i*PI/18)*0.025*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i=0;i<36;i++) {
		// float x1 = x-1.21*size+(float)cos(i*PI/18)*0.025*size;
		float x1 = -0.28*size+(float)cos(i*PI/18)*0.025*size;
		// float y1 = y+0.33*size+(float)sin(i*PI/18)*0.025*size;
		float y1 = 0.42*size+(float)sin(i*PI/18)*0.025*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
}

void Lion::drawUpperLeg() {
	glPushMatrix();
	glRotatef(90,1,0,0);
	glScalef(5,5,5);
	glutWireCylinder(0.2,0.5,10,10);
	glutWireSphere(0.2,20,20);
	glPopMatrix();
}

void Lion::drawLowerLeg() {
	glPushMatrix();
	glRotatef(90,1,0,0);
	glScalef(5,5,5);
	glutWireCylinder(0.2,0.5,10,10);
	glutWireSphere(0.2,20,20);
	glPopMatrix();
}