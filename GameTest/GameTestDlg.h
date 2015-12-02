// GameTestDlg.h : ͷ�ļ�
//

#pragma once
#include "MyCreature.h"
#include "MyAnimal.h"
#include "MyScenery.h"

#define FREQUENCY_TIMER 50
//#define PATH_PIC "pic/"
#define PATH_PIC "../GameTest/pic/"


// CGameTestDlg �Ի���
class CGameTestDlg : public CDialog
{
// ����
public:
	CGameTestDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CMyCreature m_MyCreature;

// �Ի�������
	enum { IDD = IDD_GAMETEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedOk2();
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedOk3();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void TransparentBlt( HDC,int, int,int, int,HDC,int,int,UINT );
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
public:
	int GetBitmapIndex(const CMyCreature&, int);
	afx_msg void OnBnClickedAddscenery();
private:
	long m_iWidth;
	long m_iHeight;
	HDC m_hDCBitmap;
	HDC m_hDCMemBitmap;
	HBITMAP m_hBitmap;
	HBITMAP m_hEmptyBitmap; // �հױ���
public:
	afx_msg void OnBnClickedAddanimal();
};
