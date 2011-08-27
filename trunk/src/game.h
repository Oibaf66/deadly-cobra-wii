#ifndef GAME_H
#define GAME_H


/*---------------------------------------------------------*/
/* The 'DC_Game' class is used for storing game variables  */
/* for use in the DC Project. Its functions are as follows */
/*---------------------------------------------------------*/

class DC_Game {
	public:
	
	
	//default constructor
	DC_Game(void);
	
	//sets the number of men currently active
	void Set_Men(int men);
	
	//returns the number of men currently active
	int Get_Men(void)		{ return Men; };

	//sets the music on/off
	void Set_Music(int music);
	
	//returns if the music is on/off
	int Get_Music(void)		{ return Music; };
	
	//sets the number of obstacles currently active
	void Set_Obstacles(int obstacles);
	
	//returns the number of obstacles currently active
	int Get_Obstacles(void)		{ return Obstacles; };

	//sets the number of players
	void Set_Players(int players);
	
	//returns the number of players
	int Get_Players(void)		{ return Players; };

	//sets the current level
	void Set_Level(int level);
	
	//returns the current level
	int Get_Level(void)		{ return Level; };

	//sets the current difficulty
	void Set_Difficulty(int difficulty);
	
	//returns the current difficulty
	int Get_Difficulty(void)		{ return Difficulty; };

	//sets the current speed
	void Set_Speed(int speed);
	
	//returns the current speed
	unsigned int Get_Speed(void)		{ return Speed; };

	//sets the respawn mode
	void Set_Respawn(int respawn);
	
	//returns the respawn mode
	int Get_Respawn(void)		{ return Respawn; };

	//sets the game as won
	void Set_Win(int win);
	
	//returns if the game has been won
	int Get_Win(void)		{ return Win; };

	//sets the move count
	void Set_Active(int active);
	
	//returns if the move count
	int Get_Active(void)		{ return Active; };

	//sets if the whole screen needs to be SDL_UpdateRect'd
	void Set_Update(int updateall);
	
	//returns if the whole screen needs to be SDL_UpdateRect'd
	int Get_Update(void)		{ return Update; };

	//sets obstacle formation pattern
	void Set_Obstacle_Formation(int form);
	
	//returns obstacle formation pattern
	int Get_Obstacle_Formation(void)		{ return Form; };

	//sets snap count
	void Set_Snap(int snap);
	
	//returns snap count
	int Get_Snap(void)		{ return Snap; };

	//sets the game into/outof pause mode
	void Set_Pause(int pause);
	
	//returns if the game is paused
	int Get_Pause(void)		{ return Pause; };

	//sets the number of points the level currently has accumulated
	void Set_Level_Points(int points);
	
	//returns the number of points the level currently has accumulated
	int Get_Level_Points(void)		{ return Points; };

	//sets the menu locatoin
	void Set_Menu_Location(int location);
	
	//returns the menu location
	int Get_Menu_Location(void)		{ return Location; };

	//sets the man value for extending the snake
	void Set_Man_Length(int manlength);
	
	//returns the man value for extending the snake
	int Get_Man_Length(void)		{ return ManLength; };
	
	//sets the game mode (single, multi, longest, etc)
	void Set_Mode(int mode);
	
	//returns the game mode (single, multi, longest, etc)
	int Get_Mode(void)		{ return Mode; };

	private:

	//declares vars
	int Men;
	int Music;
	int Obstacles;
	int Players;
	int Level;
	int Difficulty;
	int Speed;
	int Respawn;
	int Win;
	int Active;
	int Update;
	int Form;
	int Snap;
	int Pause;
	int Points;
	int Location;
	int ManLength;
	int Mode;

};


#endif
