#include "SSDB_impl.h"
#include "util/strings.h"
#include <signal.h>

namespace ssdb{

ClientImpl::ClientImpl(){
	link = NULL;
}

ClientImpl::~ClientImpl(){
	if(link){
		delete link;
	}
}

Client* Client::connect(const char *ip, int port){
	return Client::connect(std::string(ip), port);
}

Client* Client::connect(const std::string &ip, int port){
	static bool inited = false;
	if(!inited){
		inited = true;
		signal(SIGPIPE, SIG_IGN);
	}
	ClientImpl *client = new ClientImpl();
	client->link = Link::connect(ip.c_str(), port);
	if(client->link == NULL){
		delete client;
		return NULL;
	}
	return client;
}

const std::vector<std::string>* ClientImpl::request(const std::vector<std::string> &req){
	if(link->send(req) == -1){
		return NULL;
	}
	if(link->flush() == -1){
		return NULL;
	}
	const std::vector<Bytes> *packet = link->response();
	if(packet == NULL){
		return NULL;
	}
	resp_.clear();
	for(std::vector<Bytes>::const_iterator it=packet->begin(); it!=packet->end(); it++){
		const Bytes &b = *it;
		resp_.push_back(b.String());
	}
	return &resp_;
}

const std::vector<std::string>* ClientImpl::request(const std::string &cmd){
	std::vector<std::string> req;
	req.push_back(cmd);
	return request(req);
}

const std::vector<std::string>* ClientImpl::request(const std::string &cmd, const std::string &s2){
	std::vector<std::string> req;
	req.push_back(cmd);
	req.push_back(s2);
	return request(req);
}

const std::vector<std::string>* ClientImpl::request(const std::string &cmd, const std::string &s2, const std::string &s3){
	std::vector<std::string> req;
	req.push_back(cmd);
	req.push_back(s2);
	req.push_back(s3);
	return request(req);
}

const std::vector<std::string>* ClientImpl::request(const std::string &cmd, const std::string &s2, const std::string &s3, const std::string &s4){
	std::vector<std::string> req;
	req.push_back(cmd);
	req.push_back(s2);
	req.push_back(s3);
	req.push_back(s4);
	return request(req);
}

const std::vector<std::string>* ClientImpl::request(const std::string &cmd, const std::string &s2, const std::string &s3, const std::string &s4, const std::string &s5){
	std::vector<std::string> req;
	req.push_back(cmd);
	req.push_back(s2);
	req.push_back(s3);
	req.push_back(s4);
	req.push_back(s5);
	return request(req);
}

const std::vector<std::string>* ClientImpl::request(const std::string &cmd, const std::string &s2, const std::string &s3, const std::string &s4, const std::string &s5, const std::string &s6){
	std::vector<std::string> req;
	req.push_back(cmd);
	req.push_back(s2);
	req.push_back(s3);
	req.push_back(s4);
	req.push_back(s5);
	req.push_back(s6);
	return request(req);
}

const std::vector<std::string>* ClientImpl::request(const std::string &cmd, const std::vector<std::string> &s2){
	std::vector<std::string> req;
	req.push_back(cmd);
	for(std::vector<std::string>::const_iterator it = s2.begin(); it != s2.end(); ++it){
		req.push_back(*it);
	}
	return request(req);
}

const std::vector<std::string>* ClientImpl::request(const std::string &cmd, const std::string &s2, const std::vector<std::string> &s3){
	std::vector<std::string> req;
	req.push_back(cmd);
	req.push_back(s2);
	for(std::vector<std::string>::const_iterator it = s3.begin(); it != s3.end(); ++it){
		req.push_back(*it);
	}
	return request(req);
}

/******************** KV *************************/

Status ClientImpl::get(const std::string &key, std::string *val)
{
	Status ret(0);
	return ret;
}

Status ClientImpl::set(const std::string &key, const std::string &val)
{
	Status ret(0);
	return ret;
}
}
