/*
Copyright (c) 2012-2014 The SSDB Authors. All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file.
*/
#ifndef SSDB_SERVER_H_
#define SSDB_SERVER_H_

#include "include.h"
#include <map>
#include <vector>
#include <string>
#include "net/server.h"

class SSDBServer
{
private:
	void reg_procs(NetworkServer *net);

public:
	SSDBServer(const Config &conf, NetworkServer *net);
	~SSDBServer();
};

#endif
