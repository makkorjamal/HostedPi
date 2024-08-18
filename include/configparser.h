#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H
#include <iostream>
#include <map>
#include <string>

class ConfigParser{
	private:
		char* filename;
	public:
		ConfigParser();
		ConfigParser(const char* fname);
		~ConfigParser();
		std::map<std::string, std::map<std::string,std::string>> parse();
};
#endif
