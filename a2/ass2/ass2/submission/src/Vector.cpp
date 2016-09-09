//
//  Vector.cpp
//  ass2
//
//  Created by Asjad Athick on 3/09/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#include "Vector.hpp"
using namespace std;

//--Vector--
template <class T>
Vector<T>::Vector(){
	this->capacity = 2;
	this->size = -1;
	array = new T[capacity];
}

template <class T>
Vector<T>::Vector(long size, T initVal){
	this->capacity = 2;
	this->size = -1;
	array = new T[capacity];
	
	for (int i = 0; i < size; ++i) {
		addItem(initVal);
	}
}

template <class T>
long Vector<T>::addItem(T item){
	if (size + 1 >= capacity) {
		resizeArray(capacity * 2);
	}
	
	if (capacity >= size + 1) {
		size++;
		array[size] = item;
		return size;
	} else {
		return 0;
	}
}

template <class T>
bool Vector<T>::removeItemAt(long index){
	if (index >= size) {
		return false;
	}
	long i;
	for (i = index; i < size; ++i) {
		array[i] = array[i+1];
	}
	size--;
	
	return true;
}

template <class T>
T& Vector<T>::operator[](long index){
	return array[index];
}

template <class T>
void Vector<T>::print(){
	for (int i = 0; i <= size; ++i) {
		cout << array[i] << endl;
	}
}

template <class T>
long Vector<T>::getSize(){
	return this->size + 1; //size in vec is 0 based
}

template <class T>
T Vector<T>::popBack(){
	size--;
	return array[size + 1];
}

template <class T>
T Vector<T>::popFront() {
	if (size > -1) {
		T ret = array[0];
		size--;
		for (int i = 0; i < size; ++i) {
			array[i+1] = array[i];
		}
		return ret;
	} else {
		return T();
	}
}

template <class T>
void Vector<T>::resizeArray(long newcapacity){
	if (this->capacity == newcapacity) {
		return;
	}
	
	T* newArray = new T[newcapacity];
	for (long i = 0; i <= size; ++i) {
		newArray[i] = array[i];
	}
	
	capacity = newcapacity;
	
	delete [] array;
	array = newArray;
}

template <class T>
Vector<T>::~Vector<T>(){
	delete [] array;
}



//--End Vector--
