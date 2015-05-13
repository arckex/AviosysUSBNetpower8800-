// GPIOTestDlg.h : header file
//

#pragma once
#include <winsock2.h>
#include "afxinet.h"
#include "utf8.h"
#define EXPORT_API __declspec(dllexport) // Visual Studio needs annotating exported functions with this
BOOL m_bWindows2000;
HANDLE m_hCOM, m_hDrv;
DCB m_DCB;
BOOL m_bGP0Enable, m_bGP1Enable;
CString m_comStr;
int Power_Status, Sch_flag;
