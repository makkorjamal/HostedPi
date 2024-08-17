#ifndef HH_PIHOLE_HH
#define HH_PIHOLE_HH

#include <map>
#include <string>

class SetupPihole{

	private:
	map<string, map<string,string>> configMap;

	public:

	SetupPihole();
	SetupPihole(map<string, map<string,string>> cmap);
	~SetupPihole();

	int install();
	std::string generateHash(std::string password);
			
};
#endif
