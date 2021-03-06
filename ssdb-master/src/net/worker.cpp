/**
* @file worker.cpp
* @Brief 
* @author Youzu-BigApp
* @version 1.0.0
* @date 2016-03-10
*/
#include "worker.h"
#include "link.h"
#include "proc.h"
#include "../util/log.h"
#include "../include.h"

ProcWorker::ProcWorker(const std::string &name){
	this->name = name;
}

void ProcWorker::init(){
	log_debug("%s %d init", this->name.c_str(), this->id);
}

int ProcWorker::proc(ProcJob *job){
	const Request *req = job->req;
	
	proc_t p = job->cmd->proc;
	job->time_wait = 1000 * (millitime() - job->stime);
	job->result = (*p)(job->serv, job->link, *req, &job->resp);
	job->time_proc = 1000 * (millitime() - job->stime) - job->time_wait;

	if(job->link->send(job->resp.resp) == -1){
		job->result = PROC_ERROR;
	}else{
		if(job->cmd->flags & Command::FLAG_READ){
			int len = job->link->write();
			if(len < 0){
				job->result = PROC_ERROR;
			}
		}
	}
	return 0;
}
