#ifndef HH_UPDATEREPO_HH
#define HH_UPDATEREPO_HH
#include <iostream>
#include <cstdlib> 

class Setup{

	    // Update package lists
    public:
    static void checkCancel(int signal);
    Setup();
    ~Setup();

    int update();
    int installEssentials();
    int installRequirements();
};
#endif
