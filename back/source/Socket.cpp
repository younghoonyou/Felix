#include "../lib/Socket.h"
#include "../lib/Response.h"
#include <iostream>
#include <vector>
void IP_Parsing(__uint32_t addr_){
    std::cout << "IP is ";
    __uint32_t bit = addr_; // IP is 32bits
    int sum = 0;
    for (int i = 0; i < 32; ++i)
    {
        if (bit & (1 << i))
            sum += (1 << (i % 8)); // read each 1 byte
        if (i == 31)
            std::cout << sum << '\n';
        else if ((i + 1) % 8 == 0)
            std::cout << sum << ".", sum = 0;
    }
}
void PostTransaction(char *buffer){
    int i = 0;
    while(buffer[i] != '{'){
        i++;
    }
    printf("request: %s\n", buffer+i);
}
void GetShowBalance(char *buffer){
    printf("request: %s\n", buffer);
}
void SendMsg(std::vector<std::pair<std::string,std::string>> &msg_,std::string &sendmsg){
    sendmsg += "HTTP/1.1 200 OK\r\n";
    sendmsg += "X-Powered-By: Express\r\n";
    sendmsg += "Access-Control-Allow-Origin: *\n";
    sendmsg += "Access-Control-Allow-Headers: origin, x-requested-with, content-type\r\n";
    sendmsg += "Content-Type: application/json; charset=utf-8\r\n";
    std::string payload = "{";
    for (auto &tmp : msg_)
    {
        payload += '"';
        payload += tmp.first;
        payload += '"';
        payload += ':';
        payload += tmp.second;
        payload += ", ";
    }
    payload.pop_back();
    payload.pop_back();
    payload += '}';
    sendmsg += "Content-Length: ";
    sendmsg += std::to_string(payload.length());
    sendmsg += "\r\n";
    sendmsg += "Date: Sun, 13 Nov 2022 19 : 08 : 57 GMT\r\n";
    sendmsg += "Connection: close\r\n\r\n";
    sendmsg += payload;
}
void Socket::Server::Write(std::string msg_)
{
    this->msg = msg_;
    write(socket_, msg.c_str(), msg_.length());
}

void Socket::Server::Read()
{
    int Read_ret = read(socket_, (void *)msg.c_str(), sizeof(msg));
    if (Read_ret == 0)
        Close();
    else if (Read_ret != -1)
        std::cout << "Client : " << msg << '\n';
}

void Socket::Server::Bind()
{
    int Bind_ret = bind(socket_, (sockaddr *)&addr, sizeof(addr)); // Bind return
    if (Bind_ret == -1)
        Error_Print(Bind_Err);
    else
        Correct_Print(Bind_Res);
}

void Socket::Server::Listen(int size)
{
    int Listen_ret = listen(socket_, size); // wait queue size
    if (Listen_ret == -1)
        Error_Print(Listen_Err);
    else
        Correct_Print(Listen_Res);
}

void Socket::Server::Accept()
{
    while (1)
    {
        unsigned int Clt_size = sizeof(clt_sock);
        int Accept_ret = accept(socket_, (sockaddr *)&clt_sock, &Clt_size);
        if (Accept_ret == -1){
            Error_Print(Accept_Err);
        }
        else
        {
            Correct_Print(Accept_Res);
            IP_Parsing(clt_sock.sin_addr.s_addr);
        }

        const uint BUFFER = 100000000;
        char *buffer = new char[BUFFER + 1];
        std::vector<std::pair<std::string, std::string>> vec;
        vec.push_back({"name","Hoons"});
        vec.push_back({"age", "25"});

        std::string sendmsg = "";
        SendMsg(vec,sendmsg);

        auto bytesRead = recv(Accept_ret, buffer, BUFFER, 0);
        buffer[bytesRead] = 0;
        if (buffer[0] == 'G')
        {
            GetShowBalance(buffer);
        }
        else if (buffer[0] == 'P')
        {
            PostTransaction(buffer);
        }
        Send(Accept_ret, sendmsg);
        close(Accept_ret);
        delete[] buffer;
    }
}

void Socket::Server::Close()
{
    Correct_Print(Close_Res);
    close(socket_);
}

void Socket::Server::Send(int target_socket, std::string msg)
{
    send(target_socket, (void *)msg.c_str(), msg.length(), 0);
}

void Socket::Client::Close()
{
    close(socket_);
}

void Socket::Client::Write(std::string msg_)
{
    this->msg = msg_;
    write(socket_, msg.c_str(), sizeof(msg));
}

void Socket::Client::Read()
{
    int Read_ret = read(socket_, (void *)msg.c_str(), sizeof(msg));
    if (Read_ret == 0)
        Close();
    else if (Read_ret != -1)
        std::cout << "Server : " << msg << '\n';
}

void Socket::Client::Connect()
{
    int Connect_ret = connect(socket_, (sockaddr *)&addr, sizeof(addr));
    if (Connect_ret == -1)
        Error_Print(Connect_Err);
    else
        Correct_Print(Connect_Res);
}