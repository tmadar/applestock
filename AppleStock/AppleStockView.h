// AppleStockView.h : interface of the CAppleStockView class
//
/////////////////////////////////////////////////////////////////////////////
#include "resource.h"
#pragma once

static UINT WM_SET_BROWSER = ::RegisterWindowMessage(_T("WM_SET_BROWSER")); 
static UINT WM_OPEN_BROWSER = ::RegisterWindowMessage(_T("WM_OPEN_BROWSER")); 
static UINT WM_SET_STOCK = ::RegisterWindowMessage(_T("WM_SET_STOCK")); 

class CAppleStockView : public CDialogImpl<CAppleStockView>
{
public:
	HWND mainFrameHandle;

	enum { IDD = IDD_APPLE_FORM };

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CWindow::IsDialogMessage(pMsg);
	}

	BEGIN_MSG_MAP(CAppleStockView)
		COMMAND_HANDLER(ID_GA, STN_CLICKED, OnStnClickedTestTextga)
		COMMAND_HANDLER(IDC_BUTTON1, BN_CLICKED, OnBnClickedButton1)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
	LRESULT OnStnClickedTestTextga(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	
	LRESULT OnBnClickedButton1(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add your control notification handler code here
		::SendMessage(mainFrameHandle, WM_OPEN_BROWSER, NULL, NULL);
		return 0;
	}

};
