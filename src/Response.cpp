#include "Response.h"
#include<unistd.h>
Response::Response(){
	this->statusCode=200;
	this->contentLength=0;
	this->body=String();
	this->message=String();
	this->contentType=String();
}

Response::Response(int code){
	this->statusCode=code;
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

	char number[4] = {0};
	sprintf(number, "%d", this->statusCode);
	this->message=this->message+number;

	if(number[0] == '4'){
		this->message+=" Not found\r\nContent-Type: text/html\r\nContent-Length: 78\r\nConnection: Closed\r\n\r\n<html>\n<body>\n<h1 style=\"color: red\">Error, page not found</h1>\n</body>\n<html>\r\n\r\n";
		return;
	}else if(number[0]=='2'){
		this->message+=" OK\r\n";
		if(contentType!=nullptr){
			this->message+="Content-Type: ";
			this->message+=this->contentType;
		}
	}

	char cont_length[64]={0};
	snprintf(cont_length, 64, "\r\nContent-Length: %d", this->contentLength);

	this->message+=cont_length;

	this->message+="\r\nConnection: Closed\r\n";
	this->message+="\r\n";
	if(this->body.length()!=0){

		this->message+=this->body;

	}
	this->message+="\r\n\r\n";

}

/*void Response::send(const String& msg){
	this->contentLength=msg.length();
	this->contentType="plain/text";
	this->body=msg;
}*/

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
	requestedFile.readsome(readData, 2048);
	this->body=((String&&)readData);
	this->contentLength=this->body.length();
	this->contentType=contentT;

	requestedFile.close();
}

String Response::getMessage(){
	generateMessage();
	return this->message;
}


Response::~Response(){
}