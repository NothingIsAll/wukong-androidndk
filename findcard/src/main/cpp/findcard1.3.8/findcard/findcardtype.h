//
// Created by TLKG-014 on 2020/7/2.
//

#ifndef WUKONG_DEMO_LOWVERSION_FINDCARDTYPE_H
#define WUKONG_DEMO_LOWVERSION_FINDCARDTYPE_H

class MicString
{
public:
    MicString();
    char* c_char();
    int length();
    int putstring(const char* buffer,int size);
    void clean();
private:
    int len;
    char micstring[1024];
};

struct cardstrdevice
{
    char str[1024];
    char pcm[1024];
    int Card;
    int device;
    bool isline;
    int cadsnum;
};

#endif //WUKONG_DEMO_LOWVERSION_FINDCARDTYPE_H
