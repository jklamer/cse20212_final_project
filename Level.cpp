/***
Level.cpp

implementation file for level class in Library Crawl
**/
#include<iostream>
#include<string>
#include<fstream>
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include "Level.h"
#include "Person.h"
#include "Player.h"
using namespace std;
const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 800;

string char1("Biz");
Player biz(char1,10,50,3,0,20);

//construct
Level::Level(int character, int carbonationLevel, int levelNumber, string levelFileName)
{	
	charSelect=character;
	carbLevel=carbonationLevel;
	levelNum=levelNumber;
	levelFile=levelFileName;
	levelHeight=20;
	levelWidth=20;
	int xorigen=300;
	int yorigen=100;
	rendererCheck=true;
	firstUpload=true;
	
	//biz(char1,10,50,3,0,20)
	
	
	squareSpecs.x=300; 
	squareSpecs.y=100;
	squareSpecs.w=30;
	squareSpecs.h=30;
	
	//load the level data into the array
	//if(levelFile != NULL)
	//{
		try{
			loadLevel(levelFile);
		} catch(char * excep)
		{
			cout<<excep;
		}
	//}
	//initialize image pointers to NULL
	gameWindow=NULL;
	screen=NULL;
	bookshelf=NULL;
	renderer1=NULL;
	
	if(IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG)
	{
		cout<<"Image support failed to load";
	}
	
	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		cout<<"Image PNG support failed to load: "<<IMG_GetError()<<endl;
	}
	
	//initialize everything
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{
		cout<<"SDL failed to initialize";
	}
	
	//create window
	gameWindow= SDL_CreateWindow("Library Crawl", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	if(gameWindow == NULL)
	{
		cout<<"Window did not open for some reason";
	}
	
	
	//get the screen surface of the window
	screen=SDL_GetWindowSurface(gameWindow);
	if(screen==NULL)
	{
		cout<<"Screen not found";
	}
	
	
	
	//create a renderer for shapes
	renderer1 = SDL_CreateRenderer( gameWindow, 1, SDL_RENDERER_TARGETTEXTURE);
	SDL_RenderClear(renderer1);
	
	if( renderer1 == NULL )
	{
		cout<<"Could not load renderer: "<<SDL_GetError();
		rendererCheck=false;
		return;
	}
	
	
	
	
	try{
		loadImages();
	}catch(string &error)
	{
		cout<<error;
		return;
	}
	
	
	
}

//deconstruct
Level::~Level()
{

	for(vector<SDL_Surface *>::iterator it=images.begin();it!=images.end();++it)
	{
		SDL_FreeSurface(*it);
		*it=NULL;
	}
	
	for(vector<SDL_Texture *>::iterator it=textures.begin(); it!=textures.end(); ++it)
	{
		SDL_DestroyTexture(*it);
		*it=NULL;
	}

	
	SDL_RenderClear(renderer1);
	SDL_DestroyRenderer(renderer1);
	renderer1=NULL;

	
	SDL_DestroyWindow(gameWindow);
	gameWindow=NULL;
	IMG_Quit();
	SDL_Quit();
	
	

}		

//load level infroamtion into array
void Level::loadLevel(string file)
{
	int number;
	ifstream input(file.c_str());
	if(input == NULL)
	{
		throw "Unable to to open file";
		return;
	}
	
	for(int i=0; i<levelHeight;i++)
	{
		for(int j=0;j<levelWidth;j++)
		{
			input >> number;
			floorArray[i][j]=number;
		}
	}
	
	firstUpload=true;
}

void Level::print()
{
	for(int i=0; i<levelHeight;i++)
	{
		for(int j=0;j<levelWidth;j++)
		{
			cout<<floorArray[i][j]<<" ";
		}
		
		cout<<endl;
	}
}


//load images
void Level::loadImages()
{
	//declare images paths
	string bookshelf_image_path("./Images/bookshelf.jpeg");
	string floor_image_path("./Images/floor.jpg");
	string wall_image_path("./Images/Wall.jpg");
	string biz_image_path("./Images/biz.jpg");
	string consum_image_path("./Images/consum.png");
	string recycle_image_path("./Images/recycle.jpg");
	string librarian_image_path("./Images/librarian.jpg");
	
	
	//load images
	bookshelf =IMG_Load(bookshelf_image_path.c_str());
	floor = IMG_Load(floor_image_path.c_str());
	wall = IMG_Load(wall_image_path.c_str());
	bizRaw = IMG_Load(biz_image_path.c_str());
	consumRaw = IMG_Load(consum_image_path.c_str());
	recycleRaw = IMG_Load(recycle_image_path.c_str());
	librarianRaw = IMG_Load(librarian_image_path.c_str());
	
	
	//store surface pointers
	images.push_back(bookshelf);
	images.push_back(floor);
	images.push_back(wall);
	images.push_back(bizRaw);
	images.push_back(consumRaw);
	images.push_back(recycleRaw);
	images.push_back(librarianRaw);
	
	
	//error check
	for(vector<SDL_Surface *>::iterator it=images.begin();it!=images.end();++it)
	{
		if(*it == NULL)
		{
			string error("Unable to Load Images");
			throw error;
		}
	}
	
	
	//manipulate background of floor occupies
	SDL_SetColorKey(bizRaw,SDL_TRUE, SDL_MapRGB(bizRaw->format,0xFF,0xFF,0xFF));
	Biz=SDL_CreateTextureFromSurface(renderer1, bizRaw);
	SDL_SetColorKey(consumRaw,SDL_TRUE, SDL_MapRGB(consumRaw->format,0xFF,0xFF,0xFF));
	consum=SDL_CreateTextureFromSurface(renderer1, consumRaw);
	SDL_SetColorKey(recycleRaw,SDL_TRUE, SDL_MapRGB(recycleRaw->format,0xFF,0xFF,0xFF));
	recycle=SDL_CreateTextureFromSurface(renderer1, recycleRaw);
	SDL_SetColorKey(librarianRaw,SDL_TRUE, SDL_MapRGB(librarianRaw->format,0xFF,0xFF,0xFF));
	librarian=SDL_CreateTextureFromSurface(renderer1, librarianRaw);
		
	//store texture pointers
	textures.push_back(Biz);
	textures.push_back(consum);
	textures.push_back(recycle);
	textures.push_back(librarian);
	
	//error check
	for(vector<SDL_Texture *>::iterator it=textures.begin(); it!=textures.end(); ++it)
	{

		if(*it == NULL)
		{
			string error("Unable to Load Textures");
			throw error;
		}
	}
}



void Level::update()
{

	squareSpecs.x=300; 
	squareSpecs.y=100;
	SDL_Rect floorSpecs = {squareSpecs.x,squareSpecs.y,squareSpecs.w*levelWidth,squareSpecs.h*levelHeight};
	SDL_Rect wallSpecs= {squareSpecs.x-squareSpecs.w/2,squareSpecs.y-squareSpecs.h/2,squareSpecs.w*(levelWidth+1),squareSpecs.h*(levelHeight+1)};
	
	
	
	try{
	
		SDL_BlitScaled(wall,NULL,screen, &wallSpecs);
		SDL_BlitScaled(floor,NULL,screen, &floorSpecs);
	}catch( exception &e)
	{
		cout<<e.what();
	}	
	
	//radner a rectangle for the floor
	//if(rendererCheck)
	//{
	
	//	SDL_SetRenderDrawColor(renderer1,0xF9,0xFD,0xAC,0xFF);
	//	SDL_RenderFillRect(renderer1, &floorSpecs);
	//}
	
	
	for(int i=0;i<levelHeight;i++)
	{
		squareSpecs.x=300;
		for(int j=0;j<levelWidth;j++)
		{
			//blit proper thing to screen
			if(floorArray[i][j] == 1)
			{
				try
				{
					SDL_BlitScaled(bookshelf,NULL,screen, &squareSpecs);
				} catch(exception &e)
				{
					cout<<e.what()<<"blit error";
				}	
			}else if(floorArray[i][j] == 3)
 			{
 				SDL_RenderCopy(renderer1,Biz, NULL, &squareSpecs);
 				if(firstUpload){
 					biz.position(i,j);
 					firstUpload=false;
 				}
 				
 			}else if(floorArray[i][j] == 2)
 			{	
 				SDL_RenderCopy(renderer1,consum,NULL, &squareSpecs);
 			}else if(floorArray[i][j] == 4)
 			{
 				SDL_RenderCopy(renderer1,recycle,NULL, &squareSpecs);
 			}else if(floorArray[i][j] == 5)
 			{
 				SDL_RenderCopy(renderer1,librarian,NULL, &squareSpecs);
 			}
 			
			
			squareSpecs.x+=squareSpecs.w;
		}
		
		
		squareSpecs.y+=squareSpecs.h;
	}
	
	//if(rendererCheck)
	//{
	//	SDL_RenderPresent(renderer1);
	//}
	SDL_UpdateWindowSurface(gameWindow);
}





int Level::playLevel(string level)
{
	//load a new level in.
	levelFile=level;
	loadLevel(level);
	update();
	bool quit =false;
	SDL_Event e;
	int state=1;
	
	
	
	//while the level has not been quit
	while(!quit)
	{
		while(SDL_PollEvent( &e) != 0)
		{
			cout<<"polled event"<<endl;
			if(e.type == SDL_QUIT )
			{
				quit=true;
				state = 99; //exits game
				continue;
			}else if(e.type == SDL_KEYDOWN)
			{
				cout<<"key pressed"<<endl;
				switch(e.key.keysym.sym)
				{
					case SDLK_SPACE:
						//enter Drinking code here
						break;
					case SDLK_w: //up
						move(0);
						break;
					case SDLK_s: //down
						move(1);//enter down code here
						break;
					case SDLK_a: //left
						move(2);//enter left code here
						break;
					case SDLK_d: //right
						move(3);//enter left code here
						break;
					case SDLK_q:
						//enter quit code here
						state=0;
						quit=true;
						continue;
						break;
					default:
						break;
				}			
			}
		}
	
	
		//insert librarian update code here
		
		//point increment code here
		
		//endcheck
	}
		
		
		
		
		
		
			
	
	
	
	
	
	
	
	return state;
}	

void Level::move(int direct)
{	
	cout<<"IN MOVE"<<endl;
	int oldX=biz.getX();cout<<"OLD X:"<<oldX<<endl;
	int oldY=biz.getY(); cout<<"OLD Y:"<<oldY<<endl;
	switch(direct)
	{
		case 0:
			if(biz.getY() == 0)
			{
				biz.position(biz.getX(),biz.getY()); //same place
			}else if(floorArray[biz.getY()-1][biz.getX()] == 1)
			{
				biz.position(biz.getX(),biz.getY()); //same place
			}else
			{
				biz.position(biz.getX(),biz.getY()-1);
			}
			break;
		case 1:
			if(biz.getY() == 19)
			{
				biz.position(biz.getX(),biz.getY()); //same place
			}else if(floorArray[biz.getY()+1][biz.getX()] == 1)
			{
				biz.position(biz.getX(),biz.getY()); //same place
			}else
			{
				biz.position(biz.getX(),biz.getY()+1);
			}
			break;
		case 2:
			if(biz.getX() == 0)
			{
				biz.position(biz.getX(),biz.getY()); //same place
			}else if(floorArray[biz.getY()][biz.getX()-1] == 1)
			{
				biz.position(biz.getX(),biz.getY()); //same place
			}else
			{
				biz.position(biz.getX()-1,biz.getY());
			}
			break;	
		case 3:
			if(biz.getX() == 19)
			{
				biz.position(biz.getX(),biz.getY()); //same place
			}else if(floorArray[biz.getY()][biz.getX()+1] == 1)
			{
				biz.position(biz.getX(),biz.getY()); //same place
			}else
			{
				biz.position(biz.getX()+1,biz.getY());
			}
			break;
	}
	//cout<<"New X:"<<biz.getX()<<endl;
	 //cout<<"New Y:"<<biz.getY()<<endl;
	//cout<<"Square specs h"<<squareSpecs.h<<endl;
	
	floorArray[oldY][oldX]=0;
	floorArray[biz.getY()][biz.getX()]=3;
	update();
	//squareSpecs.x=biz.getX()*squareSpecs.w + xorigen;
	//squareSpecs.y=biz.getY()*(squareSpecs.h) + 100;
	 //cout<<squareSpecs.x<<","<<squareSpecs.y<<endl;
	
	//SDL_RenderClear(renderer1);
	//SDL_RenderCopy(renderer1,Biz, NULL, &squareSpecs);
	//SDL_RenderPresent(renderer1);
	
}
	
	
	

	
	
	
