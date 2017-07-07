// Wanjia.h: interface for the CWanjia class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WANJIA_H__53022020_6C21_472A_85BA_3339F0D05AC9__INCLUDED_)
#define AFX_WANJIA_H__53022020_6C21_472A_85BA_3339F0D05AC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWanjia  
{

private:	
	int			m_nFenShu;									//��ҵķ���
	int			m_nPaiInhand[13];							//����
	int			m_nStartPai;								//�ƵĿ�ʼλ��
	int			m_nGang[4];									//�̶������Ƿ��и���
	int			m_nPaiOut[30];								//�������
	int			m_nOutNum;									//������
	int			m_nNewPai;									//���ƣ����ץ������˴�����ƣ�
	int			m_nOutPai;									//���˳�����
	int			m_nState;									//״̬
	bool		m_bBoy;										//�Ƿ��к�
	CUIntArray m_arrHupai;									//����
public:
	CWanjia();
	virtual ~CWanjia();
	void SetNewPai(int Pai);								//��������
	void SetOutPai(int Pai);								//���ñ��˳�����
	void SetGirl();											//���ó�Ů��
	int GetNewPai();										//�������
	bool GetSex();											//��ȡ����Ա�
	int* GetOutPai();										//��ó��˵���
	int GetOutNum();										//��ó�����
	int GetFenshu();										//�����ҷ���
	int GetState();											//������״̬
	int* GetGangPai();										//��ø���
	void SetChi(int type);									//���ó�
	void SetPeng();											//������
	void SetGang(int nPai);									//���ø�
	void SetPaiInHand(int* paiArr,int nNum);				//�������е���
	void SetFenshu(int nFen);								//������ҷ���
	void RemoveOutPai(void);								//ɾ��һ�Ŵ������
	int OutPai(int nPlace);									//�������
	int CmpOutPai(int nPai);								//���������
	int* GetPaiInHand();									//������е���
	int GetPaiStart();										//������п�ʼ���Ƶ�λ��
	void SortPai(int start=0,int end=13);					//������
	int FindPaiPos(int nPai,int nStart=0,int nEnd=13);		//�ҳ���
	bool IsStepTeam(int type);								//�Ƿ���˳��
	bool ThinkHupai();										//�����Ƿ����
	bool CheckGang(bool& m_bPeng);							//�����Ƿ���Ըܺ���
	bool CheckGangSelf(CUIntArray& m_arrGang);				//�����Լ��Ƿ���Ը�
	bool CheckEat(CUIntArray& m_arrEat);					//�����Ƿ���Գ�
};

#endif // !defined(AFX_WANJIA_H__53022020_6C21_472A_85BA_3339F0D05AC9__INCLUDED_)
