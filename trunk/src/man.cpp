
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <time.h>
#include "man.h"
#include "bitmap.h"

using namespace std;

DC_Man::DC_Man(void) {
	
	Set_X(((rand()%38)+1)*20);
	Set_Y(((rand()%25)+1)*20);
	Set_Size(20);
	Set_Type(rand()%4);
	Set_Anim(0);
	
	Img_Sentry = DC_Load("pixmaps/man_sen.png");
	Img_Random = DC_Load("pixmaps/man_rnd.png");
	Img_Follow = DC_Load("pixmaps/man_flw.png");
	Img_Opposite = DC_Load("pixmaps/man_opp.png");
	
}


//sets this man 'X' coordinate
void DC_Man::Set_X(int x) {
	X = x;
}
	
//sets this man 'Y' coordinate
void DC_Man::Set_Y(int y) {
	Y = y;
}

//sets this man's Size
void DC_Man::Set_Size(int size) {
	Size = size;
}
//sets this man's type
void DC_Man::Set_Type(int type) {
	Type = type;
}
//sets this man's animation phase
void DC_Man::Set_Anim(int anim) {
	Anim = anim;
}

//draws man to screen
void DC_Man::Draw() {
	if(Get_Type()==SENTRY) { Man_Surface = Img_Sentry; }
	else if(Get_Type()==FOLLOW) { Man_Surface= Img_Follow; }
	else if(Get_Type()==OPPOSITE) { Man_Surface= Img_Opposite; }
	else if(Get_Type()==RANDOM) { Man_Surface= Img_Random; }
	//set the color-key to pure blue
	SDL_SetColorKey(Man_Surface, SDL_SRCCOLORKEY|SDL_RLEACCEL,
		SDL_MapRGB(Man_Surface->format, 0, 0, 255));
	DC_Draw( Man_Surface,Get_X(),Get_Y() );
}
//moves man of given type in given direction in 
void DC_Man::Move(int last_direction,int active) {
	//if (active != 8) return;
	int direction;
	int type;
	type = Get_Type();
	
	switch(type) 
	{
		case SENTRY:
			//SENTRY's don't move!
			break;
		case RANDOM:
			direction=rand()%4;
			if(direction==UP && Get_Y()-Get_Size() !=0)
				Set_Y(Get_Y()-Get_Size());
			else if(direction==DOWN && Get_Y()+Get_Size() !=520)
				Set_Y(Get_Y()+Get_Size());
			else if(direction==LEFT && Get_X()-Get_Size() !=0)
				Set_X(Get_X()-Get_Size());
			else if(direction==RIGHT && Get_X()+Get_Size() !=780)
				Set_X(Get_X()+Get_Size());
			break;
		case FOLLOW:
			if(last_direction==UP && Get_Y()-Get_Size() !=0)
				Set_Y(Get_Y()-Get_Size());
			else if(last_direction==DOWN && Get_Y()+Get_Size() !=520)
				Set_Y(Get_Y()+Get_Size());
			else if(last_direction==LEFT && Get_X()-Get_Size() !=0)
				Set_X(Get_X()-Get_Size());
			else if(last_direction==RIGHT && Get_X()+Get_Size() !=780)
				Set_X(Get_X()+Get_Size());
			break;
		case OPPOSITE:
			if(last_direction == UP && Get_Y()+Get_Size() !=520)
				Set_Y(Get_Y()+Get_Size());
			if(last_direction == DOWN && Get_Y()-Get_Size() !=0)
				Set_Y(Get_Y()-Get_Size());
			if(last_direction == LEFT && Get_X()+Get_Size() !=780)
				Set_X(Get_X()+Get_Size());
			if(last_direction == RIGHT && Get_X()-Get_Size() !=0)
				Set_X(Get_X()-Get_Size());
	}		
		
}
void DC_Man::Set_OuchX(int ouch, int x) {
	Ouch = ouch;
	OuchX = x; 
}
void DC_Man::Set_OuchY(int ouch, int y) {
	Ouch = ouch;
	OuchY = y; 
}
void DC_Man::Set_Ouch(int ouch, int x, int y) {
	Ouch = ouch;
	OuchX = x;
	OuchY = y;
}
