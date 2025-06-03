#include "Server.h"
using namespace http;

Server::Server(){
	this->socket_fd=socket(AF_INET, SOCK_STREAM, 0);
	if(this->socket_fd<0){
		throw "Socket error\n";
	}
}
void Server::listenAt(int _port){
	this->port = _port;
	this->hexPort = toHex(_port);


	this->sockaddr={AF_INET, (unsigned short)this->hexPort, 0};

	if(bind(this->socket_fd, (const struct sockaddr*)&sockaddr, sizeof(sockaddr))<0){
		throw "Bind error\n";
	}

	if(listen(this->socket_fd, 20)<0){throw "Listen error\n";}
	std::cout<<"Succesfully listening at port "<<_port<<'\n';
	int i = 0;
	for(int i = 0; i< 20; i++){
		//std::cout<<"\n\n\nRequest "<<i<<" atendiendo...\n\n\n";


		struct sockaddr_in clientAddr;
		
		socklen_t clientAddrLen;
		
		this->current_request=accept(this->socket_fd, (struct sockaddr*)&clientAddr, &clientAddrLen);
		
		//printf("Port: %d, ip: %d.%d.%d.%d\n", clientAddr.sin_port, getip3(clientAddr.sin_addr.s_addr), \
			getip2(clientAddr.sin_addr.s_addr), getip1(clientAddr.sin_addr.s_addr), getip0(clientAddr.sin_addr.s_addr));
		
		char buffer[512]={0};
		recv(current_request, buffer, 512, 0);
		//printf("Buffer: %s\n", buffer);
		
		Request req{buffer};
		req.setClient(clientAddr);

		handleRequest(&req);


		close(this->current_request);
	}
		
	
}

Request* Server::formatRequest(int req){
	char buffer[512]={0};
	recv(req, buffer, 512,0);
	return new Request(buffer);
}

void Server::get(String root, const std::function<void(Request* req, Response* res)>& f){
	getBehaviour[root]=f;
}

void Server::post(String root, const std::function<void(Request* req, Response* res)>& f){
	postBehaviour[root]=f;
}

void Server::handleRequest(Request* request){
	Response response{this->current_request};
	switch (request->getMethod())
	{
	case GET:

		if( getBehaviour.find( request->getRoot() ) != getBehaviour.end()){
			getBehaviour.at(request->getRoot())(request, &response);
		}else{
			response.setStatus(404);
		}

		break;
	case POST:
		if(postBehaviour.find(request->getRoot())!=postBehaviour.end()){
			postBehaviour.at(request->getRoot())(request, &response);
		}else{response.setStatus(404);}
			break;
	case PUT:
		break;
	default:
		printf("Nada tio nada \n");
		break;
	}

}

void Server::addStaticFolder(const String& folder){
    for (const auto & entry : std::filesystem::directory_iterator((const char*)folder)){
		if(entry.is_regular_file()){
			String file = entry.path().relative_path().c_str();
			this->get(String("/")+file, [file, entry](Request* req, Response* res){
        		res->sendFile(file, String("text/")+String(entry.path().extension().c_str()+1));
    		});
		}
        std::cout << entry.path() << std::endl;
	}
}

Server::~Server(){
	close(this->socket_fd);
	std::cout<<"\nSuccesfully exiting and closing resources.\n";
}