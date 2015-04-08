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
	string bookshelf_image_path= "/afs/nd.edu/coursesp.15/cse/cse20212.01/dropbox/jklamer/finalproject/cse20212_final_project/Images/bookshelf.jpeg";
	IMG_Init(IMG_INIT_JPG);
	
	//initialize everything
	if(SDL_Init(SDL_INIT_VIDEO)<0)
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
	if(screen==NULL)
	{
		cout<<"Screen not found";
		return EXIT_FAILURE;
	}
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00) );
	bookshelf = IMG_Load(bookshelf_image_path.c_str());
	if(bookshelf==NULL)
	{
		cout<<"Bookshelf failed to load";
		return EXIT_FAILURE;
	}
	SDL_Rect squareSpecs;
	squareSpecs.x=200;
	squareSpecs.y=150;
	squareSpecs.w= 30;
	squareSpecs.h= 30;
	
	try
	{
		SDL_BlitScaled(bookshelf,NULL,screen, &squareSpecs);
	} catch(exception &e)
	{
		cout<<e.what();
	}
	SDL_Delay(5000);
	
	SDL_FreeSurface(bookshelf);
	
	SDL_DestroyWindow(gameWindow);
	SDL_Quit();
	IMG_Quit();
	return EXIT_SUCCESS;
}
