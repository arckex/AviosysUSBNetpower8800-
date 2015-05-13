// For GP0
BOOL PL2303_GP0_Enalbe(HANDLE hDrv, BOOL enable);
BOOL PL2303_GP0_GetValue(HANDLE hDrv, BYTE *val);
BOOL PL2303_GP0_SetValue(HANDLE hDrv, BYTE val);

// For GP1
BOOL PL2303_GP1_Enalbe(HANDLE hDrv, BOOL enable);
BOOL PL2303_GP1_GetValue(HANDLE hDrv, BYTE *val);
BOOL PL2303_GP1_SetValue(HANDLE hDrv, BYTE val);

// For GP23
BOOL PL2303_GP23_GetValue(HANDLE hDrv, BYTE *data);
BOOL PL2303_GP23_SetValue(HANDLE hDrv, CString str_pa);
BOOL PL2303_GP23_GetCfgValue(HANDLE hDrv, USHORT *data);
BOOL PL2303_GP23_SetCfgValue(HANDLE hDrv, CString str_pa);
