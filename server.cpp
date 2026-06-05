#include <bits/stdc++.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

constexpr int PORT=8080;

int main(){

    int serverFd=socket(AF_INET,SOCK_STREAM,0);
    if(serverFd<0){
        throw std::runtime_error("Failed to create socket");
    }
    else{
        cout<<"Socket created successfully.\n";
    }

    sockaddr_in address{};
    
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);

    int opt=1;

    setsockopt(serverFd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    if(bind(serverFd,reinterpret_cast<sockaddr*>(&address),sizeof(address)) < 0){
        throw std::runtime_error("Bind failed");
    }

    if(listen(serverFd,5) < 0){
        throw std::runtime_error("Listen failed");
    }

    std::cout<<"Listening on port : "<<PORT<<'\n';

    sockaddr_in clientAddress{};
    socklen_t clientLen=sizeof(clientAddress);

    int clientFd=accept(serverFd, reinterpret_cast<sockaddr*>(&clientAddress), &clientLen);
    if(clientFd<0){
        throw std::runtime_error("Accept failed");
    }

    char buffer[1024]{};

    int bytes=recv(clientFd,buffer,sizeof(buffer),0);
    if(bytes>0){
        cout<<"Client says : "<<buffer<<'\n';
        string reply="Hello from C++ server";
        send(clientFd,reply.c_str(),reply.size(),0);
    }

    close(clientFd);
    close(serverFd);

}