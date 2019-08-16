
// PickupAndPushOutDlg.h : header file
//

#pragma once


// CPickupAndPushOutDlg dialog
class CPickupAndPushOutDlg : public CDialogEx
{
// Construction
public:
	CPickupAndPushOutDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PICKUPANDPUSHOUT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCalcZdown();
	int mfCalZ1aDown(const int nBottleVol, const int nPickupVol, const int nBotSize);
	CButton m_CalcZdown;
	CButton m_LargeVial;
	CString m_Message;
};
