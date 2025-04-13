#include "Response.h"
#include<unistd.h>
Response::Response(){
	this->statusCode=200;
	this->contentLength=0;
	this->body=String();
	this->message=String();
	this->contentType=String();
}

Response::Response(int _statusCode, const String& body, const String& contentType){
	this->statusCode=_statusCode;
	this->contentLength=body.length();
	this->body= body;
	this->message=String();
	this->contentType=contentType;
}

Response::Response(const Response& otherResponse){
	this->statusCode=otherResponse.statusCode;
	this->contentLength=otherResponse.contentLength;
	this->body=otherResponse.body;
	this->contentType=otherResponse.contentType;
	this->message=otherResponse.message;
}

Response::Response(Response&& otherResponse){
	this->statusCode=otherResponse.statusCode;
	this->contentLength=otherResponse.contentLength;
	this->body=otherResponse.body;
	this->message=otherResponse.message;
	this->contentType=otherResponse.contentType;
}
void Response::generateMessage(){

	this->message = "HTTP/1.1 ";

	char number[4]={(char)(((this->statusCode/100)%10)+'0'), (char)(((this->statusCode/10)%10)+'0'), (char)((this->statusCode%10)+'0'), '\0'};
	this->message=this->message+number;
	if(number[0]=='4'){
		this->message+=" Not found\nContent-Type: text/html\nContent-Length: 78\nConnection: Closed\n\n<html>\n<body>\n<h1 style=\"color: red\">Error, page not found</h1>\n</body>\n<html>\r\n\r\n";
		return;
	}else if(number[0]=='2'){
		this->message+=" OK\n";
		if(contentType!=nullptr){
			this->message+="Content-Type: ";
			this->message+=this->contentType;
		}
	}
	this->message+="\nContent-Length: ";
	int l=this->contentLength;
	char size[32]={0};
	int i=0;
	while(l>0){
		size[i++]=char(l%10+'0');
		l/=10;
	}
	strreverse(size);

	this->message+=size;

	this->message+="\nConnection: Closed\n\n";

	if(this->body.length()!=0){

		this->message+=this->body;

	}
	this->message+="\r\n\r\n";
}

void Response::send(const String& msg){
	this->contentLength=msg.length();
	this->contentType="plain/text";
	this->body=msg;
}

void Response::sendFile(const String& filePath,  const String& contentT){

	String path=getenv("PWD");
	path+="/";
	path+=filePath;

	std::ifstream requestedFile{path};

	if(!requestedFile){
		this->statusCode=404;
		return;
	}
	this->statusCode=200;
	char* readData= new char[2048]{0};
	int i=0;
	while(i<1024 && requestedFile.get(*(readData+(i++)))){}
	this->body=readData;
	this->contentLength=this->body.length();
	this->contentType=contentT;
	if(readData){
		delete[]readData;
	}
	requestedFile.close();
}

String Response::getMessage(){
	generateMessage();
	return this->message;
}


Response::~Response(){
	std::cout<<"Destruyendo respuesta\n";
}