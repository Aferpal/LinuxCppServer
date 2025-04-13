#pragma once
#include<iostream>
#include"Utilities.h"
#include"../Exceptions/IndexOutOfBoundsException.h"
class String{
    friend std::ostream& operator<<(std::ostream& os, const String& str){
        for(int i=0; i<str.length(); i++){
            os<<str[i];
        }
        return os;
    }
    private:
        char* data;
        int _length;
        int _size;
    public:
        String();
        String(const char* str);
        String(const String& str);
        String(String&& str);
        void operator=(const char* str);
        void operator=(const String& str);
        void operator=(String&& str);
        int length()const{return this->_length;}
        char operator[](int index)const;
        String operator+(const String& str)const;
        String operator+(const char* ptr)const;
        int findIndexOf(char)const;
        String substr(int start, int end)const;
        bool operator==(const String& str)const;
        bool operator==(const char*)const;
        bool operator!=(const String&)const;
        bool operator!=(const char*)const;
        bool operator<(const String&)const;
        bool operator<(const char* str)const;
        bool operator>(const String&)const;
        bool operator>(const char*)const;
        String& operator+=(const char*);
        String& operator+=(const String&);
        void normalise();
        operator const char*()const{return this->data;}
        ~String();
};