/*
Library Crawl Game interface

Jack Klamer

4/7/2015
*/


#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include<iostream>
#include<string>
#include<stdlib.h>
#include<fstream>
#include<stdio.h>
#include<vector>
#include<time.h>
#include "Level.h"

using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;

const string LEVEL1("./Levels/Level1.txt");

int main( int argc, char* args[])
{
	int state=1, level=0;
	vector<string> levelSelect;
	levelSelect.push_back(LEVEL1);
	Level gameLevel(1,1,1,levelSelect[level]);
	
	
	
	while(state!=99)
	{
		switch(state)
		{
			case 0:
				//state=gameLevel.menu();
				level=0;
				state=1;
				break;
			case 1:
				state=gameLevel.playLevel(levelSelect[level]);
				if(state == 1)
				{
					//level++;
				}
				if(level == levelSelect.size())
				{
					state=3;
				}
				break;
			case 2:
				//state=gameLevel.charSelectScreen();
				break;
			case 3:
				//state=gameLevel.endScreen();
				break;
			default:
				//state=gameLevel.menu();
				break;
		}
	}
	
	
	
	
	
	//gameLevel.print();
	
	return EXIT_SUCCESS;
}





	
