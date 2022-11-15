#include "../lib/Socket.h"
#include "../lib/Response.h"
#include "../lib/HttpResponse.h"
#include "../lib/Transaction.h"
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <cctype>
#include <json/json.h>
#include <mysql/mysql.h>
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
void String_Parsing(char *buffer, std::map<std::string, std::string> &m)
{
    std::istringstream stream(buffer);
    std::string buff;
    std::string sendmsg;
    int cnt = 0;
    while (getline(stream, buff, ','))
    {
        // if(isalnum(buff[0])){
        //     cnt++;
        //     if(cnt&1){

        //     }
            // std::cout << buff << '\n';
            std::istringstream buffstream(buff);
            std::string buffs;
            while(getline(buffstream,buffs,'"')){
                if(buffs[0] == ' ' || buffs[0] == '{' || buffs[0] == '}' || buffs[0] == ':') continue;
                std::cout << buffs;
            }
            // }
    }
}
void SendMsg(std::map<std::string, std::string> &hash, std::string &sendmsg)
{
    sendmsg += HTTP200;
    std::string payload = "{";
    for (auto &tmp : hash)
    {
        payload += '"';
        payload += tmp.first;
        payload += '"';
        payload += " : ";
        payload += '"';
        payload += tmp.second;
        payload += '"';
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
void PostTransaction(char *buffer){
    int i = 0;
    while(buffer[i] != '{'){
        i++;
    }
    std::cout << buffer + i << '\n';
    // std::map<std::string, std::string> m;
    //     // m["user"] = "Handsome";
    // // String_Parsing(buffer + i,m);
    // if (m["user"] == "" || m["restaurant"] == "" || m["amount"] == ""){
    //     // send(target, HTTP403,sizeof(HTTP403),0);
    // }
    // // else if(){

    // // }
    // else{
    //     std::string sendmsg = "";
    //     SendMsg(m, sendmsg);
    //     // Send(target, sendmsg);
    // }
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

void Socket::Server::Accept(MYSQL **conn)
{
    while (1)
    {
        MYSQL *con = (*conn);
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
        std::map<std::string, std::string> m;
        // m["name"] = "Hoon";
        // m["age"] = "25";

        std::string sendmsg = "";
        // SendMsg(m,sendmsg);

        auto bytesRead = recv(Accept_ret, buffer, BUFFER, 0);
        std::cout << buffer << '\n';
        buffer[bytesRead] = 0;

        MYSQL_RES *res = nullptr; // Result
        MYSQL_ROW row;
        std::cout << buffer;
        if (buffer[0] == 'G') // Get Method
        {
            mysql_query(con, "SELECT balance FROM user WHERE name = 'Hoon';");
            res = mysql_store_result(con);
            row = mysql_fetch_row(res);
            std::cout << row[0];
            m["balance"] = row[0];
            SendMsg(m, sendmsg);
            Send(Accept_ret, sendmsg);
        }
        else if (buffer[0] == 'P') // Post Method
        {
            PostTransaction(buffer);
            Send(Accept_ret, sendmsg);
        }
        close(Accept_ret);
        // delete res;
        delete[] buffer;
    }
}








/*--------------------SERVER-------------------------*/





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