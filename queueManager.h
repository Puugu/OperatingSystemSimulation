#pragma once

/*****************************************************************************************************
This is the header file for managing the queue for the operating systems simulation.
Puugu
Project Created: 7 October 2017
Last Edited: 8 October 2017
*****************************************************************************************************/

#include <iostream>

using namespace std;

#ifndef QUEUEMANAGER_H
#define QUEUEMANAGER_H

class queueManager {
private:
	//create structure for node
	struct queueNode {
		queueNode * nextNode;
		queueNode * prevNode;
		int dataVal;
	};

	//create head, tail, current, and destruction pointer
	queueNode * head;
	queueNode * tail;
	queueNode * current;
	queueNode * godzilla;

public:
	//constructor
		/*Hey Future - Puugu, I know you always forget, so when you're looking back at old code trying
		to figure out why your constructor is giving you an error about explicit type, YOUR FUNCTION
		NAME HAS TO BE THE SAME AS YOUR CLASS NAME (when making the constructor and desctructor) */
	queueManager();

	//create node and insert onto head (FIFO)
	void addNodeFIFO (int dataVal);

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
	~queueManager();
};
#endif