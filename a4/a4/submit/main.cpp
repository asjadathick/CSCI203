//
//  main.cpp
//  a4
//
//  Created by Asjad Athick on 11/10/16.
//  Copyright © 2016 Asjad Athick. All rights reserved.
//

/*
 * CSCI203 Assignment 4
 *
 * Student name: Asjad Athick
 * Subject code: CSCI203
 * Student number: 2970512
 * Email ID: mama158@uowmail.edu.au
 * OWN WORK
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <stack>
using namespace std;

struct Node{
	vector<int> path;
	float lb;
	float ub;
	
	Node(){
		lb = 0;
		ub = 0;
	}
};

void openFile(ifstream& file, string filename, bool read = true){
	file.open(filename.c_str());
	if (!file.good()) {
		throw string("Could not open file: " + filename);
	}
}

string stripInvalidChars(string input){
	string val = "";
	for (int i = 0; i < input.length(); ++i) {
		if (isalnum(input[i]) || input[i]==' ') {
			val += input[i];
		}
	}
	return val;
}

void loadCities(vector<string>& input, string filename){
	ifstream file;
	openFile(file, filename);
	
	string buffer;
	
	input.clear();
	
	while (!file.eof()) {
		getline(file, buffer, '\n');
		input.push_back(stripInvalidChars(buffer));
	}
}

void loadMatrix(vector<vector<float> >& input, string filename){
	ifstream file;
	openFile(file, filename);
	
	int size = 0;
	file >> size;
	
	float buffer;
	for (int i = 0; i < size; ++i) {
		vector<float> temp;
		temp.clear();
		for (int j = 0; j < size; ++j) {
			file >> buffer;
			temp.push_back(buffer);
		}
		input.push_back(temp);
	}
}



bool notInPath(int index, vector<int> path){
	for (int i = 0; i < path.size(); ++i) {
		if (path[i] == index) {
			return false;
		}
	}
	return true;
}

float getPathWeight(vector<int> path, vector<vector<float> > matrix){
	float weight = 0;
	if (path.size() > 1) {
		for (int i = 1; i < path.size(); ++i) {
			weight += matrix[path[i-1]][path[i]];
		}
	}
	return weight;
}

float getLowerBound(vector<int> path, vector<vector<float> > matrix){
	int lb = 0;
	
	vector<bool> availableCols(matrix.size(), true);
	for (int i = 0; i < path.size(); ++i) {
		availableCols[path[i]] = false;
	}
	
	vector<bool> availableRows(matrix.size(), true);
	for (int i = 0; i < path.size() - 1; ++i) {
		availableRows[path[i]] = false;
	}
	
	//add weight of already included edges
	lb += getPathWeight(path, matrix);
	
	if (path.size() < matrix.size()) {
		//get min from available coloumns and rows
		for (int i = 0; i < matrix.size(); ++i) {
			if (availableCols[i]) {
				float min = MAXFLOAT;
				
				for (int j = 0; j < matrix.size(); ++j) {
					if (availableRows[j]) {
						//get min
						if (matrix[i][j] < min && (i != j)) {
							min = matrix[i][j];
						}
					}
				}
				lb += min;
			}
		}
		
		//add return path
		float min = MAXFLOAT;
		for (int i = 0; i < matrix.size(); ++i) {
			if (matrix[0][i] < min && (i != 0) && (notInPath(i, path))) {
				min = matrix[0][i];
			}
		}
		
		lb += min;
	}
	
	if (path.size() == matrix.size()) {
		//return path for fixed last element
		int lastNode = path[path.size()-1];
		lb += matrix[lastNode][0];
	}
	
	
	return lb;
}

float getUpperBound(vector<int> path, vector<vector<float> > matrix, bool verbose = false, vector<string> cities = vector<string>()){
	float ub = 0;
	vector<bool> visited (matrix.size(), false);
	visited[0] = true;
	
	int notVisited = (int) (matrix.size() - path.size());
	
	ub += getPathWeight(path, matrix);
	
	for (int i = 0; i < path.size(); ++i) {
		visited[path[i]] = true;
	}
	
	int currentNode = path[path.size()-1];
	
	while (notVisited > 0) {
		float minWeight = MAXFLOAT;
		int minNode = 0;
		
		for (int i = 0; i < matrix.size(); ++i) {
			if (matrix[currentNode][i] < minWeight && (!visited[i]) && (i != currentNode)) {
				minWeight = matrix[currentNode][i];
				minNode = i;
			}
			
		}
		
		ub += minWeight;
		visited[minNode] = true;
		currentNode = minNode;
		notVisited--;
		
		if (verbose) {
			path.push_back(minNode);
		}
	}
	
	//add return path
	ub += matrix[currentNode][0];
	
	if (verbose) {
		//return path
		path.push_back(0);
		cout << "\t";
		for (int i = 0; i < path.size(); ++i) {
			cout << path[i]+1 << " ";
		}
		cout << "\n\t";
		for (int i = 0; i < (path.size() - 1); ++i) {
			cout << cities[path[i]] << " -> ";
		}
		cout << cities[0] << endl;
		cout << "Total cost: " << ub << endl;
	}
	
	return ub;
}


void depthFirstBB(vector<string> cities, vector<vector<float> > matrix, float globalUB){
	
	stack<Node> liveNodes;
	vector<float> selectedPath;
	
	Node rootNode;
	rootNode.path.push_back(0);
	rootNode.lb = getLowerBound(rootNode.path, matrix);
	rootNode.ub = getUpperBound(rootNode.path, matrix);
	
	liveNodes.push(rootNode);
	
	vector<int> bestPath;
	float bestPathWeight = MAXFLOAT;
	
	while (!liveNodes.empty()) {
		
		//pop node, check for bounds
		Node node = liveNodes.top();
		liveNodes.pop();
		
		
		//check if leaf
		if (node.path.size() == matrix.size()) {
			float pathWeight = getPathWeight(node.path, matrix);
			//add return path
			pathWeight += matrix[node.path[node.path.size()-1]][0];
			
			if (pathWeight <= bestPathWeight) {
				bestPath = node.path;
				bestPathWeight = pathWeight;
			}
		}
		
		if (node.lb <= globalUB && (node.path.size() < matrix.size())) {
			//generate nodes
			vector<bool> nodesUsed (matrix.size(), false);
			for (int i = 0; i < node.path.size(); ++i) {
				nodesUsed[node.path[i]] = true;
			}
			
			for (int i = 0; i < nodesUsed.size(); ++i) {
				if (!nodesUsed[i]) {
					vector<int> basePath = node.path;
					basePath.push_back(i);
					nodesUsed[i] = true;
					Node newNode;
					newNode.path = basePath;
					newNode.lb = getLowerBound(newNode.path, matrix);
					newNode.ub = getUpperBound(newNode.path, matrix);
					if (newNode.ub < globalUB) {
						globalUB = newNode.ub;
					}
					liveNodes.push(newNode);
				}
			}
			
		}
		
	}
	
	cout << "Upper bound: " << rootNode.ub << endl;
	cout << "Lower bound: " << rootNode.lb << endl;
	cout << "Optimal tour:" << endl;
	cout << "\t";
	
	for (int i = 0; i < bestPath.size(); ++i) {
		cout << bestPath[i]+1 << " "; //paths are zero based
	}
	
	cout << "1\n\t";
	
	for (int i = 0; i < bestPath.size(); ++i) {
		cout << cities[bestPath[i]] << " -> ";
	}
	
	cout << cities[0] << endl;
	cout << "Total cost: " << bestPathWeight << endl;
}

int main(int argc, const char * argv[]) {
	
	if (argc < 3) {
		cout << "Insufficient arguments. Usage: $ program matrix.txt cities.txt" << endl;
		return 1;
	}
	
	string matrixInputFile = argv[1];
	string citiesInputFile = argv[2];
	
	
	vector<string> cities;
	loadCities(cities, citiesInputFile);
	
	vector<vector<float> > matrix;
	loadMatrix(matrix, matrixInputFile);
	
	//Greedy Algorithm
	cout << "1. Greedy algorithm:" << endl;
	cout << "Number of cities: " << matrix.size() << endl;
	cout << "Tour:" << endl;
	float ub = getUpperBound(vector<int>(1,0), matrix, true, cities);
	
	//Branch and Bound
	cout << "\n2. Branch-and-bound algorithm (Depth-first):" << endl;
	cout << "Number of cities: " << matrix.size() << endl;
	
	depthFirstBB(cities, matrix, ub);
	
	
    return 0;
}
