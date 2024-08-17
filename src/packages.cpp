#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <setup.h>
#include "packages.h"
#include "unbound.h"

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
    }else if (configMap.find(piholestr) != configMap.end()) {
	if(configMap[piholestr][""] == "True"){
	std::cout<<"Installing pihole..."<<std::endl;
	//SetupPiHole pihole(configMap);
	//pihole.install();
	}
    }else {
        std::cout << "Nothing to install here!" << std::endl;
    }
    return 0;
    } 
