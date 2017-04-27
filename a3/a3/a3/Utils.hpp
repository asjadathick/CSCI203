//
//  Utils.hpp
//  a3
//
//  Created by Asjad Athick on 29/9/16.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//
/*
 * CSCI203/803 Assignment 3
 *
 * Student name: Asjad Athick
 * Subject code: CSCI203
 * Student number: 4970512
 * Email ID: mama158@uowmail.edu.au
 * OWN WORK
 */

#ifndef Utils_hpp
#define Utils_hpp

#include <iostream>

struct Pair{
	int x, y;
	
	Pair(){
		x = 0;
		y = 0;
	}
};

class UniqueList{
	bool *array;
	int size;
	int count;
	
public:
	UniqueList(int);
	void add (int);
	int getCount();
	~UniqueList();
};

class Set{
	int *array;
	int size;
	int length;
public:
	Set(int);
	void add(int);
	bool find(int);
	int getLength();
	~Set();
};

#endif /* Utils_hpp */
