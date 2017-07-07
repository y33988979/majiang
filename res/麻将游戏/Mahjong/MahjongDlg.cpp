// MahjongDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Mahjong.h"
#include "MahjongDlg.h"

#include <wingdi.h>

#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CMahjongDlg dialog

CMahjongDlg::CMahjongDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMahjongDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMahjongDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hCursor = AfxGetApp()->LoadCursor (IDC_CURSOR);
	m_hCursorHand = AfxGetApp()->LoadCursor (IDC_CURSOR_Hand);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMahjongDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMahjongDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMahjongDlg, CDialog)
//{{AFX_MSG_MAP(CMahjongDlg)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_WM_TIMER()
ON_WM_MOUSEMOVE()
ON_WM_SETCURSOR()
ON_WM_LBUTTONUP()
ON_WM_LBUTTONDOWN()
ON_WM_CREATE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMahjongDlg message handlers

BOOL CMahjongDlg::OnInitDialog()
{
	SetWindowText("�齫");
	MoveWindow(0,0,800,600);
	CenterWindow();

	
	m_bgDC.CreateCompatibleDC(GetDC());
	m_paiDC.CreateCompatibleDC(GetDC());
	m_memDC.CreateCompatibleDC(GetDC());
	m_titleDC.CreateCompatibleDC(GetDC());	
	m_seziDC.CreateCompatibleDC(GetDC());
	m_numDC.CreateCompatibleDC(GetDC());

	CBitmap bm;
	bm.LoadBitmap(IDB_BITMAP_Bg);
	m_bgDC.SelectObject(&bm);
	bm.DeleteObject();
	bm.LoadBitmap(IDB_BITMAP_Maj);
	m_paiDC.SelectObject(&bm);
	bm.DeleteObject();
	bm.LoadBitmap(IDB_BITMAP_Title);
	m_titleDC.SelectObject(&bm);
	bm.DeleteObject();
	bm.LoadBitmap(IDB_BITMAP_Sezi);
	m_seziDC.SelectObject(&bm);
	bm.DeleteObject();
	bm.LoadBitmap(IDB_BITMAP_Num);
	m_numDC.SelectObject(&bm);
	bm.DeleteObject();


	bm.CreateCompatibleBitmap(GetDC(),800,600);
	m_memDC.SelectObject(&bm);
	bm.DeleteObject();
	m_bgDC.BitBlt(692,20,18,18,&m_titleDC,108,80,SRCCOPY);
	m_bgDC.BitBlt(710,20,18,18,&m_titleDC,54,80,SRCCOPY);
	m_bgDC.BitBlt(728,20,18,18,&m_titleDC,0,80,SRCCOPY);
	
	m_memDC.BitBlt(0,0,800,600,&m_bgDC,0,0,SRCCOPY);
	m_memDC.BitBlt(370,400,55,28,&m_titleDC,0,127,SRCCOPY);
	m_nMousePai=-1;

	//��ʼ������
	m_bHandDown=false;
	m_bOver=false;
	m_bZuobi=false;
	m_bStart=true;
	m_bRun=false;
	m_bCaton=false;

	m_nSelectEat=-1;
	m_nSelectGang=-1;

	//�������1��3ΪŮ��
	m_wjMaj[1].SetGirl();
	m_wjMaj[3].SetGirl();
	SetZhuang(0);

	//���ü������������
	m_rtTitle[0].SetRect(590,444,614,468);
	m_rtTitle[1].SetRect(619,444,643,468);
	m_rtTitle[2].SetRect(648,444,672,468);
	m_rtTitle[3].SetRect(678,444,702,468);
	m_rtTitle[4].SetRect(713,444,737,468);
	m_rtTitle[5].SetRect(710,20,728,38);
	m_rtTitle[6].SetRect(728,20,746,38);
	m_rtTitle[7].SetRect(692,20,710,38);

	//���ű�������
	sndPlaySound("Sounds\\bg.wav",SND_ASYNC|SND_LOOP);

	CDialog::OnInitDialog();
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMahjongDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
		UpdateFrame();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMahjongDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*************************************************************/
/*�������ܣ����ų��齫���������
/*��ڲ��������ͣ����ࣩ���������Ƿ��У�
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::PlayOtherSound(int nType,bool bBoy)
{
	CString strFile;
	switch(nType)
	{
	case S_HU:
		strFile = "��.wav";
		break;
	case S_GAN:
		strFile = "��.wav";
		break;
	case S_EAT:
		strFile = "��.wav";
		break;
	case S_PEN:
		strFile = "��.wav";
		break;
	case S_LIU:
		strFile = "����.wav";
		break;
	}
	
	if( bBoy )
	{
		strFile = "boy\\"+strFile;
	}
	else
	{
		strFile = "girl\\"+strFile;
	}
	
	::sndPlaySound("Sounds\\"+strFile,SND_ASYNC|SND_NODEFAULT);		
}

/*************************************************************/
/*�������ܣ������齫����
/*��ڲ��������壨�齫�����������Ƿ��У�
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::PlayPaiSound(int nPai,bool bBoy)
{
	CString strFile;
	if( nPai < 9 )
	{
		strFile.Format("%d��.wav",nPai%9+1);
	}
	else if( nPai < 18 )
	{
		strFile.Format("%d��.wav",nPai%9+1);
	}
	else if( nPai < 27 )
	{
		strFile.Format("%d��.wav",nPai%9+1);
	}
	else
	{
		switch(nPai)
		{
		case 27:
			strFile = "����.wav";
			break;
		case 28:
			strFile = "�Ϸ�.wav";
			break;
		case 29:
			strFile = "����.wav";
			break;
		case 30:
			strFile = "����.wav";
			break;
		case 31:
			strFile = "��.wav";
			break;
		case 32:
			strFile = "��.wav";
			break;
		case 33:
			strFile = "��.wav";
			break;
		}
	}
	if( bBoy )
	{
		strFile = "boy\\"+strFile;
	}
	else
	{
		strFile = "girl\\"+strFile;
	}
	::sndPlaySound("Sounds\\"+strFile,SND_ASYNC);		
	
}

/*************************************************************/
/*�������ܣ����Ե�״̬Ϊ����ʱ˼��
/*��ڲ��������ͣ���һ�ҵ��ԣ�
/*�������ͣ����ͣ�����Ҫ�����ƣ����˷���1000���ܷ��ظ�����
/*************************************************************/
int CMahjongDlg::CmpThink(int nWho)
{
	int a[14],i,j,k;
	int nStar,nNew;
	nStar = m_wjMaj[nWho].GetPaiStart();
	nNew = m_wjMaj[nWho].GetNewPai();

	if(m_wjMaj[nWho].ThinkHupai())							//�����Ƿ�����
	{
		return 1000;
	}
	for(i = 0;i < 13-nStar;i++)
	{
		a[i]  =m_wjMaj[nWho].GetPaiInHand()[i+nStar];
	}
	a[13-nStar] = nNew;
	CUIntArray caGang;

	CCmpThink ct;
	ct.SetMjPaiArray(a,14-nStar);
	ct.Think();
	
	m_nCmpGoodScore[nWho] = ct.GetMaxScore();					//��Ϻ��¼����

	if(m_wjMaj[nWho].CheckGangSelf(caGang))						//�����������ܸܣ��ͼ���Ƿ�ܺ�Ӱ���
	{
		for(i = 0;i < caGang.GetSize();i++)
		{	
			for(j = 0,k = 0;j < 13-nStar;j++)
			{
				if(m_wjMaj[nWho].GetPaiInHand()[i+nStar] != (int)caGang.GetAt(i))
				{
					a[k] = m_wjMaj[nWho].GetPaiInHand()[i+nStar];
					k++;
				}
			}
			if((int)caGang.GetAt(i) != nNew)
			{
				a[k] = nNew;
				k++;
			}
			CCmpThink ctTemp;
			ctTemp.SetMjPaiArray(a,k);
			ctTemp.Think();
			if(ctTemp.GetMaxScore() >= m_nCmpGoodScore[nWho]-300)
			{
				return caGang.GetAt(i)-100;
			}
		}

	}
	int ret = ct.GetBadly();									//�������һ����
	return ret;
}

/*************************************************************/
/*�������ܣ�������Ļ
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::UpdateFrame()
{
	if(m_bRun)
	{
		//����ͷ
		DrawActive(m_nActive);	
		int nFirst,nSecond;
		//���м�����
		if(m_bwjState || (m_bWait && m_wjMaj[0].GetState() == 1))
		{
			if(m_bwjState)
			{
				nFirst = m_nSelectTime/10;
				nSecond = m_nSelectTime%10;
			}
			if(m_bWait && m_wjMaj[0].GetState() == 1)
			{
				nFirst = m_nWaitTime/10;
				nSecond = m_nWaitTime%10;
			}		
			COLORREF rf = m_numDC.GetPixel(0,0);
			TransparentBlt(m_memDC.GetSafeHdc(),394,264,17,29,m_numDC.GetSafeHdc(),nFirst*17,0,17,29,rf);
			TransparentBlt(m_memDC.GetSafeHdc(),414,264,17,29,m_numDC.GetSafeHdc(),nSecond*17,0,17,29,rf);
		}
	}
	//��ʾ����DC
	CClientDC dc(this);
	dc.BitBlt(0,0,800,600,&m_memDC,0,0,SRCCOPY);
}

/*************************************************************/
/*�������ܣ���ӡ����
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::ShowFenshu()
{
	//��ӡ����
	int nGet,nRemove;
	char str[8][128];
	switch(m_nHuType)
	{
	case 1:
		{
			nGet = 150;
			nRemove = -50;
			sprintf(str[7],"���˵�����");
		}
		break;
	case 2:
		{
			nGet = 300;
			nRemove = -100;
			sprintf(str[7],"��������");
		}
		break;
	case 3:
		{
			nGet = 450;
			nRemove = -150;
			sprintf(str[7],"����,���");
		}
	case 4:
		{
			nGet = 0;
			nRemove = 0;
			sprintf(str[7],"��,����");
		}
		break;
	}

	//����˭��������ʾ����ͳ�ƽ��
	switch(m_nHuWho)
	{
	case 0:	
		{
			sprintf(str[0],"�¼ҷ���:  %-6d ( +%d )",m_wjMaj[0].GetFenshu(),nGet);	
			sprintf(str[1],"�Ҽҷ���:  %-6d ( %d )",m_wjMaj[1].GetFenshu(),nRemove);
			sprintf(str[2],"�ϼҷ���:  %-6d ( %d )",m_wjMaj[2].GetFenshu(),nRemove);
			sprintf(str[3],"��ҷ���:  %-6d ( %d )",m_wjMaj[3].GetFenshu(),nRemove);
		}
		break;
	case 1:
		{
			sprintf(str[0],"�Ҽҷ���:  %-6d ( +%d )",m_wjMaj[1].GetFenshu(),nGet);	
			sprintf(str[1],"�¼ҷ���:  %-6d ( %d )",m_wjMaj[0].GetFenshu(),nRemove);
			sprintf(str[2],"�ϼҷ���:  %-6d ( %d )",m_wjMaj[2].GetFenshu(),nRemove);
			sprintf(str[3],"��ҷ���:  %-6d ( %d )",m_wjMaj[3].GetFenshu(),nRemove);
		}
		break;
	case 2:
		{
			sprintf(str[0],"�ϼҷ���:  %-6d ( +%d )",m_wjMaj[2].GetFenshu(),nGet);	
			sprintf(str[1],"�¼ҷ���:  %-6d ( %d )",m_wjMaj[0].GetFenshu(),nRemove);
			sprintf(str[2],"�Ҽҷ���:  %-6d ( %d )",m_wjMaj[1].GetFenshu(),nRemove);
			sprintf(str[3],"��ҷ���:  %-6d ( %d )",m_wjMaj[3].GetFenshu(),nRemove);
		}
		break;
	case 3:
		{
			sprintf(str[0],"��ҷ���:  %-6d ( +%d )",m_wjMaj[3].GetFenshu(),nGet);	
			sprintf(str[1],"�¼ҷ���:  %-6d ( %d )",m_wjMaj[0].GetFenshu(),nRemove);
			sprintf(str[2],"�Ҽҷ���:  %-6d ( %d )",m_wjMaj[1].GetFenshu(),nRemove);
			sprintf(str[3],"�ϼҷ���:  %-6d ( %d )",m_wjMaj[2].GetFenshu(),nRemove);
		}
		break;
	}
	sprintf(str[4],"Ӯ�ң�");
	sprintf(str[5],"��ң�");
	sprintf(str[6],"%6d",nGet);
	CFont ft,*oldft;
	//��������
	ft.CreatePointFont(110,"����",NULL);
	oldft=m_memDC.SelectObject(&ft);
	m_memDC.SetTextColor(RGB(198,145,86));
	m_memDC.SetBkMode(TRANSPARENT);
	CRect rect0(320,223,800,243);
	CRect rect1(320,270,800,290);
	CRect rect2(320,290,800,310);
	CRect rect3(320,310,800,330);
	CRect rect4(240,223,800,243);
	CRect rect5(240,260,800,300);
	CRect rect6(300,360,800,400);
	CRect rect7(330,170,480,200);
	m_memDC.DrawText(str[0],rect0,DT_LEFT | DT_SINGLELINE | DT_VCENTER     );
	m_memDC.DrawText(str[1],rect1,DT_LEFT | DT_SINGLELINE | DT_VCENTER     );
	m_memDC.DrawText(str[2],rect2,DT_LEFT | DT_SINGLELINE | DT_VCENTER     );
	m_memDC.DrawText(str[3],rect3,DT_LEFT | DT_SINGLELINE | DT_VCENTER     );
	ft.DeleteObject();
	ft.CreatePointFont(130,"�����п�",NULL);
	m_memDC.SelectObject(ft);
	m_memDC.SetTextColor(RGB(198,145,86));
	m_memDC.DrawText(str[4],rect4,DT_LEFT | DT_SINGLELINE | DT_VCENTER     );
	m_memDC.DrawText(str[5],rect5,DT_LEFT | DT_SINGLELINE | DT_VCENTER     );
	ft.DeleteObject();
	ft.CreatePointFont(180,"����",NULL);
	m_memDC.SelectObject(ft);
	m_memDC.SetTextColor(RGB(198,145,86));
	m_memDC.DrawText(str[6],rect6,DT_LEFT | DT_SINGLELINE | DT_VCENTER     );
	ft.DeleteObject();
	ft.CreatePointFont(180,"����",NULL);
	m_memDC.SelectObject(ft);
	m_memDC.SetTextColor(RGB(232,210,140));
	m_memDC.DrawText(str[7],rect7,DT_CENTER | DT_SINGLELINE | DT_VCENTER     );
	m_memDC.SelectObject(oldft);

}

/*************************************************************/
/*�������ܣ�����ׯ��
/*��ڲ���������
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::SetZhuang(int nWan)
{
	if(nWan >= 0&&nWan < 4)
	{
		m_nZhuang = nWan;
	}
	else
	{
		m_nZhuang = 0;
	}
}

/*************************************************************/
/*�������ܣ�����ɫ����
/*��ڲ���������
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::SetSezi(int nNum)
{
	if(nNum >= 0&&nNum < 12)
	{
		m_nSeNum = nNum;
	}
	else
	{
		m_nSeNum = 12;
	}
}

/*************************************************************/
/*�������ܣ����ó�ʼ������
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::SetPai()
{
	//��ʼ��������
	m_nMousePai = -1;
	m_bStart = false;
	m_bRun = true;
	ChangBoolFalse();
	m_nOutPai = -1;

	m_bWait = true;

	m_nSelectTime = TimeSelect;
	m_nWaitTime = TimeSelect;

	m_bwjState = false;
	m_nAbandon = false;
	m_bSelect = false;

	//���Ƹ������ 
	int nWanjia[4][13] = {0};
	int i,j = 0;
	m_zmMaj.SetStart(m_nZhuang,m_nSeNum*2);
	for(i = 0;i < 13;i++)
	{
		nWanjia[0][i] = m_zmMaj.GetPai();
		nWanjia[1][i] = m_zmMaj.GetPai();
		nWanjia[2][i] = m_zmMaj.GetPai();
		nWanjia[3][i] = m_zmMaj.GetPai();
	}
	//��ʼ���������
	for(i=0;i<4;i++)
	{
		m_nGoodScore[i]=0;
	}
	int nTemp=m_nZhuang;
	for(i=0;i<4;i++)
	{
		m_wjMaj[nTemp].SetPaiInHand(nWanjia[i],13);
		nTemp++;
		if(nTemp>3)
			nTemp=0;
	}
	m_nActive=m_nZhuang;
	//ȡ�õ�����ѷ�ֵ
	for(i=1;i<4;i++)
	{	
		int a[14];
		for(int j = 0;j < 13;j++)
		{
			a[j] = m_wjMaj[i].GetPaiInHand()[j];
		}
		CCmpThink ct;
		ct.SetMjPaiArray(a,13);
		ct.Think();
		m_nCmpGoodScore[i]=ct.GetMaxScore();
	}
	m_memDC.BitBlt(0,0,800,600,&m_bgDC,0,0,SRCCOPY);
	DrawActive(m_nZhuang);
	SortWjPai();
	DrawAllpai();
	UpdateFrame();
}

/*************************************************************/
/*�������ܣ����м�ļ�ͷ��ׯ������
/*��ڲ��������ͣ���ǰ��˭���
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::DrawActive(int nWho)
{
	m_memDC.BitBlt(360,231,103,95,&m_bgDC,360,231,SRCCOPY);
	COLORREF rf=m_numDC.GetPixel(1,1);
	TransparentBlt(m_memDC.GetSafeHdc(),385,255,60,48,m_numDC.GetSafeHdc(),0,55,60,48,rf);
	switch(m_nZhuang)				//����ׯ�һ�
	{
	case 0:
		TransparentBlt(m_memDC.GetSafeHdc(),400,325,25,25,m_numDC.GetSafeHdc(),173,0,25,25,rf);
		break;
	case 1:	
		TransparentBlt(m_memDC.GetSafeHdc(),462,265,25,25,m_numDC.GetSafeHdc(),198,0,25,25,rf);
		break;
	case 2:	
		TransparentBlt(m_memDC.GetSafeHdc(),400,206,25,25,m_numDC.GetSafeHdc(),173,0,25,25,rf);
		break;
	case 3:
		TransparentBlt(m_memDC.GetSafeHdc(),334,265,25,25,m_numDC.GetSafeHdc(),173,0,25,25,rf);
		break;
	}
	switch(nWho)					//����˭�����ͷ
	{
	case 0:	
		TransparentBlt(m_memDC.GetSafeHdc(),402,300,22,25,m_numDC.GetSafeHdc(),0,30,22,25,rf);
		break;
	case 1:
		TransparentBlt(m_memDC.GetSafeHdc(),438,265,25,26,m_numDC.GetSafeHdc(),22,30,25,26,rf);
		break;
	case 2:
		TransparentBlt(m_memDC.GetSafeHdc(),402,231,22,25,m_numDC.GetSafeHdc(),50,30,22,25,rf);
		break;
	case 3:
		TransparentBlt(m_memDC.GetSafeHdc(),360,265,25,26,m_numDC.GetSafeHdc(),72,30,25,26,rf);
		break;
	}
}

/*************************************************************/
/*�������ܣ������е���
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::DrawAllpai()
{
	DrawPai();
	DrawPaiQiang();
	DrawPaiOut();
	DrawPaiUp(m_nMousePai);
	DrawTitle();
}

/*************************************************************/
/*�������ܣ�������
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::DrawTitle()
{
	//������
	m_memDC.BitBlt(692,20,18*3,18,&m_bgDC,692,20,SRCCOPY);
	if(m_nMousePai == TITLE_MIN)
	{
		m_memDC.BitBlt(710,20,18,18,&m_titleDC,54+18,80,SRCCOPY);
	}
	else if(m_nMousePai == TITLE_CLOSE)
	{
		m_memDC.BitBlt(728,20,18,18,&m_titleDC,18,80,SRCCOPY);
	}
	else if(m_nMousePai == TITLE_SET)
	{
		m_memDC.BitBlt(692,20,18,18,&m_titleDC,108+18,80,SRCCOPY);
	}
	//����״̬�µĳ����ܵȱ���
	if(m_bRun)
	{
		m_memDC.BitBlt(580,440,162,34,&m_titleDC,0,0,SRCCOPY);
		if(m_bGang)
		{
			if(m_nMousePai == TITLE_GANG)
				m_memDC.BitBlt(646,444,26,26,&m_titleDC,108,54,SRCCOPY);
			m_memDC.BitBlt(648,446,22,22,&m_titleDC,43,34,SRCCOPY);
		}
		if(m_bHu)
		{
			if(m_nMousePai == TITLE_HU)
				m_memDC.BitBlt(676,444,26,26,&m_titleDC,108,54,SRCCOPY);
			m_memDC.BitBlt(678,446,22,22,&m_titleDC,64,34,SRCCOPY);
		}
		//ѡ��״̬�µ�
		if(m_bwjState)
		{
			if(m_bChi)
			{
				if(m_nMousePai == TITLE_EAT)
					m_memDC.BitBlt(590,444,26,26,&m_titleDC,108,54,SRCCOPY);
				m_memDC.BitBlt(592,446,22,22,&m_titleDC,0,34,SRCCOPY);
			}
			if(m_bPeng)
			{
				if(m_nMousePai == TITLE_PENG)
					m_memDC.BitBlt(617,444,26,26,&m_titleDC,108,54,SRCCOPY);
				m_memDC.BitBlt(619,446,22,22,&m_titleDC,21,35,SRCCOPY);
			}

			if(m_nMousePai == TITLE_GUO)
			{		
				m_memDC.BitBlt(710,444,26,26,&m_titleDC,108,54,SRCCOPY);
			}
			m_memDC.BitBlt(712,446,22,22,&m_titleDC,86,34,SRCCOPY);
		}
	}
	//ϵͳ��ʼʱ�Ŀ�ʼ��ť
	if(m_bStart)
	{
		m_memDC.BitBlt(370,400,55,28,&m_bgDC,370,400,SRCCOPY);
		if(m_nTitle == 3)
		{
			if(m_bHandDown)
			{
				m_memDC.BitBlt(370,400,55,28,&m_titleDC,112,127,SRCCOPY);
			}
			else
			{
				m_memDC.BitBlt(370,400,55,28,&m_titleDC,56,127,SRCCOPY);
			}
		}
		else
		{
			m_memDC.BitBlt(370,400,55,28,&m_titleDC,0,127,SRCCOPY);
		}
	}
	//ϵͳ����ʱ��ȷ����ť
	if(m_bOver)
	{
		m_memDC.BitBlt(220,130,370,311,&m_seziDC,0,99,SRCCOPY);		
		COLORREF rf = m_titleDC.GetPixel(113,101);
		ShowFenshu();
		if(m_nTitle == 4)	
		{
			if(m_bHandDown)
			{
				TransparentBlt(m_memDC.GetSafeHdc(),370,455,55,28,m_titleDC.GetSafeHdc(),112,100,55,28,rf);
			}
			else
			{
				TransparentBlt(m_memDC.GetSafeHdc(),370,455,55,28,m_titleDC.GetSafeHdc(),56,100,55,28,rf);
			}
		}
		else
		{
			TransparentBlt(m_memDC.GetSafeHdc(),370,455,55,28,m_titleDC.GetSafeHdc(),0,100,55,28,rf);
		}
	}
}

/*************************************************************/
/*�������ܣ�����ҵ�����
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::DrawPai()
{
	int i;	
	int* nPaiInhand[4],nStart[4];

	for( i = 0;i < 4;i++ )
	{
		nStart[i] = m_wjMaj[i].GetPaiStart();
		nPaiInhand[i] = m_wjMaj[i].GetPaiInHand();
	}
	DrawTitle();

	if(m_bOver || m_bZuobi)
	{	
		//�ұ���ҵ���
		m_memDC.BitBlt(680,105,31,323,&m_bgDC,680,110,SRCCOPY);
		if(m_wjMaj[1].GetState() == 1)
		{
			m_memDC.BitBlt(680,119,31,28,&m_paiDC,m_wjMaj[1].GetNewPai()*33+1,167,SRCCOPY);
		}
		for(i = 12;i >= 0;i--)
		{
			m_memDC.BitBlt(680,400-i*21,31,28,&m_paiDC,nPaiInhand[1][i]*33+1,167,SRCCOPY);
		}
		//��������ҵ�
		m_memDC.BitBlt(210,50,343,36,&m_bgDC,216,50,SRCCOPY);
		if(m_wjMaj[2].GetState() == 1)									//����ץ����
			m_memDC.BitBlt(222,50,23,35,&m_paiDC,m_wjMaj[2].GetNewPai()*24+1,197,SRCCOPY);
		for(i = 12;i >= 0;i--)
		{
			m_memDC.BitBlt(528-23*i,50,23,35,&m_paiDC,nPaiInhand[2][i]*24+1,197,SRCCOPY);
		}
		//�����ҵ���
		m_memDC.BitBlt(110,100,31,345,&m_bgDC,110,130,SRCCOPY);

		if(m_wjMaj[3].GetState() == 1)									//����ץ����
		{
			m_memDC.BitBlt(110,410,31,28,&m_paiDC,m_wjMaj[3].GetNewPai()*33+1,138,SRCCOPY);
		}
		for(i = 0;i < 13;i++)
		{
			m_memDC.BitBlt(110,130+i*21,31,28,&m_paiDC,nPaiInhand[3][i]*33+1,138,SRCCOPY);
		}
	}
	else
	{
		//�ұ���ҵ���
		m_memDC.BitBlt(680,105,31,323,&m_bgDC,680,110,SRCCOPY);
		if(m_wjMaj[1].GetState() == 1)
			m_memDC.BitBlt(680,105,15,39,&m_paiDC,35*45+19,1,SRCCOPY);
		if(nStart[1]>0)
		{
			for(i = 12;i >= nStart[1];i--)
			{
				m_memDC.BitBlt(680,383-i*21,15,39,&m_paiDC,35*45+1+18,1,SRCCOPY);
			}
			for(i = nStart[1]-1;i >= 0;i--)
			{
				m_memDC.BitBlt(680,400-i*21,31,28,&m_paiDC,nPaiInhand[1][i]*33+1,167,SRCCOPY);
			}
		}
		else
		{
			for(i = m_wjMaj[1].GetPaiStart();i < 13;i++)
			{
				m_memDC.BitBlt(680,130+i*21,15,39,&m_paiDC,35*45+1+18,1,SRCCOPY);
			}
		}
		//��������ҵ�
		m_memDC.BitBlt(210,50,343,36,&m_bgDC,216,50,SRCCOPY);
		if(m_wjMaj[2].GetState() == 1)									//����ץ����
		{
			m_memDC.BitBlt(213,50,24,36,&m_paiDC,34*24+1,196,SRCCOPY);
		}
		if(nStart[2] > 0)
		{
			for(i = 12;i >= nStart[2];i--)
			{
				m_memDC.BitBlt(528-24*i,50,24,36,&m_paiDC,34*24+1,196,SRCCOPY);	
			}
			for(i = nStart[2]-1;i >= 0;i--)
			{
				m_memDC.BitBlt(528-23*i,50,23,35,&m_paiDC,nPaiInhand[2][i]*24,197,SRCCOPY);
			}
		}
		else
		{
			for(i = 0;i < 13;i++)
			{
				m_memDC.BitBlt(240+24*i,50,24,36,&m_paiDC,34*24+1,196,SRCCOPY);
			}
		}
		//�����ҵ���
		m_memDC.BitBlt(110,100,31,345,&m_bgDC,110,130,SRCCOPY);
		for(i = 0;i < nStart[3];i++)
		{
			m_memDC.BitBlt(110,130+i*21,31,28,&m_paiDC,nPaiInhand[3][i]*33+1,138,SRCCOPY);
		}
		for(i = nStart[3];i < 13;i++)
		{
			m_memDC.BitBlt(110,130+i*21,15,39,&m_paiDC,35*45+2,1,SRCCOPY);
		}
		if(m_wjMaj[3].GetState() == 1)
		{
			m_memDC.BitBlt(110,133+i*21,15,39,&m_paiDC,35*45+2,1,SRCCOPY);
		}
	}
	//�ұ���ҵĸ���
	for(i=0;i<4;i++)
	{
		if(m_wjMaj[1].GetGangPai()[i] != 0)
		{
			if(m_wjMaj[1].GetGangPai()[i] == 1)
			{
				m_memDC.BitBlt(680,396-(3*i+1)*21,31,28,&m_paiDC,nPaiInhand[1][3*i]*33,167,SRCCOPY);
			}
			else
			{
				m_memDC.BitBlt(680,396-(3*i+1)*21,31,28,&m_paiDC,34*33,167,SRCCOPY);
			}
		}
	}
	//������ҵĸ���
	for(i=0;i<4;i++)
	{
		if(m_wjMaj[2].GetGangPai()[i] != 0)
		{
			if(m_wjMaj[2].GetGangPai()[i] == 1)
			{
				m_memDC.BitBlt(528-23*(3*i+1),45,23,35,&m_paiDC,nPaiInhand[2][3*i]*24,197,SRCCOPY);
			}
			else
			{
				m_memDC.BitBlt(528-23*(3*i+1),45,23,35,&m_paiDC,35*24+1,197,SRCCOPY);
			}
		}
	}
	//������ҵĸ���
	for(i=0;i<4;i++)
	{
		if(m_wjMaj[3].GetGangPai()[i] != 0)
		{
			if(m_wjMaj[3].GetGangPai()[i] == 1)
			{
				m_memDC.BitBlt(110,125+(3*i+1)*21,31,28,&m_paiDC,nPaiInhand[3][3*i]*33+1,138,SRCCOPY);
			}
			else
			{
				m_memDC.BitBlt(110,125+(3*i+1)*21,31,28,&m_paiDC,34*33,138,SRCCOPY);
			}
		}
	}
}

/*************************************************************/
/*�������ܣ�����ǽ
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::DrawPaiQiang()
{
	int i,j;
	int nPaiqiang[4][34];
	int* nP[4];
	for( i = 0;i < 4;i++ )
		nP[i]=nPaiqiang[i];
	m_zmMaj.GetPaiqiang(nP);

	//������ǰ����ǽ
	m_memDC.BitBlt(251,430,320,33,&m_bgDC,251,430,SRCCOPY);
	for( i = 0,j = 0;j < 34;j = j+2,i++ )
	{	
		if( nPaiqiang[0][j+1] != -1 )
		{
			m_memDC.BitBlt(540-17*i,435,17,28,&m_paiDC,35*24+2,234,SRCCOPY);
		}
		if( nPaiqiang[0][j] != -1 )
		{
			m_memDC.BitBlt(540-17*i,430,17,28,&m_paiDC,35*24+2,234,SRCCOPY);
		}
	}
	//������ҵ���ǽ
	m_memDC.BitBlt(270,105,340,40,&m_bgDC,270,105,SRCCOPY);
	for( i = 0,j = 0;j < 34;j = j+2,i++ )
	{	
		if(nPaiqiang[2][j+1] != -1)
		{
			m_memDC.BitBlt(270+17*i,110,17,28,&m_paiDC,35*24+2,234,SRCCOPY);
		}
		if( nPaiqiang[2][j] != -1 )
		{
			m_memDC.BitBlt(270+17*i,105,17,28,&m_paiDC,35*24+2,234,SRCCOPY);
		}
	}
	//�����ҵ���ǽ
	m_memDC.BitBlt(170,155,24,250,&m_bgDC,170,155,SRCCOPY);
	for( i = 0,j = 33;j >= 0;j = j-2,i++ )
	{
		if(nPaiqiang[3][j] != -1)
		{
			m_memDC.BitBlt(170,160+14*i,24,19,&m_paiDC,34*24+1,233,SRCCOPY);
		}
		if(nPaiqiang[3][j-1] != -1)
		{
			m_memDC.BitBlt(170,155+14*i,24,19,&m_paiDC,34*24+1,233,SRCCOPY);
		}
	}
	//�ұ���ҵ���ǽ
	m_memDC.BitBlt(620,155,24,280,&m_bgDC,620,155,SRCCOPY);
	for(i = 0,j = 0;j < 34;j = j+2,i++)
	{
		if(nPaiqiang[1][j+1] != -1)
		{
			m_memDC.BitBlt(620,160+14*i,24,19,&m_paiDC,34*24+1,233,SRCCOPY);
		}
		if(nPaiqiang[1][j] != -1)
		{
			m_memDC.BitBlt(620,155+14*i,24,19,&m_paiDC,34*24+1,233,SRCCOPY);
		}
	}
}

/*************************************************************/
/*�������ܣ�������ҳ�����
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::DrawPaiOut()
{
	int i;
	int* nOutPai[4];
	for(i = 0;i < 4;i++)
	{
		nOutPai[i] = m_wjMaj[i].GetOutPai();
	}

	m_memDC.BitBlt(257,390,230,35,&m_bgDC,257,390,SRCCOPY);
	m_memDC.BitBlt(280,363,184,35,&m_bgDC,280,363,SRCCOPY);
	m_memDC.BitBlt(303,336,184,35,&m_bgDC,303,336,SRCCOPY);

	//���˳�����
	if(m_wjMaj[0].GetOutNum() > 10)
	{
		if(m_wjMaj[0].GetOutNum() > 18)
		{	
			for( i = 18;i < m_wjMaj[0].GetOutNum();i++ )
			{
				m_memDC.BitBlt(303+23*(i-18),336,23,35,&m_paiDC,(nOutPai[0][i])*24+1,234,SRCCOPY);
			}
			for(i = 10;i < 18;i++)
			{
				m_memDC.BitBlt(280+23*(i-10),363,23,35,&m_paiDC,(nOutPai[0][i])*24+1,234,SRCCOPY);
			}
			for(i = 0;i < 10;i++)
			{
				m_memDC.BitBlt(257+23*i,390,23,35,&m_paiDC,(nOutPai[0][i])*24+1,234,SRCCOPY);
			}
		}
		else
		{
			for(i = 10;i < m_wjMaj[0].GetOutNum();i++)
			{
				m_memDC.BitBlt(280+23*(i-10),363,23,35,&m_paiDC,(nOutPai[0][i])*24+1,234,SRCCOPY);
			}
			for(i = 0;i < 10;i++)
			{
				m_memDC.BitBlt(257+23*i,390,23,35,&m_paiDC,(nOutPai[0][i])*24+1,234,SRCCOPY);
			}
		}
	}
	else
	{
		for(i = 0;i < m_wjMaj[0].GetOutNum();i++)
		{
			m_memDC.BitBlt(257+23*i,390,23,35,&m_paiDC,(nOutPai[0][i])*24+1,234,SRCCOPY);
		}
	}
		
	//�ұ���ҳ�����
	int nI = m_wjMaj[1].GetOutNum(),j;
	if(nI<11)
	{
		m_memDC.BitBlt(565,210,31,200,&m_bgDC,565,200,SRCCOPY);
		for(i = nI-1,j = 0;i >= 0;i--,j++)
		{
			m_memDC.BitBlt(565,400-nI*19+19*j,31,27,&m_paiDC,(nOutPai[1][i])*33+1,168,SRCCOPY);
		}
	}
	else
	{
		if(nI < 19)
		{
			m_memDC.BitBlt(534,210,31,200,&m_bgDC,534,210,SRCCOPY);
			for(i = nI-11,j = 0;i >= 0;i--,j++)
			{
				m_memDC.BitBlt(534,363-(nI-11)*19+19*j,31,27,&m_paiDC,(nOutPai[1][i+10])*33+1,168,SRCCOPY);
			}
		}
		else
		{
			m_memDC.BitBlt(503,220,31,150,&m_bgDC,503,220,SRCCOPY);
			for(i = nI-18,j = 0;i >= 0;i--,j++)
			{
				m_memDC.BitBlt(503,333-(nI-19)*19+19*j,31,27,&m_paiDC,(nOutPai[1][i+18])*33+1,168,SRCCOPY);
			}
		}
	}
		
	//�����ҳ�����
	nI = m_wjMaj[3].GetOutNum();
	m_memDC.BitBlt(215,170,31,20*10+7,&m_bgDC,215,170,SRCCOPY);
	m_memDC.BitBlt(246,190,31,20*8+7,&m_bgDC,246,190,SRCCOPY);
	m_memDC.BitBlt(277,210,31,20*6+7,&m_bgDC,277,210,SRCCOPY);
	for(i=0;i<nI;i++)
	{
		if(i < 10)
		{
			m_memDC.BitBlt(215,170+20*i,31,27,&m_paiDC,(nOutPai[3][i])*33+1,138,SRCCOPY);
		}
		else if(i < 18)
		{
			m_memDC.BitBlt(246,190+20*(i-10),31,27,&m_paiDC,(nOutPai[3][i])*33+1,138,SRCCOPY);
		}
		else
		{
			m_memDC.BitBlt(277,210+20*(i-18),31,27,&m_paiDC,(nOutPai[3][i])*33+1,138,SRCCOPY);
		}
	}
	
	//������ҳ�����
	nI=m_wjMaj[2].GetOutNum();
	m_memDC.BitBlt(320,150,260,35,&m_bgDC,320,150,SRCCOPY);
	m_memDC.BitBlt(340,175,184,35,&m_bgDC,340,175,SRCCOPY);
	m_memDC.BitBlt(360,200,138,35,&m_bgDC,360,200,SRCCOPY);
	for(i = 0;i < nI;i++)
	{
		if(i < 10)
		{
			m_memDC.BitBlt(550-23*i,150,23,35,&m_paiDC,(nOutPai[2][i])*24+1,197,SRCCOPY);
		}
		else if(i < 18)
		{
			m_memDC.BitBlt(550-23*(i-9),175,23,35,&m_paiDC,(nOutPai[2][i])*24+1,197,SRCCOPY);
		}
		else
		{
			m_memDC.BitBlt(550-23*(i-17),200,23,35,&m_paiDC,(nOutPai[2][i])*24+1,197,SRCCOPY);
		}
	}
		
}

/*************************************************************/
/*�������ܣ���ѡ��״̬�µ�С���ͷ
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::DrawSelect()
{
	int i;
	if(!m_bSelect)
	{
		m_memDC.BitBlt(100,485,602,11,&m_bgDC,100,485,SRCCOPY);
		return;
	}
	//��ѡ��״̬�����ϵļ�ͷ
	if(m_wjMaj[0].GetState() == 1)
	{
		int pos;
		for(i = 0;i < m_arrGang.GetSize();i++)
		{
			if(m_wjMaj[0].GetNewPai() == (int)m_arrGang.GetAt(i))
			{
				TransparentBlt(m_memDC.GetSafeHdc(),670+12,485, 15,11,m_titleDC.GetSafeHdc(),108,34,15,11,RGB(255,255,255));
			}
			else
			{
				pos =  m_wjMaj[0].FindPaiPos(m_arrGang.GetAt(i),m_wjMaj[0].GetPaiStart());
				TransparentBlt(m_memDC.GetSafeHdc(),100+pos*43+15,485, 15,11,m_titleDC.GetSafeHdc(),108,34,15,11,RGB(255,255,255));
			}
		}
	}
	else
	{
		if(m_arrEat.GetSize() > 2)
		{
			for(i = 0;i < m_arrEat.GetSize();i++)
			{
				TransparentBlt(m_memDC.GetSafeHdc(),115+m_arrEat.GetAt(i)*43,475, 15,11,m_titleDC.GetSafeHdc(),108,34,15,11,RGB(255,255,255));
			}
		}
	}
}

/*************************************************************/
/*�������ܣ������˵��ƺ���������״̬
/*��ڲ����������е���
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::DrawPaiUp(int nPai)
{	int i;
	m_memDC.BitBlt(100,475,620,78,&m_bgDC,100,475,SRCCOPY);		//���˵���
	//�Ƿ����
	if(m_bOver)
	{
		for(i = 0;i < 13;i++)
		{
			m_memDC.BitBlt(100+43*i,487,43,66,&m_paiDC,m_wjMaj[0].GetPaiInHand()[i]*45+1,71,SRCCOPY);
		}
		if(m_wjMaj[0].GetState() == 1)
		{
			m_memDC.BitBlt(670,487,43,66,&m_paiDC,m_wjMaj[0].GetNewPai()*45+1,71,SRCCOPY);
		}
	}
	else
	{
		for(i = 0;i < m_wjMaj[0].GetPaiStart();i++)
		{
			m_memDC.BitBlt(100+43*i,487,43,66,&m_paiDC,m_wjMaj[0].GetPaiInHand()[i]*45+1,71,SRCCOPY);
		}
		for(i = m_wjMaj[0].GetPaiStart();i < 13;i++)
		{
			m_memDC.BitBlt(100+43*i,485,43,68,&m_paiDC,m_wjMaj[0].GetPaiInHand()[i]*45+1,1,SRCCOPY);
		}
		if(m_wjMaj[0].GetState() == 1)
		{
			m_memDC.BitBlt(670,485,43,68,&m_paiDC,m_wjMaj[0].GetNewPai()*45+1,1,SRCCOPY);
		}
	}
	//����
	for(i = 0;i < 4;i++)
	{
		if(m_wjMaj[0].GetGangPai()[i] != 0)
		{
			if(m_wjMaj[0].GetGangPai()[i] == 1)
			{
				m_memDC.BitBlt(100+43*(3*i+1),477,43,66,&m_paiDC,m_wjMaj[0].GetPaiInHand()[3*i]*45+1,71,SRCCOPY);
			}
			else
			{
				m_memDC.BitBlt(100+43*(3*i+1),477,43,66,&m_paiDC,34*45+1,72,SRCCOPY);
			}
		}
	}
	//ѡ��״̬�µ���ֻ�и�����������
	if(m_bSelect)
	{
		if(m_wjMaj[0].GetState() == 1)
		{
			int pos;
			for(i=0;i<m_arrGang.GetSize();i++)
			{
				if(m_wjMaj[0].GetNewPai() == (int)m_arrGang.GetAt(i))
				{
					pos = 14;
				}
				else
				{
					pos = m_wjMaj[0].FindPaiPos(m_arrGang.GetAt(i),m_wjMaj[0].GetPaiStart());
				}
				if(nPai == pos)
				{
					DrawUpPai(pos);
					m_nSelectGang = (int)m_arrGang.GetAt(i);
					break;
				}
				else 
				{
					m_nSelectGang = -1;
				}
			}	
		}
		else
		{
			for(i = 0;i < (int)m_arrEat.GetSize()/2;i++)
			{
				if(nPai == (int)m_arrEat.GetAt(2*i) || nPai == (int)m_arrEat.GetAt(2*i+1))
				{
					DrawUpPai((int)m_arrEat.GetAt(2*i));
					DrawUpPai((int)m_arrEat.GetAt(2*i+1));			
					m_nSelectEat = m_wjMaj[0].GetPaiInHand()[(int)m_arrEat.GetAt(2*i)];
					break;
				}
				else
				{
					m_nSelectEat = -1;
				}

			}
		}
		DrawSelect();
		return;
	}
	DrawUpPai(nPai);
}

/*************************************************************/
/*�������ܣ�������һ��������
/*��ڲ��������ͣ�Ҫ�������Ƶ�λ�ã�
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::DrawUpPai(int nPlace)
{
	if( nPlace == 14 )
	{
		m_memDC.BitBlt(670,485, 43,68,&m_bgDC,670,485,SRCCOPY);
		if( m_wjMaj[0].GetPaiInHand()[13] != -1 )
		{
			m_memDC.BitBlt(670,475, 43,68,&m_paiDC,(m_wjMaj[0].GetNewPai())*45+1,1,SRCCOPY);
		}
	}
	else if(nPlace >= 0 && nPlace < 14)
	{
		m_memDC.BitBlt(100+nPlace*43,485, 43,68,&m_bgDC,100+nPlace*43,485,SRCCOPY);
		m_memDC.BitBlt(100+nPlace*43,475, 43,68,&m_paiDC,(m_wjMaj[0].GetPaiInHand()[nPlace])*45+1,1,SRCCOPY);
	}
}


/*************************************************************/
/*�������ܣ��������ҵ���
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::SortWjPai()
{
	for(int i = 0;i < 4;i++)
	{
		m_wjMaj[i].SortPai();
	}
}

/*************************************************************/
/*�������ܣ�����Ƿ�����
/*��ڲ�������
/*�������ͣ�����
/*************************************************************/
bool CMahjongDlg::CheckLiuju()
{
	//��������ϵ���ʣ�²���10�ž�����
	if(m_zmMaj.GetMajNum() <= 10)
	{
		PlayOtherSound(S_LIU);
		m_nHuWho = 0;
		m_nHuType = 4;
		m_bOver = true;
		m_bRun = false;
		DrawAllpai();
		ShowFenshu();
		UpdateFrame();
		KillTimer(1);
		return true;
	}
	else
	{
		return false;
	}
}


void CMahjongDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default	

	switch(nIDEvent)
	{
	case 1:
		{
			if(m_bRun&&!m_bwjState&&!m_bSelect)
			{
				//����г��ƵĻ��������Ƹ�˭Ҫ
				if(m_nOutPai!=-1)
				{
					//��ø���ҵķ���
					static bool blTemp=false;
					if(!blTemp && m_nChupaiUser == 0)
					{
						blTemp = true;
						return;
					}
					blTemp = false;
					CheckWhoGet();
					//����û������Ͱ��û��ķ�������
					if(m_nAbandon)
					{
						m_nAbandon = false;
						m_nGoodScore[0] = m_nChupaiUser;
					}
					//��˭�÷����
					int nWho,nMax;
					nWho = GetMaxWho(nMax);
					m_nActive = nWho;
					//����û��л�������Ⱦ����û�ѡ���Ƿ�
					if(0 == nWho&&nMax >= 100)
					{
						m_bwjState = true;
						DrawTitle();
						UpdateFrame();
						SetTimer(3,1000,NULL);
						OnTimer(3);
						return;
					}
				}
				switch(m_nActive)
				{
				case 0:
					{
						//����û�״̬�ǳ��Ʋ��Ǿ�ץһ����
						if(m_wjMaj[0].GetState() != 1)
						{
							if(CheckLiuju()) return;
							sndPlaySound("Sounds\\draw.wav",SND_ASYNC|SND_NODEFAULT);
							m_wjMaj[0].SetNewPai(m_zmMaj.GetPai());
							CheckPerson();
							DrawTitle();
							m_nActive = 0;
							m_nOutPai = -1;
							DrawAllpai();
							UpdateFrame();
						}
						else
						{
							//����Ͱ��ȴ�ʱ��ݼ�
							m_nWaitTime--;
							if(m_nWaitTime < TimeSelect/2)
							{
								sndPlaySound("Sounds\\hurry.wav",SND_ASYNC|SND_NODEFAULT);
							}
							//����ȴ�ʱ��������Զ���һ����
							if(m_nWaitTime < 0)
							{		
								m_nOutPai = m_wjMaj[0].GetNewPai();
								m_wjMaj[0].OutPai(14);
								m_nChupaiUser = 0;
								m_nOutPai = m_wjMaj[0].GetOutPai()[m_wjMaj[0].GetOutNum()-1];	
								m_nActive = 1;
								PlayPaiSound(m_nOutPai);
								DrawAllpai();
								UpdateFrame();
								m_nWaitTime = TimeSelect;
								return;
							}
							UpdateFrame();
						}
						break;
					}
				case 1:
					{
						CmpActive(1);
					}
					break;
				case 2:
					{
						CmpActive(2);
					}
					break;
				case 3:
					{
						CmpActive(3);
					}
					break;
				}
			}
		}
		break;
	case 2:
		{
			DrawSezi();
		}
		break;
	case 3:
		{
			//ѡ��ʱ���������
			if(m_bwjState)
			{
				m_nSelectTime = m_nSelectTime-1;
				//ʱ�䵽һ����ʾ
				if(m_nSelectTime < TimeSelect/2)
				{
					sndPlaySound("Sounds\\hurry.wav",SND_ASYNC|SND_NODEFAULT);
				}
				//ʱ�������Զ�����
				if(m_nSelectTime < 0)
				{	
					m_bwjState = false;
					m_nAbandon = true;
					m_nSelectTime = TimeSelect;
					OnTimer(1);
					KillTimer(3);
				}
				UpdateFrame();
			}
		}
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

/*************************************************************/
/*�������ܣ���ɫ�ӹ����Ķ���
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void  CMahjongDlg::DrawSezi()
{
	if(m_bCaton)
	{
		static bool bRuff = false;
		//ϴ��һ��
		if(!bRuff)
		{
			sndPlaySound("Sounds\\deal.wav",SND_ASYNC|SND_NODEFAULT);
			m_zmMaj.Ruffle();
			m_zmMaj.SortMaj();
			bRuff = true;	
			m_memDC.BitBlt(0,0,800,600,&m_bgDC,0,0,SRCCOPY);		
			DrawPaiQiang();
			UpdateFrame();
		}
		static CPoint pt(0,0);
		COLORREF rf = m_seziDC.GetPixel(1,1);
		m_memDC.BitBlt(0,0,800,600,&m_bgDC,0,0,SRCCOPY);		
		DrawPaiQiang();
		//����ɫ�ӵ�ת��
		TransparentBlt(m_memDC.GetSafeHdc(),380,260,32,33,m_seziDC.GetSafeHdc(),pt.x+32,pt.y,32,33,rf);
		TransparentBlt(m_memDC.GetSafeHdc(),410,250,32,33,m_seziDC.GetSafeHdc(),pt.x,pt.y,32,33,rf);
		UpdateFrame();
		pt.x += 32;
		if(pt.x >= 256)
		{
			pt.y += 33;
			if(pt.y >= 66)
			{
				pt.x = 0;
				pt.y = 0;
			}
		}
		static int nTemp = 0;
		nTemp += 1;
		//ת����Ϳ�ʼ
		if(nTemp >= TimeSezi)
		{
			nTemp = 0;
			srand((unsigned)time(NULL));
			int nFirst,nSecond;
			//�漴��������ɫ����
			nFirst = rand()%6;
			nSecond = rand()%6;
			SetSezi(nFirst+nSecond+2);
			m_memDC.BitBlt(0,0,800,600,&m_bgDC,0,0,SRCCOPY);		
			DrawPaiQiang();
			TransparentBlt(m_memDC.GetSafeHdc(),380,260,32,33,m_seziDC.GetSafeHdc(),nFirst*32,66,32,33,rf);
			TransparentBlt(m_memDC.GetSafeHdc(),410,250,32,33,m_seziDC.GetSafeHdc(),nSecond*32,66,32,33,rf);
			UpdateFrame();
			Sleep(1000);
			m_bRun = true;
			bRuff = false;
			SetPai();
			m_bCaton = false;
		}
	}
}

/*************************************************************/
/*�������ܣ�ͳ�Ʒ���
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void  CMahjongDlg::CountFenshu()
{	
	int nGet,nRemove;
	switch(m_nHuType)
	{
	case 1:
		nGet = 150;
		nRemove = -50;
		break;
	case 2:
		nGet = 300;
		nRemove = -100;
		break;
	case 3:
		nGet = 450;
		nRemove = -150;
		break;
	}
	//���ݺ���ͳ�Ʒ���
	for(int i = 0;i<4;i++)
	{
		if(i == m_nHuWho)
		{
			m_wjMaj[i].SetFenshu(nGet);
		}
		else
		{
			m_wjMaj[i].SetFenshu(nRemove);
		}
	}
}

/*************************************************************/
/*�������ܣ�����Ե���Ϊ
/*��ڲ��������ͣ����Ǽҵ��ԣ�
/*�������ͣ�void
/*************************************************************/
void  CMahjongDlg::CmpActive(int nWho)
{
	if(m_wjMaj[nWho].GetState() == 1)
	{
		int ret;
		ret = CmpThink(nWho);
		if(ret == 1000)				//��������
		{
			m_nHuWho=nWho;
			m_nHuType = 2;
			m_nMousePai = -1;
			CountFenshu();
			m_bOver = true;
			m_bRun = false;
			m_nZhuang=(m_nZhuang+1)%4;
			KillTimer(1);
			m_nOutPai = -1;
			PlayOtherSound(S_HU,m_wjMaj[nWho].GetSex());
			Sleep(200);
			sndPlaySound("Sounds\\countfan.wav",SND_ASYNC|SND_NODEFAULT);
			DrawPai();
			DrawPaiOut();
			DrawPaiUp(m_nMousePai);
			DrawTitle();
		}
		else if(ret < 0)			//�������Ը�
		{
			PlayOtherSound(S_GAN,m_wjMaj[nWho].GetSex());
			m_wjMaj[nWho].SetGang(ret+100);
			m_wjMaj[nWho].SetNewPai(m_zmMaj.GetGangPai());
			m_nActive=nWho;
			DrawPai();
			DrawPaiQiang();
		}
		else if(ret >= 0 && ret <= 34)
		{
			m_wjMaj[nWho].CmpOutPai(ret);//���Գ���	
			m_nChupaiUser = nWho;	
			m_nOutPai = ret;
			sndPlaySound("Sounds\\give.wav",SND_ASYNC|SND_NODEFAULT);
			//Sleep(100);
			PlayPaiSound(m_nOutPai,m_wjMaj[nWho].GetSex());
			DrawPai();
			DrawPaiOut();
		}
	}
	else
	{
		if(m_nGoodScore[nWho] >= 1000)	//���˷�����
		{
			m_nHuWho = nWho;
			m_nHuType = 1;
			m_nMousePai = -1;
			CountFenshu();
			m_wjMaj[nWho].SetNewPai(m_nOutPai);
			m_wjMaj[m_nChupaiUser].RemoveOutPai();
			m_bOver = true;
			m_bRun = false;
			m_nZhuang = (m_nZhuang+1)%4;
			KillTimer(1);
			PlayOtherSound(S_HU,m_wjMaj[nWho].GetSex());
			Sleep(200);
			sndPlaySound("Sounds\\countfan.wav",SND_ASYNC|SND_NODEFAULT);
			DrawAllpai();
			DrawTitle();
		}
		else if(m_nGoodScore[nWho] >= 800)	//��
		{
			PlayOtherSound(S_GAN,m_wjMaj[nWho].GetSex());
			m_wjMaj[nWho].SetGang(m_nOutPai);
			m_wjMaj[nWho].SetNewPai(m_zmMaj.GetGangPai());
			m_wjMaj[m_nChupaiUser].RemoveOutPai();
			m_nOutPai = -1;
			m_nActive = nWho;
			DrawAllpai();
		}
		else if(m_nGoodScore[nWho] >= 500)	//��
		{	
			PlayOtherSound(S_PEN,m_wjMaj[nWho].GetSex());
			m_wjMaj[nWho].SetPeng();			
			m_wjMaj[m_nChupaiUser].RemoveOutPai();
			m_nOutPai = -1;
			m_nActive = nWho;
			DrawAllpai();
		}
		else if(m_nGoodScore[nWho] >= 100)	//��
		{	
			PlayOtherSound(S_EAT,m_wjMaj[nWho].GetSex());					
			m_wjMaj[m_nChupaiUser].RemoveOutPai();
			m_nOutPai = -1;
			//�������ֳԷ�
			if(m_nGoodScore[nWho] >= 300)
			{
				m_wjMaj[nWho].SetChi(2);
			}
			else if(m_nGoodScore[nWho] >= 200)
			{
				m_wjMaj[nWho].SetChi(1);
			}
			else
			{
				m_wjMaj[nWho].SetChi(0);
			}
			m_nActive = nWho;
			DrawAllpai();
		}
		if(m_nGoodScore[nWho] < 100)		//�����Ǿ�ץ��
		{
			if(CheckLiuju()) return;
			sndPlaySound("Sounds\\draw.wav",SND_ASYNC|SND_NODEFAULT);
			m_wjMaj[nWho].SetNewPai(m_zmMaj.GetPai());
			m_nActive = nWho;
			CheckPerson();
			m_nOutPai = -1;
			DrawPaiQiang();
			DrawPai();
		}
	}
	UpdateFrame();	
	return;
}

/*************************************************************/
/*�������ܣ��������������Һͷ���
/*��ڲ������������ã���������
/*�������ͣ����ͣ���ң�
/*************************************************************/
int CMahjongDlg::GetMaxWho(int& nMaxScore)
{
	nMaxScore = 0;
	int nMaxWho;
	//��������� 
	for(int i = 0;i < 4;i++)
	{
		if(i != m_nChupaiUser)
		{
			if(m_nGoodScore[i] > nMaxScore)
			{
				nMaxWho = i;
				nMaxScore = m_nGoodScore[i];
			}
		}
	}
	return nMaxWho;
}

/*************************************************************/
/*�������ܣ���Ȿ�˵�״̬
/*��ڲ�������
/*�������ͣ�����
/*************************************************************/
bool CMahjongDlg::CheckPerson()
{
	ChangBoolFalse();
	m_wjMaj[0].SetOutPai(m_nOutPai);
	m_bHu = m_wjMaj[0].ThinkHupai();
	//���û��Ƿ���Գ�
	if(m_nChupaiUser == 3)
	{
		m_bChi = m_wjMaj[0].CheckEat(m_arrEat);
	}
	//���û��Ƿ���Ըܺ���
	if(m_wjMaj[0].GetState() == 1)
	{
		m_bGang = m_wjMaj[0].CheckGangSelf(m_arrGang);
	}
	else
	{
		m_bGang = m_wjMaj[0].CheckGang(m_bPeng);
	}
	return (m_bChi||m_bHu||m_bPeng||m_bGang);
}

/*************************************************************/
/*�������ܣ�����ڱ������ƶ�
/*��ڲ���������
/*�������ͣ�boid
/*************************************************************/
void CMahjongDlg::MoveTitle(CPoint point)
{
	bool blFind=false;
	CRect rt;
	//�û�����Ƿ��ƶ������Ͻǵ�Сͼ����
	if(m_rtTitle[7].PtInRect(point))
	{
		if(m_nMousePai == TITLE_SET)
		{
			return;
		}
		else
		{
			m_nMousePai = TITLE_SET;
			blFind = true;
		}
	}
	if(m_rtTitle[6].PtInRect(point))
	{
		if(m_nMousePai == TITLE_CLOSE)
		{
			return;
		}
		else
		{
			m_nMousePai = TITLE_CLOSE;
			blFind = true;
		}
	}
	if(m_rtTitle[5].PtInRect(point))
	{
		if(m_nMousePai == TITLE_MIN)
		{
			return;
		}
		else
		{
			m_nMousePai = TITLE_MIN;
			blFind = true;
		}
	}
	if(m_bRun && !blFind)
	{
		//�Ƿ��ƶ����ܳԵ�ͼ����
		if(m_bGang)
		{
			if(m_rtTitle[2].PtInRect(point))
			{
				if(m_nMousePai == TITLE_GANG)
				{
					return;
				}
				else
				{
					m_nMousePai = TITLE_GANG;
					blFind = true;
				}
			}
		}		
		if(m_bHu)
		{
			if(m_rtTitle[3].PtInRect(point))
			{
				if(m_nMousePai == TITLE_HU)
				{
					return;
				}
				else
				{
					m_nMousePai = TITLE_HU;
					blFind = true;
				}
			}
		}
		if(m_bChi)
		{
			if(m_rtTitle[0].PtInRect(point))
			{
				if(m_nMousePai == TITLE_EAT)
				{
					return;
				}
				else
				{
					m_nMousePai = TITLE_EAT;
					blFind=true;
				}
			}
		}
		if(m_bPeng)
		{
			if(m_rtTitle[1].PtInRect(point))
			{
				if(m_nMousePai == TITLE_PENG)
				{
					return;
				}
				else
				{
					m_nMousePai = TITLE_PENG;
					blFind=true;
				}
			}
		}

		if(m_rtTitle[4].PtInRect(point))
		{
			if(m_nMousePai == TITLE_GUO)
			{
				return;
			}
			else
			{
				m_nMousePai = TITLE_GUO;
				blFind=true;
			}
		}

		rt.SetRect(100,485,713,68+485);
		//�Ƿ��ƶ�������ȥ��
		if(rt.PtInRect(point) && !blFind)
		{
			for( int i = m_wjMaj[0].GetPaiStart();i < 13;i++ )
			{
				rt.SetRect(100+i*43,485,100+i*43+43,68+485 );
				if( rt.PtInRect(point) )
				{
					m_nMousePai = i;
					blFind = true;
				}
			}
			rt.SetRect(670,485,713,68+485);
			if(rt.PtInRect(point)&&m_wjMaj[0].GetState() == 1)
			{
				m_nMousePai = 14;
				blFind = true;
			}
		}
	}	
	if(!blFind)
	{
		m_nMousePai = -1;
	}
	DrawTitle();
	if(m_bRun)
	{
		DrawPaiUp(m_nMousePai);
	}
	if(m_nFirst == m_nMousePai) 
	{
		return;
	}
	UpdateFrame();	
	m_nFirst = m_nMousePai;
}


void CMahjongDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//����ǷŶ�����ֱ���˳�
	if(m_bCaton)
		return;
	MoveTitle(point);

	CRect rt;	
	//��ʼ
	if(m_bStart)
	{
		rt.SetRect(370,400,425,428);
		if(rt.PtInRect(point))
		{
			m_nTitle = 3;
			DrawTitle();
			UpdateFrame();
			return;
		}
		m_nTitle = -1;
		DrawTitle();
		UpdateFrame();
	}
	//����
	if(m_bOver)
	{
		rt.SetRect(370,450,425,478);
		if(rt.PtInRect(point))
		{
			m_nTitle = 4;
			DrawTitle();
			Invalidate(false);
			return;
		}
		m_nTitle = -1;
		DrawTitle();
		Invalidate(false);
	}

	CDialog::OnMouseMove(nFlags, point);
}

BOOL CMahjongDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	//�������
	if(m_bStart || m_bOver)
	{
		if(m_nTitle == 3||m_nTitle == 4)
		{
			SetCursor(m_hCursorHand);
		}
		else
		{
			SetCursor(m_hCursor);
		}
	}
	else
	{
		if(m_nMousePai < 0 || m_nMousePai >= 100)
		{
			SetCursor(m_hCursor);
		}
		else
		{
			SetCursor(m_hCursorHand);
		}
	}
	return TRUE;
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

/*************************************************************/
/*�������ܣ�����ڱ����ϵ��
/*��ڲ���������
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::OnClickTitle(CPoint point)
{
	//�������˱����е�һ��
	if((m_nMousePai == TITLE_PENG)||(m_nMousePai == TITLE_EAT)
		||(m_nMousePai == TITLE_GANG)||(m_nMousePai == TITLE_HU)||(m_nMousePai == TITLE_GUO))
	{
		ChangBoolFalse();
		m_nSelectTime = TimeSelect;
		DrawTitle();
		UpdateFrame();
	}
	if(m_nMousePai == TITLE_GANG)
	{	
		if(m_wjMaj[0].GetState() != 1)	//���˴��Ƶĸ�
		{
			m_bwjState = false;
			m_wjMaj[m_nChupaiUser].RemoveOutPai();
			m_wjMaj[0].SetGang(m_nOutPai);
			PlayOtherSound(S_GAN,m_wjMaj[0].GetSex());
			m_nActive = 0;
			m_nOutPai = -1;
			m_wjMaj[0].SetNewPai(m_zmMaj.GetGangPai());
			CheckPerson();
			DrawAllpai();
			UpdateFrame();
			OnTimer(1);
		}
		else
		{
			if(m_arrGang.GetSize() == 1)
			{
				m_bwjState = false;
				m_wjMaj[0].SetGang(m_arrGang.GetAt(0));	
				PlayOtherSound(S_GAN,m_wjMaj[0].GetSex());
				m_nActive = 0;
				m_wjMaj[0].SetNewPai(m_zmMaj.GetGangPai());
				CheckPerson();
				DrawAllpai();
				UpdateFrame();
				OnTimer(1);
			}
			else
			{
				m_bwjState = false;
				m_nActive = 0;
				m_bSelect = true;
				DrawTitle();
				UpdateFrame();
			}
		}
	}
	//��Һ���
	if(m_nMousePai == TITLE_HU)
	{
		m_bwjState = false;
		PlayOtherSound(S_HU,m_wjMaj[0].GetSex());
		Sleep(200);
		sndPlaySound("Sounds\\countfan.wav",SND_ASYNC|SND_NODEFAULT);
		m_nHuWho = 0;
		if(m_nOutPai == -1)
			m_nHuType = 2;
		else
		{
			m_nHuType = 1;
			m_wjMaj[m_nChupaiUser].RemoveOutPai();
			m_wjMaj[0].SetNewPai(m_nOutPai);
		}
		CountFenshu();
		m_bOver = true;
		m_bRun = false;
		m_nOutPai = -1;
		m_nZhuang = (m_nZhuang+1)%4;
		DrawAllpai();
		ShowFenshu();
		UpdateFrame();
		KillTimer(1);
	}
	//��ҵĵȴ�ѡ��״̬�µ������ر���
	if(m_bwjState)
	{
		if(m_nMousePai == TITLE_EAT)
		{
			m_bwjState = false;
			//���Ƿ�ֻ��һ�Կ��Գԣ��Ǿ�ֱ�ӳ�
			if(m_arrEat.GetSize() == 2)
			{
				int nType;
				if( m_wjMaj[0].GetPaiInHand()[(int)m_arrEat.GetAt(0)] == (m_nOutPai-2) )
				{
					nType = 2;
				}
				else if( m_wjMaj[0].GetPaiInHand()[(int)m_arrEat.GetAt(0)] == (m_nOutPai-1) )
				{
					nType = 1;
				}
				else
				{
					nType = 0;
				}
				PlayOtherSound(S_EAT,m_wjMaj[0].GetSex());
				m_wjMaj[0].SetChi(nType);
				m_nActive = 0;
				m_nOutPai = -1;
				m_wjMaj[3].RemoveOutPai();
				DrawAllpai();
				UpdateFrame();
				OnTimer(1);
			}
			else if(m_arrEat.GetSize() > 2)			//���Ǿ�����ѡ��
			{
				m_bwjState = false;
				ChangBoolFalse();
				m_nActive = 0;
				m_bSelect = true;
				DrawTitle();
				DrawSelect();
				UpdateFrame();
			}
		}
		//��
		if(m_nMousePai == TITLE_PENG)
		{
			m_bwjState=false;
			m_wjMaj[0].SetPeng();
			m_wjMaj[m_nChupaiUser].RemoveOutPai();
			m_nOutPai = -1;
			m_nActive = 0;
			PlayOtherSound(S_PEN,m_wjMaj[0].GetSex());
			DrawAllpai();
			UpdateFrame();
			OnTimer(1);
		}
		//��
		if(m_nMousePai == TITLE_GUO)
		{
			m_bwjState = false;
			m_nAbandon = true;
			UpdateFrame();
			m_nSelectTime = TimeSelect;
			KillTimer(3);
			OnTimer(1);
		}
	}
}


void CMahjongDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bHandDown=false;
	//�Ƿ��������Ͻǵ�Сͼ��
	if(m_nMousePai == TITLE_MIN)
	{
		CloseWindow();
	}
	else if(m_nMousePai == TITLE_CLOSE)
	{
		DestroyWindow();
	}
	else if(m_nMousePai == TITLE_SET)			//����
	{
		m_bZuobi =! m_bZuobi;
		if(m_bRun)
		{
			DrawPai();
			UpdateFrame();
		}
	}
	//��ʼ״̬
	if(m_bStart)
	{
		if(m_nTitle == 3)
		{
			sndPlaySound("Sounds\\start.wav",SND_ASYNC);
			m_bCaton = true;
			m_bStart = false;

			SetTimer(2,50,NULL);
			SetTimer(1,TimeRun,NULL);
			SetCursor(m_hCursor);
			return;
		}
	}
	//����״̬
	if(m_bOver)
	{
		if(m_nTitle == 4)
		{
			m_bStart = true;
			m_bOver = false;
			m_bRun = false;

			m_memDC.BitBlt(0,0,800,600,&m_bgDC,0,0,SRCCOPY);
			m_memDC.BitBlt(370,400,55,28,&m_titleDC,0,127,SRCCOPY);		
			SetCursor(m_hCursor);
			UpdateFrame();
			sndPlaySound("Sounds\\bg.wav",SND_ASYNC|SND_LOOP);
			return;
		}
	}
	//����״̬
	if(m_bRun)
	{
		OnClickTitle(point);
		//����ǳԻ�ܵ�ѡ��״̬
		if(m_bSelect)
		{
			//�����ҵ�״̬�ǳ��ƾͱ����Ǹܵ�ѡ��״̬�����ǳԵ�ѡ��״̬
			if(m_wjMaj[0].GetState() == 1 )
			{
				if(m_nSelectGang != -1)
				{
					m_bSelect = false;
					PlayOtherSound(S_GAN);
					m_wjMaj[0].SetGang(m_nSelectGang);
					m_wjMaj[0].SetNewPai(m_zmMaj.GetGangPai());
					m_nActive = 0;	
					m_nSelectGang = -1;
					DrawPaiUp(m_nMousePai);
					UpdateFrame();
				}
			}
			else
			{
				if(m_nSelectEat != -1)
				{
					int type;
					PlayOtherSound(S_EAT);
					m_bSelect = false;
					if(m_nOutPai-2 == m_nSelectEat)
					{
						type = 2;
					}
					else if(m_nOutPai-1 == m_nSelectEat)
					{
						type = 1;
					}
					else
					{
						type = 0;
					}
					m_wjMaj[0].SetChi(type);
					m_wjMaj[m_nChupaiUser].RemoveOutPai();
					m_nActive = 0;	
					m_nOutPai = -1;
					m_nSelectEat = -1;
					DrawAllpai();
					UpdateFrame();
				}
			}
			return;
		}
	}
	//��ҳ���
	if(m_bRun &&m_nMousePai != -1 && m_nMousePai < 100 && m_wjMaj[0].GetState() == 1)
	{
		m_wjMaj[0].OutPai(m_nMousePai);
		m_nWaitTime = TimeSelect;
		m_nOutPai = m_wjMaj[0].GetOutPai()[m_wjMaj[0].GetOutNum()-1];	
		ChangBoolFalse();
		m_nChupaiUser = 0;
		DrawAllpai();
		UpdateFrame();	
		sndPlaySound("Sounds\\give.wav",SND_ASYNC|SND_NODEFAULT);	
		PlayPaiSound(m_nOutPai,m_wjMaj[0].GetSex());
		return;
	}
	CDialog::OnLButtonUp(nFlags, point);
}

/*************************************************************/
/*�������ܣ��ı䱾�˵�״̬
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void CMahjongDlg::ChangBoolFalse()
{
	m_bHu = false;
	m_bChi = false;
	m_bPeng = false;
	m_bGang = false;
}

/*************************************************************/
/*�������ܣ�ͳ�Ƹ���ҵķ���
/*��ڲ�������
/*�������ͣ�void
/*************************************************************/
void  CMahjongDlg::CheckWhoGet()
{	
	int a[4],i,j,k;
															
	for(i = 0;i < 4;i++)									//��ʼ������ҷ�ֵ
	{
		m_nGoodScore[i] = 0;
		if(i != 0)
		{
			a[i] = CheckNeedGet(i,m_nOutPai);	
		}
	}
	CheckPerson();
	i = m_nChupaiUser;										//��õ�ǰ˭������
	for(j = 0,k = 3;j < 3;j++,k--)
	{
		i++;
		if(i > 3)											//��ø���ҵ����Ʒ�
		{
			i = 0;
			if(m_bHu)
			{
				m_nGoodScore[i] = k+1000;
			}
			else if(m_bPeng||m_bGang)
			{
				m_nGoodScore[i] = k+500;
			}
			else if(m_bChi)
			{
				m_nGoodScore[i] = k+100;
			}
			else
			{
				m_nGoodScore[i] = k;
			}
		}
		else
		{
			m_nGoodScore[i] = k+a[i];
		}
	}
}

/*************************************************************/
/*�������ܣ������Զ������Ƶ���Ҫ
/*��ڲ��������ͣ��Ǽҵ��ԣ������ͣ��ƣ�
/*�������ͣ����ͣ�������Ҫ�ķ�����
/*************************************************************/
int CMahjongDlg::CheckNeedGet(int nWho,int pai)
{
	int a[14],i,j;
	int nStar;
	m_wjMaj[nWho].SetOutPai(pai);								//���õ�����ҵĳ���
	nStar = m_wjMaj[nWho].GetPaiStart();						//���������Ч�Ŀ�ʼ

	if(m_wjMaj[nWho].ThinkHupai())								//��������
	{
		return 1000;
	}
	bool bPeng;
	if(m_wjMaj[nWho].CheckGang(bPeng))							//���Կ��Ǹ���
	{
		for(i = 0,j = 0;i < 13-nStar;i++)
		{
			if(m_wjMaj[nWho].GetPaiInHand()[i] != pai)
			{
				a[j] = m_wjMaj[nWho].GetPaiInHand()[i+nStar];
				j++;
			}
		}
		CCmpThink ctTemp;
		ctTemp.SetMjPaiArray(a,j);
		ctTemp.Think();
		if(ctTemp.GetMaxScore() >= m_nCmpGoodScore[nWho] - 300)//����Ƴ��Ǽ����ƺ��������ͱ�ʾ���Ը�
		{
			return 800;
		}

	}
	for(i = 0;i < 13-nStar;i++)	
	{
		a[i] = m_wjMaj[nWho].GetPaiInHand()[i+nStar];
	}
	
	a[13-nStar] = pai;
	CCmpThink ct;											//˼��
	ct.SetMjPaiArray(a,14-nStar);
	ct.Think();												//���Կ���

	int ret = ct.GetBadly();								//�������������
	if( ret == pai )return 0;								//��������Ƶ��ڵ�ǰ��ҳ����Ʒ���0
	if( ct.GetMaxScore() > m_nCmpGoodScore[nWho]+150 )		//�����ǰ��������Ϻ�������־Ϳ��Գ���
	{		
		int pai1,pai2,pai3;								
		ct.GetGoodTeam(pai1,pai2,pai3);						//��õ�ǰ�����Ƶ�������
		if( pai1 == pai2 )
			return 500;
		else
		{
			nWho--;
			if(nWho<0)
				nWho=3;
			if(m_nChupaiUser == nWho)						//�������һ�ҳ����Ƽ����Գ�
			{
				if( pai1 == pai )
					return 100;
				else if( pai2 == pai )
					return 200;
				else
					return 300;
			}
		}
	}
	return 0;
}

void CMahjongDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bHandDown = true;
	if(m_bOver||m_bStart)
	{
		DrawTitle();
		UpdateFrame();
	}
	CDialog::OnLButtonDown(nFlags, point);
	MSG message;
	while(::PeekMessage(&message,this->m_hWnd,WM_LBUTTONDOWN,WM_LBUTTONDOWN,PM_REMOVE));
}

int CMahjongDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
