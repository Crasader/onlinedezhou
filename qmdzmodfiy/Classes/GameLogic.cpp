#include "GameLogic.h"
#include <string.h>
#include <stdlib.h>

#define CountArray(arr) (sizeof(arr) / sizeof(arr[0]))

unsigned char CGameLogic::m_cbCardData[FULL_COUNT]=
{
	0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,	//���� A - K
	0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,	//÷�� A - K
	0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,	//���� A - K
	0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,	//���� A - K
};

CGameLogic::CGameLogic()
{
}

CGameLogic::~CGameLogic()
{
}

void CGameLogic::RandCardList(unsigned char cbCardBuffer[], unsigned char cbBufferCount)
{
	//����׼��
	unsigned char bCardCount = CountArray(m_cbCardData);
	unsigned char cbCardData[CountArray(m_cbCardData)];
	memcpy(cbCardData, m_cbCardData,sizeof(m_cbCardData));

	//�����˿�
	unsigned char cbRandCount=0,cbPosition=0;
	do
	{
		cbPosition=rand()%(bCardCount-cbRandCount);
		cbCardBuffer[cbRandCount++]=cbCardData[cbPosition];
		cbCardData[cbPosition]=cbCardData[bCardCount-cbRandCount];
	} while (cbRandCount<cbBufferCount);
}

//��ȡ����
unsigned char CGameLogic::GetCardType(unsigned char cbCardData[], unsigned char cbCardCount)
{
	//����У��
	if(cbCardCount !=MAX_CENTERCOUNT) return 0;

	//��������
	bool cbSameColor=true,bLineCard=true;
	unsigned char cbFirstColor=GetCardColor(cbCardData[0]);
	unsigned char cbFirstValue=GetCardLogicValue(cbCardData[0]);

	//���η���
	for (unsigned char i=1;i<cbCardCount;i++)
	{
		//���ݷ���
		if (GetCardColor(cbCardData[i])!=cbFirstColor) cbSameColor=false;
		if (cbFirstValue!=(GetCardLogicValue(cbCardData[i])+i)) bLineCard=false;

		//�����ж�
		if ((cbSameColor==false)&&(bLineCard==false)) break;
	}

	//��Сͬ��˳
	if((bLineCard == false)&&(cbFirstValue == 14))
	{
		unsigned char i=1;
		for (i=1;i<cbCardCount;i++)
		{
			unsigned char cbLogicValue=GetCardLogicValue(cbCardData[i]);
			if ((cbFirstValue!=(cbLogicValue+i+8))) break;
		}
		if( i == cbCardCount)
			bLineCard =true;
	}

	//�ʼ�ͬ��˳
	if ((cbSameColor==true)&&(bLineCard==true)&&(GetCardLogicValue(cbCardData[1]) ==13 )) 
		return CT_KING_TONG_HUA_SHUN;

	//˳������
	if ((cbSameColor==false)&&(bLineCard==true)) 
		return CT_SHUN_ZI;

	//ͬ������
	if ((cbSameColor==true)&&(bLineCard==false)) 
		return CT_TONG_HUA;

	//ͬ��˳����
	if ((cbSameColor==true)&&(bLineCard==true))
		return CT_TONG_HUA_SHUN;

	//�˿˷���
	tagAnalyseResult AnalyseResult;
	AnalysebCardData(cbCardData,cbCardCount,AnalyseResult);

	//�����ж�
	if (AnalyseResult.cbFourCount==1) 
		return CT_TIE_ZHI;
	if (AnalyseResult.cbLONGCount==2) 
		return CT_TWO_LONG;
	if ((AnalyseResult.cbLONGCount==1)&&(AnalyseResult.cbThreeCount==1))
		return CT_HU_LU;
	if ((AnalyseResult.cbThreeCount==1)&&(AnalyseResult.cbLONGCount==0))
		return CT_THREE_TIAO;
	if ((AnalyseResult.cbLONGCount==1)&&(AnalyseResult.cbSignedCount==3)) 
		return CT_ONE_LONG;

	return CT_SINGLE;
}

//�������
unsigned char CGameLogic::FiveFromSeven(const unsigned char cbHandCardData[],unsigned char cbHandCardCount,const unsigned char cbCenterCardData[],unsigned char cbCenterCardCount,unsigned char cbLastCardData[],unsigned char cbLastCardCount)
{
	//��ʱ����
	unsigned char cbTempCardData[MAX_COUNT+MAX_CENTERCOUNT],cbTempLastCardData[5];
	memset(cbTempCardData, 0, sizeof(cbTempCardData));
	memset(cbTempLastCardData, 0, sizeof(cbTempLastCardData));

	//��������
	memcpy(cbTempCardData,cbHandCardData,sizeof(unsigned char)*MAX_COUNT);
	memcpy(&cbTempCardData[2],cbCenterCardData,sizeof(unsigned char)*MAX_CENTERCOUNT);

	//�����˿�
	SortCardList(cbTempCardData,CountArray(cbTempCardData));

	memcpy(cbLastCardData,cbTempCardData,sizeof(unsigned char)*MAX_CENTERCOUNT);
	unsigned char cbCardKind = GetCardType(cbLastCardData,sizeof(unsigned char)*MAX_CENTERCOUNT);
	unsigned char cbTempCardKind = 0;

	//����㷨
	for (int i=0;i<3;i++)
	{
		for (int j= i+1;j<4;j++)
		{
			for (int k = j+1;k<5;k++)
			{
				for (int l =k+1;l<6;l++)
				{
					for (int m=l+1;m<7;m++)
					{
						//��ȡ����
						cbTempLastCardData[0]=cbTempCardData[i];
						cbTempLastCardData[1]=cbTempCardData[j];
						cbTempLastCardData[2]=cbTempCardData[k];
						cbTempLastCardData[3]=cbTempCardData[l];
						cbTempLastCardData[4]=cbTempCardData[m];

						//��ȡ����
						cbTempCardKind = GetCardType(cbTempLastCardData,CountArray(cbTempLastCardData));

						//���ʹ�С
						if(CompareCard(cbTempLastCardData,cbLastCardData,CountArray(cbTempLastCardData))==2)
						{
							cbCardKind = cbTempCardKind;
							memcpy(cbLastCardData,cbTempLastCardData,sizeof(unsigned char)*CountArray(cbTempLastCardData));
						}
					}
				}
			}
		}
	}

	return cbCardKind;
}

//6��5
unsigned char CGameLogic::FiveFromSix(const unsigned char cbHandCardData[],unsigned char cbHandCardCount,const unsigned char cbCenterCardData[],unsigned char cbCenterCardCount,unsigned char cbLastCardData[],unsigned char cbLastCardCount)
{
	//��ʱ����
	unsigned char cbTempCardData[MAX_COUNT+MAX_CENTERCOUNT-1]/*,cbTempLastCardData[5]*/;
	memset(cbTempCardData, 0, sizeof(cbTempCardData));
//	ZeroMemory(cbTempLastCardData,sizeof(cbTempLastCardData));

	//��������
	memcpy(cbTempCardData,cbHandCardData,sizeof(unsigned char)*MAX_COUNT);
	memcpy(&cbTempCardData[2],cbCenterCardData,sizeof(unsigned char)*(MAX_CENTERCOUNT-1));

	//�����˿�
	SortCardList(cbTempCardData,CountArray(cbTempCardData));

	memcpy(cbLastCardData,cbTempCardData,sizeof(unsigned char)*MAX_CENTERCOUNT);
	unsigned char cbCardKind = GetCardType(cbLastCardData,sizeof(unsigned char)*MAX_CENTERCOUNT);
	for (unsigned i = 0; i < MAX_CENTERCOUNT+1; ++i)
	{
		int nNum = 0;
		unsigned char cbCardTemp[MAX_CENTERCOUNT];
		for (unsigned j = 0; j < MAX_CENTERCOUNT+1; ++j)
		{
			if (i == j)
			{
				continue;
			}
			cbCardTemp[nNum++] = cbTempCardData[j];
		}

		unsigned char cbTempCardKind = GetCardType(cbCardTemp, CountArray(cbCardTemp));

		//���ʹ�С
		if(CompareCard(cbCardTemp, cbLastCardData, CountArray(cbCardTemp))==2)
		{
			cbCardKind = cbTempCardKind;
			memcpy(cbLastCardData,cbCardTemp,sizeof(unsigned char)*CountArray(cbCardTemp));
		}
	}
	return cbCardKind;
}


//�������
/*
bool CGameLogic::SelectMaxUser(unsigned char bCardData[GAME_PLAYER][MAX_CENTERCOUNT],UserWinList &EndResult,const __int64 lAddScore[])
{
	//��������
	memset(&EndResult,0, sizeof(EndResult));

	//First����
	unsigned short wWinnerID;
	unsigned char k=0;
	for (;k<GAME_PLAYER;k++)
	{
		if(bCardData[k][0]!=0)
		{
			wWinnerID=k;
			break;
		}
	}

	//����ȫ��
	if(k==GAME_PLAYER)return false;

	//��������û�
	unsigned short wTemp = wWinnerID;
	for(unsigned short i=1;i<GAME_PLAYER;i++)
	{
		unsigned short j=(i+wTemp)%GAME_PLAYER;
		if(bCardData[j][0]==0)continue;
		if(CompareCard(bCardData[j],bCardData[wWinnerID],MAX_CENTERCOUNT)>1)
		{
			wWinnerID=j;
		}
	}

	//������ͬ����
	EndResult.wWinerList[EndResult.bSameCount++] = wWinnerID;
	for(unsigned short i=0;i<GAME_PLAYER;i++)
	{
		if(i==wWinnerID || bCardData[i][0]==0)continue;
		if(CompareCard(bCardData[i],bCardData[wWinnerID],MAX_CENTERCOUNT)==0)
		{
			EndResult.wWinerList[EndResult.bSameCount++] = i;
		}
	}

	//��С����
	if(EndResult.bSameCount>1 && lAddScore!=NULL)
	{
		int iSameCount=(int)EndResult.bSameCount;
		while((iSameCount--)>0)
		{
			__int64 lTempSocre = lAddScore[EndResult.wWinerList[iSameCount]];
			for(int i=iSameCount-1;i>=0;i--)
			{
				if(lTempSocre < lAddScore[EndResult.wWinerList[i]])
				{
					lTempSocre = lAddScore[EndResult.wWinerList[i]];
					unsigned short wTemp = EndResult.wWinerList[iSameCount];
					EndResult.wWinerList[iSameCount] = EndResult.wWinerList[i];
					EndResult.wWinerList[i] = wTemp;
				}
			}
		}
	}

	return true;
}
*/
CGameLogic::CardValueScope CGameLogic::GetCardValueScope(unsigned char cbCardValue)
{
	if (cbCardValue >= 2 && cbCardValue < 5)
	{
		return CardValue2To5;
	}
	else if (cbCardValue >= 5 && cbCardValue < 10)
	{
		return CardValue5To10;
	}
	else
	{
		return CardValue10ToA;
	}
}

CGameLogic::TwoCardResult CGameLogic::AnalyseTwoCard(const unsigned char cbCard[2])
{
	unsigned char cbClr1 = GetCardColor(cbCard[0]);
	unsigned char cbClr2 = GetCardColor(cbCard[1]);

	unsigned char cbValue1 = GetCardValue(cbCard[0]);
	unsigned char cbValue2 = GetCardValue(cbCard[1]);

	TwoCardResult tr;
	tr.cbCardType = 0;
	if (cbClr1 == cbClr2)
	{
		tr.cbCardType |= TongHua;
	}
	if (cbValue1 == cbValue2)
	{
		tr.cbCardType |= DuiZi;
	}

	unsigned char cbBigV = std::max(cbValue1, cbValue2);
	unsigned char cbSmallV = std::min(cbValue1, cbValue2);
	tr.bigCardValueScope = GetCardValueScope(cbBigV);
	tr.smallCardValueScope = GetCardValueScope(cbSmallV);
	return tr;
}

//�����˿�
void CGameLogic::SortCardList(unsigned char cbCardData[], unsigned char cbCardCount)
{
	//ת����ֵ
	unsigned char cbLogicValue[FULL_COUNT];
	for (unsigned char i=0;i<cbCardCount;i++) 
		cbLogicValue[i]=GetCardLogicValue(cbCardData[i]);	

	//�������
	bool bSorted=true;
	unsigned char cbTempData,bLast=cbCardCount-1;
	do
	{
		bSorted=true;
		for (unsigned char i=0;i<bLast;i++)
		{
			if ((cbLogicValue[i]<cbLogicValue[i+1])||
				((cbLogicValue[i]==cbLogicValue[i+1])&&(cbCardData[i]<cbCardData[i+1])))
			{
				//����λ��
				cbTempData=cbCardData[i];
				cbCardData[i]=cbCardData[i+1];
				cbCardData[i+1]=cbTempData;
				cbTempData=cbLogicValue[i];
				cbLogicValue[i]=cbLogicValue[i+1];
				cbLogicValue[i+1]=cbTempData;
				bSorted=false;
			}	
		}
		bLast--;
	} while(bSorted==false);

	return;
}

//�߼���ֵ
unsigned char CGameLogic::GetCardLogicValue(unsigned char cbCardData)
{
	//�˿�����
	unsigned char bCardColor=GetCardColor(cbCardData);
	unsigned char bCardValue=GetCardValue(cbCardData);

	//ת����ֵ
	return (bCardValue==1)?(bCardValue+13):bCardValue;
}

//�Ա��˿�
unsigned char CGameLogic::CompareCard(unsigned char cbFirstData[], unsigned char cbNextData[], unsigned char cbCardCount)
{
	//��ȡ����
	unsigned char cbNextType=GetCardType(cbNextData,cbCardCount);
	unsigned char cbFirstType=GetCardType(cbFirstData,cbCardCount);

	//�����ж�
	//��
	if(cbFirstType>cbNextType)
		return 2;

	//С
	if(cbFirstType<cbNextType)
		return 1;

	//������
	switch(cbFirstType)
	{
	case CT_SINGLE:			//����
		{
			//�Ա���ֵ
			unsigned char i=0;
			for (i=0;i<cbCardCount;i++)
			{
				unsigned char cbNextValue=GetCardLogicValue(cbNextData[i]);
				unsigned char cbFirstValue=GetCardLogicValue(cbFirstData[i]);

				//��
				if(cbFirstValue > cbNextValue)
					return 2;
				//С
				else if(cbFirstValue <cbNextValue)
					return 1;
				//��
				else
					continue;
			}
			//ƽ
			if( i == cbCardCount)
				return 0;
		}
	case CT_ONE_LONG:		//����
	case CT_TWO_LONG:		//����
	case CT_THREE_TIAO:		//����
	case CT_TIE_ZHI:		//��֧
	case CT_HU_LU:			//��«
		{
			//�����˿�
			tagAnalyseResult AnalyseResultNext;
			tagAnalyseResult AnalyseResultFirst;
			AnalysebCardData(cbNextData,cbCardCount,AnalyseResultNext);
			AnalysebCardData(cbFirstData,cbCardCount,AnalyseResultFirst);

			//������ֵ
			if (AnalyseResultFirst.cbFourCount>0)
			{
				unsigned char cbNextValue=AnalyseResultNext.cbFourLogicVolue[0];
				unsigned char cbFirstValue=AnalyseResultFirst.cbFourLogicVolue[0];

				//�Ƚ�����
				if(cbFirstValue != cbNextValue)return (cbFirstValue > cbNextValue)?2:1;

				//�Ƚϵ���
				cbFirstValue = AnalyseResultFirst.cbSignedLogicVolue[0];
				cbNextValue = AnalyseResultNext.cbSignedLogicVolue[0];
				if(cbFirstValue != cbNextValue)return (cbFirstValue > cbNextValue)?2:1;
				else return 0;
			}

			//������ֵ
			if (AnalyseResultFirst.cbThreeCount>0)
			{
				unsigned char cbNextValue=AnalyseResultNext.cbThreeLogicVolue[0];
				unsigned char cbFirstValue=AnalyseResultFirst.cbThreeLogicVolue[0];

				//�Ƚ�����
				if(cbFirstValue != cbNextValue)return (cbFirstValue > cbNextValue)?2:1;

				//��«����
				if(CT_HU_LU == cbFirstType)
				{
					//�Ƚ϶���
					cbFirstValue = AnalyseResultFirst.cbLONGLogicVolue[0];
					cbNextValue = AnalyseResultNext.cbLONGLogicVolue[0];
					if(cbFirstValue != cbNextValue)return (cbFirstValue > cbNextValue)?2:1;
					else return 0;
				}
				else //��������
				{
					//�Ƚϵ���

					//ɢ����ֵ
					unsigned char i=0;
					for (i=0;i<AnalyseResultFirst.cbSignedCount;i++)
					{
						unsigned char cbNextValue=AnalyseResultNext.cbSignedLogicVolue[i];
						unsigned char cbFirstValue=AnalyseResultFirst.cbSignedLogicVolue[i];
						//��
						if(cbFirstValue > cbNextValue)
							return 2;
						//С
						else if(cbFirstValue <cbNextValue)
							return 1;
						//��
						else continue;
					}
					if( i == AnalyseResultFirst.cbSignedCount)
						return 0;
				}
			}

			//������ֵ
			unsigned char i=0;
			for ( i=0;i<AnalyseResultFirst.cbLONGCount;i++)
			{
				unsigned char cbNextValue=AnalyseResultNext.cbLONGLogicVolue[i];
				unsigned char cbFirstValue=AnalyseResultFirst.cbLONGLogicVolue[i];
				//��
				if(cbFirstValue > cbNextValue)
					return 2;
				//С
				else if(cbFirstValue <cbNextValue)
					return 1;
				//ƽ
				else
					continue;
			}

			//�Ƚϵ���
			{
				//ɢ����ֵ
				for (i=0;i<AnalyseResultFirst.cbSignedCount;i++)
				{
					unsigned char cbNextValue=AnalyseResultNext.cbSignedLogicVolue[i];
					unsigned char cbFirstValue=AnalyseResultFirst.cbSignedLogicVolue[i];
					//��
					if(cbFirstValue > cbNextValue)
						return 2;
					//С
					else if(cbFirstValue <cbNextValue)
						return 1;
					//��
					else continue;
				}
				//ƽ
				if( i == AnalyseResultFirst.cbSignedCount)
					return 0;
			}
			break;
		}
	case CT_SHUN_ZI:		//˳��
	case CT_TONG_HUA_SHUN:	//ͬ��˳
		{
			//��ֵ�ж�
			unsigned char cbNextValue=GetCardLogicValue(cbNextData[0]);
			unsigned char cbFirstValue=GetCardLogicValue(cbFirstData[0]);

			bool bFirstmin= (cbFirstValue ==(GetCardLogicValue(cbFirstData[1])+9));
			bool bNextmin= (cbNextValue ==(GetCardLogicValue(cbNextData[1])+9));

			//��С˳��
			if ((bFirstmin==true)&&(bNextmin == false))
			{
				return 1;
			}
			//��С˳��
			else if ((bFirstmin==false)&&(bNextmin == true))
			{
				return 2;
			}
			//��ͬ˳��
			else
			{
				//ƽ
				if(cbFirstValue == cbNextValue)return 0;		
				return (cbFirstValue > cbNextValue)?2:1;		
			}
		}
	case CT_TONG_HUA:		//ͬ��
		{	
			//ɢ����ֵ
			unsigned char i=0;
			for (;i<cbCardCount;i++)
			{
				unsigned char cbNextValue=GetCardLogicValue(cbNextData[i]);
				unsigned char cbFirstValue=GetCardLogicValue(cbFirstData[i]);

				if(cbFirstValue == cbNextValue)continue;
				return (cbFirstValue > cbNextValue)?2:1;
			}
			//ƽ
			if( i == cbCardCount) return 0;
		}
	}

	return  0;
}

//�����˿�
void CGameLogic::AnalysebCardData(const unsigned char cbCardData[], unsigned char cbCardCount, tagAnalyseResult & AnalyseResult)
{
	//���ý��
	memset(&AnalyseResult,0,sizeof(AnalyseResult));

	//�˿˷���
	for (unsigned char i=0;i<cbCardCount;i++)
	{
		//��������
		unsigned char cbSameCount=1;
		unsigned char cbSameCardData[4]={cbCardData[i],0,0,0};
		unsigned char cbLogicValue=GetCardLogicValue(cbCardData[i]);

		//��ȡͬ��
		for (int j=i+1;j<cbCardCount;j++)
		{
			//�߼��Ա�
			if (GetCardLogicValue(cbCardData[j])!=cbLogicValue) break;

			//�����˿�
			cbSameCardData[cbSameCount++]=cbCardData[j];
		}

		//������
		switch (cbSameCount)
		{
		case 1:		//����
			{
				AnalyseResult.cbSignedLogicVolue[AnalyseResult.cbSignedCount]=cbLogicValue;
				memcpy(&AnalyseResult.cbSignedCardData[(AnalyseResult.cbSignedCount++)*cbSameCount],cbSameCardData,cbSameCount);
				break;
			}
		case 2:		//����
			{
				AnalyseResult.cbLONGLogicVolue[AnalyseResult.cbLONGCount]=cbLogicValue;
				memcpy(&AnalyseResult.cbLONGCardData[(AnalyseResult.cbLONGCount++)*cbSameCount],cbSameCardData,cbSameCount);
				break;
			}
		case 3:		//����
			{
				AnalyseResult.cbThreeLogicVolue[AnalyseResult.cbThreeCount]=cbLogicValue;
				memcpy(&AnalyseResult.cbThreeCardData[(AnalyseResult.cbThreeCount++)*cbSameCount],cbSameCardData,cbSameCount);
				break;
			}
		case 4:		//����
			{
				AnalyseResult.cbFourLogicVolue[AnalyseResult.cbFourCount]=cbLogicValue;
				memcpy(&AnalyseResult.cbFourCardData[(AnalyseResult.cbFourCount++)*cbSameCount],cbSameCardData,cbSameCount);
				break;
			}
		}

		//���õ���
		i+=cbSameCount-1;
	}

	return;
}
//////////////////////////////////////////////////////////////////////////
