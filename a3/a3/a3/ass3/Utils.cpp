//
//  Utils.cpp
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

#include "Utils.hpp"

UniqueList::UniqueList(int n){
	size = n;
	array = new bool[n];
	count = 0;
	for (int i = 0; i < n; ++i) {
		array[i] = false;
	}
}

void UniqueList::add(int val){
	if (!array[val]) {
		array[val] = true;
		count++;
	}
}

int UniqueList::getCount(){
	return count;
}

UniqueList::~UniqueList(){
	delete [] array;
}

Set::Set(int size){
	this->size = size;
	length = 0;
	array = new int[size];
	for (int i = 0; i < size; ++i) {
		array[i]=0;
	}
}

int Set::getLength(){
	return length;
}

bool Set::find(int val){
	for (int i = 0; i < length; ++i) {
		if (array[i] == val) {
			return true;
		}
	}
	
	return false;
}

void Set::add(int val){
	if (length > size) {
		throw std::string ("Set: length > size");
	}
	if (!find(val)) {
		array[length] = val;
		length++;
	}
}

Set::~Set(){
	delete [] array;
}
