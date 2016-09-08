//
//  Utils.cpp
//  ass2
//
//  Created by Asjad Athick on 6/09/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#include "Utils.hpp"
#include <iomanip>

void openFile(std::string filename, std::ifstream& file){
	file.open(filename.c_str());
	if (!file.good()) {
		throw std::string ("Exc: File could not be opened" + filename);
	}
}

void printStatPack(StatPack pack){
	std::cout << "\n---Simulation Results---\n" <<
	std::left << std::setw(29)<< "Number of people served: " << pack.numOfPeopleServed <<
	std::setw(30)<< "\nTotal simulation time: " << pack.simEndTime <<
	std::setw(30)<< "\nAverage service time: " << pack.averageServiceTime <<
	std::setw(30)<< "\nAverage time spent in queue: " << pack.averageTimeSpentInQueue <<
	std::setw(30)<< "\nMaximum time spent in queue: " << pack.maxTimeSpentInQueue <<
	std::setw(30)<< "\nAverage length of queue: " << pack.averageLengthOfQueue <<
	std::setw(30)<< "\nMaximum length of queue: " << pack.maxLengthOfQueue <<
	"\n\nTotal idle time for servers:\n" << pack.serverIdleTime <<
	"\n---Simulation complete---\n" << std::endl;
}


