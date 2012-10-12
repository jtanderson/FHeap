#ifndef FHEAP_H
#define FHEAP_H

#include "FNode.h"
#include <cstddef>
#include <string>
#include <stdlib.h>
#include <sstream>

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
	void meldWith(FHeap * f);
	std::string print();
};

#endif
