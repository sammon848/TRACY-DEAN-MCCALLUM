#include "CalculatorMainFrame.h"
#include "CalculatorView.h"

BEGIN_MESSAGE_MAP(CalculatorMainFrame, CFrameWnd)
    ON_WM_CREATE()
END_MESSAGE_MAP()

CalculatorMainFrame::CalculatorMainFrame() {}

int CalculatorMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
        CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL)) {
        return -1;
    }

    return 0;
}

BOOL CalculatorMainFrame::PreCreateWindow(CREATESTRUCT& cs) {
    if (!CFrameWnd::PreCreateWindow(cs))
        return FALSE;

    cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME | 
               WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

    return TRUE;
}