//
// Created by TLKG-014 on 2020/7/2.
//

#ifndef WUKONG_DEMO_LOWVERSION_FINDCARDHID_H
#define WUKONG_DEMO_LOWVERSION_FINDCARDHID_H

#include <mutex>
#include "findcardtype.h"
class MicNumDecode;
class FindCardAdapter;
class FindCardHid{
private:
    FindCardHid();
    FindCardAdapter* findcard;
    MicNumDecode* micNumDecode;
    static FindCardHid* findCardHid;
    int FindcardInit();
    char* Getdecode();
    int SetSerialnum(char* num);
    bool IsHIDdmic_do();
    int HidkeyID_do();
//    std::mutex mutex;
public:
    /**
     * 单例模式
     * @return
     */
    static FindCardHid* getIns();

    /**
     * 获取card_num 声卡的 采样率和支持的声道
     * @param card_num
     * @return
     */
    FindCardHid* GetAudioInfo(int card_num);
    /**
     * FindCardHid* GetAudioInfo(int card_num);返回
     * 支持的采样率数量
     * 如果 -1
     * 代表不支持任何采样率
     * 则 rate_table[] 中数值无效
     */
    int nr_rates;
    /**
     * FindCardHid* GetAudioInfo(int card_num);返回
     * 支持的采样率数组
     */
    int rate_table[24];
    /**
     * FindCardHid* GetAudioInfo(int card_num);返回
     * 支持的声道数
     */
    int channels;

    int SetMicPriority(const char* mic,int priority,int device = 0,bool islinein = false);
    int SetMask(const char* maskmic);
    void SetNetPolicy();
    void SetCollectPolicy(int policy,int flag = 0);
    int FilterInit();
    int CollectPolicyFilter(char* buffer,int size);
    int GetSerialnum(MicString* micstr);
    int GetInUseDeviceInfo(MicString* micstr);
    int GetCards(cardstrdevice* rescsd);

    /**
     * 是否是hid麦克风
     * @return
     * -1 不是天籁麦克风
     * 0  是天籁麦克风不支持hid
     * 1 是天籁麦克风支持hid
     */
    int IsHIDdmic();
    /**
     * hid麦克风
     * @return
     */
    int HidkeyID();
    ~FindCardHid();
};



#endif //WUKONG_DEMO_LOWVERSION_FINDCARDHID_H
