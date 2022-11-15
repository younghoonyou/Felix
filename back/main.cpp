#include <iostream>
#include "./lib/Restaurant.h"
#include "./lib/Customer.h"
#include "./lib/Transaction.h"
#include "./lib/Socket.h"
#include <mysql/mysql.h>

Socket::Server sock_server(8888);

void Network(){
    sock_server.Bind();
    sock_server.Listen(5);
    sock_server.Accept();
    sock_server.Close();
}
void Restaurant_queryInit(Restaurant **res,std::string &restaurnt_query){
    restaurnt_query += '(';
    restaurnt_query += ((*res)->acc);
    restaurnt_query += ',';
    restaurnt_query += '\'';
    restaurnt_query += ((*res)->RestId);
    restaurnt_query += '\'';
    restaurnt_query += ',';
    restaurnt_query += std::to_string((*res)->GetRestaurantBalance());
    restaurnt_query += ");";
}
void Customer_queryInit(Customer **cus,std::string &user_query){
    user_query += '(';
    user_query += ((*cus)->acc);
    user_query += ',';
    user_query += '\'';
    user_query += ((*cus)->userId);
    user_query += '\'';
    user_query += ',';
    user_query += std::to_string((*cus)->balance);
    user_query += ')';
}
void DB_Connect(MYSQL *conn){
    std::string server = "localhost";
    std::string user = "root";
    std::string password = "";
    std::string database = "felix";    
    if (!mysql_real_connect(conn, server.c_str(), user.c_str(), password.c_str(), database.c_str(), 0, NULL, 0))
    {
        std::cout << mysql_error(conn);
        exit(1);
    }
}
int main(){

    Restaurant *JanMoJib = Restaurant::GetInstance("JanMoJib","11111",0); // Restaurant Info
    Customer *Hoon = new Customer("Hoon", "12345", 1000);                 // User Info

    MYSQL *conn;
    conn = mysql_init(NULL);

    std::string user_query = "insert into user values ";            // User initial
    std::string restaurnt_query = "insert into restaurant values "; // Restaurant initial

    Customer_queryInit(&Hoon,user_query);
    Restaurant_queryInit(&JanMoJib,restaurnt_query);

    DB_Connect(conn); // MYSQL DB connection

    mysql_query(conn, user_query.c_str());      // User query string
    mysql_query(conn, restaurnt_query.c_str()); // Restaurant query string

    Network(); // Socket HTTP TCP/IPv4 

    conn = NULL;
    delete JanMoJib;
    delete Hoon;
    return 0;
}