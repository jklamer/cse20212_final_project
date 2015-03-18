/*                                                                                         
PlayerDriver.h                                                                                       
Jeremy Doyle                                                                                       
cse 20210                                                                                        
March 18, 2015                                                                                   
purpose: Driver file to instantiate objects of Player class                                       
*/

#include<iostream>
#include"Person.h"
#include"Player.h"
#include<string>
using namespace std;

int main(){
  Player Ralph = ("Ralph",1,3,1,3);
  Player Sledge = ("Sledge",3,2,1,2);
  Player Dozer = ("Dozer",2,3,1,2);
  Player Biz = ("Biz",2,1,3,2);

  string character;

  cout<<"Please enter the name of the player whose characteristics you wish to view."<<endl;
  cin<<character;

  cout<<character.getName()<<" drinks soda at a speed of "<<character.getDrinkSpeed()<<", has a sugar tolerance level of "<<character.getSugarTolerance<<", digests the soda at a speed of "<<character.getDigestionSpeed()<<", and runs at a speed of "<<character.getSpeed()<<"."<<endl;
}
