/*****************************************************************************************************
These are the methods for managing the queues.
Puugu
Project Created: 7 October 2017
Last Edited: 16 November 2017
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
	priority1Insert = NULL;
	priority2Insert = NULL;
	first2 = true;
	first3 = true;
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

//pop FIFO node
void queueManager::popNodeFIFO(){
	//check to see if head exists
	if (!head) {
		cout << "ERROR: FIFO QUEUE is empty.\n";
	}
	else {
		//output data value of popped node
		cout << "Popping: " << tail->dataVal<<endl;
		//check to see if more than one node exists
		if (tail->prevNode == NULL) {
			//empty queue
			delete tail;
			tail = NULL;
			head = NULL;
		}
		else {
			//remove node at tail
			godzilla = tail;
			tail->prevNode->nextNode = NULL;
			tail = tail->prevNode;
			delete godzilla;
			godzilla = NULL;
		}
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

//pop LIFO node
void queueManager::popNodeLIFO() {
	//check to see if head exists
	if (!head) {
		cout << "ERROR: LIFO QUEUE is empty.\n";
	}
	else {
		//output data value of popped node
		cout << "Popping: " << head->dataVal<<endl;
		//check to see if there is more than one node
		if (head->nextNode == NULL) {
			delete head;
			head = NULL;
			tail = NULL;
		}
		else {
			//remove node at head
			godzilla = head;
			head->nextNode->prevNode = NULL;
			head = head->nextNode;
			delete godzilla;
			godzilla = NULL;
		}
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
	//check to see if new node is greater than the head (and will therefore go before it)
	else if (newNode->dataVal >= head->dataVal) {
		newNode->nextNode = head;
		head->prevNode = newNode;
		head = newNode;
	}
	//check to see if new node is smaller than the tail (and will therefore go after it)
	else if (newNode->dataVal <=tail->dataVal){
		newNode->prevNode = tail;
		tail->nextNode = newNode;
		tail = newNode;
	}
	//iterate through the list to find where the sorted value goes
	else {
		//set current equal to head
		current = head;
		
		while (current != NULL) {
			//check to see if current dataVal is less than the new node
			//(therefore, newNode will go before current)
			if (newNode->dataVal >= current->dataVal) {
				//newNode goes before current
				newNode->nextNode = current;
				newNode->prevNode = current->prevNode;
				current->prevNode->nextNode = newNode;
				current->prevNode = newNode;
				//set current equal to NULL to end the loop
				current = NULL;
			}
			//increment current
			else {
				current = current->nextNode;
			}
		}
	}
}

//pop sort node
void queueManager::popNodeSort() {
	//check to see if head exists
	if (!head) {
		cout << "ERROR: SORT QUEUE is empty.\n";
	}
	else {
		//output data value of popped node
		cout << "Popping: " << head->dataVal<<endl;
		//check to see if queue only has one node
		if (head->nextNode == NULL) {
			//delete queue
			delete head;
			head = NULL;
			tail = NULL;
		}
		else {
			//pop node with highest value
			godzilla = head;
			head->nextNode->prevNode = NULL;
			head = head->nextNode;
			delete godzilla;
			godzilla = NULL;
		}
	}
}

//create node and insert via priority
void queueManager::addNodePriority(int dataVal, int priorityVal) {

	//create node
	queueNode * newNode = new queueNode;
	newNode->dataVal = dataVal;
	newNode->priorityVal = priorityVal;
	newNode->nextNode = NULL;
	newNode->prevNode = NULL;

	//check to see if head exists
	if (!head) {
		head = newNode;
		tail = newNode;
	}
	//check to see if priority of newNode is >= the priority of the head
	//(if it is, then insert it at the head)
	else if (newNode->priorityVal >= head->priorityVal){
		newNode->nextNode = head;
		head->prevNode = newNode;
		head = newNode;
	}
	//check to see if the newNode's priority value is lower than 
	//that of the tail (if so, make it the new tail
	else if (newNode->priorityVal < tail->priorityVal) {
		newNode->prevNode = tail;
		tail->nextNode = newNode;
		tail = newNode;
	}
	/*check to see if head and tail are the same
	if so, insert node before/after head in relation to appropriate priorities
	(this checks to see if there is more than one node in the list)*/
	else if (head == tail) {
		if (head->priorityVal > newNode->priorityVal) {
			//make newNode the tail
			head->nextNode = newNode;
			newNode->prevNode = head;
			tail = newNode;
		}
		else {
			//newNode->priorityVal is >= head->priorityVal
			//make newNode the head
			tail->prevNode = newNode;
			newNode->nextNode = tail;
			head = newNode;
		}
	}
	//iterate through list to find where priority 2 or 1 begins (as relative to priorityVal
	//of newNode) and insert in correct location
	else {
		//set current equal to head
		current = head;

		while (current != NULL) {
			//check to see if priority of current node equals priority of newNode
			//if it does, insert newNode before current node
			if (current->priorityVal == newNode->priorityVal) {
				newNode->nextNode = current;
				newNode->prevNode = current->prevNode;
				current->prevNode->nextNode = newNode;
				current->prevNode = newNode;
				//set current equal to NULL to exit loop
				current = NULL;
			}
			else {
				//increment current
				current = current->nextNode;
			}
		}
	}

	////check to see if head exists
	//if (!head) {
	//	head = newNode;
	//	tail = newNode;
	//	//check to see if prioritiy value is 2 or 3
	//	if (priorityVal == 2) {
	//		//set priority1 marker
	//		priority1Insert = newNode;
	//		//reset p2 checker
	//		first2 = false;
	//	}
	//	else if(priorityVal == 3) {
	//		//set priority2 marker
	//		priority2Insert = newNode;
	//		//reset p3 checker
	//		first3 = false;
	//	}
	//}
	////check to see priority of newNode
	//else {
	//	switch (priorityVal) {
	//	case 3:
	//		newNode->nextNode = head;
	//		head->prevNode = newNode;
	//		head = newNode;
	//		//check to see if is first priority 3
	//		if (first3 == true) {
	//			//set priority2 marker
	//			priority2Insert = newNode;
	//			//reset p3 checker
	//			first3 = false;
	//		}
	//		break;
	//	case 1:
	//		//check to see if priority1 pointer has been set
	//		if (priority1Insert != NULL) {
	//			//add new node
	//			newNode->nextNode = priority1Insert->nextNode;
	//			newNode->nextNode->prevNode = newNode;
	//			newNode->prevNode = priority1Insert;
	//			priority1Insert->nextNode = newNode;
	//		}
	//		//priority1 pointer has not been set, check to see tail has priority1
	//		else if (tail->priorityVal != 1) {
	//			//no nodes with priority 1 have been added, newNode should be tail
	//			newNode->prevNode = tail;
	//			tail->nextNode = newNode;
	//			tail = newNode;
	//		}
	//		else {
	//			//set current = tail
	//			current = tail;
	//			//iterate back from tail until priority !=1
	//			while (current->priorityVal == 1) {
	//				current = current->prevNode;
	//			}
	//			//add node
	//			newNode->nextNode = current->nextNode;
	//			newNode->prevNode = current;
	//			current->nextNode = newNode;
	//			newNode->nextNode->prevNode = newNode;
	//		}
	//		break;
	//	case 2:
	//		//check to see if is first p2
	//		if (first2 == true) {
	//			//set p1 pointer to node
	//			priority1Insert = newNode;
	//			//reset p2 counter
	//			first2 = false;
	//		}
	//		//check to see if priority2 pointer has been set
	//		if (priority2Insert != NULL) {
	//			//add new node
	//			newNode->nextNode = priority2Insert->nextNode;
	//			priority2Insert->nextNode->prevNode = newNode;
	//			priority2Insert->nextNode = newNode;
	//			newNode->prevNode = priority2Insert;
	//		}
	//		//priority2 pointer has not been set, no p3s have been entered and
	//		//node should be new head
	//		else {
	//			newNode->nextNode = head;
	//			head->prevNode = newNode;
	//			head = newNode;
	//		}
	//		break;
	//	default:
	//		cout << "ERROR: Priority level is too low.\n";
	//	}
	//}
}

//pop priority node
void queueManager::popNodePriority() {
	//check to see if head exists
	if (!head) {
		cout << "ERROR: PRIORITY QUEUE is empty.\n";
	}
	else {
		//output data value of popped node
		cout << "Popping: " << tail->dataVal << endl;
		//check to see if queue only has one node
		if (tail->prevNode == NULL) {
			//delete queue
			delete tail;
			tail = NULL;
			head = NULL;
		}
		else {
			//pop node with highest priority
			godzilla = tail;
			tail->prevNode->nextNode = NULL;
			tail = tail->prevNode;
			delete godzilla;
			godzilla = NULL;
		}
	}
}

//display queue
void queueManager::displayQueue() {
	//check to see if head exists
	if (!head) {
		cout << "ERROR: No list exists.\n";
	}
	else if (head == tail) {
		//there is only one element in the list
		//display that element
		cout << head->dataVal << endl;
	}
	else {
		//set current equal to the head
		current = head;
		do {
			//display current value
			cout << current->dataVal << ", ";
			//increment current
			current = current->nextNode;
		} while (current->nextNode != NULL);
		//display data value of last node
		cout << current->dataVal << endl;
	}
}

//destructor
queueManager::~queueManager() {
	//check to see if head exists
	if (!head) {
		cout << "List is empty.\n";
	}
	else {
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
}