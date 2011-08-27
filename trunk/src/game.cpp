
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
//#include <SDL/SDL_image.h>
#include <time.h>
#include "game.h"
#include "define.h"

using namespace std;

DC_Game::DC_Game(void) {
	Set_Music(0);
	Set_Players(1);
	Set_Level(1);
	Set_Difficulty(1);
	Set_Respawn(0);
	Set_Win(0);
	Set_Obstacle_Formation(0);
	Set_Snap(0);
	Set_Level_Points(0);
	Set_Menu_Location(0);
	Set_Mode(0);
}
//sets the move count
void DC_Game::Set_Active(int active) {
	Active = active;
}
//sets the difficulty
void DC_Game::Set_Difficulty(int difficulty) {
	Difficulty = difficulty;
	if(difficulty==1) {
		Set_Men(5);
		Set_Man_Length(0);
		Set_Obstacles(5);
		Set_Speed(130);
	}
	else if(difficulty==2) {
		Set_Men(5);
		Set_Man_Length(1);
		Set_Obstacles(7);
		Set_Speed(120);
	}
	else if(difficulty==3) {
		Set_Men(4);
		Set_Man_Length(2);
		Set_Obstacles(9);
		Set_Speed(120);
	}
	else if(difficulty==4) {
		Set_Men(4);
		Set_Man_Length(3);
		Set_Obstacles(11);
		Set_Speed(110);
	}
	else if(difficulty==5) {
		Set_Men(4);
		Set_Man_Length(3);
		Set_Obstacles(13);
		Set_Speed(110);
	}
	else if(difficulty==6) {
		Set_Men(3);
		Set_Man_Length(4);
		Set_Obstacles(15);
		Set_Speed(110);
	}
	else if(difficulty==7) {
		Set_Men(3);
		Set_Man_Length(4);
		Set_Obstacles(17);
		Set_Speed(100);
	}
	else if(difficulty==8) {
		Set_Men(2);
		Set_Man_Length(5);
		Set_Obstacles(19);
		Set_Speed(100);
	}
	else if(difficulty==9) {
		Set_Men(2);
		Set_Man_Length(6);
		Set_Obstacles(22);
		Set_Speed(90);
	}
	if(Get_Mode()==LONGEST) { 
		Set_Men(1);
		Set_Man_Length(0);
		Set_Obstacles(0);
	}
}
//sets the level
void DC_Game::Set_Level(int level) {
	Level = level;
}
//sets the number of points the level currently has accumulated
void DC_Game::Set_Level_Points(int points) {
	Points = points;
}
//sets the man value for extending the snake
void DC_Game::Set_Man_Length(int manlength) {
	ManLength = manlength;
}
//sets the number of men currently active
void DC_Game::Set_Men(int men) {
	Men = men;
}
//sets the menu location that is currently highlighted
void DC_Game::Set_Menu_Location(int location) {
	Location = location;
}
//sets the music on/off
void DC_Game::Set_Music(int music) {
	Music = music;
}
//sets the number of obstacles currently active
void DC_Game::Set_Obstacles(int obstacles) {
	Obstacles = obstacles;
}
//sets obstacle formation
void DC_Game::Set_Obstacle_Formation(int form) {
	Form = form;
}
//sets the game into/outof pause mode
void DC_Game::Set_Pause(int pause) {
	Pause = pause;
}
//sets the number of players
void DC_Game::Set_Players(int players) {
	Players = players;
}
//sets the respawn mode
void DC_Game::Set_Respawn(int respawn) {
	Respawn = respawn;
}
//sets the snap counter
void DC_Game::Set_Snap(int snap) {
	Snap = snap;
}
//sets the current speed (rate)
void DC_Game::Set_Speed(int speed) {
	Speed = speed;
}
//sets if the whole screen needs to be SDL_UpdateRect'd
void DC_Game::Set_Update(int updateall) {
	Update = updateall;
}
//sets the game as won
void DC_Game::Set_Win(int win) {
	Win = win;
}
//sets the game mode (single, multi, longest, etc)
void DC_Game::Set_Mode(int mode) {
	Mode = mode;
	if(Mode == SINGLE) { 
		Set_Players(1); 
		Set_Respawn(0);
	}
	if(Mode == TWOPLAYER) { 
		Set_Players(2); 
		Set_Respawn(0);
	}
	if(Mode == INSTANT) { 
		Set_Players(2);
		Set_Respawn(1);
	}
	if(Mode == LONGEST) { 
		Set_Players(1); 
		Set_Respawn(0);
	}
}
