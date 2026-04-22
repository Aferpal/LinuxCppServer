#pragma once
#include<fstream>
#include"String/String.h"
#include<map>
class Response{
	private:
		int statusCode;
		String message;
		String body;
		std::map<String, String> headers;
	public:
		Response();
		Response(int);
		Response(const Response&);
		Response(Response&&);
		void generateMessage();
		void send(const String&, const String&);
		void sendFile(const String&);
		void setStatus(int c){this->statusCode=c;}
		String getMessage();
		~Response();
};
