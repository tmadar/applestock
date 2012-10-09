// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CBrowserFrame : 
	public CFrameWindowImpl<CBrowserFrame>, 
	public CUpdateUI<CBrowserFrame>,
	public CMessageFilter, public CIdleHandler
{
public:
	CTestBrowserView m_view;

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if(CFrameWindowImpl<CBrowserFrame>::PreTranslateMessage(pMsg))
			return TRUE;

		return m_view.PreTranslateMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CBrowserFrame)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CBrowserFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		CHAIN_MSG_MAP(CUpdateUI<CBrowserFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CBrowserFrame>)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{

		m_hWndClient = m_view.Create(m_hWnd, rcDefault, _T("https://www.google.com/finance?client=ob&q=NASDAQ:AAPL"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL, WS_EX_CLIENTEDGE);
		// register object for message filtering and idle updates
		// CMessageLoop* pLoop = _Module.GetMessageLoop();
		// ATLASSERT(pLoop != NULL);
		// pLoop->AddMessageFilter(this);
		// pLoop->AddIdleHandler(this);
		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		// unregister message filtering and idle updates
		// CMessageLoop* pLoop = _Module.GetMessageLoop();
		// ATLASSERT(pLoop != NULL);
		// pLoop->RemoveMessageFilter(this);
		// pLoop->RemoveIdleHandler(this);

		bHandled = FALSE;
		return 1;
	}
};
