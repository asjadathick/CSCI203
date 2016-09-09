//
//  Vector.hpp
//  ass2
//
//  Created by Asjad Athick on 3/09/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <iostream>

template <class T>
class Vector{
	long capacity;
	long size;
	T* array;
	
	void resizeArray(long);
public:
	Vector();
	Vector(long, T);
	~Vector();
	long addItem(T item);
	T popBack();
	T popFront();
	bool removeItemAt(long index);
	long getSize();
	void print();
	T& operator [] (long);
};

#endif /* Vector_hpp */
