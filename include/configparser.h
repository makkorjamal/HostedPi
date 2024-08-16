#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H
#include <iostream>
#include <map>
#include <string>
using namespace std;
class ConfigParser{
	private:
		char* filename;
	public:
		ConfigParser();
		ConfigParser(const char* fname);
		~ConfigParser();
		map<string, map<string,string>> parse();
};
#endif
