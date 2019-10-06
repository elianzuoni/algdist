// UDP wrapper
#ifndef UDP_H
#define UDP_H

#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>


namespace udp
{
	/*An instance of this class wraps a UDP socket.
	  Provides methods for sending and receiving messages with that socket.*/
	class UDP
	{
		public:
			/*Opens socket once and for all*/
			UDP(char *srcIP, int srcPort);
			/*Closes socket on destruction*/
			~UDP();
			
			/*Sends message to specified recipient.
			  Returns number of bytes sent, or -1.*/
			int send(void *buf, size_t len, char *destIP, int destPort);
			/*Blocks and listens for any incoming datagram.
			  Saves sender's info in srcIP and srcPort.
              Returns number of bytes received, or -1.*/
			int receive(void *buf, size_t len, char *srcIP, int *srcPort);
		
		private:
			/*The socket descriptor*/
			int fd;
	};
}

#endif