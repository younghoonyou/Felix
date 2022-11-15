#pragma once
#include <sys/socket.h>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
namespace Socket{
class Socket{
protected:
    int port;
    std::string msg;
    int socket_;
    struct sockaddr_in addr;
public:
    Socket(){
        memset(&addr,0,sizeof(addr));//init
        addr.sin_family = AF_INET;   //TCP/IP protocol
        msg = "";
        port = 8000;// default
        socket_ = socket(PF_INET, SOCK_STREAM, 0); // IPv4 , TCP : SOCK_STREAM , protocal
        addr.sin_port = htons(port);
    }
    Socket(int port_){
        memset(&addr, 0, sizeof(addr)); // init
        addr.sin_family = AF_INET;      // TCP/IP protocol
        msg = "";
        port = port_;
        socket_ = socket(PF_INET, SOCK_STREAM, 0);// IPv4 , TCP : SOCK_STREAM , protocal
        addr.sin_port = htons(port);
    }
    virtual void Read() = 0;
    virtual void Write(std::string msg_) = 0;
    virtual void Close() = 0;
};

    class Server : public Socket{
        private:
            struct sockaddr_in clt_sock;
        public:
            Server() : Socket(){
                addr.sin_addr.s_addr = htonl(INADDR_ANY);//IP address 4 bytes structure
            }
            Server(int port_) : Socket(port_){
                addr.sin_addr.s_addr = htonl(INADDR_ANY);
            }
            void Read();
            void Write(std::string msg_);
            void Accept();
            void Bind();
            void Listen(int size);
            void Close();
            void Send(int target_socket, std::string msg);
    };
    class Client : public Socket{
        private:
            std::string ip;
        public:
            Client() : Socket(){

            }
            Client(std::string& IP) : Socket(){
                ip = IP;
                addr.sin_addr.s_addr = inet_addr(ip.std::string::c_str());//casting string -> char*
            }
            Client(int port_,std::string &IP) : Socket(port_){
                ip = IP;
            }
            void Read();
            void Write(std::string msg_);
            void Close();
            void Connect();
    };
}