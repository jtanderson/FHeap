#include "FNode.h"

// #define DEBUG

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

FNode::FNode(){
	right = this;
	left = this;
	parent = NULL;
	children = NULL;
	marked = false;
	degree = 0;
}

FNode::FNode(int v){
	value = v;
	right = this;
	left = this;
	parent = NULL;
	children = NULL;
	marked = false;
	degree = 0;
}

FNode::FNode(FNode * f){
	if ( f == NULL ){
		throw "ERROR: tried to operate on a NULL node pointer.";
	}
	
	value = f->getValue();
	left = this;
	right = this;
	marked = f->isMarked();
	parent = NULL;
	degree = 0;
	if ( f->children != NULL ){
		FNode * current = f->children;
		do {
			addChild(current);
			current = current->right;
		} while ( current != f->children );
	} else {
		children = NULL;
	}
}

FNode::~FNode(){
	// @TODO: make this better nobody likes a leaky heap
	FNode * tmp = children;
	FNode * tmp2;
	while ( tmp ){
		tmp2 = tmp->right;
		delete tmp;
		tmp = tmp2;
	}
	delete tmp;
}

FNode * FNode::unlink(){
	if( right == this ){
		throw "ERROR: Unlinking singleton node";
	} else {
		this->right->left = left;
		this->left->right = right;
		this->right = this;
		this->left = this;
		if ( this->parent && this->parent->children == this ){
			this->parent->children = this->right;
			this->parent->mark();
		}
		this->parent = NULL;
	}
	return this;
}

FNode * FNode::appendNode(FNode * f){
	if ( f == NULL ){
		throw "ERROR: tried to operate on a NULL node pointer.";
	}
	
	FNode * n = new FNode (f);
	n->right = right;
	n->left = this;
	right->left = n;
	right = right->left;
	return n;
}

FNode * FNode::prependNode(FNode * f){
	if ( f == NULL ){
		throw "ERROR: tried to operate on a NULL node pointer.";
	}

	FNode * n = new FNode(f);
	f->left = left;
	f->right = this;
	left->right = n;
	left = left->right;
	return n;
}


FNode * FNode::addChild(FNode * f){
	if ( f == NULL ){
		throw "ERROR: tried to operate on a NULL node pointer.";
	}

	#ifdef DEBUG
	cout << "Adding " << f->getValue() << " to node " << value << endl;
	#endif

	FNode * n = new FNode(f);
	if ( children == NULL ){

		#ifdef DEBUG
		cout << "Node " << value << " currently has no children." << endl;
		#endif

		this->children = n;
		n->parent = this;
		n->unMark();
	} else {
		this->children->appendNode(n)->parent = this;
	}
	degree++;

	return n;
}

FNode * FNode::addChild(int i){
	return addChild(new FNode(i));
}


FNode * FNode::findInChildren(int target){
	if ( target == value ){
		return this;
	} else if ( target < value && children ){
		FNode * tmp = children;
		do {
			if ( tmp->findInChildren(target) ){
				return tmp->findInChildren(target);
			} else {
				tmp = tmp->right;
			}
		} while ( tmp->right != children);
	}
	return NULL;
}