#include "CalculatorView.h"
#include "Calculator.h"

BEGIN_MESSAGE_MAP(CalculatorView, CView)
    ON_COMMAND(IDC_BUTTON_CALCULATE, &CalculatorView::OnCalculate)
END_MESSAGE_MAP()

CalculatorView::CalculatorView() {}

void CalculatorView::OnDraw(CDC* /*pDC*/) {
    // Drawing code here
}

void CalculatorView::OnCalculate() {
    // Calculation logic here
}