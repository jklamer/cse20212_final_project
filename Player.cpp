/*
Player.cpp
Jeremy Doyle
cse20210
March 18, 2015
purpose: function definitions for Player class
*/

#include<iostream>
#include<string>
#include"Person.h"
#include"Player.h"
using namespace std;

Player::Player(string uname, int udrinkSpeed, int ucarbTolerance, int udigestionSpeed, double ucarbLevel, int uspeed) : Person()
{//I forget how to do this with inheritance - is this correct?
  name = uname;
  drinkSpeed = udrinkSpeed;
  carbTolerance = ucarbTolerance;
  digestionSpeed = udigestionSpeed;
  carbLevel = ucarbLevel;  
  speed = uspeed;
  setSpeed(speed);
}

string Player::getName(){
  return name;
}

int Player::getDrinkSpeed(){
  return drinkSpeed;
}

void Player::setDrinkSpeed(int newDrinkSpeed){
  drinkSpeed = newDrinkSpeed;
}

int Player::getCarbTolerance(){
  return carbTolerance;
}

void Player::setCarbTolerance(int newCarbTolerance){
  carbTolerance = newCarbTolerance;
}

int Player::getDigestionSpeed(){
  return digestionSpeed;
}

void Player::setDigestionSpeed(int newDigestionSpeed){
  digestionSpeed = newDigestionSpeed;
}

double Player::getCarbLevel(){
  return carbLevel;
}

void Player::setCarbLevel(double newCarbLevel){
  carbLevel = newCarbLevel;
}

bool Player::needToBurp(){
  if(carbLevel>carbTolerance){
    return 1;
  }else{
    return 0;
  }
}

void Player::print(){
  //add in code here after learning SDL tutorials
}

void Player::consume(string object){
  if(object == "rootBeer"){//if drinks root beer
    setCarbLevel(carbLevel + (1/carbTolerance));//increase sugar level by tolerance amount
  }else if(object == "hiccups"){
    setCarbLevel(carbLevel + 1);//doing +1 for now...change if need be
  }else if(object == "tums"){
    setCarbLevel(carbLevel - 1);//doing -1 for now...change if need be
  }else if(object == "chips"){
    setDrinkSpeed(drinkSpeed + 1);//drink faster
  }else if(object == "water"){
    setDrinkSpeed(drinkSpeed - 1);//drink slower
  }else if(object == "candy"){
    setSpeed(speed + 1);//increase speed
  }
}
