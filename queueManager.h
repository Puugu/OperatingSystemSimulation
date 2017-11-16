#pragma once

/*****************************************************************************************************
This is the header file for managing the queue for the operating systems simulation.
Puugu
Project Created: 7 October 2017
Last Edited: 16 Novemeber 2017
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
		int dataVal= 0;
		int priorityVal = 0;
	};

	//create head, tail, current, priority1&2, and destruction pointers
	queueNode * head;
	queueNode * tail;
	queueNode * current;
	queueNode * godzilla;
	queueNode * priority1Insert;
	queueNode * priority2Insert;

	//create priority2 (p2) and priority3 (p3) bool
	bool first2;
	bool first3;

public:
	//constructor
		/*Hey Future - Puugu, I know you always forget, so when you're looking back at old code trying
		to figure out why your constructor is giving you an error about explicit type, YOUR FUNCTION
		NAME HAS TO BE THE SAME AS YOUR CLASS NAME (when making the constructor and desctructor) */
	queueManager();

	//create node and insert onto head (FIFO)
	void addNodeFIFO (int dataVal);

	//pop node (FIFO)
	void popNodeFIFO();

	//get value that will be popped (FIFO
	int getFIFOpop();

	//create node adn insert onto tail (LIFO)
	void addNodeLIFO(int dataVal);

	//pop node LIFO
	void popNodeLIFO();

	//get value that will be popped (LIFO)
	int getLIFOpop();

	//create node and insert via sorting
		//largest to tail
	void addNodeSort(int dataVal);

	//pop node sort
	void popNodeSort();

	//get value that will be popped (sorting)
	int getSORTpop();

	//create node and insert via priority
	void addNodePriority(int dataVal, int priorityVal);

	//pop node priority
	void popNodePriority();

	//get node that will be popped (priority)
	int getPRIORITYpop();

	//display queue
	void displayQueue();

	//destructor
	~queueManager();
};
#endif