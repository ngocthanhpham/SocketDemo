/*
 * ServerTCP.cpp
 *
 *  Created on: Nov 21, 2017
 *      Author: thanhpn
 */

#include "../header/ServerTCP.h"

ServerTCP::ServerTCP(int portNo) :
		newSokcfd(0), sockfd(0), portNo(portNo) {

	struct sockaddr_in servAddr = { 0 };
	struct sockaddr_in clientAddr = { 0 };

	if (portNo == 0) {
		error("ERROR, no port provided\n");
	}

	start(servAddr, portNo, clientAddr);
}

void ServerTCP::start(struct sockaddr_in servAddr, int portNo, struct sockaddr_in clientAddr) {

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) error("ERROR, cant open the socket\n");

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = INADDR_ANY; // automatically be filled with current host's IP address
	servAddr.sin_port = htons(portNo);

	if (bind(sockfd, (struct sockaddr*) (&servAddr), sizeof(servAddr)) < 0)
		error("ERROR, cant binding socket\n");
	else
		std::cout << "INFO, bind success socket: "
				  << inet_ntoa(servAddr.sin_addr)
				  << ":" << ntohs(servAddr.sin_port);

	listen(sockfd, 10);
	socklen_t clientLength = sizeof(clientAddr);
	newSokcfd = accept(sockfd, (struct sockaddr*) (&clientAddr), &clientLength);
	std::cout << "Accepted new connection: "
			  << inet_ntoa(clientAddr.sin_addr)
			  << ":" << ntohs(clientAddr.sin_port);
	send(sockfd, "From the server!\n", 13, 0);

	char buffer[512];
	memset(buffer, 0, sizeof(buffer));

	int n = read(newSokcfd, buffer, 512);

	if(n < 0) error("ERROR, reading from socket");

	std::cout <<  "Received: " << buffer;

}


ServerTCP::~ServerTCP() {
	stop();
}

void ServerTCP::error(const char *msg) {
	std::cout << msg << std::endl;
	exit(1);
}

void ServerTCP::stop() {
	close(newSokcfd);
	close(sockfd);

}
