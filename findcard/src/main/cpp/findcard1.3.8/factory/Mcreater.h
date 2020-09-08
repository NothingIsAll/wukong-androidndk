#ifndef MCREATER_HH_
#define MCREATER_HH_
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include "descheck.h"
#include "findcardtype.h"
#include "findcard.h"
#include "Abstindentyvertion.h"
#include "indentyvertion.h"

class Mcreater{
public:
	static FindCard* Getfindcard(){};
	static Abstindentyvertion* GetAbstindentyvertion();
	static Descheck* GetSeriDescheck();

};


#endif
