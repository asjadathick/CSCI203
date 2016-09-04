//
//  main.cpp
//  a2
//
//  Created by Asjad Athick on 23/08/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#include <iostream>
//#include "singleQueue.hpp"
#include "container.cpp"
#include "container.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
//	cout << "Enter data file path: ";
//	string filename;
//	cin >> filename;
//	
//	//SingleQueue sim1(filename);
	
	List<int> list;
	for (int i = 0; i < 100; ++i) {
		list.addItem(i);
	}
	
	list.print();
	
	for (int i = 1000; i < 2000; ++i) {
		list.addItem(i);
	}
	list.print();
	
    return 0;
}
