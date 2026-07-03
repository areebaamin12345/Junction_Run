#pragma once
#include <iostream>
#include <ctime>
using namespace std;

class Node {
public:
	int data;
	Node* next;
	Node* correspondingNode; // Pointer to the corresponding node in the other lane

	Node(int data) {
		this->data = data;
		next = nullptr;
		correspondingNode = nullptr; // Initialize correspondingNode to nullptr
	}
};

class LinkedList {
public:
	Node* head;
	Node* tail;

	LinkedList() {
		head = nullptr;
		tail = nullptr;
	}

	// Add a node with the given data to the end of the list
	void AddNodeLinear(int data) {
		Node* newNode = new Node(data);

		if (head == nullptr) {
			// The list is empty, so the new node becomes the head and tail
			head = newNode;
			tail = newNode;
		}
		else {
			// Append the new node to the end of the list
			tail->next = newNode;
			tail = newNode;
		}
	}

	// Display the contents of the linked list
	void Display() {
		Node* current = head;
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}

	// Function to count the number of nodes in the list
	int CountNodes() {
		int count = 0;
		Node* current = head;
		while (current != nullptr) {
			count++;
			current = current->next;
		}
		return count;
	}
};

class Lane {

	LinkedList leftLane;
	LinkedList rightLane;
	bool lane;

	Node* CurrPos = nullptr;
public:
	Lane() {
		srand(time(0));
		int x;

		for (int i = 1; i < 5; i++)
		{
			x = (rand() % 2) + 1;
			// cout << "x: " << x << endl;
			// cout << "i: " << i << endl;

			if (x == 1)
			{
				leftLane.AddNodeLinear(-1);
				rightLane.AddNodeLinear(i);
			}
			else if (x == 2)
			{
				leftLane.AddNodeLinear(i);
				rightLane.AddNodeLinear(-1);
			}

		}
		cout << "lane left: \n";
		leftLane.Display();
		cout << "lane right: \n";
		rightLane.Display();
		cout << "\n";
		LinkLanes();
	}
	void LinkLanes() {
		// Ensure both lanes have the same number of nodes
		if (leftLane.CountNodes() != rightLane.CountNodes()) {
			cout << "Both lanes must have the same number of nodes for parallel arrangement." << endl;
			return;
		}

		Node* leftCurrent = leftLane.head;
		Node* rightCurrent = rightLane.head;

		while (leftCurrent != nullptr && rightCurrent != nullptr) {

			leftCurrent->correspondingNode = rightCurrent;
			rightCurrent->correspondingNode = leftCurrent;

			leftCurrent = leftCurrent->next;
			rightCurrent = rightCurrent->next;
		}
	}
	//left=0(false)		right=1(true)
	// set lane is only for the first jump
	void setLane(bool laneFlag)
	{
		if (laneFlag)
		{
			CurrPos = rightLane.head;
			lane = true;
		}
		else {
			CurrPos = leftLane.head;
			lane = false;
		}

	}
	bool getLane()
	{
		return lane;
	}
	void MoveDiagonal(bool keyFlag)
	{
		//right right
		if (getLane() == true && keyFlag == true)
		{
			cout << "cant move right again" << endl;

		}
		//right -> left
		else if (getLane() == true && keyFlag == false)
		{
			//cout << "\n\ncur pos" << CurrPos->data << " CurrPos next data " << CurrPos->correspondingNode->next->data;
			CurrPos = CurrPos->correspondingNode->next;
			cout << "\n\nCurrPos " << CurrPos->data<<" ";
			// setLane(false);
			lane = false;

		}
		//left->right
		else if (getLane() == false && keyFlag == true)
		{
			// cout << "\n\ncur pos" << CurrPos->data << " CurrPos next data " << CurrPos->correspondingNode->next->data;
			CurrPos = CurrPos->correspondingNode->next;//added by sh
			cout << "\n\nCurrPos " << CurrPos->data << " ";
			// setLane(true);
			lane = true;
		}
		//left left
		else if (getLane() == false && keyFlag == false)
		{
			cout << "cant move left again" << endl;

		}


	}
	void MoveUp()
	{
		CurrPos = CurrPos->next;
	}
	bool checkLoss()
	{
		if (CurrPos->data == -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};