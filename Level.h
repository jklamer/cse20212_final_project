#ifndef LEVEL_H
#define LEVEL_H

/*
class definition for level class of each level
*/
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include "Player.h"

using namespace std;


class Level
{
	public:
		Level(int, int, int, string);
		~Level();
		void print();
		void update(double=0,double=0);
		void loadLevel(string);
		void loadImages();
		int playLevel(string);
		int menu();
		int charSelectScreen();
		int tutorial();
		void resetCarbLevels();
		//int endScreen();
		
		
		
		
	private:
		//helpers
		bool move(int);
		void moveLibs();
		void changeChar(int);
		int distance(Player, Person);
		bool checkLibrarian(Player, vector<Person>);
		void renderBar(int, int,double, SDL_Texture *);
			
		//declare variables
		int levelHeight;
		int levelWidth;
		int charSelect;
		int carbLevel;
		int levelNum;
		int floorArray[20][20];
		int xorigen;
		int yorigen;
		int endX, endY;
		SDL_Rect squareSpecs;
		string levelFile;
		
		
		//containers
		vector<SDL_Surface * > images;
		vector<SDL_Texture *> textures;
		vector<Player> players;
		vector<Person> librarians;
		map<int,int> objectsUnderPeople;
		vector<SDL_Texture *> faces;
		vector<SDL_Texture *> drinkingFaces;
		
		//SDL stuff,Surfaces, and Textures to be used
		SDL_Window * gameWindow=NULL;
		SDL_Surface * screen=NULL;
		SDL_Renderer * renderer1=NULL;
		SDL_Surface * bookshelf=NULL;
		SDL_Surface * floor=NULL;
		SDL_Surface * wall=NULL;
		SDL_Texture * Biz=NULL;
		SDL_Surface * bizRaw=NULL;
		SDL_Texture * consum=NULL;
		SDL_Surface * consumRaw=NULL;
		SDL_Texture * recycle=NULL;
		SDL_Surface * recycleRaw=NULL;	
		SDL_Texture * librarian=NULL;
		SDL_Surface * librarianRaw=NULL;
		SDL_Texture * biz_drinking=NULL;
		SDL_Surface * biz_drinkingRaw=NULL;
		SDL_Texture * bar=NULL;
		SDL_Surface * barRaw=NULL;
		TTF_Font * titleFont = NULL;
		SDL_Surface * Title=NULL;
		TTF_Font * captionFont = NULL;
		SDL_Surface * Carbonation=NULL;
		SDL_Surface * RootBeerAmount=NULL;
		SDL_Surface * GameOver=NULL;
		
		
		SDL_Texture * Sledge=NULL;
		SDL_Surface * sledgeRaw=NULL;
		SDL_Texture * sledge_drinking=NULL;
		SDL_Surface * sledge_drinkingRaw=NULL;
		
		
		SDL_Texture * Doz=NULL;
		SDL_Surface * dozRaw=NULL;
		SDL_Texture * doz_drinking=NULL;
		SDL_Surface * doz_drinkingRaw=NULL;
		
		SDL_Texture * Ralph=NULL;
		SDL_Surface * ralphRaw=NULL;
		SDL_Texture * ralph_drinking=NULL;
		SDL_Surface * ralph_drinkingRaw=NULL;
		
		
		//control checks
		bool drinking;
		bool firstUpload;
		bool rendererCheck;
};
			
#endif
