#ifndef MAN_H
#define MAN_H

#include "define.h"

/*---------------------------------------------------------*/
/* The 'DC_Man' class is used for making a movable man     */
/* for use in the DC Project. Its functions are as follows */
/*---------------------------------------------------------*/

class DC_Man {
	public:
	
	//man surface
	SDL_Surface *Man_Surface;
	
	//default constructor
	DC_Man(void);
	
	//returns the 'X' coordinate of this man
	int Get_X(void)		{ return X; };
	
	//returns the 'Y' coordinate of this man
	int Get_Y(void)		{ return Y; };
	
	//returns the size (in pixels) of this man
	int Get_Size(void)		{ return Size; };
	
	//sets this man 'X' coordinate
	void Set_X(int x);	
	
	//sets this man 'Y' coordinate
	void Set_Y(int y);	
	
	//sets this man's type
	void Set_Type(int type);
	
	//egts this man's type
	int Get_Type(void) { return Type; };

	//sets this man's animation phase
	void Set_Anim(int anim);
	
	//gets this man's animation phase
	int Get_Anim(void) { return Anim; };
	
	//sets this man's size
	void Set_Size(int size);
	
	//inits man to screen
	void Draw();
	
	//sets this man's x/y coords on his "ouch"
	void Set_OuchX(int ouch, int x);
	
	//gets ouch
	int Get_OuchX(void) { return OuchX; };
	
	void Set_Ouch(int ouch, int x, int y);
	
	int Get_Ouch(void) { return Ouch; };

	//sets this man's x/y coords on his "ouch"
	void Set_OuchY(int ouch, int y);
	
	//gets ouch
	int Get_OuchY(void) { return OuchY; };
	
	//moves the man in a given direction
	void Move(int last_direction, int active);
	
	private:

	//declares vars
	int direction;
	int X,Y;
	int Size;
	int Type;
	int Ouch;
	int OuchX;
	int OuchY;
	int Anim;
	
	SDL_Surface *Img_Sentry;
	SDL_Surface *Img_Random;
	SDL_Surface *Img_Follow;
	SDL_Surface *Img_Opposite;

};


#endif
