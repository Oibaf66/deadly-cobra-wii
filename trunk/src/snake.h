#ifndef SNAKE_H
#define SNAKE_H

#include "define.h"

/*--------------------------------------------------------*/
/* The 'Snake_Part' class is used for making the abdomen  */
/* of the snake for use in the 'DC_Snake' class. This     */
/* class is not used outside of this module, so knowing   */
/* these member fuctions and variables is not neccessary  */
/* for making a funtional snake game.                     */
/*--------------------------------------------------------*/

class Snake_Part {
	
/* public members of Snake_Part */
	public:
	
	//this is the image surface of this 'part'
	SDL_Surface *Part_Surface;
	
	//returns a snake piece's size (in pixels)
	int Get_Size(void)	{ return Size; };
	
	//returns the 'X' coordinate of this snake part
	int Get_X(void)		{ return X; };
	
	//returns the 'Y' coordinate of this snake part
	int Get_Y(void)		{ return Y; };
	
	//sets this part's 'X' coordinate
	void Set_X(int x);	
	
	//sets this part's 'Y' coordinate
	void Set_Y(int y);	
	
	//sets this part's image size (in pixels)
	void Set_Size(int size);
	
	//sets direction
	void Set_Direction(int direction);
	
	//gets direction
	int Get_Direction(void)	{ return Direction; };
	
	//toggle var that decides wheather a part is full (eaten man inside) or not
	int Full;
	
	//toggle var that decides whether a part is active(visible) or not 
	int Active;
	
/* private members of Snake_Part */	
	private:
	
	//declares vars
	int X,Y;
	int Size;
	int Direction;
};



/*---------------------------------------------------------*/
/* The 'DC_Snake' class is used for making a movable snake */
/* for use in the DC Project. Its functions are as follows */
/*---------------------------------------------------------*/

class DC_Snake {
	public:
	
	//default constructor
	DC_Snake(void);
	
	//draws snake to screen
	void Draw(int direction, int last_direction);
	
	//resets snakes starting vars
	void Reset(int x, int y, int direction, int player);
	
	//adds a 'piece' onto the snake
	void Add_Piece(int num_pieces);
	
	//removes a 'piece from the snake
	void Rem_Piece(int num_pieces);
	
	//moves the snake in a given direction
	void Move(int direction);
	
	//set snake's score
	void Set_Score(int score);
	
	//get snake's score
	int Get_Score(void) { return Scores; }
	
	//set snake's lives
	void Set_Lives(int lives);
	
	//get snake's lives
	int Get_Lives(void) { return Lives; }
	
	//length of the snake (in pieces)
	void Set_Length(int length);
	
	//length of the snake (in pieces)
	int Get_Length(void) { return Length; };
	
	//handles food (man) flow through body parts
	void Set_Full(int full);
	
	//sets snake's alive/dead status
	void Set_Alive(int alive);
	
	//gets snake's alive/dead status
	int Get_Alive(void) { return Alive; }
	
	//gets if it is blank or not
	int Get_Blank(int i);
	
	//sets current direction
	void Set_Current_Direction(int current_direction);
	
	//gets current direction
	int Get_Current_Direction(void) { return Current_Direction; };
	
	//sets snake's blinking status
	void Set_Blink(int blink);
	
	//gets snake's blinking status
	int Get_Blink(void) { return Blink; }
	
	//changes alpha level from 128->255 or 255->128
	void Switch_Alpha(void);

	//sets snake's alpha level
	void Set_Alpha(int alpha);
	
	//gets snake's alpha level
	int Get_Alpha(void) { return Alpha; }
	
	void DisplayALL(int y);

	//makes a "body" consisting of 30 snake "parts"
	Snake_Part Body[MAX_SIZE];
	
	
	//Wiimote Rumble
	void Rumble(int player);
	
	private:
	
	//declares vars
	int direction;
	int Scores;
	int Lives;
	int Length;
	int Full;
	int Part;
	int Normal;
	int Alive;
	int Current_Direction;
	int Blink;
	int Alpha;
	
	SDL_Surface *Blank;
	SDL_Surface *Cobra_Body_LR;
	SDL_Surface *Cobra_Body_LR_F;
	SDL_Surface *Cobra_Body_UD;
	SDL_Surface *Cobra_Body_UD_F;
	SDL_Surface *Cobra_Head_U;
	SDL_Surface *Cobra_Head_D;
	SDL_Surface *Cobra_Head_L;
	SDL_Surface *Cobra_Head_R;
	SDL_Surface *Cobra_Dead;
	SDL_Surface *Cobra_Body_RD_UL;
	SDL_Surface *Cobra_Body_RD_UL_F;
	SDL_Surface *Cobra_Body_UR_LD;
	SDL_Surface *Cobra_Body_UR_LD_F;
	SDL_Surface *Cobra_Body_LU_DR;
	SDL_Surface *Cobra_Body_LU_DR_F;
	SDL_Surface *Cobra_Body_DL_RU;
	SDL_Surface *Cobra_Body_DL_RU_F;
	SDL_Surface *Cobra_Tail_U;
	SDL_Surface *Cobra_Tail_D;
	SDL_Surface *Cobra_Tail_L;
	SDL_Surface *Cobra_Tail_R;

};


#endif
