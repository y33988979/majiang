// CmpThink.cpp: implementation of the CCmpThink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mahjong.h"
#include "CmpThink.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCmpThink::CCmpThink()
{
	
}

/*************************************************************/
/*�������ܣ����������Ƽ������
/*��ڲ���������
/*�������ͣ�����
/*************************************************************/
int CCmpThink::AddGood(int pai)
{
	int nGood = 0;
	if( pai >= 27 )
	{
		return 0;
	}
	if( pai%9 != 0 && FindPos(pai-1) != -1 )	//���ʣ��������б�����һ����
	{
		if( pai%9 != 1 )						//�����ǰ�Ʋ��Ƕ��༴��3
		{
			nGood += 3;
		}
		else
		{
			nGood += 1;
		}
	}
	if( pai%9 != 8 && FindPos(pai+1) != -1 )	//���ʣ��������б����һ������
	{
		if( pai%9 != 7 )
		{
			nGood += 3;
		}
		else
		{
			nGood += 1;
		}
	}
	if( pai%9 > 1 && FindPos(pai-2) != -1 )		//���ʣ��������б����ٶ����ƣ���3��5,1_3�ȣ�
	{
		nGood += 2;
	}
	
	if( pai%9 < 7 && FindPos(pai+2) != -1 )		//���ʣ��������б���������
	{
		nGood += 2;
	}
	return nGood;
}

/*************************************************************/
/*�������ܣ����Կ���
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CCmpThink::Think()
{
	ThinkThree();											//����������ϵ����
	int i;

	if( m_nMaxScoreThree == 0 || m_nRemainNumThree == 0 )	//���û��һ�����
	{
		m_nRemainNumThree = m_nMjNum;
		for( i = 0;i < m_nRemainNumThree;i++ )
		{
			m_nRemainThree[i] = m_nMajiang[i];
		}
	}

	ThinkTwo();												//�������ŵ����
	if( m_nMaxScoreTwo == 0  )
	{
		m_nRemainNumTwo = m_nRemainNumThree;
		for( i = 0;i < m_nRemainNumTwo;i++ )
		{
			m_nRemainTwo[i] = m_nRemainThree[i];
		}
	}

	if(  m_nRemainNumTwo == 0  )							//����������ж������
	{
		CheckOnlyTwo();
		return;
	}

	ThinkOne();
}

/*************************************************************/
/*�������ܣ�����3��
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CCmpThink::ThinkThree()
{
	int pos1,pos2;
	for( int i = 0;i < m_nMjNum;i++ )
	{
		if( m_bMjSelect[i] == false )
		{
			m_bMjSelect[i] = true;
            if( IsSameTeam(m_nMajiang[i],pos1,pos2 ) )
			{
				m_nPaiTeamThree[m_nCheckNum*3] = m_nMajiang[i];
				m_nPaiTeamThree[m_nCheckNum*3+1] = m_nMajiang[i];
				m_nPaiTeamThree[m_nCheckNum*3+2] = m_nMajiang[i];

				if( m_nMajiang[i] == m_nNeedPai )					//���ô�������ܷ����
				{
					SetTeamPai(0);
				}
				
				m_nScoreThree += 300;
				m_nCheckNum++;
				m_bMjSelect[pos1] = true;
				m_bMjSelect[pos2] = true;
				ThinkThree();
				m_bMjSelect[pos1] = true;
				m_bMjSelect[pos2] = true;
				m_nScoreThree -= 300;
				m_nCheckNum--;
			}
			if( IsStepTeam(m_nMajiang[i],pos1,pos2 ) )
			{
				if( m_nMajiang[i] == m_nNeedPai )
				{
					SetTeamPai(1);
				}
				else if( m_nMajiang[pos1] == m_nNeedPai )
				{
					SetTeamPai(2);
				}
				else if( m_nMajiang[pos2] == m_nNeedPai )
				{
					SetTeamPai(3);
				}
				
				m_nPaiTeamThree[m_nCheckNum*3] = m_nMajiang[i];
				m_nPaiTeamThree[m_nCheckNum*3+1] = m_nMajiang[i]+1;
				m_nPaiTeamThree[m_nCheckNum*3+2] = m_nMajiang[i]+2;
				
				m_nScoreThree += 300;
				m_nCheckNum++;
				m_bMjSelect[pos1] = true;
				m_bMjSelect[pos2] = true;
				ThinkThree();
				m_bMjSelect[pos1] = false;
				m_bMjSelect[pos2] = false;
				m_nScoreThree -= 300;
				m_nCheckNum--;
			}
			m_bMjSelect[i] = false;
		}
	}
		
	if( m_nScoreThree > m_nMaxScoreThree )
	{
		m_nRemainNumThree = 0;
		m_nMaxScoreThree = m_nScoreThree;
		for(i = 0;i < 3;i++)
		{
			m_nTotalTeam[i] = m_nGoodTeamThree[i];
		}
		int good = 0;
		for( i = 0;i < m_nMjNum;i++ )
		{
			if( m_bMjSelect[i] == false )
			{
				m_nRemainThree[m_nRemainNumThree] = m_nMajiang[i];
				m_nRemainNumThree++;
			}
		}
	}	
}

/*************************************************************/
/*�������ܣ�����3�ź���������
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CCmpThink::ThinkTwo()
{
	int pos1;
	for( int i = 0;i < m_nRemainNumThree;i++ )
		if( m_bMjSelect[i] == false )
		{
			m_bMjSelect[i] = true;
			if( IsSameTeamThree(m_nRemainThree[i],pos1,i ) )				//�Ƿ��ж���
			{
				int nGoodSame = 90;
				if( m_bHaveDui == false )									//���û�������ý�
				{
					nGoodSame = 120;
					m_bHaveDui = true;
				}
				m_nScoreTwo += nGoodSame;
				m_bMjSelect[pos1] = true;
				ThinkTwo();
				m_bMjSelect[pos1] = false;
				if( nGoodSame == 120 )
				{
					m_bHaveDui = false;
				}
				m_nScoreTwo -= nGoodSame;
			}

			if( IsStepTeamThree(m_nRemainThree[i],1,pos1,i ) )				//�Ƿ�������
			{
				int nGoodstep;
				if( IsEdge( m_nRemainThree[i],m_nRemainThree[i]+1 ) )
				{
					nGoodstep = 80;
				}
				else 
				{
					nGoodstep = 100;
				}
				m_nScoreTwo += nGoodstep;
				m_bMjSelect[pos1] = true;
				ThinkTwo();
				m_bMjSelect[pos1] = false;
				m_nScoreTwo -= nGoodstep;
			}
			if( IsStepTeamThree(m_nRemainThree[i],2,pos1,i ) )
			{
				int nGoodstep;

				if( IsEdge( m_nRemainThree[i],m_nRemainThree[i]+2 ) )		//����Ǳ�Ե���Ӿͼ�70
				{
					nGoodstep = 70;
				}
				else 
				{
					nGoodstep = 90;
				}
				m_nScoreTwo += nGoodstep;
				m_bMjSelect[pos1] = true;
				ThinkTwo();
				m_bMjSelect[pos1] = false;
				m_nScoreTwo -= nGoodstep;
			}
			m_bMjSelect[i] = false;
		}
		if( m_nScoreTwo > m_nMaxScoreTwo)
		{
			m_nRemainNumTwo = 0;
			m_nMaxScoreTwo = m_nScoreTwo;
			for(i = 0;i < m_nRemainNumThree;i++ )
			{
				if( m_bMjSelect[i] == false )
				{
					m_nRemainTwo[m_nRemainNumTwo++] = m_nRemainThree[i];
				}
			}
		}
}

/*************************************************************/
/*�������ܣ�����һ�ŵ����
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CCmpThink::ThinkOne()
{
	int pai;
	int nGood[14];
	int nMin = 33;
	for(int i = 0;i < m_nRemainNumTwo;i++ )	//�ҳ�����һ����
	{
		pai = m_nRemainTwo[i];

		if( pai >= 27 )						//�������
		{
			nGood[i] = 2;
		}
		else if( pai%9 == 0 || pai%9 == 8 )	//�����һ���߾�
		{
			nGood[i] = 6;
		}
		else 
		{
			nGood[i] = 10;
		}

		nGood[i] += AddGood(pai);
		if( nGood[i] < nMin )
		{
			nMin = nGood[i];
			m_nBadly = pai;
		}
	}
}

/*************************************************************/
/*�������ܣ����ֻʣ���ŵ����
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CCmpThink::CheckOnlyTwo()
{
	int two[14],num = 0;
	bool bSameHave = false;
	int max = 100;
	int score[8];
	bool bTeamHave = false;
	for( int i = 0;i < m_nRemainNumThree;i++ )
		two[num++] = m_nRemainThree[i];

	if( num == 2 )												//���ֻ��������
	{
		if(two[0] == two[1])									//�����ʣ����������ͬ�ͺ���
		{
			m_nBadly = 1000;
			return;
		}
		for( int j = 0;j < m_nMjNum-1;j++ )						//��������Ʋ�ͬ�ʹ�һ�Խ�
		{
			if( m_nMajiang[j] == m_nMajiang[j+1] 
				&& m_nMajiang[j] == m_nMajiang[j+2] )			//���Ƿ���������
			{
				bTeamHave = true;
				m_nBadly = m_nMajiang[j];
				break;
			}
		}
		if( bTeamHave == false )
		{
			m_nRemainNumTwo = 2;
			m_nRemainTwo[0] = two[0];
			m_nRemainTwo[1] = two[1];
			ThinkOne();
		}
	}
	else
	{
		for( int j = 0;j < num/2;j++ )					//ѭ����¼ÿ���Ƶķ���
		{
			if( two[j*2] == two[j*2 + 1] )
			{
				if( bSameHave )
				{
					score[j] = 6;
				}
				else 
				{
					score[j] = 8;
					bSameHave = true;
				}
			}
			else if( two[j*2] == two[j*2+1] - 1 )
			{
				if( two[j*2]%9 == 0 || two[j*2+1]%9 == 8 )
				{
					score[j] = 4;
				}
				else
				{
					score[j] = 7;
				}
			}
			else
			{
				if( two[j*2]%9 == 0 || two[j*2+1]%9 == 8 )
					score[j] = 3;
				else
					score[j] = 5;
			}
			
		}
		for( int k = 0;k < num/2;k++)						//�ҳ�������С��һ���ƾ�������һ��
		{
			if( score[k] < max )
			{
				max = score[k];
				if( two[k*2] % 9 == 0 )
				{
					m_nBadly = two[k*2];
				}
				else if( two[k*2+1] % 9 == 8 )
				{
					m_nBadly = two[k*2+1];
				}
				else 
				{
					m_nBadly = two[k*2 + rand()%2];
				}
			}
		}
	}
}