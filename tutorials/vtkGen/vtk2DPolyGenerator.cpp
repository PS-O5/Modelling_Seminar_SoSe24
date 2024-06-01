#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

void write2DVTK(std::vector<double> input);

int main(int argc, char* argv[]) {
    if (argc != 6) {
        std::cout << "Randya kay type kelais?!" << std::endl;
        return 1;
    }

    std::vector<double> input;

    for (int i = 1; i < argc; i++) {
        try {
            std::string buff = argv[i];
            input.push_back(std::stod(buff));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument at position " << i << ": could not convert to double" << std::endl;
            return 1;
        } catch (const std::out_of_range& e) {
            std::cerr << "Out of range at position " << i << ": the number is too large to convert to double" << std::endl;
            return 1;
        }
    }

    /* //Check vector
    for (const auto& i : input) {
        std::cout << i << std::endl;
    }*/

    write2DVTK(input);

    return 0;
}

void write2DVTK(std::vector<double> input){
    if(std::abs(input[0]-input[2]) != std::abs(input[1]-input[3])){
        std::cerr << "Not a square domain\n";
        return;
    }
    
    int gridSize = std::abs(input[4]) + 1;
    double h = std::abs(input[0]-input[2])/std::abs(input[4]);
    int numPoly = std::pow(std::abs(input[4]), 2) * 2;

    std::ofstream vtkFile("square.vtk");
    if(!vtkFile){
        std::cout << "Aai ghatli: File sapadli nahi" << std::endl;
        return;
    }

    vtkFile << "# vtk DataFile Version 3.0" << std::endl;
    vtkFile << "Algorithm Sample" << std::endl;
    vtkFile << "ASCII" << std::endl;
    vtkFile << "DATASET POLYDATA" << std::endl;
    vtkFile << "POINTS " << gridSize * gridSize << " double" << std::endl;

    for(int i = 0; i < gridSize; i++){
        for(int j = 0; j < gridSize; j++){
            vtkFile << j * h << " " << i * h << " " << 0 << std::endl;
        }
    }

    vtkFile << "POLYGONS " << numPoly << " " << numPoly * 4 << std::endl;

    for(int i = 0; i < gridSize - 1; i++){
        for(int j = 0; j < gridSize - 1; j++){
            vtkFile << 3 << " " << i * gridSize + j << " " << (i + 1) * gridSize + j << " " << i * gridSize + j + 1 << std::endl;
            vtkFile << 3 << " " << (i + 1) * gridSize + j << " " << (i + 1) * gridSize + j + 1 << " " << i * gridSize + j + 1 << std::endl;
        }
    }

    vtkFile.close();

/*
    //Uncomment this section if you want output on your terminal
    std::cout << "# vtk DataFile Version 3.0" << std::endl;
    std::cout << "Algorithm Sample" << std::endl;
    std::cout << "ASCII" << std::endl;
    std::cout << "DATASET POLYDATA" << std::endl;
    std::cout << "POINTS " << gridSize * gridSize << " double" << std::endl;

    for(int i = 0; i < gridSize; i++){
        for(int j = 0; j < gridSize; j++){
            std::cout << j * h << " " << i * h << " " << 0 << std::endl;
        }
    }

    std::cout << "POLYGONS " << numPoly << " " << numPoly * 4 << std::endl;

    for(int i = 0; i < gridSize - 1; i++){
        for(int j = 0; j < gridSize - 1; j++){
            std::cout << 3 << " " << i * gridSize + j << " " << (i + 1) * gridSize + j << " " << i * gridSize + j + 1 << std::endl;
            std::cout << 3 << " " << (i + 1) * gridSize + j << " " << (i + 1) * gridSize + j + 1 << " " << i * gridSize + j + 1 << std::endl;
        }
    }

*/

  
}

