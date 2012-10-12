#include "FHeap.h"
#include <iostream>
 
using namespace std;

FHeap::FHeap(){
	min = NULL;
}

FHeap::~FHeap(){
	FNode * tmp = min;
	FNode * tmp2;
	while ( tmp ){
		tmp2 = tmp->right;
		delete tmp;
		tmp = tmp2;
	}
}

FHeap * FHeap::operator=(FHeap * f){
	if ( this != f ){
		min = new FNode();
		min->setValue(f->getMin()->getValue());
		min->right = min;
		min->left = min;
		FNode * iterator = f->getMin();
		while ( iterator->right != f->getMin() ){
			FNode * newNode = new FNode(iterator->getValue());
			insert(newNode);
		}
	}
	return this;
}

void FHeap::insert(int v){
	insert(new FNode(v));
}

void FHeap::insert(FNode * f){
	if ( min == NULL ){
		min = new FNode(f);
	} else {
		FHeap * H = new FHeap();
		H->insert(f);
		this->meldWith(H);
	}
}

FNode * FHeap::find(int target){
	FNode * tmp = min;
	do {
		if ( tmp->findInChildren(target) ){
			return tmp->findInChildren(target);
		}
		tmp = tmp->right;
	} while ( tmp != min );
	return NULL;
}

FNode * FHeap::getMin(){
	return min;
}

void FHeap::deleteMin(){
	// 1. remove node with the min. key from the root cycle
	FNode * tmpMin = min->right;
	FNode * tmp;
	FNode * tmp2;
	int roots = 0;
	// int minVal = tmpMin->getValue();
	int arrayDegree;
	min->unlink();

	// 2. merge the root cycle with the cycle of children of this node
	tmp = min->children;
	while ( tmp ){
		tmpMin->appendNode(tmp);
		tmp->parent = NULL;
		tmp = tmp->right;
		if ( tmp == min->children ){ break; }
	}

	// 3. while two roots have the same degree, link them
	//  - Adjust the minimum key along the way
	tmp = tmpMin;
	do {
		roots++;
		tmp = tmp->right;
	} while ( tmp != tmpMin );

	tmp = tmpMin;
	min = tmpMin;

	//Create the array to keep track of the root node degrees
	int rootDegrees [roots+1];
	
	// Initialize the array to zeros
	for ( int i = 0; i < roots+1; i++ ){ rootDegrees[i] = 0; }

	// @TODO: make sure this runs enough times
	do {
		if ( tmp == tmpMin ){
			for ( int i = 0; i < roots+1; i++ ){ rootDegrees[i] = 0; }
		}

		// Fix the "min" pointer if necessary
		if ( tmp->getValue() < min->getValue() ){
			min = tmp;
		}

		arrayDegree = rootDegrees[tmp->getDegree()];
		if ( arrayDegree == 0 ){
			rootDegrees[tmp->getDegree()] = tmp->getValue();
			tmp = tmp->right;
		} else {
			if ( find(arrayDegree) && find(arrayDegree)->getValue() < tmp->getValue() ){
				find(arrayDegree)->addChild(tmp);
				tmp2 = tmp->right;
				delete tmp->unlink();
				tmp = tmp2;
			} else {
				tmp2 = find(arrayDegree);
				tmp2->unlink();
				tmp->addChild(tmp2);
				delete tmp2;
				tmp = tmp->right;
			}
		}
	} while ( tmp != tmpMin );
}

void FHeap::deleteNode(int target){
	FNode * tmp = find(target);
	FNode * tmpChildren = tmp->children;
	tmp->unlink();

	do {
		min->appendNode(tmpChildren);
		tmpChildren = tmpChildren->right;
	} while ( tmpChildren && tmpChildren != tmp->children );

	delete tmp;
}

void FHeap::decreaseKey(int target, int delta){
	// 1. Unlink tree rooted at the target
	FNode * t = find(target);
	if ( t == NULL ){
		throw "ERROR: Cannot find node to modify.";
	}

	if ( t == min ){
		min->setValue(min->getValue() - delta);
		return;
	}

	// 2. Decrease the key by delta
	t->setValue(t->getValue() - delta);

	// 3. Add the target to the root cycle
	min->appendNode(t);

	// 4. Unlink and do cascading cuts
	t->unlink();
}

void FHeap::meldWith(FHeap * f){
	int t;
	if ( f->getMin() ){
		FNode * tmp = f->getMin();
		// tmp = tmp->right;
		do {
			min->appendNode(tmp);
			tmp = tmp->right;
		} while ( tmp && tmp != f->getMin() );
		
		t = f->getMin()->getValue();
		if ( min->getValue() > t ){
			min = find(t);
		}
	}
}

std::string FHeap::print(){
	if ( min != NULL ){
		std::stringstream sstm;
		std::string result;
		// FNode * tmp = min;

		sstm << printCycle(min);

		result = sstm.str();
		return result;
	} else {
		return "[Empty F-Heap]";
	}
}

std::string FHeap::printCycle(FNode * f){
	// @TODO: this only prints the children of one node of the particular level. Fix it.
	
	std::stringstream result;
	std::string parent;
	FNode * tmp = f;
	int childrenCycles = 0;
	int childrenIndex = 0;

	if ( f ){

		do {
			if ( tmp->children ){
				childrenCycles++;
			}
			tmp = tmp->right;
		} while ( tmp != f);

		FNode * next [childrenCycles];

		if ( childrenCycles > 0 ){
			for ( int i = 0; i < childrenCycles; i++ ){ next[i] = NULL; }
		}

		do {
			result << tmp->getValue();
			if ( tmp->parent ){
				result << "(" << tmp->parent->getValue() << ")";
			}
			result << " ";

			if ( childrenCycles > 0 && tmp->children ){
				next[childrenIndex] = tmp->children;
				childrenIndex++;
			}

			tmp = tmp->right;
		} while ( tmp != f);

		if ( childrenCycles > 0 ) {
			for ( int i = 0; i < childrenCycles; i++ ){
				if ( next[i] ){
					if ( i == 0 ){
						result << endl;
					}
					result << printCycle(next[i]);
				}
			}
		}

		if ( childrenCycles > 0 ){
			result << endl;
		}

		return result.str();
	} else {
		throw "ERROR: Cannot print a cycle with a NULL pointer.";
	}
}