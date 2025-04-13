#pragma once
#include"String/String.h"
enum Method{GET, POST, DELETE, PUT, BAD_METHOD};

class Request{
	private:
		Method method;
		String root;
	public:
		Request(const String& req);
		Request(const Request& req);
		Request(Request&& req);
		void operator=(const Request& req);
		void operator=(Request&& req);
		const String& getRoot() const;
		Method getMethod() const;
		Method getMethodFromString(const String&);
		~Request();

};
