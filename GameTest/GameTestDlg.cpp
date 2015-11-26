// GameTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameTest.h"
#include "GameTestDlg.h"
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
int g_index;
HBITMAP g_hbmPerson[800];
HBITMAP g_hbmScenery[97];
vector<CMyScenery> g_vScenery;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGameTestDlg �Ի���




CGameTestDlg::CGameTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGameTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CGameTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CGameTestDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDCANCEL, &CGameTestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK3, &CGameTestDlg::OnBnClickedOk3)
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_AddScenery, &CGameTestDlg::OnBnClickedAddscenery)
END_MESSAGE_MAP()


// CGameTestDlg ��Ϣ�������

BOOL CGameTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	g_index = 0;
	srand(unsigned(time(NULL)));

	// ��������ͼƬ��Դ
	CString path = "pic/per/";
	for(int i = 0; i < 800; i++) {
		CString name = "c";
		char str[10];
		sprintf(str, "%05d.bmp", i);
		CString x = str;
		name = name + x;
		g_hbmPerson[i] = (HBITMAP)LoadImage(AfxGetInstanceHandle(), path + name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	}

	// ���ؾ���ͼƬ��Դ
	path = "pic/��/";
	for (int i = 0; i < 97; i++) {
		CString name = "c";
		char str[10];
		sprintf(str, "%05d.bmp", i);
		name += CString(str);
		g_hbmScenery[i] = (HBITMAP)LoadImage(AfxGetInstanceHandle(), path + name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}

	CClientDC dc(this);
	m_hDCBitmap = CreateCompatibleDC(dc);
	m_hDCMemBitmap = CreateCompatibleDC(dc);
	m_hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), "pic/diA.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hEmptyBitmap = CreateCompatibleBitmap(dc, m_iWidth = 640, m_iHeight = 480);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CGameTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGameTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CGameTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGameTestDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnOK();
	CClientDC dc(this);
	HDC hdc = dc.m_hDC;
	HPEN penRed = ::CreatePen(PS_SOLID, 5, RGB(200, 200, 254));
	HPEN penOld = (HPEN)SelectObject(hdc, penRed);
	MoveToEx(hdc, 150, 100, NULL);
	LineTo(hdc, 200, 150);
	LineTo(hdc, 100, 150);
	LineTo(hdc, 150, 100);
	SelectObject(hdc, penOld);
	DeleteObject(penRed);
	return ;
}

void CGameTestDlg::OnBnClickedOk2()
{	
	CClientDC dc(this);
	SelectObject(m_hDCBitmap, m_hBitmap);
	DIBSECTION ds;
	BITMAPINFOHEADER &bm = ds.dsBmih;
	GetObject(m_hBitmap, sizeof(ds), &ds);
	int iWidth = bm.biWidth;
	int iHeight = bm.biHeight;
	BitBlt(dc.m_hDC, 0, 0, iWidth, iHeight, m_hDCBitmap, 0, 0, SRCCOPY);
	KillTimer(0);
}

void CGameTestDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void CGameTestDlg::OnBnClickedOk3()
{
	g_index = 0;
	SetTimer(0, 70, NULL);
}

int CGameTestDlg::GetBitmapIndex(CMyCreature MyCreature, int idx) {
	int res;
	if (MyCreature.GetState() == STAND) {
		res = MyCreature.GetFace() + idx % 5;
	}
	else {
		res = MyCreature.GetFace() * 2 + 40 + idx % 10;
	}
	return res;
}

void CGameTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// �����ƶ�
	m_MyCreature.Move(g_index);
	CClientDC dc(this);
	DIBSECTION ds;
	BITMAPINFOHEADER &bm = ds.dsBmih;

	// ���ص�ͼ
	SelectObject(m_hDCBitmap, m_hBitmap);
	SelectObject(m_hDCMemBitmap, m_hEmptyBitmap);
	// SelectObject(m_hDCMemBitmap, hTmpBitmap);
	SelectObject(m_hDCMemBitmap, m_hBitmap);
	GetObject(m_hBitmap, sizeof(ds), &ds);
	int iWidth = bm.biWidth;
	int iHeight = bm.biHeight;
	BitBlt(m_hDCMemBitmap, 0, 0, iWidth, iHeight, m_hDCBitmap, 0, 0, SRCCOPY);

	// ���ؾ���
	int iScenerySize = g_vScenery.size();
	vector<pair<int, int> > *drawSeq = new vector<pair<int, int> >();
	for (int i = 0; i < iScenerySize; i++) {
		GetObject(g_hbmScenery[g_vScenery[i].GetID()], sizeof ds, &ds);
		drawSeq->push_back({ g_vScenery[i].GetY() + bm.biHeight, i });
	}
	GetObject(g_hbmPerson[GetBitmapIndex(m_MyCreature, g_index)], sizeof(ds), &ds);
	drawSeq->push_back({ m_MyCreature.GetY() + bm.biHeight, iScenerySize });
	sort(drawSeq->begin(), drawSeq->end());
	for (int i = 0; i <= iScenerySize; i++) {
		int iID = (*drawSeq)[i].second;
		if (iID == iScenerySize) {
			// ��������
			GetObject(g_hbmPerson[GetBitmapIndex(m_MyCreature, g_index)], sizeof(ds), &ds);
			iWidth = bm.biWidth;
			iHeight = bm.biHeight;
			SelectObject(m_hDCBitmap, g_hbmPerson[GetBitmapIndex(m_MyCreature, g_index)]);
			SelectObject(m_hDCMemBitmap, g_hbmPerson[GetBitmapIndex(m_MyCreature, g_index)]);
			TransparentBlt(m_hDCMemBitmap, m_MyCreature.GetX(), m_MyCreature.GetY(), iWidth, iHeight, m_hDCBitmap, 0, 0, RGB(255, 255, 255));
		}
		else {
			SelectObject(m_hDCBitmap, g_hbmScenery[g_vScenery[iID].GetID()]);
			SelectObject(m_hDCMemBitmap, g_hbmScenery[g_vScenery[iID].GetID()]);
			GetObject(g_hbmScenery[g_vScenery[iID].GetID()], sizeof ds, &ds);
			iWidth = bm.biWidth;
			iHeight = bm.biHeight;
			TransparentBlt(m_hDCMemBitmap, g_vScenery[iID].GetX(), g_vScenery[iID].GetY(), iWidth, iHeight, m_hDCBitmap, 0, 0, RGB(255, 255, 255));
		}
	}
	drawSeq->clear();
	delete drawSeq;

	TransparentBlt(dc.m_hDC, 0, 0, m_iWidth, m_iHeight, m_hDCMemBitmap, 0, 0, RGB(255, 255, 255));
	g_index = (g_index + 1) % 10;
	CDialog::OnTimer(nIDEvent);
}

void CGameTestDlg::TransparentBlt( HDC hDesDC,	
					 int iDesX, int iDesY,
					 int iWide, int iHigh,
					 HDC hSurDC,
					 int iSurX,int iSurY,
					 UINT iMaskCol
					 )
{	
	HBITMAP hTmpBmp   = CreateCompatibleBitmap( hDesDC, iWide, iHigh );
	HBITMAP hMaskBmp   = CreateBitmap( iWide, iHigh, 1, 1, NULL );	
	HDC		hTmpDC    = CreateCompatibleDC( hDesDC );
	HDC		hMaskDC    = CreateCompatibleDC( hDesDC );
	HBITMAP hOldTmpBmp = (HBITMAP)SelectObject( hTmpDC, hTmpBmp );
	HBITMAP hOldMaskBmp = (HBITMAP)SelectObject( hMaskDC, hMaskBmp );

	BitBlt( hTmpDC, 0, 0, iWide, iHigh, hSurDC, iSurX, iSurY, SRCCOPY );

	COLORREF colOld = SetBkColor( hTmpDC, iMaskCol );
	BitBlt( hMaskDC, 0, 0, iWide, iHigh, hTmpDC, 0, 0, SRCCOPY );
	SetBkColor( hTmpDC, colOld );

	BitBlt( hMaskDC, 0, 0, iWide, iHigh, hMaskDC, 0, 0, NOTSRCCOPY );

	BitBlt( hTmpDC, 0, 0, iWide, iHigh, hMaskDC, 0, 0, SRCAND );


	BitBlt( hMaskDC, 0, 0, iWide, iHigh, hMaskDC, 0, 0, NOTSRCCOPY );
	BitBlt( hDesDC, iDesX, iDesY, iWide, iHigh, hMaskDC, 0, 0, SRCAND );
	BitBlt( hDesDC, iDesX, iDesY, iWide, iHigh, hTmpDC, 0, 0, SRCPAINT);

	SelectObject(hTmpDC, hOldTmpBmp);				
	DeleteDC(hTmpDC);
	SelectObject(hMaskDC, hOldMaskBmp);
	DeleteDC(hMaskDC);

	DeleteObject(hTmpBmp);
	DeleteObject(hMaskBmp);
}
void CGameTestDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int toX = min(640 - 22 - 3, point.x - 11);
	int toY = min(480 - 42 - 3, point.y - 42);
	m_MyCreature.SetDes(toX, toY);
	CDialog::OnLButtonDblClk(nFlags, point);
}


void CGameTestDlg::OnBnClickedAddscenery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMyScenery tmpScenery(rand() % 510, rand() % 300, rand() % 97);
	// CMyScenery tmpScenery(rand() % 510, rand() % 300, 62);
	//g_msScenery.insert(tmpScenery);
	g_vScenery.push_back(tmpScenery);
}
