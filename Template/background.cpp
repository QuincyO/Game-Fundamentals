#include "background.h"
#include "textFund.h"
#include "GameFund.h"


int level1[32][28] = {
	{0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
	{0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	
};

background::background() {
	//Star.bigStar = textFund::loadTexture("../Assets/PNG/Background/starBig.png", NULL);
	//if (Star.bigStar) std::cout << "Star Loaded\n";
;
	
	//SDL_QueryTexture(Star.bigStar, NULL, NULL,&Star.src.w,&Star.src.h);
	//loadMap(level1);

	

	//Star.src.x = Star.src.y = 0;
	//Star.dst.w = Star.src.w = 23;
	//Star.dst.h = Star.src.h = 21;
}
void background::drawStar()

{

}
void background::loadMap()
{
	for (int i = 0; i <=30 ; i++)
	{
		Stars s("../Assets/PNG/Background/starBig.png");
		s.dst.x = rand() % 896 - s.dst.w;
		s.dst.y = rand() % 1026 - s.dst.h;
		stars1.push_back(s);
	}
	for (int i = 0; i <= 15; i++)
	{
		Stars s("../Assets/PNG/Background/starBig.png");
		s.dst.w *= 2;
		s.dst.h *= 2;
		s.dst.x = rand() % 896 - s.dst.w;
		s.dst.y = rand() % 1026 - s.dst.h;
		stars2.push_back(s);
	}

	
}

void background::update()
{	
	for (Stars& s : stars1) {
		s.dst.y += backgroundStarSpeed;
		if (s.dst.y >= 1024 + s.dst.h) {
			s.dst.y = 0 - s.dst.h;
			s.dst.x = rand() % 896 - s.dst.w;
		}
	}
	
	for (Stars& s : stars2) {
		s.dst.y += foregroundStarSpeed;
		if (s.dst.y >= 1024 + s.dst.h) {
			s.dst.y = 0 - s.dst.h;
			s.dst.x = rand() % 896 - s.dst.w;
		}
	}
}

void background::draw()
{

for (Stars& s : stars1) {
	s.drawStars();
}
for (Stars& s : stars2) {
	s.drawStars();
}



	int type = 0;

	//for (int row = 0; row < 32; row++) {
	//	for (int col = 0; col < 28; col++) {
	//		type = map[row][col];
	//
	//		dst.x = col * 32;
	//		dst.y = row * 32;
	//
	//		switch (type)
	//		{
	//		case 1:
	//			textFund::draw(littleStar, src, dst);
	//			//std::cout << "Star Printed\n";
	//			break;
	//		case 2:
	//			textFund::draw(Star.bigStar , src, dst);
	//			break;
	//		case 3:
	//			textFund::draw(nebula, src, dst);
	//			break;
	//		case 4:
	//			textFund::draw(lines, src, dst);
	//			break;
	//		}
	//		
	//
	//	}
	//}

}