/*
Person.h
Jeremy Doyle
cse 20212
March 24, 2015
purpose: abstract base class from which any type of character (librarian or player) derives
*/

#include<iostream>
#include<SDL2/SDL.h>
#include<string>
#include<ctime>
#include<cstdlib>
#include<algorithm>

using namespace std;

#ifndef PERSON_H
#define PERSON_H

class Person{
	public:

		Person();//default constructor
		virtual void print()=0;//pure virtual function to display the person
		void move(char);//function to move the person. Takes char (wasd) as input to determine direction
		int getSpeed();//returns the speed
		void setSpeed(int);//change speed
		//may need more functions here, is hard to tell at this point
		int getX();
		int getY();
		void position(int, int);
		int getWidth();
		int getHeight();
		void Height(int);
		void Width(int);
		void erase();
		void random();
		void drinking();

	protected:
		int speed;//private data member that determines the speed at which the person moves
		int width;
		int height;
		int x;
		int y;		
		int isTextureLoaded;
		int drinkAmount;
};

#endif
