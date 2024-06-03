#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <unordered_map>
#include <utility>



void meshParti(std::string meshInputFile, int parts);
std::vector<int> vtkReader(std::string vtkFile);
void meshWriter(std::string fileName, std::vector<int> data);
void partiReader(std::string eFile, std::string nFile);

int main(int argc, char* argv[]){

	if(argc != 3){
		std::cout << "Invalid Command!" <<  std::endl;
		return 1;
	}
	
	
	//std::string fileName = argv[1];
	//std::cout << fileName << std::endl;
	std::vector<int> meshData = vtkReader(argv[1]);

	meshWriter(argv[1],meshData);
	std::string temp = argv[1];
	temp = temp + ".mesh";
	std::string parts = argv[2];
	meshParti(temp, std::stoi(parts));
	partiReader(temp+".epart."+parts, temp+".npart."+parts);

	return 0;
}


std::vector<int> vtkReader(std::string vtkFile){

	std::vector<int> polyData;
	std::string line;
    	bool polygonSectionFound = false;

	std::ifstream inputFile(vtkFile);
    	while (std::getline(inputFile, line)) {
        	if (polygonSectionFound) {
            	std::istringstream iss(line);
            	int value;
            	// Read the first value (i.e., 3) and ignore it
            	if (iss >> value) {
                	// Now read the rest of the values
                	while (iss >> value) {
                    	polyData.push_back(value);
			//polyData.push_back(value+1);
                	}
            	}
        	}

        	// Check for the POLYGONS line
        	if (line.find("POLYGONS") != std::string::npos) {
            	polygonSectionFound = true;
        	}	
   	 }

    	inputFile.close();

    	/*
	// Output the extracted data
    	for (int num : polyData) {
        	std::cout << num << " ";
    	}
    	std::cout << polyData.size()/3 << std::endl;	

	*/
	return polyData;

}

void meshWriter(std::string fileName, std::vector<int> data){
	
	
	std::ofstream meshFile(fileName+".mesh");
	if(!meshFile)
	{
		std::cerr << "Haglas!" << std::endl;
	}

	meshFile << data.size()/3 << " " << 1 << std::endl;
	for(int i = 0; i<data.size();i+=3){
		for(int j = 0; j<3;j++){
		meshFile << data[j+i];
			if(j<2){meshFile << " ";}
		}
		meshFile << std::endl;
	}

	


/*
	std::cout << data.size()/3 << " " << 1 << std::endl;
	for(int i = 0; i<data.size();i++){
		for(int j=0; j<4;j++){
			std::cout << data[i];
			if(j<4){std::cout << " ";}
		}
		std::cout << std::endl;

	}

*/
}

void meshParti(std::string meshInputFile, int n){

	std::string command = "mpmetis " + meshInputFile + " " + std::to_string(n);

	std::cout << "METIS Partitioning Started!" << std::endl;
	int result = system(command.c_str());
	if(result != 0){
		std::cerr << "METIS Install kelais ky?" << std::endl;
	}

}


void partiReader(std::string eFile, std::string nFile){
	
	std::unordered_map<int, std::pair<int,int>> infoParti;
	std::ifstream epart(eFile), npart(nFile);
	int id = 0;
        int ePartition, nPartition;
	if(!epart || !npart){
		std::cerr << "Aai ghatli!" << std::endl;
	}
	
	while (epart >> ePartition && npart >> nPartition) {
        //partitionInfo[id] = ePartition; // Store partition ID from .epart.* file
        infoParti[id] = std::make_pair(ePartition, nPartition);
	id++;
    	}
	epart.close();
	npart.close();

	for (std::unordered_map<int, std::pair<int, int>>::const_iterator it = infoParti.begin(); it != infoParti.end(); ++it) {
        std::cout << "Element/Node ID: " << it->first
                  << ", ePartition ID: " << it->second.first
                  << ", nPartition ID: " << it->second.second << std::endl;
    }

}
