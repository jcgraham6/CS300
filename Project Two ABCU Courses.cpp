//============================================================================
// Name        : Project.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <time.h>
#include <vector>
#include <valarray>
#include <fstream>



using namespace std;


//======================================================================================
//Global Variable Declaration for all methods and classes
//======================================================================================


const unsigned int DEFAULT_SIZE = 179; //Define default size of hash table
string ans; //String to store user input
vector<string> courseNumbers;


void SkipBOM(ifstream &in) { //Function for removing BOM when reading file
	char test[3] = {0};
	in.read(test, 3);
	if ((unsigned char)test[0] == 0xEF &&
			(unsigned char)test[1] == 0xBB &&
			(unsigned char)test[2] == 0xBF)
	{
		return;
	}
	in.seekg(0);
}

//Define structure to hold course information
class Course {
public:
	string courseNumber;
	string courseName;
	string courseNum;
	string preRequisite1;
	string preRequisite2;
};

//Define class for hash table with data members and methods

class HashTable {
private:
	struct Node {
		Course course;
		unsigned int key; //Key for the hashed index
		Node* next; //Pointer to next node

		//Default constructor
		Node() {
			key = UINT_MAX; //Set key to max value
			next = nullptr;
		}

		//Initialize with a course
		Node(Course aCourse) : Node () {
			course = aCourse;
		}

		//Bid with the key
		Node(Course aCourse, unsigned int aKey) : Node(aCourse) {
			key = aKey;
		}
	};
	vector<Node> nodes;

	unsigned int tableSize = DEFAULT_SIZE; //179

	unsigned int hash(int key);

public:
	HashTable();
	HashTable(unsigned int size);
	virtual ~HashTable();
	void Insert(Course course);
	void PrintSorted();
	void PrintAll();
	Course PrintCourse(string courseNumber);
	void checkElements();
	bool checkCourse(string courseNumber);

};

HashTable::HashTable() { //Initialize the structure to hold courses
	nodes.resize(tableSize); //Resize the node structure
}

//Constructor for declaring size of the hash table
//Important for handling collisions

HashTable::HashTable(unsigned int size){
	this->tableSize = size; //Refer to local tableSize to adjust
	nodes.resize(size);
}


//Destructor
HashTable::~HashTable() {
	nodes.erase(nodes.begin()); //Empty nodes to create space
}

//Calculate hash value
unsigned int HashTable::hash(int key) {

	return key % tableSize; //Modular hashing
}

void HashTable::Insert(Course course) {

	unsigned key = hash(atoi(course.courseNum.c_str()));


	// retrieve node using key
	    // if no entry found for the key
	    Node* oldNode = &nodes.at(key);
	    if (oldNode == nullptr) {
	        Node* newNode = new Node(course, key);
	        nodes.insert(nodes.begin() + key, (*newNode));
	    }
	        // assign this node to the key position
	    // else if node is not used
	         // assing old node key to UNIT_MAX, set to key, set old node to bid and old node next to null pointer

	    else {
	        if (oldNode->key == UINT_MAX) {
	            oldNode->key = key;
	            oldNode->course = course;
	            oldNode->next = nullptr;
	        }

	        // else find the next open node
	        // add new newNode to end
	        else {     //if data is already here there is a collision
	            while (oldNode->next != nullptr) { //cycle to find empty node
	                oldNode = oldNode->next;
	            }
	            oldNode->next = new Node(course, key); //empty slot found for new bid
	        }
	    }
}


void HashTable::PrintAll() {

	for (auto i = nodes.begin(); i != nodes.end(); ++i) {
		if (i->key != UINT_MAX) {
			 cout << "Key " << i->key << ": | " << i->course.courseNumber << " | " << i->course.courseName << " | Prerequisites: "
				  << i->course.preRequisite1 << " | " << i->course.preRequisite2 << endl;

			Node* node = i->next;
			while (node != nullptr) {
				cout << "Chained " << node->key << ": |" << i->course.courseNumber << " | " << i->course.courseName << " | Prerequisites:  "
						  << i->course.preRequisite1 << " | " << i->course.preRequisite2 << endl;
				node = node->next;
			}
		}
	}


}


Course HashTable::PrintCourse(string courseNumber){

	cout <<"Searching..." << endl;

	Course course;

	courseNumber = courseNumber.substr(4,7); //Create into number for key


	unsigned int key = hash(atoi(courseNumber.c_str())); //Define the key
	Node *node = &(nodes.at(key)); //Create node

	if (node != nullptr && node->key != UINT_MAX) { //Node is not empty
		if (node->course.courseNum.compare(courseNumber) == 0) {
			return node->course;
	    }

		else {
			cout << "Error: Course not found in key" << endl;
			abort();
	    	}
	   }


	    if (node == nullptr && node->key == UINT_MAX) {
	    	return course;
	    }

	    while (node != nullptr) {
	    	if (node->key != UINT_MAX && node->course.courseNum.compare(courseNumber) == 0) {
	    		return node->course; //Return match if found
	    	}
	    	node = node->next; //Move to next node
	    }
	    return course;
}

void HashTable::PrintSorted() {

	sort(courseNumbers.begin(), courseNumbers.end(), [](const string& a, const string& b) {
		if(isalpha(a[0]) && isdigit(b[0])) {
			return true;
		}

		if (isdigit(a[0]) && isalpha(b[0])) {
			return false;
		}
		return a < b;
	});

	for (const string& iter : courseNumbers) {
		cout << iter << endl;
	}

	return;
}

void HashTable::checkElements() {
    if (ans == "Y" || ans == "y"){
    	return;
    }

	if (tableSize == 179) {
		cout << "HashTable is default size. Have you loaded bids? Y/N" << endl;
		cin >> ans;
		if (ans == "Y" || ans == "y") {
			return;
		}
		else if (ans == "N" || ans == "n") {
			cout << "Please load bids before calling function.\n" << endl;
		}
		else {
			cout << "Please enter in Y or N. Your input was " << ans << endl;
			return;
		}

	}

	else {
		return;
	}


}

bool HashTable::checkCourse(string courseNumber){

	bool found = false;

	for (const string& iter : courseNumbers){
		if (iter == courseNumber) {
			found = true;
			break;
		}
	}

	if (found){
		return true;
	}

	else {
		return false;
	}
}

void displayCourse(Course course) {
    cout << course.courseNumber<< ": " << course.courseName << " | Prerequisites: " << course.preRequisite1 << " | "
        << course.preRequisite2 << endl;
    return;
}

void loadCourses(string csvPath, HashTable* hashTable) {

	ifstream in(csvPath);
	SkipBOM(in);

	if (!in.is_open()) { //Unable to open throw error
		cerr << "Error: Failed to open the CSV file." << endl;
		return;
	}

	string line;
	int rowCount = 0; //Row counter

	try {
		while (getline(in, line)){

			Course course;
			stringstream lineStream(line);
			string courseNumber, courseName, preRequisite1, preRequisite2;

			if (getline(lineStream, course.courseNumber, ',')) { //courseNumber field
				if(!course.courseNumber.empty() && course.courseNumber.front() == '"') {
					course.courseNumber = course.courseNumber.substr(1);
				}
			}
			if (getline(lineStream, course.courseName, ',')) { //courseName field

			}

			if (getline(lineStream,course.preRequisite1,',')) { //preRequisite 1 field

			}

			if (getline(lineStream, course.preRequisite2, ',')) { //preRequisite 2 field

			}

			courseNumbers.push_back(course.courseNumber);
			course.courseNum = course.courseNumber.substr(4,6); //Separate number from course for key creation

			hashTable->Insert(course); //Add into table

			rowCount += 1;

			}
		} catch (const exception &e) {
			cerr << "Error:" << e.what() << endl;
		}


		in.close();

	cout << "Courses loaded!" << endl;
	cout << rowCount << " Total courses added." << endl;

	return;
}


int main(int argc, char* argv[]) {

	//Menu for option selection
	string csvPath, courseKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        courseKey = "CSCI350";
        break;
    case 3:
        csvPath = argv[1];
        courseKey = argv[2];
        break;
    default:
        csvPath = "CS300_Project2.csv";
        courseKey = "CSCI350";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the courses
    HashTable* courseTable;

    Course course;
    courseTable = new HashTable();

    int choice = 0;
    while (choice != 9) {
		cout << "Welcome to the course planner! Please pick an option: " << endl;
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  4. Print All" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:

            // Initialize a timer variable before loading bids
            ticks = clock();

            cout << "What is the name of the file? Please include file type.\nReminder, file name must NOT have any spaces. Instead use underscores (_)" << endl;
            cin >> csvPath;

            cout << "\nConfirm this is the file name: Y/N\n" << csvPath << endl;

            cin >> ans;

            if (ans == "Y" || ans == "y") {

                //Load courses
                loadCourses(csvPath, courseTable);
            }

            else if (ans == "N" || ans == "n") {

            	cout << "Please try to load file again." << endl;
            }

            else {
            	cout << "Please input either Y or N. Your input was: " << ans << endl;

            }



            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:

        	courseTable->checkElements();
        	courseTable->PrintSorted();
        	break;

        case 3:
            ticks = clock();

        	courseTable->checkElements();

            cout << "Please enter the course you would like to search. Ex. CSCI350 " << endl;
            cin >> courseKey;
            transform(courseKey.begin(),courseKey.end(), courseKey.begin(), ::toupper);

            cout << "Confirm the course please: Y/N\n" << courseKey << endl;
            cin >> ans;

            if (courseTable->checkCourse(courseKey) == true){

            	if (ans == "Y" || ans == "y") {

            		course = courseTable->PrintCourse(courseKey);
            	}

            	else if (ans == "N" || ans == "n") {

            		cout << "Please enter new course to search." << endl;
            	}

            	else {
            		cout << "Please input either Y or N. Your input was: " << ans << endl;

            	}


            	if (!course.courseNumber.empty()) {
            	displayCourse(course);
            	}
            }

           else {
                cout << "Course number " << courseKey << " not found." << endl;
            }

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;


        case 4:

        	courseTable->checkElements();
        	courseTable->PrintAll();
            break;
        }

    }

    cout << "Good bye." << endl;

    return 0;
}
