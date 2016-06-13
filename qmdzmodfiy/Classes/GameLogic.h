#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#include "GameCommon.h"

#define FULL_COUNT					    52									//ȫ����Ŀ
#define MAX_COUNT						2									//�����Ŀ
#define MAX_CENTERCOUNT					5									//�����Ŀ

//��ֵ����
#define	LOGIC_MASK_COLOR			0xF0								//��ɫ����
#define	LOGIC_MASK_VALUE			0x0F								//��ֵ����

//�˿�����
#define CT_SINGLE					1									//��������
#define CT_ONE_LONG					2									//��������
#define CT_TWO_LONG					3									//��������
#define CT_THREE_TIAO				4									//��������
#define	CT_SHUN_ZI					5									//˳������
#define CT_TONG_HUA					6									//ͬ������
#define CT_HU_LU					7									//��«����
#define CT_TIE_ZHI					8									//��֧����
#define CT_TONG_HUA_SHUN			9									//ͬ��˳��
#define CT_KING_TONG_HUA_SHUN		10									//�ʼ�ͬ��˳

//ʤ����Ϣ�ṹ
struct UserWinList
{
	unsigned char bSameCount;
	unsigned short wWinerList[GAME_PLAYER];
};

//�����ṹ
struct tagAnalyseResult
{
	unsigned char cbFourCount;						//������Ŀ
	unsigned char cbThreeCount;						//������Ŀ
	unsigned char cbLONGCount;						//������Ŀ
	unsigned char cbSignedCount;					//������Ŀ
	unsigned char cbFourLogicVolue[1];				//�����б�
	unsigned char cbThreeLogicVolue[1];				//�����б�
	unsigned char cbLONGLogicVolue[2];				//�����б�
	unsigned char cbSignedLogicVolue[5];			//�����б�
	unsigned char cbFourCardData[MAX_CENTERCOUNT];	//�����б�
	unsigned char cbThreeCardData[MAX_CENTERCOUNT];	//�����б�
	unsigned char cbLONGCardData[MAX_CENTERCOUNT];	//�����б�
	unsigned char cbSignedCardData[MAX_CENTERCOUNT];//������Ŀ
};

class CGameLogic
{
public:
	CGameLogic();
	virtual ~CGameLogic();

private:
	static unsigned char m_cbCardData[FULL_COUNT];				//�˿˶���

public:
	void SortCardList(unsigned char cbCardData[], unsigned char cbCardCount);
	void RandCardList(unsigned char cbCardBuffer[], unsigned char cbBufferCount);

public:
	unsigned char GetCardType(unsigned char cbCardData[], unsigned char cbCardCount);
	unsigned char GetCardValue(unsigned char cbCardData) { return cbCardData&LOGIC_MASK_VALUE; }
	unsigned char GetCardColor(unsigned char cbCardData) { return cbCardData&LOGIC_MASK_COLOR; }

public:
	unsigned char GetCardLogicValue(unsigned char cbCardData);
	unsigned char CompareCard(unsigned char cbFirstData[], unsigned char cbNextData[], unsigned char cbCardCount);
	void AnalysebCardData(const unsigned char cbCardData[], unsigned char cbCardCount, tagAnalyseResult & AnalyseResult);
	unsigned char FiveFromSeven(const unsigned char cbHandCardData[],unsigned char cbHandCardCount,const unsigned char cbCenterCardData[],unsigned char cbCenterCardCount,unsigned char cbLastCardData[],unsigned char cbLastCardCount);
	unsigned char FiveFromSix(const unsigned char cbHandCardData[],unsigned char cbHandCardCount,const unsigned char cbCenterCardData[],unsigned char cbCenterCardCount,unsigned char cbLastCardData[],unsigned char cbLastCardCount);
	//bool SelectMaxUser(unsigned char bCardData[GAME_PLAYER][MAX_CENTERCOUNT], UserWinList &EndResult, const __int64 lAddScore[]);

	enum TwoCardType
	{
		Single,
		DuiZi,
		TongHua,
	};

	enum CardValueScope
	{
		CardValue2To5, 
		CardValue5To10,
		CardValue10ToA
	};

	struct TwoCardResult
	{
		unsigned char cbCardType;
		CardValueScope smallCardValueScope;
		CardValueScope bigCardValueScope;
	};
	CardValueScope GetCardValueScope(unsigned char cbCardValue);
	TwoCardResult AnalyseTwoCard(const unsigned char cbCard[2]);
};

#endif