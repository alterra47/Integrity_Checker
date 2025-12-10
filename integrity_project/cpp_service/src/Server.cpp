#include "Server.hpp"
#include <iostream>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
void Server::start(int port){
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd==0){
        std::cerr << "Socket creation failed!" << std::endl;
        return;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_fd, (struct sockaddr*) &address, sizeof(address))<0){
        std::cerr << "Bind failed! Port might be in use" << std::endl;
        return;
    }

    if (listen(server_fd, 3)<0)
    {
        std::cerr << "Listen failed!" << std::endl;
        return;
    }

    std::cout << "Service running on port " << port << " ..." << std::endl;

    while(true){
        int addrlen = sizeof(address);
        int new_socket = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen);

        if(new_socket<0){
            std::cerr << "Accept failed!" << std::endl;
            return;
        }

        char buffer[1024] = {0};
        read(new_socket, buffer, sizeof(buffer));
        std::string filepath(buffer);

        //format filepath to remove newlines
        filepath.erase(filepath.find_last_not_of(" \n\r\t")+1);
        std::cout << "Recieved request for : " << filepath << std::endl;

        std::string result = hasher.generate_hash(filepath);

        send(new_socket, result.c_str(), result.length(), 0);

        close(new_socket);
    }
}