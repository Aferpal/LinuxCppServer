#pragma once
#define toHex(_port) ((_port>>8&0x00ff) + (_port<<8&0xff00))
#define getip0(ip) ( ip >> 24 ) & 0x0ff
#define getip1(ip) ( ip >> 16 ) & 0x0ff
#define getip2(ip) ( ip >> 8 ) & 0x0ff
#define getip3(ip) ( ip >> 0 ) & 0x0ff

int lengthOf(const char * str);
bool strcmp(const char* str1, const char* str2);
void strcpy(char* dest, const char* origin);
void strconcat(char* dest, const char* origin);
void strreverse(char*);