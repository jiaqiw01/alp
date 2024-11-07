#include "stdafx.h"
#include "CustomizeTimingDlg.h"
#include "EasyProj.h"
#include "afxdialogex.h"
//#include "EasyProjDlg.h"
IMPLEMENT_DYNAMIC(CustomizeTimingDlg, CDialogEx);

CustomizeTimingDlg::CustomizeTimingDlg(int num_pic, std::vector<CString> fnames, CWnd* pParent)
	: CDialogEx(IDD_TIMING_DIALOG, pParent), num_pic(num_pic), fnames(fnames) {}

CustomizeTimingDlg::CustomizeTimingDlg(int num_pic, std::vector<CString> fnames, int record_idx, CWnd* pParent)
	: CDialogEx(IDD_TIMING_DIALOG, pParent), num_pic(num_pic), record_idx(record_idx), fnames(fnames) {}

CustomizeTimingDlg::CustomizeTimingDlg(int num_pic, std::vector<CString> fnames, int record_idx, std::vector<std::vector<int>> timings, CWnd* pParent)
	: CDialogEx(IDD_TIMING_DIALOG, pParent), num_pic(num_pic), fnames(fnames), m_values(timings), record_idx(record_idx) {}

void CustomizeTimingDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CustomizeTimingDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CustomizeTimingDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	if (num_pic == 0) {
		return TRUE;
	}

	int startX = text_startX;
	int startY = text_startY;
	int boxWidth = 80;
	int boxHeight = 60;
	int offsetX = 120;
	int offsetY = 200 / num_pic;

	fields.resize(num_pic, std::vector<CEdit*>(2, nullptr));
	if (m_values.empty()) {
		m_values.resize(num_pic, std::vector<int>(2));
	}
    // create labels
	int leftOffset = startX;
	int vertOffset = 50;
	CRect labelRect(leftOffset, vertOffset, leftOffset + boxWidth, vertOffset + boxHeight);
	CStatic* plabel = new CStatic();
	CString labelText = _T("ON ( / base)");
	plabel->Create(labelText, WS_CHILD | WS_VISIBLE, labelRect, this);
	labels.push_back(plabel);

	leftOffset = leftOffset + offsetX;
	CRect labelRect2(leftOffset, vertOffset, leftOffset + boxWidth, vertOffset + boxHeight);
	plabel = new CStatic();
	labelText = _T("OFF ( / base)");
	plabel->Create(labelText, WS_CHILD | WS_VISIBLE, labelRect2, this);
	labels.push_back(plabel);

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
		labels.push_back(plabel);

	}

	for (int row = 0; row < num_pic; ++row) {
		for (int col = 0; col < 2; ++col) {
			CEdit* pEdit = new CEdit();
			pEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
				CRect(startX + col * offsetX, startY + row * offsetY, startX + col * offsetX + boxWidth, startY + row * offsetY + boxHeight),
				this, IDC_TIMING_VALUE + row * num_pic + col);
			if (m_values[row][col] != 0) {
				CString strValue;
				strValue.Format(_T("%d"), m_values[row][col]);  // Convert the integer to a CString
				pEdit->SetWindowText(strValue);  // Set the converted CString as the text
			}
			else {
				pEdit->SetWindowText(_T("1"));
			}
			fields[row][col] = pEdit;
			edits.push_back(pEdit);
		}
		startY += boxHeight;
	}

	CreateRadioButtons(img_startX + 150, img_startY);
	//Adjust
	return TRUE;
}

void CustomizeTimingDlg::AdjustDialogSize()
{
	int maxWidth = curr_x;
	int maxHeight = curr_y;

	// Add some padding
	maxWidth += 20;
	maxHeight += 20;

	// Resize the dialog
	SetWindowPos(NULL, 0, 0, maxWidth, maxHeight, SWP_NOMOVE | SWP_NOZORDER);
	Invalidate();
	UpdateWindow();
}



void CustomizeTimingDlg::CreateRadioButtons(int startX, int startY) {
	// Starting position for the radio buttons
	int buttonWidth = button_width;
	int buttonHeight = button_height;
	int offsetY = thumb_height + 30;
	int verticalSpacing = offsetY;

	// Loop to create the radio buttons
	for (int i = 0; i < num_pic; ++i)
	{
		// Create a new CButton object
		CButton* pRadioButton = new CButton();

		// Generate a unique ID for each radio button
		UINT buttonID = 2000 + i;  // IDs should be unique
		// Create the radio button
		pRadioButton->Create(
			L"Record",  // Button text
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,  // Styles
			CRect(startX, startY + (i * verticalSpacing), startX + buttonWidth, startY + (i * verticalSpacing) + buttonHeight),
			this,  // Parent window (the dialog)
			buttonID  // Unique ID
		);

		// Add the button to your dialog
		m_radioButtons.push_back(pRadioButton);

	}

	// Optionally, set the first radio button as checked
	if (!m_radioButtons.empty() && record_idx == 0)
	{
		m_radioButtons[0]->SetCheck(BST_CHECKED);
	}
	else if (record_idx != 0){
		m_radioButtons[record_idx - 1]->SetCheck(BST_CHECKED);
	}
	//curr_x = startX;
	//curr_y = startY;
}

	// Destructor to clean up dynamically allocated memory
CustomizeTimingDlg::~CustomizeTimingDlg()
{
	for (CButton* button : m_radioButtons)
	{
		delete button;
	}
	for (CStatic* stat : labels) {
		delete stat;
	}
	for (CEdit* edit : edits) {
		delete edit;
	}
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
	//check which image gets selected
	int selectedButtonIndex = -1; 

	for (size_t i = 0; i < m_radioButtons.size(); ++i)
	{
		if (m_radioButtons[i]->GetCheck() == BST_CHECKED)
		{
			selectedButtonIndex = static_cast<int>(i);
			break; 
		}
	}

	if (selectedButtonIndex != -1)
	{
		record_idx = selectedButtonIndex + 1; //back to 1-indexed
	}
	else
	{
		// No button is selected
		MessageBox(_T("No button is selected"), _T("Info"), MB_OK);
		return;
	}

	CDialogEx::OnOK();
}

void CustomizeTimingDlg::OnPaint() {
	CPaintDC dc(this);

	Gdiplus::Graphics graphics(dc.m_hDC);
	const int thumbWidth = thumb_width;
	const int thumbHeight = thumb_height;

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



