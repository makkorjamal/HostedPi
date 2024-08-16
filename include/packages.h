#ifndef HH_PACKAGES_HH
#define HH_PACKAGES_HH
#include <map>
#include <iostream>

using namespace std;
class InstallPackages{
	private:
		map<string, map<string,string>> configMap;
	public:
		InstallPackages();
		InstallPackages(map<string, map<string,string>> cmap);
		~InstallPackages();
		int install();
};
#endif
