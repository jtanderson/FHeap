/**
 * File: main.cpp
 *
 * The driver file for the Fibonacci-heap project. This handles
 * processing user input throgh the command file as specified by the
 * project specifications.
 * 
 * @author Joseph T. Anderson <jtanderson@ratiocaeli.com>
 * @since 2012-11-04
 * @version 2012-11-04
 *
 */
#include "main.h"

// #define DEBUG

int main(int argc, char *argv[]){
	try{
		if ( argc == 2 ){
			// Open the file, read it, and do stuff
			ifstream f(argv[1]);
			if ( ! f.fail() ){
				FHeap * heap = new FHeap();
				string line;
				int i, arg1, arg2;
				while ( ! f.eof() ){
					getline(f,line);
					switch ( line[0] ){
						case 'i':
							i = line.find(" ");
							arg1 = atoi(line.substr(i+1).c_str());
							#ifdef DEBUG
								cout << "Inserting: " << arg1 << endl;
							#endif
							heap->insert(arg1);
							break;
						case 'm':
							#ifdef DEBUG
								cout << "Printing Min: " << ( heap->getMin() != NULL ? heap->getMin()->getValue() : 0 ) << endl;
							#endif
							cout << heap->getMin()->getValue() << endl;
							break;
						case 'd':
							#ifdef DEBUG
								cout << "Deleting Min: " << ( heap->getMin() != NULL ? heap->getMin()->getValue() : 0 ) << endl;
							#endif
							heap->deleteMin();
							break;
						case 'x':
							i = line.find(" ");
							arg1 = atoi(line.substr(i+1).c_str());
							#ifdef DEBUG
								cout << "Deleting Node: " << arg1 << endl;
							#endif
							heap->deleteNode(arg1);
							break;
						case 'c':
							i = line.find(" ");
							arg1 = atoi(line.substr(i+1).c_str());
							arg2 = atoi(line.substr(line.find(" ", i+1)).c_str());
							#ifdef DEBUG
								cout << "Setting key: " << arg1 << " to: " << arg2 << endl;
							#endif
							heap->setKey(arg1, arg2);
							break;
						default:
							break;
					}
					#ifdef DEBUG	
						cout << "Current tree: " << endl << heap->print() << endl;
					#endif
				}
				f.close();
			} else {
				cerr << "Error: the specified file could not be opened for reading." << endl;
			}
		} else {
			cerr << "Error: no file specified." << endl;
			cerr << "Usage: fheap file" << endl;
			exit(2);
		}
	} catch ( const char* message ){
		#ifdef DEBUG
			cerr << message << endl;
		#else
			cout << "error" << endl;
		#endif
		return 1;
	}
	return 0;
}