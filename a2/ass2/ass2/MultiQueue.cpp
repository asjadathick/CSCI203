//
//  MultiQueue.cpp
//  ass2
//
//  Created by Asjad Athick on 9/09/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#include "MultiQueue.hpp"
using namespace std;

MultiQueue::MultiQueue(){
	currentTime = 0;
	numServers = 0;
	setup();
}

void MultiQueue::simulate(){
	bool processed = false;
	long customerIndex = 0;
	MinHeap eventHeap;
	JobType nextJob = UnAlloc;
	int busyServers = 0;
	Vector<Customer> queue;
	
	
	while (!processed) {
		if (customerIndex < list.getSize()) {
			//customers exist
			if (eventHeap.getMinimum() != 0) {
				if (list[customerIndex].arrival < eventHeap.getMinimum()) {
					//arrival
					nextJob = Arrival;
				} else {
					//finish
					nextJob = Finish;
				}
			} else {
				//arrival because cust index is still valid
				nextJob = Arrival;
			}
		} else {
			if (eventHeap.getMinimum() != 0) {
				//finish
				nextJob = Finish;
			} else {
				//if it ends before processing queue, add check here
				//done
				processed = true;
			}
		}
		
		if (!processed) {
			if (nextJob == Arrival) {
				currentTime = list[customerIndex].arrival;
				//debug
				//cout<<currentTime<<endl;
				//
				pack.averageServiceTime += list[customerIndex].duration;
				if (busyServers < numServers) {
					eventHeap.insert(currentTime + list[customerIndex].duration);
					
					//stats
					//sever idle time
					int serverIndex = getFreeServer();
					servers[serverIndex].totalIdle += (currentTime - servers[serverIndex].busyTill);
					servers[serverIndex].busyTill = (currentTime + list[customerIndex].duration);
					
					
					busyServers++;
					customerIndex++;
				} else {
					//add to queue
					queue.addItem(list[customerIndex]);
					
					//stats
					pack.averageLengthOfQueue += queue.getSize();
					pack.queueLengthCount++;
					
					if (pack.maxLengthOfQueue < queue.getSize()) {
						pack.maxLengthOfQueue = queue.getSize();
					}
					
					customerIndex++;
				}
				
			} else if (nextJob == Finish){
				if (eventHeap.getMinimum() != 0) {
					currentTime = eventHeap.popMin();
					//debug
					//cout<<currentTime<<endl;
					//
					//Stats
					pack.numOfPeopleServed++;
					pack.simEndTime = currentTime;
					
					busyServers--;
					
					if (queue.getSize() != 0) {
						Customer temp = queue.popFront();
						eventHeap.insert(currentTime + temp.duration);
						
						//stats
						float timeSpentInQueue = currentTime - temp.arrival;
						pack.averageTimeSpentInQueue += timeSpentInQueue;
						pack.queueLengthCount++;
						
						if (timeSpentInQueue > pack.maxTimeSpentInQueue) {
							pack.maxTimeSpentInQueue = timeSpentInQueue;
						}
						
						//server idle time
						int serverIndex = getFreeServer();
						servers[serverIndex].totalIdle += (currentTime - servers[serverIndex].busyTill);
						servers[serverIndex].busyTill = (currentTime + temp.duration);
						
						busyServers++;
						
					}
					
				} else {
					continue;
				}
				
				
			} else {
				//shouldn't get here.
				cout << "Debug: Something's not right" << endl;
				processed = true;
			}
		}
	}
	
	//average out stats
	pack.averageServiceTime /= (pack.numOfPeopleServed == 0 ? 1: pack.numOfPeopleServed);
	pack.averageTimeSpentInQueue /= (pack.numOfPeopleServed == 0 ? 1 : pack.numOfPeopleServed);
	pack.averageLengthOfQueue /= (pack.queueLengthCount == 0 ? 1 : pack.queueLengthCount);
	ostringstream ss;
	for (int i = 0; i < numServers; ++i) {
		ss << "Server " << i+1 << ": " << servers[i].totalIdle << "\n";
	}
	pack.serverIdleTime = ss.str();
}

void MultiQueue::printStats(){
	printStatPack(pack);
}

void MultiQueue::printQueue(){
	for (int i = 0; i < list.getSize(); ++i) {
		cout << list[i].arrival << " " << list[i].duration << endl;
	}
}

int MultiQueue::getFreeServer(){
	for (int i = 0; i < numServers; ++i) {
		if (servers[i].busyTill < currentTime) {
			return i;
		}
	}
	return -1;
}

void MultiQueue::setup(){
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
	
	Server tem;
	for (int i = 0; i < numServers; ++i) {
		servers.addItem(tem);
	}
	
}
