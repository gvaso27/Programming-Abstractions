/**********************************************
 * File: pqueue-heap.h
 *
 * A priority queue class backed by a binary
 * heap.
 */
#ifndef PQueue_Heap_Included
#define PQueue_Heap_Included

#include <string>
using namespace std;

/* A class representing a priority queue backed by an
 * binary heap.
 */
class HeapPriorityQueue {
public:
	/* Constructs a new, empty priority queue backed by a binary heap. */
	HeapPriorityQueue();
	
	/* Cleans up all memory allocated by this priority queue. */
	~HeapPriorityQueue();
	
	/* Returns the number of elements in the priority queue. */
	int size();
	
	/* Returns whether or not the priority queue is empty. */
	bool isEmpty();
	
	/* Enqueues a new string into the priority queue. */
	void enqueue(string value);
	
	/* Returns, but does not remove, the lexicographically first string in the
	 * priority queue.
	 */
	string peek();
	
	/* Returns and removes the lexicographically first string in the
	 * priority queue.
	 */
	string dequeueMin();

private:
int initialSize;
string *heap;
int count;

//expanding the size of array
void expand(){
	initialSize = initialSize * 2;
	string *newHeap = new string[initialSize];
	for(int i = 0; i < count; i++){
		newHeap[i] = heap[i];
	}
	heap = newHeap;
}

//moving the new element to its place
void bubbleUp(int count){
	if(count <= 1)return;
	int parentIndex = count/2 - 1;
	if(heap[parentIndex] < heap[count - 1])return;
	if(heap[parentIndex] > heap[count - 1]){
		string s = heap[count/2-1];
		heap[parentIndex] = heap[count - 1];
		heap[count - 1] = s;
	}
	bubbleUp(parentIndex+1);
}

//moving the last element to its place
void bubbleDown(int n){
	if(heap[n] < heap[(n+1)*2 - 1] && heap[0] < heap[(n+1)*2])return;
	if(heap[(n+1)*2 - 1] > heap[(n+1)*2]){
		string s = heap[n];
		heap[n] = heap[(n+1)*2];
		heap[(n+1)*2] = s;
		n = (n+1)*2;
	}else{
		string s = heap[n];
		heap[n] = heap[(n+1)*2 - 1];
		heap[(n+1)*2 - 1] = s;
		n = (n+1)*2 - 1;
	}
	bubbleDown(n);
}
};

#endif
