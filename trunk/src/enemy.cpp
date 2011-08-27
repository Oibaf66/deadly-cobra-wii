
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
//#include <SDL/SDL_image.h>
#include <time.h>
#include "enemy.h"
#include "bitmap.h"

using namespace std;

DC_Enemy::DC_Enemy(void) {
	
	Set_X(((rand()%38)+1)*20);
	Set_Y(((rand()%25)+1)*20);
	Set_Size(20);
	
	Img_Enemy = DC_Load("pixmaps/enemy_mower.png");
	
}


//sets this enemy 'X' coordinate
void DC_Enemy::Set_X(int x) {
	X = x;
}
	
//sets this enemy 'Y' coordinate
void DC_Enemy::Set_Y(int y) {
	Y = y;
}

//sets this enemy's Size
void DC_Enemy::Set_Size(int size) {
	Size = size;
}
//sets this enemy's type
void DC_Enemy::Set_Type(int type) {
	Type = type;
}

//draws enemy to screen
void DC_Enemy::Draw() {
	Enemy_Surface = Img_Enemy;
	//set the color-key to pure blue
	SDL_SetColorKey(Enemy_Surface, SDL_SRCCOLORKEY|SDL_RLEACCEL,
		SDL_MapRGB(Enemy_Surface->format, 0, 0, 255));
	DC_Draw( Enemy_Surface,Get_X(),Get_Y() );
}
//moves enemy of given type in given direction in 
void DC_Enemy::Move(int last_direction,int active) {
	if (active != 8) return;
	int direction;
	//int type;
	direction=rand()%4;
	if(direction==UP && Get_Y()-Get_Size() !=0)
		Set_Y(Get_Y()-Get_Size());
	else if(direction==DOWN && Get_Y()+Get_Size() !=520)
		Set_Y(Get_Y()+Get_Size());
	else if(direction==LEFT && Get_X()-Get_Size() !=0)
		Set_X(Get_X()-Get_Size());
	else if(direction==RIGHT && Get_X()+Get_Size() !=780)
		Set_X(Get_X()+Get_Size());		
		
}
