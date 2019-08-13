
// DataMatrixReaderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataMatrixReader.h"
#include "DataMatrixReaderDlg.h"
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


// CDataMatrixReaderDlg dialog



CDataMatrixReaderDlg::CDataMatrixReaderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DATAMATRIXREADER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Image = NULL;
}

CDataMatrixReaderDlg::~CDataMatrixReaderDlg()
{
	if (m_Image != NULL)
		delete m_Image;
}

void CDataMatrixReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDataMatrixReaderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD, &CDataMatrixReaderDlg::OnBnClickedLoadBIN)
	ON_BN_CLICKED(IDC_SCAN, &CDataMatrixReaderDlg::OnBnClickedLoadJPG)
END_MESSAGE_MAP()


// CDataMatrixReaderDlg message handlers

BOOL CDataMatrixReaderDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDataMatrixReaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDataMatrixReaderDlg::OnPaint()
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
HCURSOR CDataMatrixReaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDataMatrixReaderDlg::OnBnClickedLoadBIN()
{
	// TODO: Add your control notification handler code here
	LoadBinaryFile(".\\datafile2.bin");
}

void CDataMatrixReaderDlg::LoadBinaryFile(const char* filename)
{
	if (m_Image != NULL)
		delete m_Image;
	FILE *fp;
	fopen_s(&fp, filename, "rb");
	BITMAPINFOHEADER header;
	int count = fread(&header, sizeof(BITMAPINFOHEADER), 1, fp);
	if (count != 1)
	{
		MessageBox(_T("Failed to load data file!"));
		return;
	}
	size_t size = header.biWidth * header.biHeight;
	byte *srcPtr = (byte*)malloc(size);
	byte *blockMemPtr = srcPtr;
	fread(srcPtr, 1, size, fp);
	fclose(fp);
	m_Image = new CImage();
	m_Image->Create(header.biWidth, -header.biHeight, 24);
	byte* dstPtr = (byte *)m_Image->GetBits();
	for (int i = 0; i < header.biHeight; i++)
	{
		srcPtr = blockMemPtr + header.biWidth * (header.biHeight - i - 1);
		for (int j = 0; j < header.biWidth; j++, srcPtr++)
		{
			*dstPtr++ = *srcPtr;
			*dstPtr++ = *srcPtr;
			*dstPtr++ = *srcPtr;
		}
	}
	free(blockMemPtr);
	DrawPicture(m_Image);
}

void CDataMatrixReaderDlg::DrawPicture(CImage *image)
{
	CStatic *picture = (CStatic *)GetDlgItem(IDC_PICTURE);
	picture->ModifyStyle(0xF, SS_BITMAP, SWP_NOSIZE);
	CDC *screenDC = GetDC();
	CDC *pMDC = new CDC;
	pMDC->CreateCompatibleDC(screenDC);

	CRect *rect = new CRect();
	picture->GetClientRect(rect);
	int x0 = rect->left;
	int y0 = rect->top;
	int width = rect->right - rect->left;
	int height = rect->bottom - rect->top;
	CBitmap *newbmp = new CBitmap();
	newbmp->CreateCompatibleBitmap(screenDC, width, height);
	CBitmap *oldbmp = pMDC->SelectObject(newbmp);
	SetStretchBltMode(pMDC->m_hDC, COLORONCOLOR);
	image->StretchBlt(pMDC->m_hDC, 0, 0, width, height, 0, 0, image->GetWidth(), image->GetHeight(), SRCCOPY);
	pMDC->SelectObject(oldbmp);
	picture->SetBitmap((HBITMAP)(*newbmp));
	delete pMDC;
	delete rect;
	newbmp->Detach();
	delete newbmp;
	ReleaseDC(screenDC);
}

void CDataMatrixReaderDlg::OnBnClickedLoadJPG()
{
	// TODO: Add your control notification handler code here
	if (m_Image != NULL)
		delete m_Image;
	m_Image = new CImage();
	HRESULT hr = m_Image->Load(_T(".\\Photo_1.jpg"));
	if (SUCCEEDED(hr) && m_Image->IsDIBSection() && (m_Image->GetWidth() > 320) && (m_Image->GetHeight() > 240))
	{
		BITMAPINFOHEADER header;
		memset(&header, 0, sizeof(BITMAPINFOHEADER));
		header.biSize = sizeof(BITMAPINFOHEADER);
		header.biWidth = 320;
		header.biHeight = 240;
		header.biBitCount = 8;
		header.biPlanes = 1;
		header.biSizeImage = 320 * 240;
		size_t dataSize = sizeof(BITMAPINFOHEADER) + header.biSizeImage;
		byte * data = (byte *)malloc(dataSize);
		memcpy(data, &header, sizeof(BITMAPINFOHEADER));
		byte * dstRecStartPtr = (byte *)data + sizeof(BITMAPINFOHEADER);
		int startRowIndex = (m_Image->GetHeight() - 240) / 2;
		int startColumnIndex = (m_Image->GetWidth() - 320) / 2;
		int bytesPerRow = abs(m_Image->GetPitch());
		byte *srcImageStartPtr = (byte *)m_Image->GetBits() - bytesPerRow * m_Image->GetHeight();
		for (int i = 0; i < header.biHeight; i++)
		{
			byte *srcPtr = srcImageStartPtr + (i + startRowIndex) * bytesPerRow + startColumnIndex * 3;
			byte *dstPtr = dstRecStartPtr + i * header.biWidth;
			for (int j = 0; j < header.biWidth; j++, dstPtr++, srcPtr += 3)
			{
				double value = (*srcPtr + *(srcPtr + 1) + *(srcPtr + 2)) / 3;
				*dstPtr = (byte) value;
			}
		}
		FILE *fp;
		fopen_s(&fp, ".\\test.bin", "wb");
		fwrite((byte *)data, 1, dataSize, fp);
		fclose(fp);
		free(data);
		LoadBinaryFile(".\\test.bin");
	}
	else
	{
		MessageBox(_T("Failed to load JPG Image File!"));
	}

}
