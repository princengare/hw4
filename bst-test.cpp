#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('b',2));
    
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');


    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');

	AVLTree<int, double> bst;
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(3, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(4, 1.0));

	cout << "\nAVLTree contents:" << endl;
    for(AVLTree<int,double>::iterator it = bst.begin(); it != bst.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bst.find(1) != bst.end()) {
        cout << "Found 1" << endl;
				cout << "Erasing 1" << endl;
				bst.remove(1);
    }
    else {
        cout << "Did not find 1" << endl;
    }

		cout << "\nAVLTree contents:" << endl;
    for(AVLTree<int,double>::iterator it = bst.begin(); it != bst.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }

		/*AVLTree<int, double> bst;
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(3, 1.0));

	cout << "\nAVLTree contents:" << endl;
    for(AVLTree<int,double>::iterator it = bst.begin(); it != bst.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bst.find(2) != bst.end()) {
        cout << "Found 2" << endl;
				cout << "Erasing 2" << endl;
				bst.remove(2);
    }
    else {
        cout << "Did not find 2" << endl;
    }

		cout << "\nAVLTree contents:" << endl;
    for(AVLTree<int,double>::iterator it = bst.begin(); it != bst.end(); ++it) {
        cout << it->first << " " << it->second << endl;
		} */

    return 0;
}
