//#define LOG_TAG "MICDECODE"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include "TLMicLog.h"
//#include"include/hashlibpp.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "tlmicdes.h"
//函数声明
// int Do_DES(char* strSrc, char* strKey, char* strDest, char flag);
// int Do_3DES(char* strSrc, char* strKey, char* strDest, char flag);
int BCDToByte(unsigned char* strBCD, int count, unsigned char* bytes);
int ByteToBit(unsigned char* bytes, int count, unsigned char* strBit);
int Des_GenSubKey(unsigned char* strKey, unsigned char strSubKey[16][48+1]);
int Des_IP(unsigned char* strIn, unsigned char* strOut);
int Des_F(unsigned char* strR, unsigned char* strK, unsigned char* strOut);
int Do_XOR(unsigned char* strSrc, int count, unsigned char* strDest);
int Des_IP_1(unsigned char* strIn, unsigned char* strOut);
int BitToByte(unsigned char* strBit, int count, unsigned char* bytes);
int ByteToBCD(unsigned char* bytes, int count,unsigned char* strBCD);





//做DES加密或解密运算
int Do_DES(unsigned char* strSrc, unsigned char* strKey, unsigned char* strDest, char flag)
{
	int i,j;
	unsigned char subKey[16][48+1],byte8[8+1],bits[64+1],strTmp[64+1];
	unsigned char L0[32+1],R0[32+1],Lx[32+1],Rx[32+1];
	
	if(!( flag == 'e' || flag == 'E' || flag == 'd' || flag == 'D'))
		return -1;
	if(strSrc == NULL || strKey == NULL)
		return -2;
	
	if(flag == 'e' || flag == 'E')
	{
		memset(byte8,0,sizeof(byte8));
		BCDToByte(strKey, 16, byte8);
		memset(bits,0,sizeof(bits));
		ByteToBit(byte8, 8, bits);
		
		Des_GenSubKey(bits,subKey);
		
		BCDToByte(strSrc, 16, byte8);
		ByteToBit(byte8, 8, bits);
		Des_IP(bits, strTmp);
		memcpy(L0,strTmp,32);
		memcpy(R0,strTmp+32,32);
		
		for(i=0;i<16;i++)
		{
			memcpy(Lx,R0,32);
			Des_F(R0,subKey[i],Rx);
			Do_XOR(L0,32,Rx);
			memcpy(L0,Lx,32);
			memcpy(R0,Rx,32);
		}
		memcpy(bits,R0,32);
		memcpy(bits+32,L0,32);
		Des_IP_1(bits,strTmp);
		BitToByte(strTmp,64,byte8);
		ByteToBCD(byte8,8,strDest);
	}
	else
	{
		memset(byte8,0,sizeof(byte8));
		BCDToByte(strKey, 16, byte8);
		memset(bits,0,sizeof(bits));
		ByteToBit(byte8, 8, bits);
		
		Des_GenSubKey(bits,subKey);
		
		BCDToByte(strSrc, 16, byte8);
		ByteToBit(byte8, 8, bits);
		Des_IP(bits, strTmp);
		memcpy(L0,strTmp,32);
		memcpy(R0,strTmp+32,32);
		
		for(i=0;i<16;i++)
		{
			memcpy(Lx,R0,32);
			Des_F(R0,subKey[15-i],Rx);
			Do_XOR(L0,32,Rx);
			memcpy(L0,Lx,32);
			memcpy(R0,Rx,32);
		}
		memcpy(bits,R0,32);
		memcpy(bits+32,L0,32);
		Des_IP_1(bits,strTmp);
		BitToByte(strTmp,64,byte8);
		ByteToBCD(byte8,8,strDest);
	}
	
	return 0;
}

//做3DES加密或解密运算
int Do_3DES(unsigned char* strSrc, unsigned char* strKey, unsigned char* strDest, char flag)
{ 
	unsigned char strBCDKey[32+1],strByteKey[16+1];
	unsigned char strMidDest1[16+1],strMidDest2[16+1];
	unsigned char strLKey[16+1],strMKey[16+1],strRKey[16+1];
	
	if(!( flag == 'e' || flag == 'E' || flag == 'd' || flag == 'D'))
		return -1;
	if(strSrc == NULL || strKey == NULL)
		return -2;
	
	if(strlen((char*)strKey) < 32)
		return -3;
	
	if(flag == 'e' || flag == 'E')
	{
		memset(strBCDKey,0,sizeof(strBCDKey));
		memcpy(strBCDKey,strKey,32);
		
		memset(strLKey,0,sizeof(strLKey));
		memcpy(strLKey,strBCDKey,16);
		memset(strRKey,0,sizeof(strRKey));
		memcpy(strRKey,strBCDKey+16,16);
		
		Do_DES(strSrc,strLKey,strMidDest1,'e');
		Do_DES(strMidDest1,strRKey,strMidDest2,'d');
		Do_DES(strMidDest2,strLKey,strMidDest1,'e');
		
		memcpy(strDest,strMidDest1,16);
	}
	else
	{
		memset(strBCDKey,0,sizeof(strBCDKey));
		memcpy(strBCDKey,strKey,32);
		
		memset(strLKey,0,sizeof(strLKey));
		memcpy(strLKey,strBCDKey,16);
		memset(strRKey,0,sizeof(strRKey));
		memcpy(strRKey,strBCDKey+16,16);
		
		Do_DES(strSrc,strLKey,strMidDest1,'d');
		Do_DES(strMidDest1,strRKey,strMidDest2,'e');
		Do_DES(strMidDest2,strLKey,strMidDest1,'d');
		
		memcpy(strDest,strMidDest1,16);
	}
	
	return 0;
}

//对输入的字节串作BCD编码扩展
int ByteToBCD(unsigned char* bytes, int count,unsigned char* strBCD)
{
	unsigned char cTmp;
	int i;
	
	for(i=0;i<count;i++)
	{
		cTmp = (bytes[i] & 0xF0) >> 4;
		strBCD[i*2] = (cTmp > 9) ? cTmp - 10 + 'A' : cTmp + '0';
		cTmp = bytes[i] & 0x0F;
		strBCD[i*2+1] = (cTmp > 9) ? cTmp - 10 + 'A' : cTmp + '0'; 
	}
	
	return (count*2); 
}

//把输入的BCD编码串还原成字节串
int BCDToByte(unsigned char* strBCD, int count, unsigned char* bytes)
{
	unsigned char cTmp;
	int i;
	
	for(i=0;i<count/2;i++)
	{
		cTmp = strBCD[i*2];
		if(cTmp >= 'A' && cTmp <= 'F')
			cTmp = cTmp - 'A' + 10;
		else if(cTmp >= 'a' && cTmp <= 'f')
			cTmp = cTmp - 'a' + 10;
		else
			cTmp &= 0x0F;
		bytes[i] = cTmp << 4;
		cTmp = strBCD[i*2+1];
		if(cTmp >= 'A' && cTmp <= 'F')
			cTmp = cTmp - 'A' + 10;
		else if(cTmp >= 'a' && cTmp <= 'f')
			cTmp = cTmp - 'a' + 10;
		else
			cTmp &= 0x0F;
		bytes[i] += cTmp;
	}
	
	return (count/2);
}

//把字节串变成比特串
int ByteToBit(unsigned char* bytes, int count, unsigned char* strBit)
{
	unsigned char cTmp;
	int i,j;
	
	for(i=0;i<count;i++)
	{
		cTmp = 0x80;
		for(j=0;j<8;j++)
		{
			strBit[i*8+j] = (bytes[i] & cTmp) >> (7-j);
			cTmp = cTmp >> 1;
		} 
	}
	
	return (count*8); 
}

//把比特串变成字节串
int BitToByte(unsigned char* strBit, int count, unsigned char* bytes)
{
	unsigned char cTmp;
	int i,j;
	
	for(i=0;i<(count/8);i++)
	{
		cTmp = 0x00;
		for(j=0;j<8;j++)
		{
			cTmp += (strBit[i*8+j] << (7-j));
		}
		bytes[i] = cTmp; 
	}
	
	return (count/8);
}

//做异或操作
int Do_XOR(unsigned char* strSrc, int count, unsigned char* strDest)
{
	int i;
	
	if(strSrc == NULL || strDest == NULL)
		return -1;
	
	for(i=0;i<count;i++)
		strDest[i] ^= strSrc[i];
	
	return 0;
}

//des算法PC-1变换，把64比特的密钥K变换成56比特
int Des_PC_1(unsigned char* strIn, unsigned char* strOut)
{
	int i;
	
	for(i=0;i<56;i++)
		strOut[i] = strIn[pc_1_table[i]-1];
	
	return 56; 
}

//des算法PC-2变换，把56比特变换成48比特
int Des_PC_2(unsigned char* strIn, unsigned char* strOut)
{
	int i;
	
	for(i=0;i<48;i++)
		strOut[i] = strIn[pc_2_table[i]-1];
	
	return 48;
}

//des算法的循环左移位运算
int Des_LS(unsigned char* strIn, int count, unsigned char* strOut)
{
	int i;
	
	for(i=0;i<28;i++)
//		strOut[i] = strIn[(i+count)];
	strOut[(i-count+28)%28] = strIn[i];
	return 28; 
}

//des算法中通过父密钥产生16个48比特位的子密钥
int Des_GenSubKey(unsigned char* strKey, unsigned char strSubKey[16][48+1])
{
	unsigned char tmp[56+1],C0[28+1],D0[28+1],Cx[28+1],Dx[28+1];
	int i,j;
	
	memset(tmp,0,sizeof(tmp));
	memset(C0,0,sizeof(C0));
	memset(D0,0,sizeof(D0));
	memset(Cx,0,sizeof(Cx));
	memset(Dx,0,sizeof(Dx));
	
	Des_PC_1(strKey, tmp);
	
	memcpy(C0,tmp,28);
	memcpy(D0,tmp+28,28);
	
	for(i=0;i<16;i++)
	{
		Des_LS(C0,ls_num_table[i],Cx);
		Des_LS(D0,ls_num_table[i],Dx);
		memcpy(tmp,Cx,28);
		memcpy(tmp+28,Dx,28);
		Des_PC_2(tmp,strSubKey[i]);
		memcpy(C0,Cx,28);
		memcpy(D0,Dx,28);
	}
	
	return 0;
}

//des算法IP置换
int Des_IP(unsigned char* strIn, unsigned char* strOut)
{
	int i;
	
	for(i=0;i<64;i++)
		strOut[i] = strIn[ip_table[i]-1];
	
	return 64;
}

//des算法IP-1置换
int Des_IP_1(unsigned char* strIn, unsigned char* strOut)
{
	int i;
	
	for(i=0;i<64;i++)
		strOut[i] = strIn[ip_1_table[i]-1];
	
	return 64;
}

//des算法e变换，将32比特变成48比特
int Des_E(unsigned char* strIn, unsigned char* strOut)
{
	int i;
	
	for(i=0;i<48;i++)
		strOut[i] = strIn[e_table[i]-1];
	
	return 48;
}

//des算法P变换
int Des_P(unsigned char* strIn, unsigned char* strOut)
{
	int i;
	
	for(i=0;i<32;i++)
		strOut[i] = strIn[p_table[i]-1];
	
	return 32;
}

//des算法S盒变换
int Des_S_Box(unsigned char* strIn, int nSBox, unsigned char* strOut)
{
	int x,y,i,nValue;
	unsigned char c;
	
	if(nSBox < 1 || nSBox > 8)
		return -1;
	
	x = strIn[0] * 2 + strIn[5];
	y = strIn[1] * 8 + strIn[2] * 4 + strIn[3] * 2 + strIn[4];
	
	nValue = s_box_table[nSBox-1][x][y];
	c = 0x08;
	for(i=0;i<4;i++)
	{
		strOut[i] = (nValue & c) >> (3 - i);
		c = c >> 1; 
	}
	
	return 4;
}

//des算法F函数，对Ri-1和Ki进行运算
int Des_F(unsigned char* strR, unsigned char* strK, unsigned char* strOut)
{
	int i,j,k;
	unsigned char strAftE[48],strPreP[32],sbIn[8][6],sbOut[8][4];
	
	for(i=0;i<48;i++)
		strAftE[i] = strR[e_table[i]-1];
	Do_XOR(strK, 48, strAftE);
	
	for(i=0;i<8;i++)
		for(j=0;j<6;j++)
			sbIn[i][j] = strAftE[i*6+j];
		
		for(i=0;i<8;i++)
			Des_S_Box(sbIn[i], i+1, sbOut[i]);
		
		for(i=0;i<32;i++)
			strPreP[i] = sbOut[i/4][i%4];
		Des_P(strPreP, strOut);
	
	return 32;
}

#ifdef __cplusplus
}
#endif

int MicNumDecode::setSerialnum(char* num){
	if(num == nullptr || strlen(num)< 14)
		return -1;
	memset(key16,0,MAXBUFSIZE_MICNUM);
	memset(micnum,0,MAXBUFSIZE_MICNUM);
	memset(decodenum,0,MAXBUFSIZE_MICNUM);
	sprintf((char*)key16,"%s","TLCYTLKGTLCYTLKG");
	sprintf((char*)micnum,"%s",num);
	Do_DES(micnum,key16,decodenum,'d');
	DLOG("decodenum = %s \n",decodenum);
	if(strlen((char*)decodenum) >= 16){
		int hidflag = 0;
		DLOG("hidflag = %s \n",&decodenum[strlen((char*)decodenum)-2]);
		sscanf((char*)&decodenum[strlen((char*)decodenum)-2],"%02x",&hidflag);
		ishidmic = hidflag & 0x1;
		hidkeyid = (hidflag >> 1) & 0x7f;
	}else{
		ishidmic = false;
		hidkeyid = 0;
	}

	return 0;
}
char* MicNumDecode::getdecode(){
	return (char*)decodenum;
}
bool MicNumDecode::isHIDdmic(){
	return ishidmic;
}
int MicNumDecode::hidkeyID(){
	return hidkeyid;
}

int main(int argc,char** argv)
{
	
	unsigned char src16[16+1],key16[16+1],key48[48+1],dest16[16+1];
	memset(key16,0,sizeof(key16));
	sprintf((char*)key16,"TLCYTLKGTLCYTLKG");
	if(strcmp(argv[1],"-e") == 0)
	{
		FILE* srcfp = fopen("date.f","r");
		FILE* didfp = fopen("did.f","w+");
		FILE* md5fp = fopen("md5.f","w+");
//		hashwrapper *myWrapper = new md5wrapper();
		char s1[100] ={};
		char ecodetmp[100] = {};
		char ecodemd5[1024] ={};
		while((fgets(s1,100,srcfp)))
		{
//			printf("fgets = %s\n",s1);
//			printf("this char 13 is :%c\n",s1[13]);
			memset(src16,0,sizeof(src16));
			memcpy(src16,s1,14);
			memset(dest16,0,sizeof(dest16));
			Do_DES(src16,key16,dest16,'e');
//			printf("dest16 = %s\n",dest16);
			memset(ecodetmp,0,99);
			sprintf(ecodetmp,"\n%s",dest16);
			fwrite(ecodetmp,17,1,didfp);
//			std::string encodestr;
//			encodestr.assign((char*)dest16);
//			std::string md5str = myWrapper->getHashFromString(encodestr);
//			sprintf(ecodemd5,"\n%s",md5str.c_str());
//			printf("md5str = %s",ecodemd5);
//			fwrite(ecodemd5,1,strlen(ecodemd5),md5fp);
		}
		fclose(srcfp);
		fclose(didfp);
		fclose(md5fp);
	}
	else if(strcmp(argv[1],"-d") == 0)
	{
		FILE* didfp = fopen("did.f","r");
		FILE* resrcfp = fopen("ddid.f","w+");
		char s1[100] ={};
		char ecodetmp[100] = {};
		
		while((fgets(s1,100,didfp)))
		{
//			printf("fgets = %s\n",s1);
//			printf("this char 15 is :%c\n",s1[15]);
			memset(src16,0,sizeof(src16));
			memcpy(src16,s1,16);
			memset(dest16,0,sizeof(dest16));
			Do_DES(src16,key16,dest16,'d');
//			printf("dest16 = %s\n",dest16);
			memset(ecodetmp,0,99);
			sprintf(ecodetmp,"\n%s",dest16);
			fwrite(ecodetmp,15,1,resrcfp);
		}
		fclose(resrcfp);
		fclose(didfp);
		
		
		
	}
	
	return 0;
}


//主函数
int main1(int argc, char** argv)
{
	unsigned char src16[16+1],key16[16+1],key48[48+1],dest16[16+1];
	
	if(argc != 3)
	{
		fprintf(stderr,"Usage: [%s -e|-d s|3]\n",argv[0]);
		exit(1); 
	}
	
	if(strcmp(argv[2],"-s") == 0)
	{
		if(strcmp(argv[1],"-e") == 0)
		{
			fprintf(stderr,"Please input the string that you want to encrypt(16 hex number):\n");
			memset(src16,0,sizeof(src16));
			scanf("%s",src16);
			fprintf(stderr,"Please input the Key string(16 hex number):\n");
			memset(key16,0,sizeof(key16));
			scanf("%s",key16);
			memset(dest16,0,sizeof(dest16));
			Do_DES(src16,key16,dest16,'e');
			fprintf(stderr,"Result: [%s]\n",dest16);
		}
		else if(strcmp(argv[1],"-d") == 0)
		{
			fprintf(stderr,"Please input the string that you want to decrypt(16 hex number):\n");
			memset(src16,0,sizeof(src16));
			scanf("%s",src16);
			fprintf(stderr,"Please input the Key string(16 hex number):\n");
			memset(key16,0,sizeof(key16));
			scanf("%s",key16);
			memset(dest16,0,sizeof(dest16));
			Do_DES(src16,key16,dest16,'d');
			fprintf(stderr,"Result: [%s]\n",dest16);
		}
		else
			return -1;
	}
	else if(strcmp(argv[2],"-3") == 0)
	{
		if(strcmp(argv[1],"-e") == 0)
		{
			fprintf(stderr,"Please input the string that you want to encrypt(16 hex number):\n");
			memset(src16,0,sizeof(src16));
			scanf("%s",src16);
			fprintf(stderr,"Please input the Key string(16 hex number):\n");
			memset(key48,0,sizeof(key48));
			scanf("%s",key48);
			memset(dest16,0,sizeof(dest16));
			Do_3DES(src16,key48,dest16,'e');
			fprintf(stderr,"Result: [%s]\n",dest16);
		}
		else if(strcmp(argv[1],"-d") == 0)
		{
			fprintf(stderr,"Please input the string that you want to decrypt(16 hex number):\n");
			memset(src16,0,sizeof(src16));
			scanf("%s",src16);
			fprintf(stderr,"Please input the Key string(16 hex number):\n");
			memset(key48,0,sizeof(key48));
			scanf("%s",key48);
			memset(dest16,0,sizeof(dest16));
			Do_3DES(src16,key48,dest16,'d');
			fprintf(stderr,"Result: [%s]\n",dest16);
		}
		else
			return -1;
	}
	else
		return -1;
	
	return 0;  
}



