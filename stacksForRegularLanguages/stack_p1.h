#ifndef stack_p1_h
#define stack_p1_h
#include <iostream>


//this file implements the functionality of the stack
template <typename T>
class stack_p1 {
	struct node
	{
		T data;
		node *next;
		node(T item) {
			this->data = item;
			this->next = NULL;
		}
		node() {}
	};

private:
	node *head;
	node *temp;

public:
	stack_p1() {
		head = NULL;
		temp = NULL;
	}
	bool isEmpty() {
		if (head == NULL)
			return true;
		else {
			return false;
		}
	}
	T pop() {
		T info;
		if (head == NULL)
			std::cout << "Empty Stack\n";
		else {
			temp = head;
			info = head->data;
			head = head->next;
			delete temp;
		}
		return info;
	}

	void push(T item) {
		if (head == NULL)
			head = new node(item);
		else {
			temp = new node(item);
			temp->next = head;
			head = temp;
		}
		return;
	}

	T peek() {
		if (head == NULL)
			std::cout << "Empty Stack";
		return head->data;
	}
};

#endif /* stack_p1_h */


