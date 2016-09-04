//
//  container.hpp
//  a2
//
//  Created by Asjad Athick on 27/08/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#ifndef container_hpp
#define container_hpp

#include <iostream>

//--Struct Declarations

struct ResultPack{
	long simulationTime = 0;
	long queueLength = 0;
	long totalServiceDuration = 0;
	long totalTimeSpentInQueue = 0;
	int maxTimeSpentInQueue = 0;
};

struct Server{
	int busyTill = 0;
	int idleSince = 0;
};

//--Class Declarations

template <class T>
class List{
	long size;
	long length;
	T* array;
	
	void resizeArray(long);
public:
	List();
	~List();
	long addItem(T item);
	bool removeItemAt(long index);
	long getLength();
	void print();
	T& operator [] (long);
};

template <class T>
class Heap{
	List<T> array;
private:
	void siftUp(long nodeIndex);
	void swap(long i1, long i2);
public:
	void addItem(T item);
	void removeMin();
	long getLeftChild(long index);
	long getRightChild(long index);
	long getParent(long index);
};

#endif /* container_hpp */
