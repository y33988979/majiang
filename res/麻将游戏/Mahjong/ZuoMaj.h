// ZuoMaj.h: interface for the CZuoMaj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUOMAJ_H__697F1B51_B570_466A_A57E_5992D69AC855__INCLUDED_)
#define AFX_ZUOMAJ_H__697F1B51_B570_466A_A57E_5992D69AC855__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CZuoMaj  
{
private:
	int m_nMaj[136];							//�齫��
	int m_nZuoPai[4][34];						//�������ŵ��齫��4������
	int m_nMajNum;								//�齫����
	int m_nWhere;								//�齫ȡ���Ǹ�λ��
	int m_nWho;									//��ȡ�ĸ�λ�õ��齫
	int m_nZhuang;								//ׯ��
	int m_nSezi;								//ɫ����
	int m_nTailWho;								//�ʼ�õ��ļҵ���
public:
	CZuoMaj();
	virtual ~CZuoMaj();
	void Ruffle();								//ϴ��
	void SortMaj();								//���ĸ�����ڷ���ǽ
	void SetStart(int nwho,int nwhere);			//������ʼλ�ã�ׯ�Һ�ɫ������
	int GetPai();								//��ȡ��ǰ�齫
	void GetPaiqiang(int** nPaiqiang);			//��ȡ��ǽ
	int GetMajNum();							//���ʣ���齫����
	int GetWho();								//��ȡ��ȡ�Ǹ�����
	int GetWhere();								//��ȡ��ȡ����ǽ���Ǹ�λ��
	int GetGangPai();							//��ø���֮�����
};

#endif // !defined(AFX_ZUOMAJ_H__697F1B51_B570_466A_A57E_5992D69AC855__INCLUDED_)
