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
	CustomizeTimingDlg(int num_pic, std::vector<CString> fnames, BOOL multiplex, CWnd* pParent = nullptr);
	CustomizeTimingDlg(int num_pic, std::vector<CString> fnames, BOOL multiplex, int record_idx, CWnd* pParent = nullptr);
	CustomizeTimingDlg(int num_pic, std::vector<CString> fnames, BOOL multiplex, int record_idx, std::vector<std::vector<int>> timings, CWnd* pParent = nullptr);
	~CustomizeTimingDlg();
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
	int record_idx;
	int text_startX = 200;
	int text_startY = 100;
	int img_startX = 500;
	int img_startY = 100;
	int thumb_height = 100;
	int thumb_width = 100;
	int button_height = 50;
	int button_width = 100;
	int curr_x;
	int curr_y;
	BOOL multiplex_mode;
	std::vector<std::vector<CEdit*>> fields;
	std::vector<std::vector<int>> m_values;
	std::vector<CString> fnames;
	void CreateRadioButtons(int startX, int startY);
	void AdjustDialogSize();
	std::vector<CButton*> m_radioButtons;
	std::vector<CStatic*> labels;
	std::vector<CEdit*> edits;

public:
	std::vector<std::vector<int>> get_values() const { return m_values; }
	virtual void OnOK();
	int get_record_index() { return record_idx; }

};

