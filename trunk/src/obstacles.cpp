
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
//#include <SDL/SDL_image.h>
#include <time.h>
#include "obstacles.h"
#include "bitmap.h"

using namespace std;

DC_Obstacles::DC_Obstacles(void) {
	Arange(0,0);
} 

void DC_Obstacles::Set_X(int x) {
	X = x;
}
	
void DC_Obstacles::Set_Y(int y) {
	Y = y;
}
void DC_Obstacles::Set_Coords(int x, int y){
	X = x;
	Y = y;
}

void DC_Obstacles::Draw(int levelnum) {
	if(levelnum == 1)
		Obstacles_Surface=DC_Load("pixmaps/grass_ob.png");
	else if(levelnum == 2)
		Obstacles_Surface=DC_Load("pixmaps/snow_ob.png");
	else if(levelnum == 3)
		Obstacles_Surface=DC_Load("pixmaps/desert_ob.png");
	DC_Draw(Obstacles_Surface,Get_X(),Get_Y() );
}
void DC_Obstacles::Arange(int form, int i){
	if (form == 0) {
		Set_X(((rand()%38)+1)*20);
		Set_Y(((rand()%25)+1)*20);
		if(Get_Y()==100 || Get_Y()==400) { Set_Y(300); }
	}
	if (form == 1) {
		if (i == 0) Set_Coords(220,260);
		if (i == 1) Set_Coords(560,260);
		if (i == 2) Set_Coords(380,140);
		if (i == 3) Set_Coords(380,380);
		if (i == 4) Set_Coords(380,260);
		if (i == 5) Set_Coords(20,20);
		if (i == 6) Set_Coords(760,20);
		if (i == 7) Set_Coords(20,500);
		if (i == 8) Set_Coords(760,500);
		//next lvl
		if (i == 9) Set_Coords(300,200);
		if (i == 10) Set_Coords(460,320);
		//next lvl
		if (i == 11) Set_Coords(300,320);
		if (i == 12) Set_Coords(460,200);
		//next lvl
		if (i == 13) Set_Coords(120,380);
		if (i == 14) Set_Coords(660,140);
		//next lvl
		if (i == 15) Set_Coords(120,140);
		if (i == 16) Set_Coords(660,380);
		//next lvl
		if (i == 17) Set_Coords(40,260);
		if (i == 18) Set_Coords(740,260);
	}
}
