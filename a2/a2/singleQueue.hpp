//
//  singleQueue.hpp
//  a2
//
//  Created by Asjad Athick on 27/08/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#ifndef singleQueue_hpp
#define singleQueue_hpp

#include <iostream>
#include <fstream>
#include "container.cpp"
#include "container.hpp"

class SingleQueue{
private:
	class Item{
	public:
		float arrival;
		float duration;
		
		Item() : arrival(0) , duration(0) {}
		Item(float arr, float dur) : arrival(arr), duration(dur) {}
		
		friend ostream& operator << (ostream& os, const Item& i){
			os << i.arrival << ", " << i.duration;
			return os;
		}
	};
	
	List<Item> customers;
	List<Server> servers;
	
	int numOfServers;
	void setup(std::string);
	
	//helpers
	long getFreeServer(long);
	long getCurrentTime(long);
public:
	SingleQueue(std::string);
	void simulate();
	void printResults();
};

#endif /* singleQueue_hpp */
