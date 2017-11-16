/*****************************************************************************************************
This project is designed to simulate how an operating system uses queues to manage the registers.
Puugu
Project Created: 7 October 2017
Last Edited: 16 November 2017
*****************************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "queueManager.h"
#include <fstream>

using namespace std;

//function predicates
void randomNumberGenerator(int lowNum, int highNum, int queue[100]);
void processFIFOQueue(queueManager fifo, int queue[100]);
void processLIFOQueue(queueManager lifo, int queue[100]);
void processSortQueue(queueManager sort, int queue[100]);
void processPriorityQueue(queueManager priority, int queue[100], int queuePriority[100]);
void singleRegisterSimulation(int queue1[100], int queue2[100], int queue3[100], int queue4[100], int queuePriority[100]);
void multiRegisterSimulation(int queue1[100], int queue2[100], int queue3[100], int queue4[100], int queuePriority[100]);
void multiInOneOutSimulation(int queue1[100], int queue2[100], int queue3[100], int queue4[100], int queuePriority[100]);

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
	processLIFOQueue(lifo, queue2); // Will output that list is empty when finished
	processSortQueue(sorting, queue3); // Will output that list is empty when finished
	processPriorityQueue(priority, queue4, queuePriority); // Will output that list is empty when finished

	//run single register simulation
	singleRegisterSimulation(queue1, queue2, queue3, queue4, queuePriority);

	//run 4-4 register simulation
	multiRegisterSimulation(queue1, queue2, queue3, queue4, queuePriority);

	//run 4-1 register simulation
	multiInOneOutSimulation(queue1, queue2, queue3, queue4, queuePriority);

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
	// Last Edit: 15 November 2017

	//initialize queue
	for (int i = 0; i < 10; i++) {
		lifo.addNodeLIFO(queue[i]);
	}

	//iterate through remainder of array, popping and adding to queue
	for (int i = 0; i < 100; i++) {
		lifo.popNodeLIFO();
		if (i < 90) {
			lifo.addNodeLIFO(queue[i+10]);
		}
	}
}

void processSortQueue(queueManager sort, int queue[100]) {
	// This function iterates through the sorted queue
	// Puugu
	// Created: 30 October 2017
	// Last Edit: 15 November 2017

	//initialize queue
	for (int i = 0; i < 10; i++) {
		sort.addNodeSort(queue[i]);
	}
	
	//iterate through remainder of array, popping and adding to queue
	for (int i = 0; i < 100; i++) {
		sort.popNodeSort();
		if (i < 90) {
			sort.addNodeSort(queue[i+10]);
		}
	}
}

void processPriorityQueue(queueManager priority, int queue[100], int queuePriority[100]) {
	// This function iterates through the priority-sorted queue
	// Puugu
	// Created: 30 October 2017
	// Last Edit: 16 November 2017

	//initialize queue
	for (int i = 0; i < 10; i++) {
		priority.addNodePriority(queue[i], queuePriority[i]);
	}

	//iterate through remainder of array, popping and adding to queue
	for (int i = 0; i < 100; i++) {
		priority.popNodePriority();
		if (i < 90) {
			priority.addNodePriority(queue[i+10], queuePriority[i+10]);
		}
	}
}

void singleRegisterSimulation(int queue1[100], int queue2[100], int queue3[100], int queue4[100], int queuePriority[100]) {
	// This function uses one input and one output register to write the data to the file
			//(It's so ugly and inefficient, but it gets the job done for the assignment and the clock is ticking on that)
	// Puugu
	// Created: 16 November 2017
	// Last Edit: 16 November 2017

	//declare and intiialize variables, etc.
	int regIn = 0;;
	int regOut = 0;
	int clockIn = 0;
	int clockOut = 0;
	queueManager fifo;
	queueManager lifo;
	queueManager sorting;
	queueManager priority;

	//fill beginning queue and registers with first 10 values
	for (int i = 0; i < 10; i++) {
		regIn = queue1[i];
		fifo.addNodeFIFO(regIn);
		clockIn++;
		regIn = queue2[i];
		lifo.addNodeLIFO(regIn);
		clockIn++;
		regIn = queue3[i];
		sorting.addNodeSort(regIn);
		clockIn++;
		regIn = queue4[i];
		priority.addNodePriority(regIn, queuePriority[i]);
		clockIn++;
	}

	//move through the rest of the queue
	for (int i = 0; i < 100; i++) {
		//pop value from each of the queues
		regOut = fifo.getFIFOpop();
		fifo.popNodeFIFO();
		clockOut++;
		regOut = lifo.getLIFOpop();
		lifo.popNodeLIFO();
		clockOut++;
		regOut = sorting.getSORTpop();
		sorting.popNodeSort();
		clockOut++;
		regOut = priority.getPRIORITYpop();
		priority.popNodePriority();
		clockOut++;
		//add new value to queue
		if (i < 90) {
			regIn = queue1[i+10];
			fifo.addNodeFIFO(regIn);
			clockIn++;
			regIn = queue2[i+10];
			lifo.addNodeLIFO(regIn);
			clockIn++;
			regIn = queue3[i+10];
			sorting.addNodeSort(regIn);
			clockIn++;
			regIn = queue4[i+10];
			priority.addNodePriority(regIn, queuePriority[i+10]);
			clockIn++;
		}
	}
	cout << "Clock In: " << clockIn << endl;
	cout << "Clock Out: " << clockOut << endl;
}

void multiRegisterSimulation(int queue1[100], int queue2[100], int queue3[100], int queue4[100], int queuePriority[100]) {
	// This function uses four input and four output registers to write the data to the file
			//This code is so inefficient it hurts to turn it in....
	// Puugu
	// Created: 16 November 2017
	// Last Edit: 16 November 2017

	//declare and initialize variables, etc.
	int clockIn = 0;
	int clockOut = 0;
	int regIn1 = 0;
	int regIn2 = 0;
	int regIn3 = 0;
	int regIn4 = 0;
	int regOut1 = 0;
	int regOut2 = 0;
	int regOut3 = 0;
	int regOut4 = 0;
	queueManager fifo;
	queueManager lifo;
	queueManager sorting;
	queueManager priority;
	
	//fill beginning queue and registers with first 10 values
	for (int i = 0; i < 10; i++) {
		regIn1 = queue1[i];
		regIn2 = queue2[i];
		regIn3 = queue3[i];
		regIn4 = queue4[i];
		fifo.addNodeFIFO(regIn1);
		lifo.addNodeLIFO(regIn2);
		sorting.addNodeSort(regIn3);
		priority.addNodePriority(regIn4, queuePriority[i]);
		clockIn++;
	}

	//move through the rest of the queue
	for (int i = 0; i < 100; i++) {
		//pop value from each of the queues
		regOut1 = fifo.getFIFOpop();
		regOut2 = lifo.getLIFOpop();
		regOut3 = sorting.getSORTpop();
		regOut4 = priority.getPRIORITYpop();
		fifo.popNodeFIFO();
		lifo.popNodeLIFO();
		sorting.popNodeSort();
		priority.popNodePriority();
		clockOut++;
		//add new value to queue
		if (i < 90) {
			regIn1 = queue1[i+10];
			regIn2 = queue2[i+10];
			regIn3 = queue3[i+10];
			regIn4 = queue4[i+10];
			fifo.addNodeFIFO(regIn1);
			lifo.addNodeLIFO(regIn2);
			sorting.addNodeSort(regIn3);
			priority.addNodePriority(regIn4, queuePriority[i+10]);
			clockIn++;
		}
	}
	cout << "Clock In: " << clockIn << endl;
	cout << "Clock Out: " << clockOut << endl;
}

void multiInOneOutSimulation(int queue1[100], int queue2[100], int queue3[100], int queue4[100], int queuePriority[100]) {
	// This function uses four input and one output registers to write the data to the file
	// Puugu
	// Created: 16 November 2017
	// Last Edit: 16 November 2017

	//declare and initialize variables, etc.
	int clockIn = 0;
	int clockOut = 0;
	int regIn1 = 0;
	int regIn2 = 0;
	int regIn3 = 0;
	int regIn4 = 0;
	int regOut = 0;
	queueManager fifo;
	queueManager lifo;
	queueManager sorting;
	queueManager priority;

	//fill beginning queue and registers with first 10 values
	for (int i = 0; i < 10; i++) {
		regIn1 = queue1[i];
		regIn2 = queue2[i];
		regIn3 = queue3[i];
		regIn4 = queue4[i];
		fifo.addNodeFIFO(regIn1);
		lifo.addNodeLIFO(regIn2);
		sorting.addNodeSort(regIn3);
		priority.addNodePriority(regIn4, queuePriority[i]);
		clockIn++;
	}

	//move through the rest of the queue
	for (int i = 0; i < 100; i++) {
		//pop value from each of the queues
		regOut = fifo.getFIFOpop();
		fifo.popNodeFIFO();
		clockOut++;
		regOut = lifo.getLIFOpop();
		lifo.popNodeLIFO();
		clockOut++;
		regOut = sorting.getSORTpop();
		sorting.popNodeSort();
		clockOut++;
		regOut = priority.getPRIORITYpop();
		priority.popNodePriority();
		clockOut++;
		//add new value to queue
		if (i < 90) {
			regIn1 = queue1[i + 10];
			regIn2 = queue2[i + 10];
			regIn3 = queue3[i + 10];
			regIn4 = queue4[i + 10];
			fifo.addNodeFIFO(regIn1);
			lifo.addNodeLIFO(regIn2);
			sorting.addNodeSort(regIn3);
			priority.addNodePriority(regIn4, queuePriority[i + 10]);
			clockIn++;
		}
	}
	cout << "Clock In: " << clockIn << endl;
	cout << "Clock Out: " << clockOut << endl;
}