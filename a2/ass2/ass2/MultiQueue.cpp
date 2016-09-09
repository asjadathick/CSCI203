//
//  MultiQueue.cpp
//  ass2
//
//  Created by Asjad Athick on 9/09/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#include "MultiQueue.hpp"
using namespace std;


MultiQueue::MultiQueue(string f){
	currentTime = 0;
	numServers = 0;
	filename = f;
	setup();
	queueArray = new Vector<Customer>[numServers];
}

long MultiQueue::getShortestQueue(){
	long minIndex = 0, minVal = queueArray[0].getSize();
	
	for (int i = 1; i < numServers; ++i) {
		if (queueArray[i].getSize() < minVal) {
			minVal = queueArray[i].getSize();
			minIndex = i;
		}
	}
	
	return minIndex;
}

int MultiQueue::findFinishingServer(float time){
	for (int i = 0; i < numServers; ++i) {
		if (servers[i].busyTill == time) {
			return i;
		}
	}
	return -1; //shouldn't ideally happen when called in proper context
}

void MultiQueue::simulate(){
	bool processed = false;
	long customerIndex = 0;
	MinHeap eventHeap;
	JobType nextJob = UnAlloc;
	int busyServers = 0;
	Vector<float> averageServerQueueLengths(numServers,0);
	Vector<float> queueLengthCounts(numServers, 0);
	Vector<float> maxQueueLengths(numServers, 0);
	
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
					
					//get shortest queue
					
					long queueIndex = getShortestQueue();
					
					queueArray[queueIndex].addItem(list[customerIndex]);
					
					//stats
					averageServerQueueLengths[queueIndex] += queueArray[queueIndex].getSize();
					
					queueLengthCounts[queueIndex]++;
					
					if (maxQueueLengths[queueIndex] < queueArray[queueIndex].getSize()) {
						maxQueueLengths[queueIndex] = queueArray[queueIndex].getSize();
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
					
					//find the server that finished
					int finishServerIndex = findFinishingServer(currentTime);
					
					//check queue for this particular server
					if (queueArray[finishServerIndex].getSize() != 0) {
						Customer temp = queueArray[finishServerIndex].popFront();
						eventHeap.insert(currentTime + temp.duration);
						
						//stats
						float timeSpentInQueue = currentTime - temp.arrival;
						pack.averageTimeSpentInQueue += timeSpentInQueue;
						pack.queueLengthCount++;
						
						if (timeSpentInQueue > pack.maxTimeSpentInQueue) {
							pack.maxTimeSpentInQueue = timeSpentInQueue;
						}
						
						//server idle time
						servers[finishServerIndex].totalIdle += (currentTime - servers[finishServerIndex].busyTill); //would be 0
						servers[finishServerIndex].busyTill = (currentTime + temp.duration);
						
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
	//pack.averageLengthOfQueue /= (pack.queueLengthCount == 0 ? 1 : pack.queueLengthCount);
	
	//collect av queue lengths into str
	ostringstream s1;
	s1 << endl;
	for (int i = 0; i < numServers; ++i) {
		s1 << "Server " << i+1 << ": " << (averageServerQueueLengths[i]/(queueLengthCounts[i]== 0? 1 : queueLengthCounts[i])) << endl;
		
	}
	
	pack.averageLengthOfQueue = s1.str();
	
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

MultiQueue::~MultiQueue(){
	delete [] queueArray;
}

void MultiQueue::setup(){
	
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
