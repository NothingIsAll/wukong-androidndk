#include "Mcreater.h"

#include "findcard.h"


#ifdef FACTORY_LOG
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, FACTORY_LOG, fmt, ##args)
//#define LOGE(fmt, args...) printf( fmt, ##args)
#else
#define LOGE(fmt, args...)
#endif


Abstindentyvertion* Mcreater::GetAbstindentyvertion(){
	LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
	return Mindentyvertion::GetInstance();
}

Descheck* Mcreater::GetSeriDescheck(){
	LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
	return Descheck::getInstance();
}
