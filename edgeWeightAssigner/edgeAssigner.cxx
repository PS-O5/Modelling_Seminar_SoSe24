#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Function to read the .graph file
int readGraphFile(const string& filename, vector<vector<int>>& adjacencyList) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    int numVertices, numEdges;

    // Read the first line which contains the number of vertices and edges
    getline(file, line);
    stringstream ss(line);
    ss >> numVertices >> numEdges;

    // Resize the adjacency list to hold all vertices
    adjacencyList.resize(numVertices);

    // Read the adjacency list
    int vertex = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        int neighbor;
        while (ss >> neighbor) {
            adjacencyList[vertex].push_back(neighbor); // Assuming vertices are 1-indexed in file
        }
        vertex++;
    }

    file.close();
    return numEdges;
}

// Function to write the .graph file with weights
void writeGraphFile(const string& filename, const vector<vector<int>>& adjacencyList, const vector<vector<int>>& vertexWeights, const vector<int>& edgeWeights, const int& numEdges) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    int numVertices = adjacencyList.size();
    //int numEdges = edgeWeights.size();
    int ncon = 1;

    // Write the number of vertices, edges, and weight flags
    file << numVertices << " " << numEdges << " 001" /*<< " " << ncon*/ << endl;

    int edgeIndex = 0;

    // Write the adjacency list with vertex and edge weights
    for (int i = 0; i < numVertices; ++i) {
      
	   //file << 5 << " "; 
	if(i == numVertices/2){
        for (int j = 0; j < adjacencyList[i].size(); ++j) {
            file << adjacencyList[i][j] << " " << 10 << " "/* << edgeWeights[edgeIndex++] << " "*/;
        }
	}
	else{
		for (int j = 0; j < adjacencyList[i].size(); ++j) {
            file << adjacencyList[i][j] << " " << 1 << " "/* << edgeWeights[edgeIndex++] << " "*/;
        	}
	}
        file << endl;
    }

    /*
    for (int i = (numVertices)/3; i < numVertices; ++i) {
       
	    //file << 3 << " ";
        for (int j = 0; j < adjacencyList[i].size(); ++j) {
            file << adjacencyList[i][j] << " " << 7 << " " << edgeWeights[edgeIndex++] << " ";
        }
        file << endl;
    }*/

    file.close();
}

int main(int argc, char* argv[]) {
    string inputFilename = argv[1];
    string outputFilename = argv[2];

    // Example vertex and edge weights
    vector<vector<int>> vertexWeights = {
        {1, 2}, {3, 4}, {5, 6} // Add your specific vertex weights here
    };

    vector<int> edgeWeights = {
        1, 2, 3, 4, 5, 6 // Add your specific edge weights here
    };

    vector<vector<int>> adjacencyList;

    int numEdges = readGraphFile(inputFilename, adjacencyList);
    writeGraphFile(outputFilename, adjacencyList, vertexWeights, edgeWeights, numEdges);
  
 /*   for(auto& list : adjacencyList){
    	for(auto& ele : list){
		std::cout << ele << " " << std::endl;
	}
    }
*/
    cout << "Graph file with weights written to " << outputFilename << endl;

    return 0;
}
