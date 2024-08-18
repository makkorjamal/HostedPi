#include <iostream>
#include <fstream> 
#include <iomanip>
#include <sstream>
#include "openssl/sha.h"
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include "pihole.h"

SetupPihole::SetupPihole(){
}

SetupPihole::SetupPihole(std::map<std::string, std::map<std::string,std::string>> cmap){
	configMap = cmap;
}

SetupPihole::~SetupPihole(){
}

int SetupPihole::install(){

	if(configMap["pihole"].find("password") != configMap["pihole"].end()) {
		//pass is read from the conf file
		std::string pass = configMap["pihole"]["password"];
		std::string firstHash = generateHash(pass);
		std::string passHash = generateHash(firstHash);
		std::cout<<"Hashed pass is: "<<passHash<<std::endl;
		std::string filename = "setupVars.conf";// file for unattended pihole install 

   	        std::ofstream outFile(filename);
	        if (!outFile) {
	    	    std::cerr << "Error opening file for writing: " << filename << std::endl;
	    	return 1;
	        }
	            outFile << "WEBPASSWORD=" <<passHash<<std::endl; 
		    std::string interface = configMap["pihole"].find("interface") != 
			    configMap["pihole"].end()?configMap["pihole"]
			    ["interface"]:"eth0";
	            outFile << "PIHOLE_INTERFACE=" <<interface<<std::endl; 
		    std::string ipv4 = configMap["pihole"].find("IPV4") != 
			    configMap["pihole"].end()?configMap["pihole"]
			    ["IPV4"]:"localhost";
	            outFile << "IPV4_ADDRESS=" <<ipv4<<std::endl; 
		    std::string ipv6 = configMap["pihole"].find("IPV6") != 
			    configMap["pihole"].end()?configMap["pihole"]
			    ["IPV6"]:"localhost";
	            outFile << "IPV6_ADDRESS=" <<ipv6<<std::endl; 
		    std::string logging = configMap["pihole"].find("logging") != 
			    configMap["pihole"].end()?configMap["pihole"]
			    ["logging"]:"yes";
	            outFile << "QUERY_LOGGING=" <<logging<<std::endl; 
		    std::string web_interface = configMap["pihole"].find("web_interface") != 
			    configMap["pihole"].end()?configMap["pihole"]
			    ["web_interface"]:"yes";
	            outFile << "INSTALL_WEB_INTERFACE=" <<web_interface<<std::endl; 
	            outFile << "LIGHTTPD_ENABLED=true"<<std::endl; 
	            outFile << "INSTALL_WEB_SERVER=true"<<std::endl; 
	            outFile << "DNSMASQ_LISTENING=single"<<std::endl; 
		    std::string dns1 = configMap["pihole"].find("dns1") != 
			    configMap["pihole"].end()?configMap["pihole"]
			    ["dns1"]:"8.8.8.8";
	            outFile << "PIHOLE_DNS_1="<<dns1<<std::endl; 
		    std::string dns2 = configMap["pihole"].find("dns2") != 
			    configMap["pihole"].end()?configMap["pihole"]
			    ["dns2"]:"8.8.8.8";
	            outFile << "PIHOLE_DNS_2="<<dns2<<std::endl; 
	            outFile << "DNS_FQDN_REQUIRED=true"<<std::endl; 
	            outFile << "DNS_BOGUS_PRIV=true"<<std::endl; 
	            outFile << "DNSSEC=false"<<std::endl; 
	            outFile << "TEMPERATUREUNIT=C"<<std::endl; 
	            outFile << "WEBUIBOXEDLAYOUT=traditional"<<std::endl; 
	            outFile << "API_EXCLUDE_DOMAINS="<<std::endl; 
	            outFile << "API_EXCLUDE_CLIENTS="<<std::endl; 
	            outFile << "API_QUERY_LOG_SHOW=all"<<std::endl; 
	            outFile << "API_PRIVACY_MODE=false"<<std::endl; 
	            outFile << "BLOCKING_ENABLED=true"<<std::endl; 
	            outFile << "CACHE_SIZE=10000"<<std::endl; 
	            outFile.close(); 

		    std::string command = "sudo mkdir -p /etc/pihole && ";
		    command.append("sudo mv ");
		    command.append(filename);
		    command.append(" /etc/pihole");
		    command.append(" && curl -L https://install.pi-hole.net | "
				    "sudo bash /dev/stdin --unattended ");
		    int result = system(command.c_str());

		    // Check the result
		    if(result == -1) {
			perror("system");
			return EXIT_FAILURE;
		    }
	}
	else{
		std::cout<<"Password is required exiting..."<<std::endl;
		exit(0);
	}
	return 0;
}

std::string SetupPihole::generateHash(const std::string inputStr){

    unsigned char hash[SHA256_DIGEST_LENGTH];
    const unsigned char* data = (const unsigned char*)inputStr.c_str();
    SHA256(data, inputStr.size(), hash);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();

}
