//Basic BMP Load/Display Module

#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include "snake.h"
#include "man.h"

using namespace std;

extern SDL_Surface *screen;

SDL_Surface *DC_Load(char const *file) {

	SDL_Surface *image;
	image=IMG_Load(file);
	
	if ( image == NULL ) {
		fprintf(stderr, "Error: Couldn't load %s %s\n ", file, SDL_GetError());
		return(NULL);
	}
	return(image);
}

void DC_Draw(SDL_Surface *bitmap, Sint16 x, Sint16 y) { 

	SDL_Rect dest; 
 
	dest.x = x*0.8; 
	dest.y = y*0.8; 
	dest.w = bitmap->w; 
	dest.h = bitmap->h;

	// Draw "bitmap" onto "screen" according to "dest" 
	SDL_BlitSurface(bitmap, NULL, screen, &dest); 
}
