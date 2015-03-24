/*
Player.h
Jeremy Doyle
cse 20210
March 24, 2015
purpose: Class that derives from the Person class that stores characteristics for all of the possible players that the user can play as
*/

#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>
#include<string>
#include"Person.h"
using namespace std;

class Player : public Person{

 public:
  Player(string, int, int, int, double, int);//non-default constructor to be used for each player
  string getName();//returns the name of the player
  int getDrinkSpeed();//returns the drinkSpeed of the player
  void setDrinkSpeed(int);//sets the drinkSpeed of the player (needed for powerups)
  int getCarbTolerance();//returns the carbTolerance of the player
  void setCarbTolerance(int);//sets the carbTolerance of the player (needed for powerups)
  int getDigestionSpeed();//returns the digestionSpeed of the player 
  void setDigestionSpeed(int);//sets the digestionSpeed of the player (needed for powerups)
  double getCarbLevel();//returns current carbonation level of player
  void setCarbLevel(double);//sets new carbonation level after drinking/digesting
  bool needToBurp();//determines if player drank too much root beer

  virtual void print();//virtual function to display character to screen
  void consume(string);//function that allows player to drink root beer or consume powerups 

 private:
  string name;
  int drinkSpeed;//stores the rate at which the player can drink soda
  int carbTolerance;//determines how much the carbonation affects the player
  int digestionSpeed;//determines how quickly the player can digest the sugar
  double carbLevel;//describes current level of carbonation buildup for player
};

#endif
