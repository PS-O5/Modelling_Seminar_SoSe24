#include <metis.h>
#include <iostream>
#include <utility>

void metisBinaryCheck();


int main() {
    std::cout << "METIS version: " << METIS_VER_MAJOR << "." 
              << METIS_VER_MINOR << "." << METIS_VER_SUBMINOR << std::endl;
    metisBinaryCheck();
    return 0;

}

void metisBinaryCheck(){
	std::string command = "gpmetis -help";
	int result = system(command.c_str());
	if(result != 0){
		std::cerr << "METIS Binaries not installed!" << std::endl;
	}
}
