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
using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

int main( int argc, char* args[])
{
	//declare variables
	SDL_Window * gameWindow=NULL;
	SDL_Surface * screen=NULL;
	SDL_Surface * bookshelf=NULL;
	string bookshelf_image_path= "./Images/bookshelf.jpeg";
	
	//initialize everything
	if(SDL_Init(SDL_INIT_EVERYTHING)<0)
	{
		cout<<"SDL failed to initialize";
		return EXIT_FAILURE;
	}
	
	//create window
	gameWindow= SDL_CreateWindow("Library Crawl", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	if(gameWindow == NULL)
	{
		cout<<"Window did not open for some reason";
		return EXIT_FAILURE;
	}
	
	//load and blit jpeg
	screen=SDL_GetWindowSurface(gameWindow);
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00) );
	bookshelf = IMG_Load(bookshelf_image_path.c_str());
	
	SDL_Rect squareSpecs;
	squareSpecs.x=200;
	squareSpecs.y=150;
	squareSpecs.w= 30;
	squareSpecs.h= 30;
	
	SDL_BlitScaled(bookshelf,NULL,screen, &squareSpecs);
	
	SDL_Delay(2000);
	
	SDL_FreeSurface(bookshelf);
	
	SDL_DestroyWindow(gameWindow);
	SDL_Quit();
	
	return EXIT_SUCCESS;
}
