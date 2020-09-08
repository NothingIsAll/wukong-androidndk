#ifndef indentyvertion_HH_
#define indentyvertion_HH_

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<ctype.h>
#include "des.h"
#include "descheck.h"
#include "Mcreater.h"
#include "findcard.h"
#include "ivconfig.h"
#include "Abstindentyvertion.h"

class Mindentyvertion : public Abstindentyvertion{

public:
	Mindentyvertion();
	~Mindentyvertion();
public:
	static Abstindentyvertion* GetInstance();
	virtual void Destroy();
	virtual void Setfindcard(FindCard* fc);
	virtual int Vertion(int cardcount);
	virtual void show();

	static Abstindentyvertion* instance;

private:
	FindCard* fc;
	Descheck* serinumcheck;
	pthread_mutex_t mMutex;
};









#endif
