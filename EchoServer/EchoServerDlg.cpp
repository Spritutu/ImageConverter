// EchoServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EchoServer.h"
#include "EchoServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEchoServerDlg dialog

CEchoServerDlg::CEchoServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEchoServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEchoServerDlg)
	m_port = 0;
	m_recieveddata = _T("");
	m_status = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEchoServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEchoServerDlg)
	DDX_Control(pDX, IDC_BUTTON2, m_stopbutton);
	DDX_Control(pDX, IDC_BUTTON1, m_listenbutton);
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDX_Text(pDX, IDC_EDIT2, m_recieveddata);
	DDX_Text(pDX, IDC_STATUS, m_status);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEchoServerDlg, CDialog)
	//{{AFX_MSG_MAP(CEchoServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEchoServerDlg message handlers

BOOL CEchoServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_sListener.SetParentDlg(this); 
	m_sConnected.SetParentDlg(this);
	m_status="Idle...!!!";
	m_port=2000;
	m_stopbutton.EnableWindow(FALSE); 
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEchoServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEchoServerDlg::OnPaint() 
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
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEchoServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEchoServerDlg::OnAccept()
{
	CString strIP;
	UINT port;
	if(m_sListener.Accept(m_sConnected))
	{
		m_sConnected.GetSockName(strIP, port);
		m_status="Client Connected,IP :"+ strIP;
		//m_sConnected.Send("Connected To Server",strlen("Connected To Server")); 
		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("Cannoot Accept Connection"));
	}
}

void CEchoServerDlg::OnClose()
{
	AfxMessageBox(_T("Socket Is Closed!!!"));
	OnButton2(); 
}

void CEchoServerDlg::OnReceive()
{
	char *pBuf =new char [1025];
	int iLen;
	iLen=m_sConnected.Receive(pBuf,1024);
	CString message;
	message.Format(_T("Bytes received = %d\n"), iLen);
	TRACE(message);
	for (int i = 0; i < iLen; i++)
	{
		message.Format(_T("pBuf[%d]=%u\n"), i, pBuf[i]);
		TRACE(message);
	}
	if(iLen==SOCKET_ERROR)
	{
		AfxMessageBox(_T("Could not Recieve"));
	}
	else
	{
		message = "";
		for (int i = 4; i < iLen; i++)
		{
			if (pBuf[i] != 0)
				message += TCHAR(pBuf[i]);
		}
		m_recieveddata.Insert(message.GetLength(), message); 
		UpdateData(FALSE);
		m_sConnected.Send(pBuf, iLen, 0);
		m_sConnected.ShutDown(0);  
	}
	delete pBuf;
}

void CEchoServerDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_sListener.Create(m_port); 
	if(m_sListener.Listen()==FALSE)
	{
		AfxMessageBox(_T("Unable to Listen on that port,please try another port"));
		m_sListener.Close(); 
		return;			
	}
	m_status="Listening For Connections!!!";
	UpdateData(FALSE);
	m_listenbutton.EnableWindow(FALSE);
	m_stopbutton.EnableWindow(TRUE); 
	
}

void CEchoServerDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
m_sConnected.Close(); 
m_sListener.Close(); 
m_status="Idle!!";	
UpdateData(FALSE);
m_listenbutton.EnableWindow(TRUE);
m_stopbutton.EnableWindow(FALSE); 

}
