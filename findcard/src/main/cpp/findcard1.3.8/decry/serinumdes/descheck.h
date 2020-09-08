#ifndef DESCHECK_H_
#define DESCHECK_H_

//#include<iostream>

#include "Abstdescheck.h"
#include "des.h"
#include "ivconfig.h"
using namespace std;



class Descheck : public Abstdescheck{
public:
	Descheck();
public:
	virtual int Check(string str,string ){};
	virtual int EncodeCheck(string str);
	virtual int DecodeCheck(string str);
	static Descheck* getInstance();
	virtual int LengthCheck(string srcstr,int len);
	virtual int PlaceCheck(string srcstr,int len);
	virtual int Des_De_Code(string srcstr);
	virtual int DestrTailCheck(string srcstr);
	virtual int EnstrTailCheck(string srcstr);
	virtual string GetEcode();
	virtual string GetDcode();

private:
	static Descheck* dcinstance;
	string encodestr;
	string decodestr;

};



#endif
