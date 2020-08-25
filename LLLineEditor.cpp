#include <iostream>
#include <string>
using namespace std;
// HEADER ===========================================================================
struct Node {
	Node* next = nullptr;
	string data;
};

void insertEnd(Node* head, string line);
void insertAt(Node* head, string line, unsigned int n);
void deleteLine(Node* head, string line, unsigned int n);
void editAt(Node* head, string line, unsigned int n);
void print(Node* head);
void search(Node* head, string line);
void quit(Node* head);
void testNodeIteration(Node* head);
unsigned int nodeSize(Node* head);
int commandType(string command);
void newCommand(string& command, string& line, string& position, unsigned int& n);

//===================================================================================

int main() {
	/* Stores the main data structure as the head here and updates through reference to other functions.
	input, command, position, and n are used to break apart user input into various sections. The command string
	is used in the commandType() function to change input into an int value for switch cases. The value n stores the
	users choice of line to be used in various funcitons that target specific places in the document. The position string
	is the initial string value of n.*/

	bool program = true;
	Node* head = new Node;
	string input;
	string command;
	string position;
	unsigned int n = 0;
	string line;
	newCommand(command, line, position, n);

	while (program != false) {
		switch (commandType(command)) {
		case 1: //insert
			insertAt(head, line, n);
			newCommand(command, line, position, n);
			break;
		case 2: //insertEnd
			insertEnd(head, line);
			newCommand(command, line, position, n);
			break;
		case 3: //delete
			deleteLine(head, line, n);
			newCommand(command, line, position, n);
			break;
		case 4: //edit
			editAt(head, line, n);
			newCommand(command, line, position, n);
			break;
		case 5: //print
			print(head);
			newCommand(command, line, position, n);
			break;
		case 6: //search
			search(head, line);
			newCommand(command, line, position, n);
			break;
		case 7: // request to quit
			quit(head);
		}
	}
	return 0;
}

void testNodeIteration(Node* head) {
	/* This function was used solely for testing purposes and has no effect on the code. It can be used to help with debugging */
    cout << "Test Node Iteration function called. Printing all node data: " << endl << endl;
	Node* temp = new Node;
	temp = head;
	for (unsigned int i = 0; i < nodeSize(head); ++i) {
		if (temp == head && head->next != nullptr) {
			temp = temp->next;
		}
		else {
			cout << temp->data << endl;
			temp = temp->next;
		}
	}
}

unsigned int nodeSize(Node* head) {
	/* Will get the length of the node chain which is used in various other parts of the code
	to iterate temp pointers through the chain. Also, this function is used to initialize the first
	node of in the linked list if the linked list is empty. insertAt() and insertEnd() both account for this.*/
	unsigned int size = 0;
	Node* temp = new Node;
	temp = head;
	if (head->next == nullptr) {
		Node* node = new Node;
		head->next = node;
	}

	while (temp->next != nullptr) {
		size++;
		temp = temp->next;
	}
	return size;
}
int commandType(string command) {
	if (command == "insert")
		return 1;
	else if (command == "insertEnd")
		return 2;
	else if (command == "delete")
		return 3;
	else if (command == "edit")
		return 4;
	else if (command == "print")
		return 5;
	else if (command == "search")
		return 6;
	else if (command == "quit")
		return 7;
	else
		return 8; //error case
}
void newCommand(string& command, string& line, string& position, unsigned int& n) {
	/* Takes the user input and breaks it up into substrings based on white space delimiters. Will also go
	into recursion if the user types something incorrectly. Only by typing quit will the program end.*/
	string input;
	getline(cin, input);

	command = input.substr(0, input.find(" "));
	input.erase(0, input.find(" ") + 1);
	if (command == "insertEnd" || command == "search" || command == "quit" || command == "print") {

	}
	else if (command == "insert" || command == "delete" ||  command == "edit") {
		position = input.substr(0, input.find(" "));
		try {
			n = stoi(position);
		}
		catch (invalid_argument) {
			newCommand(command, line, position, n);
		}
		input.erase(0, input.find(" ") + 1);
	}
	else
		newCommand(command, line, position, n);
	line = input;
}
void insertEnd(Node* head, string line) {
	/*The overflow string stores the first 80 characters of a line and continues to overwrite and delete the first 80 characters
	until the line is less than 80 characters long. Note this may be the opposite of what the variable name
	would assume it does, but this is so data is stored in the correct order. */
	Node* temp = new Node;
	temp = head;
	for (unsigned int i = 0; i < nodeSize(head); i++) {
		temp = temp->next;
	}
	string overflow ="";
	if (line.length() >= 80) {
		if (temp->data == "") {
			if (line.at(0) == '"')
				line.erase(0, 1);
			if (line.at(line.length() - 1) == '"')
				line.pop_back();
			overflow = line.substr(0, 80);
			line.erase(0, 80);
			temp->data = overflow;
			insertEnd(head, line);
		}
		else {
			if (line.at(0) == '"')
				line.erase(0, 1);
			if (line.at(line.length() - 1) == '"')
				line.pop_back();
			overflow = line.substr(0, 80);
			line.erase(0, 80);
			Node* node = new Node;
			node->data = overflow;
			temp->next = node;
			temp = node;
			insertEnd(head, line);
		}
	}
	else {
		if (temp->data == "") {
			temp->data = line;
			Node* node = new Node;
			temp->next = node;
		}
		else {
			Node* node = new Node;
			node->data = line;
			temp->next = node;
			temp = node;
		}
	}
}
void insertAt(Node* head, string line, unsigned int n) {
	/* This is the function called when a user uses the command "insert n "*/
    if (n == 0) {}
	
	else if (n > nodeSize(head)) {} //error catch, program does not respond to out of bound request
	else {
		Node* temp = new Node;
		temp = head;
		string overflow;
		if (nodeSize(head) == 1) {}
		else {
			for (unsigned int i = 0; i < n - 1; i++)
				temp = temp->next;
		}
		if (line.length() >= 80) {
			if (line.at(0) == '"')
				line.erase(0, 1);
			if (line.at(line.length() - 1) == '"')
				line.pop_back();
				overflow = line.substr(0, 80);
				line.erase(0, 80);
				Node* node = new Node;
				node->next = temp->next;
				temp->next = node;
				node->data = overflow;
				insertAt(head, line, n + 1);
		}
		else {
				Node* node = new Node;
				node->data = line;
				node->next = temp->next;
				temp->next = node;
		}
	}
}
void editAt(Node* head, string line, unsigned int n) {
	if (n > nodeSize(head)) {} //error catch, program does not respond to out of bound request

	else {
		Node* temp = new Node;
		temp = head;     
		string overflow;
		for (unsigned int i = 0; i < n; i++) {
			temp = temp->next;
		}
		if (line.length() >= 80) {
			overflow = line.substr(0, 80);
			line.erase(0, 80);
			temp->data = overflow;
			editAt(head, line, n + 1);
		}
		else if (line.length() <= 80 && line.empty()) {
			temp->data = line;
		}
		else {
			temp->data = line;
		}
	}
}
void deleteLine(Node* head, string line, unsigned int n) {
	Node* temp = new Node;
	temp = head;
	
	if (n > nodeSize(head)) {} //error catch. If out of bound the program does nothing
	else {
		for (unsigned int i = 0; i < n; i++) {
			temp = temp->next;
		}
		temp->data.clear();
		while (temp->next != nullptr) {
			temp->data = temp->next->data;
			if (temp->next->next == nullptr) {
				Node* end = new Node;
				end = temp->next->next;
				temp->next = nullptr;
				delete(end);
			}
			else 
				temp = temp->next;
		}
	}
}
void search(Node* head, string line) {
	if (head->next == nullptr) {}
	else {
		bool notFound = true;
		Node* temp = new Node;
		temp = head->next;
		if (line.at(0) == '"')
			line.erase(0, 1);
		if (line.at(line.length() - 1) == '"')
			line.pop_back();
		for (unsigned int i = 0; i < nodeSize(head); i++) {
			if (!temp->data.empty()) {
				if (temp->data.at(0) == '"')
					temp->data.erase(0, 1);
				if (temp->data.at(temp->data.length() - 1) == '"')
					temp->data.pop_back();
				size_t found = temp->data.find(line);
				if (found != string::npos) {
					cout << i+1 << " " << temp->data << endl;
					notFound = false;
				}
			}
			temp = temp->next;
		}
		if (notFound)
			cout << "not found" << endl;
	}
} 
void print(Node* head) {
	
	if (head->next == nullptr) {} //prevents the print function from doing anything if the entire document is empty.
	else {
		Node* temp = new Node;
		temp = head->next;

		for (unsigned int i = 0; i < nodeSize(head); ++i) {
			if (!temp->data.empty()) {
				if (temp->data.at(0) == '"')
					temp->data.erase(0,1);
				if (temp->data.at(temp->data.length()-1) == '"')
					temp->data.pop_back();
				cout << i + 1 << " " << temp->data << endl;
				temp = temp->next;
			}
		}
		//DEBUG
		Node* debug;
		debug = head->next;
		for (unsigned int i = 0; i < nodeSize(head); ++i) {
			cout << "The length of line " << i + 1 << " is: " << debug->data.length() << endl;
			debug = debug->next;
		}
	}
	
}
void quit(Node* head) {
	//deallocates memory and then quits the program
	Node* temp;
	temp = head;
	while (head != nullptr) {
		temp = head->next;
		delete head;
		head = temp;
	}
	exit(0);
}
