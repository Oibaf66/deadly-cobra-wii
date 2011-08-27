#ifndef BITMAP_H
#define BITMAP_H


//makes screen usable through all project files
extern SDL_Surface *screen;

//basic load/display bmp functions
void DC_Draw(SDL_Surface *bitmap, Sint16 x, Sint16 y);
SDL_Surface *DC_Load(char const *file);

#endif
