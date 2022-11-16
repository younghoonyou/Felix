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
void PostTransaction(char *buffer, std::map<std::string, std::string> &m)
{
    int i = 0;
    while (buffer[i]!='{')
    {
        i++;
    }

    std::string str(buffer + i);
    str.erase(str.begin());
    str.pop_back();
    std::istringstream stream(str);
    std::string buff;
    std::cout << str<<'\n';
    while (std::getline(stream, buff, ','))
    {
        //ex buff -> "name":"Hoon"
        std::string key = "", val = "";
        int i = 1;
        while(buff[i]!='\"'){
            key += buff[i];
            i++;
        }
        i += 3;
        while (buff[i] != '\"')
        {
            val += buff[i];
            i++;
        }
        m[key] = val;
    }
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

        std::string sendmsg = "";

        auto bytesRead = recv(Accept_ret, buffer, BUFFER, 0);
        buffer[bytesRead] = 0;
        std::cout<<buffer<<'\n';
        MYSQL_RES *res = nullptr; // Result
        MYSQL_ROW row = nullptr;
        if (buffer[0] == 'G') // Get Method
        {
            mysql_query(con, "SELECT balance FROM user WHERE name = 'Hoon';");
            res = mysql_store_result(con);
            row = mysql_fetch_row(res);
            m["balance"] = row[0];
            SendMsg(m, sendmsg);
            Send(Accept_ret, sendmsg);
        }
        else if(buffer[0] =='P')// Post Method
        {
            PostTransaction(buffer,m);
            std::string query = "select balance from user where name=";
            query += '\'';
            query += m["user"];
            query += '\'';
            query += ';';
            mysql_query(con, query.c_str());
            res = mysql_store_result(con);
            row = mysql_fetch_row(res);
            if(!row){
                sendmsg += HTTP403;
                Send(Accept_ret, sendmsg);
            }
            else{
                std::cout << row[0] << '\n';
                if (m["user"] == "" || m["restaurant"] == "" || m["amount"] == "" || atoi(row[0]) < stoi(m["amount"]))
                {
                    sendmsg += HTTP403;
                }
                else
                {
                    std::string sendQuery = "update restaurant set balance=balance+";
                    sendQuery += m["amount"];
                    sendQuery += " where name='";
                    sendQuery += m["restaurant"];
                    sendQuery += "';";
                    mysql_query(con, sendQuery.c_str());
                    std::string sendMoney = "update user set balance=balance-";
                    sendMoney += m["amount"];
                    sendMoney += " where name='";
                    sendMoney += m["user"];
                    sendMoney += "';";
                    mysql_query(con, sendMoney.c_str());
                    sendmsg += HTTP202;
                }
                Send(Accept_ret, sendmsg);
            }
        }
        close(Accept_ret);
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