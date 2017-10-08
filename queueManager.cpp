/*****************************************************************************************************
These are the methods for managing the queues.
Puugu
Project Created: 7 October 2017
Last Edited: 8 October 2017
*****************************************************************************************************/

#include "queueManager.h"

using namespace std;

//constructor
queueManager::queueManager() {
	/*Hey Future - Puugu, I know you always forget, so when you're looking back at old code trying
	to figure out why your constructor is giving you an error about explicit type, YOUR FUNCTION
	NAME HAS TO BE THE SAME AS YOUR CLASS NAME (when making the constructor and desctructor) */
	head = NULL;
	current = NULL;
	tail = NULL;
	godzilla = NULL;
}

//create node and insert onto head (FIFO)
void queueManager::addNodeFIFO(int dataVal) {
	//create node
	queueNode * newNode = new queueNode;
	newNode->dataVal = dataVal;
	newNode->nextNode = NULL;
	newNode->prevNode = NULL;

	//check to see if head exists
	if (!head) {
		head = newNode;
		tail = newNode;
	}
	else {
		//insert new node before head
		newNode->nextNode = head;
		head->prevNode = newNode;
		head = newNode;
	}
}

//create node adn insert onto tail (LIFO)
void queueManager::addNodeLIFO(int dataVal) {
	//create node
	queueNode * newNode = new queueNode;
	newNode->dataVal = dataVal;
	newNode->nextNode = NULL;
	newNode->prevNode = NULL;

	//check to see if head exists
	if (!head) {
		head = newNode;
		tail = newNode;
	}
	else {
		//insert node after tail
		newNode->prevNode = tail;
		tail->nextNode = newNode;
		tail = newNode;
	}
}

//create node and insert via sorting
//largest to tail
void queueManager::addNodeSort(int dataVal) {
	//create node
	queueNode * newNode = new queueNode;
	newNode->dataVal = dataVal;
	newNode->nextNode = NULL;
	newNode->prevNode = NULL;

	//check to see if head exists
	if (!head) {
		head = newNode;
		tail = newNode;
	}
	//check to see if the data value is smaller than the tail
	else if (newNode->dataVal < tail->dataVal) {
		tail->nextNode = newNode;
		newNode->prevNode = tail;
		tail = newNode;
	}
	//check to see if data value is larger than the head
	else if (newNode->dataVal >head->dataVal) {
		newNode->nextNode = head;
		head->prevNode = newNode;
		head = newNode;
	}
	//iterate through the list to find where new node goes
	else {
		//set current = head
		current = head;
		while (current->nextNode != NULL) {
			if (newNode->dataVal >= current->dataVal) {
				//insert node
				newNode->nextNode = current;
				newNode->prevNode = current->prevNode;
				current->prevNode->nextNode = newNode;
				current->prevNode = newNode;
			}
			else {
				current = current->nextNode;
			}
		}
	}
}

//create node and insert via priority
void queueManager::addNodePriority(int dataVal, int priorityVal) {
	//create node
	queueNode * newNode = new queueNode;
	newNode->dataVal = dataVal;
	newNode->nextNode = NULL;
	newNode->prevNode = NULL;
}

//display queue
void displayQueue();

//destructor
queueManager::~queueManager() {
	//set current and destruction pointers equal to the head
	current = head;
	godzilla = head;
	//delete nodes in the list
	while (godzilla != NULL) {
		current = current->nextNode;
		delete godzilla;
		godzilla = current;
	}
	//set all pointers to null
	godzilla = NULL;
	current = NULL;
	head = NULL;
	tail = NULL;
}