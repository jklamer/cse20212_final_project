/*
Library Crawl Game interface

Jack Klamer

4/7/2015
*/


#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
const string LEVEL2("./Levels/Level2.txt");
const string LEVEL3("./Levels/Level3.txt");
const string LEVEL4("./Levels/Level4.txt");
const string LEVEL5("./Levels/Level5.txt");
const string LEVEL6("./Levels/Level6.txt");
const string LEVEL7("./Levels/Level7.txt");
const string LEVEL8("./Levels/Level8.txt");
const string LEVEL9("./Levels/Level9.txt");
const string LEVEL10("./Levels/Level10.txt");
const string LEVEL11("./Levels/Level11.txt");
const string LEVEL12("./Levels/Level12.txt");
const string LEVEL13("./Levels/Level13.txt");
const string LEVEL14("./Levels/Level14.txt");
int main( int argc, char* args[])
{
	int state=0, level=0,lives=3;
	vector<string> levelSelect;
	levelSelect.push_back(LEVEL1);
	levelSelect.push_back(LEVEL2);
	levelSelect.push_back(LEVEL3);
	levelSelect.push_back(LEVEL4);
	levelSelect.push_back(LEVEL5);
	levelSelect.push_back(LEVEL6);
	levelSelect.push_back(LEVEL7);
	levelSelect.push_back(LEVEL8);
	levelSelect.push_back(LEVEL9);
	levelSelect.push_back(LEVEL10);
	levelSelect.push_back(LEVEL11);
	levelSelect.push_back(LEVEL12);
	levelSelect.push_back(LEVEL13);
	levelSelect.push_back(LEVEL14);
	
	Level gameLevel(0,1,level+1,levelSelect[level]);
	
	
	
	while(state!=99)
	{
		switch(state)
		{
			case 0:
				gameLevel.resetCarbLevels();
				state=gameLevel.menu();
				level=0;
				lives=3;
				break;
			case 1:
				state=gameLevel.playLevel(levelSelect[level]);
				if(state==99)
				{
					//exits game unconditionally
				}else if(state == 1)
				{
					level++;
				}else if(state== -1 && lives>0)
				{
					lives--;
					state=1;
				}else if(lives<=0)
				{
					state=0;
				}
				
				if(level == levelSelect.size() && state!=99)
				{
					state=0; //end of game
				}
				break;
			case 2:
				state=gameLevel.charSelectScreen();
				break;
			case 3:
				state=gameLevel.tutorial();
				break;
			default:
				//state=gameLevel.menu();
				break;
		}
	}
	
	
	
	
	
	//gameLevel.print();
	
	return EXIT_SUCCESS;
}





	
