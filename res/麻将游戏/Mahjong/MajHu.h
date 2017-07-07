// MajHu.h: interface for the CMajHu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAJHU_H__00A958AE_66FF_4B60_9929_20194583CCB8__INCLUDED_)
#define AFX_MAJHU_H__00A958AE_66FF_4B60_9929_20194583CCB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMajHu  
{
private:
	void ThinkFour();									//����ֻ�����ŵ����
	void DeleteStepTeam(int pai,int type);				//��������ɾ��˳��
	void DeleteSameTeam(int pai);						//��������ɾ��3����
	void AddHupai(int pai);								//����ƽ�����
	bool IsStepTeam(int pai,int type);					//�Ƿ���˳��
	bool IsSameTeam(int pai);							//�Ƿ���3����
	void ThinkHu();										//ѭ��ɾ���������е���Ͽ��Ǻ���
	void ThinkThirty();									//����ʮ�����Ƶ����

	CUIntArray m_MajList,m_HupaiList;					//��������Ƶ�����
public:
	void GetHupai(CUIntArray *arr);						//��ú�����
	void SetMjPaiArray(CUIntArray *nPai);				//�����������
	void SetMjPaiArray(int *nPai,int nNum);				//�����������
};

#endif // !defined(AFX_MAJHU_H__00A958AE_66FF_4B60_9929_20194583CCB8__INCLUDED_)
