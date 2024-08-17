#include <iostream>
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

SetupPihole::SetupPihole(map<string, map<string,string>> cmap){
	configMap = cmap;
}

SetupPihole::~SetupPihole(){
}

int SetupPihole::install(){

	if(configMap["pihole"].find("password") != configMap["pihole"].end()) {
		//pass is read from the conf file
		firstHash = generateHash(pass);
		passHash = generateHash(firstHash);
	    }
	else{
		std::<<cout<<"Password is necessary"<<endl;
	}
}

std::string generateHash(const string& inputStr){

    unsigned char hash[SHA256_DIGEST_LENGTH];
    const unsigned char* data = (const unsigned char*)inputStr.c_str();
    SHA256(data, inputStr.size(), hash);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();

}
