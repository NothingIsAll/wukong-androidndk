/*************************************************************************
	> File Name: findcard.cpp
	> Author: wc
	> Version:1.3.5(release)
	> Created Time: 2017.01.13
 ************************************************************************/
#include <pthread.h>
#include <sys/stat.h>
#include <unistd.h>

#include "findcardtype.h"
#include "findcard.h"

//#include "Mcreater.h"
//#include "ivconfig.h"
//#include "Abstindentyvertion.h"
//#include "indentyvertion.h"
//#include<iostream>
#define FIND_CARD_LOG "FINDCARD"
#ifdef FIND_CARD_LOG
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, FIND_CARD_LOG, fmt, ##args)
//#define LOGE(fmt, args...) printf( fmt, ##args)
#else
#define LOGE(fmt, args...)
#endif

const static char __attribute__((unused,section("FINDCARD_VERSION")))  Version[] = VERSION;

using namespace std;

MicString::MicString()
{
	memset(micstring,0,1024);
	len = 0;
}
void MicString::clean(){
	memset(micstring,0,1024);
	len = 0;
}
char* MicString::c_char()
{
	return micstring;
}
int MicString::length()
{
	return len;
}
int MicString::putstring(const char* buffer,int size)
{
	int lensize = size;
	if(size <= 1024)
		lensize = size;
	else
		lensize = 1024;
	memcpy(micstring,buffer,lensize);
	len = lensize;
	return len;
}

FindCard::FindCard()
{
	devicepath = NULL;
	valuereset();
//	mindentyv = nullptr;//new Mindentyvertion;//Mcreater::GetAbstindentyvertion();
}

void FindCard::valuereset()
{
	fp1 = NULL;
	fp2 = NULL;
	dir1 = 0;
	Card = -1;
	rescardsnum = 0;
	Cardsindex = -1;
	Cardindex = -1;
	Device = -1;
	Usingothers = 1;
	cardspath_filestr_num = 0;
	pcmpath_filestr_num = 0;
	usfulpcm_str_num = 0;
	mcollectpolicy = 2;
	cachepolicy = 2;
	netpolicy = 0;
	makenoise = 0;
	muteflag = 0;
	memset(&Cards,0,1024);
	memset(&serialnum,0,20);
	memset(&InUseDeviceId,0,1024);
	memset(&rescsd,0,sizeof(cardstrdevice));
	memset(&maskmic,0,sizeof(Maskmic));

	for(int i = 0;i< 100;i++)
	{
		memset(cardspath_filestr[i],0,1024);
		memset(pcmpath_filestr[i],0,1024);
		memset(usfulpcm_str[i],0,1024);
		memset(&rescsds[i],0,sizeof(cardstrdevice));

	}
}

void FindCard::valueflush()
{
	Card = -1;
	rescardsnum = 0;
	Cardsindex = -1;
	Cardindex = -1;
	Device = -1;
	cardspath_filestr_num = 0;
	pcmpath_filestr_num = 0;
	usfulpcm_str_num = 0;
	memset(&Cards,0,1024);
	memset(&serialnum,0,20);
	memset(&InUseDeviceId,0,1024);
	memset(&rescsd,0,sizeof(cardstrdevice));
	for(int i = 0;i< 100;i++)
	{
		memset(cardspath_filestr[i],0,1024);
		memset(pcmpath_filestr[i],0,1024);
		memset(usfulpcm_str[i],0,1024);
		memset(&rescsds[i],0,sizeof(cardstrdevice));

	}
}

void FindCard::SetNetPolicy(){
	pthread_mutex_lock(&fMutexthree);
	pthread_mutex_lock(&fMutex);
	mcollectpolicy = cachepolicy;
	pthread_mutex_unlock(&fMutex);
	pthread_mutex_unlock(&fMutexthree);
	FilterInit();
}


void FindCard::SetCollectPolicy(int policy,int flag)
{
	LOGE("linenum = %d,mcollectpolicy=%d,policy:%d,flag:%d,funname=%s\n",__LINE__,mcollectpolicy,policy,flag,__FUNCTION__);
	pthread_mutex_lock(&fMutexthree);
	pthread_mutex_lock(&fMutex);

	if(flag){//本地设置
		mcollectpolicy = policy;
	}else{//联网设置
		cachepolicy = policy;
		LOGE("linenum = %d,mcollectpolicy=%d，cachepolicy:%d,funname=%s\n",__LINE__,mcollectpolicy,cachepolicy,__FUNCTION__);
		if(mcollectpolicy != 3)
			mcollectpolicy = policy;
	}
	pthread_mutex_unlock(&fMutex);
	pthread_mutex_unlock(&fMutexthree);
	FilterInit();

}

int FindCard::FilterInit()
{
	pthread_mutex_lock(&fMutexthree);
	pthread_mutex_lock(&fMutex);
	selectmiccore();
	LOGE("linenum = %d,mcollectpolicy=%d，funname=%s\n",__LINE__,mcollectpolicy,__FUNCTION__);
	char* res = 0;
	//LOGE("FLL - mcollectpolicy = %d\n",mcollectpolicy);
	switch(mcollectpolicy)
	{
	case 0:
	{
		muteflag = 0;
		setothermic();
		makenoise = 0;
	}
	break;
	case 1:
	{
		setothermic();
		muteflag = 0;
		if((res = strstr(cardspath_filestr[Cardindex],"TLCY-")) == NULL)
			makenoise = 1;
		else
			makenoise = 0;
	}
	break;
	case 2:
	{
		muteflag = 0;
		setothermic(0);
		makenoise = 0;
	}
	break;
	case 3:
	{
		setothermic(0);
		makenoise = 0;
		muteflag = 1;
	}
	break;
	}
	//LOGE("FLL - mcollectpolicy makenoise = %d\n",makenoise);
	pthread_mutex_unlock(&fMutex);
	pthread_mutex_unlock(&fMutexthree);
	return 0;
}

int FindCard::CollectPolicyFilter(char* buffer,int size)
{
	//LOGE("linenum = %d,funname=%s\n",__LINE__,__FUNCTION__);
	short* bufp = NULL;
	if(makenoise){
	bufp = (short*)buffer;
	//bufp[0] = 32766;
	bufp[0] = 0;
	}
	if(muteflag){
		memset(buffer,0,size);
	}
	return 0;
}

string& FindCard::trim(string &str, string::size_type pos)
{
    static const string delim = " \t"; //删除空格或者tab字符
    pos = str.find_first_of(delim, pos);
    if (pos == string::npos)
        return str;
    return trim(str.erase(pos, 1));
}


FindCard::~FindCard()
{
//	delete mindentyv;
	pthread_mutex_destroy(&fMutex);
	pthread_mutex_destroy(&fMutexthree);

}


int FindCard::getCardNumFromStr(char* cardstr)
{
	char thiscardnumstr[10] ={};
	char* firstnull = strchr(cardstr,' ');
	char* secondnull = strchr(firstnull+1,' ');
	int post = secondnull - firstnull;
	memcpy(thiscardnumstr,firstnull+1,post);
	int thiscardnum = atoi(thiscardnumstr);
	return thiscardnum;
}

char* FindCard::strlwr(char* pcmstr)
{
	for(int i = 0;i < strlen(pcmstr);i++)
		pcmstr[i]=tolower(pcmstr[i]);
	return pcmstr;
}


int FindCard::getCardNumFromPcmStr(char* pcmstr)
{
	char tcardnumstr[10] ={};
	char* lpcmstr = strlwr(pcmstr);
	char* pcmcptr = strstr(lpcmstr,"pcmc");
	char* cardptr = pcmcptr + 4;
	char* Dptr = strchr(lpcmstr,'d');
	int postsize = Dptr - cardptr;
	//LOGE("--------------------------postsize =%d",postsize);
	memcpy(tcardnumstr,cardptr,postsize);
	int cardnumber = atoi(tcardnumstr);
	return cardnumber;
}


int FindCard::getDeviceNumFromPcmStr(char* pcmstr)
{
	char tcardnumstr[10] ={};
	char* lpcmstr = strlwr(pcmstr);
	char* Dptr = strchr(lpcmstr,'d');
	char* Cptr = strchr(Dptr,'c');
	char* Pptr = strchr(Dptr,'p');
	int postsize = 0;
	if(Cptr == NULL)
	{
		postsize = Pptr-Dptr-1;
	}
	else
	{
		postsize = Cptr-Dptr-1;
	}
	memcpy(tcardnumstr,Dptr+1,postsize);
	int cardnumber = atoi(tcardnumstr);
	return cardnumber;
}

bool FindCard::isCapMic(char* pcmstr)
{
	char* lpcmstr = strlwr(pcmstr);
	char* Dptr = strchr(lpcmstr,'d');
	char* Cptr = strchr(Dptr,'c');
	if(Cptr == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int FindCard::setothermic(bool others)
{
    Usingothers = others;
    return 0;
}

int FindCard::geteffectbit(char* begi)
{
    for(int i = 0;i<1000;i++)
    {
        if(begi[i] == 'O')
        return i;
    }
    return 0;
}

int FindCard::geteffectbittestold(char* begi)
{
    for(int i = 0;i<1000;i++)
    {
        if(begi[i] == 'P')
        return i;
    }
    return 0;
}

int FindCard::GetInUseDeviceInfo(MicString* micstr)
{
	pthread_mutex_lock(&fMutexthree);
	pthread_mutex_lock(&fMutex);
	LOGE("GetInUseDeviceInfo LINE=%d fun=%s \n",__LINE__,__FUNCTION__);
	int index = 0;//支持扩展可选择多个mic中的某一个的控制，现在默认是第1个可用mic
	selectmiccore();
	memset(InUseDeviceId,0,1024);
	LOGE("GetInUseDeviceInfo LINE=%d fun=%s \n",__LINE__,__FUNCTION__);
	for(int i = 0;i<cardspath_filestr_num;i++)
	{
	LOGE("GetInUseDeviceInfo LINE=%d fun=%s \n",__LINE__,__FUNCTION__);
		if(ishavemask(i))
		{
		LOGE("GetInUseDeviceInfo LINE=%d fun=%s \n",__LINE__,__FUNCTION__);
			continue;
		}
		LOGE("GetInUseDeviceInfo LINE=%d fun=%s \n",__LINE__,__FUNCTION__);
		int nmn = getCardNumFromStr(cardspath_filestr[i]);
		//LOGE("fllrescsds[index].Card =%d,nmn =%d,cardspath_filestr_num = %d\n",rescsds[index].Card,nmn,cardspath_filestr_num);
		if(nmn == rescsds[index].Card)
		{
		LOGE("GetInUseDeviceInfo LINE=%d fun=%s \n",__LINE__,__FUNCTION__);
			string trimbefore(cardspath_filestr[i]);
			string trimafter;
			trimafter = trim(trimbefore);
			memcpy(InUseDeviceId,trimafter.c_str(),trimafter.length());
			//LOGE("fllcardspath_filestr =%s",cardspath_filestr[i]);
			micstr->putstring(InUseDeviceId,strlen(InUseDeviceId));
			pthread_mutex_unlock(&fMutex);
			pthread_mutex_unlock(&fMutexthree); //******
			return 0;
		}
		LOGE("GetInUseDeviceInfo LINE=%d fun=%s \n",__LINE__,__FUNCTION__);
		//LOGE("GetInUseDeviceId end 0\n");
	}
	pthread_mutex_unlock(&fMutex);
	pthread_mutex_unlock(&fMutexthree);
	//LOGE("GetInUseDeviceId end 1\n");
	LOGE("GetInUseDeviceInfo LINE=%d fun=%s \n",__LINE__,__FUNCTION__);
	return -1;
}

int FindCard::GetSerialnum(MicString* micstr)
{
	pthread_mutex_lock(&fMutexthree);
	pthread_mutex_lock(&fMutex);
	selectmiccore();
    char* res = NULL;
    serialnum[12] ='\0';
    if(Card != -1)
    {
        if((res = strstr(cardspath_filestr[Cardindex],"TLCY-")) == NULL)
        {
        	pthread_mutex_unlock(&fMutex);
        	pthread_mutex_unlock(&fMutexthree);
            return -1;
        }
        else
        {
        	////LOGE("zhao dao serialnum te zheng fu \n");
			//int effectbit = geteffectbittestold(res+12);
			int effectbit = geteffectbit(res+5);
			LOGE("effectbit = %d\n",effectbit);
			memcpy(serialnum,res+5,effectbit);
			//memcpy(serialnum,res+12,effectbit);
			serialnum[effectbit] = '\0';
			micstr->putstring(serialnum,strlen(serialnum));
			pthread_mutex_unlock(&fMutex);
			pthread_mutex_unlock(&fMutexthree);
			return 0;
        }
    }
    else
    {
    	pthread_mutex_unlock(&fMutex);
    	pthread_mutex_unlock(&fMutexthree);
        return -2;
    }
    return 0;
}

int FindCard::getstrfrompath()
{
    fp1 = fopen(cardspath,"r");
	LOGE("%s open fp1=%d! line=%d\n",cardspath,fp1,__LINE__);
    if(fp1 == (FILE*)0)
    {
     LOGE("%s open fail fp1=%d! line=%d\n",cardspath,fp1,__LINE__);
    	fp1 = fopen(cardspath,"r");
        LOGE("%s open fail fp1=%d! line=%d\n",cardspath,fp1,__LINE__);
        if(fp1 ==0){
        	return -1;
        }
        
    }
    char buffer[2048] = {};
    int res = 0;
    int index = 0;
    int num = 0;
    int indextmp = -1;
	if(!(access(cardspath,F_OK)== 0)){
		LOGE("file %s not exit!! line=%d\n",cardspath,__LINE__);
		return -1;
	}
	if(!(access(cardspath,R_OK)== 0)){
		LOGE("file %s can not read!! line=%d\n",cardspath,__LINE__);
		return -1;
	}
    LOGE("getstrfrompath before while buffer =%p fp1 = %d\n",buffer,fp1);
    while((res = fgets(buffer,1024,fp1) != NULL))
    {
		LOGE(" line =%d new getstrfrompath cardspath_filestr_num =%d  str=%s buffer=%p res=%d",__LINE__,cardspath_filestr_num,buffer,buffer,res);
        if(strstr(buffer,"]:"))
        {
        	cardspath_filestr_num++;
        	strcpy(cardspath_filestr[cardspath_filestr_num -1],buffer);
        }
        else
        {
        	strcat(cardspath_filestr[cardspath_filestr_num -1],buffer);
        }

        memset(buffer,0,1024);
    }
    fclose(fp1);
    return 0;
}


int FindCard::getpcmfrompath()
{
    dir1 = opendir(devicepath);
    if(dir1 == 0)
    {
        //LOGE("%s dir open fail!\n",devicepath);
        return -1;
    }
    struct dirent* indirfiles;
    struct stat filestat;
    int index = 0;
    while((indirfiles = readdir(dir1)) != NULL)
    {
        if(strncmp(indirfiles->d_name,".",1) == 0)
        continue;
        if(strncmp(indirfiles->d_name,"pcm",3) != 0)
        continue;
        strcpy(pcmpath_filestr[index],indirfiles->d_name);
        index++;
    }
    pcmpath_filestr_num = index;
    closedir(dir1); 
    return 0;
}

int FindCard::ishavemask(int index)
{
    for(int i = 0;i < maskmic.masknum;i++)
    {
        if(strstr(cardspath_filestr[index],maskmic.maskmics[i]) != NULL)
        return 1;
    }
    return 0;
}


int FindCard::GetCards(cardstrdevice* cardsdevice)
{

	pthread_mutex_lock(&fMutexthree);
	pthread_mutex_lock(&fMutex);
	selectmiccore();
	int numcard = rescardsnum; //使rescardsnum线程安全
	if(rescardsnum > 0){
    //*cardsdevice = rescsds[0];
    (*cardsdevice).Card = rescsds[0].Card;
    (*cardsdevice).cadsnum = rescsds[0].cadsnum;
    //(*cardsdevice).cardsnum = rescsds[0].cardsnum;
    (*cardsdevice).device = rescsds[0].device;
    (*cardsdevice).isline = rescsds[0].isline;
    memcpy((*cardsdevice).pcm,rescsds[0].pcm,1024);
    //memcpy((*cardsdevice).str,rescsds[0].str,1024);//!!!!!!!会导致mindentyv为0，及一些默认名棋妙的问题

	}//show();
    pthread_mutex_unlock(&fMutex);
    pthread_mutex_unlock(&fMutexthree);
//    mindentyv = Mcreater::GetAbstindentyvertion();
//    if(mindentyv)
//    mindentyv->Vertion(numcard);
//    pthread_mutex_lock(&fMutexthree);
//    pthread_mutex_lock(&fMutex);
//	selectmiccore();
//	numcard = rescardsnum; //使rescardsnum线程安全
//	if(rescardsnum > 0)
//	*cardsdevice = rescsds[0];
//	//show();
//	pthread_mutex_unlock(&fMutex);
//	pthread_mutex_unlock(&fMutexthree);
    return numcard;
}


int FindCard::istlcy(char* istlcy)
{
    if(strstr("TLCY-",istlcy) != NULL)
    return 1;
    else
    return 0;
}

int FindCard::select_cardspath_filestr(char* mapstr)
{
    for(int i = 0;i<cardspath_filestr_num;i++)
    {
        if(ishavemask(i))
        continue;
        
        if((strstr(cardspath_filestr[i],mapstr) != NULL))
        {
           // int nmn = atoi(&(cardspath_filestr[i][0]));
            int nmn = getCardNumFromStr(cardspath_filestr[i]);
            /*
            LOGE("fll cardspath_filestr[%d] =%s\n",i,cardspath_filestr[i]);
            LOGE("fll cardspath_filestr[%d][0] =%c\n",i,cardspath_filestr[i][0]);
            LOGE("fll cardspath_filestr[%d][1] =%c\n",i,cardspath_filestr[i][1]);
            LOGE("fll cardspath_filestr[%d][2] =%c\n",i,cardspath_filestr[i][2]);
            LOGE("fll cardspath_filestr[%d][3] =%c\n",i,cardspath_filestr[i][3]);
            LOGE("fll cardspath_filestr atoinum1 = %d\n",nmn);
            int xnmn = atoi(&(cardspath_filestr[i][1]));
            LOGE("fll cardspath_filestr atoinum2 = %d\n",xnmn);
            xnmn = atoi(&(cardspath_filestr[i][2]));
            LOGE("fll cardspath_filestr atoinum3 = %d\n",xnmn);
            xnmn = atoi(&(cardspath_filestr[i][3]));
            LOGE("fll cardspath_filestr atoinum4 = %d\n",xnmn);
            int ynum =0;
            memcpy((char*)&ynum,&(cardspath_filestr[i][0]),1);
            LOGE("fll cardspath_filestr atoinum1 = %d\n",ynum);
            memcpy((char*)&ynum,&(cardspath_filestr[i][1]),1);
            LOGE("fll cardspath_filestr atoinum1 = %d\n",ynum);
            memcpy((char*)&ynum,&(cardspath_filestr[i][2]),1);
            LOGE("fll cardspath_filestr atoinum1 = %d\n",ynum);
            memcpy((char*)&ynum,&(cardspath_filestr[i][3]),1);
            LOGE("fll cardspath_filestr atoinum1 = %d\n",ynum);
             */
            Cardindex = i;
            Card = nmn; 
            return 0;
        }
        // //LOGE("select_cardspath_filestr()--ardspath_filestr = %s\n",cardspath_filestr[i]);
    }
    return -1;
}

int FindCard::List_cardspath_filestr2Card()
{
    Cardsindex = 0;
    for(int i = 0;i<cardspath_filestr_num;i++)
    {
        if(ishavemask(i))
        {
        	//LOGE("List_cardspath_filestr2Card i =%d",i);
        	continue;
        }
        int nmn = getCardNumFromStr(cardspath_filestr[i]);
        //int nmn = atoi(&(cardspath_filestr[i][0]));
        //LOGE("atoinum = %d\n",nmn);
        Cards[Cardsindex] = nmn;
        Cardsindex++;
    }
    for(int i=0;i< Cardsindex;i++)
    {
    	//LOGE("CARD[%d] = %d",i,Cards[i]);
    }
    return 0;
}

int FindCard::iscardshasthispcm(int cards)
{
	if(!Cardsindex)
		return 0;
    for(int i = 0;i< Cardsindex;i++)
    {
        if(Cards[i] == cards)
        return 1;
    }
    return 0;
}

int FindCard::selecusefulcmdepencards()
{
    //LOGE("come pcmpath_filestr_num  =%d\n",pcmpath_filestr_num);
    if(!pcmpath_filestr_num)
    	return 0;
    for(int i = 0;i < pcmpath_filestr_num;i++)
    {
        //int res = atoi(&(pcmpath_filestr[i][4]));
    	int res = getCardNumFromPcmStr(pcmpath_filestr[i]);
        //LOGE("pcmpath_filestr 5 char to num =%d\n",res);

		if(iscardshasthispcm(res) && isCapMic(pcmpath_filestr[i]))
		// if(iscardshasthispcm(res) && (pcmpath_filestr[i][7] == 'c'))
        {
            memcpy(usfulpcm_str[usfulpcm_str_num],pcmpath_filestr[i],strlen(pcmpath_filestr[i]));
            usfulpcm_str_num ++;
        }
		else
		{
			//LOGE("ooooo iscardshasthispcm =%d,isCapMic =%d",iscardshasthispcm(res),isCapMic(pcmpath_filestr[i]));
			//LOGE("iiiii res =%d,pcmpath_filestr =%s",res,pcmpath_filestr[i]);
		}
    }
    return usfulpcm_str_num;
}

int FindCard::usfulpcm_str2cardstrdevice()
{
	if(!usfulpcm_str_num)
		return 0;
	for(int i = 0;i<usfulpcm_str_num;i++)
    {
       // rescsds[i].Card = atoi(&(usfulpcm_str[i][4]));
       // rescsds[i].device = atoi(&(usfulpcm_str[i][6]));
		rescsds[i].Card = getCardNumFromPcmStr(usfulpcm_str[i]);
		rescsds[i].device = getDeviceNumFromPcmStr(usfulpcm_str[i]);
    }
    rescardsnum = usfulpcm_str_num;
    return 0;
}


int FindCard::noUsingOtherMic()
{
    for(iter = mymap.begin();iter != mymap.end();++iter)
    {
        //LOGE("iter->first=%d,(iter->second).str = %s,device=%d\n",iter->first,(iter->second).str,(iter->second).device);
        int res = select_cardspath_filestr((iter->second).str);
        if(res == 0)
        {
            Device = (iter->second).device;
            rescsd.isline = (iter->second).isline;
            rescsds[0].isline = (iter->second).isline;
            return 0; 
        }
    }
    return -1;
}

int FindCard::selectmiccore()
{
	valueflush();
    getstrfrompath();
    getpcmfrompath();
    int res = noUsingOtherMic();
    //LOGE("come noUsingothers res =%d\n",res);
    if(res == 0 && Card != -1 && Device != -1)
    {
        rescsds[0].Card = Card;
        rescsds[0].device = Device;
        rescardsnum = 1;
        //LOGE("come noUsingothers\n");
    }
    if(res == -1 && Usingothers)
    {
        //LOGE("come Usingothers\n");
        List_cardspath_filestr2Card();
        res = selecusefulcmdepencards();
        if(res == 0)
        {
            //LOGE("selecusefulcmdepencards return 0 \n");
        }
        else if(res > 0)
        {
            usfulpcm_str2cardstrdevice();
        }
    }
   // show();
   return 0;
}

int FindCard::SetMicPriority(const char* mic,int priority,int device,bool islinein)
{
	pthread_mutex_lock(&fMutex);
    cardstrdevice cads;
    memcpy(cads.str,mic,1024);
    cads.device = device;
    cads.isline = islinein;
    mymap.insert(pair<int,cardstrdevice>(priority,cads));
    pthread_mutex_unlock(&fMutex);
    return 0;
}

int FindCard::SetMask(const char* maskmic)
{
	pthread_mutex_lock(&fMutex);
    memcpy(FindCard::maskmic.maskmics[(FindCard::maskmic.masknum)],maskmic,strlen(maskmic));
    (FindCard::maskmic.masknum)++;
    pthread_mutex_unlock(&fMutex);
    return 0;
}

int FindCard::getCard()
{
    return Card;
}

int FindCard::getDevice()
{
    return Device;
}

int FindCard::FindcardInit()
{
//	mindentyv->Setfindcard(this);
	printf("%s\n",Version);

	if(!devicepath)
	{
		cardspath = "/proc/asound/cards";
		devicepath = "/dev/snd";
		pthread_mutex_init(&fMutex, 0);
		pthread_mutex_init(&fMutexthree, 0);
		return 0;
	}
	else
		return -1;
}

int FindCard::change()
{
    cardspath = "xxxxx";
    return 0;
}


int FindCard::show()
{
	LOGE("value ----- ============================start==============================\n");
	LOGE("value ----- Card= %d\n",Card);
	LOGE("value ----- rescardsnum= %d\n",rescardsnum);
	LOGE("value ----- Cardsindex= %d\n",Cardsindex);
	LOGE("value ----- Cardindex= %d\n",Cardindex);
	LOGE("value ----- Device= %d\n",Device);
	LOGE("value ----- Usingothers= %d\n",Usingothers);
	LOGE("value ----- cardspath_filestr_num= %d\n",cardspath_filestr_num);
	LOGE("value ----- pcmpath_filestr_num= %d\n",pcmpath_filestr_num);
	LOGE("value ----- usfulpcm_str_num= %d\n",usfulpcm_str_num);
	LOGE("value ----- mcollectpolicy= %d\n",mcollectpolicy);
	LOGE("value ----- makenoise= %d\n",makenoise);
	LOGE("value ----- cardspath_filestr_num= %d\n",cardspath_filestr_num);
	LOGE("value ----- maskmic= %d\n",maskmic.masknum);
	LOGE("value ----- =============================end================================\n");
    return 0;
}


