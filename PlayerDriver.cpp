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
  Player Ralph("Ralph",1,3,1,0,3);
  Player Sledge("Sledge",3,2,1,0,2);
  Player Dozer("Dozer",2,3,1,0,2);
  Player Biz("Biz",2,1,3,0,2);

  cout<<Ralph.getName()<<" drinks soda at a speed of "<<Ralph.getDrinkSpeed()<<", currently has carbonation level of "<<Ralph.getCarbLevel()<<", has a carbonation tolerance level of "<<Ralph.getCarbTolerance()<<", digests the soda at a speed of "<<Ralph.getDigestionSpeed()<<", and runs at a speed of "<<Ralph.getSpeed()<<"."<<endl;
}
