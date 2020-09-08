#ifndef _TLCY_platforminfo_H_
#define _TLCY_platforminfo_H_

#include <fstream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include<signal.h>
#define GETLENS 200

using namespace std;
class platforminfo
{
private:
	fstream msrcfile;
	string mpinfo;
	string& trim(string &str, string::size_type pos = 0);
public:
	platforminfo();
	~platforminfo();
	int Init();
	int Getpinfo(string& pinfo);

};




#endif
