/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	initialSize = 100;
	heap = new string[initialSize];
	count = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] heap;
}

int HeapPriorityQueue::size() {
	return count;
}

bool HeapPriorityQueue::isEmpty() {
	return size() == 0;
}

void HeapPriorityQueue::enqueue(string value) {
	if(initialSize == count)expand();
	heap[count] = value;
	count++;
	bubbleUp(count);
}

string HeapPriorityQueue::peek() {
	if (size() == 0)error("there are no elements in this list.");
	return heap[0];
}

string HeapPriorityQueue::dequeueMin() {
	if (size() == 0)error("there are no elements in this list.");
	string s = peek();
	heap[0] = heap[count-1];
	count--;
	bubbleDown(0);
	return s;
}

