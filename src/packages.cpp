#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <setup.h>
#include "packages.h"
#include "unbound.h"
#include "pihole.h"

using namespace std;

InstallPackages::InstallPackages(){
	//nothing here
}
InstallPackages::InstallPackages(map<string, map<string,string>> cmap){
	configMap = cmap;
	Setup pkgsetup;
	pkgsetup.update();
	pkgsetup.installEssentials();
	pkgsetup.installRequirements(cmap);
}
InstallPackages::~InstallPackages(){

}
int InstallPackages::install(){

    string dryinstall = "sudo apt-get install ";
    string unboundstr  = "unbound";
    string piholestr  = "pihole";
    if (configMap.find(unboundstr) != configMap.end()) {
	if(configMap[unboundstr][""] == "True"){
	std::cout<<"Installing unbound..."<<std::endl;
	SetupUnbound unbound(configMap);
	unbound.install();
	}
	}
    if (configMap.find(piholestr) != configMap.end()) {
	
	if(configMap[piholestr][""] == "True"){
		startInstall("Pihole");
		SetupPihole pihole(configMap);
		pihole.install();
		endInstall("Pihole");
	}
    }else {
        std::cout << "Nothing to install here!" << std::endl;
    }
    return 0;
} 
void InstallPackages::startInstall(const std::string& softwareName) {
	/*
	 * Beautify the prompt
	 */
	std::cout << getColor(GREEN) << "Starting installation of " 
		  << getColor(CYAN) << softwareName 
		  << getColor(GREEN) << "..." 
		  << getColor(RESET) << std::endl;
}

void InstallPackages::endInstall(const std::string& softwareName) {
	std::cout << getColor(GREEN) << "Installation of " 
		  << getColor(CYAN) << softwareName 
		  << getColor(GREEN) << " completed successfully!" 
		  << getColor(RESET) << std::endl;
}
    // Function to get ANSI escape code from Color enum
std::string InstallPackages::getColor(ColorCode color) const {
	return "\033[" + std::to_string(static_cast<int>(color)) + "m";
}
