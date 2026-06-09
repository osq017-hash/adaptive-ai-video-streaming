#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

int main(){
	const int port = 9000;

	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd < 0){
		std::cerr << "Failed to create socket." << std::endl;
		return 1;
	}

	int opt = 1;
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	sockaddr_in server_addr{};
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);
	
	if(bind(server_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0){
	std::cerr<<"Failed to bind port" << port << std::endl;
	close(server_fd);
	return 1;
	}

	if(listen(server_fd, 5) < 0){
		std::cerr << "Falied to listen." << std::endl;
		close(server_fd);
		return 1;
	}

	std::cout << "Rceiver is listening on port" << port << "..." << std::endl;
	sockaddr_in client_addr{};
	socklen_t client_len = sizeof(client_addr);

	int client_fd = accept(server_fd, reinterpret_cast<sockaddr*>(&client_addr), &client_len);
	if(client_fd < 0){
		std::cerr << "Failed to accept client." << std::endl;
		close(server_fd);
		return 1;
	}

	std::cout << "Sender connected." << std::endl;

	char buffer[1024];
	std::memset(buffer, 0, sizeof(buffer));

	ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
	if(bytes_received > 0){
		std::cout << "Received message:" << buffer << std::endl;
	}else{
		std::cout << "No data received." << std::endl;
	}

	close(client_fd);
	close(server_fd);
	return 0;
}
