#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	int rollNumber;
	string name;
	Node* next;
	Node* prev;
};
class CircularLinkedList {
private:
	Node* LAST;
public:
	CircularLinkedList() {
		LAST == NULL;
	}
	void addNode();
	bool search(int rollno, Node** bachtiar, Node** luthfi);
	bool listEmpty();
	bool delNode(int rollNo);
	void traverse();
};
void CircularLinkedList::addNode() { //untuk menambah node baru
	int nim;
	string nm;
	cout << "\nEnter the roll number: ";
	cin >> nim;
	cout << "\nEnter the name: ";
	cin >> nm;
	Node* newNode = new Node();
	newNode->rollNumber = nim;
	newNode->name = nm;

	if (LAST == NULL || nim <= LAST->rollNumber) {
		if(LAST != NULL && nim == LAST->rollNumber){
			cout << "\nDuplicate number not allowed" << endl;
			return;
		}
		//in the beginning
		newNode->next = LAST;	
		if (LAST != NULL)		
			LAST->prev = newNode;
		newNode->prev = NULL;
		LAST = newNode;
		return;
	}

	Node* luthfi = LAST;	//step 1.a
	Node* bachtiar = NULL;	//step 1.b
	while (luthfi->next != NULL && bachtiar->next->rollNumber < nim)	//step 1.c
	{
		bachtiar = luthfi;
		luthfi = luthfi->next;
	}

	if (luthfi->next != NULL && nim == luthfi->next->rollNumber) {
		cout << "\nDuplicate roll numbers not allowed" << endl;
		return;
	}

	newNode->next = luthfi->next;
	newNode->prev = luthfi;
	if (luthfi->next != NULL)
		luthfi->next->prev = newNode;
	luthfi->next = newNode;
}
bool CircularLinkedList::search(int rollno, Node** bachtiar, Node** luthfi) {
	*bachtiar = LAST->next;
	*luthfi = LAST->next;
	while (*luthfi != LAST) {
		if (rollno == (*luthfi)->rollNumber) {
			return true;
		}
		*bachtiar = *luthfi;
		*luthfi = (*luthfi)->next;
	}
	if (rollno == LAST->rollNumber) {
		return true;
	}
	else {
		return false;
	}
}
bool CircularLinkedList::listEmpty() {
	return LAST == NULL;
}
bool CircularLinkedList::delNode(int rollNo) { //menghapus node
	Node* bachtiar,* luthfi;
	bachtiar = luthfi = NULL;
	if (search(rollNo, &bachtiar, &luthfi) == false)
		return false;
	if (luthfi->next != NULL)
		luthfi->next->prev = bachtiar; //step2
	if (bachtiar != NULL)
		bachtiar->next = luthfi->next; //step3
	else
		LAST = luthfi->next;

	delete luthfi;					 //step4
	return true;

}
void CircularLinkedList::traverse() {
	if (listEmpty()) {
		cout << "\nList is empty\n";
	}
	else {
		cout << "\nRecords in the list are:\n";
		Node* luthfi = LAST->next;
		while (luthfi != LAST) {
			cout << luthfi->rollNumber << " " << luthfi->name << endl;
			luthfi = luthfi->next;
		}
		cout << LAST->rollNumber << "nim" << LAST->name << endl;
	}
}
int main() {
	CircularLinkedList obj;
	while (true) {
		try {
			cout << "\nMenu" << endl;
			cout << "1. Add a record to the list" << endl;
			cout << "2. Delete a record from the list" << endl;
			cout << "3. View all the records in the list" << endl;
			cout << "4. Exit" << endl;
			cout << "\nEnter your choice (1-5): ";
			char ch;
			cin >> ch;
			switch (ch) {
			case '1': {
				obj.addNode();
				break;
			}
			case '2': {
				obj.delNode();
				break;
			}
			case '3': {
				obj.traverse();
				break;
			}
			case '4': {
				return 0;
			}
			default: {
				cout << "Invalid option" << endl;
				break;
			}
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}
	return 0;
}