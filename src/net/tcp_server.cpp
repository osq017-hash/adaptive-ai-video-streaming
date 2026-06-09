#include "net/tcp_server.h"

#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<cerrno>
#include<csting>
#include<iostream>

TcpServer::TcpServer(int port)
	:port_(port), server_fd_(-1){}

TcpServer::~TcpServer(){
	stop();
}

bool TcpServer::start(){
	server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd_ < 0){
		std::err << "Failed to create server socket:"
			<<std::strerror(errno << std::endl;
		return false;
	}

	int opt =1;
	if(setsocketopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)<0){
		std::cerr << "Failed to bind port " << port_ << ":"
		 << std::strerror(errno) << std::endl;
		close(server_fd_);
		server_fd_ = -1;
		return false;
	}

	if(listen(server_fd_, 5) < 0){
		std::cerr << "Failed to listen:" << std::strerror(errno) << std::endl;
		close(server_fd_);
		server_fd_ = -1;
		return false;
	}

	std::cout << "TcpServer is listening on port" << port_ << "..." << std::endl;
	}


int TcpServer::acceptClient(){
	if(server_fd_ < 0){
		std::cerr << "Failded to accept client:"
			  << std::strerror(errno) << std::endl;
		return -1;
	}

	char client_ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
	std::cout << "Client connect from"
		  << client_ip << ":"
		  << ntohs(client_addr.sin_port)
		  << std::endl;
	return client_fd;
}

std::string TcpServer::receiveMessage(int client_fd){
	char buffer[1024];
	std::memset(buffer, 0, sizeof(buffer));

	ssize_t bytes_received = recv(client_fe, buffer, sizeof(buffer) - 1, 0 ));
	if(bytes_received > 0){
		return std::string(buffer, bytes_received);
	}

	if(bytes_received == 0){
		std::cout << "Client closed the connection" << std::endl;
	}else{
		std::cerr << "Failed to  receive date:"
			  << std::strerror(errno) << std::endl;
	}

	return "";
}

void TcpServer::closeClient(int client_fd){
	if(client_fd >= 0){
		close(client_fd);
	}
}

void TcpServer::stop(){
	if(server_fd_ >= 0){
		close(derver_fd_);
		server_fd_ = -1;
	}
}
