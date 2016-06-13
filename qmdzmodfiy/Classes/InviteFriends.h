#ifndef _INVITEFRIENDS_H_
#define  _INVITEFRIENDS_H_


#include "cocos2d.h"
#include "GameDialog.h"
#include "CCScrollView.h"

#include "FrameSpriteButton.h"


class MenuItemFrameSprite ;
class HttpSprite;
struct FamilyRoleBaseInfo;
class FrameSpriteButton;
class MenuItemScale9Sprite;

class InviteFriends :public GameDialog
{
public:
	CREATE_FUNC(InviteFriends) ;

	bool init() ;

	void  updateView() ;


	void removeRoleItem(std::string uid);
protected:
	void onMenuItemSelected(cocos2d::Ref * ref) ;


	struct RoleIconItem
	{
		cocos2d::Sprite *m_pSpriteSelect;			    // ������ͼ�еı���	
		cocos2d::Node* m_pSpriteBgItem ;
		LayerButton *m_pBtDetail;
		HttpSprite *m_pSpriteRoleIcon;	
		cocos2d::Label *m_uName;	
		unsigned m_uid ;
	};

	//��ȡ�б���ʾ
	RoleIconItem *GetFamilyListItem(FamilyRoleBaseInfo baseInfo);
	void UpdateItem(InviteFriends::RoleIconItem *item, const FamilyRoleBaseInfo& roleInfo);
	void menuClickBgItem(FamilyRoleBaseInfo baseInfo,InviteFriends::RoleIconItem *item);
	virtual void onGrabTouchBegan(bool bHitDialog);


	void clearAllSelect() ;
private:
	cocos2d::Label                              *m_lableTips;                   //��ʾ
	cocos2d::extension::ScrollView              *m_ScrollView;					//������ͼ
	cocos2d::Label                              *m_lableTipsup;                   //��ʾ
	cocos2d::Label                              *m_lableTipsdown;                   //��ʾ

	MenuItemScale9Sprite                         *m_bttoViceShaikh ;
	MenuItemScale9Sprite                         *m_btclose ;


	std::vector <RoleIconItem*>		        m_vecFriendsOld;		//ԭʼ����

	std::vector<int>                        m_vecInviteID ;

	GameLayer                               *m_layerTop;
	GameLayer                               *m_layerBottom;
};


#endif

