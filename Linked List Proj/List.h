#ifndef LIST_H
#define LIST_H

class List
{
private: //They can only be defined in the functions in the class that we describe later

	typedef struct node{
		int data;
		node* next;
	}* nodePtr;

	nodePtr head;
	nodePtr curr;
	nodePtr temp;


public: //This is where the funtions go

List();
void AddNode(int addData);
void DeleteNode(int delData);
void PrintList();


};

#endif