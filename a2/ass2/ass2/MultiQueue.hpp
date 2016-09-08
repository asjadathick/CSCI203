//
//  MultiQueue.hpp
//  ass2
//
//  Created by Asjad Athick on 9/09/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#ifndef MultiQueue_hpp
#define MultiQueue_hpp

#include "Heap.hpp"
#include "Utils.hpp"
#include <sstream>

class MultiQueue{
	Vector<Customer> list;
	Vector<Server> servers;
	StatPack pack;
	int numServers;
	void setup();
	int getFreeServer();
	void printQueue(); //test
	double currentTime;
public:
	MultiQueue();
	void simulate();
	void printStats();
};

#endif /* MultiQueue_hpp */
