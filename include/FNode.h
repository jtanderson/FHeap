#ifndef FNODE_H
#define FNODE_H

#include "FNode.h"
#include <cstddef>

class FNode{
private:
	int value;
	bool marked;
	int degree;

public:
	FNode();
	FNode(FNode * f);
	FNode(int v);
	~FNode();
	int getValue(){ return value; };
	void setValue( int i ){ value = i; }
	bool isMarked(){ return marked; }
	void mark(){ marked = true; }
	void unMark(){ marked = false; }
	int getDegree(){ return degree; }
	FNode * unlink();
	FNode * appendNode(FNode * f);
	FNode * prependNode(FNode * f);
	FNode * addChild(FNode * f);
	FNode * addChild(int i);
	FNode * findInChildren(int target);
	FNode * left;
	FNode * right;
	FNode * children;
	FNode * parent;
};

#endif