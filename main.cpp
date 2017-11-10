/*****************************************************************************************************
This project is designed to simulate how an operating system uses queues to manage the registers.
Puugu
Project Created: 7 October 2017
Last Edited: 9 November 2017
*****************************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "queueManager.h"

using namespace std;

//function predicates
void randomNumberGenerator(int lowNum, int highNum, int queue[100]);
void processFIFOQueue(queueManager fifo, int queue[100]);
void processLIFOQueue(queueManager lifo, int queue[100]);
void processSortQueue(queueManager sort, int queue[100]);
void processPriorityQueue(queueManager priority, int queue[100], int queuePriority[100]);

int main() {
	//declare and initialize variables, etc.
	int queue1[100];
	int queue2[100];
	int queue3[100];
	int queue4[100];
	int queuePriority[100];

	//call function to create pool for queues
	randomNumberGenerator(0, 99, queue1);
	randomNumberGenerator(0, 99, queue2);
	randomNumberGenerator(0, 99, queue3);
	randomNumberGenerator(0, 99, queue4);
	randomNumberGenerator(1, 3, queuePriority);

	//create sort queue objects
	queueManager fifo;
	queueManager lifo;
	queueManager sorting;
	queueManager priority;

	//iterate through each queue
	processFIFOQueue(fifo, queue1); // Will output that list is empty when finished
	system("CLS");
	processLIFOQueue(lifo, queue2); // Will output that list is empty when finished
	system("CLS");
	processSortQueue(sorting, queue3);
	//processPriorityQueue(priority, queue4, queuePriority);

	system("pause");
	return 0;
}

void randomNumberGenerator(int lowNum, int highNum, int queue[100])
{
	// This function generates a series of random numbers from 0 to 99
	// Puugu
	// Created: 7 October 2017
	// Last Edit: 8 October 2017

	//initialize random seed
	srand(time(0));

	//check to see if low number is zero
	if (lowNum != 0) {
		//adjust highNum
				//by subtracting the low num, it allows rand() to calculate the correct
				//range of values, then adding lowNum back in places the values within
				//the correct set of possible values
		highNum -= lowNum;
	}

	//loop through array and populate with random numbers
	for (int i = 0; i < 100; i++) {
		queue[i] = rand() % highNum + lowNum;
	}
}

void processFIFOQueue(queueManager fifo, int queue[100]) {
	// This function iterates through the fifo queue
	// Puugu
	// Created: 30 October 2017
	// Last Edit: 30 October 2017

	//initialize queue
	for (int i = 0; i < 10; i++) {
		fifo.addNodeFIFO(queue[i]);
	}

	//iterate through remainder of array, popping and adding to queue
	for (int i = 0; i < 100; i++) {
		fifo.popNodeFIFO();
		if (i < 90) {
			fifo.addNodeFIFO(queue[i+10]);
		}
	}

	//exit function
	return;
}

void processLIFOQueue(queueManager lifo, int queue[100]) {
	// This function iterates through the lifo queue
	// Puugu
	// Created: 30 October 2017
	// Last Edit: 30 October 2017

	//initialize queue
	for (int i = 0; i < 10; i++) {
		lifo.addNodeLIFO(queue[i]);
	}

	//iterate through remainder of array, popping and adding to queue
	for (int i = 0; i < 100; i++) {
		lifo.popNodeLIFO();
		if (i < 90) {
			lifo.addNodeLIFO(queue[i]);
		}
	}
}

void processSortQueue(queueManager sort, int queue[100]) {
	// This function iterates through the sorted queue
	// Puugu
	// Created: 30 October 2017
	// Last Edit: 30 October 2017

	//initialize queue
	for (int i = 0; i < 10; i++) {
		sort.addNodeSort(queue[i]);
	}

	//iterate through remainder of array, popping and adding to queue
	for (int i = 0; i < 100; i++) {
		sort.popNodeSort();
		if (i < 90) {
			sort.addNodeSort(queue[i]);
		}
	}
}

void processPriorityQueue(queueManager priority, int queue[100], int queuePriority[100]) {
	// This function iterates through the priority-sorted queue
	// Puugu
	// Created: 30 October 2017
	// Last Edit: 30 October 2017

	//initialize queue
	for (int i = 0; i < 10; i++) {
		priority.addNodePriority(queue[i], queuePriority[i]);
	}

	//iterate through remainder of array, popping and adding to queue
	for (int i = 0; i < 100; i++) {
		priority.popNodePriority();
		if (i < 90) {
			priority.addNodePriority(queue[i], queuePriority[i]);
		}
	}
}