
// PickupAndPushOutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PickupAndPushOut.h"
#include "PickupAndPushOutDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPickupAndPushOutDlg dialog



CPickupAndPushOutDlg::CPickupAndPushOutDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PICKUPANDPUSHOUT_DIALOG, pParent)
	, m_Message(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPickupAndPushOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LVIAL, m_LargeVial);
	DDX_Control(pDX, IDC_CALC_ZDOWN, m_CalcZdown);
	DDX_Text(pDX, IDC_EDITBOX, m_Message);
}

BEGIN_MESSAGE_MAP(CPickupAndPushOutDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CALC_ZDOWN, &CPickupAndPushOutDlg::OnBnClickedCalcZdown)
END_MESSAGE_MAP()


// CPickupAndPushOutDlg message handlers

BOOL CPickupAndPushOutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_Message = _T("PickupVolume(in ul unit)=");
	UpdateData(FALSE);
	m_LargeVial.SetCheck(BST_CHECKED);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPickupAndPushOutDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPickupAndPushOutDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPickupAndPushOutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPickupAndPushOutDlg::OnBnClickedCalcZdown()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int bottleRemainingVol = 30000;
	int pickupVol = 200;
	int nBotSize = (int) 'L';
	int checked = m_LargeVial.GetCheck();
	if (checked == BST_UNCHECKED)
	{
		bottleRemainingVol = 2640;
		nBotSize - (int) 'S';
	}

	int nsteps = mfCalZ1aDown(bottleRemainingVol, pickupVol, nBotSize);
	m_Message.Format(_T("Z Steps=%d"), nsteps);
	UpdateData(FALSE);
}

int CPickupAndPushOutDlg::mfCalZ1aDown(const int nBottleVol, const int nPickupVol, const int nBotSize)
{
	const int m_nZmax = 1860;
	const int m_nInclineVolLarge = 5500;
	const int m_nInclineStepsLarge = 133;
	const int m_nSteps5mlLarge = 40;
	const int m_nInclineVolSmall = 3000;
	const int m_nInclineStepsSmall = 124;
	const int m_nSteps5mlSmall = 100;

	int nSteps = m_nZmax;
	int iVol;
	int nSteps5ml;
	int iSteps;

	if (nBotSize == 'L') {
		iVol = m_nInclineVolLarge;
		iSteps = m_nInclineStepsLarge;
		nSteps5ml = m_nSteps5mlLarge;
	}
	else {
		iVol = m_nInclineVolSmall;
		iSteps = m_nInclineStepsSmall;
		nSteps5ml = m_nSteps5mlSmall;
	}

	if ((nBottleVol - iVol) > nPickupVol) {						// start in flat region end in flat region
		nSteps = m_nZmax - iSteps - (nBottleVol - iVol - nPickupVol) * nSteps5ml / 5000;
	}
	else {
		if ((nBottleVol - iVol) == nPickupVol)
			nSteps = m_nZmax - iSteps;
		else {
			if (nBottleVol > iVol) {                                // starts in flat region end in incline region
				nSteps = m_nZmax - iSteps + (nPickupVol - (nBottleVol - iVol)) * iSteps / iVol;
			}
			else {													// all in incline regiion
				nSteps = m_nZmax;								// just go to the bottom of the bottle
			}
		}
	}

	if (nSteps < 0)
		nSteps = 0;
	if (nSteps > m_nZmax)
		nSteps = m_nZmax;

	return nSteps;
}