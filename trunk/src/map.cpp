//Map Module

#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<SDL/SDL.h>
//#include<SDL/SDL_image.h>
#include"bitmap.h"
#include"map.h"

using namespace std;

Tile::Tile() {

	TileSize = 20;
	Modified = 0;
		
}
void Tile::Set_Modified(int modified) {
	Modified = modified;
}

Map::Map(int levelnum) {
	//TileLength = 8;
	//TileWidth = 12;
	//int x=0, y=0;
	SetWidth(40);
	SetHeight(30);
	
}

void Map::Reset(int levelnum) {
	
		char MapLayout[40][30] = {  
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,1,2,2,1},
		{1,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,4,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,1,2,2,1},
		{1,0,0,0,4,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
	
	int x,y;
   for(x=0;x<GetWidth();x++) {
    for(y=0;y<GetHeight();y++) {
      switch(MapLayout[x][y]) {
		 case 0:
			if(levelnum==1)
				MapGrid[x][y].TileSurface=DC_Load("pixmaps/grass_bg.png");
			else if(levelnum==2)
				MapGrid[x][y].TileSurface=DC_Load("pixmaps/snow_bg.png");
			else if(levelnum==3)
				MapGrid[x][y].TileSurface=DC_Load("pixmaps/desert_bg.png");
			break;
		 case 1:
			if(levelnum==1)
				MapGrid[x][y].TileSurface=DC_Load("pixmaps/grass_border1.png");
			else if(levelnum==2)
				MapGrid[x][y].TileSurface=DC_Load("pixmaps/snow_border1.png");
			else if(levelnum==3)
				MapGrid[x][y].TileSurface=DC_Load("pixmaps/desert_border1.png");
			break;
		 case 2:
			if(levelnum==1)
				MapGrid[x][y].TileSurface=DC_Load("pixmaps/grass_border2.png");
			else if(levelnum==2)
				MapGrid[x][y].TileSurface=DC_Load("pixmaps/snow_border2.png");
			else if(levelnum==3)
				MapGrid[x][y].TileSurface=DC_Load("pixmaps/desert_border2.png");
			break;
		 case 3:
			if(levelnum==1)
				MapGrid[x][y].TileSurface=DC_Load("pixmaps/grass_fg2.png");
			else if(levelnum==2)
				MapGrid[x][y].TileSurface=DC_Load("pixmaps/snow_fg2.png");
			else if(levelnum==3)
				MapGrid[x][y].TileSurface=DC_Load("pixmaps/desert_fg2.png");
			break;
		 case 4:
			if(levelnum==1)
				MapGrid[x][y].TileSurface=DC_Load("pixmaps/grass_fg1.png");
		 	else if(levelnum==2)
				MapGrid[x][y].TileSurface=DC_Load("pixmaps/snow_fg1.png");
			else if(levelnum==3)
				MapGrid[x][y].TileSurface=DC_Load("pixmaps/desert_fg1.png");
			break;
		default:
			MapGrid[x][y].TileSurface=DC_Load("pixmaps/grass_fg1.png");
			
		}
	}
   }
}

//Set TileWidth of a map to a given value
void Map::SetWidth(Uint8 Width) { TilesWide = Width; }

//Set TileLength of a map to a given value 
void Map::SetHeight(Uint8 Height) { TilesHigh = Height; }

//Sets XOffset of a map to given value
void Map::SetXOffset(int NewXOffset) { XOffset = NewXOffset; }

//Sets YOffset of a map to given value
void Map::SetYOffset(int NewYOffset) {	YOffset = NewYOffset; }

//Scrolls Map in Direction(UP,DOWN,LEFT,RIGHT) by Amount(pixels)
void Map::Scroll(Uint8 Direction,signed int Amount) {
	
	switch(Direction) {
		case UP:
			SetYOffset(GetYOffset()+Amount);
			break;
		case DOWN:
			SetYOffset(GetYOffset()-Amount);
			break;
		case LEFT:
			SetXOffset(GetXOffset()+Amount);
			break;
		case RIGHT:
			SetXOffset(GetXOffset()-Amount);
			break;
		default:
			cout << "\nERROR: Cannot Scroll!\n";

	}
	Draw(GetXOffset(),GetYOffset());
}
	

void Map::Draw(int x,int y) {
	
	//counters for tile numbers
	int i,j=0;

	//x-y coordinate vars
	int X = x;
	int Y = y;
	
	//draw tiles to screen from left-to-right,up-to-down
	for(i=0;i<=TilesWide;i++) {
		if(i == TilesWide) {
			i = 0;
			X = x;
			j++;
			Y+=MapGrid[i][j].GetTileSize();
		} 
		if(j == TilesHigh)
				break;

		DC_Draw(MapGrid[i][j].TileSurface,X+XOffset,Y+YOffset);
		X+=MapGrid[i][j].GetTileSize();
	}
	
}
void Map::DrawTile(int x, int y) {
	int X = x;
	int Y = y;
	int XTile = (X / 20);
	int YTile = (Y / 20);
	DC_Draw(MapGrid[XTile][YTile].TileSurface,X+XOffset,Y+YOffset);
	Set_Modified(1,XTile,YTile);
}
void Map::Set_Modified(int modified, int x, int y) {
	MapGrid[x][y].Set_Modified(modified);
}
