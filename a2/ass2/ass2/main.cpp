//
//  main.cpp
//  ass2
//
//  Created by Asjad Athick on 3/09/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#include <iostream>
#include "SingleQueue.hpp"
#include "MultiQueue.hpp"

using namespace std;


int main(int argc, const char * argv[]) {
	string filename, file;
	cout << "Enter the text file name: ";
	cin >> filename;
	
	try {
		SingleQueue sim1(filename);
		sim1.simulate();
		cout << "\nSimulation Type: Single Queue" << endl;
		sim1.printStats();
		
		MultiQueue simMult(filename);
		simMult.simulate();
		cout << "\nSimulation Type: Multi Queue" << endl;
		simMult.printStats();

	} catch (string ex) {
		cout << ex << endl;
	}
	
	return 0;
}
