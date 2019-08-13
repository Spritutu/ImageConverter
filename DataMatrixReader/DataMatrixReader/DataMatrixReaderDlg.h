
// DataMatrixReaderDlg.h : header file
//

#pragma once

#include <atlstr.h>
#include <atlimage.h>

// CDataMatrixReaderDlg dialog
class CDataMatrixReaderDlg : public CDialogEx
{
// Construction
public:
	CDataMatrixReaderDlg(CWnd* pParent = nullptr);	// standard constructor
	virtual ~CDataMatrixReaderDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATAMATRIXREADER_DIALOG };
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
	afx_msg void OnBnClickedLoadBIN();
	afx_msg void OnBnClickedLoadJPG();

private:
	CImage* m_Image;
	void DrawPicture(CImage *image);
	void LoadBinaryFile(const char* filename);
};
