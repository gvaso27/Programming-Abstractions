/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	count = 0;
	head = NULL;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	Node *cp = head;
	while(cp != NULL){
		Node *tmp = cp;
		cp = cp->next;
		delete tmp;
	}
}

int LinkedListPriorityQueue::size() {
	return count;
}

bool LinkedListPriorityQueue::isEmpty() {
	return size() == 0;
}

void LinkedListPriorityQueue::enqueue(string value){

	//creating new node
	Node *newNode = new Node;
	newNode->value = value;
	newNode->next = NULL;

	Node *tmp = head;
	Node *prev = NULL;
	//finding the place for it to store
	while(tmp != NULL && tmp->value < value){
		prev = tmp;
		tmp = tmp->next;
	}

	//storing new node in its place
	newNode->next = tmp;
	if (prev == NULL){
        head = newNode;
    }else{
        prev->next = newNode;
    }

	count++;
}

string LinkedListPriorityQueue::peek() {
	if (size() == 0)error("there are no elements in this list.");
	return head->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	if (size() == 0)error("there are no elements in this list.");
	string s = peek();

	//we need cp to delete first word node
	Node *cp = head;
	head = head->next;
	delete cp;
	count--;
	return s;
}

