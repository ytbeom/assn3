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
	knee_angle_list[4] = 15.0;
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
	//front leg
	/*
	if(state==0){
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
	glVertex3f(x, y-0.3*size,0.0);
	glVertex3f( x+0.01*size, y-0.67*size,0.0);
	glVertex3f( x, y-0.7*size,0.0);
	glVertex3f( x-0.1*size, y-0.7*size,0.0);
	glVertex3f( x-0.11*size, y-0.67*size,0.0);
	glVertex3f( x-0.1*size, y-0.3*size,0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f( x-0.15*size, y-0.3*size,0.0);
	glVertex3f( x-0.14*size, y-0.67*size,0.0);
	glVertex3f( x-0.15*size, y-0.7*size,0.0);
	glVertex3f( x-0.25*size, y-0.7*size,0.0);
	glVertex3f( x-0.26*size, y-0.67*size,0.0);
	glVertex3f( x-0.25*size, y-0.3*size,0.0);
	glEnd();
	//back leg

	glBegin(GL_POLYGON);
	glVertex3f( x-0.75*size, y-0.3*size,0.0);
	glVertex3f( x-0.74*size, y-0.67*size,0.0);
	glVertex3f( x-0.75*size, y-0.7*size,0.0);
	glVertex3f( x-0.85*size, y-0.7*size,0.0);
	glVertex3f( x-0.86*size, y-0.67*size,0.0);
	glVertex3f( x-0.85*size, y-0.3*size,0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f( x-0.9*size, y-0.2*size,0.0);
	glVertex3f( x-0.89*size, y-0.67*size,0.0);
	glVertex3f( x-0.9*size, y-0.7*size,0.0);
	glVertex3f( x-1.0*size, y-0.7*size,0.0);
	glVertex3f( x-1.01*size, y-0.67*size,0.0);
	glVertex3f( x-1.0*size, y-0.2*size,0.0);
	glEnd();
	}
	else if(state==1){
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
	glVertex3f(x, y-0.2*size,0.0);
	glVertex3f( x+0.39*size, y-0.39*size,0.0);
	glVertex3f( x+0.39*size, y-0.41*size,0.0);
	glVertex3f( x+0.34*size, y-0.49*size,0.0);
	glVertex3f( x+0.32*size, y-0.495*size,0.0);
	glVertex3f( x-0.1*size, y-0.3*size,0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f( x-0.15*size, y-0.3*size,0.0);
	glVertex3f( x+0.29*size, y-0.54*size,0.0);
	glVertex3f( x+0.29*size, y-0.56*size,0.0);
	glVertex3f( x+0.21*size, y-0.64*size,0.0);
	glVertex3f( x+0.19*size, y-0.645*size,0.0);
	glVertex3f( x-0.25*size, y-0.35*size,0.0);
	glEnd();
	//back leg

	glBegin(GL_POLYGON);
	glVertex3f( x-0.65*size, y-0.3*size,0.0);
	glVertex3f( x-0.99*size, y-0.64*size,0.0);
	glVertex3f( x-1.01*size, y-0.64*size,0.0);
	glVertex3f( x-1.09*size, y-0.61*size,0.0);
	glVertex3f( x-1.09*size, y-0.59*size,0.0);
	glVertex3f( x-0.85*size, y-0.3*size,0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f( x-0.8*size, y-0.2*size,0.0);
	glVertex3f( x-1.12*size, y-0.54*size,0.0);
	glVertex3f( x-1.13*size, y-0.54*size,0.0);
	glVertex3f( x-1.22*size, y-0.51*size,0.0);
	glVertex3f( x-1.22*size, y-0.49*size,0.0);
	glVertex3f( x-1.0*size, y-0.2*size,0.0);
	glEnd();

	}
	else if(state==2){
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
	glVertex3f(x, y-0.3*size,0.0);
	glVertex3f( x-0.07*size, y-0.65*size,0.0);
	glVertex3f( x-0.08*size, y-0.68*size,0.0);
	glVertex3f( x-0.18*size, y-0.68*size,0.0);
	glVertex3f( x-0.19*size, y-0.65*size,0.0);
	glVertex3f( x-0.1*size, y-0.3*size,0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f( x-0.15*size, y-0.3*size,0.0);
	glVertex3f( x-0.22*size, y-0.65*size,0.0);
	glVertex3f( x-0.23*size, y-0.68*size,0.0);
	glVertex3f( x-0.33*size, y-0.68*size,0.0);
	glVertex3f( x-0.34*size, y-0.65*size,0.0);
	glVertex3f( x-0.25*size, y-0.3*size,0.0);
	glEnd();
	//back leg

	glBegin(GL_POLYGON);
	glVertex3f( x-0.75*size, y-0.3*size,0.0);
	glVertex3f( x-0.64*size, y-0.65*size,0.0);
	glVertex3f( x-0.65*size, y-0.68*size,0.0);
	glVertex3f( x-0.75*size, y-0.68*size,0.0);
	glVertex3f( x-0.76*size, y-0.65*size,0.0);
	glVertex3f( x-0.85*size, y-0.3*size,0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f( x-0.9*size, y-0.2*size,0.0);
	glVertex3f( x-0.79*size, y-0.65*size,0.0);
	glVertex3f( x-0.80*size, y-0.68*size,0.0);
	glVertex3f( x-0.90*size, y-0.68*size,0.0);
	glVertex3f( x-0.91*size, y-0.65*size,0.0);
	glVertex3f( x-1.0*size, y-0.2*size,0.0);
	glEnd();
	}*/
}

void Lion::drawLion(){
	/*
	int i;
	// lion BODY start //

	//torso

	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
	glVertex3f( x, y,0.0);
	glVertex3f( x-0.8*size, y,0.0);
	glVertex3f( x-0.95*size, y-0.07*size,0.0);
	glVertex3f( x-1.0*size, y-0.15*size,0.0);
	glVertex3f( x-1.0*size, y-0.23*size,0.0);
	glVertex3f( x-0.95*size, y-0.35*size,0.0);
	glVertex3f( x-0.5*size, y-0.37*size,0.0);
	glVertex3f( x, y-0.35*size,0.0);
	glEnd();
	//tail
	glBegin(GL_POLYGON);
	glVertex3f( x-0.93*size, y-0.09*size,0.0);
	glVertex3f( x-1.2*size, y+0.3*size,0.0);
	glVertex3f( x-1.23*size, y+0.3*size,0.0);
	glVertex3f( x-0.95*size, y-0.09*size,0.0);
	glEnd();
	glColor3f(1.0,0.5,0.0);
	glBegin(GL_POLYGON);
	for(i=0;i<36;i++){

	float x1 =  x-1.19*size+(float)cos(i*PI/18)*0.025*size;
	float y1 =  y+0.3*size+(float)sin(i*PI/18)*0.025*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for(i=0;i<36;i++){

	float x1 =  x-1.22*size+(float)cos(i*PI/18)*0.025*size;
	float y1 =  y+0.3*size+(float)sin(i*PI/18)*0.025*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for(i=0;i<36;i++){

	float x1 =  x-1.21*size+(float)cos(i*PI/18)*0.025*size;
	float y1 =  y+0.33*size+(float)sin(i*PI/18)*0.025*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();


	// lion BODY end   //

	// lion HEAD start //


	//gal gi botton
	glColor3f(1.0,0.5,0.0);
	glBegin(GL_POLYGON);
	for(i=0;i<60;i++){

	float x1 =  x-0.01*size+(float)cos(i*PI/30)*0.15*size;
	float y1 =  y-0.35*size+(float)sin(i*PI/30)*0.15*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();
	//gal gi top
	glColor3f(1.0,0.5,0.0);
	glBegin(GL_POLYGON);
	for(i=0;i<60;i++){

	float x1 =  x-0.01*size+(float)cos(i*PI/30)*0.15*size;
	float y1 =  y+0.35*size+(float)sin(i*PI/30)*0.15*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();
	//gal gi left
	glColor3f(1.0,0.5,0.0);
	glBegin(GL_POLYGON);
	for(i=0;i<60;i++){

	float x1 =  x-0.3*size+(float)cos(i*PI/30)*0.15*size;
	float y1 =  y+(float)sin(i*PI/30)*0.15*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();
	//gal gi right
	glColor3f(1.0,0.5,0.0);
	glBegin(GL_POLYGON);
	for(i=0;i<60;i++){

	float x1 =  x+0.27*size+(float)cos(i*PI/30)*0.15*size;
	float y1 =  y+(float)sin(i*PI/30)*0.15*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();
	////
	glBegin(GL_POLYGON);
	for(i=0;i<60;i++){

	float x1 =  x+0.197*size+(float)cos(i*PI/30)*0.15*size;
	float y1 =  y+0.23*size+(float)sin(i*PI/30)*0.15*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for(i=0;i<60;i++){

	float x1 =  x+0.197*size+(float)cos(i*PI/30)*0.15*size;
	float y1 =  y-0.23*size+(float)sin(i*PI/30)*0.15*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for(i=0;i<60;i++){

	float x1 =  x-0.23*size+(float)cos(i*PI/30)*0.15*size;
	float y1 =  y+0.23*size+(float)sin(i*PI/30)*0.15*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for(i=0;i<60;i++){

	float x1 =  x-0.23*size+(float)cos(i*PI/30)*0.15*size;
	float y1 =  y-0.23*size+(float)sin(i*PI/30)*0.15*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();

	//face
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
	for(i=0;i<60;i++){

	float x1 =  x+(float)cos(i*PI/30)*0.225*size;
	float y1 =  y+(float)sin(i*PI/30)*0.3*size;
	glVertex3f(x1,y1,0.0);

	}
	glEnd();
	//left eye
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
	for(i=0;i<36;i++){

	float x1 =  x-0.09*size+(float)cos(i*PI/18)*0.025*size;
	float y1 =  y+0.05*size+(float)sin(i*PI/18)*0.025*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();
	//right eye
	glBegin(GL_POLYGON);
	for(i=0;i<36;i++){

	float x1 =  x+0.15*size+(float)cos(i*PI/18)*0.025*size;
	float y1 =  y+0.05*size+(float)sin(i*PI/18)*0.025*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();
	//mouth
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	for(i=0;i<36;i++){

	float x1 =  x+0.075*size+(float)cos(i*PI/18)*0.065*size;
	float y1 =  y-0.085*size+(float)sin(i*PI/18)*0.07*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for(i=0;i<36;i++){

	float x1 =  x-0.005*size+(float)cos(i*PI/18)*0.065*size;
	float y1 =  y-0.085*size+(float)sin(i*PI/18)*0.07*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();
	//nose
	glColor3f(1.0,0.5,0.0);
	glBegin(GL_POLYGON);
	for(i=0;i<36;i++){

	float x1 =  x+0.05*size+(float)cos(i*PI/18)*0.025*size;
	float y1 =  y-0.05*size+(float)sin(i*PI/18)*0.025*size;
	glVertex3f(x1,y1,0.0);
	}
	glEnd();
	// lion HEAD end //
	*/

	// assignment2 drawLion function

	// 시작은 Torso의 기준점, 겹치는 문제 때문에 다리를 먼저그림

	if (jump_state == 0) {
		// 앞쪽 왼다리
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.23*size,-0.35*size,0);
		glRotatef(thigh_angle_list[state],0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.17*size,0);
		glRotatef(knee_angle_list[state],0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();	

		// 앞쪽 오른다리
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.1*size,-0.35*size,0);
		glRotatef(thigh_angle_list[(state+0)%8],0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.17*size,0);
		glRotatef(knee_angle_list[(state+0)%8],0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();

		// 뒷쪽 왼다리
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.9*size,-0.35*size,0);
		glRotatef(thigh_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.17*size,0);
		glRotatef(thigh_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();

		// 뒷쪽 오른다리
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.77*size,-0.35*size,0);
		glRotatef(thigh_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.17*size,0);
		glRotatef(thigh_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();
	}
	else {
		// 앞쪽 왼다리
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.23*size,-0.35*size,0);
		glRotatef(45,0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.17*size,0);
		glRotatef(45,0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();	

		// 앞쪽 오른다리
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.1*size,-0.35*size,0);
		glRotatef(45,0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.17*size,0);
		glRotatef(45,0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();

		// 뒷쪽 왼다리
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.9*size,-0.35*size,0);
		glRotatef(-45,0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.17*size,0);
		glRotatef(-45,0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();

		// 뒷쪽 오른다리
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.77*size,-0.35*size,0);
		glRotatef(-45,0.0,0.0,1.0);
		drawUpperLeg();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.17*size,0);
		glRotatef(-45,0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();
	}

	drawTorso();
	drawHead();

	glPushMatrix();
	// Torso의 기준점에서 꼬리의 상대적인 위치로 변환
	glTranslatef(-0.93*size,-0.09*size,0);
	drawTail();
	glPopMatrix();
}

// 시작 좌표를 (0,0)으로 해 몸통을 그림
void Lion::drawTorso() {
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0,0,0.0);
	glVertex3f(-0.8*size,0,0.0);
	glVertex3f(-0.95*size,-0.07*size,0.0);
	glVertex3f(-1.0*size,-0.15*size,0.0);
	glVertex3f(-1.0*size,-0.23*size,0.0);
	glVertex3f(-0.95*size,-0.35*size,0.0);
	glVertex3f(-0.5*size,-0.37*size,0.0);
	glVertex3f(0,-0.35*size,0.0);
	glEnd();
}

// 시작 좌표를 (0,0)으로 해 머리를 그림
void Lion::drawHead() {
	// mane bottom
	glColor3f(1.0,0.5,0.0);
	glBegin(GL_POLYGON);
	for (int i=0;i<60;i++) {
		float x1 = -0.01*size+(float)cos(i*PI/30)*0.15*size;
		float y1 = -0.35*size+(float)sin(i*PI/30)*0.15*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
	// mane top
	glColor3f(1.0,0.5,0.0);
	glBegin(GL_POLYGON);
	for (int i=0;i<60;i++) {
		float x1 = -0.01*size+(float)cos(i*PI/30)*0.15*size;
		float y1 = +0.35*size+(float)sin(i*PI/30)*0.15*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
	// mane left
	glColor3f(1.0,0.5,0.0);
	glBegin(GL_POLYGON);
	for (int i=0;i<60;i++) {
		float x1 = -0.3*size+(float)cos(i*PI/30)*0.15*size;
		float y1 = (float)sin(i*PI/30)*0.15*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
	// mane right
	glColor3f(1.0,0.5,0.0);
	glBegin(GL_POLYGON);
	for (int i=0;i<60;i++) {
		float x1 = 0.27*size+(float)cos(i*PI/30)*0.15*size;
		float y1 = (float)sin(i*PI/30)*0.15*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
	// mane right top
	glBegin(GL_POLYGON);
	for (int i=0;i<60;i++) {
		float x1 = 0.197*size+(float)cos(i*PI/30)*0.15*size;
		float y1 = 0.23*size+(float)sin(i*PI/30)*0.15*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
	// mane right bottom
	glBegin(GL_POLYGON);
	for (int i=0;i<60;i++) {
		float x1 = 0.197*size+(float)cos(i*PI/30)*0.15*size;
		float y1 = -0.23*size+(float)sin(i*PI/30)*0.15*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
	// mane left top
	glBegin(GL_POLYGON);
	for (int i=0;i<60;i++) {
		float x1 = -0.23*size+(float)cos(i*PI/30)*0.15*size;
		float y1 = 0.23*size+(float)sin(i*PI/30)*0.15*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
	// mane left bottom
	glBegin(GL_POLYGON);
	for (int i=0;i<60;i++) {
		float x1 = -0.23*size+(float)cos(i*PI/30)*0.15*size;
		float y1 = -0.23*size+(float)sin(i*PI/30)*0.15*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
	//face
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
	for (int i=0;i<60;i++) {
		float x1 = (float)cos(i*PI/30)*0.225*size;
		float y1 = (float)sin(i*PI/30)*0.3*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
	//left eye
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
	for (int i=0;i<36;i++) {
		float x1 =  -0.09*size+(float)cos(i*PI/18)*0.025*size;
		float y1 =  0.05*size+(float)sin(i*PI/18)*0.025*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
	//right eye
	glBegin(GL_POLYGON);
	for (int i=0;i<36;i++) {
		float x1 = 0.15*size+(float)cos(i*PI/18)*0.025*size;
		float y1 = 0.05*size+(float)sin(i*PI/18)*0.025*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
	// right mouth
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	for (int i=0;i<36;i++) {
		float x1 = 0.075*size+(float)cos(i*PI/18)*0.065*size;
		float y1 = -0.085*size+(float)sin(i*PI/18)*0.07*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
	// left mouth
	glBegin(GL_POLYGON);
	for (int i=0;i<36;i++) {
		float x1 = -0.005*size+(float)cos(i*PI/18)*0.065*size;
		float y1 = -0.085*size+(float)sin(i*PI/18)*0.07*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
	// nose
	glColor3f(1.0,0.5,0.0);
	glBegin(GL_POLYGON);
	for (int i=0;i<36;i++) {
		float x1 = 0.05*size+(float)cos(i*PI/18)*0.025*size;
		float y1 = -0.05*size+(float)sin(i*PI/18)*0.025*size;
		glVertex3f(x1,y1,0.0);
	}
	glEnd();
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
	glBegin(GL_POLYGON);
	glVertex3f(0.025*size, 0.05*size, 0.0);
	glVertex3f(0.06*size, 0, 0.0);
	glVertex3f(0.06*size, -0.165*size, 0.0);
	glVertex3f(0.025*size, -0.195*size, 0.0);
	glVertex3f(-0.025*size, -0.195*size, 0.0);
	glVertex3f(-0.06*size, -0.165*size, 0.0);
	glVertex3f(-0.06*size, 0, 0.0);
	glVertex3f(-0.025*size, 0.05*size, 0.0);
	glEnd();
}

void Lion::drawLowerLeg() {
	glBegin(GL_POLYGON);
	glVertex3f(0.025*size, 0.05*size, 0.0);
	glVertex3f(0.07*size, 0, 0.0);
	glVertex3f(0.06*size, -0.165*size, 0.0);
	glVertex3f(0.025*size, -0.195*size, 0.0);
	glVertex3f(-0.025*size, -0.195*size, 0.0);
	glVertex3f(-0.06*size, -0.165*size, 0.0);
	glVertex3f(-0.07*size, 0, 0.0);
	glVertex3f(-0.025*size, 0.05*size, 0.0);
	glEnd();
}