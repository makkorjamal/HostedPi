#ifndef HH_PACKAGES_HH
#define HH_PACKAGES_HH
#include <map>
#include <iostream>

using namespace std;
class InstallPackages{
	private:
		map<string, map<string,string>> configMap;
		enum ColorCode {
		    RESET = 0,
		    GREEN = 32,
	            CYAN = 36
		    };
	public:
		InstallPackages();
		InstallPackages(map<string, map<string,string>> cmap);
		~InstallPackages();
		int install();
		void startInstall(const std::string& softwareName);
		void endInstall(const std::string& softwareName);
		std::string getColor(ColorCode color) const;
};
#endif
