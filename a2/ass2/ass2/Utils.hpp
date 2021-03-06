//
//  Utils.hpp
//  ass2
//
//  Created by Asjad Athick on 6/09/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <iostream>
#include <fstream>

struct Customer{
	float arrival, duration;
};

struct Server{
	float busyTill;
	float totalIdle;
	
	Server(){
		busyTill = 0;
		totalIdle = 0;
	}
};

struct StatPack{
	long numOfPeopleServed;
	float simEndTime;
	float averageServiceTime;
	float averageTimeSpentInQueue;
	float maxTimeSpentInQueue;
	std::string averageLengthOfQueue;
	std::string maxLengthOfQueue;
	std::string serverIdleTime; //for each server, CSV
	
	//utils
	int inQueueCount;
	int queueLengthCount;
	//
	
	StatPack(){
		numOfPeopleServed = 0;
		simEndTime = 0;
		averageServiceTime = 0;
		averageTimeSpentInQueue = 0;
		maxTimeSpentInQueue = 0;
		
		inQueueCount = 0;
		queueLengthCount = 0;
	}
};

enum JobType{
	Arrival, Finish, UnAlloc
};

void openFile(std::string filename, std::ifstream& file);

void printStatPack(StatPack pack);

#endif /* Utils_hpp */
