#ifndef ENEMY_H
#define ENEMY_H

#include "define.h"

/*---------------------------------------------------------*/
/* The 'DC_Enemy' class is used for making a movable enemy     */
/* for use in the DC Project. Its functions are as follows */
/*---------------------------------------------------------*/

class DC_Enemy {
	public:
	
	//enemy surface
	SDL_Surface *Enemy_Surface;
	
	//default constructor
	DC_Enemy(void);
	
	//returns the 'X' coordinate of this enemy
	int Get_X(void)		{ return X; };
	
	//returns the 'Y' coordinate of this enemy
	int Get_Y(void)		{ return Y; };
	
	//returns the size (in pixels) of this enemy
	int Get_Size(void)		{ return Size; };
	
	//sets this enemy 'X' coordinate
	void Set_X(int x);	
	
	//sets this enemy 'Y' coordinate
	void Set_Y(int y);	
	
	//sets this enemy's type
	void Set_Type(int type);
	
	//egts this enemy's type
	int Get_Type(void) { return Type; };
	
	//sets this enemy's size
	void Set_Size(int size);
	
	//inits enemy to screen
	void Draw();
	
	//moves the enemy in a given direction
	void Move(int last_direction, int active);
	
	private:

	//declares vars
	int direction;
	int X,Y;
	int Size;
	int Type;
	
	SDL_Surface *Img_Enemy;

};


#endif
