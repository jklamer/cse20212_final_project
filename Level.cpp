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
#include<SDL2/SDL_ttf.h>

using namespace std;
const int SCREEN_WIDTH = 1250;
const int SCREEN_HEIGHT = 800;

SDL_Color textColor = { 255, 255, 255 };
SDL_Color gameOverTextColor={255,0,0};

//we had an issue constructing objects with the string in the Level constructor while it still being accessable to the whole class
string char1("Biz");
string char2("Sledge");
string char3("Dozer");
string char4("Ralph");

	//name,drinkSpeed, carbTolerance, digestionSpeed,carbLevel,speed
Player biz(char1,10,70,2,0,25);
Player sledge(char2,15,100,3,0,20);
Player doz(char3,10,130,2,0,15);
Player ralph(char4,5,130,2,0,20);
Person lib(12);


//construct
Level::Level(int character, int carbonationLevel, int levelNumber, string levelFileName)
{	
	changeChar(character);
	carbLevel=carbonationLevel;
	levelNum=levelNumber;
	levelFile=levelFileName;
	levelHeight=20;
	levelWidth=20;
	xorigen=300;
	yorigen=100;
	
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
	players.push_back(sledge);
	players.push_back(doz);
	players.push_back(ralph);
	
	
	
	
	
	
	
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
	
	if( TTF_Init() == -1 ) 
	{ 
		cout<< "SDL_ttf could not initialize! SDL_ttf Error: "<< TTF_GetError()<<endl; 
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
	
	
	titleFont=TTF_OpenFont("04B_19__.TTF",32);
	captionFont=TTF_OpenFont("04B_19__.TTF",20);
	if(titleFont==NULL || captionFont==NULL)
	{
		cout<<"Font did not load"<<endl;
		
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
	
	
	//Close the font that was used
	 TTF_CloseFont( titleFont );
	 TTF_CloseFont(captionFont); 
	 //Quit SDL_ttf 
	 TTF_Quit();
	
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
	string bar_image_path("./Images/bar.jpg");
	string sledge_image_path("./Images/sledge.jpg");
	string sledge_drinking_image_path("./Images/sledgeDrinking.jpg");
	string doz_image_path("./Images/doz.jpg");
	string doz_drinking_image_path("./Images/dozDrinking.jpg");
	string ralph_image_path("./Images/ralph.jpg");
	string ralph_drinking_image_path("./Images/ralphDrinking.jpg");
	
	//load images
	bookshelf =IMG_Load(bookshelf_image_path.c_str());
	floor = IMG_Load(floor_image_path.c_str());
	wall = IMG_Load(wall_image_path.c_str());
	bizRaw = IMG_Load(biz_image_path.c_str());
	consumRaw = IMG_Load(consum_image_path.c_str());
	recycleRaw = IMG_Load(recycle_image_path.c_str());
	librarianRaw = IMG_Load(librarian_image_path.c_str());
	biz_drinkingRaw=IMG_Load(biz_drinking_image_path.c_str());
	barRaw=IMG_Load(bar_image_path.c_str());
	Title = TTF_RenderText_Solid( titleFont, "Library Crawl", textColor );
	Carbonation=TTF_RenderText_Solid(captionFont, "Carbonation Level",textColor);
	RootBeerAmount=TTF_RenderText_Solid(captionFont, "Root Beer Remaining",textColor);
	GameOver=TTF_RenderText_Solid(titleFont, "GAME OVER", gameOverTextColor);
	sledgeRaw=IMG_Load(sledge_image_path.c_str());
	sledge_drinkingRaw=IMG_Load(sledge_drinking_image_path.c_str());
	dozRaw=IMG_Load(doz_image_path.c_str());
	doz_drinkingRaw=IMG_Load(doz_drinking_image_path.c_str());
	ralphRaw=IMG_Load(ralph_image_path.c_str());
	ralph_drinkingRaw=IMG_Load(ralph_drinking_image_path.c_str());
	
	//store surface pointers
	images.push_back(bookshelf);
	images.push_back(floor);
	images.push_back(wall);
	images.push_back(bizRaw);
	images.push_back(consumRaw);
	images.push_back(recycleRaw);
	images.push_back(librarianRaw);
	images.push_back(biz_drinkingRaw);
	images.push_back(barRaw);
	images.push_back(Title);
	images.push_back(Carbonation);
	images.push_back(RootBeerAmount);
	images.push_back(GameOver);
	images.push_back(sledgeRaw);
	images.push_back(sledge_drinkingRaw);
	images.push_back(dozRaw);
	images.push_back(doz_drinkingRaw);
	images.push_back(ralphRaw);
	images.push_back(ralph_drinkingRaw);
	
	
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
	SDL_SetColorKey(barRaw,SDL_TRUE, SDL_MapRGB(barRaw->format,0xFF,0xFF,0xFF));
	bar=SDL_CreateTextureFromSurface(renderer1, barRaw);
	
	SDL_SetColorKey(sledgeRaw,SDL_TRUE, SDL_MapRGB(sledgeRaw->format,0xFF,0xFF,0xFF));
	Sledge=SDL_CreateTextureFromSurface(renderer1, sledgeRaw);
	SDL_SetColorKey(sledge_drinkingRaw,SDL_TRUE, SDL_MapRGB(sledge_drinkingRaw->format,0xFF,0xFF,0xFF));
	sledge_drinking=SDL_CreateTextureFromSurface(renderer1, sledge_drinkingRaw);
	
	SDL_SetColorKey(dozRaw,SDL_TRUE, SDL_MapRGB(dozRaw->format,0xFF,0xFF,0xFF));
	Doz=SDL_CreateTextureFromSurface(renderer1, dozRaw);
	SDL_SetColorKey(doz_drinkingRaw,SDL_TRUE, SDL_MapRGB(doz_drinkingRaw->format,0xFF,0xFF,0xFF));
	doz_drinking=SDL_CreateTextureFromSurface(renderer1, doz_drinkingRaw);
	
	
	SDL_SetColorKey(ralphRaw,SDL_TRUE, SDL_MapRGB(ralphRaw->format,0xFF,0xFF,0xFF));
	Ralph=SDL_CreateTextureFromSurface(renderer1, ralphRaw);
	SDL_SetColorKey(ralph_drinkingRaw,SDL_TRUE, SDL_MapRGB(ralph_drinkingRaw->format,0xFF,0xFF,0xFF));
	ralph_drinking=SDL_CreateTextureFromSurface(renderer1, ralph_drinkingRaw);
		
	//store texture pointers
	textures.push_back(Biz);
	textures.push_back(consum);
	textures.push_back(recycle);
	textures.push_back(librarian);
	textures.push_back(biz_drinking);
	textures.push_back(bar);
	textures.push_back(Sledge);
	textures.push_back(sledge_drinking);
	textures.push_back(Doz);
	textures.push_back(doz_drinking);
	textures.push_back(Ralph);
	textures.push_back(ralph_drinking);
	
	//order matters
	faces.push_back(Biz);
	faces.push_back(Sledge);
	faces.push_back(Doz);
	faces.push_back(Ralph);
	
	drinkingFaces.push_back(biz_drinking);
	drinkingFaces.push_back(sledge_drinking);
	drinkingFaces.push_back(doz_drinking);
	drinkingFaces.push_back(ralph_drinking);
	
	
	
	
	
	
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



void Level::update(double drinkPercent, double carbPercent)
{

	
	SDL_RenderClear(renderer1);
	int numLibs=0;
	squareSpecs.x=xorigen; 
	squareSpecs.y=yorigen;
	SDL_Rect floorSpecs = {squareSpecs.x,squareSpecs.y,squareSpecs.w*levelWidth,squareSpecs.h*levelHeight};
	SDL_Rect wallSpecs= {squareSpecs.x-squareSpecs.w/2,squareSpecs.y-squareSpecs.h/2,squareSpecs.w*(levelWidth+1),squareSpecs.h*(levelHeight+1)};
	SDL_Rect titleSpecs={squareSpecs.x+10*squareSpecs.w-(Title->w)/2,10,Title->w, Title->h};
	SDL_Rect carbLevelCap={xorigen+625,yorigen+100,Carbonation->w,Carbonation->h};
	SDL_Rect rootBeerLevelCap={xorigen+625,yorigen-20,RootBeerAmount->w,RootBeerAmount->h};
	
	
	//render floors and words
	try{
		
		SDL_BlitSurface(Title,NULL,screen, &titleSpecs);
		SDL_BlitScaled(wall,NULL,screen, &wallSpecs);
		SDL_BlitScaled(floor,NULL,screen, &floorSpecs);
		SDL_BlitSurface(Carbonation,NULL,screen, &carbLevelCap);
		SDL_BlitSurface(RootBeerAmount,NULL,screen, &rootBeerLevelCap);
	}catch( exception &e)
	{
		cout<<e.what();
	}	
	
	
	for(int i=0;i<levelHeight;i++)
	{
		squareSpecs.x=xorigen;
		for(int j=0;j<levelWidth;j++)
		{
			//blit proper things to screen based on current information in array
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
 					SDL_RenderCopy(renderer1,drinkingFaces[charSelect],NULL, &squareSpecs);
 				}else{
 				
 					SDL_RenderCopy(renderer1,faces[charSelect], NULL, &squareSpecs);
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
 				if(firstUpload){
 					endX=j;
 					endY=i;	
 				}
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
	
	
	renderBar(xorigen+625,yorigen,drinkPercent,bar);
	
	renderBar(xorigen+625,yorigen+120,carbPercent,bar);
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
	
	//declare variables
	bool quit =false;
	bool consumed=false;
	SDL_Event e;
	int state=1;
	int speed=players[charSelect].getSpeed();
	int drinkSpeed=players[charSelect].getDrinkSpeed();
	int digSpeed=players[charSelect].getDigestionSpeed();
	int carbLevel=(int)players[charSelect].getCarbLevel();
	int tolerance=players[charSelect].getCarbTolerance();
	int drinkAmount=120;
	int libSpeed=lib.getSpeed();
	unsigned long int count=0,upCount=0,downCount=0,leftCount=0,rightCount=0,drinkCount=0,libSpeedCount=0;
	const Uint8 *keystates;
	//stops you from auto losing on a carry over carb level
	if(carbLevel>=tolerance){carbLevel = tolerance -6;}
	//while the level has not been quit
	while(!quit)
	{
		SDL_PollEvent( &e) ;
		keystates= SDL_GetKeyboardState( NULL );
		
		if(e.type == SDL_QUIT )
		{
			quit=true;
			state = 99; //exits game
			continue;
		}else if(e.type == SDLK_q)
		{
			state=0;
			quit=true;
			continue;
		}else
		{	
			//handle drinking or moving actions space is first so you can drinking and move
			drinking=false;
			if(keystates[SDL_SCANCODE_SPACE] && drinkAmount>0)
			{
				if(drinkCount/100 < (drinkCount+drinkSpeed)/100)
				{
					drinkAmount-=5;
					carbLevel+=10;
				}
				drinkCount+=drinkSpeed;
				drinking=true;
			}else if(keystates[SDL_SCANCODE_W])
			{
				if(upCount/100 < (upCount+speed)/100)
				{
					consumed=move(0); //up
				}
				upCount+=speed;
			}else if(keystates[SDL_SCANCODE_S])
			{
				if(downCount/100 < (downCount+speed)/100)
				{
					consumed=move(1); //down
				}
				downCount+=speed;
			}else if(keystates[SDL_SCANCODE_A])
			{
				if(leftCount/100 < (leftCount+speed)/100)
				{
					consumed=move(2); //left
				}
				leftCount+=speed;
			}else if(keystates[SDL_SCANCODE_D])
			{
				if(rightCount/100 < (rightCount+speed)/100)
				{
					consumed=move(3); //right
				}
				rightCount+=speed;
			}else if(keystates[SDL_SCANCODE_Q])
			{
				state=0;
				quit=true;
			}			
		}
		
		//handle powerup
		if(consumed)
		{
			int powerup=rand()%11;
			consumed=false;
			switch(powerup)
			{
				case 0: //Taco Bell Carb Level up
					carbLevel=(tolerance-carbLevel)/2 + carbLevel;
					break;
				case 1: //Tums Carb Level down
					carbLevel/=2;
					break;
				case 2: //Candy wall/Sugar Rush speed up
					speed*=2;
					break;
				case 3: //Its monday speed down
					speed=speed*2/3;
					break;
				case 4: //Grew a pair Tolerance Up
					tolerance=tolerance*3/2;
					break;
				case 5:// Had subway an hour ago tolerance down
					tolerance=tolerance-(tolerance-carbLevel)/2;
					break;
				case 6: //Chips drink speed up
					drinkSpeed*=2;
					break;
				case 7: // water drink speed down
					drinkSpeed=drinkSpeed*2/3;
					break;
				case 8: //D-hall Food Digestion speed up
					digSpeed*=2;
					break;
				case 9: // digestion speed down
					digSpeed/=2;
					if(digSpeed==0)digSpeed=1;
					break;
				case 10: // kills a librarian
					int randoLib=rand()%librarians.size();
					floorArray[librarians[randoLib].getY()][librarians[randoLib].getX()]=0;
					librarians.erase(librarians.begin()+randoLib);
					break;
			}
		}
	
	
		if(libSpeedCount/100 < (libSpeedCount+libSpeed)/100)
		{
			moveLibs();
		}
		libSpeedCount+=libSpeed;
		// move libs
		if(count%10==0)
		{
			
			if(carbLevel>0)carbLevel-=digSpeed;
			count=0;
		}
		
		//update the screen
		update((double)drinkAmount/120,(double)carbLevel/tolerance);
		
		
		//begin lose checks
		if(checkLibrarian(players[charSelect],librarians))
		{
			//display game over and reset
			SDL_Rect gameOverLocation={xorigen+10*squareSpecs.w-(GameOver->w)/2,yorigen+10*squareSpecs.h-(GameOver->h)/2,GameOver->w,GameOver->h};
			SDL_BlitSurface(GameOver,NULL,screen, &gameOverLocation);
			SDL_UpdateWindowSurface(gameWindow);	
			
			SDL_Delay(3000);
			quit=true;
			objectsUnderPeople.clear();
			state=-1;
		}
		if(carbLevel >= tolerance)
		{
			//display game over and reset
			SDL_Rect gameOverLocation={xorigen+10*squareSpecs.w-(GameOver->w)/2,yorigen+10*squareSpecs.h-(GameOver->h)/2,GameOver->w,GameOver->h};
			SDL_BlitSurface(GameOver,NULL,screen, &gameOverLocation);
			SDL_UpdateWindowSurface(gameWindow);	
			
			SDL_Delay(3000);
			quit=true;
			objectsUnderPeople.clear();
			state=-1;
		}
		
		//end check
		if(players[charSelect].getX()==endX && players[charSelect].getY() == endY && drinkAmount <= 0)
		{
		
			players[charSelect].setCarbLevel((double)carbLevel);
			quit=true;
			objectsUnderPeople.clear();
			state=1;
		}
		
		
		SDL_Delay(10);
		count++;
		
		
	}
		
		
		
	return state;
}	


//move function for the charactor, recieves direction and changes characters position based on that
bool Level::move(int direct)
{	
	bool consumed=false;
	int oldX=players[charSelect].getX();//cout<<"OLD X:"<<oldX<<endl;
	int oldY=players[charSelect].getY(); //cout<<"OLD Y:"<<oldY<<endl;
	//determin if new direction valid
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
	
	//handle putting object back on the map once stepped on
	if(objectsUnderPeople.count(-1)>0)
	{
		floorArray[oldY][oldX]=4;
		objectsUnderPeople.erase(-1);
	}else
	{
		floorArray[oldY][oldX]=0;
	}
	
	
	//handleing dealing with stepping on things
	if(floorArray[players[charSelect].getY()][players[charSelect].getX()] == 4)
	{
		objectsUnderPeople[-1]=4;
	}else if(floorArray[players[charSelect].getY()][players[charSelect].getX()] == 2)
	{
		consumed=true;
	}
	
	//place new spot
	floorArray[players[charSelect].getY()][players[charSelect].getX()]=3;

	return consumed;	
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
		
		//moving librarians in same manner as person but they can't move into a wall. they must alwasy move one direction.
		while(!moveMade)
		{	
		
			
			switch(rand()%4)
			{
				case 0:
					if(librarians[i].getY() == 0)
					{
						librarians[i].position(librarians[i].getX(),librarians[i].getY()); //same place
					}else if(floorArray[librarians[i].getY()-1][librarians[i].getX()] == 1 || floorArray[librarians[i].getY()-1][librarians[i].getX()] == 6)
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
					}else if(floorArray[librarians[i].getY()+1][librarians[i].getX()] == 1 || floorArray[librarians[i].getY()+1][librarians[i].getX()] == 6)
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
					}else if(floorArray[librarians[i].getY()][librarians[i].getX()-1] == 1 || floorArray[librarians[i].getY()][librarians[i].getX()-1] == 6)
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
					}else if(floorArray[librarians[i].getY()][librarians[i].getX()+1] == 1 || floorArray[librarians[i].getY()][librarians[i].getX()+1] == 6)
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
	
		//stops librarians from eating up recycling bin and consumables
		if(objectsUnderPeople.count(i)>0)
		{
			floorArray[oldY][oldX]=objectsUnderPeople[i];
			objectsUnderPeople.erase(i);
		}else
		{
			floorArray[oldY][oldX]=0;
		}
		
		if(floorArray[librarians[i].getY()][librarians[i].getX()]==4 || floorArray[librarians[i].getY()][librarians[i].getX()]==2)
		{
			objectsUnderPeople[i]=floorArray[librarians[i].getY()][librarians[i].getX()];
		}
		
		
		
		floorArray[librarians[i].getY()][librarians[i].getX()]=6;
	
	
	}
	
}





//calculates the "city block" distance, as opposed to bird's flight                     

int Level::distance(Player ibiz, Person dina){

  int distance=0;

  distance=abs((ibiz.getX()-dina.getX()))+abs((ibiz.getY()-dina.getY()));

  return distance;

}


//returns 1 if player is too close to librarian, 0 otherwise                            

bool Level::checkLibrarian(Player ibiz, vector<Person> ilibrarians)
{
	int catchableDistance;
	bool end=false;
	if(drinking)
	{
		catchableDistance = 3;
	}else
	{
		catchableDistance = 1;
	}
	
	for(int i=0; i<ilibrarians.size(); i++)
	{
		if(distance(ibiz, ilibrarians[i]) <= catchableDistance)
		{
			end=true;//end the game  
			return end;                                                         
		}
  	}

return end;
}




void Level::renderBar(int x, int y,double percentage, SDL_Texture * ibar)
{
	//render the percentage of the bar required with its origen at x,y
	int w, h;
	SDL_QueryTexture(ibar, NULL, NULL, &w, &h);
	
	double dw=(double)w;
	
	if(percentage>1){percentage=1;}
	
	SDL_Rect partofTexturetoRender={0,0,dw*percentage,h};
	SDL_Rect wholeAreaToRenderto={x,y,300*percentage,60};
	
	SDL_RenderCopy(renderer1,ibar,&partofTexturetoRender,&wholeAreaToRenderto);
}

//handling the menu, 
int Level::menu()
{
	int state=0;
	string menu_image_path("./Images/menu.jpg");
	SDL_Surface * menuScreen =IMG_Load(menu_image_path.c_str());
	if(menuScreen == NULL)
	{
		cout<<"Failed to load menu";
		return 99;
	}
	
	SDL_Event e;
	SDL_Rect fullScreen={0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_BlitScaled(menuScreen,NULL,screen, &fullScreen);
	
	bool quit=false;
	
	while(!quit)
	{
		SDL_UpdateWindowSurface(gameWindow);
		while( SDL_PollEvent(&e) != 0 ){
			if (e.type == SDL_QUIT) 
			{
				quit = true;
				state=99;
			
			}else if (e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_RETURN:
						state=2;
						quit=true;
						break;
					case SDLK_t:
						state=3;
						quit=true;
						break;
				}
			}
		}
	}
	SDL_FreeSurface(menuScreen);
	
	return state;
}		


//handle the character select screen	
int Level::charSelectScreen()
{
	int state=2;
	string charSelect_image_path("./Images/charSelect.jpg");
	SDL_Surface * charSelectScreenX =IMG_Load(charSelect_image_path.c_str());
	if(charSelectScreenX==NULL)
	{
		cout<<"Failed to character select";
		return 0;
	}
	SDL_Event e;
	SDL_Rect fullScreen={0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_BlitScaled(charSelectScreenX,NULL,screen, &fullScreen);
	
	bool quit=false;
	
	while(!quit)
	{
		SDL_UpdateWindowSurface(gameWindow);
		while( SDL_PollEvent(&e) != 0 )
		{
			if (e.type == SDL_QUIT) 
			{
				quit = true;
				state=99;

			}else if (e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_r:
						changeChar(3);
						state=1;
						quit=true;
						break;
					case SDLK_d:
						changeChar(2);
						state=1;
						quit=true;
						break;
					case SDLK_b:
						changeChar(0);
						state=1;
						quit=true;
						break;
					case SDLK_h:
						changeChar(1);
						state=1;
						quit=true;
						break;
					case SDLK_q:
						state=0;
						quit=true;
						break;
				}
			}
		}
	}
	
	
	SDL_FreeSurface(charSelectScreenX);
	
	return state;
}



//handle the tutorial screen
int Level::tutorial()
{
	
	int state=3;
	string tutorial_image_path("./Images/tutorial.jpg");
	SDL_Surface * tutorialScreen =IMG_Load(tutorial_image_path.c_str());
	if(tutorialScreen==NULL)
	{
		cout<<"Failed to load tutorial";
		return 0;
	}
	SDL_Event e;
	SDL_Rect fullScreen={0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_BlitScaled(tutorialScreen,NULL,screen, &fullScreen);
	bool quit=false;
	
	while(!quit)
	{
		SDL_UpdateWindowSurface(gameWindow);
		while( SDL_PollEvent(&e) != 0 )
		{
			if (e.type == SDL_QUIT) 
			{
				quit = true;
				state = 99;

			}else if (e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_q:
						state=0;
						quit=true;
						break;
				}
			}
		}
	}
	
	
	SDL_FreeSurface(tutorialScreen);
	
	return state;
}

//reset the carb levels on the last character
void Level::resetCarbLevels()
{
	players[charSelect].setCarbLevel(0);
}
