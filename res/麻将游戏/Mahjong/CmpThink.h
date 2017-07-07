// CmpThink.h: interface for the CCmpThink class.
//
//////////////////////////////////////////////////////////////////////
#include "BasicThink.h"


#if !defined(AFX_CMPTHINK_H__69461101_C669_42EB_B306_5099EC88B2D3__INCLUDED_)
#define AFX_CMPTHINK_H__69461101_C669_42EB_B306_5099EC88B2D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCmpThink:public CBasicThink
{
public:	
	CCmpThink();											//���캯��
	void CheckOnlyTwo();									//�����޳����ź������ӻ���ӵ����
	void Think();											//˼���ó�����ֵ

protected:
	int AddGood(int pai);
	void ThinkThree();										//�������ŵ����(�����е�����޳�)
	void ThinkTwo();										//(����������޳���)����2�ŵ����
	void ThinkOne();										//(����������޳���)����1���Ƶ������
};

#endif // !defined(AFX_CMPTHINK_H__69461101_C669_42EB_B306_5099EC88B2D3__INCLUDED_)
