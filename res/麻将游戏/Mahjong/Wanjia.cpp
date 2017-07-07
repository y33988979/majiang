// Wanjia.cpp: implementation of the CWanjia class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mahjong.h"
#include "Wanjia.h"
#include "MajHu.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*************************************************************/
/*�������ܣ�����
/*��ڲ�������
/*�������ͣ���
/*************************************************************/
CWanjia::CWanjia()
{
	m_nFenShu = 500;
	m_nNewPai = -1;
	m_nOutNum = 0;
	m_nStartPai = 0;
	m_nState = -1;
	m_bBoy = true;
	int i;
	for(i = 0;i < 30;i++)
		m_nPaiOut[i]=-1;
	for(i = 0;i < 13;i++)
		m_nPaiInhand[i]=-1;
	for(i = 0;i < 4;i++)
		m_nGang[i] = 0;
}

/*************************************************************/
/*�������ܣ���ȡ�Ա�
/*��ڲ�������
/*�������ͣ�������������У��پ���Ů
/*************************************************************/
bool CWanjia::GetSex()
{
	return m_bBoy;
}

/*************************************************************/
/*�������ܣ��Ƿ���˳��
/*��ڲ�����˳�ӵ�����type
/*�������ͣ�����,�������˳�ӣ��پ���û��
/*************************************************************/
bool CWanjia::IsStepTeam(int type)
{
	int nPai1,nPai2;
	if(type == 1)
	{
		nPai1 = m_nOutPai-1;
		nPai2 = m_nOutPai+1;
	}
	else if(type == 0)
	{
		nPai1 = m_nOutPai+1;
		nPai2 = m_nOutPai+2;
	}
	else
	{
		nPai1 = m_nOutPai-1;
		nPai2 = m_nOutPai-2;
	}
	//�ж��Ƿ���ͬ����ʽ��������
	if( nPai1/9 != nPai2/9 || nPai1/9 != m_nOutPai/9 || nPai1 >= 27 || nPai2 >= 27  )
	{
		return false;
	}
	int pos1,pos2;
	pos1 = FindPaiPos(nPai1,m_nStartPai);
	pos2 = FindPaiPos(nPai2,m_nStartPai);
	//��1��2�����ھ�Ϊ��,���඼Ϊ��
    return (pos1 != -1 && pos2 != -1);
}

/*************************************************************/
/*�������ܣ������Ƿ��ܺ���
/*��ڲ�������
/*�������ͣ��������������
/*************************************************************/
bool CWanjia::ThinkHupai()
{
	int a[13],i;
	CMajHu mf;
	for(i = 0;i < 13-m_nStartPai;i++)
		a[i] = m_nPaiInhand[i + m_nStartPai];

	m_arrHupai.RemoveAll();
	mf.SetMjPaiArray(a,13 - m_nStartPai);
	mf.GetHupai(&m_arrHupai);

	for( i = 0;i < (int)m_arrHupai.GetSize();i++ )
	{
		//����״̬�ж��Ƿ����
		if(( m_nOutPai == (int)m_arrHupai.GetAt(i) && m_nState != 1)
			|| (m_nNewPai == (int)m_arrHupai.GetAt(i) && m_nState == 1))
			return true;
	}
	return false;
}

/*************************************************************/
/*�������ܣ�����Ƿ��иܺ���
/*��ڲ������Ƿ���������������m_bPeng������
/*�������ͣ��������������
/*************************************************************/
bool CWanjia::CheckGang(bool& m_bPeng)
{
	int pos1,pos2,pos3;
	bool bGang = false;
	pos1 = FindPaiPos(m_nOutPai,m_nStartPai);
	if(pos1 != -1)
	{
		pos2=FindPaiPos(m_nOutPai,pos1+1);
		if(pos2 != -1)
		{	
			m_bPeng = true;
			pos3 = FindPaiPos(m_nOutPai,pos2+1);
			if(pos3 != -1)
			{
				bGang = true;
			}
		}
	}
	return bGang;
}

/*************************************************************/
/*�������ܣ�����Ƿ��ܰ���
/*��ڲ������ܸܵ������
/*�������ͣ��������������
/*************************************************************/
bool CWanjia::CheckGangSelf(CUIntArray& m_arrGang)
{
	m_arrGang.RemoveAll();
	int i;
	for(i = 0;i < m_nStartPai/3;i++)
	{
		if(m_nPaiInhand[3*i] == m_nPaiInhand[3*i+1] 
			&& m_nPaiInhand[3*i] == m_nPaiInhand[3*i+2])
		{
			int pos=FindPaiPos(m_nPaiInhand[3*i],m_nStartPai);
			if(pos != -1)
			{
				m_arrGang.Add(m_nPaiInhand[3*i]);
			}
			else
			{
				if(m_nPaiInhand[3*i] == m_nNewPai)
				{
					m_arrGang.Add(m_nNewPai);
				}
			}
		}
	}

	SortPai(m_nStartPai);

	for(i = m_nStartPai;i < 10;i++)
	{
		if(m_nPaiInhand[i] == m_nPaiInhand[i+1] && m_nPaiInhand[i] == m_nPaiInhand[i+2])
		{
			if(m_nPaiInhand[i] == m_nPaiInhand[i+3] || m_nPaiInhand[i] == m_nNewPai)
			{
				m_arrGang.Add(m_nPaiInhand[i]);
			}
		}
	}
	if(m_arrGang.GetSize() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*************************************************************/
/*�������ܣ�����ܷ���Գ�
/*��ڲ������������
/*�������ͣ�����������ǿ���
/*************************************************************/
bool CWanjia::CheckEat(CUIntArray& m_arrEat)
{
	m_arrEat.RemoveAll();
	int pos1,pos2;

	if(IsStepTeam(0))
	{
		pos1 = FindPaiPos(m_nOutPai+1,m_nStartPai);
		pos2 = FindPaiPos(m_nOutPai+2,m_nStartPai);
		m_arrEat.Add(pos1);
		m_arrEat.Add(pos2);
	}
	if(IsStepTeam(1))
	{
		pos1 = FindPaiPos(m_nOutPai-1,m_nStartPai);
		pos2 = FindPaiPos(m_nOutPai+1,m_nStartPai);
		m_arrEat.Add(pos1);
		m_arrEat.Add(pos2);
	}
	if(IsStepTeam(2))
	{
		pos1 = FindPaiPos(m_nOutPai-2,m_nStartPai);
		pos2 = FindPaiPos(m_nOutPai-1,m_nStartPai);
		m_arrEat.Add(pos1);
		m_arrEat.Add(pos2);
	}
	if(m_arrEat.GetSize() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


CWanjia::~CWanjia()
{
	
}

/*************************************************************/
/*�������ܣ������ҵ�״̬
/*��ڲ�������
/*�������ͣ����α�����1���ǳ���״̬��0���ǵȴ�״̬��
/*************************************************************/
int CWanjia::GetState()
{
	return m_nState;
}

/*************************************************************/
/*�������ܣ��������е�����
/*��ڲ��������α������ƣ�
/*�������ͣ�void
/*************************************************************/
void CWanjia::SetNewPai(int Pai)
{
	m_nState = 1;
	if(Pai >= 0 && Pai < 34)
		m_nNewPai = Pai;
	else
		m_nNewPai = -1;
}

/*************************************************************/
/*�������ܣ����ñ��˳����ƣ��Ա㿼�ǣ�
/*��ڲ�����������
/*�������ͣ�void
/*************************************************************/
void CWanjia::SetOutPai(int Pai)
{
	if(Pai >=0 && Pai < 34)
		m_nOutPai = Pai;
	else
		m_nOutPai = -1;
}

/*************************************************************/
/*�������ܣ���ø���
/*��ڲ�������
/*�������ͣ����������ָ��
/*************************************************************/
int* CWanjia::GetGangPai()
{
	return m_nGang;
}

/*************************************************************/
/*�������ܣ��������
/*��ڲ�������
/*�������ͣ����Σ����ƣ�
/*************************************************************/
int CWanjia::GetNewPai()
{
	return m_nNewPai;
}

/*************************************************************/
/*�������ܣ���ó��˵��Ƶ����
/*��ڲ�����void
/*�������ͣ����˵�����ϵ�ָ��
/*************************************************************/
int* CWanjia::GetOutPai(void)
{
		return m_nPaiOut;
}

/*************************************************************/
/*�������ܣ���ó�����
/*��ڲ�������
/*�������ͣ����ͣ���������
/*************************************************************/
int CWanjia::GetOutNum()
{
	return m_nOutNum;
}

/*************************************************************/
/*�������ܣ���÷���
/*��ڲ�������
/*�������ͣ�����
/*************************************************************/
int CWanjia::GetFenshu()
{
	return m_nFenShu;
}

/*************************************************************/
/*�������ܣ����ó�
/*��ڲ��������ͣ��Ե����ࣩ
/*�������ͣ�void
/*************************************************************/
void CWanjia::SetChi(int type)
{
	if(m_nOutPai!=-1)
	{
		int pos1,pos2,i;
		switch(type)
		{
		case 2:
			{
				//β��
				pos1 = FindPaiPos(m_nOutPai-2,m_nStartPai);
				for( i = pos1;i > m_nStartPai;i--)
				{
					m_nPaiInhand[i] = m_nPaiInhand[i-1];
				}
				m_nPaiInhand[m_nStartPai] = m_nOutPai-2;

				pos2 = FindPaiPos(m_nOutPai-1,m_nStartPai);				
				for( i=pos2;i > m_nStartPai+1;i-- )
				{
					m_nPaiInhand[i] = m_nPaiInhand[i-1];
				}
				
				m_nPaiInhand[m_nStartPai+1] = m_nOutPai-1;
				m_nNewPai=m_nPaiInhand[12];
				for( i = 12;i > m_nStartPai+2;i-- )
				{
					m_nPaiInhand[i]=m_nPaiInhand[i-1];
				}
				m_nPaiInhand[m_nStartPai+2] = m_nOutPai;

				m_nStartPai += 3;
				m_nOutPai = -1;
			}
			break;
		case 1:
			{
				//�г�
				pos1 = FindPaiPos(m_nOutPai-1,m_nStartPai);
				for( i = pos1;i > m_nStartPai;i-- )
				{
					m_nPaiInhand[i] = m_nPaiInhand[i-1];
				}
				m_nPaiInhand[m_nStartPai] = m_nOutPai-1;
				
				pos2 = FindPaiPos(m_nOutPai+1,m_nStartPai);				
				for( i = pos2;i > m_nStartPai+1;i-- )
				{
					m_nPaiInhand[i] = m_nPaiInhand[i-1];
				}
				m_nPaiInhand[m_nStartPai+1] = m_nOutPai+1;

				m_nNewPai = m_nPaiInhand[12];
				for( i = 12;i > m_nStartPai+1;i-- )
				{
					m_nPaiInhand[i] = m_nPaiInhand[i-1];
				}
				m_nPaiInhand[m_nStartPai+1] = m_nOutPai;

				m_nStartPai += 3;
				m_nOutPai = -1;
			}
			break;
		case 0:
			{
				//ͷ��
				pos1 = FindPaiPos(m_nOutPai+1,m_nStartPai);				
				for( i = pos1;i > m_nStartPai;i-- )
				{
					m_nPaiInhand[i] = m_nPaiInhand[i-1];
				}
				m_nPaiInhand[m_nStartPai] = m_nOutPai+1;

				pos2 = FindPaiPos(m_nOutPai+2,m_nStartPai);				
				for( i = pos2;i > m_nStartPai+1;i-- )
				{
					m_nPaiInhand[i] = m_nPaiInhand[i-1];
				}
				m_nPaiInhand[m_nStartPai+1] = m_nOutPai+2;

				m_nNewPai = m_nPaiInhand[12];
				for( i = 12;i > m_nStartPai;i-- )
				{
					m_nPaiInhand[i] = m_nPaiInhand[i-1];
				}
				m_nPaiInhand[m_nStartPai] = m_nOutPai;

				m_nStartPai += 3;
				m_nOutPai = -1;
			}
			break;
		}
	}
	m_nState=1;
}

/*************************************************************/
/*�������ܣ�������
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CWanjia::SetPeng()
{
	if(m_nOutPai!=-1)
	{
		int pos1,pos2,i;
		pos1 = FindPaiPos(m_nOutPai,m_nStartPai);
		for( i = pos1;i > m_nStartPai;i-- )
		{
			m_nPaiInhand[i] = m_nPaiInhand[i-1];
		}
		m_nPaiInhand[m_nStartPai] = m_nOutPai;
		
		pos2 = FindPaiPos(m_nOutPai,pos1+1);
		for( i = pos2;i > m_nStartPai;i-- )
		{
			m_nPaiInhand[i] = m_nPaiInhand[i-1];
		}
		m_nPaiInhand[m_nStartPai+1] = m_nOutPai;
		
		m_nNewPai = m_nPaiInhand[12];
		for( i = 12;i > m_nStartPai+1;i-- )
		{
			m_nPaiInhand[i] = m_nPaiInhand[i-1];
		}
		m_nPaiInhand[m_nStartPai+2] = m_nOutPai;
		
		m_nStartPai += 3;
		m_nOutPai = -1;
	}
	m_nState = 1;
}

/*************************************************************/
/*�������ܣ����ø�
/*��ڲ��������ͣ�Ҫ�ܵ������ƣ�
/*�������ͣ�void
/*************************************************************/
void CWanjia::SetGang(int nPai)
{
	int i,pos1,pos2,pos3;
	pos1 = FindPaiPos(nPai,m_nStartPai);
	pos2 = FindPaiPos(nPai,pos1+1);
	pos3 = FindPaiPos(nPai,pos2+1);
	//������Ƶ���Ҫ�ܵ�������(1���ܣ�2����)
	if(m_nOutPai == nPai)
	{
		for( i = pos1;i > m_nStartPai;i-- )
		{
			m_nPaiInhand[i] = m_nPaiInhand[i-1];
		}
		m_nPaiInhand[m_nStartPai] = nPai;

		pos2 = FindPaiPos(nPai,pos1+1);
		for( i = pos2;i > m_nStartPai+1;i-- )
		{
			m_nPaiInhand[i] = m_nPaiInhand[i-1];
		}
		m_nPaiInhand[m_nStartPai+1] = nPai;

		pos3 = FindPaiPos(nPai,pos2+1);
		for( i = pos3;i > m_nStartPai+2;i-- )
		{
			m_nPaiInhand[i] = m_nPaiInhand[i-1];
		}
		m_nPaiInhand[m_nStartPai+2] = nPai;

		int pos4 = FindPaiPos(nPai,pos3+1);
		m_nPaiInhand[pos4] = m_nNewPai;
		m_nNewPai = -1;

		m_nGang[m_nStartPai/3] = 1;
		m_nStartPai += 3;	
		m_nOutPai = -1;
	}
	else
	{
		if( pos1 != -1 && pos2 != -1 && pos3 != -1 )//��û�й̶��������Ҳ����ͱ����ǰ���
		{
			m_nPaiInhand[pos1] = m_nPaiInhand[m_nStartPai];
			m_nPaiInhand[pos2] = m_nPaiInhand[m_nStartPai+1];
			m_nPaiInhand[pos3] = m_nPaiInhand[m_nStartPai+2];

			if(nPai == m_nNewPai)
			{
				m_nNewPai = -1;
			}
			else
			{
				int pos4 = FindPaiPos(nPai,pos3+1);
				m_nPaiInhand[pos4] = m_nNewPai;
				m_nNewPai = -1;
			}
			m_nPaiInhand[m_nStartPai+2] = nPai;
			m_nPaiInhand[m_nStartPai+1] = nPai;
			m_nPaiInhand[m_nStartPai] = nPai;
			
			m_nGang[m_nStartPai/3] = 2;
			m_nStartPai += 3;
			SortPai(m_nStartPai);
		}
		else			
		{
			pos1 = FindPaiPos(nPai,0,m_nStartPai);

			if(nPai == m_nNewPai)
			{
				m_nNewPai = -1;

			}
			else
			{
				int pos4 = FindPaiPos(nPai,m_nStartPai);
				m_nPaiInhand[pos4] = m_nNewPai;
				m_nNewPai = -1;
			}
			m_nGang[pos1/3] = 1;
			SortPai(m_nStartPai);
		}
	}
}

/*************************************************************/
/*�������ܣ������Ա�����һ���Ա�ͱ�һ�Σ�
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CWanjia::SetGirl()
{
	m_bBoy =! m_bBoy;
}

/*************************************************************/
/*�������ܣ��������е���
/*��ڲ�����ָ�루�Ƶ����飩�����ͣ��Ƶ�������
/*�������ͣ�void
/*************************************************************/
void CWanjia::SetPaiInHand(int* paiArr,int nNum)
{
	m_nNewPai = -1;
	m_nOutNum = 0;
	m_nStartPai = 0;
	m_nState = -1;
	for(int i = 0;i< 4;i++)
	{
		m_nGang[i]=0;
	}
	for(i = 0;i < nNum;i++)
	{
		m_nPaiInhand[i] = paiArr[i];
	}
	for(i = 0;i < 30;i++)
	{
		m_nPaiOut[i] = -1;
	}
}

/*************************************************************/
/*�������ܣ����÷���
/*��ڲ��������ͣ�������
/*�������ͣ�void
/*************************************************************/
void CWanjia::SetFenshu(int nFen)
{
	m_nFenShu = m_nFenShu + nFen;
}

/*************************************************************/
/*�������ܣ��Ƴ��������һ����
/*��ڲ�����void
/*�������ͣ�void
/*************************************************************/
void CWanjia::RemoveOutPai(void)
{
	m_nPaiOut[m_nOutNum-1] = -1;
	m_nOutNum--;
}

/*************************************************************/
/*�������ܣ����Գ���
/*��ڲ��������ͣ��ƣ�
/*�������ͣ����ͣ������ǳ��ƣ�
/*************************************************************/
int CWanjia::CmpOutPai(int nPai)
{
	if(m_nNewPai != nPai)
	{
		int pos;
		pos = FindPaiPos(nPai,m_nStartPai);
		if(pos != -1)
		{
			m_nPaiInhand[pos] = m_nNewPai;
		}
		SortPai(m_nStartPai);
	}
	m_nPaiOut[m_nOutNum] = nPai;
	m_nNewPai = -1;
	m_nOutPai = -1;
	m_nOutNum++;
	m_nState = -1;
	return nPai;
}	

/*************************************************************/
/*�������ܣ���λ�ó���
/*��ڲ��������ͣ��Ƶ�λ�ã�
/*�������ͣ����ͣ������ǳ��ƣ�
/*************************************************************/
int CWanjia::OutPai(int nPlace)
{
	if(nPlace == 14)
	{
		m_nPaiOut[m_nOutNum] = m_nNewPai;
	}
	else
	{
		m_nPaiOut[m_nOutNum] = m_nPaiInhand[nPlace];
		m_nPaiInhand[nPlace] = m_nNewPai;
	}
	SortPai(m_nStartPai);
	m_nNewPai = -1;
	m_nOutPai = -1;
	m_nOutNum++;
	m_nState = -1;
	return m_nPaiOut[m_nOutNum-1];
}

/*************************************************************/
/*�������ܣ��������
/*��ڲ�����void
/*�������ͣ�ָ�루�Ƶ����飩
/*************************************************************/
int* CWanjia::GetPaiInHand(void)
{
	return m_nPaiInhand;
}

/*************************************************************/
/*�������ܣ�����ƿ�ʼ��λ�ã���û�г����ܵ��ƵĿ�ʼλ�ã�
/*��ڲ�������
/*�������ͣ����ͣ�λ�ã�
/*************************************************************/
int CWanjia::GetPaiStart()
{
	return m_nStartPai;
}

/*************************************************************/
/*�������ܣ�������
/*��ڲ��������ͣ�����ʼλ�ã������ͣ��������λ�ã�
/*�������ͣ�void
/*************************************************************/
void CWanjia::SortPai(int start,int end)
{
	int i,j;
	for(i = start;i < end-1;i++)
	{
		for(j = i;j < end;j++)
		{
			if(m_nPaiInhand[i] > m_nPaiInhand[j])
			{
				m_nPaiInhand[i] = m_nPaiInhand[i]^m_nPaiInhand[j];
				m_nPaiInhand[j] = m_nPaiInhand[i]^m_nPaiInhand[j];
				m_nPaiInhand[i] = m_nPaiInhand[i]^m_nPaiInhand[j];
			}
		}
	}
}

/*************************************************************/
/*�������ܣ�����ָ���Ƶ�λ��
/*��ڲ��������ͣ������ƣ������ͣ������￪ʼ�ң������ͣ��ҵ����������
/*�������ͣ����ͣ��ҵ���λ�ã��Ҳ�������-1��
/*************************************************************/
int CWanjia::FindPaiPos(int nPai,int nStart,int nEnd)
{
	for( int i = nStart;i < nEnd;i++ )
	{
		if( m_nPaiInhand[i] == nPai )
		{
			return i;
		}
	}
	return -1;
}
