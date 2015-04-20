#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>
#include <string>

using namespace std;

//Might change these
//Screen dimension constants
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

/* not sure if I need this
enum DirectionType{
	RIGHT,
	LEFT,
	UP,
	DOWN
};
*/

class sprite{
	public:
		sprite();
		virtual ~sprite();
		int getX();
		int getY();
		void position(int, int);
		int getWidth();
		int getHeight();
		void Height(int);
		void Width(int);
		void erase();
		
	private:
		int width;
		int height;
		int x;
		int y;		
		int isTextureLoaded;
};

sprite::sprite(){
	Width(0);
	Height(0);
	position(0,0);
}

sprite::~sprite(){

}

int sprite::getX(){
	return x;
}

int sprite::getY(){
	return y;
}

void sprite::position(int Xcoord, int Ycoord){
	int x=Xcoord;
	int y=Ycoord;
}

int sprite::getWidth(){
	return width;
}

int sprite::getHeight(){
	return height;
}

void sprite::Height(int h){
	height=h;
}

void sprite::Width(int w){
	width=w;
}

void sprite::erase(){
	isTextureLoaded=0;
}
#endif
