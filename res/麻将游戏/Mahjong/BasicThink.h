// BasicThink.h: interface for the CBasicThink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASICTHINK_H__168DF0E8_CA7B_45EC_98FA_99DCD8BE9309__INCLUDED_)
#define AFX_BASICTHINK_H__168DF0E8_CA7B_45EC_98FA_99DCD8BE9309__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBasicThink  
{
public:
	CBasicThink();
	virtual ~CBasicThink();
	void GetGoodTeam(int &pai1,int &pai2,int &pai3);			//��ó����������
	void SetMjPaiArray(int *nPailist, int nNum);				//�����齫��
	int GetBadly();												//���������
	int GetMaxScore();											//�������ֵ

protected:
	void SetTeamPai(int type);									//���ó������
	bool IsEdge(int pai1,int pai2);								//�����Ƿ��Ǳ�Ե
	void SortMj(int *who,int end);								//����

	bool IsStepTeam(int pai,int &pos1,int &pos2);				//�ж��������Ƿ���˳��
	bool IsSameTeam(int pai,int &pos1,int &pos2);				//�ж��������Ƿ���3����

	bool IsStepTeamThree(int pai,int type,int &pos1,int nStart);//�ж��޳������Ժ��Ƿ��������
	bool IsSameTeamThree(int pai,int &pos1,int nStart);			//�ж��޳������Ժ��Ƿ��ж���

	int FindPos(int pai,int nStart=0);							//�������������д���λ��
	int FindPosThree(int pai,int nStart=0);						//���������޳�������Ϻ�Ĵ���λ��

protected:
	int m_nMajiang[14];
	int m_nRemainThree[14];										//�����޳���ʣ�����		
	int m_nRemainTwo[14];										//�����޳���ʣ�����
	bool m_bMjSelect[14];										//�齫�Ƿ�ѡ��
	
	int m_nPaiTeamThree[15];									//�����Ƶ����
	int m_nCheckNum;											//�����Ƶ������

	int m_nGoodTeamThree[3];									//��ʱ����
	int m_nTotalTeam[3];										//��������
	int m_nNeedPai;												//��Ҫ���ǳ���

	int m_nRemainNumThree,m_nRemainNumTwo,m_nRemainNumOne;		//ÿ���޳���ʣ�����
	int m_nMjNum;												//�齫������
	int m_nScoreThree,m_nScoreTwo;								//�������3�ź����ŵķ���
	int m_nMaxScoreThree,m_nMaxScoreTwo,m_nMaxScoreOne;			//��������ķ���
	int m_nBadly;												//����һ����

	bool m_bHaveDui;											//�Ƿ��н�
};

#endif // !defined(AFX_BASICTHINK_H__168DF0E8_CA7B_45EC_98FA_99DCD8BE9309__INCLUDED_)
