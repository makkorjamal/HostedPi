#include <iostream>
#include <map>
#include <csignal>
#include <string>
#include <cstdlib> 
#include "setup.h" 
using namespace std;

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
    int installStatus = system("sudo apt-get install -y build-essential "
		    "git flex bison lighttpd");
    if (installStatus == 0) {
        std::cout << "build-essential installed successfully." << std::endl;
    } else {
        std::cerr << "Failed to install build-essential." << std::endl;
        return 1; 
    }
    return 0;

}
int Setup::installRequirements(std::map<string, map<string,string>> cmap){

	/*
	 * This method is installs requirement
	 * per package. The list is read from 
	 * the config cmap
	 */
	    string unboundstr = "unbound";
	    if (cmap.find(unboundstr) != cmap.end()) {
		if(cmap[unboundstr][""] == "True"){

			if (cmap[unboundstr].find("port") != cmap[unboundstr].end()) {
			    int port = stoi(cmap[unboundstr]["port"]);
			    if (port == 443){
				    std::cout<< "Installing required packages..."<<endl;
			            string command = "sudo apt-get -y install libssl-dev";
				    command.append(" libnghttp2-dev libsystemd-dev libexpat1-dev");
				    int result = system(command.c_str());
				    if (result == -1) {
					perror("system");
					return EXIT_FAILURE;
				    } else {
					    std::cout<< "Unbound installed"<<endl;
				    }
			    }
			    else{
				    return 1;
			    }
			}else{
				return 1;
			}
		}
	    }

	return 0;
}
