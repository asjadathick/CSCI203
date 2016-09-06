//
//  SingleQueue.cpp
//  ass2
//
//  Created by Asjad Athick on 6/09/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#include "SingleQueue.hpp"
using namespace std;

SingleQueue::SingleQueue(){
	numServers = 0;
	setup();
}

void SingleQueue::simulate(){
	long currentCustomer = 0;
	double currentTime = 0;
	int serversBusy = 0;
	
	MinHeap heap;
	
	while (currentCustomer < list.getSize()) {
		//determine what next event is
		if (heap.getMinimum() != 0) {
			//min wont be 0 unless the heap is empty
			if (heap.getMinimum() <= list[currentCustomer].arrival) {
				//job finish event
				currentTime = heap.popMin();
				//stats
				pack.numOfPeopleServed++;
				pack.simEndTime = currentTime;
				//--
				serversBusy--;
			}
		}
		
		currentTime = list[currentCustomer].arrival;
		//arrival - assign if server available
		if (serversBusy < numServers) {
			heap.insert(currentTime + list[currentCustomer].duration);
			//stats
			pack.averageServiceTime += list[currentCustomer].duration;
			
			float timeSpentInQueue = currentTime - list[currentCustomer].arrival;
			if (timeSpentInQueue > 0) {
				pack.averageTimeSpentInQueue += timeSpentInQueue;
				pack.inQueueCount++;
				
				if (pack.maxTimeSpentInQueue < timeSpentInQueue) {
					pack.maxTimeSpentInQueue = timeSpentInQueue;
				}
			}
			
			//--
			serversBusy++;
			currentCustomer++;
		} else {
			//put in queue and inc cust num
		}
	}
	
	//Average result pack
	pack.averageServiceTime /= pack.numOfPeopleServed;
	pack.averageTimeSpentInQueue /= pack.inQueueCount;
	
}

void SingleQueue::printStats(){
	printStatPack(pack);
}

void SingleQueue::printQueue(){
	for (int i = 0; i < list.getSize(); ++i) {
		cout << list[i].arrival << " " << list[i].duration << endl;
	}
}

void SingleQueue::setup(){
	string filename;
	cout << "Enter the text file name: ";
	cin >> filename;
	
	ifstream file;
	openFile(filename, file);
	
	file >> this->numServers;
	
	Customer temp;
	while ((file >> temp.arrival) && file >> temp.duration) {
		list.addItem(temp);
	}
	
}

