
#ifndef DRAW_H
#define DRAW_H

// Set_Pixel:  Set a given pixel on a given surface to a given color.
int Set_Pixel(SDL_Surface *Surface, Sint32 x, Sint32 y, Uint32 color);

// Draw_Line:  Draws a line to a surface.
int Draw_Line(SDL_Surface *Surface, Sint32 _x1, Sint32 _y1, Sint32 _x2, Sint32 _y2, Uint32 color);

// Draw_Rect:	Draws a Rectangle to a surface.
int Draw_Rect(SDL_Surface *Surface, SDL_Rect *Rect, Uint32 color);

#endif
