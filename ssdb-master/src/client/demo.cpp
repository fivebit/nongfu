#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <vector>
#include "SSDB_client.h"

char* readline(char *buf, int num){
	char *ret = fgets(buf, num , stdin);
	if(!ret){
		return NULL;
	}
	if(strlen(ret) > 0){
		ret[strlen(ret) - 1] = '\0';
	}
	return ret;
}

int main(int argc, char **argv){
	printf("Usage: %s [host] [port]\n", argv[0]);
	const char *ip = (argc >= 2)? argv[1] : "127.0.0.1";
	int port = (argc >= 3)? atoi(argv[2]) : 8888;

	// connect to server
	ssdb::Client *client = ssdb::Client::connect(ip, port);
	if(client == NULL){
		printf("fail to connect to server!\n");
		return 0;
	}
	
	ssdb::Status s;
	std::string key = "k";
	std::string test_val = "test_val";
	std::string val;
	
	printf("\n");
	{
		s = client->set(key, "test_val");
		assert(s.ok());

		s = client->get(key, &val);
		assert(s.ok() && (val == test_val));
		printf("%s = %s\n", key.c_str(), val.c_str());
	}
	
	delete client;
	return 0;
}
