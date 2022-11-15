#include <iostream>
#include "Restaurant.h"
#include "Customer.h"
#include "Transaction.h"
#include "Socket.h"
#include <mysql/mysql.h>

Socket::Server sock_server(8888);
MYSQL *conn;

void Network(){
    sock_server.Bind();
    sock_server.Listen(5);
    sock_server.Accept();
    sock_server.Close();
}

int main(){

    Restaurant *JanMoJib = Restaurant::GetInstance("JanMoJib");
    JanMoJib->GetRestaurantAccount();
    Customer *Hoon = new Customer("Hoon", "12345", 1000);

    char *server = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "felix";
    
    char *query = "create database felix;";
    std::string user_queryt = "insert into user values ";
    user_queryt += '(';
    user_queryt += (Hoon->acc);
    user_queryt += ', ';
    user_queryt += '\'';
    user_queryt += (Hoon->userId);
    user_queryt += '\'';
    user_queryt += ', ';
    user_queryt += std::to_string(Hoon->balance);
    user_queryt += ')';
    // std::string restaurant = "insert into restaurant values ";

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        std::cout << mysql_error(conn);
        exit(1);
    }
    mysql_query(conn, user_queryt.c_str());
    // mysql_query(conn, query);
    Network();
    conn = NULL;
    delete JanMoJib;
    delete Hoon;
    return 0;
}