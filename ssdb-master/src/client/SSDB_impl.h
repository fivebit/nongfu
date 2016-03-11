#ifndef SSDB_API_IMPL_CPP_
#define SSDB_API_IMPL_CPP_

#include "SSDB_client.h"
#include "net/link.h"

namespace ssdb{

class ClientImpl : public Client{
private:
	friend class Client;
	
	Link *link;
	std::vector<std::string> resp_;
public:
	ClientImpl();
	~ClientImpl();

	virtual const std::vector<std::string>* request(const std::vector<std::string> &req);
	virtual const std::vector<std::string>* request(const std::string &cmd);
	virtual const std::vector<std::string>* request(const std::string &cmd, const std::string &s2);
	virtual const std::vector<std::string>* request(const std::string &cmd, const std::string &s2, const std::string &s3);
	virtual const std::vector<std::string>* request(const std::string &cmd, const std::string &s2, const std::string &s3, const std::string &s4);
	virtual const std::vector<std::string>* request(const std::string &cmd, const std::string &s2, const std::string &s3, const std::string &s4, const std::string &s5);
	virtual const std::vector<std::string>* request(const std::string &cmd, const std::string &s2, const std::string &s3, const std::string &s4, const std::string &s5, const std::string &s6);
	virtual const std::vector<std::string>* request(const std::string &cmd, const std::vector<std::string> &s2);
	virtual const std::vector<std::string>* request(const std::string &cmd, const std::string &s2, const std::vector<std::string> &s3);

	virtual Status get(const std::string &key, std::string *val);
	virtual Status set(const std::string &key, const std::string &val);
};

}; // namespace ssdb

#endif
