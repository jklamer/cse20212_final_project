/*
Player.h
Jeremy Doyle
cse 20210
March 17, 2015
purpose: Class that derives from the Person class that stores characteristics for all of the possible players that the user can play as
*/

#include<iostream>
#include"Person.h"
using namespace std;

#define PLAYER_H
#ifndef PLAYER_H

class Player : public Person{

 public:
  Player(int, int, int, int);//non-default constructor to be used for each player
  virtual void print();//virtual function to display character to screen
  void consume(Consumable);//function that allows player to drink root beer or consume powerups 

 private:
  int drinkSpeed;//stores the rate at which the player can drink soda
  int sugarTolerance;//determines how much the sugar affects the player
  int digestionSpeed;//determines how quickly the player can digest the sugar
};
