#include <pthread.h>
#include "indentyvertion.h"

//#include<iostream>

#include "ivconfig.h"
#ifdef Indentyvertion_LOG
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, Indentyvertion_LOG, fmt, ##args)
//#define LOGE(fmt, args...) printf( fmt, ##args)
#else
#define LOGE(fmt, args...)
#endif


Mindentyvertion::Mindentyvertion(){
	pthread_mutex_init(&mMutex, 0);
	LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
	serinumcheck = new Descheck;//Mcreater::GetSeriDescheck();
}
Mindentyvertion::~Mindentyvertion(){
	pthread_mutex_destroy(&mMutex);
	LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
	delete serinumcheck;
}
 Abstindentyvertion* Mindentyvertion::GetInstance(){
	LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
	if(instance == NULL)
	instance = new Mindentyvertion();
	return const_cast <Abstindentyvertion* >(instance);
}
void Mindentyvertion::Destroy(){
	LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);

}
 void Mindentyvertion::Setfindcard(FindCard* fc){
	 this->fc = fc;
	LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
}

 int Mindentyvertion::Vertion(int cardcount){
	 pthread_mutex_lock(&mMutex);
	LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
	int mcardcount = cardcount;
	MicString str;
	fc->GetSerialnum(&str);
	string checkstr;
	checkstr.assign(str.c_char());
	if(mcardcount)
	{
		LOGE("here has mic : %s\n",str.c_char());
		if(str.length() == 0){
			LOGE("THIS is not tlcymic is others serialnum is NULL\n");
			fc->SetCollectPolicy(fc->cachepolicy,1);
			pthread_mutex_unlock(&mMutex);
			return 0;
		}else{
			LOGE("linenum = %d,serinumcheck=%p,funname=%s \n",__LINE__,serinumcheck,__FUNCTION__);
			if(!(serinumcheck->EncodeCheck(checkstr))){
				LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
				serinumcheck->Des_De_Code(checkstr);
				LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
				if(!serinumcheck->DecodeCheck(serinumcheck->GetDcode())){
					LOGE("HERE DECODE DOMAIN decode:%s\n",serinumcheck->GetDcode().c_str());
					fc->SetCollectPolicy(fc->cachepolicy,1);
					LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
					pthread_mutex_unlock(&mMutex);
					return 0;
				}
			}
			LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
			fc->SetCollectPolicy(3,1);
			pthread_mutex_unlock(&mMutex);
			return -1;
		}
	}else{
		LOGE("has no mic\n");
	}
	LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
	fc->SetCollectPolicy(fc->cachepolicy,1);
	pthread_mutex_unlock(&mMutex);
	return 0;
}

 void Mindentyvertion::show(){
	LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
}
 Abstindentyvertion* Mindentyvertion::instance = NULL;//new Mindentyvertion();
