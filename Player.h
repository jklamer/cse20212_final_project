/*
Player.h
Jeremy Doyle
cse 20210
March 17, 2015
purpose: Class that derives from the Person class that stores characteristics for all of the possible players that the user can play as
*/

#include<iostream>
#include<string>
#include"Person.h"
using namespace std;

#define PLAYER_H
#ifndef PLAYER_H

class Player : public Person{

 public:
  Player(string, int, int, int, int);//non-default constructor to be used for each player
  string getName();//returns the name of the player
  int getDrinkSpeed();//returns the drinkSpeed of the player
  void setDrinkSpeed(int);//sets the drinkSpeed of the player (needed for powerups)
  int getSugarTolerance();//returns the sugarTolerance of the player
  void setSugarTolerance(int);//sets the sugarTolerance of the player (needed for powerups)
  int getDigestionSpeed();//returns the digestionSpeed of the player 
  void setDigestionSpeed(int);//sets the digestionSpeed of the player (needed for powerups)

  virtual void print();//virtual function to display character to screen
  void consume(string);//function that allows player to drink root beer or consume powerups 

 private:
  string name;
  int drinkSpeed;//stores the rate at which the player can drink soda
  int sugarTolerance;//determines how much the sugar affects the player
  int digestionSpeed;//determines how quickly the player can digest the sugar
};

#endif
