#ifndef __GUIDETIPS_H__
#define __GUIDETIPS_H__

#include "cocos2d.h"

//    <data id="1" status="0" des="��Ů������"/>
//    <data id="2" status="0" des="���泡����"/>
//    <data id="3" status="0" des="���忪������"/>
//    <data id="4" status="0" des="��ӹ�ע����"/>
//    <data id="5" status="0" des="���ѹ�������"/>
//    <data id="6" status="0" des="��Ƶ6�˳��л�"/>
//    <data id="7" status="0" des="SNG������"/>
struct GuideItemInfo
{
    int id;
    bool status;
};

enum
{
    DelaerGuide=0,//������Ů���б�
    NormalSceneGuide,//��ͨ��������
    VipDefineRoomGuide,//VIP�Զ��忪��
    AddAttentionGuide,//��Ϸ�мӹ�ע
    FriendListGuide,//��Ϸ�к����б�
    SwitchvideoOr6Guide,//�л���Ƶ�������˳�
    SNGGuide,//SNG����
    MTTHelp,//MTT����
    MTTSign,//MTT����������
    MTTFilter,//MTT����ɸѡ
    MTTDescription,//MTT���峡����Ϣ
    MTTPageUpAndDown//MTT���·�ҳ
};

#define GuideInfo ReadGuideInfo::getInstance()

//1.strMask:����ģ��
//2.pos    :ģ������
//3.bottom..:�װ�
cocos2d::ClippingNode* CreateClippingMask(std::string strMask, cocos2d::Vec2 pos, cocos2d::Node* bottomBoard, std::string strMask1="", cocos2d::Vec2 pos1=cocos2d::Vec2(0,0));

class GuideTips : public cocos2d::Layer
{
public:
    //static GuideTips* getInstance();
    static GuideTips* create(std::string strBg, std::string strFlag);
    bool init(std::string strBg, std::string strText);
    void setBgPosition(cocos2d::Vec2 vec);
    void setFlagPosition(cocos2d::Vec2 vec);
    void ResetBgSprite(std::string strBg);
    void addFlagSpriteAndPos(std::string strFlag, cocos2d::Vec2 pos);
    void setVisible(bool bVisible);
    void setTipsID(unsigned uID);
protected:

private:
    //static GuideTips*       m_GuideTips;
    cocos2d::EventListenerTouchOneByOne *m_listenerTouch;
    cocos2d::LayerColor*    m_layerColorBg;
    cocos2d::Sprite*        m_bgSprite;
    cocos2d::Sprite*        m_flagSprite;
    unsigned                m_uTipsID;
};

class ReadGuideInfo
{
public:
    static ReadGuideInfo* getInstance();
    ReadGuideInfo();
    //�ӷ���˻�ȡÿ�����������״̬
    void getAllGuideInfo(unsigned status);
    //��ȡ������Ϣ
    bool readGuideInfo(unsigned id);
    //�������޸�״̬
    void ModifyGuideInfo(unsigned id, unsigned status = 1);
    //����vector
    void clearOldGuideInfo();
    std::vector<GuideItemInfo> m_vecGuideInfo;
private:
    static ReadGuideInfo* m_ReadGuideInfo;
    std::vector<unsigned> m_vecGuideStatus;
};

#endif