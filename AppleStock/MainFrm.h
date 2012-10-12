// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlstr.h>
#include <atlmisc.h>
#include "aboutdlg.h"
#include "TestBrowserView.h"
#include "TestBrowserForm.h"
#include "AppleStockUpdater.h"
#include "windowfont.h"
#pragma once

class CMainFrame : public CFrameWindowImpl<CMainFrame>, 
	public CUpdateUI<CMainFrame>,
	public CMessageFilter, public CIdleHandler
{
public:

	DECLARE_FRAME_WND_CLASS(NULL, NULL)

	struct _RunData
	{
		HWND CMainFrameHandle;
	};

	CAppleStockView m_view;
	HWND browserWindowHandle;
	AppleStockUpdater appleStockUpdater;
	CWindowFont m_fontBold;

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
			return TRUE;

		return m_view.PreTranslateMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CMainFrame)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SET_BROWSER, OnMyMessage)
		MESSAGE_HANDLER(WM_OPEN_BROWSER, OnOpenBrowser)
		MESSAGE_HANDLER(WM_SET_STOCK, OnSetStock)
		MESSAGE_HANDLER(WM_SET_STOCK_COLOR, OnSetStockColor)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNew)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(ID_OPENBROWSER, OnOpenBrowser)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()


	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)



	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		ModifyStyle(WS_MAXIMIZEBOX, NULL, NULL);
		ModifyStyle(WS_THICKFRAME, NULL, NULL);

		appleStockUpdater = AppleStockUpdater();
		appleStockUpdater.CMainFrameHandle = m_hWnd;
		appleStockUpdater.StartThread();
		appleStockUpdater.stockPrice = "Please wait...";

		

		m_hWndClient = m_view.Create(m_hWnd);
		m_view.stockUpdater = &appleStockUpdater;

		m_fontBold = CWindowFont();
		m_fontBold.Apply(m_view.m_hWnd, CWindowFont::typeBold | CWindowFont::typeDoubleHeight , ID_GA);
	

		// omg.SubclassDlgItem(ID_GA, m_view);
		m_view.mainFrameHandle = m_hWnd;
		//CFont m_Font1;
		//m_Font1.CreatePointFont(16, _T("Arial"));
		//m_view.GetDlgItem(ID_HEADER).SetFont(m_Font1);
		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		// unregister message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(this);
		pLoop->RemoveIdleHandler(this);

		bHandled = FALSE;
		return 1;
	}

	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		PostMessage(WM_CLOSE);
		return 0;
	}

	LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: add code to initialize document

		return 0;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnOpenBrowser(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{	
		OpenBrowser();
		return 0;
	}

	LRESULT OnOpenBrowser(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{	
		OpenBrowser();
		return 0;
	}

	void OpenBrowser() {
		if (browserWindowHandle == NULL || ::IsWindow(browserWindowHandle) == FALSE) {
			DWORD dwThreadID;
			_RunData* pData = new _RunData;
			pData->CMainFrameHandle = m_hWnd;
			::PostMessage(m_hWnd, WM_SET_STOCK_COLOR, NULL, (LPARAM) RGB(0,255,0));
			HANDLE hThread = ::CreateThread(NULL, 0, RunThread, pData, 0, &dwThreadID);
		}
		else {
			::BringWindowToTop(browserWindowHandle);
		}
	}

	LRESULT OnSetStock(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{	
		HWND gaHandle = ::GetDlgItem(m_hWnd, ID_GA);
		m_view.SetDlgItemText(ID_GA, appleStockUpdater.stockPrice);
		return 0;
	}

	LRESULT OnMyMessage(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/) {
		browserWindowHandle = (HWND) wParam;
		WTL::CString changeText = "Browser was launched!";
		HWND gaHandle = ::GetDlgItem(m_hWnd, ID_GA);
		m_view.SetDlgItemText(ID_GA, changeText);

		return 0;
	}

	static DWORD WINAPI RunThread(LPVOID lpData)
	{
		CMessageLoop theLoop;
		CBrowserFrame wndFrame;
		_RunData* pData = (_RunData*)lpData;

		if(wndFrame.CreateEx() == NULL)
		{
			ATLTRACE(_T("Frame window creation failed!\n"));
			return 0;
		}


		HWND hMainFrame = reinterpret_cast<HWND>(pData->CMainFrameHandle);
		::PostMessage(hMainFrame, WM_SET_BROWSER, (WPARAM)wndFrame.m_hWnd, NULL);

		wndFrame.ShowWindow(TRUE);
		::SetForegroundWindow(wndFrame);	// Win95 needs this

		int nRet = theLoop.Run();

		free(pData);

		::PostMessage(hMainFrame, WM_SET_BROWSER, (WPARAM) NULL, NULL);

		return nRet;
	}

	LRESULT OnSetStockColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{	
		CStatic staticLabel = m_view.GetDlgItem(ID_GA);
		return 1;
	}
};