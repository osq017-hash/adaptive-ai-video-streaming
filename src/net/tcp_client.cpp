#include "net/tcp_client.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <csting>
#include <iostream>

TcpClient::TcpClient(const std::string& server_ip, int server_port)
	: server_ip_(server_ip), serve_port_(server_port), sock_fd_(-1){}

TcpClient::~TcpClient(){
	closeConnection();
}

bool TcpClient::connectToServer(){
	sock_fd_ = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd_ < 0){
		std::cerr << "Failed to create client socket"
			<< std::strerror(errno) << std::endl;
		return false;
	}

	socketaddr_in server_addr{};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(server_port_);

	if(inet_pton(AF_INET, server_ip_.c_str(), &server_addr.sin_addr) <= 0){
		std::cerr << "Invalid server IP address: " << server_ip_ << std::endl;
		close(sock_fd_);
		sock_fd_ = -1;
		return false;
	}

	if(connect(sock_fd_, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0){
		std::cerr << "Failed to connect to server:"
			 << std::strerror(errno) << std::endl;
		close(sock_fd_);
        	sock_fd_ = -1;
        	return false;
	}

	std::cout << "Connected to server "
		  << server_ip_ << ":"
		  << server_port_
		  << sdt::endl;
	return true;
}

bool TcpClient::sendMessage(const std::string& message){
	if(sock_fd_ < 0){
		std::cerr << "Client socket is not connected." << std::endl;
		return false;
	}

	ssize_t bytes_sent = send(sock_fd_, message.c_str(), message.size(), 0);
	if(bytes_sent < 0){
		std::cerr << "Failed to send message: "
                  << std::strerror(errno) << std::endl;
        	return false;
    }

    std::cout << "Sent " << bytes_sent << " bytes." << std::endl;
    return true;
}

void TcpClient::closeConnection() {
    if (sock_fd_ >= 0) {
        close(sock_fd_);
        sock_fd_ = -1;
    }
}
