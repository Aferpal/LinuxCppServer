#pragma once
#include<fstream>
#include"String/String.h"
class Response{
	private:
		int statusCode;
		int contentLength;
		String contentType;
		String message;
		String body;
	public:
		Response();
		Response(int sCode, const String& body, const String& contentType);
		Response(const Response&);
		Response(Response&&);
		void generateMessage();
		void send(const String&);
		void sendFile(const String&, const String&);
		void setStatus(int c){this->statusCode=c;}
		String getMessage();
		~Response();
};
