#ifndef __BALANCE__
#define __BALANCE__
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cstddef>
#define NUMBER 100
#define EXITFLAG -1
#define BAD 5
#define CORRECT 7
typedef enum { ERROR = -1, SMALL, LARGE, EQUAL, SUCCESS } status;
typedef int coins;
static int call_count = 0;
static int __coin[100];
void initialize(int p);
int balance(int a[], int b[]);
#endif
//컴파일 :
//g++ main.cpp Coin.cpp balance.c
