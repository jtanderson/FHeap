C++ Fibonacci Heap Implementation
=================================

Joseph Anderson
---------------

This project is the implementation of a Fibonacci Heap and its related
operations.

To build the project, use GNU `make` from the root of the project directory. It 
has been tested on the CSE stdlinux system and found to be working.

To run the project, the executable is found in the `./bin` folder and can be 
executed with the command

	./bin/fheap test_file.txt

and the results will be displayed to the standard output. That means one can
send the results to another file like

	./bin/fheap test_file.txt > results.txt

The input file can contain five commands:

* m - prints the minimum key in the heap
* i <key> - inserts a new node with the key <key> into the heap
* d - deletes the node with the minimum key from the heap
* c <key> <new_key> - for the node with the key <key>, the key becomes <new_key>
* x <key> - erases the node with the key <key>

and they must each be on a separate line. Any invalid commands will be skipped
and execution will continue.

Note:

* All key values in the heap must be unique
* All commands must appear on separate lines
* The file name must be passes as a parameter
