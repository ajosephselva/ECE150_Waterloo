#include <iostream>
using namespace std;

struct node {
	int value;
	node * next;
};

int main() {
	
	node * head = NULL;
	node * nextNode = new node;
 
	nextNode -> value = 1;
	nextNode -> next = NULL;
	head = nextNode;
	nextNode = NULL;

	nextNode = new node;
	nextNode -> value = 2;
	nextNode -> next = NULL;
	head -> next = nextNode;
	nextNode = NULL;

	nextNode = new node;
	nextNode -> value = 3;
	nextNode -> next = NULL;
	head -> next -> next = nextNode;
	nextNode = NULL;

	nextNode = new node;
	nextNode -> value = 4;
	nextNode -> next = NULL;
	head -> next -> next -> next = nextNode;
	nextNode = NULL;

	cout << "The value stored in the last node is " << head -> next -> next -> next -> value << endl;
}