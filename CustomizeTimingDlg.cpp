//#include "stdafx.h"
//#include "CustomizeTimingDlg.h"
//#include "EasyProjDlg.h"
//#include "EasyProj.h"
//#include "afxdialogex.h"
//
////IMPLEMENT_DYNAMIC(CEasyProjDlg, CDialogEx);
//
//CustomizeTimingDlg::CustomizeTimingDlg(int num_sequences, int num_pic_per_seq, CWnd* pParent)
//	: CDialogEx(IDD_TIMING_DIALOG, pParent), num_seq(num_sequences), num_pic(num_pic_per_seq) {}
//
//void CustomizeTimingDlg::DoDataExchange(CDataExchange* pDX) {
//	CDialogEx::DoDataExchange(pDX);
//}
//
//BEGIN_MESSAGE_MAP(CustomizeTimingDlg, CDialogEx)
//END_MESSAGE_MAP()
//
//BOOL CustomizeTimingDlg::OnInitDialog() {
//	CDialogEx::OnInitDialog();
//	int startX = 10;
//	int startY = 20;
//	int boxWidth = 50;
//	int boxHeight = 20;
//	int offsetX = 30;
//	int offsetY = 60;
//
//	fields.resize(num_seq, std::vector<CEdit*>(num_pic, nullptr));
//	m_values.resize(num_seq, std::vector<int>(num_pic));
//
//	for (int row = 0; row < num_seq; ++row) {
//		for (int col = 0; col < num_pic; ++col) {
//			CEdit* pEdit = new CEdit();
//			pEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
//				CRect(startX + col * offsetX, startY + row * offsetY, startX + col * offsetX + boxWidth, startY + row * offsetY + boxHeight),
//				this, IDC_TIMING_VALUE + row * num_pic + col);
//			fields[row][col] = pEdit;
//		}
//	}
//	return TRUE;
//}
//
//void CustomizeTimingDlg::OnOK() {
//	for (int row = 0; row < num_seq; ++row) {
//		for (int col = 0; col < num_pic; ++col) {
//			BOOL success = FALSE;
//			int controlID = IDC_TIMING_VALUE + row * num_pic + col;
//			int value = GetDlgItemInt(controlID, &success);
//			if (!success) {
//				AfxMessageBox(_T("Please enter a valid integer"));
//				value = 0;
//			}
//
//			m_values[row][col] = value;
//
//		}
//	}
//}
//
//
//
//
