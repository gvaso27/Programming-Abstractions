/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "simpio.h"
#include "console.h"
using namespace std;

int Cnk(int n, int k);

int main() {
	int n = getInteger("n = ");
	int k = getInteger("k = ");
	while(n < k){//in pascal traingle n should never be lower than k
		cout<<"'n' should not be lower integer than 'k',"<<endl;
		cout<<"insert another 'k'"<<endl;
		k = getInteger("k = ");
	}
	cout<<"C(n,k) = "<<Cnk(n, k)<<endl;
    return 0;
}

int Cnk(int n, int k){
	if(k == 0 || n == k){ //this "if" returns 1 if the number is located on the sides of pascal traingle
		return 1;
	}else{
		return Cnk(n-1, k) + Cnk(n-1, k-1);// this adds up two numbers which are above the number we are looking for
	}
}
