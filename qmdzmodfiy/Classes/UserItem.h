#ifndef _USERITEM_H_
#define _USERITEM_H_
/************************************************************************/
/* 
modify by sunjinfang 2015-9-15
�̳���ĵ��� �Զ�Ϊʹ��״̬


*/
/************************************************************************/

#include "cocos2d.h"
#include "GameDialog.h"
#include "UICommon.h"
//#include "FrameSpriteButton.h"

class DataLoading ;
class HttpSprite ;
class FrameScale9SpriteButton;
class FrameSprite;
struct UserItemInfo ;
class UserItem : public GameDialog
{
public:
	CREATE_FUNC(UserItem) ;
	bool init() ;

	void updateItemView() ;
	void setShowDataLoading(bool flag) ;
	void setVisible(bool bVisible) ;
public:

	struct UItemLabel
	{
		FrameSprite		    *m_pSpriteBGItem;		// ������ͼ�еı���
		HttpSprite			*m_pSpriteIcon;			// ͷ��
		cocos2d::Sprite	    *m_pSpriteCountBlock ;	//��������������
		cocos2d::Label		*m_pLabelCount ;		//��������
		cocos2d::Label		*m_pLabelName;			//��������
		cocos2d::Label		*m_pLabelExpDate;		//��Ч��
		cocos2d::Label		*m_pLabelDes;			//��������
		FrameScale9SpriteButton   *m_pBt;					//��ť��������ʾ����	
		cocos2d::Label		*m_pLabelBtDes;			//��ť��������
		unsigned			*m_count ;				//
	};
	//��ȡ�б���ʾ
	UItemLabel* GetListItem(const UserItemInfo& itemInfo);
	void UpdateItem(UserItem::UItemLabel *item, const UserItemInfo& itemInfo);

private:
	void menuClickItem(UserItemInfo baseInfo);		//���߹��ܻص�
	void callItemShop() ;							//�򿪵����̳�
	void cleanView() ;
private:
	cocos2d::extension::ScrollView* m_ScrollView ;
	cocos2d::Size sizeListView;

	std::vector<UItemLabel*>	    m_vecItemListOld;
	DataLoading* s_dataLoading ;


	cocos2d::Node	*m_withoutItemLayer ;			//û�е���ʱ�Ľ�����ʾ
	cocos2d::Sprite *m_spriteGril ;					//��ʾ������
	cocos2d::Label *m_lableWithoutItem ;			//û�е��ߵ���ʾ
	FrameScale9SpriteButton   *m_btItemShop;				//��ť��������ʾ����

};




#endif