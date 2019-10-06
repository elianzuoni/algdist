#include <iostream>
#include <cstdlib>
#include "UDP.hpp"
#include <cstring>

using namespace std;
using namespace udp;

UDP setup(char *IP, int port);
int send(UDP sock);
int listen(UDP sock);

int main(int argc, char **argv){
	char cmd;
	
	if(argc != 3){
		cout << "Usage: " << argv[0] << " <myIP> <myPort>" << endl;
		exit(EXIT_FAILURE);
	}
	
	UDP sock = setup(argv[1], atoi(argv[2]));
	while(true){
		do{
			cout << "Input 'l' for listen, 's' for send" << endl;
			cin >> cmd;
		}while(cmd != 'l' && cmd != 's');
		
		if(cmd == 'l'){
			listen(sock);
		}
		else{
			send(sock);
		}
	}
	
	return 0;
}

UDP setup(char *IP, int port){
	UDP sock(IP, port);
	return sock;
}

int send(UDP sock){
	char ipAddr[20];
	char buf[200];
	int port, ret;
	
	cout << "Insert destination <IP> <port>: ";
	cin >> ipAddr >> port;
	cout << "Insert message: " << endl;
	cin >> buf;
	ret = sock.send(buf, strlen(buf)+1, ipAddr, port);
	cout << "Sent " << ret << " bytes" << endl << endl;
	
	return ret;
}
int listen(UDP sock){
	char buf[200];
	char srcIP[20];
	int srcPort, ret;
	
	ret = sock.receive(buf, sizeof(buf), srcIP, &srcPort);
	
	cout << "Received " << ret << " bytes by " << srcIP << ":" << srcPort << endl;
	cout << buf << endl << endl;
	
	return ret;
}