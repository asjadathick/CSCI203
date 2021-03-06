//
//  SingleQueue.cpp
//  ass2
//
//  Created by Asjad Athick on 6/09/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#include "SingleQueue.hpp"
using namespace std;

SingleQueue::SingleQueue(string f){
	currentTime = 0;
	numServers = 0;
	filename = f;
	setup();
}

void SingleQueue::simulate(){
	bool processed = false;
	long customerIndex = 0;
	MinHeap eventHeap;
	JobType nextJob = UnAlloc;
	int busyServers = 0;
	Vector<Customer> queue;
	long maxQueueLenStat = 0;
	
	float avQueueLenStat = 0;
	
	
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
					avQueueLenStat += queue.getSize();
					pack.queueLengthCount++;
					
					if (maxQueueLenStat < queue.getSize()) {
						maxQueueLenStat = queue.getSize();
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
	
	//add idle time at end of sim
	for (int i = 0; i < numServers; ++i) {
		servers[i].totalIdle += (currentTime - servers[i].busyTill);
	}
	
	//average out stats
	pack.averageServiceTime /= (pack.numOfPeopleServed == 0 ? 1: pack.numOfPeopleServed);
	pack.averageTimeSpentInQueue /= (pack.numOfPeopleServed == 0 ? 1 : pack.numOfPeopleServed);
	ostringstream s1;
	avQueueLenStat /= (pack.queueLengthCount == 0 ? 1 : pack.queueLengthCount);
	
	s1 << avQueueLenStat;
	
	pack.averageLengthOfQueue = s1.str();
	
	s1.str(std::string());
	s1 << maxQueueLenStat;
	pack.maxLengthOfQueue = s1.str();
	
	ostringstream ss;
	for (int i = 0; i < numServers; ++i) {
		ss << "Server " << i+1 << ": " << servers[i].totalIdle << "\n";
	}
	pack.serverIdleTime = ss.str();
}

void SingleQueue::printStats(){
	printStatPack(pack);
}

void SingleQueue::printQueue(){
	for (int i = 0; i < list.getSize(); ++i) {
		cout << list[i].arrival << " " << list[i].duration << endl;
	}
}

int SingleQueue::getFreeServer(){
	for (int i = 0; i < numServers; ++i) {
		if (servers[i].busyTill < currentTime) {
			return i;
		}
	}
	return -1;
}

void SingleQueue::setup(){
	
	ifstream file;
	openFile(filename, file);
	
	file >> this->numServers;
	
	Customer temp;
	while ((file >> temp.arrival) && file >> temp.duration) {
		list.addItem(temp);
	}
	
	file.close();
	
	Server tem;
	for (int i = 0; i < numServers; ++i) {
		servers.addItem(tem);
	}
	
}

