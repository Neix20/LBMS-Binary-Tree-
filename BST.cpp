#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

//1.

bool BST::checkDuplicate(int id) {
	if (root == NULL)
		return false;
	return checkDuplicate2(root, id);
}

bool BST::checkDuplicate2(BTNode* temp,int id) {
	if (temp == NULL)
		return false;
	if (temp->item.compare3(id))
		return true;
	bool ltree = checkDuplicate2(temp->left, id);//Check if node exists in left tree
	bool rtree = checkDuplicate2(temp->right, id);//Check if node exists in right tree
	if (ltree || rtree)
		return true;
	return false;
}

BTNode* BST::find(BTNode* temp, int id) {
	if (temp == NULL)
		return NULL;
	if (temp->item.id == id)
		return temp;
	else {//Consider all cases from all paths, otherwise it will return NULL value even if it's true
		BTNode* t1 = find(temp->left, id);
		if (t1 != NULL) return t1;
		t1 = find(temp->right, id);
		if (t1 != NULL)return t1;
	}
	return NULL;
}

//2.

int BST::height(BTNode* temp) {
	if (!temp)
		return 0;
	int lheight = height(temp->left);
	int rheight = height(temp->right);
	if (lheight > rheight)
		return lheight + 1;
	else
		return rheight + 1;
}

bool BST::deepestNode() {
	if (root == NULL)
		return false;
	int numOfStudent(0);
	int h = height(root);
	cout << "\n========================================================================================================================" << endl;
	cout << "\nDeepest nodes: ";
	printStudentId(root, h);
	cout << "\n\n========================================================================================================================" << endl;
	printStudentDetails(root, h, numOfStudent);
	cout << "\n========================================================================================================================" << endl;
	return true;
}

void BST::printStudentDetails(BTNode* temp, int level,int&num) {
	if (temp == NULL)
		return;
	if (level == 1) {
		cout << "\nStudent " << ++num << ": " << endl;
		temp->item.print(cout);
	}
	printStudentDetails(temp->left, level - 1,num);
	printStudentDetails(temp->right, level - 1,num);
}

void BST::printStudentId(BTNode* temp, int level) {
	if (temp == NULL)
		return;
	if (level == 1)
		cout << temp->item.id << " ";
	printStudentId(temp->left, level - 1);
	printStudentId(temp->right, level - 1);
}

//3.

void BST::printAscending(BTNode* temp,int& num,ostream& out) {
	if (temp == NULL)
		return;
	else {
		printAscending(temp->left, num, out);
		out << "\nStudent " << ++num << ": " << endl;
		temp->item.print(out);
		out << endl << "========================================================================================================================" << endl;
		printAscending(temp->right, num, out);
	}
}

void BST::printDescending(BTNode* temp, int& num, ostream& out) {
	if (temp == NULL)
		return;
	else {
		printDescending(temp->right, num, out);
		out << "\nStudent " << ++num << ": " << endl;
		temp->item.print(out);
		out << endl << "========================================================================================================================" << endl;
		printDescending(temp->left, num, out);
	}
}
bool BST::display(int order, int source) {
	if (root == NULL)
		return false;
	int num(0);
	if (order == 1 && source == 1)
		printAscending(root, num, cout);
	else if (order == 2 && source == 1)
		printDescending(root, num, cout);
	else if (source == 2) {
		ofstream outFile("student-info.txt");
		if (order == 1)
			printAscending(root, num, outFile);
		else if (order == 2)
			printDescending(root, num, outFile);
		outFile.close();
	}
	return true;
}

//4.

bool BST::CloneSubTree(BST t1, type item) {
	if (t1.root == NULL)
		return false;
	CloneSubTree2(t1.root, item);
	return true;
}

void BST::CloneSubTree2(BTNode* temp, type item) {
	if (temp == NULL)
		return;
	if (temp->item.compare2(item)) {
		//BTNode* cur;//Use the BFS queue method (as shown above) to insert a new node into the new tree
		//Queue q;
		//q.enqueue(temp);
		//while (!q.empty()) { 	
		//	q.dequeue(cur);
		//	if (cur != NULL) {
		//		insert(cur->item);

		//		if (cur->left != NULL)
		//			q.enqueue(cur->left);

		//		if (cur->right != NULL)
		//			q.enqueue(cur->right);
		//	}
		//}
		CloneSubTree3(temp);
		return;
	}
	CloneSubTree2(temp->left, item);
	CloneSubTree2(temp->right, item);
}

void BST::CloneSubTree3(BTNode* temp) {
	if (temp == NULL)
		return;
	insert(temp->item);
	CloneSubTree3(temp->left);
	CloneSubTree3(temp->right);
}

//5.

bool BST::printAncestor(type item) {
	if (root == NULL)
		return false;
	bool gotRoots = false;
	/*cout << "\nAncestor of the node with Student ID " << item.id << ": ";*/
	if (printAncestor2(root,item, gotRoots))
		if (!gotRoots)
			cout << "There is no ancestor for this item.";
	cout << endl;
	return true;
}

bool BST::printAncestor2(BTNode* temp, type item,bool& gotRoots) {
	if (temp == NULL)
		return false;

	if (temp->item.compare2(item))
		return true;

	if (printAncestor2(temp->left, item,gotRoots) || printAncestor2(temp->right, item,gotRoots)) {
		cout << temp->item.id << " ";
		gotRoots = true;
		return true;
	}

	return false;
}

//6.

bool BST::printSpiral() {
	if (root == NULL)
		return false;
	int h = height(root);
	bool r = false;
	cout << "\n========================================================================================================================" << endl
		<< "\nPrint Spiral ID Order: ";
	for (int i = 1; i <= h; i++) {
		printSpiralID(root, i, r);
		r = !r;
	}
	cout<< "\n\n========================================================================================================================" << endl;
	r = false;
	for (int i = 1; i <= h; i++) {
		printSpiral2(root, i,r);
		r = !r;
	}
	cout << "\n========================================================================================================================" << endl << endl;
	return true;
}

void BST::printSpiral2(BTNode* temp, int level,bool revert) {
	if (temp == NULL)
		return;
	if (level == 1) {
		temp->item.print(cout);
	}
	else 
		if (revert) {
			printSpiral2(temp->left, level - 1, revert);
			printSpiral2(temp->right, level - 1, revert);
		}
		else {
			printSpiral2(temp->right, level - 1, revert);
			printSpiral2(temp->left, level - 1, revert);
		}
}

void BST::printSpiralID(BTNode* temp, int level, bool revert) {
	if (temp == NULL)
		return;
	if (level == 1)
		cout << temp->item.id << " ";
	else
		if (revert) {
			printSpiralID(temp->left, level - 1, revert);
			printSpiralID(temp->right, level - 1, revert);
		}
		else {
			printSpiralID(temp->right, level - 1, revert);
			printSpiralID(temp->left, level - 1, revert);
		}
}

Queue[4]