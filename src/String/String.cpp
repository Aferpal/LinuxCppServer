#include"String.h"

String::String(){
    this->data=nullptr;
    this->_length=0;
    this->_size=0;
}
String::String(const char* str){
    this->_length=lengthOf(str);
    this->data=new char[this->_length+1]{0};
    this->_size=this->_length;
    strcpy(this->data, str);
}

String::String(const String& str){
    this->data=new char[str._length+1]{0};
    strcpy(this->data, str.data);
    this->_length=str._length;
    this->_size=str._length;
}

String::String(String&& str):data{str.data}, _length{str._length}, _size{str._size}{
    str.data=nullptr;
}

void String::operator=(const char* str){
    if(this->data){delete[]this->data;}
    this->_length=lengthOf(str);
    this->_size=this->_length;
    this->data=new char[this->_length+1]{0};
    strcpy(this->data, str);
}

void String::operator=(const String& str){
    if(this->data){delete[] this->data;}
    this->_length=str._length;
    this->_size=str._size;
    this->data= new char[this->_length+1]{0};
    strcpy(this->data, str.data);
}

void String::operator=(String&& str){
    if(this->data){delete[]this->data;}
    this->data=str.data;
    str.data=nullptr;
    this->_length=str._length;
    this->_size=str._size;
}

char String::operator[](int i)const{
    if(i>=_length || i<(_length*-1)){
        IndexOutOfBoundsEXception ex;
        throw ex;
    }
    return i>=0?*(data+i):*(data+_length+i);
}
String String::operator+(const String& str)const{
    char * temporal= new char[this->_length+str._length+1]{0};
    strcpy(temporal, this->data);
    strconcat(temporal, str.data);
    String str2=temporal;
    delete[]  temporal;
    return str2;
}
String String::operator+(const char* str)const{
    char * temporal= new char[this->_length+lengthOf(str)+1]{0};
    strcpy(temporal, this->data);
    strconcat(temporal, str);
    String str2=temporal;
    delete[]  temporal;
    return str2;
}
bool String::operator==(const String& str)const{
    return strcmp(this->data, str.data);
}
bool String::operator==(const char* str)const{
    return strcmp(this->data, str);
}
bool String::operator!=(const String& str)const{
    return !this->operator==(str);
}
bool String::operator!=(const char* str)const{
    return !this->operator==(str);
}
String& String::operator+=(const char* str){
    if(str==nullptr){
        return *this;
    }
    if(!this->data){
        this->operator=(str);
        return *this;
    }
    char* newString=new char[_length+lengthOf(str)+1]{0};
    strconcat(newString, this->data);
    strconcat(newString, str);
    delete[]this->data;
    this->data=newString;
    this->_length=lengthOf(this->data);
    this->_size=this->_length;
    return *this;
}
String& String::operator+=(const String& str){
    if(str.length()==0){
        return *this;
    }
    if(!this->data){
        this->operator=(str);
        return *this;
    }
    char* newString=new char[_length+str.length()+1]{0};
    strconcat(newString, this->data);
    strconcat(newString, str.data);
    delete[]this->data;
    this->data=newString;
    this->_length=lengthOf(this->data);
    this->_size=this->_length;
    return *this;
}
bool String::operator<(const String& str)const{
    int minLength=str._length<_length?str._length:_length;
    for(int i=0; i<minLength; i++){
        if(str[i]>data[i]){return true;}
        if(str[i]<data[i]){return false;}
    }
    if(str._length==_length){return false;}
    return minLength==_length?true:false;
}
bool String::operator<(const char* str)const{
    int strlen=lengthOf(str);
    int minLength=strlen<_length?strlen:_length;
    for(int i=0; i<minLength; i++){
        if(str[i]>data[i]){return true;}
        if(str[i]<data[i]){return false;}
    }
    if(strlen==_length){return false;}
    return minLength==_length?true:false;
}

bool String::operator>(const String& str)const{
    int minLength=str._length<_length?str._length:_length;
    for(int i=0; i<minLength; i++){
        if(str[i]<data[i]){return true;}
        if(str[i]>data[i]){return false;}
    }
    if(str._length==_length){return false;}
    return minLength==_length?false:true;
}
bool String::operator>(const char* str)const{
    int strlen=lengthOf(str);
    int minLength=strlen<_length?strlen:_length;
    for(int i=0; i<minLength; i++){
        if(str[i]<data[i]){return true;}
        if(str[i]>data[i]){return false;}
    }
    if(strlen==_length){return false;}
    return minLength==_length?false:true;
}
int String::findIndexOf(char c)const{
    for(int i=0; i<this->_length; i++){
        if(*(this->data+i)==c){
            return i;
        }
    }
    return -1;
}
String String::substr(int start, int end)const{
    if(start<0 || end>_length || start>=end){
        return String();
    }
    char* finalSubstring=new char[end-start+1]{0};
    for(int i=start; i<end; i++){
        *(finalSubstring+i-start)=*(this->data+i);
    }
    return String(finalSubstring);
}
void String::normalise(){
    if(!this->data){return;}
    char* dataStart=this->data;
    char* dataEnd=this->data+_length-1;
    while(*(dataStart)==' '){
        dataStart++;
    }
    while(*(dataEnd)==' '){
        dataEnd--;
    }
    this->_length=dataEnd-dataStart+1;
    char* normalisedString=new char[_length+1]{0};
    int index=0;
    while(dataStart!=(dataEnd+1)){
        *(normalisedString+(index++))=*(dataStart++);
    }
    delete[] this->data;
    this->data=normalisedString;
    this->_size=this->_length;
}
String::~String(){
    if(this->data != nullptr){
        delete[]this->data;
    }  
}