#ifndef __HTTPRES_H__
#define __HTTPRES_H__
#define HTTP202 "HTTP/1.1 202 GOOD"
#define HTTP200 "HTTP/1.1 200 OK\r\nX-Powered-By: Express\r\nAccess-Control-Allow-Origin: *\nAccess-Control-Allow-Headers: origin, x-requested-with, content-type\r\nContent-Type: application/json; charset=utf-8\r\n"
#define HTTP403 "HTTP/1.1 403 Transaction Error"
#define HTTP405 "HTTP/1.1 405 Method Not Allowed"
#endif