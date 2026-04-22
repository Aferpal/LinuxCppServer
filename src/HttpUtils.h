#pragma once
#include "String/String.h"


String content_type_from_extension(const String& ext){

	if ( ext == ".js"){
		return "text/javascript";
	}else if( ext == ".json" ){
		return "application/json";
	}else if( ext == ".jpg" || ext == ".jpeg"){
		return "image/jpeg";
	}else if( ext == ".css"){
		return "text/css";
	}else if ( ext == ".html"){
		return "text/html";
	}else{
		return "text/plain";
	}

}

String status_from_code(int status_code){
	switch (status_code) {
        case 200: return "OK\r\n";
        case 201: return "Created\r\n";
        case 204: return "No Content\r\n";

        case 301: return "Moved Permanently\r\n";
        case 302: return "Found\r\n";

        case 400: return "Bad Request\r\n";
        case 401: return "Unauthorized\r\n";
        case 403: return "Forbidden\r\n";
        case 404: return "Not Found\r\n";

        case 500: return "Internal Server Error\r\n";
        case 502: return "Bad Gateway\r\n";
        case 503: return "Service Unavailable\r\n";

        default: return "Unknown Status\r\n";
    }
}