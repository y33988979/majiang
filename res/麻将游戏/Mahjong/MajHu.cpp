// MajHu.cpp: implementation of the CMajHu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mahjong.h"
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
/*�������ܣ���������
/*��ڲ��������鼯��
/*�������ͣ�void
/*************************************************************/
void CMajHu::SetMjPaiArray(CUIntArray *nPai)
{
	for(int i = 0;i < nPai->GetSize();i++)
	{
		m_MajList.Add(nPai->GetAt(i));
	}
}

/*************************************************************/
/*�������ܣ���������
/*��ڲ�����ָ�룬����
/*�������ͣ�void
/*************************************************************/
void CMajHu::SetMjPaiArray(int *nPai,int nNum)
{
	for(int i = 0;i < nNum;i++)
	{
		m_MajList.Add(nPai[i]);
	}
}

/*************************************************************/
/*�������ܣ��Ƿ�����ͬ��
/*��ڲ���������
/*�������ͣ�����
/*************************************************************/
bool CMajHu::IsSameTeam(int pai)
{
	for(int i = 0;i < m_MajList.GetSize();i++)
	{
		if(pai == (int)m_MajList.GetAt(i))			//������ڵ�һ��
		{
			for(int j = i+1;j < m_MajList.GetSize();j++)
			{
				if(pai == (int)m_MajList.GetAt(j))
				{
					return true;
				}
			}
		}
	}
	return false;
}

/*************************************************************/
/*�������ܣ��Ƿ���˳��
/*��ڲ��������ͣ�����
/*�������ͣ�����
/*************************************************************/
bool CMajHu::IsStepTeam(int pai,int type)
{
	int nPai1,nPai2;
	if(type == 1)
	{
		nPai1 = pai-1;
		nPai2 = pai+1;
	}
	else if(type == 2)
	{
		nPai1 = pai+1;
		nPai2 = pai+2;
	}
	else
	{
		nPai1 = pai-1;
		nPai2 = pai-2;
	}
	if( nPai1/9 != nPai2/9 || nPai1/9 != pai/9 
		|| nPai1 >= 27 || nPai2 >= 27  )	//�ж��Ƿ���ͬ����ʽ��������
	{
		return false;
	}
	bool b1 = false,b2 = false;
	int i,nPaiTemp;
	for(i = 0;i < m_MajList.GetSize();i++)
	{
		nPaiTemp = m_MajList.GetAt(i);
		if(nPai1 == nPaiTemp )
		{
			b1 = true;
			break;
		}
	}
	for(i = 0;i < m_MajList.GetSize();i++)
	{
		nPaiTemp = m_MajList.GetAt(i);
		if(nPai2 == nPaiTemp )
		{
			b2 = true;
			break;
		}
	}
	//��1��2�����ھ�Ϊ��,���඼Ϊ��
    return (b1 && b2);
}

/*************************************************************/
/*�������ܣ�ɾ��3��һ����
/*��ڲ���������
/*�������ͣ�void
/*************************************************************/
void CMajHu::DeleteSameTeam(int pai)
{
	
	int i,nPai;
	for(i = 0;i < m_MajList.GetSize();i++)
	{
		nPai = m_MajList.GetAt(i);
		//�ж��Ƿ���ڸ��ƣ����ھ��Ƴ�
		if(pai == nPai )
		{
			m_MajList.RemoveAt(i);
			break;
		}
	}
	for(i = 0;i < m_MajList.GetSize();i++)
	{
		nPai = m_MajList.GetAt(i);
		if(pai == nPai )
		{
			m_MajList.RemoveAt(i);
			break;
		}
	}
}

/*************************************************************/
/*�������ܣ�ɾ��˳��
/*��ڲ��������ͣ����ͣ����ࣩ
/*�������ͣ�void
/*************************************************************/
void CMajHu::DeleteStepTeam(int pai, int type)
{
	int nPai1,nPai2,nPaiTemp;

	if(type == 1)						//��һ��������м��˳�ӣ�
	{
		nPai1 = pai-1;
		nPai2 = pai+1;
	}
	else if(type == 2)					//�ڶ���������ڿ�ͷ��˳�ӣ�
	{
		nPai1 = pai+1;
		nPai2 = pai+2;
	}
	else								//�����������������˳�ӣ�
	{
		nPai1 = pai-1;
		nPai2 = pai-2;
	}
	for(int i = 0;i < m_MajList.GetSize();i++)
	{
		nPaiTemp = m_MajList.GetAt(i);
		if(nPai1 == nPaiTemp )			//����������ƾ�ɾ��
		{
			m_MajList.RemoveAt(i);
			break;
		}
	}
	for(i = 0;i < m_MajList.GetSize();i++)
	{
		nPaiTemp = m_MajList.GetAt(i);
		if(nPai2 == nPaiTemp )
		{
			m_MajList.RemoveAt(i);
			break;
		}
	}
}

/*************************************************************/
/*�������ܣ���Ӻ��Ƶ���
/*��ڲ���������
/*�������ͣ�void
/*************************************************************/
void CMajHu::AddHupai(int pai)
{
	if(pai < 0 || pai > 33)
	{
		return;
	}
	int i,nPai;
	for(i = 0;i < m_HupaiList.GetSize();i++)
	{
		nPai = m_HupaiList.GetAt(i);
		if(pai == nPai )				//�ж��Ƿ�����ͬ�����ں��Ƽ�����
		{
			return;
		}
		if(pai < nPai)				//��˳������ں��������Ӧλ���Ա����
		{
			break;	
		}
	}
	m_HupaiList.InsertAt(i,pai);
}

/*************************************************************/
/*�������ܣ���ú�����
/*��ڲ����������鼯��
/*�������ͣ�void
/*************************************************************/
void CMajHu::GetHupai(CUIntArray *arr)
{
	if((m_MajList.GetSize()-1)%3)
	{
		return;
	}
	if(m_MajList.GetSize() == 13)			//�����߶Ե����
	{
		ThinkThirty();
	}
	if(m_MajList.GetSize() == 1)			//���ֻ��һ�ž�ֻ��ӵ�ǰ��һֻ
	{
		arr->Add(m_MajList.GetAt(0));
		return;
	}
	ThinkHu();
    for(int i = 0;i < m_HupaiList.GetSize();i++)
	{
		arr->Add(m_HupaiList.GetAt(i));
	}
}

/*************************************************************/
/*�������ܣ�����ֻ��4���Ƶ����
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CMajHu::ThinkFour()
{
	int nPai1,nPai2,nPai3,nPaiTemp,i,j;
	//ѭ�������Ƿ�ֻ����
	for(i = 0;i < 4;i++)
	{
		nPai1 = m_MajList.GetAt(i);
		m_MajList.RemoveAt(i);
		
		if(IsSameTeam(nPai1))
		{
			DeleteSameTeam(nPai1);
			AddHupai(m_MajList.GetAt(0));
			m_MajList.Add(nPai1);
			m_MajList.Add(nPai1);
		}
		
		if(IsStepTeam(nPai1,1))
		{
			DeleteStepTeam(nPai1,1);
			AddHupai(m_MajList.GetAt(0));
			m_MajList.Add(nPai1-1);
			m_MajList.Add(nPai1+1);
		}
		
		if(IsStepTeam(nPai1,2))
		{
			DeleteStepTeam(nPai1,2);
			AddHupai(m_MajList.GetAt(0));
			m_MajList.Add(nPai1+1);
			m_MajList.Add(nPai1+2);
		}
		
		if(IsStepTeam(nPai1,3))
		{
			DeleteStepTeam(nPai1,3);
			AddHupai(m_MajList.GetAt(0));
			m_MajList.Add(nPai1-2);
			m_MajList.Add(nPai1-1);
		}
		m_MajList.Add(nPai1);
	}
	//ѭ������4�������Ƿ��У�һ�Խ������ӵĺ�����
	for(i = 0;i < 4;i++)
	{
		nPai1 = m_MajList.GetAt(i);
		m_MajList.RemoveAt(i);
		for(j = 0;j < 3;j++)
		{
			nPaiTemp = m_MajList.GetAt(j);
			//�ж��Ƿ���һ�Խ��������ж��Ƿ�������
			if(nPai1 == nPaiTemp  )
			{
				m_MajList.RemoveAt(j);
				//ʣ���������
				nPai2=m_MajList.GetAt(0);
				nPai3=m_MajList.GetAt(1);
				//���ʣ�����������ͬ�����Ǻ���������
				if(nPai2 == nPai3  )
				{
					AddHupai(nPai1);
					AddHupai(nPai2);
				}
				//���ʣ��������Ʋ�ͬ������һ����ʽ���ڣ����Ҷ�������
				if( nPai2/9 == nPai3/9 && nPai2 < 27 && nPai3 < 27 )
				{
					//�ж������Ƶ�����������
					switch(nPai2 - nPai3)
					{
					case 1://����������6-5��7-6��
						if((nPai2-8)%9)//�ж��Ƿ�߽�8
						{
							AddHupai(nPai2+1);
						}
						if((nPai2-1)%9)//�ж��Ƿ�߽�1
						{
							AddHupai(nPai2-2);
						}
						break;
					case -1://˳��������5-6��7-8��
						if(nPai2%9)//�ж��Ƿ�߽�0
						{
							AddHupai(nPai2-1);
						}
						if((nPai2+1-8)%9)//�ж��Ƿ�߽�7
						{
							AddHupai(nPai2+2);
						}
						break;
					case 2://������һ�ŵ�������4-2��6-4��
						if( nPai2%9)
						{
							AddHupai(nPai2-1);
						}
						break;
					case -2://˳����һ�ŵ�������2-4��4-6��
						if( (nPai2-8)%9)
						{
							AddHupai(nPai2+1);
						}
						break;
					default:
						break;
					}
				}
				m_MajList.Add(nPai1);
			}
		}
		m_MajList.Add(nPai1);	
	}
}

/*************************************************************/
/*�������ܣ�����ʮ�����Ƿ��߶Ե����
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CMajHu::ThinkThirty()
{
	int i,j,nPai;
	bool bTemp = false;
	CUIntArray m_MajTemp;
	for(i = 0;i < m_MajList.GetSize();i++)
	{
		m_MajTemp.Add(m_MajList.GetAt(i));
	}
	for(i = 0;i < m_MajTemp.GetSize();i++)
	{
		nPai = m_MajTemp.GetAt(i);
		m_MajTemp.RemoveAt(i);
		bTemp = false;
		for(j=0;j<m_MajTemp.GetSize();j++)			//���Ƿ��ж���
		{
			if((int)m_MajTemp.GetAt(j)==nPai)		//�о��Ƴ�������
			{
				m_MajTemp.RemoveAt(j);
				bTemp = true;
			}
		}
		if( !bTemp )								//û�оͰѸղ��Ƴ��ļ���
		{
			m_MajTemp.Add(nPai);
		}
	}
	if(m_MajTemp.GetSize() == 1)					//������ֻʣһ�ž�����
	{
		m_HupaiList.Add(m_MajTemp.GetAt(0));
	}
}

/*************************************************************/
/*�������ܣ����Ǻ���
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CMajHu::ThinkHu()
{
	int nPai,i;
	//���ѭ������ֻʣ��4�žͿ���
	if(m_MajList.GetSize() <= 4)
	{
		ThinkFour();
		return;
	}
	//����������е����
	for(i = 0;i < m_MajList.GetSize();i++)
	{
		nPai = m_MajList.GetAt(i);
		m_MajList.RemoveAt(i);
		if(IsSameTeam(nPai))
		{
			DeleteSameTeam(nPai);
			ThinkHu();
			m_MajList.Add(nPai);
			m_MajList.Add(nPai);
		}

		if(IsStepTeam(nPai,1))
		{
			DeleteStepTeam(nPai,1);
			ThinkHu();
			m_MajList.Add(nPai-1);
			m_MajList.Add(nPai+1);		
		}
		if(IsStepTeam(nPai,2))
		{
			DeleteStepTeam(nPai,2);
			ThinkHu();
			m_MajList.Add(nPai+1);
			m_MajList.Add(nPai+2);
		}
		if(IsStepTeam(nPai,3))
		{
			DeleteStepTeam(nPai,3);
			ThinkHu();
			m_MajList.Add(nPai-1);
			m_MajList.Add(nPai-2);
		}
		m_MajList.Add(nPai);
	}
	
}