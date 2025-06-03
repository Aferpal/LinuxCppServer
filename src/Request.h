#pragma once
#include"String/String.h"
#include<sys/socket.h>
#include<netinet/in.h>
enum Method{GET, POST, DELETE, PUT, BAD_METHOD};

class Request{
	private:
		Method method;
		String root;
		String body;
		String headers;
		struct sockaddr_in client;

	public:
		Request(const String& req);
		Request(char* req);
		Request(const Request& req);
		Request(Request&& req);
		void operator=(const Request& req);
		void operator=(Request&& req);
		const String& getRoot() const;
		Method getMethod() const;
		Method getMethodFromString(const String&);
		void setClient(const struct sockaddr_in addr_in);
		~Request();

};
