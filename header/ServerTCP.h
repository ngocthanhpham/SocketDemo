/*
 * ServerTCP.h
 *
 *  Created on: Nov 21, 2017
 *      Author: thanhpn
 */

#ifndef SERVERTCP_H_
#define SERVERTCP_H_
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>

class ServerTCP {
public:
	ServerTCP(int);
	virtual ~ServerTCP();

private:
	int sockfd;
	int newSokcfd;
	int portNo;

	void error(const char*);
	void start(struct sockaddr_in servAddr, int portNo, struct sockaddr_in clientAddr);
	void stop();
};

#endif /* SERVERTCP_H_ */
