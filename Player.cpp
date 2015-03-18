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
using namespace std;

Player::Player(string uname, int udrinkSpeed, int usugarTolerance, int udigestionSpeed, int uspeed){//I forget how to do this with inheritance - is this correct?
  name = uname;
  drinkSpeed = udrinkSpeed;
  sugarTolerance = usugarTolerance;
  digestionSpeed = udigestionSpeed;
  speed = uspeed;
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

int Player::getSugarTolerance(){
  return sugarTolerance;
}

void Player::setSugarTolerance(int newSugarTolerance){
  sugarTolerance = newSugarTolerance;
}

int Player::getDigestionSpeed(){
  return digestionSpeed;
}

void Player::setDigestionSpeed(int newDigestionSpeed){
  digestionSpeed = newDigestionSpeed;
}

void Player::print(){
  //add in code here after learning SDL tutorials
}

void Player::consume(string object){
  //many if statements. each changes one of the player's characteristics depending on what object the player consumes
}
