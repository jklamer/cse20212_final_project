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
#include<math.h>

using namespace std;
const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 800;

//we had an issue constructing objects with the string in the Level constructor while it still being accessable to the whole class
string char1("Biz");
Player biz(char1,10,50,3,0,20);
Person lib(35);


//construct
Level::Level(int character, int carbonationLevel, int levelNumber, string levelFileName)
{	
	changeChar(character);
	carbLevel=carbonationLevel;
	levelNum=levelNumber;
	levelFile=levelFileName;
	levelHeight=20;
	levelWidth=20;
	int xorigen=300;
	int yorigen=100;
	
	//set control variables
	rendererCheck=true;
	firstUpload=true;
	drinking=false;
	
	
	squareSpecs.x=300; 
	squareSpecs.y=100;
	squareSpecs.w=30;
	squareSpecs.h=30;
	
	srand(time(NULL));
	
		
	players.push_back(biz);
	
	
	
	
	
	
	
	
	
	//load level file from the constructor
	try{
		loadLevel(levelFile);
	} catch(char * excep)
	{
			cout<<excep;
	}


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
	if(screen == NULL)
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
	string biz_drinking_image_path("./Images/biz_drinking.jpg");
	
	
	//load images
	bookshelf =IMG_Load(bookshelf_image_path.c_str());
	floor = IMG_Load(floor_image_path.c_str());
	wall = IMG_Load(wall_image_path.c_str());
	bizRaw = IMG_Load(biz_image_path.c_str());
	consumRaw = IMG_Load(consum_image_path.c_str());
	recycleRaw = IMG_Load(recycle_image_path.c_str());
	librarianRaw = IMG_Load(librarian_image_path.c_str());
	biz_drinkingRaw=IMG_Load(biz_drinking_image_path.c_str());
	
	
	//store surface pointers
	images.push_back(bookshelf);
	images.push_back(floor);
	images.push_back(wall);
	images.push_back(bizRaw);
	images.push_back(consumRaw);
	images.push_back(recycleRaw);
	images.push_back(librarianRaw);
	images.push_back(biz_drinkingRaw);
	
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
	SDL_SetColorKey(biz_drinkingRaw,SDL_TRUE, SDL_MapRGB(biz_drinkingRaw->format,0xFF,0xFF,0xFF));
	biz_drinking=SDL_CreateTextureFromSurface(renderer1, biz_drinkingRaw);
		
	//store texture pointers
	textures.push_back(Biz);
	textures.push_back(consum);
	textures.push_back(recycle);
	textures.push_back(librarian);
	textures.push_back(biz_drinking);
	
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
	int numLibs=0;
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
 				if(drinking)
 				{
 					SDL_RenderCopy(renderer1,biz_drinking,NULL, &squareSpecs);
 				}else{
 				
 					SDL_RenderCopy(renderer1,Biz, NULL, &squareSpecs);
 				}
 				if(firstUpload){
 					players[charSelect].position(i,j);	
 				}
 				
 			}else if(floorArray[i][j] == 2)
 			{	
 				SDL_RenderCopy(renderer1,consum,NULL, &squareSpecs);
 			}else if(floorArray[i][j] == 4)
 			{
 				SDL_RenderCopy(renderer1,recycle,NULL, &squareSpecs);
 			}else if(floorArray[i][j] == 5 || floorArray[i][j] == 6)
 			{
 				
 				SDL_RenderCopy(renderer1,librarian,NULL, &squareSpecs);
 				if(firstUpload)
 				{
	 				librarians.push_back(lib);
	 				librarians[numLibs].position(j,i);
	 				numLibs++;
 				}
 				
 			}
 			
			
			squareSpecs.x+=squareSpecs.w;
		}
		
		
		squareSpecs.y+=squareSpecs.h;
	}
	
	//if(rendererCheck)
	//{
	//	SDL_RenderPresent(renderer1);
	//}
	firstUpload=false;
	SDL_UpdateWindowSurface(gameWindow);
}





int Level::playLevel(string level)
{
	librarians.clear();
	//load a new level in.
	levelFile=level;
	loadLevel(level);
	update();
	bool quit =false;
	SDL_Event e;
	int state=1;
	unsigned long int count=0;
	const Uint8 *keystates;
	
	//while the level has not been quit
	while(!quit)
	{
		while(SDL_PollEvent( &e) != 0)
		{
			if(e.type == SDL_QUIT )
			{
				quit=true;
				state = 99; //exits game
				continue;
			}else if(e.type == SDL_KEYDOWN)
			{
				if(e.key.keysym.sym == SDLK_SPACE)
				{
					drinking=true;
				}else
				{
					switch(e.key.keysym.sym)
					{
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
		}
	
	
		keystates= SDL_GetKeyboardState( NULL );
		if(keystates[SDL_SCANCODE_SPACE])
		{
			drinking=true;
		}else
		{
			drinking=false;
		}
		if(count%10==0)
		{
			moveLibs();
		}
		
		if(checkLibrarian(players[charSelect],librarians))
		{
			quit=true;
			state=1;
		}
		update();
		SDL_Delay(10);
		count++;
		//point increment code here
		
		//endcheck
	}
		
		
		
	return state;
}	


//move function for the charactor, recieves direction and changes characters position based on that
void Level::move(int direct)
{	
	int oldX=players[charSelect].getX();//cout<<"OLD X:"<<oldX<<endl;
	int oldY=players[charSelect].getY(); //cout<<"OLD Y:"<<oldY<<endl;
	switch(direct)
	{
		case 0:
			if(players[charSelect].getY() == 0)
			{
				players[charSelect].position(players[charSelect].getX(),players[charSelect].getY()); //same place
			}else if(floorArray[players[charSelect].getY()-1][players[charSelect].getX()] == 1)
			{
				players[charSelect].position(players[charSelect].getX(),players[charSelect].getY()); //same place
			}else
			{
				players[charSelect].position(players[charSelect].getX(),players[charSelect].getY()-1);
			}
			break;
		case 1:
			if(players[charSelect].getY() == 19)
			{
				players[charSelect].position(players[charSelect].getX(),players[charSelect].getY()); //same place
			}else if(floorArray[players[charSelect].getY()+1][players[charSelect].getX()] == 1)
			{
				players[charSelect].position(players[charSelect].getX(),players[charSelect].getY()); //same place
			}else
			{
				players[charSelect].position(players[charSelect].getX(),players[charSelect].getY()+1);
			}
			break;
		case 2:
			if(players[charSelect].getX() == 0)
			{
				players[charSelect].position(players[charSelect].getX(),players[charSelect].getY()); //same place
			}else if(floorArray[players[charSelect].getY()][players[charSelect].getX()-1] == 1)
			{
				players[charSelect].position(players[charSelect].getX(),players[charSelect].getY()); //same place
			}else
			{
				players[charSelect].position(players[charSelect].getX()-1,players[charSelect].getY());
			}
			break;	
		case 3:
			if(players[charSelect].getX() == 19)
			{
				players[charSelect].position(players[charSelect].getX(),players[charSelect].getY()); //same place
			}else if(floorArray[players[charSelect].getY()][players[charSelect].getX()+1] == 1)
			{
				players[charSelect].position(players[charSelect].getX(),players[charSelect].getY()); //same place
			}else
			{
				players[charSelect].position(players[charSelect].getX()+1,players[charSelect].getY());
			}
			break;
	}
	//cout<<"New X:"<<players[charSelect].getX()<<endl;
	 //cout<<"New Y:"<<players[charSelect].getY()<<endl;
	//cout<<"Square specs h"<<squareSpecs.h<<endl;
	
	floorArray[oldY][oldX]=0;
	floorArray[players[charSelect].getY()][players[charSelect].getX()]=3;
	//squareSpecs.x=players[charSelect].getX()*squareSpecs.w + xorigen;
	//squareSpecs.y=players[charSelect].getY()*(squareSpecs.h) + 100;
	 //cout<<squareSpecs.x<<","<<squareSpecs.y<<endl;
	
	//SDL_RenderClear(renderer1);
	//SDL_RenderCopy(renderer1,Biz, NULL, &squareSpecs);
	//SDL_RenderPresent(renderer1);
	
}
	
void Level::changeChar(int newChar)
{
	if(newChar >= 0 && newChar<players.size())
	{
		charSelect=newChar;
	}else
	{
		charSelect=0;
	}
}
	
void Level::moveLibs()
{
	bool moveMade=false;
	int oldX;
	int oldY;
	for(int i=0;i<librarians.size();i++)
	{
		oldX=librarians[i].getX();//cout<<"OLD X:"<<oldX<<endl;
		oldY=librarians[i].getY(); //cout<<"OLD Y:"<<oldY<<endl;
		moveMade=false;
		while(!moveMade)
		{	
		
			
			switch(rand()%4)
			{
				case 0:
					if(librarians[i].getY() == 0)
					{
						librarians[i].position(librarians[i].getX(),librarians[i].getY()); //same place
					}else if(floorArray[librarians[i].getY()-1][librarians[i].getX()] == 1)
					{
						librarians[i].position(librarians[i].getX(),librarians[i].getY()); //same place
					}else if(floorArray[librarians[i].getY()-1][librarians[i].getX()] == 3)
					{
						librarians[i].position(librarians[i].getX(),librarians[i].getY()); //same place
						moveMade=true;
					}else 
					{
						librarians[i].position(librarians[i].getX(),librarians[i].getY()-1);
						moveMade=true;
					}
					break;
				case 1:
					if(librarians[i].getY() == 19)
					{
						librarians[i].position(librarians[i].getX(),librarians[i].getY()); //same place
					}else if(floorArray[librarians[i].getY()+1][librarians[i].getX()] == 1)
					{
						librarians[i].position(librarians[i].getX(),librarians[i].getY()); //same place
					}else if(floorArray[librarians[i].getY()+1][librarians[i].getX()] == 3)
					{
						librarians[i].position(librarians[i].getX(),librarians[i].getY()); //same place
						moveMade=true;
					}else
					{
						librarians[i].position(librarians[i].getX(),librarians[i].getY()+1);
						moveMade=true;
					}
					break;
				case 2:
					if(librarians[i].getX() == 0)
					{
						librarians[i].position(librarians[i].getX(),librarians[i].getY()); //same place
					}else if(floorArray[librarians[i].getY()][librarians[i].getX()-1] == 1)
					{
						librarians[i].position(librarians[i].getX(),librarians[i].getY()); //same place
					}else if(floorArray[librarians[i].getY()][librarians[i].getX()-1] == 3)
					{
						librarians[i].position(librarians[i].getX(),librarians[i].getY()); //same place
						moveMade=true;
					}else
					{
						librarians[i].position(librarians[i].getX()-1,librarians[i].getY());
						moveMade=true;
					}
					break;	
				case 3:
					if(librarians[i].getX() == 19)
					{
						librarians[i].position(librarians[i].getX(),librarians[i].getY()); //same place
					}else if(floorArray[librarians[i].getY()][librarians[i].getX()+1] == 1)
					{
						librarians[i].position(librarians[i].getX(),librarians[i].getY()); //same place
					}else if(floorArray[librarians[i].getY()][librarians[i].getX()+1] == 3)
					{
						librarians[i].position(librarians[i].getX(),librarians[i].getY()); //same place
						moveMade=true;
					}else
					{
						librarians[i].position(librarians[i].getX()+1,librarians[i].getY());
						moveMade=true;
					}
					break;
			}
		}
	
		
		floorArray[oldY][oldX]=0;
		floorArray[librarians[i].getY()][librarians[i].getX()]=5;
	
	
	}
	
}





//calculates the "city block" distance, as opposed to bird's flight                     

int Level::distance(Player ibiz, Person dina){

  int distance=0;

  distance=abs((ibiz.getX()-dina.getX()))+abs((ibiz.getY()-dina.getY()));

  return distance;

}


//returns 0 if player is too close to librarian, 1 otherwise                            

bool Level::checkLibrarian(Player ibiz, vector<Person> ilibrarians)
{

	bool end=false;
	for(int i=0; i<ilibrarians.size(); i++)
	{
		if(distance(ibiz, ilibrarians[i])<2)
		{
			end=true;//end the game  
			return end;                                                         
		}
  	}

return end;
}


//function that determines what kind of powerup you get, and then implements it. do we need a consumables class??                                                              
/*
vector<consumables> powerups;

for(i=0; i<powerups.getSize(); i++){

  if(biz.getX()==powerup[i].getX() && biz.getY()==powerup[i].getY()){

    int powerUp=rand()%6;

    if(powerUp==0){//delete librarian                                                   

      librarians.pop_back();//remove a librarian from librarians vector                 

    }else if(powerUp==1){//if hiccups                                                   

      setCarbLevel(carbLevel + 1);//doing +1 for now...change if need be                

    }else if(powerUp==2){//tums                                                         

      setCarbLevel(carbLevel - 1);//doing -1 for now...change if need be                

      }else if(powerUp==3){//chips                                                      

      setDrinkSpeed(drinkSpeed + 1);//drink faster                                      

    }else if(powerUp==4){//water                                                        

      setDrinkSpeed(drinkSpeed - 1);//drink slower                                      

    }else if(powerUp==5){//candy                                                        

      setSpeed(speed + 1);//increase speed                                              

    }

  }

}
*/	
