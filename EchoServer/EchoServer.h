// EchoServer.h : main header file for the ECHOSERVER application
//

#if !defined(AFX_ECHOSERVER_H__7AA7D190_8407_49A5_A315_FB3E228E6F80__INCLUDED_)
#define AFX_ECHOSERVER_H__7AA7D190_8407_49A5_A315_FB3E228E6F80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEchoServerApp:
// See EchoServer.cpp for the implementation of this class
//

class CEchoServerApp : public CWinApp
{
public:
	CEchoServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEchoServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEchoServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECHOSERVER_H__7AA7D190_8407_49A5_A315_FB3E228E6F80__INCLUDED_)
