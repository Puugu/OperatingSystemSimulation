/*****************************************************************************************************
This project is designed to simulate how an operating system uses queues to manage the registers.
Puugu
Project Created: 7 October 2017
Last Edited: 7 October 2017
*****************************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "queueManager.h"

using namespace std;

//function predicates
void randomNumberGenerator(int queue[100]);

int main() {
	//declare and initialize variables, etc.
	int queue1[100];
	int queue2[100];
	int queue3[100];
	int queue4[100];

	//call function to populate first queue
	randomNumberGenerator(queue1);

	//display to validate
	for (int i = 0; i < 100; i++) {
		cout << queue1[i] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}

void randomNumberGenerator(int queue[100]) {
	// This function generates a series of random numbers from 0 to 99
	// Puugu
	// Created: 7 October 2017
	// Last Edit: 7 October 2017

	//initialize random seed
	srand(time(0));

	//loop through array and populate with random numbers
	for (int i = 0; i < 100; i++) {
		queue[i] = rand() % 99;
	}

	//calculate random number and return
	//return rand() % 99 + 1;
}