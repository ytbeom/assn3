#include "rock.h"

Rock::Rock(int jumplength){
	RockList.push_back((rand()%2+1)*jumplength*2); 
}

void Rock::init(int _jumplength, float mapsize, int stage){
	// 불항아리 개수/위치 설정 (게임 map 안에 있게끔)
	rockmodel.Load("tri_rock.obj","tri_rock.mtl");
	RockList.clear();
	RockList.push_back((rand()%2+1)*_jumplength*2);
	for (int i=0; i<(mapsize/_jumplength); i++) {
		 // 앞 항아리와 1*jumplength~2*jumplength 의 간격을 갖는 항아리를 생성
		int position = RockList[i]+((rand()%(6-stage)+1)*_jumplength*2);
		if (position < mapsize*2)
			RockList.push_back(position);
		else
			break;
	}
	NumofRock = RockList.size();
}

void Rock::display_rock() {
	// 항아리를 그리는 부분
	for (int i = 0; i < NumofRock; i++) {
		glPushMatrix();
		glTranslatef(RockList[i],15,0);
		glScalef(6.0,6.0,6.0);
		rockmodel.draw();
		glPopMatrix();
	}
}