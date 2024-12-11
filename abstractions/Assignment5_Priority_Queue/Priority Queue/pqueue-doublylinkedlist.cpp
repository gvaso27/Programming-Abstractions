/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
	count = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
    Node *cp = head;
    while (cp != NULL) {
        Node *tmp = cp;
        cp = cp->next;
        delete tmp;
    }
}

int DoublyLinkedListPriorityQueue::size() {
	return count;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return size() == 0;;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	//creating new node
	Node *newNode = new Node;
	newNode->value = value;
	newNode->prev = NULL;
	newNode->next = NULL;

	//conecting new node to head
	if (head != NULL) {
		head->prev = newNode;
		newNode->next = head;
	}
	head = newNode;

	count++;
}

string DoublyLinkedListPriorityQueue::peek() {
	if (size() == 0)error("there are no elements in this list.");
	string s = head->value;
	Node *tmp = head;

	//finding the first word
	while(tmp != NULL){
		if(tmp->value < s)s = tmp->value;
		tmp = tmp->next;
	}

	return s;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (size() == 0)error("there are no elements in this list.");
	string s = peek();
	Node *tmp = head;

	//finding the node where the first word is located
	while(tmp->value != s){
		tmp = tmp->next;
	}

	//looking through all possibilities and adjusting them to remove first word
	if(tmp->next == NULL && tmp->prev == NULL){
		head = NULL;
	}else if(tmp->next != NULL && tmp->prev != NULL){
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}else if(tmp->next != NULL && tmp->prev == NULL){
		head = head->next;
	}else if(tmp->next == NULL && tmp->prev != NULL){
		tmp->prev->next = NULL;
	}

	count--;
	delete tmp;
	return s;
}

