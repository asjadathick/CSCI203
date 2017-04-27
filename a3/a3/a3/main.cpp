//
//  main.cpp
//  a3
//
//  Created by Asjad Athick on 26/9/16.
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

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "Utils.hpp"

using namespace std;

float **matrix = NULL;
int size = 0;
int edges = 0;
float *edgesArray = NULL;

//prototypes


void allocMemory(){
	
	//alloc memory for matrix
	matrix = new float *[size];
	for (int i = 0; i < size; ++i) {
		matrix[i] = new float[size];
		for (int j = 0; j < size; ++j) {
			matrix[i][j] = 0;
		}
	}
	
	edges = (size * (size - 1)) / 2;
	edgesArray = new float[edges];
	for (int i = 0; i < edges; ++i) {
		edgesArray[i] = 0;
	}
	
}

void loadFile(ifstream& input){
	int n = 0;
	float temp = 0;
	while (n < (size*size) && (input >> temp)) {
		matrix[n/size][n%size] = temp;  // n/size gets row, n%size gets coloumn, n is simply the count of the item
		++n;
	}
	
	if (n != size*size) {
		throw string("File did not contain enough information for the dimensions entered.");
	}
}

void deallocMemory(){
	for (int i = 0; i < size; ++i) {
		delete [] matrix[i];
	}
	
	delete [] edgesArray;
}

void printMatrix(){
	//test print matrix
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

int numberOfBits(int i)
{
	//Algorithm derived by learning material on
	//https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
	
	i = i - ((i >> 1) & 0x55555555);
	i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
	return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

string show_binary(unsigned int u, int num_of_bits)
{
	string a = "";
	
	int t = pow(double(2), (double)num_of_bits); //max num
	
	for(; t>0; t = t/2) //iterate through p of 2s
		if(u >= t){
			u -= t;
			a += "1";
		}
		else {
			a += "0";
		}
	
	return a ;
}

Pair getEdgeNodes(int i){
	Pair nodes;
	
	if (i > edges) {
		throw string ("Invalid value of i");
	}
	
	for (int j = 0; j < i; ++j) {
		nodes.x++;
		if (nodes.x >= size-1) {
			nodes.y++;
			nodes.x = nodes.y;
		}
	}
	
	return nodes;
}

bool bfAllVertices(unsigned int num){
	bool connected = false;
	
	//get binary rep, and find indexes of 1s
	//look up corresponding index in edges array, and determine x,y
	//add x,y to a set, and check if all edges appear to be connected
	
	string binaryRep = show_binary(num, edges-1);
	UniqueList list(edges);
//	cout << "Bin: " << binaryRep << endl;
	for (int i = 0; i < binaryRep.size(); ++i) {
		if (binaryRep[i]=='1') {
			Pair nodes = getEdgeNodes(i);
			list.add(nodes.x);
			list.add(nodes.y);
//			cout << "Added: " << nodes.x << "," << nodes.y << endl;
		}
	}
	
//	cout << "---------------" << endl;
	
	//if unique list size = size, connected
	if (list.getCount() == (size-1)) {
		connected = true;
	}
	
	return connected;
}

bool bfConnected(unsigned int num){
	bool connected = false;
	Pair *nodeList = new Pair[size-1];
	int nodeListSize = 0;
	
	string binaryRep = show_binary(num, edges-1);
	for (int i = 0; i < binaryRep.size(); ++i) {
		if (binaryRep[i] == '1') {
			Pair nodes = getEdgeNodes(i);
			nodeList[nodeListSize] = nodes;
			nodeListSize++;
//			cout << "Added: " << nodes.x << "," << nodes.y << endl;
		}
	}
	
	//check for connectivity
	Set set(size-1);
	set.add(nodeList[0].x);
	
	for (int i = 0; i < size; ++i) {
		if (set.find(nodeList[i].x)) {
			set.add(nodeList[i].y);
		}
	}
	
	if (set.getLength() == size-1) {
//		cout << "----Spanning tree!----" << endl;
		connected = true;
	}
	
	
	delete [] nodeList;
	
	return connected;
}

float getWeight(int num){
	float weight = 0;
	
	string binaryRep = show_binary(num, edges - 1);
	for (int i = 0; i < binaryRep.size(); ++i) {
		if (binaryRep[i] == '1') {
			Pair node = getEdgeNodes(i);
			weight += matrix[node.x][node.y];
		}
	}
	
	return weight;
}

void bfWriteToFile(int val){
	ofstream out;
	out.open("output_mst_Algorithm1.txt");
	string binaryRep = show_binary(val, edges - 1);
	
	float weight = 0;
	
	for (int i = 0; i < binaryRep.size(); ++i) {
		if (binaryRep[i] == '1') {
			Pair node = getEdgeNodes(i);
			out << node.x+1 << "-" << node.y+1 << " " << matrix[node.x][node.y] << endl;
			weight += matrix[node.x][node.y];
		}
	}
	
	out << weight << endl;
}


void bruteForce(){
	long start_time = clock();
	int count = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size; ++j) {
			edgesArray[count] = matrix[i][j];
			++count;
		}
	}
	
	float minWeight = MAXFLOAT;
	int mst = 0;
	
	
	//find candidates of n-1 from edges
	int n = pow((double)2, (double)edges);
	for (int i = 0; i < n; ++i) {
		//check if correct number of edges to be spanning tree
		//number of bits in number represent the number of edges
		if (numberOfBits(i) == size-1) {
			
			//check if all vertices connected
			if (bfAllVertices(i)) {
				
				//check for loops
				if (bfConnected(i)) {
//					cout << "Spanning tree: " << show_binary(i, edges-1) << endl;
					
					//check weight
					float weight = getWeight(i);
					if (weight < minWeight) {
						minWeight = weight;
						mst = i;
					}
					
				}
			}
		}
	}
	
	long end_time = clock();
	
	if (mst != 0) {
		bfWriteToFile(mst);
		cout << "1. Brute-force algorithm 1: " << (end_time - start_time) / double(CLOCKS_PER_SEC) << " seconds" << endl;
	}
	
}

void primsAlgorithm(){
	bool *done = new bool[size];
	bool allDone = false;
	for (int i = 0; i < size; ++i) {
		done[i] = false;
	}
	done[0] = true;
	
	long startTime = clock();
	
	Pair selectedNode;
	float minWeight;
	Pair *nodeList = new Pair[size-1];
	int listAddCount = 0;
	float treeWeight = 0;
	
	while (!allDone) {
		//find lowest weight in all "done" columns
		minWeight = MAXFLOAT;
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j){
				if ((!done[j]) || (done[i])) {
					continue;
				}
				//only trues
				if (matrix[i][j] < minWeight) {
					selectedNode.x = j;
					selectedNode.y = i;
					minWeight = matrix[i][j];
				}
			}
		}
		done[selectedNode.y] = true;
//		cout << "Selected: " << selectedNode.x << ", " << selectedNode.y << endl;
		nodeList[listAddCount] = selectedNode;
		listAddCount++;
		treeWeight += matrix[selectedNode.y][selectedNode.x];
		
		bool flag = true;
		for (int i = 0; i < size; ++i) {
			if (!done[i]) {
				flag = false;
			}
		}
		if (flag) {
			allDone = true;
		}
	}
	
	long endTime = clock();
	ofstream out;
	out.open("output_mst_Algorithm2.txt");
	for (int i = 0; i < listAddCount; ++i) {
		out << nodeList[i].x << "-" << nodeList[i].y << " " << matrix[nodeList[i].y][nodeList[i].x] << endl;
	}
	
	out << treeWeight << endl;
	
	cout << "2. Prim's algorithm 2 (matrix): " << (endTime - startTime) / double(CLOCKS_PER_SEC) << " seconds" << endl;
	
	delete [] nodeList;
	delete [] done;
}

int main(int argc, const char * argv[]) {
	if (argc < 1) {
		throw string ("Argument expected: matrixinput.txt");
		return 1;
	}
	
	
	//load file
	ifstream input;
	input.open(argv[1]);
	if (!input.good()) {
		throw string ("Input file could not be opened");
		return 1;
	}
	
	input >> size;
	
	allocMemory(); //allocates 2d float array with size*size
	loadFile(input); //loads data in file into array
	
	cout << "Number of vertices: " << size << endl;
	
	//process
	bruteForce();
	primsAlgorithm();
	
	
	deallocMemory();
    return 0;
}
