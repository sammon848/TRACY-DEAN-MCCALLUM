#include "CalculatorApp.h"
#include "CalculatorMainFrame.h"

BEGIN_MESSAGE_MAP(CalculatorApp, CWinApp)
END_MESSAGE_MAP()

CalculatorApp theApp;

CalculatorApp::CalculatorApp() {}

BOOL CalculatorApp::InitInstance() {
    CWinApp::InitInstance();

    CalculatorMainFrame* pFrame = new CalculatorMainFrame();
    m_pMainWnd = pFrame;

    pFrame->LoadFrame(IDR_MAINFRAME);
    pFrame->ShowWindow(SW_SHOW);
    pFrame->UpdateWindow();

    return TRUE;
}