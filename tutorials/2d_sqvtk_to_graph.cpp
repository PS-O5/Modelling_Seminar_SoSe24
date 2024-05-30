#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

std::vector<std::vector<int>> MeshToGraph_2DTri(int h);

int main() {
    std::vector<std::vector<int>> meshToGraph = MeshToGraph_2DTri(10); 	//It takes 'h' as input
    for(auto& vecs : meshToGraph){
	    for(auto& elements : vecs){
	    	std::cout << " " << elements << " ";
	    }
	    std::cout << std::endl;
    }
    return 0;
}

std::vector<std::vector<int>> MeshToGraph_2DTri(int k) {
    int h = k + 1;
    std::vector<std::vector<int>> graph;

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= h; j++) {
            if (i == 1 && j == 1) {             // UL corner
                std::vector<int> buff = {i + 1, h + 1, h + 2};
                graph.push_back(buff);
            } else if (i == 1 && j == h) {      // UR corner
                std::vector<int> buff = {h - 1, 2 * h};
                graph.push_back(buff);
            } else if (i == h && j == 1) {      // LL corner
                std::vector<int> buff = {(h - 2) * h + 1, (h - 1) * h + 2};
                graph.push_back(buff);
            } else if (i == h && j == h) {      // LR corner
                std::vector<int> buff = {(h * h) - 1, (h - 1) * h, (h - 1) * h - 1};
                graph.push_back(buff);
            } else if (i == 1 && j != 1 && j != h) {    // Top border
                std::vector<int> buff = {j - 1, j + 1, h + j, h + j + 1};
                graph.push_back(buff);
            } else if (i == h && j != 1 && j != h) {    // Bottom border
                std::vector<int> buff = {(h - 1) * h + j - 1, (h - 2) * h + j - 1, (h - 2) * h + j, (h - 1) * h + j + 1};
                graph.push_back(buff);
            } else if (i != 1 && i != h && j == 1) {    // Left border
                std::vector<int> buff = {(i - 2) * h + 1, (i - 1) * h + 2, (i * h) + 1, (i * h) + 2};
                graph.push_back(buff);
            } else if (i != 1 && i != h && j == h) {    // Right border
                std::vector<int> buff = {(i - 1) * h, (i - 2) * h + h - 1, (i * h) - 1, (i + 1) * h};
                graph.push_back(buff);
            } else {    // Inner vertices
                std::vector<int> buff = {(i - 2) * h + j - 1, (i - 2) * h + j, (i - 1) * h + j - 1, (i - 1) * h + j + 1, (i * h) + j, (i * h) + j + 1};
                graph.push_back(buff);
            }
        }
    }
    return graph;
}
