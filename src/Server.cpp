#include "Server.h"

#define BUF_BASE_LEN 1024

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

	if( bind(this->socket_fd, (const struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0 ){

		throw "Bind error\n";

	}

	if( listen(this->socket_fd, 20) < 0 ){

		throw "Listen error\n";

	}

	std::cout<<"Succesfully listening at port "<<_port<<'\n';

	struct sockaddr_in clientAddr;

	socklen_t clientAddrLen;

	char* buffer;

	int buf_len, stored;

	while(true){
		
		this->current_request = accept(this->socket_fd, (struct sockaddr*)&clientAddr, &clientAddrLen);
		
		//printf("Port: %d, ip: %d.%d.%d.%d\n", clientAddr.sin_port, getip3(clientAddr.sin_addr.s_addr), \
			getip2(clientAddr.sin_addr.s_addr), getip1(clientAddr.sin_addr.s_addr), getip0(clientAddr.sin_addr.s_addr));
		
		buffer = (char*)malloc(sizeof(char)*BUF_BASE_LEN);

		buf_len = BUF_BASE_LEN;

		while( ( stored = recv( this->current_request, ( buffer + buf_len - BUF_BASE_LEN ), BUF_BASE_LEN, 0 )) == BUF_BASE_LEN ){
			buf_len += BUF_BASE_LEN;
			buffer = (char*)realloc(buffer, buf_len);
		}

		buffer[buf_len-(BUF_BASE_LEN-stored) + 1] = 0;
		
		Request req{buffer};

		req.setClient(clientAddr);

		handleRequest(req);

		free(buffer);

		close(this->current_request);
		
	}
		
	
}

void Server::get(const String& root, const req_handler_t& f){
	getBehaviour[root]=f;
}

void Server::post(const String& root, const req_handler_t& f){
	postBehaviour[root]=f;
}

void Server::handleRequest(const Request& request){

	Response response{this->current_request};

	switch (request.getMethod())
	{
	case GET:

		if( getBehaviour.find( request.getRoot() ) != getBehaviour.end()){
			getBehaviour.at(request.getRoot())(request, response);
		}else{
			response.setStatus(404);
		}

		break;

	case POST:

		if(postBehaviour.find(request.getRoot())!=postBehaviour.end()){
			postBehaviour.at(request.getRoot())(request, response);
		}else{
			response.setStatus(404);
		}

		break;

	case PUT:

		break;

	default:

		std::cout << "UNKNOWN METHOD\n";
		response.setStatus(404);
		break;

	}

	const String responseMsg = response.getMessage();
	send(this->current_request, (const char*)responseMsg, responseMsg.length() , 0);


}

String content_type_from_extension(const String& ext){

	if ( ext == ".js"){
		return "text/javascript";
	}else if( ext == ".json" ){
		return "application/json";
	}else if( ext == ".jpg" || ext == ".jpeg"){
		return "image/jpeg";
	}else if( ext == ".css"){
		return "text/css";
	}else{
		return "text/plain";
	}

}

void Server::addStaticFolder(const String& folder){
    for (const auto & entry : std::filesystem::directory_iterator((const char*)folder)){
		if(entry.is_regular_file()){
			String file = entry.path().relative_path().c_str();
			String extension = (entry.path().extension().c_str());
			String content_type = content_type_from_extension(extension);
			this->get(String("/")+file, [file, content_type](const Request& req, Response& res){
        		res.sendFile(file, content_type);
    		});
		}
	}
}

Server::~Server(){
	close(this->socket_fd);
	std::cout<<"\nSuccesfully exiting and closing resources.\n";
}