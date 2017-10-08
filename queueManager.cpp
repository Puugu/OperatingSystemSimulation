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
void addNodeFIFO(int dataVal);

//create node adn insert onto tail (LIFO)
void addNodeLIFO(int dataVal);

//create node and insert via sorting
//largest to tail
void addNodeSort(int dataVal);

//create node and insert via priority
void addNodePriority(int dataVal, int priorityVal);

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