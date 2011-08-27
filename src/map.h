#ifndef MAP_H
#define MAP_H


#include "define.h"

class Tile{
   public:
	//default constructor
	Tile(void);
	
	//the image surface of the Tile
	SDL_Surface *TileSurface;
	
    //accessors
	Uint8	 GetTileSize(void)	{ return TileSize; };
	
	//set modified
	void Set_Modified(int modified);
	
	//get modified
	Uint8 Get_Modified(void) { return Modified; };
	
   private:
	//size of square tile (in pixels)
	Uint8 TileSize;
	Uint8 Modified;
};

//Map class that inherits from Tile
class Map{
   public:
	
	//sets if tile has been modified
	void Set_Modified(int modified, int x, int y);
  
	//sets if tile has been modified
	int Get_Modified(int x, int y) { return MapGrid[x][y].Get_Modified(); };
   
	//returns width of map in terms of Tiles
	Uint8 GetWidth(void)	{ return TilesWide; };

	//returns length of map in terms of Tiles
	Uint8 GetHeight(void)	{ return TilesHigh; };

	//returns X/YOffsets
	int GetXOffset(void)	{ return XOffset; };
	int GetYOffset(void)	{ return YOffset; };
	
	//default constructor
	Map(int levelnum);
	
	//loads mapfile
	Map(char *mapfile);
	
	//draw 1 tile from map onto screen
	void DrawTile(int x, int y);
	
	//draws map onto screen
	void Draw(int x,int y);
	
	//scrolls map in given amount and direction
	void Scroll(Uint8 Direction,int Amount);
	
	//sets X/YOffsets
	void SetXOffset(int NewXOffset);
	void SetYOffset(int NewYOffset);
	
	void Reset(int levelnum);
	
	Tile MapGrid[XMAX][YMAX];

   private:
	//num of tiles width/length-wise
	Uint8 TilesWide;
	Uint8 TilesHigh;
	//int X,Y;
	int XOffset;
	int YOffset;
	
	//sets tile sizes width/length-wise
	void SetWidth(Uint8 TileWidth);
	void SetHeight(Uint8 TileHigh);

};

#endif
