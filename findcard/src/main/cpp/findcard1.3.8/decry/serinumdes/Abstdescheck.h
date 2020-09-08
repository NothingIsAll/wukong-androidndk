//#include<iostream>
#include <stdint.h>
#include <string>
#include "descheck.h"

using namespace std;

class Descheck;

class Abstdescheck{
public:
	static Descheck* getInstance(){};
	virtual int Check(string str,string )=0;
};
