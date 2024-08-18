#ifndef HH_PIHOLE_HH
#define HH_PIHOLE_HH

#include <map>
#include <string>

class SetupPihole{

	private:
		std::map<std::string, std::map<std::string,std::string>> configMap;

	public:

	SetupPihole();
	SetupPihole(std::map<std::string, std::map<std::string,std::string>> cmap);
	~SetupPihole();

	int install();
	std::string generateHash(const std::string password);
			
};
#endif
