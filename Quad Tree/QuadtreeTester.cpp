#include <iostream>
#include "Quadtree_tester.h"
#include "Quadtree.h"
#include <algorithm>
#include <string>
using namespace std;

class NodeXY;
class NodeXYSeg;
class NodeXYChain;
class NodeStack;
class NodeStackSegs;

class NodeXY{
private:
	int xVal, yVal;
public:
	NodeXY(int x, int y);
	~NodeXY();
	int x();
	int y();
	static bool equals(NodeXY node, int x, int y);
};

class NodeXYSeg{
private:
	NodeXY *value;
public:
	NodeXYSeg *next;
	NodeXYSeg(int x, int y);
	NodeXY *getValue() const;
};

class NodeXYChain{
private:
	NodeXYSeg *head;
	int count;
public:
	NodeXY getHead() const;
	void add(int x, int y);
	bool exists(int x, int y);
};

class NodeStack{
private:
	NodeStackSegs *top;
	NodeStackSegs *bottom;
public:
	int capacity;
	NodeStack();
	void push(Quadtree_node<int> *toPush, string dir);
	Quadtree_node<int> *pop();
	void summary();
};

class NodeStackSegs{
public:
	Quadtree_node<int> *node;
	int level;
	string direction;
	NodeStackSegs *below;
	NodeStackSegs(Quadtree_node<int> *toInsert, int lvl, string dir);
};

void test();
void debug();
void treeTraverse(Quadtree_node<int> *node, int level);
void updateValue(int x, int y);
void traverse(Quadtree<int> *tree);

int main() {
	cout << "Welcome to the Quadtree tester and debugger" << endl;
	cout << "This program currently does not test memory usage and deletes" << endl;
	cout << "The following commands are: test, debug, and exit. Type in the command to start" << endl;
	string option = "";
	bool exit = false;
	while (!exit){
		cin >> option;
		if (option == "test")
			test();
		else if (option == "debug")
			debug();
		else if (option == "exit")
			exit = true;
		else
			cout << "Please insert a valid command: test, debug, or exit" << endl;
	}
	return 0;
}

void test(){
	cout << "Conducting standard tree of type int test" << endl;
	Quadtree<int> *tree = new Quadtree<int>();
	cout << "testing initial conditions of the tree" << endl;
	try{
		if (!(tree->empty()))
			cout << "initial non-empty tree detected, check empty() method" << endl;
		if (!(tree->size() == 0))
			cout << "initial tree size not 0 detected, check size() method" << endl;
		if (!(tree->root() == 0))
			cout << "tree root is not empty, check root() or constructor method" << endl;
	}
	catch(...){
		cout << "error in initial checking of empty(), size() and root(), returning" << endl;
		return;
	}
	tree->insert(5, 5);
	tree->insert(4, 4);
	tree->insert(4, 6);
	tree->insert(6, 4);
	tree->insert(6, 6);
	tree->insert(1, 2);
	tree->insert(8, 2);
	tree->insert(2, 7);
	tree->insert(6, 3);
	tree->insert(9, 7);
	int xsum = 51;
	int ysum = 46;
	int maxx = 9;
	int maxy = 7;
	int minx = 1;
	int miny = 2;

	cout << "now testing sum, min, and max values" << endl;
	if (!(tree->sum_x() == xsum))
		cout << "unmatched x sum value between fetched and expected" << endl << "Fetched is " << tree->sum_x() << ", expected is " << xsum << endl;
	if (!(tree->sum_y() == ysum))
		cout << "unmatched y sum value between fetched and expected" << endl << "Fetched is " << tree->sum_y() << ", expected is " << ysum << endl;
	if (!(tree->max_x() == maxx))
		cout << "unmatched x max value between fetched and expected" << endl << "Fetched is " << tree->max_x() << ", expected is " << maxx << endl;
	if (!(tree->max_y() == maxy))
		cout << "unmatched y max value between fetched and expected" << endl << "Fetched is " << tree->max_y() << ", expected is " << maxy << endl;
	if (!(tree->min_x() == minx))
		cout << "unmatched x min value between fetched and expected" << endl << "Fetched is " << tree->min_x() << ", expected is " << minx << endl;
	if (!(tree->min_y() == miny))
		cout << "unmatched y min value between fetched and expected" << endl << "Fetched is " << tree->min_y() << ", expected is " << miny << endl;

	cout << "now testing size of tree" << endl;
	int size = 10;
	if (!(tree->size() == size))
		cout << "unmatched tree size value between fetched and expected, fetched is " << tree->size() << ", expected is " << size << endl;

	cout << "checking random tree members" << endl;
	if (!(tree->member(6, 4)))
		cout << "inserted member not found in tree" << endl;
	if (!(tree->member(9, 7)))
		cout << "inserted member not found in tree" << endl;
	if (tree->member(1, 1))
		cout << "non-inserted member found in tree" << endl;

	cout << "inserting more members into tree, rechecking new integrity" << endl;
	tree->insert(10, 3);
	tree->insert(1, 9);
	tree->insert(0, 1);
	tree->insert(4, 7);
	tree->insert(1, 15);

	xsum += 16;
	ysum += 35;
	maxx = 10;
	maxy = 15;
	minx = 0;
	miny = 1;

	cout << "now re-testing sum, min, and max values" << endl;
	if (!(tree->sum_x() == xsum))
		cout << "unmatched x sum value between fetched and expected" << endl << "Fetched is " << tree->sum_x() << ", expected is " << xsum << endl;
	if (!(tree->sum_y() == ysum))
		cout << "unmatched y sum value between fetched and expected" << endl << "Fetched is " << tree->sum_y() << ", expected is " << ysum << endl;
	if (!(tree->max_x() == maxx))
		cout << "unmatched x max value between fetched and expected" << endl << "Fetched is " << tree->max_x() << ", expected is " << maxx << endl;
	if (!(tree->max_y() == maxy))
		cout << "unmatched y max value between fetched and expected" << endl << "Fetched is " << tree->max_y() << ", expected is " << maxy << endl;
	if (!(tree->min_x() == minx))
		cout << "unmatched x min value between fetched and expected" << endl << "Fetched is " << tree->min_x() << ", expected is " << minx << endl;
	if (!(tree->min_y() == miny))
		cout << "unmatched y min value between fetched and expected" << endl << "Fetched is " << tree->min_y() << ", expected is " << miny << endl;

	cout << "now re-testing size of tree" << endl;
	size += 5;
	if (!(tree->size() == size))
		cout << "unmatched tree size value between fetched and expected, fetched is " << tree->size() << ", expected is " << size << endl;

	cout << "checking inserting duplicates" << endl;
	tree->insert(5, 5);
	tree->insert(0, 1);
	if (!(tree->size() == size))
		cout << "tree inserted duplicate values or size is incorrect, fetched is " << tree->size() << ", expected is " << size << endl;

	cout << "now traversing the tree to check value integrity" << endl;
	treeTraverse(tree->root(), 0);
	cout << "tree traversal completed" << endl;

	cout << "now clearing the tree" << endl;
	tree->clear();

	cout << "checking functions done to a clear tree" << endl;
	if (!(tree->size() == 0) || !(tree->empty()) || (tree->root() != 0))
		cout << "Tree size is not 0, fetched is " << tree->size() << endl;

	try{
		tree->min_x();
	}
	catch (underflow){
	
	}
	catch (...){
		cout << "invalid exception caught, expecting underflow with min_x()" << endl;
	}
	try{
		tree->min_y();
	}
	catch (underflow){

	}
	catch (...){
		cout << "invalid exception caught, expecting underflow with min_y()" << endl;
	}
	try{
		tree->max_x();
	}
	catch (underflow){

	}
	catch (...){
		cout << "invalid exception caught, expecting underflow with max_x()" << endl;
	}
	try{
		tree->max_y();
	}
	catch (underflow){

	}
	catch (...){
		cout << "invalid exception caught, expecting underflow with max_y()" << endl;
	}
	try{
		tree->sum_x();
	}
	catch (underflow){
		cout << "underflow caught, if it is an empty tree, please return 0" << endl;
	}
	catch (...){
		cout << "invalid exception caught, expecting underflow with sum_x()" << endl;
	}
	try{
		tree->sum_y();
	}
	catch (underflow){
		cout << "underflow caught, if it is an empty tree, please return 0" << endl;
	}
	catch (...){
		cout << "invalid exception caught, expecting underflow with sum_y()" << endl;
	}

	xsum = 0;
	ysum = 0;
	maxx = 0;
	maxy = 0;
	minx = 0;
	miny = 0;
	size = 0;

	cout << "conducting stress test with many values" << endl;
	for (int i = 0; i < 10000; i++){
		int x = rand() % 10000 - 5000;
		int y = rand() % 10000 - 5000;
		if (!(tree->member(x, y))){
			tree->insert(x, y);
			if (x > maxx)
				maxx = x;
			if (x < minx)
				minx = x;
			if (y > maxy)
				maxy = y;
			if (y < miny)
				miny = y;
			//updates the sums and count
			xsum += x;
			ysum += y;
			size++;
		}
	}

	cout << "now re-testing sum, min, and max values" << endl;
	if (!(tree->sum_x() == xsum))
		cout << "unmatched x sum value between fetched and expected" << endl << "Fetched is " << tree->sum_x() << ", expected is " << xsum << endl;
	if (!(tree->sum_y() == ysum))
		cout << "unmatched y sum value between fetched and expected" << endl << "Fetched is " << tree->sum_y() << ", expected is " << ysum << endl;
	if (!(tree->max_x() == maxx))
		cout << "unmatched x max value between fetched and expected" << endl << "Fetched is " << tree->max_x() << ", expected is " << maxx << endl;
	if (!(tree->max_y() == maxy))
		cout << "unmatched y max value between fetched and expected" << endl << "Fetched is " << tree->max_y() << ", expected is " << maxy << endl;
	if (!(tree->min_x() == minx))
		cout << "unmatched x min value between fetched and expected" << endl << "Fetched is " << tree->min_x() << ", expected is " << minx << endl;
	if (!(tree->min_y() == miny))
		cout << "unmatched y min value between fetched and expected" << endl << "Fetched is " << tree->min_y() << ", expected is " << miny << endl;

	cout << "now re-testing size of tree" << endl;
	if (!(tree->size() == size))
		cout << "unmatched tree size value between fetched and expected, fetched is " << tree->size() << ", expected is " << size << endl;

	cout << "now traversing the tree to check value integrity" << endl;
	treeTraverse(tree->root(), 0);
	cout << "tree traversal completed" << endl;



	cout << "complete testing suite complete, now returning" << endl;

	delete tree;

}

static int maxx = NULL, minx = NULL, maxy = NULL, miny = NULL, sumx = 0, sumy = 0, size = 0;
void debug(){
	cout << "welcome to the debug options" << endl;
	cout << "options are: insert, insertDemo, member, max_x, min_x, max_y, min_y, sum_x, sum_y, size, empty, clear" << endl;
	cout << "other options are: options, traverse, check, exit" << endl;
	cout << "creating a new tree of type int" << endl;
	Quadtree<int> *tree = new Quadtree<int>();
	NodeXYChain *members = new NodeXYChain();
	string choice = "";
	bool demoAcc = false;
	bool exit = false;
	while (!exit){
		cout << "Please type an option, or type 'options' to see available options" << endl;
		cin >> choice;
		if (choice == "insert"){
			cout << "please insert the x and y values you would like to insert" << endl;
			int x, y;
			cin >> x;
			cin >> y;
			tree->insert(x, y);
			updateValue(x, y);
			members->add(x, y);
		}
		else if (choice == "insertDemo"){
			if (!demoAcc){
				tree->insert(5, 5);
				updateValue(5, 5);
				members->add(5, 5);
				tree->insert(4, 4);
				updateValue(4, 4);
				members->add(4, 4);
				tree->insert(4, 6);
				updateValue(4, 6);
				members->add(4, 6);
				tree->insert(6, 4);
				updateValue(6, 4);
				members->add(6, 4);
				tree->insert(6, 6);
				updateValue(6, 6);
				members->add(6, 6);
				tree->insert(1, 2);
				updateValue(1, 2);
				members->add(1, 2);
				tree->insert(8, 2);
				updateValue(8, 2);
				members->add(8, 2);
				tree->insert(2, 7);
				updateValue(2, 7);
				members->add(2, 7);
				tree->insert(6, 3);
				updateValue(6, 3);
				members->add(6, 3);
				tree->insert(9, 7);
				updateValue(9, 7);
				members->add(9, 7);
				tree->insert(10, 3);
				updateValue(10, 3);
				members->add(10, 3);
				tree->insert(1, 9);
				updateValue(1, 9);
				members->add(1, 9);
				tree->insert(0, 1);
				updateValue(0, 1);
				members->add(0, 1);
				tree->insert(4, 7);
				updateValue(4, 7);
				members->add(4, 7);
				tree->insert(1, 15);
				updateValue(1, 15);
				members->add(1, 15);
				tree->insert(-5, 12);
				updateValue(-5, 12);
				members->add(-5, 12);
				tree->insert(5, -8);
				updateValue(5, -8);
				members->add(5, -8);
				tree->insert(0, 0);
				updateValue(0, 0);
				members->add(0, 0);
				tree->insert(8, -2);
				updateValue(8, -2);
				members->add(8, -2);
				tree->insert(7, 13);
				updateValue(7, 13);
				members->add(7, 13);
				demoAcc = true;
			}
			else
				cout << "You had already used the demo values, please clear to use again" << endl;
		}
		else if (choice == "member"){
			cout << "please insert the x and y values you would like to insert" << endl;
			int x, y;
			cin >> x;
			cin >> y;
			if (tree->member(x, y)){
				cout << "values inserted is a member" << endl;
				if (!(members->exists(x, y)))
					cout << "the values are not expected to exist in the tree";
			}
			else{
				cout << "values inserted is not a member" << endl;
				if (members->exists(x, y))
					cout << "the values are expected to exist in the tree";
			}
		}
		else if (choice == "max_x"){
			try{
				int val = tree->max_x();
				cout << "max value retrieved is " << val << endl;
				if (val != maxx)
					cout << "Expected max x value from tracking is " << maxx << endl;
			}
			catch (underflow){
				if (tree->size() == 0 && tree->empty()){
					cout << "empty tree found" << endl;
				}
				else
					cout << "size() and clear() property is not 0 and true respectively for empty tree" << endl;
			}
			catch (...){
				cout << "another type of exception caught" << endl;
			}
		}
		else if (choice == "min_x"){
			try{
				int val = tree->min_x();
				cout << "min value retrieved is " << val << endl;
				if (val != minx)
					cout << "Expected min x value from tracking is " << minx << endl;
			}
			catch (underflow){
				if (tree->size() == 0 && tree->empty()){
					cout << "empty tree found" << endl;
				}
				else
					cout << "size() and clear() property is not 0 and true respectively for empty tree" << endl;
			}
			catch (...){
				cout << "another type of exception caught" << endl;
			}
		}
		else if (choice == "max_y"){
			try{
				int val = tree->max_y();
				cout << "max value retrieved is " << val << endl;
				if (val != maxy)
					cout << "Expected max y value from tracking is " << maxy << endl;
			}
			catch (underflow){
				if (tree->size() == 0 && tree->empty()){
					cout << "empty tree found" << endl;
				}
				else
					cout << "size() and clear() property is not 0 and true respectively for empty tree" << endl;
			}
			catch (...){
				cout << "another type of exception caught" << endl;
			}
		}
		else if (choice == "min_y"){
			try{
				int val = tree->min_y();
				cout << "min value retrieved is " << val << endl;
				if (val != miny)
					cout << "Expected min y value from tracking is " << miny << endl;
			}
			catch (underflow){
				if (tree->size() == 0 && tree->empty()){
					cout << "empty tree found" << endl;
				}
				else
					cout << "size() and clear() property is not 0 and true respectively for empty tree" << endl;
			}
			catch (...){
				cout << "another type of exception caught" << endl;
			}
		}
		else if (choice == "sum_x"){
			try{
				int val = tree->sum_x();
				cout << "x sum retrieved is " << val << endl;
				if (val != sumx)
					cout << "Expected x sum value from tracking is " << sumx << endl;
			}
			catch (underflow){
				cout << "underflow caught, if it is an empty tree, please return 0" << endl;
				if (tree->size() == 0 && tree->empty()){
					cout << "empty tree found" << endl;
				}
				else
					cout << "size() and clear() property is not 0 and true respectively for empty tree" << endl;
			}
			catch (...){
				cout << "another type of exception caught" << endl;
			}
		}
		else if (choice == "sum_y"){
			try{
				int val = tree->sum_y();
				cout << "y sum retrieved is " << val << endl;
				if (val != sumy)
					cout << "Expected y sum value from tracking is " << sumy << endl;
			}
			catch (underflow){
				cout << "underflow caught, if it is an empty tree, please return 0" << endl;
				if (tree->size() == 0 && tree->empty()){
					cout << "empty tree found" << endl;
				}
				else
					cout << "size() and clear() property is not 0 and true respectively for empty tree" << endl;
			}
			catch (...){
				cout << "another type of exception caught" << endl;
			}
		}
		else if (choice == "size"){
			int val = tree->size();
			cout << "tree size is " << val << endl;
			if (val != size)
				cout << "Expected tree size from tracking is " << size << endl;
		}
		else if (choice == "empty"){
			if (tree->empty()){
				cout << "The tree is empty" << endl;
				if (size != 0){
					cout << "Tree is not expected to be empty as size is currently " << size << " by tracking" << endl;
				}
			}
			else
				cout << "The tree is not empty" << endl;
		}
		else if (choice == "clear"){
			cout << "resetting the tree" << endl;
			tree->clear();
			sumx = 0;
			sumy = 0;
			size = 0;
			maxx = NULL;
			maxy = NULL;
			minx = NULL;
			miny = NULL;
			demoAcc = false;
			if (tree->size() != 0 || !(tree->empty()))
				cout << "Size of Tree is not 0 or the tree is not clear by the clear() method" << endl;
			if (tree->root() != 0)
				cout << "The root is not cleared yet" << endl;
		}
		else if (choice == "options"){
			cout << "options are: insert, insert demo, member, max_x, min_x, max_y, min_y, sum_x, sum_y, size, empty, clear" << endl;
			cout << "other options are: options, traverse, check, exit" << endl;
		}
		else if (choice == "traverse"){
			traverse(tree);
		}
		else if (choice == "check"){
			treeTraverse(tree->root(), 0);
			cout << "checking sequence done, any detected errors will be printed above this line" << endl;
		}
		else if (choice == "exit"){
			exit = true;
			cout << "exiting debug menu, deleting any created trees" << endl;
			delete tree;
			sumx = 0;
			sumy = 0;
			size = 0;
			maxx = NULL;
			maxy = NULL;
			minx = NULL;
			miny = NULL;
		}
		else{
			cout << "please pick an option below" << endl;
			cout << "options are: insert, insert demo, member, max_x, min_x, max_y, min_y, sum_x, sum_y, size, empty, clear" << endl;
			cout << "other options are: options, traverse, check, exit" << endl;
		}
	}

}

void traverse(Quadtree<int> *tree){
	cout << "Welcome to the tree traversal tool" << endl;
	cout << "Here, you can traverse the tree" << endl;
	Quadtree_node<int> *currentNode;
	NodeStack currentStack;
	currentNode = tree->root();
	cout << "The commands are: goInto, peek, goBack, summary, and exit" << endl;
	bool exit = false;
	while (!(exit)){
		cout << "current node is at " << currentNode->retrieve_x() << " " << currentNode->retrieve_y() << endl;
		string input = "";
		cin >> input;
		if (input == "goInto"){
			cout << "Please select the direction to go into" << endl;
			string direction = "";
			cin >> direction;
			if (direction == "ne"){
				if (currentNode->ne() == NULL)
					cout << "The ne direction is null" << endl;
				else{
					currentStack.push(currentNode, "ne");
					currentNode = currentNode->ne();
				}
			}
			else if (direction == "se"){
				if (currentNode->se() == NULL)
					cout << "The se direction is null" << endl;
				else{
					currentStack.push(currentNode, "se");
					currentNode = currentNode->se();
				}
			}
			else if (direction == "sw"){
				if (currentNode->sw() == NULL)
					cout << "The sw direction is null" << endl;
				else{
					currentStack.push(currentNode, "sw");
					currentNode = currentNode->sw();
				}
			}
			else if (direction == "nw"){
				if (currentNode->nw() == NULL)
					cout << "The nw direction is null" << endl;
				else{
					currentStack.push(currentNode, "nw");
					currentNode = currentNode->nw();
				}
			}
			else{
				cout << "invalid direction" << endl;
			}

		}
		else if (input == "peek"){
			if (currentNode->ne() == NULL)
				cout << "at ne, the node is null" << endl;
			else
				cout << "at ne, the node has value of " << currentNode->ne()->retrieve_x() << " " << currentNode->ne()->retrieve_y() << endl;
			if (currentNode->se() == NULL)
				cout << "at se, the node is null" << endl;
			else
				cout << "at se, the node has value of " << currentNode->se()->retrieve_x() << " " << currentNode->se()->retrieve_y() << endl;
			if (currentNode->sw() == NULL)
				cout << "at sw, the node is null" << endl;
			else
				cout << "at sw, the node has value of " << currentNode->sw()->retrieve_x() << " " << currentNode->sw()->retrieve_y() << endl;
			if (currentNode->nw() == NULL)
				cout << "at nw, the node is null" << endl;
			else
				cout << "at nw, the node has value of " << currentNode->nw()->retrieve_x() << " " << currentNode->nw()->retrieve_y() << endl;
		}
		else if (input == "goBack"){
			currentNode = currentStack.pop();
		}
		else if (input == "summary"){
			cout << "printing out traversal summary" << endl;
			currentStack.summary();
		}
		else if (input == "exit"){
			exit = true;
			cout << "exiting tree travsersal" << endl;
		}
		else{
			cout << "invalid command, please type goInto, peek, goBack, summary, or exit" << endl;
		}
	}
}

void updateValue(int x, int y){
	//initial update
	if (maxx == NULL)
		maxx = x;
	if (maxy == NULL)
		maxy = y;
	if (minx == NULL)
		minx = x;
	if (miny == NULL)
		miny = y;
	//updates the min and max
	if (x > maxx)
		maxx = x;
	if (x < minx)
		minx = x;
	if (y > maxy)
		maxy = y;
	if (y < miny)
		miny = y;
	//updates the sums and count
	sumx += x;
	sumy += y;
	size++;
}

void treeTraverse(Quadtree_node<int> *node, int level){
	if (node == 0)
		return;
	int nodex = node->retrieve_x();
	int nodey = node->retrieve_y();
	int quadx, quady;
	if (node->ne() != 0){
		quadx = node->ne()->retrieve_x();
		quady = node->ne()->retrieve_y();
		if (!(quadx >= nodex && quady >= nodey))
			cout << "at level " << level << " with node " << nodex << " " << nodey << ", an invalid value found at ne() with " << quadx << " " << quady << endl;
		treeTraverse(node->ne(), level+1);
	}
	if (node->se() != 0){
		quadx = node->se()->retrieve_x();
		quady = node->se()->retrieve_y();
		if (!(quadx >= nodex && quady < nodey))
			cout << "at level " << level << " with node " << nodex << " " << nodey << ", an invalid value found at se() with " << quadx << " " << quady << endl;
		treeTraverse(node->se(), level+1);
	}
	if (node->sw() != 0){
		quadx = node->sw()->retrieve_x();
		quady = node->sw()->retrieve_y();
		if (!(quadx < nodex && quady < nodey))
			cout << "at level " << level << " with node " << nodex << " " << nodey << ", an invalid value found at sw() with " << quadx << " " << quady << endl;
		treeTraverse(node->sw(), level+1);
	}
	if (node->nw() != 0){
		quadx = node->nw()->retrieve_x();
		quady = node->nw()->retrieve_y();
		if (!(quadx < nodex && quady >= nodey))
			cout << "at level " << level << " with node " << nodex << " " << nodey << ", an invalid value found at nw() with " << quadx << " " << quady << endl;
		treeTraverse(node->nw(), level+1);
	}
}

NodeXY::NodeXY(int x, int y){
	xVal = x;
	yVal = y;
}

NodeXY::~NodeXY(){}

int NodeXY::x(){
	return xVal;
}

int NodeXY::y(){
	return yVal;
}

bool NodeXY::equals(NodeXY node, int x, int y){
	if (node.x() == x && node.y() == y)
		return true;
	else
		return false;
}

NodeXY NodeXYChain::getHead() const{
	return *head->getValue();
}

void NodeXYChain::add(int x, int y){
	NodeXYSeg *newSeg = new NodeXYSeg(x, y);
	//pretty much the initialization of a new linked list
	if (head == NULL){
		head = newSeg;
		return;
	}
	newSeg->next = head;
	head = newSeg;
}

bool NodeXYChain::exists(int x, int y){
	//start at the head, traverse, but if head is null, give nothign
	if (head == NULL)
		return false;
	NodeXYSeg *sniffer = head;
	while (sniffer != NULL){
		if (NodeXY::equals(*sniffer->getValue(), x, y))
			return true;
		sniffer = sniffer->next;
	}
	return false;
}

NodeXYSeg::NodeXYSeg(int x, int y){
	value = new NodeXY(x, y);
	next = NULL;
}

NodeXY *NodeXYSeg::getValue() const{
	return value;
}

NodeStack::NodeStack(){
	top = NULL;
	bottom = NULL;
	capacity = 0;
}

void NodeStack::push(Quadtree_node<int> *toPush, string dir){
	NodeStackSegs *newSeg = new NodeStackSegs(toPush, capacity, dir);
	//signifies new stack
	if (top == NULL || bottom == NULL){
		top = newSeg;
		bottom = newSeg;
		return;
	}
	newSeg->below = top;
	top = newSeg;
	capacity++;
}

Quadtree_node<int> *NodeStack::pop(){
	NodeStackSegs *toReturn = top;
	top = top->below;
	capacity--;
	return toReturn->node;
}

void NodeStack::summary(){
	NodeStackSegs *sniffer = top;
	cout << "Traversing through the traveled path stack" << endl;
	while (sniffer != NULL){
		cout << "at level " << sniffer->level << ", node values " << sniffer->node->retrieve_x() << ", " << sniffer->node->retrieve_y() << ", next direction is " << sniffer->direction << endl;
		sniffer = sniffer->below;
	}
}

NodeStackSegs::NodeStackSegs(Quadtree_node<int> *toInsert, int lvl, string dir){
	node = toInsert;
	level = lvl;
	direction = dir;
}