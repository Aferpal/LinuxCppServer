#include "Request.h"

/*Request::Request(const String& req){
	String method=(req.substr(0, req.findIndexOf('/')));

	method.normalise();

	this->method=getMethodFromString(method);

	int endRoot=req.substr(req.findIndexOf('/'), req.length()-1).findIndexOf(' ')+req.findIndexOf('/');
	if(endRoot==-1){endRoot=req.length()-1;}
	this->root=String(req.substr(req.findIndexOf('/'), endRoot));
}*/


Request::Request(char* req){
	char* cpy = req;
	if( req != nullptr ){
		char* method = req;
		//find the first space
		while( *req != ' '){req++;}
		//change the blank space to a null character (str end)
		*req = 0;
		req++;
		this->method = getMethodFromString(method);
		//printf("Method: %s\n", method);
		

		char* root = req;
		while( *req != ' '){req++;}
		//change the blank space to a null character (str end)
		*req = 0;
		req++;
		this->root = root;
		//printf("Root: %s\n", root);

		//skip http version
		while(*req != '\n'){req++;}
		req++;

		char* headers = req;
		while(!(*req == '\r' && *(req+1)=='\n' && *(req+2)=='\r' && *(req+3)=='\n')){req++;}
		*req = 0;
		req+=4;
		this->headers = headers;
		//printf("Headers: %s\n", headers);

		if(*req != '\0'){
			this->body = req;
			//printf("Body: %s\n", req);
		}else{
			this->body = String();
		}
		
		
	}
}

Request::Request(const Request& req){
	this->method=req.method;
	this->root=req.root;
}
Request::Request(Request&& req){
	this->method=req.method;
	this->root=req.root;
}

void Request::operator=(const Request& req){
	this->method=req.method;
	this->root=req.root;
	this->client = req.client;
}
void Request::operator=(Request&& req){
	this->method=req.method;
	this->root=req.root;
	this->client = req.client;
}

Method Request::getMethodFromString(const String& str){
	if(str=="GET"){
		return GET;
	}else if(str=="POST"){
		return POST;
	}else if(str=="DELETE"){
		return DELETE;
	}else if(str=="PUT"){
		return PUT;
	}
	return BAD_METHOD;
}
Method Request::getMethod()const{return this->method;}
const String& Request::getRoot()const{return this->root;}
Request::~Request(){
}

void Request::setClient(const struct sockaddr_in addr_in){
	this->client = addr_in;
}
