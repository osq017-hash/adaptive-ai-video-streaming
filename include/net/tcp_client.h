#pragma once

#include <string>

class TcpClient{
public:
	TcpClient(const std::string& server_ip, int server_port);
	~TcpClient();

	bool connectToServer();
	bool sendMessage(const std::string& message);
	void closeConnection();

private:
	std::string server_ip_;
	int server_port_;
	int sock_fd_;
};
