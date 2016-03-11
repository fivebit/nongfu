/*
Copyright (c) 2012-2015 The SSDB Authors. All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file.
*/
#include "include.h"
#include "version.h"
#include "net/server.h"
#include "util/app.h"
#include "util/log.h"
#include "util/config.h"
#include "serv.h"

#define APP_NAME "ssdb-server"
#define APP_VERSION SSDB_VERSION

class MyApplication : public Application
{
public:
	virtual void usage(int argc, char **argv);
	virtual void welcome();
	virtual void run();
};

void MyApplication::welcome(){
	fprintf(stderr, "%s %s\n", APP_NAME, APP_VERSION);
	fprintf(stderr, "Copyright (c) 2012-2015 ssdb.io\n");
	fprintf(stderr, "\n");
}

void MyApplication::usage(int argc, char **argv){
	printf("Usage:\n");
	printf("    %s [-d] /path/to/ssdb.conf [-s start|stop|restart]\n", argv[0]);
	printf("Options:\n");
	printf("    -d    run as daemon\n");
	printf("    -s    option to start|stop|restart the server\n");
	printf("    -h    show this message\n");
}

void MyApplication::run(){
	std::string data_db_dir = app_args.work_dir + "/data";
	std::string meta_db_dir = app_args.work_dir + "/meta";

	log_info("ssdb-server %s", APP_VERSION);
	log_info("conf_file        : %s", app_args.conf_file.c_str());
	log_info("log_level        : %s", Logger::shared()->level_name().c_str());
	log_info("log_output       : %s", Logger::shared()->output_name().c_str());
	log_info("log_rotate_size  : %" PRId64, Logger::shared()->rotate_size());

	log_info("main_db          : %s", data_db_dir.c_str());
	log_info("meta_db          : %s", meta_db_dir.c_str());
	log_info("sync_speed       : %d MB/s", conf->get_num("replication.sync_speed"));

	NetworkServer *net = NULL;	
	SSDBServer *server = NULL;
	net = NetworkServer::init(*conf);
	server = new SSDBServer(*conf, net);
	
	log_info("pidfile: %s, pid: %d", app_args.pidfile.c_str(), (int)getpid());
	log_info("ssdb server started.");
	net->serve();
	
	delete net;
	delete server;

	log_info("%s exit.", APP_NAME);
}

int main(int argc, char **argv){
	MyApplication app;
	return app.main(argc, argv);
}
