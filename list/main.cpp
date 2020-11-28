/*
 * =====================================================================================
 *
 *		 Filename:	main.cpp
 *
 *	  Description:	
 *
 *		  Version:	1.0
 *		  Created:	11/24/2020 06:16:59 PM
 *		 Revision:	none
 *		 Compiler:	gcc
 *
 *		   Author:	YOUR NAME (), 
 *	 Organization:	
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <assert.h>
#include <iostream>

class List {
public:
	List();
	List(int value) {
		head = (Node*) malloc(sizeof(Node));
		head->value = value;
		tail = head;
	}

	~List() {
		std::cout << head->value << " " << std::endl;
		if (head == tail) {
			free(head);
			return;
		}

		Node* current = head;
		while (current) {
			current = current->next;
			free(current);
		}
	};

	friend List& operator+(List& left, const List& right) {
		auto left_copy = std::move(left);
		auto right_copt = std::move(right);
		auto result = List();
		result.tail->next = right.head;
		result.tail = right.tail;
		return &result;
	}

	void print() {
		Node* current = head;
		std::cout << "List[";
		while (current) {
			std::cout << " " << current->value;
			current = current->next;
		}
		std::cout << " ]" << std::endl;
	};
private:
	struct Node {
		int value;
		Node* next;
	};
	Node* head;
	Node* tail;
};


int main(void) {
	auto l = List(1) + List(2) + List(3) + List(4);
	l.print();
	return 0;
}
