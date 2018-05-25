#include <cstdlib>
#include <iostream>
#include "List.h"

using namespace std;

List::List(){
	head = NULL;
	curr = NULL;
	temp = NULL;
	//constructor functions for our linked list
}

void List::AddNode(int addData){
	nodePtr n = new node;
	n->next = NULL;
	n->data = addData;

	if(head != NULL){
		curr = head;
		while(curr->next != NULL){
			curr = curr->next;
		}
		curr->next = n;
	}

	else{
		head = n;
	}
}

void List::DeleteNode(int delData){

	nodePtr delPtr = NULL;
	temp = head;
	curr = head;
	while(curr != NULL && curr->data != delData){ //as long as these conditions exist,the two pointers will keep moving forward
		temp = curr;
		curr = curr->next;
	}
	if(curr == NULL){
		cout<< delData << "Was not found in the list" << endl;
		delete delPtr;
	}
	else{
		delPtr = curr;
		curr = curr->next;
		temp->next = curr;
		delete delPtr;
		cout << "The value " << delData << "Was deleted" <<  endl;
	}

}

void List::PrintList(){
	curr = head;
	while(curr != NULL){
		cout << curr->data;
		curr = curr->next;
	}

}

int main(int argc, char const *argv[])
{
	
	return 0;
}


