/////////////////////////////////////////////////***#INCLUDE DEFINITIONS***/////////////////////////////////////////////////
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>

//////////////////////////////////////////////////////////////
//
// local #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
#endif

/////////////////////////////////////////////////***STRUCT DEFINITIONS***/////////////////////////////////////////////////

#ifndef MARMOSET_TESTING

enum COURSE {CHE102, MATH115, MATH117, ECE105, ECE150, ECE190, Null};

struct Assignment 
{
	COURSE course; // CHE102, MATH117, etc.
	int assnNum; // Assignment Number
	int dueMonth; // Month due (1-12)
	int dueDay; // Day due (1-31)
	char* description; // Assignment description
};

struct HomeworkQueue
{
	Assignment* assn;
	HomeworkQueue* nextInQueue;
};

#endif

/////////////////////////////////////////////////***FUNCTION DEFINITIONS***/////////////////////////////////////////////////

bool enqueue(HomeworkQueue*& queue, const Assignment& assignment);
bool assignemntDueEarlierCheck (const Assignment* a1, const Assignment* a2);
const Assignment* dequeue(HomeworkQueue*& queue);
int daysTillDue(const HomeworkQueue* q, const COURSE course);
const Assignment* dueIn(const HomeworkQueue* q, const int numDays);


/////////////////////////////////////////////////***FUNCTIONS***/////////////////////////////////////////////////

bool assignemntDueEarlierCheck (Assignment* firstAssignemnt, Assignment* secondAssignment){

// check to see if the second assignment is empty (NULL)
	if (secondAssignment == NULL){																		
		return true;																					// returns true if the second assignment does not exist (node is empty)
	}

// check to see if assigment one is due earlier than assignment two
	if ((firstAssignemnt -> dueMonth) < (secondAssignment -> dueMonth)){
		return true;																					// returns true if the month the first assignment is due is before the month the second assignemnt is due

		// check if the first assignment is due within the same month as the second assignment
	} else if ((firstAssignemnt -> dueMonth) == (secondAssignment -> dueMonth)){
		
		// check to see if first assignment is due before the second assignment 
		if ((firstAssignemnt -> dueDay) < (secondAssignment -> dueDay)){
			return true;																				// returns true if assignment one is due before assignment two
		} else{
			return false;																				// returns false if assignment one is due after assignment two
		}
	} else{
		return false;																					// returns false if the month assigment one is due is after the month assignment two is due
	}

}

bool enqueue(HomeworkQueue*& queue, const Assignment& assignment){

// Error Checking For The Entered

	// check to see if the month of the assignment is less than 0 or greater than 12
	if (assignment.dueMonth <= 0 || assignment.dueMonth > 12) {
		return false;																					// returns false if the month the assignment is due is less than 0 or greater than 12
	}

	// check to see if the day of the assignment is less than 0 or greater than 31
	if (assignment.dueDay <= 0 || assignment.dueDay > 31) {
		return false;																					// returns false if the day the assignment is due is less than 0 or greater than 31
	}

	// check to see if the course the assignment is due for is NULL

	if (assignment.course == '\0') {
		return false;																					// returns false if the assignment does not have a course
	}

////

// create a new assignment
	Assignment* newAssignment = new Assignment;

// create a new linked list (called queue)
	HomeworkQueue* newAssignmentNode = new HomeworkQueue;

// assign the assignment to the newAssignment 
	*newAssignment = assignment;

// assign the new assignment to the new node
	newAssignmentNode -> assn = newAssignment;


// check to see if the head of the queue is NULL
	if (queue == NULL) {
		newAssignmentNode -> nextInQueue = NULL;
		queue = newAssignmentNode;
		return true;

	// make a call to the assignmentDueEarlierCheck to see if the new assignment is due before the existing assignment
	} else if (assignemntDueEarlierCheck(newAssignmentNode-> assn, queue -> assn)){
		newAssignmentNode -> nextInQueue = queue;
		queue = newAssignmentNode;
		return true;
	} else {
		HomeworkQueue* traverseThruLinkedList = queue;

		while (traverseThruLinkedList -> nextInQueue != NULL){

			if (assignemntDueEarlierCheck(newAssignmentNode -> assn, traverseThruLinkedList -> nextInQueue -> assn)){
				newAssignmentNode -> nextInQueue = traverseThruLinkedList -> nextInQueue;
				traverseThruLinkedList -> nextInQueue = newAssignmentNode;
				return true;
			}
			traverseThruLinkedList = traverseThruLinkedList -> nextInQueue;
		}
		if (traverseThruLinkedList -> nextInQueue == NULL){
			traverseThruLinkedList -> nextInQueue = newAssignmentNode;
			newAssignmentNode -> nextInQueue = NULL;
			return true;
		}
	}
}
const Assignment* dequeue(HomeworkQueue*& queue) {

// constant and variable declaration
	const Assignment* firstAssignment = 0;

// error check to see if the queue (linked list) is empty (or NULL)
	if (queue == NULL){
		//cout << "the queue is empty" << endl;
		return NULL;
	}

// process the dequeue 
	firstAssignment = queue->assn;
	queue = queue->nextInQueue;
	//cout << "the dequeue worked...finally"<< endl;
// return the assignment in thr queue
	return firstAssignment;
}


int daysTillDue(const HomeworkQueue* q, const COURSE course) {

	// constant and variable declaration
	char currentDay[100]; 
	char currentMonth[100];
	int daysUntilDue;
	const HomeworkQueue* traverseThruLinkedList = q;


	/*
	 * variables to determine time relative to todays date
	 * The time import library information was taken from : http://pubs.opengroup.org/onlinepubs/7908799/xsh/time.h.html
	 * This code is used to determine how long the assignment is due in relative to the current date
`	*/
	time_t rawtime; 
	time (&rawtime);
	struct tm *timeinfo = localtime(&rawtime);
	strftime (currentDay, sizeof(currentDay)-1, "%d", timeinfo);
	strftime (currentMonth, sizeof(currentMonth)-1, "%m", timeinfo);


	if (q->assn != NULL){
		if (q->assn->course == course){
			daysUntilDue = (q->assn->dueMonth - atoi(currentMonth))*30 + (q->assn->dueDay - atoi(currentDay));
			return daysUntilDue;
		}
	}

	while (traverseThruLinkedList->nextInQueue != NULL){
		if (traverseThruLinkedList->nextInQueue->assn->course == course){
			daysUntilDue = (traverseThruLinkedList->nextInQueue->assn->dueMonth - atoi(currentMonth))*30 + (traverseThruLinkedList->nextInQueue->assn->dueDay - atoi(currentDay));
			return daysUntilDue;
		}
		traverseThruLinkedList = traverseThruLinkedList->nextInQueue;
	}

// return INT_MAX if none of the above conditions are not met

	return 2147483647;
}


const Assignment* dueIn(const HomeworkQueue* q, const int numDays) {

	// constants and variable declaration
	int counter = 0;
	// create a new array for assignments due date
	Assignment* assignmentDueInArray = new Assignment[200];
    
    // declare a copy of the queue, declaraing a new queue each time the function is called
    const HomeworkQueue* copyOfQ = new HomeworkQueue;

    // set the new copy of the queue to the existing queue
    copyOfQ = q;

	
	// for loop to go through the entire queue and it also increments the counter    
    for(const HomeworkQueue* test = copyOfQ; test != NULL; test = test->nextInQueue){
        if(daysTillDue(test,test->assn->course) <= numDays){
            assignmentDueInArray[counter] = *(test->assn);
            counter++;
        }
    }

    // set the value of the assignment to 0 and or Null
    assignmentDueInArray[counter].course = Null;
    assignmentDueInArray[counter].assnNum = 1;
    assignmentDueInArray[counter].dueMonth = 1;
    assignmentDueInArray[counter].dueDay = 1;
    assignmentDueInArray[counter].description = 0;

    // set the pointer for the assignment
    Assignment * pointerForAssignment = assignmentDueInArray;
    
   	// return the pointer for the assignment
    if (pointerForAssignment != NULL){
    return pointerForAssignment;
}

}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
//

#ifndef MARMOSET_TESTING

int main(const int argc, const char* const argv[]) {
  		// Some test driver code here ....
	std::cout << std::endl << "Implement some more appropriate tests in main()" << std::endl << std::endl;

	HomeworkQueue* p_queue = new HomeworkQueue;
	p_queue->nextInQueue = NULL;
	p_queue->assn = NULL;

	char sampleDescription[] = "Sequential Execution";
	Assignment assn1 = 
	{
		.course = ECE150,
		.assnNum = 0,
		.dueMonth = 9,
		.dueDay = 15,
		.description = sampleDescription
	};
	
	bool enqueueSuccess = enqueue(p_queue, assn1);

	if(enqueueSuccess)
	{
		std::cout << "assn1 enqueued successfully" << std::endl << std::endl;

	}
	else
	{
		std::cout << "enqueue() failed" << std::endl << std::endl; 
	}

	const Assignment* p_firstAssignmentInQueue = dequeue(p_queue);
	
	if (p_firstAssignmentInQueue)
	{
		std::cout << "Dequeue successful..." << std::endl;
		std::cout << "Course: " << p_firstAssignmentInQueue->course << std::endl;
		std::cout << "Assignment #: " << p_firstAssignmentInQueue->assnNum << std::endl;
		std::cout << "Day due: " << p_firstAssignmentInQueue->dueDay << std::endl;
		std::cout << "Month due: " << p_firstAssignmentInQueue->dueMonth << std::endl;
		std::cout << "Description: " << p_firstAssignmentInQueue->description << std::endl;
	}
	else
	{
		std::cout << "dequeue() failed" << std::endl;
	}

	delete p_queue;

	return 0;
}

#endif
