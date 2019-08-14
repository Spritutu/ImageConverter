; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEchoServerDlg
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "EchoServer.h"

ClassCount=4
Class1=CEchoServerApp
Class2=CEchoServerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=MyEchoSocket
Resource3=IDD_ECHOSERVER_DIALOG

[CLS:CEchoServerApp]
Type=0
HeaderFile=EchoServer.h
ImplementationFile=EchoServer.cpp
Filter=N

[CLS:CEchoServerDlg]
Type=0
HeaderFile=EchoServerDlg.h
ImplementationFile=EchoServerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CEchoServerDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=EchoServerDlg.h
ImplementationFile=EchoServerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ECHOSERVER_DIALOG]
Type=1
Class=CEchoServerDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1342242816
Control5=IDC_EDIT2,edit,1352728708
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATUS,static,1342308352
Control8=IDC_STATIC,button,1342177287

[CLS:MyEchoSocket]
Type=0
HeaderFile=MyEchoSocket.h
ImplementationFile=MyEchoSocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q
LastObject=MyEchoSocket

