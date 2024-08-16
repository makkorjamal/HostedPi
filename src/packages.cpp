#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include "packages.h"
#include <setup.h>

using namespace std;

InstallPackages::InstallPackages(){
	//nothing here
}
InstallPackages::InstallPackages(map<string, map<string,string>> map){
	configMap = map;
	Setup pkgsetup;
	pkgsetup.update();
	pkgsetup.installEssentials();
}
InstallPackages::~InstallPackages(){

}
int InstallPackages::install(){

    string dryinstall = "apt-get --simulate install ";
    string unboundstr = "unbound";
    if (configMap.find(unboundstr) != configMap.end()) {
	if(configMap[unboundstr][""] == "True"){

		if (configMap[unboundstr].find("port") != configMap[unboundstr].end()) {
		    int port = stoi(configMap[unboundstr]["port"]);
		    if(port == 5335){
			    std::cout << "Installing unbound at non SSL port; " <<port<< std::endl;
			    string command = dryinstall.append(unboundstr);
			    int result = system(command.c_str());

			    // Check the result
			    if (result == -1) {
				perror("system");
				return EXIT_FAILURE;
			    } else {
				    std::cout<< "Unbound installed"<<endl;
			    }
		    } else if (port == 443){
			    std::cout<< "Handle ssl port here"<<endl;
		    }else{
			    std::cout<<"Invalid port"<<std::endl;
			    return EXIT_FAILURE;
		    }
		} else {
		    std::cout << "Please specify the unbound port" << std::endl;
		}
	}
    } else {
        std::cout << "Nothing to install here!" << std::endl;
    }
    return 0;
}
