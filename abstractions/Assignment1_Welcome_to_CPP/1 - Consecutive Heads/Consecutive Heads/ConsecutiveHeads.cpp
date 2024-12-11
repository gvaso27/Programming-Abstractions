/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "random.h"
using namespace std;

int headsCount = 0; //consecutive heads count
int count = 0; //how many times was the coin flipped
int stoppingHeads = 3; //how many consecutive heads are needed to stop the coinflip

int main() {
	while(headsCount != stoppingHeads){
		if(randomChance(0.5)){
			cout<<"tails"<<endl;
			headsCount = 0;
		}else{
			cout<<"heads"<<endl;
			headsCount++;
		}
		count++;
	}
	cout<<"It took "<<count<<" to get "<<headsCount<<" consecutive heads."<<endl;
    return 0;
}