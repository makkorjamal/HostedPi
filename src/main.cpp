#include <iostream>
#include <map>
#include <string>
#include <configparser.h>
#include <packages.h>

int main(){

	ConfigParser parser("config.cfg");
        auto configMap = parser.parse();
	InstallPackages packages(configMap);
	packages.install();
	return 0;
}
