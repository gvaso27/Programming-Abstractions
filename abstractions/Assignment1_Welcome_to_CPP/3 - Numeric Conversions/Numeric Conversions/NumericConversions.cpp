/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
	cout<<intToString(0)<<endl;
	cout<<stringToInt("0")<<endl;
    return 0;
}

string intToString(int n){
	if(n < 10 && n >=0){
		char rem = n + '0';
		return string() + rem;
	}else if(n < 0 && n > -10){
		n = n * -1;
		char rem = n + '0';
		return string() + '-' + rem;
	}else if(n < -9){
		n = n * -1;
		int remains = n % 10;
		return '-' + intToString(n/10) + char(remains + '0');
	}else{
		int remains = n % 10;
		if (remains != 0){
			return intToString(n/10) + char(remains + '0');
		}else{
			return intToString(n/10) + '0'; //if the number ends with '0'
		}
	}
}

int stringToInt(string str){
	if(str.length() == 1 && str != "-"){
		char ch = str[0];
		int res = ch - '0';
		return res;
	}else if(str.length() == 2 && str[0] == '-'){
		char ch = str[1];
		int res = ch - '0';
		res = res * -1;
		return res;
	}else{
		char ch = str[str.length() - 1];
		int res = ch - '0';
		if(str[0] != '-'){
			return stringToInt(str.substr(0, str.length() - 1))  * 10 + res;
		}else{
			return (stringToInt(str.substr(1, str.length() - 2))  * 10 + res) * -1;
		}
	}
}