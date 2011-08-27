#ifndef OBSTACLES_H
#define OBSTACLES_H

/*--------------------------------------------------------------------*/
/* The 'DC_Obstacle' class is used for making a stationary obstacle   */
/*     for use in the DC Project. Its functions are as follows        */
/*--------------------------------------------------------------------*/

class DC_Obstacles {
	public:
	
	//obstacle surface
	SDL_Surface *Obstacles_Surface;
	
	//defualt contructor
	DC_Obstacles(void);
	
	//returns the 'X' coordinate of this obstacle
	int Get_X(void)		{ return X; };
	
	//returns the 'Y' coordinate of this obstacle
	int Get_Y(void)		{ return Y; };
	
	//returns the size (in pixels) of this obstacle
	int Get_Size(void)		{ return Size; };
	
	//sets this obstacle 'X' coordinate
	void Set_X(int x);	
	
	//sets this obstacle 'Y' coordinate
	void Set_Y(int y);	
	
	//sets both coords at the same time
	void Set_Coords(int x, int y);
	
	//sets this obstacle's size
	void Set_Size(int size);
	
	//aranges the obstacles in formation 'form' with argument 'i'
	void Arange(int form, int i);
	
	//inits obstacle to screen
	void Draw(int levelnum);

	private:

	//declares vars
	int X,Y;
	int Size;

};

#endif
