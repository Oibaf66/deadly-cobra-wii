 /*
  *
  *
  *  DeadlyCobra 0.7.0
  *  http://deadlycobra.sf.net
  *
  *  Lead Design/Coding:
  *  outbak - outbak@users.sourceforge.net
  *
  *  Graphics/Coding:
  *  Dr Zaius X11 - drzaiusx11@users.sourceforge.net
  *
  *  Music:
  *  Cem Kaan - cemkaan@users.sourceforge.net
  * 
  *  Ported to WII by Oibaf - fabio.olimpieri@tin.it
  *
  */
  

//Standard includes
#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>
#include <time.h>
#include "snake.h"
#include "man.h"
#include "obstacles.h"
#include "bitmap.h"
#include "map.h"
#include "enemy.h"
#include "game.h"
#include "define.h"
//#define DEBUG_MAIN
//#define SHOWALL


#include <gccore.h>
#include <fat.h>



using namespace std;

//Global Variables:
DC_Game DeadlyCobra;
DC_Man HottMen[5];
DC_Obstacles Ob[22];
int Current_Directions[2];
int Last_Directions[2];
int f,g;
int i,i2,i3,x,y;
char str [80];
Uint8 *keys;
Uint8 Game = 1;
Uint8 Move_Now = 0;
Uint8 Control_Input[2];
#ifdef DEBUG_MAIN
float debug = 0;
float frames = 0;
float answer;
#endif

//SDL surfaces
SDL_Event event;
SDL_Surface *win, *ready, *screen,  *real_screen, *lives1, *lives2, *go, *gameover, *ouch, *quit, *paused, *defeated;
SDL_Surface *largenum[3];
SDL_Surface *num[10];
//menu surfaces
SDL_Surface *menu, *menu_difficulty, *menu_players, *menu_music, *menu_start, *menu_exit, *menu_high, *menu_difficulty_alt, *menu_players_alt, *menu_music_alt, *menu_start_alt, *menu_exit_alt, *menu_on, *menu_off, *menu_instant, *menu_adventure, *menu_longest, *menu_head_to_head, *menu_instant_head_to_head, *menu_music_menu, *menu_music_grass, *menu_music_snow, *menu_music_desert, *menu_beta;
SDL_Surface *menu_num[10];

SDL_Rect srcrect = {0, 0, 800, 600};
SDL_Rect dstrect = {0, 0, 640, 480};

//audio space
Mix_Music *music[4];
Mix_Chunk *sfx[4];

//Prototypes
void Play_Game(void);
void DC_Quit();
void DC_Level_Reset(DC_Snake *Cobra1, DC_Snake *Cobra2);
void DC_Game_Reset(void);
void DC_Score(int total, int x1, int x2, int x3, int x4, int y, int menu);
void DC_High_Score(int doupdate, int score, int mode);
void DC_Snap_Count(int doupdate, int snapcount);
int DC_Control_Check(void *junk);
void DC_Snake_Die(DC_Snake *Cobrai, DC_Snake *Cobra1, DC_Snake *Cobra2, int player, Map *FieldMap);
void DC_Draw_Game(DC_Snake *Cobra1, DC_Snake *Cobra2, Map *FieldMap);
void DC_Draw_Menu(int location);
void DC_Menu(void);
void DC_Modes(void);
void DC_Music_Up(void);
void DC_Music_Down(void);
void handleKey(SDL_KeyboardEvent key);
void handlejoybutton(SDL_JoyButtonEvent joybutton);

//main()
extern "C" int main(int argc, char **argv) {
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK)<0) {
		printf("Unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);
	
	SDL_JoystickEventState(SDL_ENABLE);
	if (!SDL_JoystickOpen(0)) printf("Couldn't open Joystick 0\n");
	if (!SDL_JoystickOpen(1)) printf("Couldn't open Joystick 1\n");

	
	printf("\x1b[2;0H");

	//initialize libfat library
	if (!fatInitDefault())
	{ 
		printf("Couldn't initialize SD fat subsytem\n\n");
		
		exit(0);
	}
	else
		printf("SD FAT subsytem initialized\n\n");
		
		
		
	SDL_Delay(2000);
	
	// The 2 next istructions are useless for the Wii
	SDL_WM_SetIcon(DC_Load("pixmaps/icon.png"),NULL);
	SDL_WM_SetCaption("Deadly Cobra 0.7.0",NULL);
	
	screen = SDL_SetVideoMode(640, 480, 16, SDL_FULLSCREEN); 
	if (screen == NULL) {
		printf("Unable to set 640x480x16 video: %s\n", SDL_GetError());
		return 1;
	}
	

	/*screen = SDL_CreateRGBSurface(SDL_SWSURFACE, 800, 600, 16, 0, 0, 0, 0);

	if(screen == NULL) {
        fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
        return 1;
    }
	*/
	
	Play_Game();
	while ( SDL_PollEvent(&event) >= 0 ) {
		SDL_WaitEvent(&event);
		if(keys[SDLK_RETURN] == SDL_PRESSED) {
			DC_Game_Reset();
			Play_Game(); 
		}
		if(keys[SDLK_KP_ENTER] == SDL_PRESSED) {
			DC_Game_Reset();
			Play_Game(); 
		}
		if(((event.type == SDL_JOYBUTTONDOWN) && ((event.jbutton.button == 0)||(event.jbutton.button == 9)))) {
			DC_Game_Reset();
			Play_Game(); 
		}
	}
	SDL_Quit();
	return (0);
	exit(0);
}
//Game function
void Play_Game(void) {
	
	//Music Setup
	int audio_rate = 32000;
	int audio_channels = MIX_DEFAULT_CHANNELS;
	int audio_buffers = 1024;
	Uint16 audio_format = MIX_DEFAULT_FORMAT;
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
		printf("Unable to open audio!\n");
		exit(1);
 	}	
	Mix_AllocateChannels(5);
	Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
	music[0] = Mix_LoadMUS("music/dc0.ogg");
	music[1] = Mix_LoadMUS("music/dc1.ogg");
	music[2] = Mix_LoadMUS("music/dc2.ogg");
	music[3] = Mix_LoadMUS("music/dc3.ogg");
	sfx[0] = Mix_LoadWAV("music/sfx0.wav");
	sfx[1] = Mix_LoadWAV("music/sfx1.wav");
	sfx[2] = Mix_LoadWAV("music/sfx2.wav");
	sfx[3] = Mix_LoadWAV("music/sfx3.wav");
	Mix_FadeInMusic(music[0], -1, 3000);
	
	//Misc setup
	srand(time(NULL));
	SDL_ShowCursor(0);
	DC_Snap_Count(0,0);
	DeadlyCobra.Set_Snap(g);
	Control_Input[0] = 1;
	Control_Input[1] = 1;
	Current_Directions[0] = RIGHT;
	Current_Directions[1] = RIGHT;
	Last_Directions[0] = RIGHT;
	Last_Directions[1] = RIGHT;
	
	//Load gfxs onto SDL surfaces
	ouch=DC_Load("pixmaps/ouch.png");
	num[0]=DC_Load("pixmaps/num_0.png");
	num[1]=DC_Load("pixmaps/num_1.png");
	num[2]=DC_Load("pixmaps/num_2.png");
	num[3]=DC_Load("pixmaps/num_3.png");
	num[4]=DC_Load("pixmaps/num_4.png");
	num[5]=DC_Load("pixmaps/num_5.png");
	num[6]=DC_Load("pixmaps/num_6.png");
	num[7]=DC_Load("pixmaps/num_7.png");
	num[8]=DC_Load("pixmaps/num_8.png");
	num[9]=DC_Load("pixmaps/num_9.png");
	lives1=DC_Load("pixmaps/lives_1.png");
	lives2=DC_Load("pixmaps/lives_2.png");
	quit=DC_Load("pixmaps/text_quitgame.png");
	paused=DC_Load("pixmaps/text_paused.png");
	defeated=DC_Load("pixmaps/text_defeated.png");
	go=DC_Load("pixmaps/text_gameover.png");
	//new menu loads
	menu=DC_Load("pixmaps/menu.png");
	menu_difficulty=DC_Load("pixmaps/menu_difficulty.png");
	menu_players=DC_Load("pixmaps/menu_players.png");
	menu_music=DC_Load("pixmaps/menu_music.png");
	menu_start=DC_Load("pixmaps/menu_start.png");
	menu_exit=DC_Load("pixmaps/menu_exit.png");
	menu_high=DC_Load("pixmaps/menu_high.png");
	menu_difficulty_alt=DC_Load("pixmaps/menu_difficulty_alt.png");
	menu_players_alt=DC_Load("pixmaps/menu_players_alt.png");
	menu_music_alt=DC_Load("pixmaps/menu_music_alt.png");
	menu_start_alt=DC_Load("pixmaps/menu_start_alt.png");
	menu_exit_alt=DC_Load("pixmaps/menu_exit_alt.png");
	menu_num[0]=DC_Load("pixmaps/menu_0.png");
	menu_num[1]=DC_Load("pixmaps/menu_1.png");
	menu_num[2]=DC_Load("pixmaps/menu_2.png");
	menu_num[3]=DC_Load("pixmaps/menu_3.png");
	menu_num[4]=DC_Load("pixmaps/menu_4.png");
	menu_num[5]=DC_Load("pixmaps/menu_5.png");
	menu_num[6]=DC_Load("pixmaps/menu_6.png");
	menu_num[7]=DC_Load("pixmaps/menu_7.png");
	menu_num[8]=DC_Load("pixmaps/menu_8.png");
	menu_num[9]=DC_Load("pixmaps/menu_9.png");
	menu_off=DC_Load("pixmaps/menu_off.png");
	menu_on=DC_Load("pixmaps/menu_on.png");
	menu_instant=DC_Load("pixmaps/menu_instant.png");
	menu_adventure=DC_Load("pixmaps/menu_adventure.png");
	menu_longest=DC_Load("pixmaps/menu_longest.png");
	menu_head_to_head=DC_Load("pixmaps/menu_head_to_head.png");
	menu_instant_head_to_head=DC_Load("pixmaps/menu_instant_head_to_head.png");
	menu_music_menu=DC_Load("pixmaps/menu_music_menu.png");
	menu_music_grass=DC_Load("pixmaps/menu_music_grass.png");
	menu_music_snow=DC_Load("pixmaps/menu_music_snow.png");
	menu_music_desert=DC_Load("pixmaps/menu_music_desert.png");
	menu_beta=DC_Load("pixmaps/menu_beta.png");
	
	//inizializate keys variable
	keys = SDL_GetKeyState(NULL);
	
	//DC Class Creations
	DC_Snake Cobra[2];
	Map Field_Map(DeadlyCobra.Get_Level());

	//menu display/function
	DC_Draw_Menu(0);
	DC_Menu();

	#ifdef SHOWALL
	SDL_FillRect(screen,0,0);
	Cobra[0].Reset(140,100,RIGHT,1);
	Cobra[1].Reset(140,400,RIGHT,2);
	Cobra[0].DisplayALL(100);
	Cobra[1].DisplayALL(400);
	SDL_UpdateRect(screen,0,0,0,0);
	while ( SDL_PollEvent(&event) >= 0 ) {
		SDL_WaitEvent(&event);
		if(keys[SDLK_ESCAPE] == SDL_PRESSED) { break; }
	}
	#endif
	
	//change from splash screen to map
	if(DeadlyCobra.Get_Music()!=MUSIC_OFF) { 
		Mix_HaltMusic();
		DeadlyCobra.Set_Music(DeadlyCobra.Get_Level());
		Mix_FadeInMusic(music[DeadlyCobra.Get_Level()], -1, 3000);
	}
	Uint32 Ticks_Before, Ticks_After, Ticks_Before_Turn = 0, Ticks_After_Turn = 0, Elapsed_Time = 0;
	SDL_Thread *Control = SDL_CreateThread(DC_Control_Check,NULL);
	SDL_Delay(250);
	Field_Map.SetXOffset(0);
	Field_Map.SetYOffset(0);
	Field_Map.Reset(DeadlyCobra.Get_Level());
	Field_Map.Draw(0,0);
	//Arange Obstacles
	for (i=0;i<DeadlyCobra.Get_Obstacles();i++) {
			Ob[i].Arange(DeadlyCobra.Get_Obstacle_Formation(),i);
	}
	//draw misc
	DC_Draw(lives1,130,546);
	for(i=0;i<DeadlyCobra.Get_Players();i++) { 
		Cobra[i].Set_Score(0); 
		Cobra[i].Set_Lives(3);
		Cobra[i].Set_Alive(ALIVE);
		Cobra[i].Set_Blink(14);
	}
	DC_Score(Cobra[0].Get_Score(),200,230,260,290,546,0);
	if(DeadlyCobra.Get_Players()==2) { 
		DC_Draw(lives2,590,546);
		DC_Score(Cobra[1].Get_Score(),630,660,690,720,546,0);
	}
	if(DeadlyCobra.Get_Mode()==LONGEST) { 
		for(i=0;i<DeadlyCobra.Get_Men();i++) { HottMen[i].Set_Type(SENTRY); } 
		Cobra[0].Set_Lives(1);	
	}
	DC_Draw(num[Cobra[0].Get_Lives()],60,546);
	if(DeadlyCobra.Get_Players()==2) { DC_Draw(num[Cobra[1].Get_Lives()],520,546); }
	SDL_UpdateRect(screen,0,0,0,0);
	Cobra[0].Reset(140,100,RIGHT,1);
	if(DeadlyCobra.Get_Players()==2) { Cobra[1].Reset(140,400,RIGHT,2); }
	DC_Draw_Game(&Cobra[0],&Cobra[1],&Field_Map);
	SDL_UpdateRect(screen,0,0,0,0);
	DC_Level_Reset(&Cobra[0],&Cobra[1]);
	
	//Begin The Game!!
	while (Game == 1) {
		//Get the time of the loop start
		Ticks_Before = SDL_GetTicks();
		//Set the elapsed time for the previous loop
		Elapsed_Time = Ticks_After_Turn - Ticks_Before_Turn;
		//loop until the desired rate is achived
		while(Move_Now == 0) {
			if(Elapsed_Time>=DeadlyCobra.Get_Speed()) { Elapsed_Time = 0; }
			SDL_Delay(10);
			Ticks_After = SDL_GetTicks();
			if(Ticks_After - Ticks_Before >= DeadlyCobra.Get_Speed() - Elapsed_Time) { Move_Now = 1; }
			if(DeadlyCobra.Get_Pause()==1) { Move_Now = 0; }
		}
		for(i=0;i<2;i++) { 
			Cobra[i].Set_Current_Direction(Current_Directions[i]); 
		}
		Move_Now = 0;
		for(i=0;i<2;i++) { if(Cobra[i].Get_Alive()==1) { Control_Input[i]=0; } }
		Ticks_Before_Turn = SDL_GetTicks();

		//Map covering functions
		for(i2=0;i2<DeadlyCobra.Get_Players();i2++) { for(i=0;i<Cobra[i2].Get_Length()+1;i++) { Field_Map.DrawTile(Cobra[i2].Body[i].Get_X(),Cobra[i2].Body[i].Get_Y()); } }
		for(i=0;i<DeadlyCobra.Get_Men();i++){ 
			Field_Map.DrawTile(HottMen[i].Get_X(),HottMen[i].Get_Y()); 
			if(HottMen[i].Get_Ouch()==1) { 
				Field_Map.DrawTile(HottMen[i].Get_OuchX(),HottMen[i].Get_OuchY());
				Field_Map.DrawTile(HottMen[i].Get_OuchX()+20,HottMen[i].Get_OuchY());
				HottMen[i].Set_Ouch(0,0,0);
			}
		}
		
		//Move cobra
		for(i=0;i<DeadlyCobra.Get_Players();i++) { 
			if(Cobra[i].Get_Alive()==ALIVE) { Cobra[i].Move(Cobra[i].Get_Current_Direction()); } 
		}
		//Check cobra's head vs men locations (1)
		for(i2=0;i2<DeadlyCobra.Get_Players();i2++) {
			if(Cobra[i2].Get_Alive()==ALIVE) { 
				for(i=0;i<DeadlyCobra.Get_Men();i++) {
					if(Cobra[i2].Body[HEAD].Get_Y()==HottMen[i].Get_Y() && Cobra[i2].Body[HEAD].Get_X()==HottMen[i].Get_X()) {
						Mix_PlayChannel(-1, sfx[1], 0);
						HottMen[i].Set_X(((rand()%38)+1)*20);
						HottMen[i].Set_Y(((rand()%25)+1)*20);
						if (Cobra[i2].Body[HEAD].Get_X() < 740) {
							DC_Draw(ouch,Cobra[i2].Body[HEAD].Get_X()+20,Cobra[i2].Body[HEAD].Get_Y()-20);
							HottMen[i].Set_Ouch(1,Cobra[i2].Body[HEAD].Get_X()+20,Cobra[i2].Body[HEAD].Get_Y()-20);
						}
						Cobra[i2].Add_Piece(HottMen[i].Get_Type() + DeadlyCobra.Get_Man_Length()+1);
						Cobra[i2].Set_Score(Cobra[i2].Get_Score() + HottMen[i].Get_Type() + 1);
						Cobra[i2].Set_Full(1);
						DeadlyCobra.Set_Level_Points(DeadlyCobra.Get_Level_Points()+HottMen[i].Get_Type()+1);
						HottMen[i].Set_Type(rand()%4);
						if(DeadlyCobra.Get_Mode()==LONGEST) { HottMen[i].Set_Type(SENTRY); }
						if(Cobra[0].Get_Score() >= 1337) {
							Cobra[0].Set_Score(1337);
							DeadlyCobra.Set_Win(1);
						}
					}	
				}
			}
		}
		//Move Men
		if (DeadlyCobra.Get_Active() == 8) { 
			DeadlyCobra.Set_Active(0);
			for(i=0;i<DeadlyCobra.Get_Men();i++) { 
				if(Cobra[0].Get_Alive()==ALIVE) { HottMen[i].Move(Last_Directions[0],DeadlyCobra.Get_Active()); }
				else if(Cobra[0].Get_Alive()==DEAD && Cobra[1].Get_Alive()==ALIVE) { HottMen[i].Move(Last_Directions[1],DeadlyCobra.Get_Active()); }
			}
		}
		DeadlyCobra.Set_Active(DeadlyCobra.Get_Active()+1);

		//Check cobra's head vs men locations (2)
		for(i2=0;i2<DeadlyCobra.Get_Players();i2++) {
			if(Cobra[i2].Get_Alive()==ALIVE) { 
				for(i=0;i<DeadlyCobra.Get_Men();i++) {
					if(Cobra[i2].Body[HEAD].Get_Y()==HottMen[i].Get_Y() && Cobra[i2].Body[HEAD].Get_X()==HottMen[i].Get_X()) {
						Mix_PlayChannel(-1, sfx[1], 0);
						HottMen[i].Set_X(((rand()%38)+1)*20);
						HottMen[i].Set_Y(((rand()%25)+1)*20);
						if (Cobra[i2].Body[HEAD].Get_X() < 740) {
							DC_Draw(ouch,Cobra[i2].Body[HEAD].Get_X()+20,Cobra[i2].Body[HEAD].Get_Y()-20);
							HottMen[i].Set_Ouch(1,Cobra[i2].Body[HEAD].Get_X()+20,Cobra[i2].Body[HEAD].Get_Y()-20);
						}
						Cobra[i2].Add_Piece(HottMen[i].Get_Type() + DeadlyCobra.Get_Man_Length()+1);
						Cobra[i2].Set_Score(Cobra[i2].Get_Score() + HottMen[i].Get_Type() + 1);
						Cobra[i2].Set_Full(1);
						DeadlyCobra.Set_Level_Points(DeadlyCobra.Get_Level_Points()+HottMen[i].Get_Type()+1);
						HottMen[i].Set_Type(rand()%4);
						if(DeadlyCobra.Get_Mode()==LONGEST) { HottMen[i].Set_Type(SENTRY); }
						if(Cobra[0].Get_Score() >= 1337) {
							Cobra[0].Set_Score(1337);
							DeadlyCobra.Set_Win(1);
						}
					}	
				}
			}
		}

		//Check cobra's head vs cobra's body
		for(i2=0;i2<DeadlyCobra.Get_Players();i2++) {
			if(Cobra[i2].Get_Alive()==ALIVE) { 
				for(i=1;i<Cobra[i2].Get_Length();i++) {
					if (Cobra[i2].Body[HEAD].Get_Y()==Cobra[i2].Body[i].Get_Y() && Cobra[i2].Body[HEAD].Get_X()==Cobra[i2].Body[i].Get_X() && Cobra[i2].Get_Blank(i)==0 && Cobra[i2].Get_Blink()==0) { 
						Control_Input[i2]=1;
						Mix_PlayChannel(-1, sfx[0], 0);
						Cobra[i2].Rumble(i2);
						Cobra[i2].Set_Alive(DEAD);									
					}
				}
				//Check Cobra Vs Cobra
				if(DeadlyCobra.Get_Players()==2) {
					if(i2==0) { i3 = 1;	}
					if(i2==1) { i3 = 0; }
					for(i=1;i<Cobra[i3].Get_Length();i++) {
						if (Cobra[i2].Body[HEAD].Get_Y()==Cobra[i3].Body[i].Get_Y() && Cobra[i2].Body[HEAD].Get_X()==Cobra[i3].Body[i].Get_X() && Cobra[i3].Get_Blank(i)==0 && Cobra[i2].Get_Blink()==0) { 
							Control_Input[i2]=1;
							Mix_PlayChannel(-1, sfx[0], 0);
							Cobra[i2].Rumble(i2);
							Cobra[i2].Set_Alive(DEAD); 			
						}
					}
				}
			}
		}

		//Check cobra's head vs obstacles
		for(i2=0;i2<DeadlyCobra.Get_Players();i2++) {
			if(Cobra[i2].Get_Alive()==ALIVE) { 
				for(i=0;i<DeadlyCobra.Get_Obstacles();i++) {
					if(Cobra[i2].Body[HEAD].Get_Y()==Ob[i].Get_Y() && Cobra[i2].Body[HEAD].Get_X()==Ob[i].Get_X() && Cobra[i2].Get_Blink()==0) { 
						Control_Input[i2]=1;
						Mix_PlayChannel(-1, sfx[0], 0);
						Cobra[i2].Rumble(i2);
						Cobra[i2].Set_Alive(DEAD);					
					}
				}
			}
		}

		//Check cobra's head vs screen edges
		for(i=0;i<DeadlyCobra.Get_Players();i++) {
			if(Cobra[i].Get_Alive()==ALIVE) { 
				if(Cobra[i].Body[HEAD].Get_Y() <20 || Cobra[i].Body[HEAD].Get_X()<20 || Cobra[i].Body[HEAD].Get_X()>760 || Cobra[i].Body[HEAD].Get_Y()>500) { 
					Control_Input[i]=1;
					Mix_PlayChannel(-1, sfx[0], 0);
					Cobra[i].Rumble(i);
					Cobra[i].Set_Alive(DEAD);						
				}
			}
		}

		//Point check for level change
		if(DeadlyCobra.Get_Level_Points()>=50 && DeadlyCobra.Get_Win()==0 && DeadlyCobra.Get_Mode()!=LONGEST) {
			DC_Draw_Game(&Cobra[0],&Cobra[1],&Field_Map);
			Mix_FadeOutMusic(1000);
			//Mix_HaltMusic();
			Mix_PlayChannel(-1, sfx[2], 0);
			DC_Draw(defeated,208,150);
			SDL_UpdateRect(screen,0,0,0,0);
			DeadlyCobra.Set_Level_Points(DeadlyCobra.Get_Level_Points()-50);
			DeadlyCobra.Set_Level(DeadlyCobra.Get_Level()+1);
			if (DeadlyCobra.Get_Level() == 4) {
				DeadlyCobra.Set_Level(GRASS);
				if(DeadlyCobra.Get_Players()==1) { if(Cobra[0].Get_Lives()<9) { Cobra[0].Set_Lives(Cobra[0].Get_Lives()+1); } }
				if(DeadlyCobra.Get_Difficulty()<9) { DeadlyCobra.Set_Difficulty(DeadlyCobra.Get_Difficulty()+1); }
			}
			DeadlyCobra.Set_Obstacle_Formation(DeadlyCobra.Get_Obstacle_Formation()+1);
			//max obstacle form (currently using only 0)
			if(DeadlyCobra.Get_Obstacle_Formation() == 1) { 
				DeadlyCobra.Set_Obstacle_Formation(0);
			}
			for (i=0;i<DeadlyCobra.Get_Obstacles();i++) {
				Ob[i].Arange(DeadlyCobra.Get_Obstacle_Formation(),i);
			}
			Field_Map.Reset(DeadlyCobra.Get_Level());
			Field_Map.Draw(0,0);
			DC_Draw(lives1,130,546);
			if(DeadlyCobra.Get_Players()==2) { DC_Draw(lives2,590,546); }
			DC_Score(Cobra[0].Get_Score(),200,230,260,290,546,0);
			if(DeadlyCobra.Get_Players()==2) { 
				DC_Score(Cobra[1].Get_Score(),630,660,690,720,546,0);
			}
			DC_Draw(num[Cobra[0].Get_Lives()],60,546);
			if(DeadlyCobra.Get_Players()==2) { DC_Draw(num[Cobra[1].Get_Lives()],520,546); }
			SDL_Delay(3000);
			if(DeadlyCobra.Get_Music()!=MUSIC_OFF) { 
				DeadlyCobra.Set_Music(DeadlyCobra.Get_Level());
			//	Mix_FadeOutMusic(3000);
				Mix_FadeInMusic(music[DeadlyCobra.Get_Level()], -1, 3000);
			}
			SDL_UpdateRect(screen,0,0,0,0);
			if(Cobra[0].Get_Lives()>0) { 
				Cobra[0].Set_Alive(ALIVE); 
				Cobra[0].Reset(140,100,RIGHT,1);
				Current_Directions[0]=RIGHT;
				Last_Directions[0]=RIGHT;
				Cobra[0].Set_Current_Direction(RIGHT);
				Cobra[0].Set_Blink(14);
			}
			if(DeadlyCobra.Get_Players()==2){ 
				if(Cobra[1].Get_Lives()>0) { 
					Cobra[1].Set_Alive(ALIVE); 
					Cobra[1].Reset(140,400,RIGHT,2); 
					Current_Directions[1]=RIGHT;
					Last_Directions[1]=RIGHT;
					Cobra[1].Set_Current_Direction(RIGHT);
					Cobra[1].Set_Blink(14);
				}
			}
			DC_Draw_Game(&Cobra[0],&Cobra[1],&Field_Map);
			SDL_UpdateRect(screen,0,0,0,0);
			DC_Level_Reset(&Cobra[0],&Cobra[1]);
		}
		//slowly destroy dead cobras
		for(i=0;i<DeadlyCobra.Get_Players();i++) { 
			if(Cobra[i].Get_Alive()==DEAD && Cobra[i].Get_Length()==1) {
				Cobra[i].Rem_Piece(1);
				Current_Directions[i] = 99;
				Cobra[i].Set_Current_Direction(99);
			}
			else if(Cobra[i].Get_Current_Direction()==99) {
				Cobra[i].Set_Current_Direction(98);
				Current_Directions[i]=98;
				DC_Snake_Die(&Cobra[i],&Cobra[0],&Cobra[1],i,&Field_Map);
			}
			if(Cobra[i].Get_Alive()==DEAD && Cobra[i].Get_Length()>1) { 
				if(DeadlyCobra.Get_Active()==2 || DeadlyCobra.Get_Active()==4 || DeadlyCobra.Get_Active()==6 || DeadlyCobra.Get_Active()==8) { Cobra[i].Rem_Piece(1); }
				//if(DeadlyCobra.Get_Mode()==3) { Cobra[i].Rem_Piece(Cobra[i].Get_Length()-1); }
			}			
		}
		//handle blink of new cobra
		for(i=0;i<DeadlyCobra.Get_Players();i++) { 
			if(Cobra[i].Get_Blink()>0) {
				Cobra[i].Set_Blink(Cobra[i].Get_Blink()-1);
				Cobra[i].Switch_Alpha();
			}
		}
		//Draw cobra, obstacles, men, various text and score
		DC_Draw_Game(&Cobra[0],&Cobra[1],&Field_Map);
			
		//CLEANUP!!
		for(i=0;i<DeadlyCobra.Get_Players();i++) { if(Cobra[i].Get_Alive()==ALIVE) { Last_Directions[i] = Cobra[i].Get_Current_Direction(); } }
		//partial updaterect
		for(i2=0;i2<DeadlyCobra.Get_Players();i2++) {
			for(i=0;i<Cobra[i2].Get_Length()+1;i++) { 
				Field_Map.Set_Modified(1,Cobra[i2].Body[i].Get_X()/20,Cobra[i2].Body[i].Get_Y()/20);
			}
		}
		for(i=0;i<DeadlyCobra.Get_Men();i++){
			Field_Map.Set_Modified(1,HottMen[i].Get_X()/20,HottMen[i].Get_Y()/20);
			if(HottMen[i].Get_Ouch()==1) { 
				Field_Map.Set_Modified(1,HottMen[i].Get_OuchX()/20,HottMen[i].Get_OuchY()/20);
				Field_Map.Set_Modified(1,(HottMen[i].Get_OuchX()+20)/20,HottMen[i].Get_OuchY()/20);
			}
		}
		if(DeadlyCobra.Get_Update()==1) {
			SDL_UpdateRect(screen,0,0,0,0);
			DeadlyCobra.Set_Update(0);
		}
		for(x=0;x<Field_Map.GetWidth();x++) {
			for(y=0;y<Field_Map.GetHeight();y++) {
				if(Field_Map.Get_Modified(x,y)==1) {
					Field_Map.Set_Modified(0,x,y);
					SDL_UpdateRect(screen,x*16,y*16,16,16);
				}
			}
		}
		
		//If the Win var was set, end the game.
		if (DeadlyCobra.Get_Win() == 1) {
			win=DC_Load("pixmaps/text_congratulations.png");
			SDL_SetColorKey(win, SDL_SRCCOLORKEY|SDL_RLEACCEL,
				SDL_MapRGB(win->format, 0, 0, 255));
			DC_Draw(win,208,150);
			SDL_UpdateRect(screen,0,0,0,0);
			if(Cobra[0].Get_Score()>f) { DC_High_Score(1,Cobra[0].Get_Score(),DeadlyCobra.Get_Mode()); }
			while ( SDL_PollEvent(&event) >= 0 ) {
				if(keys[SDLK_ESCAPE] == SDL_PRESSED) {
					SDL_KillThread(Control);
					DC_Quit(); 
				}
			}
		}
		//Check number of lives, and if equal to 0, end game
		if(Cobra[0].Get_Lives()==0 && Cobra[1].Get_Lives()==0) {
			//Mix_HaltMusic();
			Mix_FadeOutMusic(1000);
			Mix_PlayChannel(-1, sfx[3], 0);
			Game = 0;
		}
		Ticks_After_Turn = SDL_GetTicks();
		#ifdef DEBUG_MAIN 
		//cout << "elapsed from start:  " << Ticks_After_Turn - Ticks_Before << "\n" << Cobra[0].Get_Length() << "\n";
		if(Ticks_After_Turn - Ticks_Before>DeadlyCobra.Get_Speed()+10) { debug++; }
		frames++;
		#endif

	}
	if(Cobra[0].Get_Score()>f) { DC_High_Score(1,Cobra[0].Get_Score(),DeadlyCobra.Get_Mode());	}
	DC_Draw(go,160,150);
	SDL_UpdateRect(screen,0,0,0,0);
	SDL_KillThread(Control);
}

//Resets level and starts coundown for play
void DC_Level_Reset(DC_Snake *Cobra1, DC_Snake *Cobra2) {
	DeadlyCobra.Set_Update(1);
	if(DeadlyCobra.Get_Level()==1) {
		ready=DC_Load("pixmaps/grass_ready.png");
		largenum[2]=DC_Load("pixmaps/grass_3.png");
		largenum[1]=DC_Load("pixmaps/grass_2.png");
		largenum[0]=DC_Load("pixmaps/grass_1.png");
	}
	if(DeadlyCobra.Get_Level()==2) {
		ready=DC_Load("pixmaps/snow_ready.png");
		largenum[2]=DC_Load("pixmaps/snow_3.png");
		largenum[1]=DC_Load("pixmaps/snow_2.png");
		largenum[0]=DC_Load("pixmaps/snow_1.png");
	}
	if(DeadlyCobra.Get_Level()==3) {
		ready=DC_Load("pixmaps/desert_ready.png");
		largenum[2]=DC_Load("pixmaps/desert_3.png");
		largenum[1]=DC_Load("pixmaps/desert_2.png");
		largenum[0]=DC_Load("pixmaps/desert_1.png");
	}
	DC_Draw(ready,300,200);
	SDL_UpdateRect(screen,240,160,160,80);
	SDL_Delay(1000);
	DC_Draw(largenum[2],300,200);
	SDL_UpdateRect(screen,240,160,160,80);
	SDL_Delay(1000);
	DC_Draw(largenum[1],300,200);
	SDL_UpdateRect(screen,240,160,160,80);
	SDL_Delay(1000);
	DC_Draw(largenum[0],300,200);
	SDL_UpdateRect(screen,240,160,160,80);
	SDL_Delay(1000);
}
//Takes the number passed to it, and separates the 4 digits
void DC_Score(int total, int x1, int x2, int x3, int x4, int y, int menu) {
	int d1, d2, d3, d4;
	d1 = (total / 1000);
	total = total - (d1 * 1000);
	d2 = total / 100;
	total = total - (d2 * 100);
	d3 = total / 10;
	d4 = total - (d3 * 10);
	if(menu==0) { 
		DC_Draw(num[d1],x1,y); 
		DC_Draw(num[d2],x2,y);
		DC_Draw(num[d3],x3,y);
		DC_Draw(num[d4],x4,y);
	}
	else if(menu==1) { 
		DC_Draw(menu_num[d1],x1,y); 
		DC_Draw(menu_num[d2],x2,y);
		DC_Draw(menu_num[d3],x3,y);
		DC_Draw(menu_num[d4],x4,y);
	}
}
//Reads the High Score from the data file.  
//If "doupdate 1" was passed to it, it updates the data file with "Score"
//use 0,0 to retrieve results of the data file
void DC_High_Score(int doupdate, int score, int mode) {
	FILE * pFile;
	if(mode==LONGEST) { pFile = fopen ("data/data2","r+"); }
	else pFile = fopen ("data/data","r+");
	if(doupdate==1) { fprintf (pFile, "%i %s", score, "HighScore"); }
	rewind (pFile);
	fscanf (pFile, "%i", &f);
	fscanf (pFile, "%s", str);
	fclose (pFile);	
}

//Reads the snap count from the data1 file.  
//If "doupdate 1" was passed to it, it updates the data file with "snapcount"
//use 0,0 to retrieve results on the data1 file
void DC_Snap_Count(int doupdate, int snapcount) {
	FILE * pFile;
	pFile = fopen ("data/data1","r+");
	if (doupdate == 1) { fprintf (pFile, "%i %s", snapcount, "Snap"); }
	rewind (pFile);
	fscanf (pFile, "%i", &g);
	fscanf (pFile, "%s", str);
	fclose (pFile);	
}

//Resets all game variables
void DC_Game_Reset() {
	Game = 1;
	DeadlyCobra.Set_Level(1);
	DeadlyCobra.Set_Music(MUSIC_MENU);
	DeadlyCobra.Set_Win(0);
	DeadlyCobra.Set_Active(0);
	DeadlyCobra.Set_Players(1);
	DeadlyCobra.Set_Mode(SINGLE);
	DeadlyCobra.Set_Difficulty(1);
	DeadlyCobra.Set_Respawn(0);
	DeadlyCobra.Set_Obstacle_Formation(0);
	DeadlyCobra.Set_Level_Points(0);
	DeadlyCobra.Set_Menu_Location(MENU_DIFFICULTY);
	Current_Directions[0] = RIGHT;
	Current_Directions[1] = RIGHT;
	Last_Directions[0] = RIGHT;
	Last_Directions[1] = RIGHT;
	Control_Input[0] = 0;
	Control_Input[1] = 0;
	Move_Now = 0;
}

//controls when user hits up, down, left or right or more
int DC_Control_Check(void *junk) {
	
	if(Game==0) { return 1; }
	while(Game==1) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_KEYDOWN:
				handleKey(event.key);
				break;
		case SDL_JOYBUTTONDOWN:
				handlejoybutton(event.jbutton);
				break;
		case SDL_JOYAXISMOTION:
		//Player 1 joystick Controls:
			if ((Control_Input[0]==0) && (event.jaxis.which ==0 )) {
			if(event.jaxis.axis == 1 && (event.jaxis.value < -15000 ) && Current_Directions[0] != DOWN && Current_Directions[0] != UP) {				
				Control_Input[0] = 1;
				Current_Directions[0] = UP;
			}
			else if(event.jaxis.axis == 1 && ( event.jaxis.value > 15000 ) && Current_Directions[0] != UP && Current_Directions[0] != DOWN) {				
				Control_Input[0] = 1;
				Current_Directions[0] = DOWN;
			}       	
			else if(event.jaxis.axis == 0 && ( event.jaxis.value < -15000 ) && Current_Directions[0] != RIGHT && Current_Directions[0] != LEFT) {
				Control_Input[0] = 1;
				Current_Directions[0] = LEFT;
			}
			else if(event.jaxis.axis == 0 && (event.jaxis.value > 15000 ) && Current_Directions[0] != LEFT && Current_Directions[0] != RIGHT) {				
				Control_Input[0] = 1;
				Current_Directions[0] = RIGHT;
			}
			}
			
			//Player 2 joystick Controls :
			if ((Control_Input[1]==0) && (event.jaxis.which == 1 )) {
			if(event.jaxis.axis == 1 && (event.jaxis.value < -15000 ) && Current_Directions[1] != DOWN && Current_Directions[1] != UP) {				
				Control_Input[1] = 1;
				Current_Directions[1] = UP;
			}
			else if(event.jaxis.axis == 1 && ( event.jaxis.value > 15000 ) && Current_Directions[1] != UP && Current_Directions[1] != DOWN) {				
				Control_Input[1] = 1;
				Current_Directions[1] = DOWN;
			}       	
			else if(event.jaxis.axis == 0 && ( event.jaxis.value < -15000 ) && Current_Directions[1] != RIGHT && Current_Directions[1] != LEFT) {
				Control_Input[1] = 1;
				Current_Directions[1] = LEFT;
			}
			else if(event.jaxis.axis == 0 && (event.jaxis.value > 15000 ) && Current_Directions[1] != LEFT && Current_Directions[1] != RIGHT) {				
				Control_Input[1] = 1;
				Current_Directions[1] = RIGHT;
			}
			}
		break;
		case SDL_JOYHATMOTION:
		//Player 1 D-Pad Controls:
			if ((Control_Input[0]==0) && (event.jhat.which ==0 )) {
			if(event.jhat.value == SDL_HAT_UP && Current_Directions[0] != DOWN && Current_Directions[0] != UP) {				
				Control_Input[0] = 1;
				Current_Directions[0] = UP;
			}
			else if(event.jhat.value == SDL_HAT_DOWN && Current_Directions[0] != UP && Current_Directions[0] != DOWN) {				
				Control_Input[0] = 1;
				Current_Directions[0] = DOWN;
			}       	
			else if(event.jhat.value == SDL_HAT_LEFT && Current_Directions[0] != RIGHT && Current_Directions[0] != LEFT) {
				Control_Input[0] = 1;
				Current_Directions[0] = LEFT;
			}
			else if(event.jhat.value == SDL_HAT_RIGHT && Current_Directions[0] != LEFT && Current_Directions[0] != RIGHT) {				
				Control_Input[0] = 1;
				Current_Directions[0] = RIGHT;
			}
			}
			
			//Player 2 D-pad Controls:
			if ((Control_Input[1]==0) && (event.jhat.which == 1 )) {
			if(event.jhat.value == SDL_HAT_UP && Current_Directions[1] != DOWN && Current_Directions[1] != UP) {				
				Control_Input[1] = 1;
				Current_Directions[1] = UP;
			}
			else if(event.jhat.value == SDL_HAT_DOWN && Current_Directions[1] != UP && Current_Directions[1] != DOWN) {				
				Control_Input[1] = 1;
				Current_Directions[1] = DOWN;
			}       	
			else if(event.jhat.value == SDL_HAT_LEFT && Current_Directions[1] != RIGHT && Current_Directions[1] != LEFT) {
				Control_Input[1] = 1;
				Current_Directions[1] = LEFT;
			}
			else if(event.jhat.value == SDL_HAT_RIGHT && Current_Directions[1] != LEFT && Current_Directions[1] != RIGHT) {				
				Control_Input[1] = 1;
				Current_Directions[1] = RIGHT;
			}
			}
		break;
		}
		if(Control_Input[0]==0) {
			//Player 1 Control keys:
			if(keys[SDLK_UP] && Current_Directions[0] != DOWN && Current_Directions[0] != UP) {				
				Control_Input[0] = 1;
				Current_Directions[0] = UP;
			}
			else if(keys[SDLK_DOWN] && Current_Directions[0] != UP && Current_Directions[0] != DOWN) {				
				Control_Input[0] = 1;
				Current_Directions[0] = DOWN;
			}       	
			else if(keys[SDLK_LEFT] && Current_Directions[0] != RIGHT && Current_Directions[0] != LEFT) {
				Control_Input[0] = 1;
				Current_Directions[0] = LEFT;
			}
			else if(keys[SDLK_RIGHT] && Current_Directions[0] != LEFT && Current_Directions[0] != RIGHT) {				
				Control_Input[0] = 1;
				Current_Directions[0] = RIGHT;
			}
		}
		if(Control_Input[1]==0) {
			//Player 2 Control keys:
			if(keys[SDLK_w] && Current_Directions[1] != DOWN && Current_Directions[1] != UP) {				
				Control_Input[1] = 1;
				Current_Directions[1] = UP;
			}
			else if(keys[SDLK_s] && Current_Directions[1] != UP && Current_Directions[1] != DOWN) {				
				Control_Input[1] = 1;
				Current_Directions[1] = DOWN;
			}       	
				else if(keys[SDLK_a] && Current_Directions[1] != RIGHT && Current_Directions[1] != LEFT) {
				Control_Input[1] = 1;
				Current_Directions[1] = LEFT;
			}
			else if(keys[SDLK_d] && Current_Directions[1] != LEFT && Current_Directions[1] != RIGHT) {				
				Control_Input[1] = 1;
				Current_Directions[1] = RIGHT;
			}
		}
	}
	return 0;
}
//handles killing the snake
void DC_Snake_Die(DC_Snake *Cobrai, DC_Snake *Cobra1, DC_Snake *Cobra2, int player, Map *FieldMap) {
	Cobrai->Set_Lives(Cobrai->Get_Lives()-1);
	DC_Draw(num[Cobra1->Get_Lives()],60,546);
	if(DeadlyCobra.Get_Players()==2) { DC_Draw(num[Cobra2->Get_Lives()],520,546); }
	SDL_UpdateRect(screen,16,437,592,32);
	
	if(Cobra1->Get_Lives()!=0 || Cobra2->Get_Lives()!=0) {
		//immeditate respawn
		if(DeadlyCobra.Get_Respawn()==1) {
			if(player==0 && Cobra1->Get_Lives()>0) {
				Cobra1->Set_Alive(1);
				Cobra1->Set_Blink(14);				
				Cobra1->Reset(140,100,RIGHT,1); 
				Cobra1->Set_Current_Direction(RIGHT);
				Current_Directions[0]=RIGHT;
				Last_Directions[0] = RIGHT;
			}
			if(player==1 && Cobra2->Get_Lives()>0) { 
				Cobra2->Set_Alive(1);
				Cobra2->Set_Blink(14);
				Cobra2->Reset(140,400,RIGHT,2); 
				Cobra2->Set_Current_Direction(RIGHT);
				Current_Directions[1]=RIGHT;
				Last_Directions[1] = RIGHT;
			}
		}	
		
		//delayed respawn
		if(DeadlyCobra.Get_Respawn()==0) {
			Cobrai->Set_Alive(0);
			if(Cobra1->Get_Alive()==0 && Cobra2->Get_Alive()==0) {
				if((DeadlyCobra.Get_Players()==2 && Cobra1->Get_Current_Direction()==98 && Cobra2->Get_Current_Direction()==98) || DeadlyCobra.Get_Players()==1) { 
					if(Cobra1->Get_Lives()>0) { 
						Cobra1->Set_Alive(1);
						Cobra1->Set_Blink(14);
						Cobra1->Reset(140,100,RIGHT,1);
						Cobra1->Set_Current_Direction(RIGHT);
						Current_Directions[0]=RIGHT;
						Last_Directions[0] = RIGHT;
					}
					if(DeadlyCobra.Get_Players()==2) {
						if(Cobra2->Get_Lives()>0) { 
							Cobra2->Set_Alive(1); 
							Cobra2->Set_Blink(14);
							Cobra2->Reset(140,400,RIGHT,2);
							Cobra2->Set_Current_Direction(RIGHT);
							Current_Directions[1]=RIGHT;
							Last_Directions[1] = RIGHT;
						}										
					}
					SDL_UpdateRect(screen,32,80,96,16);
					SDL_UpdateRect(screen,32,80,96,16);
					DC_Level_Reset(Cobra1,Cobra2); 
				}
			}
		}
	}
}
//handles changing the tunes
void DC_Music_Up(void) { 
	if(DeadlyCobra.Get_Music() < 3) { 
		Mix_HaltMusic();
		Mix_PlayMusic(music[DeadlyCobra.Get_Music()+1],-1);
		DeadlyCobra.Set_Music(DeadlyCobra.Get_Music()+1);
	}
	else if(DeadlyCobra.Get_Music()==MUSIC_LVL3) {
		Mix_HaltMusic();
		DeadlyCobra.Set_Music(MUSIC_OFF);
	}
	else if(DeadlyCobra.Get_Music()==MUSIC_OFF) {
		Mix_HaltMusic();
		Mix_PlayMusic(music[MUSIC_MENU],-1);
		DeadlyCobra.Set_Music(MUSIC_MENU);
	}
}
void DC_Music_Down(void) {
	if(DeadlyCobra.Get_Music() > 0) { 
		Mix_HaltMusic();
		Mix_PlayMusic(music[DeadlyCobra.Get_Music()-1],-1);
		DeadlyCobra.Set_Music(DeadlyCobra.Get_Music()-1);
	}
	else if(DeadlyCobra.Get_Music()==MUSIC_MENU) {
		Mix_HaltMusic();
		DeadlyCobra.Set_Music(MUSIC_OFF);
	}	
}
//handles drawing the game each movement
void DC_Draw_Game(DC_Snake *Cobra1, DC_Snake *Cobra2, Map *FieldMap) {
	//draw the whole map
	if(DeadlyCobra.Get_Update() == 1) {
		FieldMap->Draw(0,0);
	}
	//draw status bar
	for(i=1;i<40;i++) {
		i2=(i * 20);
		FieldMap->DrawTile(i2,540);
		FieldMap->DrawTile(i2,560);
	}
	//draw snake's score
	DC_Score(Cobra1->Get_Score(),200,230,260,290,546,0);
	if(DeadlyCobra.Get_Players()==2) { 
		DC_Score(Cobra2->Get_Score(),630,660,690,720,546,0);
	}
	//draw obstacles
	for(i=0;i<DeadlyCobra.Get_Obstacles();i++) { Ob[i].Draw(DeadlyCobra.Get_Level()); }
	//draw snakes
	for(i=0;i<DeadlyCobra.Get_Players();i++) { 
		if(i==0) { Cobra1->Draw(Cobra1->Get_Current_Direction(),Last_Directions[i]); }
		if(i==1) { Cobra2->Draw(Cobra2->Get_Current_Direction(),Last_Directions[i]); }		
	}  
	//draw men
	for(i=0;i<DeadlyCobra.Get_Men();i++) { HottMen[i].Draw(); }
	//draw lives
	DC_Draw(lives1,130,546);
	if(DeadlyCobra.Get_Players()==2) { DC_Draw(lives2,590,546); }
	DC_Draw(num[Cobra1->Get_Lives()],60,546);
	if(DeadlyCobra.Get_Players()==2) { DC_Draw(num[Cobra2->Get_Lives()],520,546); }
}
void DC_Draw_Menu(int location) {
	DC_Draw(menu,0,0);
	if(location==MENU_DIFFICULTY) { DC_Draw(menu_difficulty_alt,140,255); }
	else DC_Draw(menu_difficulty,140,255);
	DC_Draw(menu_num[DeadlyCobra.Get_Difficulty()],400,255);
	if(location==MENU_MODE) { DC_Draw(menu_players_alt,140,315); }
	else DC_Draw(menu_players,140,315);
	if(DeadlyCobra.Get_Mode()==SINGLE) { DC_Draw(menu_adventure,400,315); }
	if(DeadlyCobra.Get_Mode()==TWOPLAYER) { DC_Draw(menu_head_to_head,400,315); }
	if(DeadlyCobra.Get_Mode()==INSTANT) { DC_Draw(menu_instant_head_to_head,400,315); }
	if(DeadlyCobra.Get_Mode()==LONGEST) { DC_Draw(menu_longest,400,315); }
	if(location==MENU_MUSIC) { DC_Draw(menu_music_alt,140,370); }
	else DC_Draw(menu_music,140,370);
	if(DeadlyCobra.Get_Music()==MUSIC_OFF) { DC_Draw(menu_off,400,375); }
	if(DeadlyCobra.Get_Music()==MUSIC_MENU) { DC_Draw(menu_music_menu,400,375); }
	if(DeadlyCobra.Get_Music()==MUSIC_LVL1) { DC_Draw(menu_music_grass,400,375); }
	if(DeadlyCobra.Get_Music()==MUSIC_LVL2) { DC_Draw(menu_music_snow,400,375); }
	if(DeadlyCobra.Get_Music()==MUSIC_LVL3) { DC_Draw(menu_music_desert,400,375); }
	if(location==MENU_START) { DC_Draw(menu_start_alt,200,430); }
	else DC_Draw(menu_start,200,430);
	if(location==MENU_EXIT) { DC_Draw(menu_exit_alt,335,490); }
	else DC_Draw(menu_exit,335,490);
	DC_Draw(menu_high,200,550);
	DC_High_Score(0,0,DeadlyCobra.Get_Mode());
	DC_Score(f,470,500,530,560,550,1);
	SDL_UpdateRect(screen,0,0,0,0);
}
void DC_Menu(void) {
	//if( SDL_PollEvent(NULL) ) { keys = SDL_GetKeyState(NULL); }
	while(true) {
		SDL_WaitEvent(&event);
		switch(event.type){
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYHATMOTION:
		case SDL_KEYDOWN:
		if(keys[SDLK_F12]) { 
			char snap_file[20];
			DeadlyCobra.Set_Snap(DeadlyCobra.Get_Snap() + 1);
			if(DeadlyCobra.Get_Snap()>=999) { DeadlyCobra.Set_Snap(0); }
			sprintf(snap_file, "snaps/snap%d.bmp", DeadlyCobra.Get_Snap());
			SDL_SaveBMP(screen, snap_file);
			DC_Snap_Count(1,DeadlyCobra.Get_Snap());
		}
		#ifdef DEBUG_MAIN 
		if(keys[SDLK_F11]) { SDL_WM_ToggleFullScreen(screen); }
		#endif
		if(keys[SDLK_1]) { DeadlyCobra.Set_Difficulty(1); }
		if(keys[SDLK_2]) { DeadlyCobra.Set_Difficulty(2); }
		if(keys[SDLK_3]) { DeadlyCobra.Set_Difficulty(3); }
		if(keys[SDLK_4]) { DeadlyCobra.Set_Difficulty(4); }
		if(keys[SDLK_5]) { DeadlyCobra.Set_Difficulty(5); }
		if(keys[SDLK_6]) { DeadlyCobra.Set_Difficulty(6); }
		if(keys[SDLK_7]) { DeadlyCobra.Set_Difficulty(7); }
		if(keys[SDLK_8]) { DeadlyCobra.Set_Difficulty(8); }
		if(keys[SDLK_9]) { DeadlyCobra.Set_Difficulty(9); }		
		if((keys[SDLK_RETURN] || ((event.type == SDL_JOYBUTTONDOWN) && ((event.jbutton.button == 0)||(event.jbutton.button == 9)))) && DeadlyCobra.Get_Menu_Location()==MENU_DIFFICULTY) { 
			if(DeadlyCobra.Get_Difficulty()==9) { DeadlyCobra.Set_Difficulty(1); }
			else DeadlyCobra.Set_Difficulty(DeadlyCobra.Get_Difficulty()+1);
		}
		else if((keys[SDLK_RETURN] || ((event.type == SDL_JOYBUTTONDOWN) && ((event.jbutton.button == 0)||(event.jbutton.button == 9)))) && DeadlyCobra.Get_Menu_Location()==MENU_MODE) { 
			if(DeadlyCobra.Get_Mode()<3) { DeadlyCobra.Set_Mode(DeadlyCobra.Get_Mode()+1); }
			else DeadlyCobra.Set_Mode(SINGLE);
			DeadlyCobra.Set_Difficulty(DeadlyCobra.Get_Difficulty());
		}
		else if((keys[SDLK_RETURN] || ((event.type == SDL_JOYBUTTONDOWN) && ((event.jbutton.button == 0)||(event.jbutton.button == 9)))) && DeadlyCobra.Get_Menu_Location()==MENU_MUSIC) { 
			DC_Music_Up();
		}
		else if((keys[SDLK_RETURN] || ((event.type == SDL_JOYBUTTONDOWN) && ((event.jbutton.button == 0)||(event.jbutton.button == 9)))) && DeadlyCobra.Get_Menu_Location()==MENU_START) { return; }
		else if((keys[SDLK_RETURN] || ((event.type == SDL_JOYBUTTONDOWN) && ((event.jbutton.button == 0)||(event.jbutton.button == 9)))) && DeadlyCobra.Get_Menu_Location()==MENU_EXIT) { DC_Quit(); }
		
		if(keys[SDLK_ESCAPE]|| ((event.type == SDL_JOYBUTTONDOWN) && ((event.jbutton.button == 6)||(event.jbutton.button == 19)))) { DC_Quit(); }
		
		if((keys[SDLK_RIGHT] || ((event.type == SDL_JOYHATMOTION) && (event.jhat.value == SDL_HAT_RIGHT))) && DeadlyCobra.Get_Menu_Location()==MENU_DIFFICULTY) {
			if(DeadlyCobra.Get_Difficulty()==9) { DeadlyCobra.Set_Difficulty(1); }
			else DeadlyCobra.Set_Difficulty(DeadlyCobra.Get_Difficulty()+1);
		}
		else if((keys[SDLK_RIGHT] || ((event.type == SDL_JOYHATMOTION) && (event.jhat.value == SDL_HAT_RIGHT))) && DeadlyCobra.Get_Menu_Location()==MENU_MODE) { 
			if(DeadlyCobra.Get_Mode()<3) { DeadlyCobra.Set_Mode(DeadlyCobra.Get_Mode()+1); }
			else DeadlyCobra.Set_Mode(SINGLE);
			DeadlyCobra.Set_Difficulty(DeadlyCobra.Get_Difficulty());
		}
		else if((keys[SDLK_RIGHT] || ((event.type == SDL_JOYHATMOTION) && (event.jhat.value == SDL_HAT_RIGHT))) && DeadlyCobra.Get_Menu_Location()==MENU_MUSIC) { 
			DC_Music_Up();
		}
		if((keys[SDLK_LEFT] || ((event.type == SDL_JOYHATMOTION) && (event.jhat.value == SDL_HAT_LEFT))) && DeadlyCobra.Get_Menu_Location()==MENU_DIFFICULTY) {
			if(DeadlyCobra.Get_Difficulty()==1) { DeadlyCobra.Set_Difficulty(9); }
			else DeadlyCobra.Set_Difficulty(DeadlyCobra.Get_Difficulty()-1);
		}
		else if((keys[SDLK_LEFT] || ((event.type == SDL_JOYHATMOTION) && (event.jhat.value == SDL_HAT_LEFT))) && DeadlyCobra.Get_Menu_Location()==MENU_MODE) { 
			if(DeadlyCobra.Get_Mode()>0) { DeadlyCobra.Set_Mode(DeadlyCobra.Get_Mode()-1); }
			else DeadlyCobra.Set_Mode(INSTANT);
			DeadlyCobra.Set_Difficulty(DeadlyCobra.Get_Difficulty());
		}
		else if((keys[SDLK_LEFT] || ((event.type == SDL_JOYHATMOTION) && (event.jhat.value == SDL_HAT_LEFT))) && DeadlyCobra.Get_Menu_Location()==MENU_MUSIC) { 
			DC_Music_Down();
		}
		if((keys[SDLK_DOWN]) || ((event.type == SDL_JOYHATMOTION) && (event.jhat.value == SDL_HAT_DOWN))){ 
			if(DeadlyCobra.Get_Menu_Location()==MENU_EXIT) { DeadlyCobra.Set_Menu_Location(MENU_DIFFICULTY); }
			else DeadlyCobra.Set_Menu_Location(DeadlyCobra.Get_Menu_Location()+1);
		}
		if((keys[SDLK_UP]) || ((event.type == SDL_JOYHATMOTION) && (event.jhat.value == SDL_HAT_UP))){ 
			if(DeadlyCobra.Get_Menu_Location()==MENU_DIFFICULTY) { DeadlyCobra.Set_Menu_Location(MENU_EXIT); }
			else DeadlyCobra.Set_Menu_Location(DeadlyCobra.Get_Menu_Location()-1);
		}
		DC_Draw_Menu(DeadlyCobra.Get_Menu_Location());
		break;
		default:
		break;
		}	
	}
}
void DC_Modes(void) {
	//from SDL_ListModes manpage example
	SDL_Rect **modes;
	/* Get available fullscreen/hardware modes */
	modes=SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);
	/* Check is there are any modes available */
	if(modes == (SDL_Rect **)0){
		printf("No modes available!");
  		exit(-1);
	}
	/* Check if or resolution is restricted */
	if(modes == (SDL_Rect **)-1){
 		printf("All resolutions available");
	}
	else{
		/* Print valid modes */
		printf("Available Modes \n");
		for(i=0;modes[i];++i)
		printf("%d x %d \n", modes[i]->w, modes[i]->h);
	}
}
void handleKey(SDL_KeyboardEvent key) {
	char snap_file[20];
	switch(key.keysym.sym) {
		case SDLK_ESCAPE:
			DC_Draw(quit,180,150);
			SDL_UpdateRect(screen,0,0,0,0);
			DeadlyCobra.Set_Pause(1);
			while(DeadlyCobra.Get_Pause()==1){
				SDL_WaitEvent(&event);
				if(keys[SDLK_y]) { 
					Game=0;
					DeadlyCobra.Set_Pause(0);
					DeadlyCobra.Set_Update(1);
				}
				else if(keys[SDLK_n]) { 
					DeadlyCobra.Set_Update(1);
					DeadlyCobra.Set_Pause(0);
				}
			}
			break;
		case SDLK_p:
			DC_Draw(paused,208,150);
			SDL_UpdateRect(screen,0,0,0,0);
			DeadlyCobra.Set_Pause(1);
			while(DeadlyCobra.Get_Pause()==1){
				SDL_WaitEvent(&event);
				if(keys[SDLK_r]) { 
					DeadlyCobra.Set_Pause(0); 
					DeadlyCobra.Set_Update(1);
				}
			}
			break;
		case SDLK_m:
			if(DeadlyCobra.Get_Music() < 4) {
				Mix_HaltMusic();
				DeadlyCobra.Set_Music(MUSIC_OFF);
			}
			else if(DeadlyCobra.Get_Music()==MUSIC_OFF) {
				DeadlyCobra.Set_Music(DeadlyCobra.Get_Level());
				Mix_FadeInMusic(music[DeadlyCobra.Get_Level()], -1, 3000);
			}
			break;
		case SDLK_F12:
			DeadlyCobra.Set_Snap(DeadlyCobra.Get_Snap() + 1);
			if(DeadlyCobra.Get_Snap()>=999) { DeadlyCobra.Set_Snap(0); }
			sprintf(snap_file, "snaps/snap%d.bmp", DeadlyCobra.Get_Snap());
			SDL_SaveBMP(screen, snap_file);
			DC_Snap_Count(1,DeadlyCobra.Get_Snap());
			break;
		default:
		break;
	}
}
void handlejoybutton(SDL_JoyButtonEvent joybutton) {
	//char snap_file[20];
	switch(joybutton.button) {
		//ESCAPE - Button HOME on Wiimote and Classic Controller
		case 6:
		case 19:
			DC_Draw(quit,180,150);
			SDL_UpdateRect(screen,0,0,0,0);
			DeadlyCobra.Set_Pause(1);
			while(DeadlyCobra.Get_Pause()==1){
				SDL_WaitEvent(&event);
				//YES - Button 1 on wiimote, y on classic controller
				if(((event.type == SDL_JOYBUTTONDOWN) && ((event.jbutton.button == 2)||(event.jbutton.button == 12)))) { 
					Game=0;
					DeadlyCobra.Set_Pause(0);
					DeadlyCobra.Set_Update(1);
				}
				//NO- Button 2 on wiimote, x on classic controller
				else if(((event.type == SDL_JOYBUTTONDOWN) && ((event.jbutton.button == 3)||(event.jbutton.button == 11)))) { 
					DeadlyCobra.Set_Update(1);
					DeadlyCobra.Set_Pause(0);
				}
			}
			break;
		//PAUSE - Button PLUS on Wiimote and Classic Controller
		case 5:
		case 18:
			DC_Draw(paused,208,150);
			SDL_UpdateRect(screen,0,0,0,0);
			DeadlyCobra.Set_Pause(1);
			while(DeadlyCobra.Get_Pause()==1){
				SDL_WaitEvent(&event);
				if(((event.type == SDL_JOYBUTTONDOWN) && ((event.jbutton.button == 5)||(event.jbutton.button == 18)))) { 
					DeadlyCobra.Set_Pause(0); 
					DeadlyCobra.Set_Update(1);
				}
			}
			break;
		//Mute - Button MINUS on Wiimote and Classic Controller
		case 4:
		case 17:
			if(DeadlyCobra.Get_Music() < 4) {
				Mix_HaltMusic();
				DeadlyCobra.Set_Music(MUSIC_OFF);
			}
			else if(DeadlyCobra.Get_Music()==MUSIC_OFF) {
				DeadlyCobra.Set_Music(DeadlyCobra.Get_Level());
				Mix_FadeInMusic(music[DeadlyCobra.Get_Level()], -1, 3000);
			}
			break;
		
		//Snapshot - Button B on Wiimote and Classic Controller
		/*
		case 1:
		case 10:
			DeadlyCobra.Set_Snap(DeadlyCobra.Get_Snap() + 1);
			if(DeadlyCobra.Get_Snap()>=999) { DeadlyCobra.Set_Snap(0); }
			sprintf(snap_file, "snaps/snap%d.bmp", DeadlyCobra.Get_Snap());
			SDL_SaveBMP(screen, snap_file);
			DC_Snap_Count(1,DeadlyCobra.Get_Snap());
			break;
		*/
		default:
		break;
	}
}
//Safely exits Deadly Cobra
void DC_Quit(void) { 
	Mix_FreeChunk(sfx[0]);
	Mix_FreeChunk(sfx[1]);
	Mix_FreeChunk(sfx[2]);
	Mix_FreeChunk(sfx[3]);
	Mix_FreeMusic(music[0]);
	Mix_FreeMusic(music[1]);
	Mix_FreeMusic(music[2]);
	Mix_FreeMusic(music[3]);
	Mix_CloseAudio();
	SDL_Quit();
	#ifdef DEBUG_MAIN
	answer = debug / frames;
	answer = answer * 100;
	cout << answer << "% missed timings by 10+ ms. missed " << debug << " timings out of " << frames << " total. \n";
	#endif
	cout << "DC safely exited\n";
	exit(1);
}
