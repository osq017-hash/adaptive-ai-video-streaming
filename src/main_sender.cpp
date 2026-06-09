#include "net/tcp_client.h"

#include <iostream>
#include <string>

int main() {
    TcpClient client("127.0.0.1", 9000);

    if (!client.connectToServer()) {
        std::cerr << "Failed to connect to receiver." << std::endl;
        return 1;
    }

    std::string message = "Hello from TcpClient. Network module is working.";

    if (!client.sendMessage(message)) {
        std::cerr << "Failed to send message." << std::endl;
        return 1;
    }

    client.closeConnection();

    return 0;
}
