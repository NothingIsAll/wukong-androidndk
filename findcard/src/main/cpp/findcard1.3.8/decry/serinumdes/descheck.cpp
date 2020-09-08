#include "descheck.h"

#include<android/log.h>
#include <jni.h>

#ifdef DESCHECK_LOG
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, DESCHECK_LOG, fmt, ##args)
//#define LOGE(fmt, args...) printf( fmt, ##args)
#else
#define LOGE(fmt, args...)
#endif

//class Descheck;



Descheck::Descheck(){
	LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
}

 Descheck* Descheck::dcinstance = NULL;

int Descheck::EncodeCheck(string str){
	LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
	if(!LengthCheck(str,ENCODELEN)){
		LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
		if(!PlaceCheck(str,ENCODELEN)){
			LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
			if(!EnstrTailCheck(str)){
				LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
				return 0;
			}
		}
	}
	decodestr.clear();
	return -1;
}

int Descheck::DecodeCheck(string str){
	LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
	if(!LengthCheck(str,DECODELEN)){
		LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
		if(!PlaceCheck(str,DECODELEN)){
			LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
			if(!DestrTailCheck(str)){
				LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
				return 0;
			}
		}
	}
	decodestr.clear();
	return -1;
}


Descheck* Descheck::getInstance(){
	if(dcinstance == NULL)
	dcinstance= new Descheck();
	LOGE("linenum = %d,instance=%p,funname=%s\n",__LINE__,dcinstance,__FUNCTION__);
	return const_cast <Descheck* >(dcinstance);
}


int Descheck::LengthCheck(string srcstr,int len){
	LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
 if(srcstr.length() == len){
	 return 0;
 }else{
	 decodestr.clear();
	 return -1;
 }
}


int Descheck::PlaceCheck(string srcstr,int len){
	for(int i= 0;i<len;i++){
		if( srcstr[i] <48 || (srcstr[i] > 57 && srcstr[i]<65) || srcstr[i] > 70){
			decodestr.clear();
			return -1;
		}
	}
	return 0;
}
int Descheck::Des_De_Code(string srcstr){
	char destmp[100]={};
	Serinum_De_DES((char*)srcstr.c_str(),destmp);
	decodestr.assign(destmp);
	return 0;
}

int Descheck::DestrTailCheck(string srcstr){
	if(srcstr[15]=='0' && srcstr[14]=='0'){
		return 0;
	}else{
		decodestr.clear();
		return -1;
	}
}
int Descheck::EnstrTailCheck(string srcstr){
	if(srcstr[16] == '0'){
		return 0;
	}else{
		decodestr.clear();
		return -1;
	}
}

string Descheck::GetEcode(){

}
string Descheck::GetDcode(){
	return decodestr;
}

