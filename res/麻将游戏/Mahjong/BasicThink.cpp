// BasicThink.cpp: implementation of the CBasicThink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mahjong.h"
#include "BasicThink.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBasicThink::CBasicThink():m_bHaveDui(false)
{

}

CBasicThink::~CBasicThink()
{

}
/*************************************************************/
/*�������ܣ������齫��
/*��ڲ�����ָ�루�齫���飩�����ͣ�������
/*�������ͣ�void
/*************************************************************/
void CBasicThink::SetMjPaiArray(int *nPailist, int nNum)
{
	for( int i = 0;i < 14;i++ )
	{
		m_bMjSelect[i] = false;
	}
	m_nCheckNum = 0;
	m_nMaxScoreThree = m_nMaxScoreTwo = m_nMaxScoreOne = 0;
	m_nMjNum = nNum;
	m_nScoreThree = m_nScoreTwo = 0;
	m_nBadly = -1;
	
	for(int j = 0;j < nNum;j++)
	{
		m_nMajiang[j] = nPailist[j];
	}

	m_nNeedPai = nPailist[nNum-1];				//������Ҫ����Ϊ���һ��
	SortMj(m_nMajiang,nNum);					//������
}

/*************************************************************/
/*�������ܣ�������
/*��ڲ�����ָ�루�Ƶ����飩�����ͣ�����λ�ã�
/*�������ͣ�void
/*************************************************************/
void CBasicThink::SortMj(int *who,int end)
{
	int i,j,nPai;
	for( i = 0 ; i < end-1 ; i++ )
	{
		for( j = i+1 ; j < end ; j++ )
            if( who[i] > who[j] )
			{
				nPai =  who[i];
				who[i] = who[j];
				who[j] = nPai;
			}
	}
}

/*************************************************************/
/*�������ܣ���ÿ��Ǻ��������
/*��ڲ�������
/*�������ͣ�����
/*************************************************************/
int CBasicThink::GetMaxScore()
{
	return m_nMaxScoreThree + m_nMaxScoreTwo;
}

/*************************************************************/
/*�������ܣ��������������
/*��ڲ�������
/*�������ͣ�����
/*************************************************************/
int CBasicThink::GetBadly()
{
	return m_nBadly;
}

/*************************************************************/
/*�������ܣ���ñ��˳��ƺ���ϵ�������
/*��ڲ��������ͣ����ͣ�����
/*�������ͣ�void
/*************************************************************/
void CBasicThink::GetGoodTeam(int &pai1, int &pai2, int &pai3)
{
	pai1=m_nTotalTeam[0];
	pai2=m_nTotalTeam[1];
	pai3=m_nTotalTeam[2];
}

/*************************************************************/
/*�������ܣ�������
/*��ڲ��������ͣ�Ҫ�ҵ��ǳ��ƣ������ͣ���ʼλ�ã�
/*�������ͣ����ͣ�λ�ã�
/*************************************************************/
int CBasicThink::FindPos(int pai,int nStart)
{
	for( int i = nStart;i < m_nMjNum;i++ )
	{
		if( m_nMajiang[i] == pai && m_bMjSelect[i] == false )
		{
			return i;
		}
	}
	return -1;
}

/*************************************************************/
/*�������ܣ��Ӽ�������ź�ʣ������в�����
/*��ڲ��������ͣ�Ҫ�ҵ��ǳ��ƣ������ͣ���ʼλ�ã�
/*�������ͣ����ͣ�λ�ã�
/*************************************************************/
int CBasicThink::FindPosThree(int pai,int nStart)
{
	for( int i = nStart;i < m_nRemainNumThree;i++ )
	{
		if( m_nRemainThree[i] == pai && m_bMjSelect[i] == false )
		{
			return i;
		}
	}
	return -1;
}

/*************************************************************/
/*�������ܣ��Ƿ���3��һ����
/*��ڲ��������ͣ����ͣ����ͣ�
/*�������ͣ��������������
/*************************************************************/
bool CBasicThink::IsSameTeam(int pai,int &pos1,int &pos2)
{
	pos1 = FindPos(pai);
	if( pos1 == -1 )
	{
		return false;
	}
	pos2 = FindPos(pai,pos1+1);
	if( pos2 == -1 )
	{
		return false;
	}
    return true;
}

/*************************************************************/
/*�������ܣ��Ƿ���3��˳�ӵ�
/*��ڲ��������ͣ����ͣ����ͣ�
/*�������ͣ��������������
/*************************************************************/
bool CBasicThink::IsStepTeam(int pai,int &pos1,int &pos2)
{
    if( pai >= 27 ) 
	{
		return false;
	}
	int nPai1 = pai+1;
	int nPai2 = pai+2;
	//�ж��Ƿ������Ƿ���һ�������
	if( nPai1/9 != nPai2/9 || nPai1/9 != pai/9 || nPai1 >= 27 || nPai2 >= 27 )
	{
		return false;
	}
	pos1 = FindPos(nPai1);
	pos2 = FindPos(nPai2);
	if( pos1 != -1 && pos2 != -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*************************************************************/
/*�������ܣ������������Ƿ��Ǳ�Ե�ģ�0��8��
/*��ڲ��������ͣ�����
/*�������ͣ��������������
/*************************************************************/
bool CBasicThink::IsEdge(int pai1,int pai2)
{
	if( pai1%9 == 0 || pai2%9 == 8 )
	{
		return true;
	}
	return false;
}

/*************************************************************/
/*�������ܣ������ż�������Ƿ��ж���
/*��ڲ��������ͣ����ͣ����ͣ�
/*�������ͣ��������������
/*************************************************************/
bool CBasicThink::IsSameTeamThree(int pai,int &pos1,int nStart)
{
	pos1 = FindPosThree(pai,nStart);
	return pos1 == -1 ? false:true;
}

/*************************************************************/
/*�������ܣ���������������Ƿ������������
/*��ڲ��������ͣ����ͣ����ͣ�����
/*�������ͣ��������������
/*************************************************************/
bool CBasicThink::IsStepTeamThree(int pai,int type,int &pos1,int nStart)
{
    if( pai >= 27 ) 
	{
		return false;
	}
	int nPai1;
	if(type == 1)
	{
		nPai1 = pai+1;
	}
	else 
	{
		nPai1 = pai+2;
	}
	//�ж������Ƿ�ͬɫ�Ƿ�����
	if(  nPai1/9 != pai/9 || nPai1 >= 27  )
	{
		return false;
	}
	pos1 = FindPosThree(nPai1,nStart);
	return pos1 == -1 ? false:true;
	
}

/*************************************************************/
/*�������ܣ�����3�ŵ����
/*��ڲ��������ͣ����ࣩ
/*�������ͣ�void
/*************************************************************/
void CBasicThink::SetTeamPai( int type)
{
	switch(type)
	{
	case 0:		//3��һ����
		m_nGoodTeamThree[0] = m_nGoodTeamThree[1] = m_nGoodTeamThree[2] = m_nNeedPai;
		break;
	case 1:
		m_nGoodTeamThree[0] = m_nNeedPai;
		m_nGoodTeamThree[1] = m_nNeedPai+1;
		m_nGoodTeamThree[2] = m_nNeedPai+2;
		break;
	case 2:
		m_nGoodTeamThree[0] = m_nNeedPai-1;
		m_nGoodTeamThree[1] = m_nNeedPai;
		m_nGoodTeamThree[2] = m_nNeedPai+1;
		break;
	case 3:
		m_nGoodTeamThree[0] = m_nNeedPai-2;
		m_nGoodTeamThree[1] = m_nNeedPai-1;
		m_nGoodTeamThree[2] = m_nNeedPai;
		break;
	}
}
