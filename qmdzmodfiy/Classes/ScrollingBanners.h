#ifndef _SCROLLINGBANNERS_H_
#define _SCROLLINGBANNERS_H_

#include "cocos2d.h"

class ScrollingBanners :public cocos2d::LayerColor
{
public:
	static ScrollingBanners* creatScrollingBanners() ;

	void callScrollTextMoveEnd() ;
	void callNextScrollText() ;

	void reSetScorlllBanners() ;
	void callScrollBannersMove() ;

	void checkVisible() ;
private:
	bool m_isScrollTextMove ;
	int m_moveLableCount ;//��ǰ��ʾ�е����������


};

#endif