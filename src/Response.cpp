#include "Response.h"
#include<unistd.h>
#include<fcntl.h>
#include "HttpUtils.h"

#define BUF_BASE_LEN 4096

Response::Response(){
	this->statusCode=200;
	this->body=String();
	this->message=String();
}

Response::Response(int code){
	this->statusCode=code;
	this->body=String();
	this->message=String();
}


Response::Response(const Response& otherResponse){
	this->statusCode=otherResponse.statusCode;
	this->body=otherResponse.body;
	this->message=otherResponse.message;
	this->headers = otherResponse.headers;
}

Response::Response(Response&& otherResponse){
	this->statusCode=otherResponse.statusCode;
	this->body=otherResponse.body;
	this->message=otherResponse.message;
	this->headers = otherResponse.headers;
}


void Response::generateMessage(){

	this->message = "HTTP/1.1 ";

	char number[4] = {0};
	sprintf(number, "%d ", this->statusCode);
	this->message=this->message+number;

	this->message += status_from_code(this->statusCode);

	if(this->statusCode >= 400 && this->statusCode < 500){
		this->message+="Content-Type: text/html\r\nContent-Length: 78\r\nConnection: Closed\r\n\r\n<html>\n<body>\n<h1 style=\"color: red\">Error, page not found</h1>\n</body>\n<html>\r\n\r\n";
		return;
	}

	for( const auto& [key, value] : this->headers){

		this->message += (key + String(": ") + value + "\r\n");
	}

	this->message += "\r\n";

	if(this->body.length() !=0 ){

		this->message += this->body;

	}

	this->message += "\r\n\r\n";

}

void Response::send(const String& msg, const String& content_type = "text/plain"){

	this->body=msg;

	char content_length[64] = {0};

	snprintf(content_length, 64, "%d", this->body.length());
	
	this->headers["Content-Length"] = content_length;

	this->headers["Content-Type"] = content_type;

}

void Response::sendFile(const String& filePath){

	String path=getenv("PWD");
	path+="/";
	path+=filePath;

	int fd = open(path, O_RDONLY);

	if(fd == -1){
		this->statusCode=404;
		return;
	}

	this->statusCode=200;

	char* buffer = (char*)malloc(sizeof(char)*BUF_BASE_LEN);

	int buf_len = BUF_BASE_LEN;

	int stored;

	while( ( stored = read( fd, ( buffer + buf_len - BUF_BASE_LEN ), BUF_BASE_LEN )) == BUF_BASE_LEN ){
		buf_len += BUF_BASE_LEN;
		buffer = (char*)realloc(buffer, buf_len);
	}


	buffer[buf_len-(BUF_BASE_LEN-stored) + 1] = 0;

	this->body=((String&&)buffer);

	char content_length[64] = {0};

	snprintf(content_length, 64, "%d", this->body.length());
	
	this->headers["Content-Length"] = content_length;

	this->headers["Content-Type"] = content_type_from_extension(filePath.substr(filePath.findIndexOf('.'), filePath.length()));

	close(fd);

}

String Response::getMessage(){
	generateMessage();
	return this->message;
}


Response::~Response(){
}