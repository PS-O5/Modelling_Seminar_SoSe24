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
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include <vtkCellArray.h>
#include <vtkIdList.h>
#include <vtkUnsignedCharArray.h>
#include <vtkPoints.h>
#include <vtkPointData.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<int> readPartitionFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open partition file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<int> partitions;
    int part;
    while (inFile >> part) {
        partitions.push_back(part);
    }
    inFile.close();

    return partitions;
}

vtkSmartPointer<vtkUnsignedCharArray> generateColors(const std::vector<int>& partitions) {
    vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
    colors->SetNumberOfComponents(3);
    colors->SetName("Colors");

    std::unordered_map<int, std::array<unsigned char, 3>> colorMap;
    int maxPartition = *std::max_element(partitions.begin(), partitions.end());

    for (size_t i = 0; i < partitions.size(); ++i) {
        int partition = partitions[i];
        if (colorMap.find(partition) == colorMap.end()) {
            colorMap[partition] = { static_cast<unsigned char>(rand() % 256),
                                    static_cast<unsigned char>(rand() % 256),
                                    static_cast<unsigned char>(rand() % 256) };
        }
        colors->InsertNextTuple3(colorMap[partition][0], colorMap[partition][1], colorMap[partition][2]);

    }

    return colors;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " input.vtk partition_file output.vtk" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inputFilename = argv[1];
    std::string partitionFilename = argv[2];
    std::string outputFilename = argv[3];

    // Read the original VTK file
    vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(inputFilename.c_str());
    reader->Update();

    vtkSmartPointer<vtkPolyData> polyData = reader->GetOutput();

    // Read the partition file
    std::vector<int> partitions = readPartitionFile(partitionFilename);
    if (partitions.size() != static_cast<size_t>(polyData->GetNumberOfPoints())) {
        std::cerr << "Number of partitions does not match the number of vertices in the mesh." << std::endl;
        return EXIT_FAILURE;
    }

    // Generate colors based on partitions
    vtkSmartPointer<vtkUnsignedCharArray> colors = generateColors(partitions);

    // Assign colors to the vertices
    polyData->GetPointData()->SetScalars(colors);

    // Write the new VTK file with colors
    vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
    writer->SetFileName(outputFilename.c_str());
    writer->SetInputData(polyData);
    writer->Write();

    std::cout << "Partitioned VTK file saved to " << outputFilename << std::endl;

    return EXIT_SUCCESS;
}
