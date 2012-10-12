#include <iostream>
#include "FNode.h"
#include "FHeap.h"

using namespace std;

int main(){
	try{
		FHeap * f = new FHeap();
		FNode * n = new FNode(3);
		n->addChild(8);
		n->addChild(9);
		f->insert(new FNode(5));
		f->insert(n);
		f->insert(1);
		f->insert(4);
		cout << f->print();
		cout << "====================================" << endl;
		f->deleteMin();
		cout << f->print();
		cout << "====================================" << endl;
		f->deleteMin();
		cout << f->print();
		cout << "====================================" << endl;
	} catch ( char* message ){
		cout << message << endl;
		return 1;
	}
	return 0;
}