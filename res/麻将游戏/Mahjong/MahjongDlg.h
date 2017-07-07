// MahjongDlg.h : header file
//

#include "Wanjia.h"
#include "CmpThink.h"
#include "CleverThink.h"
#include "ZuoMaj.h"
#include "MajHu.h"

#if !defined(AFX_MAHJONGDLG_H__BE37E4CF_7A4F_4452_8280_91342724CEDA__INCLUDED_)
#define AFX_MAHJONGDLG_H__BE37E4CF_7A4F_4452_8280_91342724CEDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMahjongDlg dialog

#define TITLE_EAT		100				//�Ա���
#define TITLE_PENG		101				//������
#define TITLE_GANG		102				//�ܱ���
#define TITLE_HU		103				//������
#define TITLE_GUO		104				//������
#define TITLE_CLOSE		105				//�ر�ͼ��
#define TITLE_MIN		106				//��С��ͼ��
#define TITLE_SET		107				//����ͼ��

#define TimeSelect		20				//���ѡ���ʱ�䣨�룩
#define TimeSezi		15				//ɫ�Ӷ�����ʱ�䣨����
#define TimeRun			500			//������Ҵ����Ƶ�ʱ�䣨���룩
									

class CMahjongDlg : public CDialog
{
// Construction
public:
	CMahjongDlg(CWnd* pParent = NULL);	// standard constructor
	void UpdateFrame();	
	void DrawTitle();									//������
	void DrawPai();										//����
	void DrawPaiUp(int nPai);							//��������
	void DrawPaiQiang();								//����ǽ
	void DrawPaiOut();									//�����˵���
	void DrawSelect();									//�����Ƶ�����
	void DrawSezi();									//��ɫ��
	void DrawActive(int nWho);							//����˭����
	void SetPai();										//���ÿ�ʼʱ����
	void SetZhuang(int nWan);							//����ׯ��
	void SetSezi(int nNum);								//����ɫ��
	void SortWjPai();									//������ҵ���
	int CmpThink(int nWho);								//����˼����Ҫ��������			
	int  CheckNeedGet(int nWho,int pai);				//�������Ƿ���Ҫ������
	void  CheckWhoGet();								//��ø���ҵ�������Ʒ�
	bool CheckPerson();									//������Ƿ���Գ�����
	int GetMaxWho(int& nMaxScore);						//������������˭����������Ʒ��Ƕ���
	bool CheckLiuju();									//�������
	void  CmpActive(int nWho);							//���Ե���Ϊ
	void  PlayPaiSound(int nPai,bool bBoy=true);		//�Ƶ�����
	void  PlayOtherSound(int nType,bool bBoy=true);		//�������
	void CountFenshu();									//������ƺ�ķ���
	void MoveTitle(CPoint point);						//����ڱ����ϵ��ƶ�
	void OnClickTitle(CPoint point);					//�������
	void DrawUpPai(int nPlace);							//��������
	void ShowFenshu();									//��ʾ����
	void ChangBoolFalse();								//�ѳԺ����Ȳ����ĳɼ�
	void DrawAllpai();									//�����е���

	enum{S_HU,S_GAN,S_EAT,S_PEN,S_LIU};
	CDC m_bgDC,m_memDC,m_paiDC,m_titleDC,m_seziDC,m_numDC;
	int				m_nOutPai;							//������
	bool			m_bStart;							//�Ƿ�ʼ
	bool			m_bRun;								//ϵͳ����
	bool			m_bCaton;							//��������
	int				m_nZhuang;							//��¼ׯ��
	int				m_nSeNum;							//��¼ɫ֮��
	int				m_nActive;							//����Ȩ
	int				m_nPanduan;							//�жϵ�˭ͷ����
	CUIntArray		m_arrHupai[4];						//��Һ�����
	CUIntArray		m_arrEat;							//�ܳԵ����						
	CUIntArray		m_arrGang;							//�ܸܵ����
	int				m_nCmpGoodScore[4];					//��¼���Ե���ѷ�ֵ
	bool m_bHu,m_bPeng,m_bChi,m_bGang;					//�ܷ��������
	int				m_nGoodScore[4];					//���ȼ�
	bool			m_nAbandon;							//����
	bool			m_bSelect;							//ѡ��ܻ��߳�				
	CRect			m_rtTitle[8];						//��������
	int				m_nSelectGang;						//��ǰѡ��ĸ�
	int				m_nSelectEat;						//��ǰѡ��ĳ�
	int				m_nSelectTime;						//ѡ���ʱ��
	int				m_nWaitTime;						//��ҵȴ�ʱ��
	bool			m_bWait;							//��ҵȴ�״̬
	int				m_nHuType;							//���Ƶ�����
	int				m_nHuWho;							//˭������
	int				m_nFirst;							//��һ��
	bool			m_bZuobi;							//����
	

// Dialog Data
	//{{AFX_DATA(CMahjongDlg)
	enum { IDD = IDD_MAHJONG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMahjongDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CWanjia			m_wjMaj[4];							//4�����
	CZuoMaj			m_zmMaj;							//������ǽ
	HCURSOR			m_hCursorHand;						//���
	HCURSOR			m_hCursor;							//���

	int				m_nMousePai;						//������ڵ���
	int				m_nChupaiUser;						//�û�����
	int				m_nTitle;							//������ڱ���
	bool			m_bHandDown;						//�����ѹ�Ƿ���ѹ
	bool			m_bwjState;							//�Ƿ����ѡ��״̬
	bool			m_bOver;							//�Ƿ����

	// Generated message map functions
	//{{AFX_MSG(CMahjongDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAHJONGDLG_H__BE37E4CF_7A4F_4452_8280_91342724CEDA__INCLUDED_)
