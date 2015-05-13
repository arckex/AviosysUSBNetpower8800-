// GPIOTestDlg.cpp : implementation file

#include "stdafx.h"
//#include "GPIOTest.h"
#include "GPIOTestDlg.h"

#include <time.h>
#include <math.h>

#include "GPIO.h"
#include "Ioctl.h"
#pragma comment( lib, "Rpcrt4.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CheckWindowsVersion()
{
	DWORD dwVersion = GetVersion();
 
	// Get the Windows version.
	DWORD dwWindowsMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
	DWORD dwWindowsMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

	// Get the build number for Windows NT/Windows 2000 or Win32s.
	if(dwVersion < 0x80000000)							// Windows NT/2000
		m_bWindows2000 = TRUE;
	else if (dwWindowsMajorVersion < 4)					// Win32s
		m_bWindows2000 = FALSE;
	else												// Windows 95/98 -- No build number
		m_bWindows2000 = FALSE;
}

void OpenSymbolicPort()
{
	if(m_bWindows2000) {
		m_hDrv = m_hCOM;
	} else {
		m_hDrv = CreateFile("\\\\.\\USBCOM-1", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL, OPEN_EXISTING, 0, NULL);
	}
}

void OnBnClickedBtnOpenport();

void OnBnClickedBtnGp0Get()
{
	BYTE val = 0;

	if(m_hDrv == INVALID_HANDLE_VALUE) {
		return;
	}

	BOOL bSuccess = PL2303_GP1_GetValue(m_hDrv, &val);				// Get GP1 value
	if(bSuccess) {
		if(val == 0) {
			Power_Status = 1;
		} else {
			Power_Status = 0;
		}
	} else {
		Power_Status = -1;
	}
}

void EXPORT_API OnBnClickedButtonLight()
{
	if(Power_Status != -1) {
		BOOL bSuccess = PL2303_GP1_SetValue(m_hDrv, Power_Status);	// Set GP1 value
		OnBnClickedBtnGp0Get();
	}
}

void OnBnClickedBtnGp3Get()
{
	BYTE val;
    BYTE data;
	if(m_hDrv == INVALID_HANDLE_VALUE) {
		return;
	}

	BOOL bSuccess = PL2303_GP23_GetValue(m_hDrv, &data);				// Get GP2 value
	                
	val = (BYTE) ((data & 0x02)>0)?1:0;
	if(bSuccess) {
		if (val == 0) { 
			OnBnClickedBtnGp0Get();
		} else {
			OnBnClickedBtnOpenport();
		}
	} else {
		OnBnClickedBtnOpenport();
	}
}

void OnBnClickedChkGp0Enable()
{
	if(m_hDrv == INVALID_HANDLE_VALUE) {
		return;
	}

	m_bGP0Enable = true;
	BOOL bSuccess = PL2303_GP1_Enalbe(m_hDrv, m_bGP0Enable);		// GP1 Output Enable
	if(!bSuccess) {
		OnBnClickedBtnOpenport();
	} else {
		OnBnClickedBtnGp3Get();		// GP3 Output Value
	}
}

void OnBnClickedBtnOpenport()
{
	HANDLE hCOM;
	bool Connectflag=0;
	CString tmpStr;
	int nIndex = 0;

	while (Connectflag == 0) 	{
		if (nIndex != 15) {
			sprintf((char*)(LPCSTR(tmpStr)),"%s%d","\\\\.\\COM",nIndex);
			hCOM = ::CreateFile(tmpStr, GENERIC_READ | GENERIC_WRITE,
					0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
			if (hCOM == INVALID_HANDLE_VALUE) {
				nIndex ++;
			} else {
				Connectflag = 1;
				m_hCOM = hCOM;
				OpenSymbolicPort();
				OnBnClickedChkGp0Enable();
			}
		} else {
			Power_Status = -1;
			break;
		}
	}
}

extern "C" void EXPORT_API Init()
{
	CheckWindowsVersion();
	OnBnClickedBtnOpenport();
}

extern "C" void EXPORT_API Toggle(bool fanState)
{
	if(Power_Status != -1) 
	{
		BOOL bSuccess = PL2303_GP1_SetValue(m_hDrv, (int)fanState);	// Set GP1 value
		OnBnClickedBtnGp0Get();
	}
}

extern "C" void EXPORT_API Close()
{
	if(m_hCOM != INVALID_HANDLE_VALUE) {
		::CloseHandle(m_hCOM);
		m_hCOM = INVALID_HANDLE_VALUE;
	}

	if(m_hDrv != INVALID_HANDLE_VALUE) {
		if(!m_bWindows2000)
			::CloseHandle(m_hDrv);
		m_hDrv = INVALID_HANDLE_VALUE;
	}
}
