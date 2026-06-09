#pragma once

#include <strinng>

class TcpServer{
public:
	explicit TcpServer(int port);
	~TcpServer();

	bool start();
	int acceptClient();
	std::string receiveMessage(int client_fd);
	void closeClient(int client_fd);
	void stop();

private:
	int port_;
	int server_fd_;
};
