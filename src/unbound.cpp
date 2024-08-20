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
			command.append(" && cp ../resources/unbound.conf doc/example.conf");
			command.append(" && make && sudo make install");
			command.append(" && sudo chown unbound:unbound /etc/unbound -R");


			int result1 = system(command.c_str());
			if (result1 != 0) {
			    std::cout<<"Invalid command 1"<<std::endl;
				return EXIT_FAILURE;
			    }

			command = "";
			command.append("sudo unbound-control-setup");
			int result2 = system(command.c_str());
			if (result2 != 0) {
			    std::cout<<"Invalid command 2"<<std::endl;
				return EXIT_FAILURE;
			    }
			command = "";
			command.append(" cd unbound");
			command.append(" && sudo cp contrib/unbound.socket /usr/lib/systemd/system");
			command.append(" && sudo cp contrib/unbound.service /usr/lib/systemd/system");
			command.append(" && sudo systemctl daemon-reload");
			command.append(" && sudo systemctl enable unbound.socket");
			command.append(" && sudo systemctl enable unbound.service");
			command.append(" && sudo systemctl start unbound.socket");
			command.append(" && sudo systemctl start unbound.service");
			std::string ftl_serv = "systemctl is-active --quiet pihole-FTL";
			if (system(ftl_serv.c_str()) == 0) { // check if pihole 
							     // dns resolver is running in the system
				// Service is running, stop it
				std::string scommand = "sudo systemctl stop pihole-FTL";
				system(scommand.c_str());
				std::cout << "Service " << "pihole-FTL"  << " stopped." << std::endl;
				int result3 = system(command.c_str());
				if (result3 != 0) {
				    std::cout<<"Invalid command 3"<<std::endl;
					return EXIT_FAILURE;
				    }
				std::string ecommand = "sudo systemctl start pihole-FTL"; // restart it afterwards
				system(ecommand.c_str());
			    }
			else{
				int result3 = system(command.c_str());
				if (result3 != 0) {
				    std::cout<<"Invalid command 3"<<std::endl;
					return EXIT_FAILURE;
				    }
			}

			command = "sudo unbound-anchor 2>&1";  // error is not handled here 
			system(command.c_str()); 	       // due to some weird bug with
							       // unbound-anchor but the 
							       // commands runs successfully
		
	    }
	    else{
		    std::cout<<"Invalid port"<<std::endl;
		    return EXIT_FAILURE;
	    }
	} else {

	    std::cout << "Please specify the unbound port" << std::endl;
	}
        if(configMap["unbound"].find("autohints") != configMap["unbound"].end()){
	    if(configMap["unbound"]["autohints"] == "True"){
		    std::string command = "";
		    command.append(" sudo systemctl enable resources/get-root-hints.timer");
		    command.append(" && sudo systemctl enable resources/get-root-hints.service");
		    command.append(" && sudo systemctl daemon-reload");
		    command.append(" && sudo systemctl start get-root-hints.timer");
		    command.append(" && sudo systemctl start get-root-hints.service");
		    int result5 = system(command.c_str());
		    if (result5 != 0) {
			std::cout<<"Invalid command 5"<<std::endl;
			return EXIT_FAILURE;
			}
		    else{
			    //inline change of unbound.conf
			    std::string reload = "sudo sed -i -e 's/#root-hints/root-hints/' /etc/unbound/unbound.conf";
			    reload.append(" && sudo service unbound reload");
			    system(reload.c_str());
		    }
	    }
    }						       
	return 0;
}
