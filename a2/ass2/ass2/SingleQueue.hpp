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
#include <sstream>

class SingleQueue{
	Vector<Customer> list;
	Vector<Server> servers;
	StatPack pack;
	int numServers;
	void setup();
	int getFreeServer();
	void printQueue(); //test
	double currentTime;
	std::string filename;
public:
	SingleQueue(std::string);
	void simulate();
	void printStats();
};

#endif /* SingleQueue_hpp */
