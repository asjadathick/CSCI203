//
//  singleQueue.cpp
//  a2
//
//  Created by Asjad Athick on 27/08/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#include "singleQueue.hpp"
using namespace std;

SingleQueue::SingleQueue(string filepath){
	setup(filepath);
	customers.print();
}

void SingleQueue::setup(string filepath){
	ifstream input;
	input.open(filepath.c_str());
	
	if (!input.good()){
		throw string ("File could not be opened " + filepath);
	}
	
	input >> numOfServers;
	
	float tempArrival, tempDuration;
	
	while ((input >> tempArrival) && (input >> tempDuration)) {
		customers.addItem(Item(tempArrival, tempDuration));
	}
	
	//setup servers
	Server tempServer;
	tempServer.busyTill = -1;
	
	for (int  i = 0; i< 10 ; ++i) {
		servers.addItem(tempServer);
	}
}

void SingleQueue::simulate(){
	
	ResultPack sim;
	
	sim.queueLength = customers.getLength();
	long currentTime = 0;
	
	long serverIndex = -1;
	
//	//do while get next event time
//	for (long i = 0; i < sim.queueLength; ++i) {
//		//update current time
//		
//		
//		//assign job
//		if ((serverIndex = getFreeServer(currentTime)) != -1) {
//			servers[serverIndex].busyTill = currentTime + customers[i].duration;
//		}
//	}
	
	//while list is not empty
	
	//update current time to next event time
	
	//if event is a job ending, do stats
	//start jobs if waiting
	
	//if event is job coming in, start
	
	//move customers from list to heap to keep track of servers
	
	
}


//--Helpers
long SingleQueue::getFreeServer(long currentTime){
	for (long i = 0; i < servers.getLength(); ++i) {
		if (servers[i].busyTill < currentTime) {
			return i;
		}
	}
	return -1;
}

