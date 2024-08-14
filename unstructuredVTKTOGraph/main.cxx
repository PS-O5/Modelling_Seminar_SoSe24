/*
# This file is part of data produced by PS_O5@RPI1-dev.
#
# PS_O5@RPI1-dev data is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# PS_O5@RPI1-dev data is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with PS_O5@RPI1-dev data.  If not, see <https://www.gnu.org/licenses/>.
*/


#include <vtkSmartPointer.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCell.h>
#include <vtkCellArray.h>
#include <vtkIdList.h>

#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input.vtk output.graph" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];

    // Read the VTK file
    vtkSmartPointer<vtkUnstructuredGridReader> reader = vtkSmartPointer<vtkUnstructuredGridReader>::New();
    reader->SetFileName(inputFilename.c_str());
    reader->Update();

    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = reader->GetOutput();

    // Extract the number of vertices
    vtkIdType numVertices = unstructuredGrid->GetNumberOfPoints();

    // Create adjacency list and count edges
    std::vector<std::unordered_set<int>> adjacencyList(numVertices);
    vtkSmartPointer<vtkCellArray> cells = unstructuredGrid->GetCells();
    vtkSmartPointer<vtkIdList> idList = vtkSmartPointer<vtkIdList>::New();

    vtkIdType numEdges = 0;
    cells->InitTraversal();
    while (cells->GetNextCell(idList)) {
        for (vtkIdType i = 0; i < idList->GetNumberOfIds(); i++) {
            for (vtkIdType j = i + 1; j < idList->GetNumberOfIds(); j++) {
                int id1 = idList->GetId(i);
                int id2 = idList->GetId(j);
                if (adjacencyList[id1].find(id2) == adjacencyList[id1].end()) {
                    adjacencyList[id1].insert(id2);
                    adjacencyList[id2].insert(id1);
                    numEdges++;
                }
            }
        }
    }

    // Write the graph file
    std::ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open output file: " << outputFilename << std::endl;
        return EXIT_FAILURE;
    }

    outFile << numVertices << " " << numEdges << std::endl;
    for (const auto& neighbors : adjacencyList) {
        for (int neighbor : neighbors) {
            outFile << (neighbor + 1) << " "; // METIS expects 1-based indexing
        }
        outFile << std::endl;
    }

    outFile.close();

    std::cout << "Conversion complete. Graph saved to " << outputFilename << std::endl;

    return EXIT_SUCCESS;
}
