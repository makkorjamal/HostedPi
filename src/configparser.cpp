#include <iostream>
#include <fstream> 
#include <map>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include "configparser.h"

ConfigParser::ConfigParser(){

	// Create
}
ConfigParser::ConfigParser(const char* fname){
	filename = strdup(fname);
}

ConfigParser::~ConfigParser(){
	//Destrory
}
std::map<std::string, std::map<std::string, std::string>> ConfigParser::parse(){
    std::map<std::string, std::map<ast::string, std::string>> configMap;
    ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return configMap;
    }

    while (getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty() || line[0] == '#') {
            continue;
        }
        size_t equalPos = line.find('=');
        if (equalPos != string::npos) {
            std::string key = line.substr(0, equalPos);
            std::string value = line.substr(equalPos + 1);

            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            size_t dotPos = key.find('.');
            if (dotPos != string::npos) {
                std::string outerKey = key.substr(0, dotPos);
                std::string innerKey = key.substr(dotPos + 1);
                configMap[outerKey][innerKey] = value; // Store nested key-value
            } else {
                configMap[key][""] = value; // Store top-level key with an empty nested key
            }
        }
    }

    file.close();
    return configMap;
}
