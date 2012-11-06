/**
 * File: FHeap.h
 *
 * The header file for the Fibonacci Heap data structure
 * 
 * @author Joseph T. Anderson <jtanderson@ratiocaeli.com>
 * @since 2012-11-04
 * @version 2012-11-04
 *
 */

#ifndef FHEAP_H
#define FHEAP_H

#include "FNode.h"
#include <cstddef>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <vector>

class FHeap{

private:
	FNode * min;
	std::string printCycle(FNode * f);

public:
	FHeap();
	~FHeap();

	FHeap * operator=(FHeap * f);

	void insert(int v);
	void insert(FNode * f);
	FNode * find(int target);
	FNode * getMin();
	void deleteMin();
	void deleteNode(int target);
	void decreaseKey(int target, int delta);
	void setKey(int target, int newValue);
	void meldWith(FHeap * f);
	std::string print();
};

#endif
