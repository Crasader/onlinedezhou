//#ifndef _GAMEFAMILY_H_
//
//#define _GAMEFAMILY_H_
//
//#include "cocos2d.h"
//#include "GameDialog.h"
//#include "UICommon.h"
//
//class HttpSprite;
//class LayerButton;
//class FrameSpriteButton;
//class FrameScale9SpriteButton;
//class MenuItemSpriteWithLabel;
//class GameHall;
//class TouchGrabber;
//class FrameSprite;
//
//class MyFamily;
//class ShowFamily;
//
//class DataLoading ;
//struct FamilyInfo;
//struct GlobalMyFamilyInfo;
//
//class GameFamily : public GameDialog, public cocos2d::ui::EditBoxDelegate
//{
//public:
//	CREATE_FUNC(GameFamily) ;
//	bool init() ;
//	
//	void setVisible(bool bVisible);
//	void setOnVisible(bool bVisible);
//	void initFamilyShow() ;
//	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox) override;
//	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
//	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
//	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
//
//	void showMyFamily(bool flag);
//
//	void UpdateView();
//	void UpdateItemView( const FamilyInfo& userInfo);
//	void AppadnItemView( const FamilyInfo& userInfo);
//	void RemoveItemView( unsigned uUserID);
//
//	//void showTargetFamily(bool flag);
//
//	void updateRankList() ;
//	
//	void updateMyFamilyData() ;
//
//	void updateTargetFamilyData() ;
//
//	void updateMyFamilyRoleRankList() ;
//
//	void setCloseButtonShow(bool flag) ;
//private:
//
//
//	 void callScaleBig(cocos2d::Node* node) ;
//	 void callScaleSmall(cocos2d::Node* node) ;
//
//	void onFamilyMenuItemClick(cocos2d::Ref *pItem,cocos2d::ui::TouchEventType type);
//
//
//	//��ʼ�����ֲ���ť������״̬
//	void showFamilyLayer(int index) ;
//	//��ʼ�����ֲ�������������״̬
//	void showFamilyInfoLayer(int index) ;
//
//
//	virtual void onMenuItemCloseSelected(cocos2d::Ref * ref);
//
//	void onButtonCallBack(cocos2d::Ref *pItem,cocos2d::ui::TouchEventType type) ;
//
//
//	//����͸
//	void menuClickLeft(Ref* pSender);
//	void menuClickRight(Ref* pSender);
//	//������ֲ�
//	void menuClickJiaRu(unsigned ufamilyID);
//
//	//��ʾ���ֲ���Ϣ
//	void menuClickBgItem(unsigned m_familyID);
//
//	//�������ֲ�
//	void menuClickCeatFamily(std::string name);
//
//	bool checkTextChineseOrNumberOrLetter(std::string str) ;
//
//	char* QXUtf82Unicode(const char* utf, size_t *unicode_number)  ;
//
//	void updateCreatFamilyLayer() ;
//
//	void updateBuyVip(unsigned uDataType) ;
//
//	void setShowDataLoading(bool flag) ;
//public:
//
//
//	struct FamilywListItem
//	{
//		FrameSprite *m_pSpriteBgItem;			    // ������ͼ�еı���	
//		LayerButton *m_pBtDetail;
//		HttpSprite *m_pSpriteFamilyTouXiang;	
//		cocos2d::Label* m_familyName;
//		cocos2d::Sprite *m_pSpriteStar;
//		cocos2d::Label* m_labellevel;
//
//		unsigned m_level; //id	
//		unsigned m_curRoleCount;
//		unsigned m_maxRoleCount;
//		cocos2d::Label* m_labelRoleCount;
//		cocos2d::Label* m_roleCount;
//		FrameScale9SpriteButton *m_pBtJiaRu;					//���밴ť
//		unsigned m_familyID; //id
//		cocos2d::Label* m_labelRankIndex;
//		unsigned m_familyRankID;//����
//		FrameSprite* m_spriteRank;
//	};
//
//	//��ȡ�б���ʾ
//	FamilywListItem *GetFamilyListItem(unsigned m_familyID);
//	void UpdateItem(GameFamily::FamilywListItem *item, const FamilyInfo& followInfo);
//
//
//private:
//	DataLoading* s_dataLoading ;
//	//MyFamily* m_myFamily;
//	//ShowFamily* m_targetFamily;
//
//	//���ֲ���ͼ���
//	cocos2d::extension::ScrollView			*m_pScrollView;			
//	std::vector<FamilywListItem*>		m_vecFollowListInfoOld;		//ԭʼ����
//	std::vector<FamilywListItem*>		m_vecFollowListInfoNew;
//	cocos2d::Size sizeListView;
//
//	TouchGrabber *m_pTouchGrabberBG;
//
//
//	cocos2d::Node* s_uiroot ;
//
//	cocos2d::ui::Layout* s_familybackgroundLayer ;//���ֲ�������
//	cocos2d::ui::Layout* s_rankLayer ; //���ֲ�����
//	cocos2d::ui::Layout* s_myFamilyLayer ;//�ҵľ��ֲ�
//	cocos2d::ui::Layout* s_myFamilyInof ;//���ֲ�����
//	cocos2d::ui::Layout* s_creatFamilyLayer ;//�������ֲ�
//
//
//
//	//�������ֲ������ж�
//	cocos2d::ui::Layout* s_cloudCreat ;
//	cocos2d::ui::Layout* s_vipLow ;
//	cocos2d::ui::Layout* s_hasFamily ;
//
//	cocos2d::ui::Button* s_buttonShop ;
//	cocos2d::ui::Button* s_buttonExit ;
//
//	//����ť
//	cocos2d::ui::Button* s_button_myFamilyMenu[4]; 
//	cocos2d::ui::Text*   s_button_myFamilyMenuText[4]; 
//
//
//
//	cocos2d::ui::EditBox* s_editBoxCreatFamliy;//�������ֲ�����
//	cocos2d::ui::Text*   s_editBoxFamilyName; 
//
//	cocos2d::ui::Layout* s_familyManager[4];
//
//
//	//�ҵľ��ֲ�
//	cocos2d::ui::Button* buttomMyFamilyCreatFamily;
//	cocos2d::ui::Button* buttomMyFamilyJoinFamily;
//
//	cocos2d::ui::EditBox* s_editBoxSearch;//���ֲ�����
//	//�������ֲ�
//	cocos2d::ui::Button* buttomCreatFamily;
//
//
//
//	std::string s_familyName ;
//
//	GameLayer                               *m_layerTop;
//	GameLayer                               *m_layerBottom;
//
//
//
//	cocos2d::Sprite* spriteStar[4] ;
//
//	int m_curLayerIndex ;
//
//	cocos2d::Sprite* spriteFamilyTips ;
//};
//
//
//
//#endif
