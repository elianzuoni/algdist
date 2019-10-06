#include "UDP.hpp"

using namespace udp;


UDP::UDP(char *srcIP, int srcPort){
	struct sockaddr_in srcAddr;
	
	if((this->fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&srcAddr, 0, sizeof(srcAddr));
	srcAddr.sin_family = AF_INET;
    inet_pton(AF_INET, srcIP, &(srcAddr.sin_addr));
    srcAddr.sin_port = htons(srcPort); 
	if(bind(this->fd, (const struct sockaddr *)&srcAddr, sizeof(srcAddr)) < 0){
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}
}

UDP::~UDP(){
	//close(this->fd);
}

int UDP::send(void *buf, size_t len, char *destIP, int destPort){
	struct sockaddr_in dstAddr;
	
	memset(&dstAddr, 0, sizeof(dstAddr));
	dstAddr.sin_family = AF_INET;
    inet_pton(AF_INET, destIP, &(dstAddr.sin_addr));
    dstAddr.sin_port = htons(destPort);
	
	return sendto(this->fd, buf, len, 0, (const struct sockaddr *) &dstAddr, sizeof(dstAddr)); 
}

int UDP::receive(void *buf, size_t len, char *srcIP, int *srcPort){
	struct sockaddr_in srcAddr;
	int ret;
	unsigned int addrLen;
	
	addrLen = sizeof(srcAddr);
	ret = recvfrom(this->fd, buf, len, 0, (struct sockaddr *) &srcAddr, &addrLen);
	
	inet_ntop(AF_INET, &(srcAddr.sin_addr), srcIP, INET_ADDRSTRLEN);
	*srcPort = ntohs(srcAddr.sin_port);
	
	return ret;
}