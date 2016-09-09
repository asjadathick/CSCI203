//
//  Heap.cpp
//  ass2
//
//  Created by Asjad Athick on 4/09/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#include "Heap.hpp"

MinHeap::MinHeap(){
	//nothing to do
}

void MinHeap::Heapify(){
	long len = array.getSize();
	for (long i = len - 1; i >= 0; --i) {
		siftDown(i);
	}
}

void MinHeap::siftDown(long index){
	long len = array.getSize();
	long leftChildIdx = (2 * index) + 1;
	long rightChildIdx = (2 * index) + 2;
	
	if (leftChildIdx >= len) {
		return; //leaf node
	}
	
	long minIdx = index;
	
	if (array[index] > array[leftChildIdx]){
		minIdx = leftChildIdx;
	}
	
	if ((rightChildIdx < len) && (array[minIdx] > array[rightChildIdx])) {
		minIdx = rightChildIdx;
	}
	
	if (minIdx != index) {
		swap(array[minIdx], array[index]);
		siftDown(minIdx);
	}
}

void MinHeap::swap(float &i1, float &i2){
	float temp = i1;
	i1 = i2;
	i2 = temp;
}

void MinHeap::siftUp(long index){
	if (index == 0) {
		return; //root
	}
	
	long parentIdx = (index - 1) / 2;
	if (array[parentIdx] > array[index]) {
		swap(array[parentIdx], array[index]);
		siftUp(parentIdx);
	}
}

void MinHeap::insert(float value){
	array.addItem(value);
	siftUp(array.getSize()-1);
}

float MinHeap::getMinimum(){
	if (array.getSize() == 0) {
		return 0;
	}
	return array[0];
}

float MinHeap::popMin(){
	float ret = getMinimum();
	removeMinimum();
	return ret;
}

void MinHeap::removeMinimum(){
	long len = array.getSize();
	
	if (len == 0) {
		return; //nothing to remove
	}
	
	array[0] = array[len - 1];
	array.popBack();
	siftDown(0);
}
