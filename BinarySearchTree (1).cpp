//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : JYour name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
            Node() {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder(); //Left right root
    void PreOrder(); //Root left right
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
    bool CheckBid(string bidId);
    bool CheckElements(); //Ensure tree is populated
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
	root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node

	while (root != nullptr) {
		Remove(root->bid.bidId); //Recursively call remove function until root is null
	}




}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // FixMe (2): In order root
    // call inOrder function and pass root

	this->inOrder(root);

}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // FixMe (3): Post order root
    // postOrder root

	postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // FixMe (4): Pre order root
    // preOrder root

	preOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (5) Implement inserting a bid into the tree
    // if root equal to null ptr
      // root is equal to new node bid

	if (root == nullptr) { //Nothing in tree. Set root to bid
		root = new Node(bid); //Call constructor
	}

    // else
      // add Node root and bid

	else {
		this->addNode(root, bid); //Call function to add node
	}

}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // FIXME (6) Implement removing a bid from the tree
    // remove node root bidID

	string ans;

	cout << "Confirm bidId to remove: " << bidId << " Y/N " << endl; //User input to confirm bid
	cin >> ans;

	if (ans == "y" || ans == "Y"){
		cout << "Removing " << bidId << " from tree..." << endl;
		this->removeNode(root, bidId);
	}

	else if (ans == "n" || ans == "N") {
		cout << "Please call function again." << endl;
		return;
	}

	else {
		cout << "Please enter Y or N. Your input was " << ans << endl;
		return;
	}


}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // FIXME (7) Implement searching the tree for a bid
    // set current node equal to root

	Node *curNode = root; //Point to root

    // keep looping downwards until bottom reached or matching bidId found
        // if match found, return current bid

	while (curNode != nullptr) {
			if(curNode->bid.bidId.compare(bidId) == 0) {
				cout << bidId << " found in tree" << endl;
				return curNode->bid;
			}

	    // if bid is smaller than current node then traverse left
	    // else larger so traverse right
			else if (curNode->bid.bidId.compare(bidId) > 0) {
				curNode = curNode->left;
			}

			else {
				curNode = curNode->right;
			}

	}

    Bid bid;
    return bid;


}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (8) Implement inserting a bid into the tree


    // if node is larger then add to left
	// if no left node
	            // this node becomes left
	// else recurse down the left node

	if (node != nullptr && node->bid.bidId.compare(bid.bidId)>0) {
		if (node->left == nullptr) {
			node->left = new Node(bid);
			return;
		}
		else {
			this->addNode(node->left, bid);
		}

	}

    // else
        // if no right node
            // this node becomes right

	else if (node != nullptr && node->bid.bidId.compare(bid.bidId)<0) {
		if (node->right == nullptr) {
			node->right = new Node(bid);
			return;
		}

		else {
			this->addNode(node->right, bid);
		}
	}


        //else
            // recurse down the right node
}
void BinarySearchTree::inOrder(Node* node) {
      // FixMe (9): Pre order root
      //if node is not equal to null ptr
      //InOrder not left
      //output bidID, title, amount, fund
      //InOrder right

	if(node != nullptr) { //Confirm node is not null
		inOrder(node->left); //Access left first
		cout << node->bid.bidId << ": " << node->bid.title << " | "
			 << node->bid.amount << " | " << node->bid.fund << endl;	//Print second
		inOrder(node->right); //Access right third
	}



}
void BinarySearchTree::postOrder(Node* node) {
      // FixMe (10): Pre order root
      //if node is not equal to null ptr
      //postOrder left
      //postOrder right
      //output bidID, title, amount, fund

	if (node != nullptr) {
		postOrder(node->left); //Access left first
		postOrder(node->right); //Access right second
		cout << node->bid.bidId << ": " << node->bid.title << " | "
			 << node->bid.amount << " | " << node->bid.fund << endl;	//Print last

	}


}

void BinarySearchTree::preOrder(Node* node) {
      // FixMe (11): Pre order root
      //if node is not equal to null ptr
      //output bidID, title, amount, fund
      //postOrder left
      //postOrder right

	if (node != nullptr) {
			cout << node->bid.bidId << " | " << node->bid.title << " | "
				 << node->bid.amount << " | " << node->bid.fund << endl; //Print first
			preOrder(node->left); //Access left second
			preOrder(node->right);//Access right third


		}
}

Node* BinarySearchTree::removeNode(Node* node, string bidId) {

	string msg = "Bid removed successfully.\n"; //Msg to publish when bid removed

	if (node == nullptr) {
		return node;
	}

	if (bidId.compare(node->bid.bidId) < 0) {
			node->left = removeNode(node->left, bidId); //Recursive call replacing parent node with node->left
		}

	else if (bidId.compare(node->bid.bidId) > 0) { //Recursive call replacing parent node with node->right
			node->right = removeNode(node->right, bidId);
		}

	else { //Match is found in tree
		if (node->left == nullptr && node->right == nullptr) {//No children (leaf node)
			delete node;
			node = nullptr;
			cout << msg;
		}

		else if (node->left != nullptr && node->right == nullptr) { //Single child in left
			Node* temp = node;
			node = node->left; //Replace parent with left child
			delete temp;
			temp = nullptr;
			cout << msg;
		}

		else if (node->right != nullptr && node->left == nullptr) { //Only one child
			Node* temp = node;
			node = node->right; //Replace parent with right child
			delete temp;
			temp = nullptr;
			cout << msg;
				}

		else {  //Both children exist
			Node* temp = node->right;
			while (temp->left != nullptr) { //Look for minimum
				temp = temp->left;
				}
			node->bid = temp->bid;
			node->right = removeNode(node->right,temp->bid.bidId); //Recursive call
		}

	}

	return node;
}

bool BinarySearchTree::CheckBid(string bidId) { //Function to check if bid is in tree. Important for duplicates

	Bid search = Search(bidId);

	string compareBid = search.bidId;

	if (compareBid == bidId) {
		return false;
	}

	else {
		return true;
	}
}

bool BinarySearchTree::CheckElements() { //Function to confirm tree is populated
	if (root == nullptr) {
		cout << "Tree is empty. Please populate before calling function.\n" << endl;
		return false;
	}

	else {
		return true;
	}
}



//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */

double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98269";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98269";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    //Define exception message to populate tree
    string load_bids = "Use the first menu choice to load bids.\n";

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:

        	try {
        		if (bst->CheckElements() == true){
        			bst->InOrder();
        		}
        		else {
        			throw(bidKey);
        			}
        		} catch (const string & bidKey){
            		cout << load_bids << endl;
        		}


            break;

        case 3:

        	try{
        		if(bst->CheckElements() == true) { //Check for elements in tree. If yes, continue
                    ticks = clock();
                    bid = bst->Search(bidKey);
                    try {
                    	if (!bid.bidId.empty()) {
                    		displayBid(bid);
                                	}
                    else {
                    	throw(bidKey);
                    }
            	} catch (const string & bidKey){
            		cout << "Bid Id " << bidKey << " not found in tree. Please try with new bid." << endl;
            		}
        		}
        	else { //No elements in tree throw exception
        		throw(bidKey);
        		}
        	} catch (const string & bidKey) {
        		cout << load_bids << endl;
        		}


            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:

        	try {
        		if(bst->CheckElements() == true) { //Check for elements in tree. If yes, continue
        			try {
        				if (bst->CheckBid(bid.bidId) == false) {
        					bst->Remove(bidKey);
        				}
        				else {
        					throw(bidKey);
        				}
        			} catch (const string & bidKey){
        				cout << "Bid: " << bidKey << " is not found in the tree. Please try a different bid.\n" << endl;
        			}
        		}

        	else { //No elements in tree throw exception
        		throw(bidKey);
        		}
            } catch (const string & bidKey) {
            	cout << load_bids << endl;
            }

            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
