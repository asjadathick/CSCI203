//
//  main.cpp
//  ass2
//
//  Created by Asjad Athick on 3/09/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#include <iostream>
#include "SingleQueue.hpp"

using namespace std;


int main(int argc, const char * argv[]) {
	SingleQueue sim1;
	sim1.simulate();
	sim1.printStats();
    return 0;
}
