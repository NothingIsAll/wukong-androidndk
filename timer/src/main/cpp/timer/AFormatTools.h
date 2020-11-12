//
// Created by TLKG-014 on 2019/2/27.
//

#ifndef ANFILEASYNCIO_AFORMATTOOLS_H
#define ANFILEASYNCIO_AFORMATTOOLS_H


class AFormatTools {
private:
    int samplerate;
    int channel;
    int deepbit;
    int bitperbyte;
public:
    AFormatTools();
    virtual long converTtoF(long time); //ms
    virtual long converFtoT(long frames);
    virtual long converBtoF(long bytesize);
    virtual long converFtoB(long frames);
    virtual long converTtoB(long time); //ms
    virtual long converBtoT(long bytesize);

    virtual int getsamplerate();
    virtual int getchannel();
    virtual int getdeepbit();
    virtual void setsamplerate(int rate);
    virtual void setchannel(int channel);
    virtual void setdeepbit(int bit);

};


#endif //ANFILEASYNCIO_AFORMATTOOLS_H
