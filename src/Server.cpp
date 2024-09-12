#include "Server.h"
using namespace http;

Server::Server(){
	this->socket_fd=socket(AF_INET, SOCK_STREAM, 0);
	if(this->socket_fd<0){
		throw "Socket error\n";
	}
}
void Server::listenAt(int _port){
	this->port=_port;
	this->hexPort=toHex(_port);
	this->sockaddr={AF_INET, (unsigned short)this->hexPort, 0};
	if(bind(this->socket_fd, (const struct sockaddr*)&sockaddr, sizeof(sockaddr))<0){
		throw "Bind error\n";
	}
	if(listen(this->socket_fd, 20)<0){throw "Listen error\n";}
	std::cout<<"Succesfully listening at port "<<_port<<'\n';
	for(int i=0; i<4; i++){
		this->current_request=accept(this->socket_fd, NULL, NULL);
		handleRequest(this->current_request);
	}
		
	
}

Request* Server::formatRequest(int req){
	char buffer[512]={0};
	recv(req, buffer, 512,0);
	return new Request(buffer);
}

void Server::get(String root, const std::function<void(Request* req, Response* res)>& f){
	rootBehaviour[root]=f;
}
void Server::handleRequest(int req){
	Request* request=formatRequest(req);
	Response* response=new Response();
	if(rootBehaviour.find(request->getRoot())!=rootBehaviour.end()){
		rootBehaviour.at(request->getRoot())(request, response);
	}else{response->setStatus(404);}
	String msg= response->getMessage();
	int bSent=send(req, msg, msg.length(), 0);
	delete request;
	delete response;
}

Server::~Server(){
	close(this->socket_fd);
	close(this->current_request);
	std::cout<<"\nSuccesfully exiting and closing resources.\n";
}