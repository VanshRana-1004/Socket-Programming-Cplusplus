#include<iostream>
#include<string>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

constexpr int PORT=8080;

int main(){
    
    int clientFd=socket(AF_INET,SOCK_STREAM,0);
    if(clientFd<0){
        throw std::runtime_error("Socket failed");
    }

    sockaddr_in serverAddr{};
    
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(PORT);

    inet_pton( AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if(connect( clientFd, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0){
        throw std::runtime_error("Connection failed");
    }

    std::string msg="Hello from C++ client";
    
    send(clientFd,msg.c_str(),msg.size(),0);

    char buffer[1024]{};

    int bytes=recv( clientFd, buffer, sizeof(buffer), 0);
    if(bytes>0){
       std::cout<<"Server replied : "<<buffer<<'\n';
    }

    close(clientFd);
}