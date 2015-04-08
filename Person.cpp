/*
Person.cpp
Jeremy Doyle
cse20210
March 24, 2015
purpose: Function definitions for Person class
*/

#include<iostream>
#include"Person.h"
using namespace std;

Person::Person(){
  speed=1;
}

void Person::move(char direction){
  //insert SDL stuff here
}

int Person::getSpeed(){
  return speed;
}

void Person::setSpeed(int newSpeed){
  speed = newSpeed;
}
