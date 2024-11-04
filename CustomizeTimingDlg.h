#pragma once
#include "afxwin.h"
#include "PlusGdi.h"	// GDI+
#include "afxcmn.h"
#include <vector>
#include "resource.h"

class CustomizeTimingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CustomizeTimingDlg);

public:
	CustomizeTimingDlg(int num_pic, std::vector<CString> fnames, CWnd* pParent = nullptr);

	// Dialog Data

	enum { IDD = IDD_TIMING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Implementation
protected:
	virtual BOOL OnInitDialog();
	virtual void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	int num_pic;
	int text_startX = 200;
	int text_startY = 100;
	int img_startX = 500;
	int img_startY = 100;
	std::vector<std::vector<CEdit*>> fields;
	std::vector<std::vector<int>> m_values;
	std::vector<CString> fnames;

public:
	std::vector<std::vector<int>> get_values() const { return m_values; }
	virtual void OnOK();

};

