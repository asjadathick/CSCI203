//
//  SingleQueue.hpp
//  ass2
//
//  Created by Asjad Athick on 6/09/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#ifndef SingleQueue_hpp
#define SingleQueue_hpp

#include "Heap.hpp"
#include "Utils.hpp"

class SingleQueue{
	Vector<Customer> list;
	StatPack pack;
	int numServers;
	void setup();
	void printQueue(); //test
public:
	SingleQueue();
	void simulate();
	void printStats();
};

#endif /* SingleQueue_hpp */
