/*************************************************************************
	> File Name: findcard.h
	> Author: wc
	> Version:1.3.8(release)
	> Created Time: 2017.08.12
 ************************************************************************/
#ifndef _FINDCARD_H
#define _FINDCARD_H

#include<android/log.h>
#include <jni.h>
//#include<stdio.h>
//#include<stdlib.h>
//#include<map>
//#include<sys/types.h>
//#include<sys/stat.h>
//#include<dirent.h>
#include "findcardtype.h"
//#include<ctype.h>
#include <string>
#include <dirent.h>
#include <map>




//#include <atomic>

using namespace std;
class Abstindentyvertion;
//class MicString
//{
//public:
//	MicString();
//	char* c_char();
//	int length();
//	int putstring(const char* buffer,int size);
//	void clean();
//private:
//	int len;
//	char micstring[1024];
//};

struct Maskmic
{
    char maskmics[100][1024];
    int masknum;
};


//struct cardstrdevice
//{
//    char str[1024];
//    char pcm[1024];
//    int Card;
//    int device;
//    bool isline;
//    int cadsnum;
//};


class FindCard
{
public:
    FindCard();
    ~FindCard();
    int FindcardInit();
    int SetMicPriority(const char* mic,int priority,int device = 0,bool islinein = false);
    int SetMask(const char* maskmic);
    void SetNetPolicy();
    void SetCollectPolicy(int policy,int flag = 0);//0:默认值联网设置，1:本地设置
    int FilterInit();
    int CollectPolicyFilter(char* buffer,int size);
    int GetSerialnum(MicString* micstr);
    int GetInUseDeviceInfo(MicString* micstr);
    int GetCards(cardstrdevice* rescsd);
    int cachepolicy;
    int mcollectpolicy;

private:

    int selectmiccore();
    void valueflush();
    void valuereset();
    string& trim(string &str, string::size_type pos = 0);
    int setothermic(bool others = true);
    int geteffectbit(char* begi);
    int geteffectbittestold(char* begi);
    int change();
    int setdevice(int key,int device);
    int noUsingOtherMic();
    int getCard();
    int getDevice();
    int getstrfrompath();
    int getpcmfrompath();
    int getmiccardnum();
    int getinused();
    int ishavemask(int index);
    int istlcy(char* istlcy);
    int select_cardspath_filestr(char* mapstr); 
    int usfulpcm_str2cardstrdevice();
    int selecusefulcmdepencards();
    int iscardshasthispcm(int cards);
    int List_cardspath_filestr2Card();
    int getCardNumFromStr(char* cardstr);
    int getCardNumFromPcmStr(char* pcmstr);
    int getCardNumFromPcmStr1(char* pcmstr);
    int getDeviceNumFromPcmStr(char* pcmstr);
    bool isCapMic(char* pcmstr);
    char* strlwr(char* pcmstr);
    int show();
private:
    //常量
    FILE* fp1 ;
    FILE* fp2 ;
    DIR* dir1 ;
    const char* cardspath;
    const char* devicepath;
    pthread_mutex_t fMutex;
    pthread_mutex_t fMutexthree;
    //输出变量
    int Card ;
    int rescardsnum ;
    int Cards[1024];
    int Cardsindex ;
    int Cardindex ;
    int Device ;
    int Usingothers ;
    char cardspath_filestr[100][1024];
    cardstrdevice rescsd ;
    cardstrdevice rescsds[100];
    int cardspath_filestr_num ;
    char pcmpath_filestr[100][1024];
    int pcmpath_filestr_num ;
    char usfulpcm_str[100][1024];
    int usfulpcm_str_num ;
    char InUseDeviceId[1024];
    char serialnum[20];
    //输入变量
    Maskmic maskmic ;
    map<int,cardstrdevice> mymap;
    map<int,cardstrdevice>::iterator iter;


    int netpolicy;
    int makenoise;
    int muteflag;
    Abstindentyvertion* mindentyv;
};

class FindCardAdapter {
public:
	FindCardAdapter(){
		fc = new FindCard();
		micType = 2;
	}
	~FindCardAdapter(){
		delete fc;
	}
	int FindcardInit(){
		return fc->FindcardInit();
	}
	int SetMicPriority(const char* mic,int priority,int device = 0,bool islinein = false){
		return fc->SetMicPriority(mic,priority,device,islinein);
	}
	int SetMask(const char* maskmic){
		return fc->SetMask(maskmic);
	}
	void SetNetPolicy(){
		fc->SetNetPolicy();
	}
	void SetCollectPolicy(int policy,int flag = 0){
		//0:榛樿鍊艰仈缃戣缃紝1:鏈湴璁剧疆
//    	fc.SetCollectPolicy(policy, flag);
		fc->SetCollectPolicy(0,0);//鏀惧紑锛岃繖鏍穎c.getCards鑳芥壘鍒板寘鎷涓夋柟鐨刴ic
		micType = policy;
	}
	int FilterInit(){
		return fc->FilterInit();
	}
	int CollectPolicyFilter(char* buffer,int size){
		short* bufp = NULL;
//    	LOGE("CollectPolicyFilter-------------micType=%d",micType);
		switch(micType){
			case 0://杂音
				bufp = (short*)buffer;
				bufp[0] = 32767;
				break;
			case 1://伪造无声
				memset(buffer,0,size);
				break;
			case 2://正常
				break;
			default:
				break;
		}
		return 0;
	}
	int GetSerialnum(MicString* micstr){
		return fc->GetSerialnum(micstr);
	}
	int GetInUseDeviceInfo(MicString* micstr){
		return fc->GetInUseDeviceInfo(micstr);
	}
	int GetCards(cardstrdevice* rescsd){
		return fc->GetCards(rescsd);
	}
private:
	FindCard *fc;
	int micType;
};

#endif
