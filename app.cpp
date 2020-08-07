#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	<iomanip>
#include	<string>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(char *, BST *);
int menu();
void centerText(string);

int main() {
	menu();
	return 0;
}

bool readFile(char* filename, BST* bt) {
	Student s;
	char trash[1000];
	ifstream infile(filename);
	if (infile) {
		while (!infile.eof()) {
			infile >> trash >> trash >> s.id
				>> trash >> trash;
			infile.ignore();
			infile.getline(s.name, 1000);
			infile >> trash >> trash;
			infile.ignore();
			infile.getline(s.address, 1000);
			infile >> trash >> trash >> s.DOB >> trash >> trash >> s.phone_no >> trash >> trash >> s.course >> trash >> trash >> s.cgpa;

			if (bt->checkDuplicate(s.id)) {
				cout << "\nA Duplicate Record Was Found. " << s.id << " is the duplicate record." << endl
					<< "It shall be removed and inserted accordingly." << endl;
				BTNode* t1 = bt->find(bt->root, s.id);
				bt->remove(t1->item);
			}
			
			bt->insert(s);

			if (infile.eof())
				break;
		}
		infile.close();
		return true;
	}
	else
		return false;
}

int menu() {
	BST studentRecords, t1;
	BTNode* temp;
	char filename[] = "student.txt";
	int id, choice, order, source, h, r;

	do{
		cout << "\nMenu" << endl
			<< "\n(1) Read data to BST" << endl
			<< "(2) Print deepest nodes" << endl
			<< "(3) Display student" << endl
			<< "(4) Clone Subtree" << endl
			<< "(5) Print Ancestor" << endl
			<< "(6) Print Spiral" << endl
			<< "(7) Exit" << endl
			<< "\nEnter Your Choice >> ";
		cin >> choice;
		system("cls");
		switch (choice) {
		case 1:
			centerText("READ DATA");
			if (readFile(filename, &studentRecords)) {
				cout << "\n========================================================================================================================"<< endl;
				centerText(to_string(studentRecords.count) + " records have been read successfully.");
				cout << "\n========================================================================================================================";
			}
			else
				cout << "File does not exist!" << endl;

			cin.ignore();
			cin.get();
			system("cls");
			break;
		case 2:
			centerText("DEEPEST NODE");
			if (studentRecords.deepestNode()) {
				cout << "\nSuccessfully Display Output" << endl;
			}
			else
				cout << "\nThe Student Records Binary Tree is currently empty." << endl;

			cin.ignore();
			cin.get();
			system("cls");
			break;
		case 3:
			centerText("DISPLAY");
			do {
				cout << "\nPlease select the order of nodes (1 - Ascending / 2 - Descending): ";
				cin >> order;
				if (order < 1 || order > 2)
					cout << "\nError!! Enter a number either 1 or 2 only!!" << endl;
			} while (order < 1 || order > 2);
			do {
				cout << "\nPlease select where you wish to display the output (1 - Screen / 2 - File): ";
				cin >> source;
				if (source < 1 || source > 2)
					cout << "\nError!! Enter a number either 1 or 2 only!!" << endl;
			} while (source < 1 || source>2);

			if (studentRecords.display(order, source)) {
				if (source == 2)
					cout << "\nSuccessfully Display Output To student-info.txt" << endl;

				cout << "\nSuccessfully Display Output." << endl;
			}
			else
				cout << "\nThe Student Records Binary Tree is currently empty." << endl;

			cin.ignore();
			cin.get();
			system("cls");
			break;
		case 4:
			t1 = BST();
			centerText("CLONE SUBTREE");
			if (studentRecords.empty())
				cout << "\nThe Student Records Binary Tree is currently empty." << endl;
			else {
				h = studentRecords.height(studentRecords.root);
				r = false;
				cout << "\n========================================================================================================================" << endl
					<< "\nAvailable ID: ";
				for (int i = 1; i <= h; i++) {
					studentRecords.printSpiralID(studentRecords.root, i, r);
					r = !r;
				}
				cout << "\n\n========================================================================================================================" << endl;
				do {
					cout << "\nPlease enter the Student ID of the Node you wish to clone: ";
					cin >> id;
					temp = studentRecords.find(studentRecords.root, id);
					if (!temp)
						cout << "\nThe Student ID does not exists. Please try again" << endl;
				} while (temp == NULL);
				if (t1.CloneSubTree(studentRecords, temp->item)) {
					cout << "\n========================================================================================================================" << endl;
					cout << "\nOriginal Tree: " << endl;
					studentRecords.preOrderPrint();
					cout << "========================================================================================================================" << endl;
					cout << "\nCloned Subtree: " << endl;
					t1.preOrderPrint();
					cout << "========================================================================================================================" << endl
						<< "\nSuccessfully Display Output." << endl;
				}
				else
					cout << "\nThe Student Records Binary Tree is currently empty." << endl;
			}
			cin.ignore();
			cin.get();
			system("cls");
			break;
		case 5:
			centerText("PRINT ANCESTOR");
			if (studentRecords.empty())
				cout << "\nThe Student Records Binary Tree is currently empty." << endl;
			else {
				h = studentRecords.height(studentRecords.root);
				r = false;
				cout << "\n========================================================================================================================" << endl
					<< "\nAvailable ID: ";
				for (int i = 1; i <= h; i++) {
					studentRecords.printSpiralID(studentRecords.root, i, r);
					r = !r;
				}
				cout << "\n\n========================================================================================================================" << endl;
				do {
					cout << "\nPlease enter the Student ID of the Node you wish to find ancestor path: ";
					cin >> id;
					temp = studentRecords.find(studentRecords.root, id);
					if (!temp)
						cout << "\nThe Student ID does not exists. Please try again" << endl;
				} while (temp == NULL);
				if (studentRecords.printAncestor(temp->item))
					cout << "\nSuccessfully Display Output." << endl;
				else
					cout << "\nThe Student Records Binary Tree is currently empty." << endl;
			}
			cin.ignore();
			cin.get();
			system("cls");
			break;
		case 6:
			centerText("PRINT SPIRAL");
			if (studentRecords.printSpiral())
				cout << "Successfully Display Output." << endl;
			else
				cout << "\nThe Student Records Binary Tree is currently empty." << endl;
			cin.ignore();
			cin.get();
			system("cls");
			break;
		}
	} while (choice != 7);

	cout << "\n========================================================================================================================" << endl;
	centerText("Thank you for using our program.");
	cout << "\n========================================================================================================================";

	return 0;
}

void centerText(string s) {
	int l = s.length();
	int empty = 60 - (int)(l / 2);
	cout << endl << setw(empty) << " " << s << endl;
}
