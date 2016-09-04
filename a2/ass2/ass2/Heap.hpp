//
//  Heap.hpp
//  ass2
//
//  Created by Asjad Athick on 4/09/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//
//

#ifndef Heap_hpp
#define Heap_hpp

#include "Vector.hpp"
#include "Vector.cpp"

class MinHeap{
	Vector<float> array;
	void siftDown(long);
	void siftUp(long);
	void swap(float&, float&);
	void Heapify();
public:
	MinHeap();
	void insert(float value);
	float getMinimum();
	void removeMinimum();
};

#endif /* Heap_hpp */

