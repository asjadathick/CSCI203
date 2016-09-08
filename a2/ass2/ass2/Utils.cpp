//
//  Utils.cpp
//  ass2
//
//  Created by Asjad Athick on 6/09/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#include "Utils.hpp"

void openFile(std::string filename, std::ifstream& file){
	file.open(filename.c_str());
	if (!file.good()) {
		throw std::string ("Exc: File could not be opened" + filename);
	}
}

void printStatPack(StatPack pack){
	std::cout << "\n---Simulation Results---\n" <<
	"Number of people served: " << pack.numOfPeopleServed <<
	"\nTotal simulation time: " << pack.simEndTime <<
	"\nAverage service time: " << pack.averageServiceTime <<
	"\nAverage time spent in queue: " << pack.averageTimeSpentInQueue <<
	"\nMaximum time spent in queue: " << pack.maxTimeSpentInQueue <<
	"\nAverage length of queue: " << pack.averageLengthOfQueue <<
	"\nMaximum length of queue: " << pack.maxLengthOfQueue <<
	"\n\nTotal idle time for servers:\n" << pack.serverIdleTime <<
	"\n---Simulation complete---\n" << std::endl;
}