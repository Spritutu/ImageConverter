// EchoServerDlg.h : header file
//

#if !defined(AFX_ECHOSERVERDLG_H__91CEEDDC_5EB4_4AE7_8175_D8A85EA9CA07__INCLUDED_)
#define AFX_ECHOSERVERDLG_H__91CEEDDC_5EB4_4AE7_8175_D8A85EA9CA07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEchoServerDlg dialog
#include "MyEchoSocket.h"

class CEchoServerDlg : public CDialog
{
// Construction
public:
	void OnReceive();
	void OnClose();
	void OnAccept();
	CEchoServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEchoServerDlg)
	enum { IDD = IDD_ECHOSERVER_DIALOG };
	CButton	m_stopbutton;
	CButton	m_listenbutton;
	int		m_port;
	CString	m_recieveddata;
	CString	m_status;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEchoServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEchoServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	MyEchoSocket m_sListener;
	MyEchoSocket m_sConnected;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECHOSERVERDLG_H__91CEEDDC_5EB4_4AE7_8175_D8A85EA9CA07__INCLUDED_)
