//
//  container.cpp
//  a2
//
//  Created by Asjad Athick on 27/08/2016.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

#include "container.hpp"
using namespace std;

//------List---

template <class T>
List<T>::List(){
	this->size = 2;
	this->length = -1;
	array = new T[size];
}

template <class T>
long List<T>::addItem(T item){
	if (length + 1 >= size) {
		resizeArray(size * 2);
	}
	
	if (size >= length + 1) {
		length++;
		array[length] = item;
		return length;
	} else {
		return 0;
	}
}

template <class T>
bool List<T>::removeItemAt(long index){
	if (index >= length) {
		return false;
	}
	long i;
	for (i = index; i < length; ++i) {
		array[i] = array[i+1];
	}
	length--;
	
	return true;
}

template <class T>
T& List<T>::operator[](long index){
	return array[index];
}

template <class T>
void List<T>::print(){
	for (int i = 0; i <= length; ++i) {
		cout << array[i] << endl;
	}
}

template <class T>
long List<T>::getLength(){
	return this->length;
}

template <class T>
void List<T>::resizeArray(long newSize){
	if (this->size == newSize) {
		return;
	}
	
	T* newArray = new T[newSize];
	for (long i = 0; i <= length; ++i) {
		newArray[i] = array[i];
	}
	
	size = newSize;
	
	delete [] array;
	array = newArray;
}

template <class T>
List<T>::~List<T>(){
	delete [] array;
}


//-----Heap----

template <class T>
void Heap<T>::addItem(T item){
	array.addItem(item);
	siftUp(array.getLength());
}

template <class T>
long Heap<T>::getLeftChild(long index) {
	return (2 * index) + 1;
}

template <class T>
long Heap<T>::getRightChild(long index){
	return (2 * index) + 2;
}

template <class T>
long Heap<T>::getParent(long index){
	if (index == 0) {
		return -1;
	}
	return (index - 1) / 2;
}

template <class T>
void Heap<T>::swap(long i1, long i2){
	T temp = array[i1];
	array[i1] = array[i2];
	array[i2] = temp;
}

template <class T>
void Heap<T>::siftUp(long nodeIndex){
	//check that nodeIndex is not tree root
	if (nodeIndex == 0) {
		return;
	}
	
	if (getParent(nodeIndex) == -1) {
		return;
	}
	
	if (array[getParent(nodeIndex)] > array[nodeIndex]) {
		swap(nodeIndex, getParent(nodeIndex));
		siftUp(getParent(nodeIndex));
	}
}
