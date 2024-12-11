/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

int VectorPriorityQueue::size() {
	return list.size();
}

bool VectorPriorityQueue::isEmpty() {
	return list.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
	list.push_back(value);
}

string VectorPriorityQueue::peek() {
	if (size() == 0) error("there are no elements in this list.");
	string s = list[0];
	//finding the first word in vector
	for(int i = 0; i < list.size(); i++){
		if(list[i] < s)s = list[i];
	}

	return s;
}

string VectorPriorityQueue::dequeueMin() {
	if (size() == 0) error("there are no elements in this list.");
	string s = peek();
	int m;
	//finding the index of the first word to remove it
	for(int i = 0; i < list.size(); i++){
		if(list[i] == s){
			m=i; 
			break;
		}
	}
	list.remove(m);

	return s;
}