#ifndef Abstindentyvertion_HH_
#define Abstindentyvertion_HH_

#include "findcard.h"

class FindCard;
class Abstindentyvertion{
public:
	Abstindentyvertion(){};
public:
    static Abstindentyvertion* GetInstance(){ return nullptr;};
    virtual void Destroy()=0;
	virtual void Setfindcard(FindCard* fc)=0;
	virtual int Vertion(int cardcount){ return 0;};
	virtual void show(){};
};



#endif
