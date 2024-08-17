#ifndef HH_UPDATEREPO_HH
#define HH_UPDATEREPO_HH
#include <iostream>
#include <cstdlib> 
#include <string>
using namespace std;

class Setup{

	    // Update package lists
    public:
    static void checkCancel(int signal);
    Setup();
    ~Setup();

    int update();
    int installEssentials();
    int installRequirements(std::map<string, map<string,string>> map);
};
#endif
