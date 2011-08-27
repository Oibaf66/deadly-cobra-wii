		//Snake class Module

#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
//#include <SDL/SDL_image.h>
#include <time.h>
#include "snake.h"
#include "bitmap.h"

#include <wiiuse/wpad.h> 

using namespace std;

/*-------------------------------------------*/
/* function definitions for Snake_Part class */
/*-------------------------------------------*/

//sets this part's image size (in pixels)
void Snake_Part::Set_Size(int size) {
	Size = size;
}
	
//sets this part's 'X' coordinate
void Snake_Part::Set_X(int x) {
	X = x;
}
	
//sets this part's 'Y' coordinate
void Snake_Part::Set_Y(int y) {
	Y = y;
}
//sets direction
void Snake_Part::Set_Direction(int direction) {
	Direction = direction;
}

/*sets Full on/off (1/0)
void Snake_Part::Set_Full(int full) {
	Full = full;
}
*/
/*-------------</Snake_Part>---------------*/

/////////////////////////////////////////////

/*-----------------------------------------*/
/* function definitions for DC_Snake class */
/*-----------------------------------------*/

//default constructor
DC_Snake::DC_Snake(void) {
	Blank = DC_Load("pixmaps/blank.png");
	Set_Current_Direction(RIGHT);
	Reset(100, 100, RIGHT,1);
	Set_Lives(0);
	Set_Alive(0);
	Set_Blink(0);
	Alpha = 255;
}

void DC_Snake::Set_Score(int score) {
	Scores = score;
}
void DC_Snake::Set_Lives(int lives) {
	Lives = lives;
}
void DC_Snake::Set_Alive(int alive) {
	Alive = alive;
}
//returns if part is blank
int DC_Snake::Get_Blank(int i) {
	if(Body[i].Part_Surface==Blank) { return 1; }
	else return 0;
}

void DC_Snake::Reset(int x, int y, int direction, int player) {
	int i;
	//initializes snake's length in parts
	Set_Length(5);
	Set_Full(0);
	if(player==1) {
		Cobra_Body_LR = DC_Load("pixmaps/cobra_body-LR.png");
		Cobra_Body_LR = SDL_DisplayFormat(Cobra_Body_LR);
		Cobra_Body_LR_F = DC_Load("pixmaps/cobra_body-LR_F.png");
		Cobra_Body_LR_F = SDL_DisplayFormat(Cobra_Body_LR_F);
		Cobra_Head_U = DC_Load("pixmaps/cobra_head-U.png");
		Cobra_Head_U = SDL_DisplayFormat(Cobra_Head_U);
		Cobra_Head_D = DC_Load("pixmaps/cobra_head-D.png");
		Cobra_Head_D = SDL_DisplayFormat(Cobra_Head_D);
		Cobra_Head_L = DC_Load("pixmaps/cobra_head-L.png");
		Cobra_Head_L = SDL_DisplayFormat(Cobra_Head_L);
		Cobra_Head_R = DC_Load("pixmaps/cobra_head-R.png");
		Cobra_Head_R = SDL_DisplayFormat(Cobra_Head_R);
		Cobra_Body_RD_UL = DC_Load("pixmaps/cobra_body-RD-UL.png");
		Cobra_Body_RD_UL = SDL_DisplayFormat(Cobra_Body_RD_UL);
		Cobra_Body_RD_UL_F = DC_Load("pixmaps/cobra_body-RD-UL_F.png");
		Cobra_Body_RD_UL_F = SDL_DisplayFormat(Cobra_Body_RD_UL_F);
		Cobra_Body_UR_LD = DC_Load("pixmaps/cobra_body-UR-LD.png");
		Cobra_Body_UR_LD = SDL_DisplayFormat(Cobra_Body_UR_LD);
		Cobra_Body_UR_LD_F = DC_Load("pixmaps/cobra_body-UR-LD_F.png");
		Cobra_Body_UR_LD_F = SDL_DisplayFormat(Cobra_Body_UR_LD_F);
		Cobra_Body_LU_DR = DC_Load("pixmaps/cobra_body-LU-DR.png");
		Cobra_Body_LU_DR = SDL_DisplayFormat(Cobra_Body_LU_DR);
		Cobra_Body_LU_DR_F = DC_Load("pixmaps/cobra_body-LU-DR_F.png");
		Cobra_Body_LU_DR_F = SDL_DisplayFormat(Cobra_Body_LU_DR_F);
		Cobra_Body_DL_RU = DC_Load("pixmaps/cobra_body-DL-RU.png");
		Cobra_Body_DL_RU = SDL_DisplayFormat(Cobra_Body_DL_RU);
		Cobra_Body_DL_RU_F = DC_Load("pixmaps/cobra_body-DL-RU_F.png");
		Cobra_Body_DL_RU_F = SDL_DisplayFormat(Cobra_Body_DL_RU_F);
		Cobra_Body_UD = DC_Load("pixmaps/cobra_body-UD.png");
		Cobra_Body_UD = SDL_DisplayFormat(Cobra_Body_UD);
		Cobra_Body_UD_F = DC_Load("pixmaps/cobra_body-UD_F.png");
		Cobra_Body_UD_F = SDL_DisplayFormat(Cobra_Body_UD_F);
		Cobra_Tail_U = DC_Load("pixmaps/cobra_tail-U.png");
		Cobra_Tail_U = SDL_DisplayFormat(Cobra_Tail_U);
		Cobra_Tail_D = DC_Load("pixmaps/cobra_tail-D.png");
		Cobra_Tail_D = SDL_DisplayFormat(Cobra_Tail_D);
		Cobra_Tail_L = DC_Load("pixmaps/cobra_tail-L.png");
		Cobra_Tail_L = SDL_DisplayFormat(Cobra_Tail_L);
		Cobra_Tail_R = DC_Load("pixmaps/cobra_tail-R.png");
		Cobra_Tail_R = SDL_DisplayFormat(Cobra_Tail_R);
		Cobra_Dead = DC_Load("pixmaps/cobra_dead.png");
	}
	if(player==2) {
		Cobra_Body_LR = DC_Load("pixmaps/cobra_body-LR2.png");
		Cobra_Body_LR = SDL_DisplayFormat(Cobra_Body_LR);
		Cobra_Body_LR_F = DC_Load("pixmaps/cobra_body-LR_F2.png");
		Cobra_Body_LR_F = SDL_DisplayFormat(Cobra_Body_LR_F);
		Cobra_Head_U = DC_Load("pixmaps/cobra_head-U2.png");
		Cobra_Head_U = SDL_DisplayFormat(Cobra_Head_U);
		Cobra_Head_D = DC_Load("pixmaps/cobra_head-D2.png");
		Cobra_Head_D = SDL_DisplayFormat(Cobra_Head_D);
		Cobra_Head_L = DC_Load("pixmaps/cobra_head-L2.png");
		Cobra_Head_L = SDL_DisplayFormat(Cobra_Head_L);
		Cobra_Head_R = DC_Load("pixmaps/cobra_head-R2.png");
		Cobra_Head_R = SDL_DisplayFormat(Cobra_Head_R);
		Cobra_Body_RD_UL = DC_Load("pixmaps/cobra_body-RD-UL2.png");
		Cobra_Body_RD_UL = SDL_DisplayFormat(Cobra_Body_RD_UL);
		Cobra_Body_RD_UL_F = DC_Load("pixmaps/cobra_body-RD-UL_F2.png");
		Cobra_Body_RD_UL_F = SDL_DisplayFormat(Cobra_Body_RD_UL_F);
		Cobra_Body_UR_LD = DC_Load("pixmaps/cobra_body-UR-LD2.png");
		Cobra_Body_UR_LD = SDL_DisplayFormat(Cobra_Body_UR_LD);
		Cobra_Body_UR_LD_F = DC_Load("pixmaps/cobra_body-UR-LD_F2.png");
		Cobra_Body_UR_LD_F = SDL_DisplayFormat(Cobra_Body_UR_LD_F);
		Cobra_Body_LU_DR = DC_Load("pixmaps/cobra_body-LU-DR2.png");
		Cobra_Body_LU_DR = SDL_DisplayFormat(Cobra_Body_LU_DR);
		Cobra_Body_LU_DR_F = DC_Load("pixmaps/cobra_body-LU-DR_F2.png");
		Cobra_Body_LU_DR_F = SDL_DisplayFormat(Cobra_Body_LU_DR_F);
		Cobra_Body_DL_RU = DC_Load("pixmaps/cobra_body-DL-RU2.png");
		Cobra_Body_DL_RU = SDL_DisplayFormat(Cobra_Body_DL_RU);
		Cobra_Body_DL_RU_F = DC_Load("pixmaps/cobra_body-DL-RU_F2.png");
		Cobra_Body_DL_RU_F = SDL_DisplayFormat(Cobra_Body_DL_RU_F);
		Cobra_Body_UD = DC_Load("pixmaps/cobra_body-UD2.png");
		Cobra_Body_UD = SDL_DisplayFormat(Cobra_Body_UD);
		Cobra_Body_UD_F = DC_Load("pixmaps/cobra_body-UD_F2.png");
		Cobra_Body_UD_F = SDL_DisplayFormat(Cobra_Body_UD_F);
		Cobra_Tail_U = DC_Load("pixmaps/cobra_tail-U2.png");
		Cobra_Tail_U = SDL_DisplayFormat(Cobra_Tail_U);
		Cobra_Tail_D = DC_Load("pixmaps/cobra_tail-D2.png");
		Cobra_Tail_D = SDL_DisplayFormat(Cobra_Tail_D);
		Cobra_Tail_L = DC_Load("pixmaps/cobra_tail-L2.png");
		Cobra_Tail_L = SDL_DisplayFormat(Cobra_Tail_L);
		Cobra_Tail_R = DC_Load("pixmaps/cobra_tail-R2.png");
		Cobra_Tail_R = SDL_DisplayFormat(Cobra_Tail_R);
		Cobra_Dead = DC_Load("pixmaps/cobra_dead.png");
	}
		
	for(i=0;i<MAX_SIZE;i++) {
		Body[i].Part_Surface = Blank;
		Body[i].Set_Size(20);
		Body[i].Set_X(x);
		Body[i].Set_Y(y);
		Body[i].Set_Direction(direction);
		Body[i].Active=0;
		Body[i].Full=0;
	}
	
	//Set snakes starting position
	Body[HEAD].Set_X(x);
	Body[HEAD].Set_Y(y);
	Body[1].Set_X(x-20);
	Body[2].Set_X(x-40);
	Body[3].Set_X(x-60);
	Body[4].Set_X(x-80);
	Body[5].Set_X(x-100);
	
	//activates the snake's pixel-size and surfaces
	for(i=0;i<=Get_Length();i++) {
			Body[i].Part_Surface= Cobra_Body_LR; 
			Body[i].Active = 1;
	}
	Draw(RIGHT,RIGHT);
}

//sets this part's image size (in pixels)
void DC_Snake::Set_Length(int length) {
	Length = length;
}

//handles eaten man to flow down snake's body
void DC_Snake::Set_Full(int full) {		
	Full = full;
	Part = 1;
	Body[1].Full = 1;
}
//handles blinking snake for invulnerability
void DC_Snake::Set_Blink(int blink) {
	Blink = blink;
}

//changes alpha level from 128->255 or 255->128
void DC_Snake::Switch_Alpha(void) {
	if (Get_Alpha()==128) { Set_Alpha(255); }
	else Set_Alpha(128);
	SDL_SetAlpha(Cobra_Head_U, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Head_D, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Head_L, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Head_R, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Tail_U, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Tail_D, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Tail_L, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Tail_R, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Body_LR, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Body_LR_F, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Body_RD_UL, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Body_RD_UL_F, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Body_UR_LD, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Body_UR_LD_F, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Body_LU_DR, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Body_LU_DR_F, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Body_DL_RU, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Body_DL_RU_F, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Body_UD, SDL_SRCALPHA, Alpha);
	SDL_SetAlpha(Cobra_Body_UD_F, SDL_SRCALPHA, Alpha);
}
//handles setting alpha level
void DC_Snake::Set_Alpha(int alpha) {
	Alpha = alpha;
}

//inits snake to 'screen'
void DC_Snake::Draw(int direction,int last_direction) {
	int i;
	int i2=0;
	//Body[HEAD].Set_Direction(direction);
	for(i=0;i<=Get_Length();i++) {
		if(Body[i].Active == 1) {
			
			//Load the HEAD of snake BMP according to 'direction'
			if(i==HEAD && direction==UP) {
				Body[HEAD].Part_Surface= Cobra_Head_U;
			}
			else if(i==HEAD && direction==DOWN) {
				Body[HEAD].Part_Surface= Cobra_Head_D;
			}
			else if(i==HEAD && direction==LEFT) {
				Body[HEAD].Part_Surface= Cobra_Head_L;
			}
			else if(i==HEAD && direction==RIGHT) {
				Body[HEAD].Part_Surface= Cobra_Head_R;
			}
			else if(i==HEAD && direction==99) { 
				Body[HEAD].Part_Surface= Cobra_Dead;
			}
			else if(i==HEAD && direction==98) { 
				Body[HEAD].Part_Surface= Cobra_Dead;
			}
//			//Load the TAIL of snake according to TAIL-1 x/y coords
			else if(i==TAIL && Body[TAIL].Part_Surface!= Blank) {
				if(Body[i-1].Get_Y() < Body[TAIL].Get_Y()) { Body[TAIL].Part_Surface= Cobra_Tail_U; }
				if(Body[i-1].Get_Y() > Body[TAIL].Get_Y()) { Body[TAIL].Part_Surface= Cobra_Tail_D; }
				if(Body[i-1].Get_X() < Body[TAIL].Get_X()) { Body[TAIL].Part_Surface= Cobra_Tail_L; }
				if(Body[i-1].Get_X() > Body[TAIL].Get_X()) { Body[TAIL].Part_Surface= Cobra_Tail_R; }
			}
			else if(Body[i].Part_Surface==Blank && i2==0) {
				i2++;
				if(Body[i-2].Get_Y() < Body[i-1].Get_Y()) { Body[i-1].Part_Surface= Cobra_Tail_U; }
				if(Body[i-2].Get_Y() > Body[i-1].Get_Y()) { Body[i-1].Part_Surface= Cobra_Tail_D; }
				if(Body[i-2].Get_X() < Body[i-1].Get_X()) { Body[i-1].Part_Surface= Cobra_Tail_L; }
				if(Body[i-2].Get_X() > Body[i-1].Get_X()) { Body[i-1].Part_Surface= Cobra_Tail_R; }
			}	
			//Load the body of snake BMP according to 'direction'

			else if((i==1 && (direction==RIGHT && last_direction==DOWN)) || 
			 (direction==UP && last_direction==LEFT)) {
				Body[1].Part_Surface= Cobra_Body_RD_UL; 
			}
			else if((i==1 && (direction==UP && last_direction==RIGHT)) || 
			 (direction==LEFT && last_direction==DOWN)) {
				Body[1].Part_Surface= Cobra_Body_UR_LD; 
			}
			else if((i==1 && (direction==LEFT && last_direction==UP)) || 
			 (direction==DOWN && last_direction==RIGHT)) {
				Body[1].Part_Surface= Cobra_Body_LU_DR;
			}
			else if((i==1 && (direction==DOWN && last_direction==LEFT)) || 
			 (direction==RIGHT && last_direction==UP)) {
				Body[1].Part_Surface= Cobra_Body_DL_RU; 
			}
			else if((i==1 && (direction==UP  && last_direction==UP)) || 
			 (direction==DOWN && last_direction==DOWN)) {
				Body[1].Part_Surface= Cobra_Body_UD; 
			}
			else if((i==1 && (direction==LEFT && last_direction==LEFT)) || 
			 (direction==RIGHT && last_direction==RIGHT)) {
				Body[1].Part_Surface= Cobra_Body_LR;
			}
			//NEW: if Not Full, change part XX_XX_F to XX_XX
			if(Body[i].Full==0 && Body[i].Part_Surface==Cobra_Body_RD_UL_F) {
				Body[i].Part_Surface= Cobra_Body_RD_UL;
			}
			else if(Body[i].Full==0 && Body[i].Part_Surface==Cobra_Body_UR_LD_F) {
				Body[i].Part_Surface= Cobra_Body_UR_LD;
			}
			else if(Body[i].Full==0 && Body[i].Part_Surface==Cobra_Body_LU_DR_F) {
				Body[i].Part_Surface= Cobra_Body_LU_DR;
			}
			else if(Body[i].Full==0 && Body[i].Part_Surface==Cobra_Body_DL_RU_F) {
				Body[i].Part_Surface= Cobra_Body_DL_RU;
			}
			else if(Body[i].Full==0 && Body[i].Part_Surface==Cobra_Body_UD_F) {
				Body[i].Part_Surface= Cobra_Body_UD;
			}
			else if(Body[i].Full==0 && Body[i].Part_Surface==Cobra_Body_LR_F) {
				Body[i].Part_Surface= Cobra_Body_LR;
			}
			
			
			//NEW: if Full, change part XX_XX to XX_XX_F
			if(Body[i].Full==1 && Body[i].Part_Surface==Cobra_Body_RD_UL) {
				Body[i].Part_Surface= Cobra_Body_RD_UL_F;
			}
			else if(Body[i].Full==1 && Body[i].Part_Surface==Cobra_Body_UR_LD) {
				Body[i].Part_Surface= Cobra_Body_UR_LD_F;
			}
			else if(Body[i].Full==1 && Body[i].Part_Surface==Cobra_Body_LU_DR) {
				Body[i].Part_Surface= Cobra_Body_LU_DR_F;
			}
			else if(Body[i].Full==1 && Body[i].Part_Surface==Cobra_Body_DL_RU) {
				Body[i].Part_Surface= Cobra_Body_DL_RU_F;
			}
			else if(Body[i].Full==1 && Body[i].Part_Surface==Cobra_Body_UD) {
				Body[i].Part_Surface= Cobra_Body_UD_F;
			}
			else if(Body[i].Full==1 && Body[i].Part_Surface==Cobra_Body_LR) {
				Body[i].Part_Surface= Cobra_Body_LR_F;
			}
			

			//set the color-key to pure blue
			SDL_SetColorKey(Body[i].Part_Surface, SDL_SRCCOLORKEY|SDL_RLEACCEL,
				SDL_MapRGB(Body[i].Part_Surface->format, 0, 0, 255));
			
			//draw the snake from HEAD to TAIL
			DC_Draw( Body[i].Part_Surface, Body[i].Get_X() , Body[i].Get_Y() );
		}
	}
	//NEW: Moves full down to the next piece
	for(i=0;i<=Get_Length();i++) {
		if(Body[i].Active == 1) {
			if(Body[i].Full==1) {
				Body[i].Full=0;
					i=i+2;
					Body[i].Full=1;
			}
		}
	}
}

void DC_Snake::DisplayALL(int y) {
	int i;
	Set_Length(20);
	Body[0].Part_Surface=Cobra_Head_U;
	Body[1].Part_Surface=Cobra_Head_D;
	Body[2].Part_Surface=Cobra_Head_L;
	Body[3].Part_Surface=Cobra_Head_R;
	Body[4].Part_Surface=Cobra_Tail_U;
	Body[5].Part_Surface=Cobra_Tail_D;
	Body[6].Part_Surface=Cobra_Tail_L;
	Body[7].Part_Surface=Cobra_Tail_R;
	Body[8].Part_Surface=Cobra_Body_LR;
	Body[9].Part_Surface=Cobra_Body_RD_UL;
	Body[10].Part_Surface=Cobra_Body_UR_LD;
	Body[11].Part_Surface=Cobra_Body_LU_DR;
	Body[12].Part_Surface=Cobra_Body_DL_RU;
	Body[13].Part_Surface=Cobra_Body_UD;
	Body[14].Part_Surface=Cobra_Body_LR_F;
	Body[15].Part_Surface=Cobra_Body_RD_UL_F;
	Body[16].Part_Surface=Cobra_Body_UR_LD_F;
	Body[17].Part_Surface=Cobra_Body_LU_DR_F;
	Body[18].Part_Surface=Cobra_Body_DL_RU_F;
	Body[19].Part_Surface=Cobra_Body_UD_F;
	for(i=0;i<=Get_Length();i++) {
		SDL_SetColorKey(Body[i].Part_Surface, SDL_SRCCOLORKEY|SDL_RLEACCEL,
				SDL_MapRGB(Body[i].Part_Surface->format, 0, 0, 255));
		DC_Draw( Body[i].Part_Surface, i*20+200 , y);
	}
}
	
//adds a 'piece' onto the snake
void DC_Snake::Add_Piece(int num_pieces) {
	int i;
	for(i=0;i<num_pieces;i++) {
		Set_Length(Get_Length()+1);
		Body[Get_Length()].Active = 1;
	}
}
	
//removes a 'piece from the snake
void DC_Snake::Rem_Piece(int num_pieces) {
	int i;
	for(i=0;i<num_pieces;i++) {
		Body[Get_Length()].Part_Surface= Blank;
		Body[Get_Length()].Active = 0;
		Set_Length(Get_Length()-1);
	}
}
//sets snake's current direction
void DC_Snake::Set_Current_Direction(int current_direction) {
	Current_Direction = current_direction;
}
//moves the snake in a given direction
void DC_Snake::Move(int direction) {
	
	int i;
	//int Last_Direction;
	
	switch(direction) {
		case UP:
			for(i=Get_Length()+1;i>=1;i--) {
				//Set the previous 'Body' image Surface of [i-1] to i
				Body[i].Part_Surface=Body[i-1].Part_Surface;
				//Set the previous 'Body' X/Y coordinates of [i-1] to i
				Body[i].Set_X(Body[i-1].Get_X());
				Body[i].Set_Y(Body[i-1].Get_Y());
				//Set the previous 'Direction' of i-1 to i
				//Body[i].Set_Direction(Body[i-1].Get_Direction());
			}
			//Move the 'HEAD' UP by the pixel-width of a Snake_Part
			Body[HEAD].Set_Y( Body[HEAD].Get_Y()-Body[HEAD].Get_Size() );
			break;
		case DOWN:
			for(i=Get_Length()+1;i>=1;i--) {
				//Set the previous 'Body' image Surface of [i-1] to i
				Body[i].Part_Surface=Body[i-1].Part_Surface;
				//Set the previous 'Body' X/Y coordinates of [i-1] to i
				Body[i].Set_X(Body[i-1].Get_X());
				Body[i].Set_Y(Body[i-1].Get_Y());
				//Set the previous 'Direction' of i-1 to i
				//Body[i].Set_Direction(Body[i-1].Get_Direction());
			}
			//Move the 'HEAD' DOWN by the pixel-width of a Snake_Part
			Body[HEAD].Set_Y( Body[HEAD].Get_Y()+Body[HEAD].Get_Size() );
			break;
		case LEFT:
			for(i=Get_Length()+1;i>=1;i--) {
				//Set the previous 'Body' image Surface of [i-1] to i
				Body[i].Part_Surface=Body[i-1].Part_Surface;
				//Set the previous 'Body' X/Y coordinates of [i-1] to i
				Body[i].Set_X(Body[i-1].Get_X());
				Body[i].Set_Y(Body[i-1].Get_Y());
				//Set the previous 'Direction' of i-1 to i
				//Body[i].Set_Direction(Body[i-1].Get_Direction());
			}
			//Move the 'HEAD' LEFT by the pixel-width of a Snake_Part
			Body[HEAD].Set_X( Body[HEAD].Get_X()-Body[HEAD].Get_Size() );
			break;
		case RIGHT:
			for(i=Get_Length()+1;i>=1;i--) {
				//Set the previous 'Body' image Surface of [i-1] to i
				Body[i].Part_Surface=Body[i-1].Part_Surface;
				//Set the previous 'Body' X/Y coordinates of [i-1] to i
				Body[i].Set_X(Body[i-1].Get_X());
				Body[i].Set_Y(Body[i-1].Get_Y());
				//Set the previous 'Direction' of i-1 to i
				//Body[i].Set_Direction(Body[i-1].Get_Direction());
			}
			//Move the 'HEAD' RIGHT by the pixel-width of a Snake_Part
			Body[HEAD].Set_X( Body[HEAD].Get_X()+Body[HEAD].Get_Size() );
			break;
		default:
			cout << "ERR: Couldn't Move!";
	 }
}

//Wiimote Rumble
void DC_Snake::Rumble(int player) {
	WPAD_Rumble(player, true);
	SDL_Delay(150);
	WPAD_Rumble(player, false);
}

/*-------------</DC_Snake_Part>--------------*/
