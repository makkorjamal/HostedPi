#include <iostream>
#include <csignal>
#include <cstdlib> 
#include "setup.h" 

Setup::Setup(){
	// do nothing
}
Setup::~Setup(){
	//~Destroy
}

void Setup::checkCancel(int signal) {
    std::cout << "Operation cancelled by the user! Exiting..." << std::endl;
    exit(0); 
}

int Setup::update(){
    std::cout << "Updating package lists..." << std::endl;
    std::signal(SIGINT, Setup::checkCancel);
    int updateStatus = system("sudo apt-get update");
    if (updateStatus == 0 ) {
	std::cout << "Package lists updated successfully." << std::endl;
    } else {
	std::cerr << "Failed to update package lists." << std::endl;
	return 1; 
    }
    return 0;
}
int Setup::installEssentials(){
    /*
     *This function is used to setup all the packages necessary
     * to install the different programs
     * packages valid for initial build
     * */
    std::cout << "Installing build-essential..." << std::endl;
    std::signal(SIGINT, Setup::checkCancel);
    int installStatus = system("sudo apt-get install -y build-essential");
    if (installStatus == 0) {
        std::cout << "build-essential installed successfully." << std::endl;
    } else {
        std::cerr << "Failed to install build-essential." << std::endl;
        return 1; 
    }
    return 0;

}
int Setup::installRequirements(){
	/*
	 * This method is installs requirement
	 * per package. The list is read from 
	 * the config map
	 */
	return 0;
}
