#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
		void rotateLeft (AVLNode<Key, Value> *n);
    void rotateRight (AVLNode<Key, Value> *n);
    void insertFix(AVLNode<Key, Value> *parent, AVLNode<Key, Value>* child);
    AVLNode<Key, Value>* getSuccessor(AVLNode<Key, Value>* node);
    void removeFix(AVLNode<Key, Value> *n, int diff);

    /* A provided helper function to swap 2 nodes location in the tree */

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
	 AVLNode<Key,Value>* new_node = new AVLNode<Key,Value>(new_item.first, new_item.second, nullptr);
    new_node->setBalance(0);   
    new_node->setRight(nullptr);
    new_node->setLeft(nullptr);

    if (this->root_ == nullptr) {
        this->root_ = new_node;
        return;
    }

    AVLNode<Key,Value> *parent = nullptr;
    AVLNode<Key,Value>* next = static_cast<AVLNode<Key,Value>*>(this->root_);

    while (true){
        parent = next;
        if (new_item.first  == parent->getKey()){
            parent->setValue(new_item.second);
						delete new_node;
            return;
        }
        else if (new_item.first < parent->getKey()) {
            if (parent->getLeft() == nullptr) {
                parent->setLeft(new_node);
                new_node->setParent(parent);
                break;
            }
            next = parent->getLeft();
        } 
        else {
            if (parent->getRight() == nullptr) {
                parent->setRight(new_node);
                new_node->setParent(parent);
                break;
            }
            next = parent->getRight();
        }
    }

    if (parent->getBalance() == -1 || parent->getBalance() == 1) {
        parent->setBalance(0);
        return;
    }
    else {
        if (parent->getLeft() == new_node){
            parent->setBalance(-1);
        }
        else {
            parent->setBalance(1);
        }
        insertFix(parent, new_node);
    }
    // TODO
}
template<typename Key, typename Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value> *parent, AVLNode<Key, Value>* child)
 {
    // parent and grandparent should not be nullptr
    if (parent == nullptr || parent->getParent() == nullptr) {
        return;
    }

    AVLNode<Key, Value> *grandparent = parent->getParent();

    if (parent == grandparent->getLeft()) { // left child of grandparent
        grandparent->setBalance(grandparent->getBalance() - 1);

        if (grandparent->getBalance() == 0) {
            return; //already balanced
        }

        if (grandparent->getBalance() == -1) {
            insertFix(grandparent, parent);
            return;
        }

        // grandparent balance is -2
        if (child == parent->getLeft()) {
            rotateRight(grandparent);
            parent->setBalance(0);
            grandparent->setBalance(0);

        } 
        else {
            rotateLeft(parent);
            rotateRight(grandparent);

            if (child->getBalance() == -1) {
                parent->setBalance(0);
                grandparent->setBalance(1);

            } else if (child->getBalance() == 0) {
                parent->setBalance(0);
                grandparent->setBalance(0);

            } else {
                parent->setBalance(-1);
                grandparent->setBalance(0);
            }
            child->setBalance(0);
        }

    } 
    else { // right child of grandparent
        grandparent->setBalance(grandparent->getBalance() + 1);

        if (grandparent->getBalance() == 0) {
            return; // nothing to do, it is already balanced
        }

        if (grandparent->getBalance() == 1) {
            insertFix(grandparent, parent);
            return;
        }

        // grandparent balance is 2
        if (child == parent->getRight()) { // zig-zig - only 1 rotation
            rotateLeft(grandparent);
            parent->setBalance(0);
            grandparent->setBalance(0);

        } 
        else { // zig-zag - 2 rotations
            rotateRight(parent);
            rotateLeft(grandparent);

            if (child->getBalance() == 1) {
                parent->setBalance(0);
                grandparent->setBalance(-1);
            } 
            else if (child->getBalance() == 0) {
                parent->setBalance(0);
                grandparent->setBalance(0);

            } 
            else {
                parent->setBalance(1);
                grandparent->setBalance(0);
            }
            child->setBalance(0);
        }
    }
}
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::getSuccessor(AVLNode<Key, Value>* node) 
{
    if (node->getRight() != nullptr) {
        node = node->getRight();
        while (node->getLeft() != nullptr) {
            node = node->getLeft();
        }
        return node;
    }
    else{
        AVLNode<Key, Value>* parent = node->getParent();
        while(parent != nullptr && node == parent->getRight()){
            node = parent;
            parent = parent->getParent();
        }
        return parent;
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    AVLNode<Key, Value>* node = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));
    if (node == nullptr) {
        return;  // the value is not in the BST
    }
    if (node->getLeft() != nullptr && node->getRight() != nullptr) {
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::predecessor(node));
        nodeSwap(node, pred);
    }
    AVLNode<Key, Value> *child = nullptr;
    if (node->getRight() != nullptr) {
        child = node->getRight();
    } else if (node->getLeft() != nullptr) {
        child = node->getLeft();
    }
    AVLNode<Key, Value>* parent = node->getParent();
    if (child != nullptr) {
        child->setParent(parent);
    }
    int diff = 0;
    if (parent == nullptr) {
        this->root_ = child;
    } else {
        if (node == parent->getLeft()) {
            parent->setLeft(child);
            diff = 1;
        } else {
            parent->setRight(child);
            diff = -1;
        }
    }
    delete node;
    removeFix(parent, diff);
    // TODO
}
template<typename Key, typename Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n, int diff)
{
    if (n == nullptr){
        return;
    }

    AVLNode<Key, Value>* p = n->getParent();
    AVLNode<Key, Value>* c;

    int ndiff = -1;
    if (p != nullptr && n==p->getLeft()){
        ndiff = 1;
    }
    //negative
    if (n->getBalance() + diff == -2){
        //zig zig
        c = n->getLeft();
        if (c->getBalance() <= 0){
            rotateRight(n);
            if(c->getBalance() == -1){
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p,ndiff);
            }
            else if(c->getBalance() == 0){
                n->setBalance(-1);
                c->setBalance(1);
                return;
            }
        }
        else{
            AVLNode<Key, Value>* g = c->getRight();
            rotateLeft(c);
            rotateRight(n);
            if (g->getBalance() == 1){
                n->setBalance(0);
                c->setBalance(-1);
                g->setBalance(0);
            }
            else if(g->getBalance() == 0){
                n->setBalance(0);
                c->setBalance(0);
                g->setBalance(0);
            }
            else if (g->getBalance() == -1){
                n->setBalance(1);
                c->setBalance(0);
                g->setBalance(0);
            }
            removeFix(p,ndiff);
        }
    }
    // else if (n->getBalance() + diff == -1){
    //     //n->setBalance(-1);
		// 		n->updateBalance(-1);
		// 		return;
    // }
    // else if (n->getBalance() + diff == 0){
    //     n->setBalance(0);
    //     removeFix(p,ndiff);
    // }
    //positive
    else if (n->getBalance() + diff == 2){
        //zig zig
        c = n->getRight();
        if (c->getBalance() >= 0){
            rotateLeft(n);
            if(c->getBalance() == 1){
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p,ndiff);
            }
            else if(c->getBalance() == 0){
                n->setBalance(1);
                c->setBalance(-1);
                return;
            }
        }
        else{//zig zag
            AVLNode<Key, Value>* g = c->getLeft();
            rotateRight(c);
            rotateLeft(n);            
            if (g->getBalance() == -1){
                //n->setBalance(-1);
                //c->setBalance(0);
								n->setBalance(0);
								c->setBalance(1);
                g->setBalance(0);
            }
            else if(g->getBalance() == 0){
                n->setBalance(0);
                c->setBalance(0);
                g->setBalance(0);
            }
            else if (g->getBalance() == 1){
                n->setBalance(-1);
                c->setBalance(0);
                g->setBalance(0);
            }
            removeFix(p,ndiff);
        }
    }
		else {
			if (n->getBalance() == 0){
        //n->setBalance(1);
				n->updateBalance(diff);
        return;
			}
			else if (n->getBalance() + diff == 0) {
					n->setBalance(0);
					removeFix(p, ndiff);
			}

		}
    // else if (n->getBalance() == 0){
    //     //n->setBalance(1);
		// 		n->updateBalance(1);
    //     return;
    // }
    // else if (n->getBalance() + diff == 0) {
    //     n->setBalance(0);
		// 		removeFix(p, ndiff);
		// }


}
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeft (AVLNode<Key, Value> *n)
{
    AVLNode<Key, Value>* y = n->getRight();
    AVLNode<Key, Value>* rootParent = n->getParent();
    y->setParent(rootParent);

    // set the root parent
    if (n->getParent() == nullptr) {        
        this->root_ = y;
    }
    else if (rootParent->getLeft() == n){
        rootParent->setLeft(y);
    }
    else{
        rootParent->setRight(y);
    }    

    // pointer shifts
    AVLNode<Key, Value>* c = y->getLeft();

    n->setRight(c);
    if (c != nullptr){
        c->setParent(n);
    }

    y->setLeft(n);
    n->setParent(y);
    
}
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateRight (AVLNode<Key, Value> *n)
{
    AVLNode<Key, Value>* y = n->getLeft();
    AVLNode<Key, Value>* rootParent = n->getParent();

    y->setParent(rootParent);
    // set the root parent
    if (n->getParent() == nullptr) {        
        this->root_ = y;
    }
    else if (rootParent->getLeft() == n){
        rootParent->setLeft(y);
    }
    else{
        rootParent->setRight(y);
    }    

    AVLNode<Key, Value>* c = y->getRight();

    n->setLeft(c);
    if (c != nullptr){
        c->setParent(n);
    }

    y->setRight(n);
    n->setParent(y);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
