#include "Request.h"

Request::Request(const String& req){
	String method=(req.substr(0, req.findIndexOf('/')));
	method.normalise();
	this->method=getMethodFromString(method);
	int endRoot=req.substr(req.findIndexOf('/'), req.length()-1).findIndexOf(' ')+req.findIndexOf('/');
	if(endRoot==-1){endRoot=req.length()-1;}
	this->root=String(req.substr(req.findIndexOf('/'), endRoot));
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
}
void Request::operator=(Request&& req){
	this->method=req.method;
	this->root=req.root;
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
