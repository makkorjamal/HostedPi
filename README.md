# HsotedPi 
A software to install different hosted services on a raspberrypi
like unbound pihole owncloud etc..
These installs are dockerless and they are done the traditional 
way

## why?
This is mostly for fun, but many tutorials on installing various self-hosted services are often incomplete and hard to follow. 
Additionally, those interested in self-hosting can find it frustrating to search for different methods to install various packages.

## how does it work?
This software reads different hosted services from a  config file
"config.cfg" and install them based on these requirements

To build the project, you need to have the OpenSSL development libraries installed. You can install them using the following commands:

### For Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install libssl-dev git
git clone https://github.com/makkorjamal/HostedPi.git && cd HostedPi
make
./main
