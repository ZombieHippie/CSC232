/*
Name: Cole Lawrence
Date: February 28th, 2015
Assignment: Asn 4
Platform/IDE: Windows 8/MVSP2013
Description:
This code demonstrates how you can perform an self-insertion sort on a singly linked
list (without creating additional SLLs). Key features of this code are the ways it
uses Java-style iterators to improve its source-code readability. This implementation
of insertion sort is not based on another source code. Considering the structure of a
singly linked list, this insertion-sort algorithm differs from standard, by the way
the algorithm finds a place to insert each unsorted element. In a standard insertion
sort the unsorted element is compared with each element of the sorted list in a
descending direction, while here we find the insertion point by comparing in an
ascending direction (due to the way the SLL works). This makes sorting lists that are
already sorted in ascending order the worst case efficiency scenario, while sorting a
list already sorted in descending order the best case efficiency scenario.
*/
#include <iostream>

template <typename T>
class LinkedList;
template <typename T>
class LLIterator;

template <typename T>
class Node //nodes to be contained with a list
{
	friend class LinkedList<T>;
	friend class LLIterator<T>;
public:
	Node(T data) : elem(data), nextPtr(NULL)
	{};
	Node(Node* ptr) : nextPtr(ptr)
	{};
private:
	T elem; //templatized data stored in node
	Node<T>* nextPtr; //pointer to the next node in list
};


template <typename T>
class LinkedList //linked list of Node objects
{
public:
	LinkedList();
	LinkedList(LinkedList<T> &linkedList);
	~LinkedList();
	void addToFront(T); //inserts new node before the first node in the list
	void addToBack(T); //inserts new node after the last node in the list
	void sort(); //sort the list
	void print() const; //print out the list
	T LinkedList<T>::pop(); // remove first element and return
	LLIterator<T> getIterator() const; // get a standarad iterator that behaves like a Java iterator.
private:
	Node<T>* insertNodeAfter(Node<T>* before, Node<T>* between); // Inserts `between` after `before` and returns that node which was after `between`
	Node<T>* insertStart(Node<T>* newStart); // Inserts `newStart` at start, while setting `newStart->nextPtr` to `start`, and returns that node which was after `newStart`
	Node<T> *startPtr; //stores the pointer of first object in the linked list
	bool isEmpty() const; //utility functions used to see if the list contains no elements
};

template <typename T>
LinkedList<T>::LinkedList() : //creates list with start as NULL
startPtr(NULL) {}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> &linkedList) : startPtr(NULL) {
	LLIterator it = linkedList.getIterator();
	if (it.hasNext()) {
		startPtr = it.next();
		Node<T>* chain = startPtr;
		while (it.hasNext()) {
			// Advance chain forward for each in the given linkedList
			chain = chain->nextPtr = it.next();
		}
	}
}

template <typename T>
LinkedList<T>::~LinkedList() {
	Node<T> *tempPtr;
	while (!isEmpty()) // List is not empty
	{
		tempPtr = startPtr->nextPtr;
		delete startPtr;
		startPtr = tempPtr;
	}
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
	return startPtr == NULL; //if the start pointer is NULL, then the list is empty
}

template <typename T>
void LinkedList<T>::addToFront(T data) {
	insertStart(new Node<T>(data));
}

template <typename T>
void LinkedList<T>::addToBack(T data) {
	Node<T> *newPtr = new Node<T>(data); //creates new node
	if (isEmpty()) { // Add to front
		startPtr = newPtr;
	}
	else {
		Node<T> *tempPtr = NULL;
		LLIterator<T> it = getIterator();
		while (it.hasNext()) // find the last element
			tempPtr = it.next();
		tempPtr->nextPtr = newPtr;
	}
}

template <typename T>
Node<T>* LinkedList<T>::insertNodeAfter(Node<T>* before, Node<T>* between) {
	Node<T>* afterBetween = between->nextPtr;
	between->nextPtr = before->nextPtr;
	before->nextPtr = between;
	return afterBetween;
}

template <typename T>
Node<T>* LinkedList<T>::insertStart(Node<T>* newStart) {
	Node<T>* afterNewStart = newStart->nextPtr;
	newStart->nextPtr = startPtr;
	startPtr = newStart;
	return afterNewStart;
}

template <typename T>
LLIterator<T> LinkedList<T>::getIterator() const {
	return LLIterator<T>(startPtr);
}

template <typename T>
void LinkedList<T>::sort() {
	if (!isEmpty()) {
		LLIterator<T> eachUnsortedIt = getIterator();
		// Use to keep track of end of sorted list
		Node<T> *lastSortedNode = NULL;

		// Initiallize lastUnsortedNode with first node
		if (eachUnsortedIt.hasNext())
			lastSortedNode = eachUnsortedIt.next();

		while (eachUnsortedIt.hasNext()) {
			// The node that we are inserting in new spot
			Node<T> *placingNode = eachUnsortedIt.next();

			// Link the nodes after placingNode to the lastSortedNode
			lastSortedNode->nextPtr = placingNode->nextPtr;

			// "Detach" placingNode from other nodes
			placingNode->nextPtr = NULL; // Unecessary

			Node<T> *currSortedNode = NULL; // Use to compare for sort
			Node<T> *prevSortedNode = NULL; // Node before currSortedNode
			LLIterator<T> eachSortedIt = getIterator();

			while (eachSortedIt.hasNext()) {
				// Keep track of nodes in case we have to insert in the place before currSortedNode
				prevSortedNode = currSortedNode;
				currSortedNode = eachSortedIt.next();

				if (currSortedNode->elem > placingNode->elem) {
					// placingNode belongs before the currSortedNode element
					if (prevSortedNode == NULL) {
						// if prevSortedNode is NULL, then there is no other Node before currSortedNode
						// therefore we need to place placingNode at the start.
						insertStart(placingNode);
					}
					else {
						// place placingNode after prevSortedNode
						insertNodeAfter(prevSortedNode, placingNode);
					}
					break;
				}
				else if (currSortedNode == lastSortedNode) {
					// insert node at end of sorted list (same spot)
					// place placingNode after lastSortedNode
					insertNodeAfter(lastSortedNode, placingNode);

					// Now the lastSortedNode is the node we just placed
					lastSortedNode = placingNode;
					break;
				}
			}
			// Next node to be sorted is node that was after placingNode
			// Note that if the Node after lastSortedNode is NULL, then the loop should cease
			eachUnsortedIt.setNext(lastSortedNode->nextPtr);
		}
	}
}

template <typename T>
void LinkedList<T>::print() const
{
	if (isEmpty())
	{
		std::cout << "The list is empty." << std::endl;
	}
	else
	{
		for (LLIterator<T> it = getIterator(); it.hasNext();) {
			std::cout << it.next()->elem << std::endl;
		}
	}
}
template <typename T>
class LLIterator {
	friend class LinkedList<T>;
private:
	Node<T>* nextPtr;
	LLIterator(Node<T>* start) :
		nextPtr(start)
	{};
public:
	void setNext(Node<T>* p_next) { nextPtr = p_next; };
	bool hasNext() const { return nextPtr != NULL; };
	Node<T>* next() {
		Node<T>* res = nextPtr;
		nextPtr = nextPtr->nextPtr;
		return res;
	};
};

#include <time.h>
#include <random>
int main() {
	// Set random seed to current time
	srand(time(NULL));

	LinkedList<float> tenRandomNumbers;
	for (int i = 0; i < 10; i++) {
		tenRandomNumbers.addToFront(.01f * (rand() % 1000));
	};
	std::cout << "Ten random floats from 0.01 to 9.99:" << std::endl;
	tenRandomNumbers.sort();
	tenRandomNumbers.print();

	int pause;
	pause << std::cin.get();
	return 0;
}