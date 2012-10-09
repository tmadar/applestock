#include <atlbase.h>
#include <atlapp.h>
#include <atlmisc.h>
#include <atlstr.h>
#include <atlmisc.h>
#include "INet.h"
#include "StockXMLParser.h"
#pragma once

class AppleStockUpdater
{
public:

	WTL::CString stockPrice;
	WTL::CString stockPriceXml;
	StockXMLParser parser;
	CInternetSession session;
	int timeToDie;
	HANDLE threadHandle;
	HANDLE CMainFrameHandle;
	UINT_PTR timer;

	AppleStockUpdater(void);
	~AppleStockUpdater(void);

	int GetStockInfo();
	int StartThread();
	static DWORD WINAPI RunThread(LPVOID lpData);
};
VOID CALLBACK MyTimerProc( 
    HWND hwnd,        // handle to window for timer messages 
    UINT message,     // WM_TIMER message 
    UINT idTimer,     // timer identifier 
    DWORD dwTime);

