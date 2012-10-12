// AppleStockView.h : interface of the CAppleStockView class
//
/////////////////////////////////////////////////////////////////////////////
#include "resource.h"
#include "time.h"
#include "AppleStockUpdater.h"
#pragma once

static UINT WM_SET_BROWSER = ::RegisterWindowMessage(_T("WM_SET_BROWSER")); 
static UINT WM_OPEN_BROWSER = ::RegisterWindowMessage(_T("WM_OPEN_BROWSER")); 
static UINT WM_SET_STOCK = ::RegisterWindowMessage(_T("WM_SET_STOCK")); 
static UINT WM_SET_STOCK_COLOR = ::RegisterWindowMessage(_T("WM_SET_STOCK_COLOR")); 

class CAppleStockView : public CDialogImpl<CAppleStockView>
{
public:
	HWND mainFrameHandle;
	AppleStockUpdater *stockUpdater;

	enum { IDD = IDD_APPLE_FORM };

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CWindow::IsDialogMessage(pMsg);
	}

	BEGIN_MSG_MAP(CAppleStockView)
		MESSAGE_HANDLER(WM_CTLCOLORDLG, OnCtrlColor)
		MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtrlColor)
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

	LRESULT OnCtrlColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//CWindow obWnd;
		//obWnd.Attach((HWND)lParam);
		//CDCHandle obDC((HDC)wParam);

		//obDC.SetTextColor( RGB(255, 0, 0) );
		//// obDC.SetBkMode(OPAQUE);
		//// obDC.SetBkColor( TRANSPARENT );
		//HBRUSH hBr = NULL;
		
		if ((HWND)lParam == this->GetDlgItem(ID_GA).m_hWnd) {
			SetBkMode((HDC)wParam, TRANSPARENT); // transparent background			
			SetTextColor((HDC)wParam, stockUpdater->changeColor == 1 ? RGB(0, 255, 0) : RGB(0, 0, 0)); // white text
		}

		return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
	}


	//HBRUSH CMyDialog::OnCtlColor(CDC* pDC, CWnd *pWnd, UINT nCtlColor)
	//{
	//	switch (nCtlColor)
	//	{
	//	case CTLCOLOR_STATIC:
	//		pDC->SetTextColor(RGB(255, 0, 0));
	//		return (HBRUSH)GetStockObject(NULL_BRUSH);
	//	default:
	//		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	//	}
	//}
};
