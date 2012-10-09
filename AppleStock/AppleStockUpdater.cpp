#include "stdafx.h"
#include "AppleStockUpdater.h"
#include "INet.h"
#include "AppleStockView.h"
#include "StockXMLParser.h"
#pragma once
#define APPLE_URL "http://www.google.com/ig/api?stock=AAPL"
#define TIMER_1  123213

AppleStockUpdater* defaultUpdater;

AppleStockUpdater::AppleStockUpdater(void) {
	session = CInternetSession(_T("Apple Stock App"));
	timeToDie = FALSE;
}


AppleStockUpdater::~AppleStockUpdater(void)
{
	KillTimer(NULL, TIMER_1);
}

struct _RunData
{
	AppleStockUpdater* appleStockInstance;
};

int AppleStockUpdater::GetStockInfo() {
	CInternetSession Session(_T("Test Application"));
	CHttpFile cHttpFile(Session,_T(APPLE_URL));
	WTL::CString pageSource, pageSize;

	UINT bytes = (UINT) cHttpFile.GetLength();

	char tChars[2048+1];
	int bytesRead;

	while((bytesRead = cHttpFile.Read((LPVOID) tChars, 2048)) != 0) {
		tChars[bytesRead] = '\0';
		pageSource += tChars;
	}

	this->stockPriceXml.Format(_T("%s"), pageSource);

	if (this->CMainFrameHandle) {
		::PostMessage(reinterpret_cast<HWND>(this->CMainFrameHandle), WM_SET_STOCK, NULL, NULL);
	}

	return 1;
}

int AppleStockUpdater::StartThread() {
	_RunData *pData = new _RunData;
	pData->appleStockInstance = this;
	threadHandle = ::CreateThread(NULL, 0, AppleStockUpdater::RunThread, pData, 0, NULL);
	return 1;
}

DWORD WINAPI AppleStockUpdater::RunThread(LPVOID lpData)
{
	_RunData* myself = (_RunData*)lpData;
	HWND hMainFrame = reinterpret_cast<HWND>(myself->appleStockInstance->CMainFrameHandle);
	defaultUpdater = myself->appleStockInstance;
	defaultUpdater->GetStockInfo();
	defaultUpdater->timer = SetTimer(hMainFrame, TIMER_1, 3000, (TIMERPROC) MyTimerProc);

	free(myself);
	return 0;
}

VOID CALLBACK MyTimerProc(
	HWND hwnd,        
    UINT message,   
    UINT idTimer,     
    DWORD dwTime)   
{ 
	defaultUpdater->GetStockInfo();
} 