#pragma once
#define Socket_Err "Socket Error"
#define Bind_Err "Bind Error"
#define Listen_Err "Listen Error"
#define Accept_Err "Accept Error"
#define Read_Err "Read Error"
#define Write_Err "Writte Error"
#define Close_Err "Close Error"
#define Connect_Err "Connect Error"

#define Socket_Res "Socket Create"
#define Bind_Res "Bind Correct"
#define Listen_Res "Listen Correct"
#define Accept_Res "Accept Correct"
#define Read_Res "Read Correct"
#define Write_Res "Writte Correct"
#define Close_Res "Close Correct"
#define Connect_Res "Connect Correct"
#include <iostream>
void Error_Print(const char *err);
void Correct_Print(const char *res);