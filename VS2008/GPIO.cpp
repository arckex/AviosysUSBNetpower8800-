#include "stdafx.h"

#include <winioctl.h>
#include "ioctl.h"

#include "GPIO.h"

// For GP0
BOOL PL2303_GP0_Enalbe(HANDLE hDrv, BOOL enable)
{
	DWORD nBytes;

	BOOL bSuccess = DeviceIoControl(hDrv, GP0_OUTPUT_ENABLE,
			&enable, sizeof(BYTE), NULL, 0, &nBytes, NULL);
	
	return bSuccess;
}

BOOL PL2303_GP0_GetValue(HANDLE hDrv, BYTE *val)
{
	DWORD nBytes;

	BOOL bSuccess = DeviceIoControl(hDrv, GP0_GET_VALUE,
			NULL, 0, val, sizeof(BYTE), &nBytes, NULL);

	return bSuccess;
}

BOOL PL2303_GP0_SetValue(HANDLE hDrv, BYTE val)
{
	DWORD nBytes;

	BOOL bSuccess = DeviceIoControl(hDrv, GP0_SET_VALUE,
			&val, sizeof(BYTE), NULL, 0, &nBytes, NULL);

	return bSuccess;
}

// For GP1
BOOL PL2303_GP1_Enalbe(HANDLE hDrv, BOOL enable)
{
	DWORD nBytes;

	BOOL bSuccess = DeviceIoControl(hDrv, GP1_OUTPUT_ENABLE,
			&enable, sizeof(BYTE), NULL, 0, &nBytes, NULL);
	
	return bSuccess;
}

BOOL PL2303_GP1_GetValue(HANDLE hDrv, BYTE *val)
{
	DWORD nBytes;

	BOOL bSuccess = DeviceIoControl(hDrv, GP1_GET_VALUE,
			NULL, 0, val, sizeof(BYTE), &nBytes, NULL);

	return bSuccess;
}

BOOL PL2303_GP1_SetValue(HANDLE hDrv, BYTE val)
{
	DWORD nBytes;

	BOOL bSuccess = DeviceIoControl(hDrv, GP1_SET_VALUE,
			&val, sizeof(BYTE), NULL, 0, &nBytes, NULL);

	return bSuccess;
}

BOOL PL2303_GP23_SetValue(HANDLE hDrv, CString str_pa){
    DWORD nBytes;
	WORD buffer23[2]={0,0};
	CString str_com="0D";
	char *endstring2;
    char *endstring3;
	int command =strtol(str_com, &endstring2, 16);
    int value = strtol(str_pa, &endstring3, 16);


	buffer23[0] = command;
	buffer23[1] = value;


 	BOOL bSuccess = DeviceIoControl(hDrv, SEND_ENCAP,
			buffer23, sizeof(buffer23), NULL, 0, &nBytes, NULL);
    return bSuccess;

}


BOOL PL2303_GP23_GetValue(HANDLE hDrv,BYTE *data){


	
	WORD buffer[2] = {0, 0};
	DWORD nBytes;
	CString str;

  	buffer[0] = 141;
BOOL bSuccess = DeviceIoControl(hDrv, GP23_GET_DATA,
			buffer, sizeof(buffer), buffer, sizeof(buffer), &nBytes, NULL);
/*
	if(bSuccess)
		str = "Get command Successfully!";
	else
		str = "Get command FAILED.";

*/

	if(bSuccess) {
		//str.Format("Response: 0x%02X", (BYTE)buffer[0]);
     *data=(BYTE)buffer[0];
	
	}							   
								   
								
	 return bSuccess;

}

BOOL PL2303_GP23_GetCfgValue(HANDLE hDrv,USHORT *data){
	
	USHORT buffer23;
	DWORD nBytes;
	CString str;
  	
	BOOL bSuccess = DeviceIoControl(hDrv, GP23_GET_CONFIG,
			NULL, 0, &buffer23, sizeof(buffer23), &nBytes, NULL);

	if(bSuccess) {
		*data=buffer23;	
	}							   
								   								
	 return bSuccess;
}

BOOL PL2303_GP23_SetCfgValue(HANDLE hDrv, CString str_pa){

	DWORD nBytes;
	USHORT buffer23;

    buffer23 = (USHORT)strtol(str_pa, 0, 16);

 	BOOL bSuccess = DeviceIoControl(hDrv, GP23_SET_CONFIG,
			&buffer23, sizeof(buffer23), NULL, 0, &nBytes, NULL);

    return bSuccess;

}
