/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cmath>
#include "console.h"
#include "simpio.h"
#include "gwindow.h"
using namespace std;

void drawingTraingles(GPoint p1, GPoint p2, GPoint p3, float length, int orderN, GWindow &gw);

int main() {
	float length = getReal("Length of the traingles: ");
	int orderN = getInteger("Sierpinski's number: ");
	while(orderN < 0){
		orderN = getInteger("Number must be 0 or more. Try again: ");
	}

	//drafing sierpinski 0 traingle
	GWindow gw(length*2, length*2);
	GPoint p1 = gw.drawPolarLine(length/2, length/2*3, length, 0);
	GPoint p2 = gw.drawPolarLine(p1, length, 120);
	GPoint p3 = gw.drawPolarLine(p2, length, 240);

	//calling reccursive function
	drawingTraingles(p1, p2, p3, length/2, orderN, gw);
    return 0;
}

void drawingTraingles(GPoint p1, GPoint p2, GPoint p3, float length, int orderN, GWindow &gw){

	//base case
	if(orderN == 0){
		return;

	}else{
		//p4 is point between p2 and p1 and this draws line from p6 to p4
		GPoint p4 = gw.drawPolarLine(p3.getX() + length/2, p2.getY() + length/2*sqrt(3.0), length, 0);

		//p5 is point between p1 and p3 and this draws line from p4 to p5
		GPoint p5 = gw.drawPolarLine(p4, length, 240);

		//p6 is point between p3 and p2 and this draws line from p5 to p6
		GPoint p6 = gw.drawPolarLine(p5, length, 120);

		orderN--;
		drawingTraingles(p4, p2, p6, length/2, orderN, gw);
		drawingTraingles(p1, p4, p5, length/2, orderN, gw);
		drawingTraingles(p5, p6, p3, length/2, orderN, gw);
	}
}