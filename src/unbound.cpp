#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <setup.h>
#include "unbound.h"


SetupUnbound::SetupUnbound(){
}
SetupUnbound::SetupUnbound(map<string, map<string,string>> cmap){
	configMap = cmap;
}

SetupUnbound::~SetupUnbound(){
}

int SetupUnbound::install(){

	string dryinstall = "sudo apt install -y ";

	if(configMap["unbound"].find("port") != configMap["unbound"].end()) {
	    int port = stoi(configMap["unbound"]["port"]);
	    if(port == 5335){
		    std::cout << "Installing unbound at non SSL port; " <<port<< std::endl;
		    string command = dryinstall.append("unbound");
		    int result = system(command.c_str());

		    // Check the result
		    if(result == -1) {
			perror("system");
			return EXIT_FAILURE;
		    }else {
			    std::cout<< "Unbound installed"<<endl;
		    }
	    }else if(port == 443){
		    // make it from source to support ssl
		    std::cout<< "Setting up encrypted Unbound"<<endl;
			string command ="";
			    if (system("getent group unbound")) { //check if the group already exists
				command.append("sudo groupadd unbound");
				command.append(" && sudo adduser --system --no-create-home --disabled-login ");
				command.append("--disabled-password --ingroup unbound unbound");
			    }
			command.append(" git clone https://github.com/NLnetLabs/unbound.git");
			command.append(" && cd unbound");
			command.append(" && ./configure --prefix=/usr --sysconfdir=/etc --disable-static");
			command.append(" --with-pidfile=/run/unbound.pid --with-libnghttp2 --enable-systemd");
			command.append(" && make && sudo make install");
			command.append(" && sudo chown unbound:unbound /etc/unbound -R");

			int result1 = system(command.c_str());
			if (result1 != 0) {
			    std::cout<<"Invalid command 1"<<std::endl;
				return EXIT_FAILURE;
			    }

			command = "";
			command.append("sudo unbound-control-setup");
			//command.append(" && sudo unbound-anchor");
			int result2 = system(command.c_str());
			if (result2 != 0) {
			    std::cout<<"Invalid command 2"<<std::endl;
				return EXIT_FAILURE;
			    }
			command = "";
			command.append(" cd unbound");
			command.append(" && sudo systemctl enable contrib/unbound.socket");
			command.append(" && sudo systemctl enable contrib/unbound.service");
			command.append(" && sudo systemctl daemon-reload");
			command.append(" && sudo systemctl start unbound.socket");
			command.append(" && sudo systemctl start unbound.service");
			int result3 = system(command.c_str());
			if (result3 != 0) {
			    std::cout<<"Invalid command 3"<<std::endl;
				return EXIT_FAILURE;
			    }

			command = "sudo unbound-anchor 2>&1";  // error is not handled here 
			int result4 = system(command.c_str()); // due to some weird but with
							       // unbound-anchor but the 
							       // commands runs successfully
							       
			
	    }else{
		    std::cout<<"Invalid port"<<std::endl;
		    return EXIT_FAILURE;
	    }
	} else {

	    std::cout << "Please specify the unbound port" << std::endl;
	}
	return 0;
}
