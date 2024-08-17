#ifndef HH_UBNOUND_HH
#define HH_UBNOUND_HH

#include <map>
#include <string>

class SetupUnbound{

	private:
	map<string, map<string,string>> configMap;

	public:

	SetupUnbound();
	SetupUnbound(map<string, map<string,string>> cmap);
	~SetupUnbound();

	int install();
			
};
#endif
