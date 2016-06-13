
#ifndef _ChooseFamilyIcon_H__
#define _ChooseFamilyIcon_H__

#include "GameDialog.h"
#include "CCScrollView.h"
#include "vector"
#include "cocos2d.h"
#include "ui/UIEditBox/UIEditBox.h"

class MenuItemSpriteWithLabel;
class MenuItemScale9SpriteWithLabel;
class HttpSprite;
class FrameSprite;
class LayerButton;

struct HeadItem 
{
	HttpSprite          *m_httpSprite;
	LayerButton         *m_layerBt;
};
class MyFamily;
class ChooseFamilyIcon : public GameDialog
{
public:
	static ChooseFamilyIcon* creatWithLayer(MyFamily* layer) ;
	bool initWithLayer(MyFamily* layer) ;
	CREATE_FUNC(ChooseFamilyIcon);

	void MyAvatar(cocos2d::Ref* pSender);
	void PersonalInfo(cocos2d::Ref* pSender);

	void UpdatePersonalInfo();
	void SelectAvatar(unsigned  uAvatarID, unsigned uIdx);

	void TakePhoto(cocos2d::Ref* pSender);
	void SelectFromAlbum(cocos2d::Ref* pSender);

	void ExpandGender();
    void onMenuItemCloseSelected(cocos2d::Ref * ref);
		MenuItemSpriteWithLabel *m_btMenuItemClose;
protected:
	virtual bool init();
	

private:
	MyFamily* m_pLayer ;

	cocos2d::Sprite* spriteTitle;
	MenuItemScale9SpriteWithLabel                     *m_btTakePhoto;                 //����
	MenuItemScale9SpriteWithLabel                     *m_btSelectFromAlbum;           //�����ѡ��

	cocos2d::Label                              *m_lableWarn;                   //����
	cocos2d::extension::ScrollView              *m_ScrollMyAvatar;              //ͷ�������ͼ

	FrameSprite                                 *m_SpriteUsing;                 //ʹ��ͷ��
	std::vector<HeadItem>                       m_vecAvatarItem;
};

#endif