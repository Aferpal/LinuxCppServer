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

	typedef std::function<void(const Request&, Response&)> req_handler_t;

	class Server{
		private:
			int socket_fd;
			int current_request;
			int port;
			int hexPort;
			struct sockaddr_in sockaddr;

			std::map<String, req_handler_t> getBehaviour;
			std::map<String, req_handler_t> postBehaviour;
			std::map<String, req_handler_t> putBehaviour;

			void handleRequest(const Request&);

		public:
			Server();
			void listenAt(int);
			void get(const String& str, const req_handler_t& f);
			void post(const String& str, const req_handler_t& f);
			void addStaticFolder(const String& folder);
			~Server();
	};
}