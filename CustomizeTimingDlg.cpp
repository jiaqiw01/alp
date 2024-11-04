#include "stdafx.h"
#include "CustomizeTimingDlg.h"
#include "EasyProj.h"
#include "afxdialogex.h"
//#include "EasyProjDlg.h"
IMPLEMENT_DYNAMIC(CustomizeTimingDlg, CDialogEx);

CustomizeTimingDlg::CustomizeTimingDlg(int num_pic, std::vector<CString> fnames, CWnd* pParent)
	: CDialogEx(IDD_TIMING_DIALOG, pParent), num_pic(num_pic), fnames(fnames) {}

void CustomizeTimingDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CustomizeTimingDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CustomizeTimingDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	int startX = text_startX;
	int startY = text_startY;
	int boxWidth = 80;
	int boxHeight = 60;
	int offsetX = 120;
	int offsetY = 200 / num_pic;

	fields.resize(num_pic, std::vector<CEdit*>(2, nullptr));
	m_values.resize(num_pic, std::vector<int>(2));
    // create labels
	int leftOffset = startX;
	int vertOffset = 50;
	CRect labelRect(leftOffset, vertOffset, leftOffset + boxWidth, vertOffset + boxHeight);
	CStatic* plabel = new CStatic();
	CString labelText = _T("ON (ms)");
	plabel->Create(labelText, WS_CHILD | WS_VISIBLE, labelRect, this);
	leftOffset = leftOffset + offsetX;
	CRect labelRect2(leftOffset, vertOffset, leftOffset + boxWidth, vertOffset + boxHeight);
	plabel = new CStatic();
	labelText = _T("OFF (ms)");
	plabel->Create(labelText, WS_CHILD | WS_VISIBLE, labelRect2, this);

	leftOffset = 50;
	vertOffset = startY + 20;
	int width = 150;
	for (int i = 0; i < num_pic; ++i) {
		CRect labelRect(leftOffset, vertOffset, leftOffset + width, vertOffset + boxHeight);
		CStatic* plabel = new CStatic();
		CString labelText;
		labelText.Format(_T("Image %d"), i + 1);
		plabel->Create(labelText, WS_CHILD | WS_VISIBLE, labelRect, this);
		vertOffset = vertOffset + offsetY + boxHeight;
	}

	for (int row = 0; row < num_pic; ++row) {
		for (int col = 0; col < 2; ++col) {
			CEdit* pEdit = new CEdit();
			pEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
				CRect(startX + col * offsetX, startY + row * offsetY, startX + col * offsetX + boxWidth, startY + row * offsetY + boxHeight),
				this, IDC_TIMING_VALUE + row * num_pic + col);
			fields[row][col] = pEdit;
		}
		startY += boxHeight;
	}
	return TRUE;
}

void CustomizeTimingDlg::OnOK() {
	for (int row = 0; row < num_pic; ++row) {
		for (int col = 0; col < 2; ++col) {
			BOOL success = FALSE;
			int controlID = IDC_TIMING_VALUE + row * num_pic + col;
			// Check if GetDlgItemInt was unsuccessful and set default value
			int value = GetDlgItemInt(controlID, &success);
			if (!success || value <= 0) {
				value = 1; // Default value
				MessageBox(_T("Please enter all numbers..."), _T("Input Error"), MB_OK | MB_ICONWARNING);
				return;
			}
			m_values[row][col] = value;
		}
	}
	CDialogEx::OnOK();
}

void CustomizeTimingDlg::OnPaint() {
	CPaintDC dc(this);

	Gdiplus::Graphics graphics(dc.m_hDC);
	const int thumbWidth = 100;
	const int thumbHeight = 100;

	int startX = img_startX;
	int startY = img_startY;

	int offsetY = 100 / num_pic;
	
	for (auto &fname : fnames) {
		Gdiplus::Bitmap b(fname);
		if (b.GetLastStatus() != Gdiplus::Ok) {
			return;
		}
		
		graphics.DrawImage(&b, startX, startY, thumbWidth, thumbHeight);
		startY = startY + thumbHeight + offsetY;
	}
}



