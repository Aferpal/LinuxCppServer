#pragma once
#include<sys/socket.h>
#include<netinet/in.h>
#include<iostream>
#include<unistd.h>
#include"Request.h"
#include"Response.h"
#include<map>
#include<functional>
#include<filesystem>



namespace http{
	class Server{
		private:
			int socket_fd;
			int current_request;
			int port;
			int hexPort;
			struct sockaddr_in sockaddr;

			std::map<String, std::function<void(Request*, Response*)>> getBehaviour;
			std::map<String, std::function<void(Request*, Response*)>> postBehaviour;
			std::map<String, std::function<void(Request*, Response*)>> putBehaviour;

		public:
			Server();
			void listenAt(int);
			Request* formatRequest(int);
			Response* formatResponse(char*);
			void handleRequest(Request*);
			void get(String str, const std::function<void(Request* req, Response* res)>& f);
			void post(String str, const std::function<void(Request* req, Response* res)>& f);
			void addStaticFolder(const String& folder);
			~Server();
	};
}