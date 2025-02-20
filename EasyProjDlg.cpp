//
// EasyProjDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EasyProj.h"
#include "EasyProjDlg.h"
#include "afxdialogex.h"
#include "CustomizeTimingDlg.h"
#include <memory>
#include <iostream>

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

GDIPLUS_APP;									// start GDI+

// CEasyProjDlg dialog

CEasyProjDlg::CEasyProjDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEasyProjDlg::IDD, pParent)
	, m_ProjectorSerial(_T(""))
	, m_SequenceLoadedImages(_T(""))
	, m_iProjType(0)
	, m_ColourComponents(1)
	, m_iLedBrightness(0)
	, m_iLEDType(0)
	, m_SequenceBitnum(_T("1"))
	, m_Led1Temperature(_T(""))
	, m_Led2Temperature(_T(""))
	, m_Led3Temperature(_T(""))
	, m_LedEnableMode( GATE_LOW )
	, m_PictureTime(0)
	, m_LedOnTime(0)
	, m_ProjectorDmdSize(_T(""))
	, m_iMaster(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_OnTimerErrors.ResetErrors();
}

void CEasyProjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_PROJ_NONE, m_RadioBtnProjTypeNone);
	DDX_Control(pDX, IDC_RADIO_PROJ_STAR_07, m_RadioBtnProjTypeStar07);
	DDX_Control(pDX, IDC_RADIO_PROJ_STAR_07_RGB, m_RadioBtnProjTypeStar07RGB);
	DDX_Control(pDX, IDC_RADIO_PROJ_V_MODULE, m_RadioBtnProjTypeVModule);
	DDX_Text(pDX, IDC_SERIAL, m_ProjectorSerial);
	DDX_Control(pDX, IDC_SEQ_LOAD, m_BtnSequenceLoad);
	DDX_Control(pDX, IDC_SEQ_FREE, m_BtnSeqFree);
	DDX_Control(pDX, IDC_PREVIEW, m_Preview);
	DDX_Text(pDX, IDC_SEQ_IMAGES, m_SequenceLoadedImages);
	DDX_Control(pDX, IDC_ILLU_TIME, m_EditIlluminateTime);
	DDX_Control(pDX, IDC_PIC_TIME, m_EditPictureTime);
	//newly added
	DDX_Control(pDX, IDC_SET_REP, m_EditNumRepetition);
	DDX_Control(pDX, IDC_SET_CUSTOMIZED, m_EditSetting);
	DDX_Control(pDX, IDC_MULTIPLEX_MODE, m_MultiplexMode);
	DDX_Control(pDX, IDC_SEQ_MODE, m_SeqMode);
	DDX_Control(pDX, IDC_PREVIEW_RECORD, m_PreviewRecord);
	//DDX_Control(pDX, IDC_RADIO_SET_MASTER_MODE, m_BtnMasterMode);
	DDX_Control(pDX, IDC_PROJ_START, m_BtnProjection);
	DDX_Control(pDX, IDC_SET_MULTIPLEX, m_EditNumMultiplex);
	DDX_Control(pDX, IDC_SET_RECORD_IDX, m_EditRecordIdx);
	// end of added
	DDX_Control(pDX, IDC_PROJ_STOP, m_BtnProjStop);
	DDX_Control(pDX, IDC_SET_SEQ_PARAM, m_BtnSet);
	DDX_Control(pDX, IDC_SLIDER_LED_BRIGHTNESS, m_sldLedBrightness);
	DDX_Slider(pDX, IDC_SLIDER_LED_BRIGHTNESS, m_iLedBrightness);
	DDX_Control(pDX, IDC_RADIO_LED_NONE, m_RadioBtnLEDTypeNone);
	DDX_Control(pDX, IDC_RADIO_LED_RED, m_RadioBtnLEDTypeRed);
	DDX_Control(pDX, IDC_RADIO_LED_GREEN, m_RadioBtnLEDTypeGreen);
	DDX_Control(pDX, IDC_RADIO_LED_BLUE_TE, m_RadioBtnLEDTypeBlueTE);
	DDX_Control(pDX, IDC_RADIO_LED_UV, m_RadioBtnLEDTypeUV);
	DDX_Control(pDX, IDC_RADIO_LED_CBT_140_WHITE, m_RadioBtnLEDTypeCBT140White);
	DDX_Text(pDX, IDC_LED1_TEMPERATURE, LedTemperature(1));
	DDX_Text(pDX, IDC_LED2_TEMPERATURE, LedTemperature(2));
	DDX_Text(pDX, IDC_LED3_TEMPERATURE, LedTemperature(3));
	DDX_Radio(pDX, IDC_RADIO_PROJ_NONE, m_iProjType);
	DDX_Radio(pDX, IDC_RADIO_LED_NONE, m_iLEDType);
	//DDX_Radio(pDX, IDC_RADIO_SET_MASTER_MODE, m_iMaster);
	DDX_Text(pDX, IDC_EDIT_REPORT_BITNUM, m_SequenceBitnum);
	DDX_Control(pDX, IDC_CHECK_PIC_TIME, m_CheckPictureTime);
	DDX_Control(pDX, IDC_CHECK_ILLU_TIME, m_CheckIlluminateTime);
	DDX_Control(pDX, IDC_CHECK_FLIP, m_CheckFlip);
	DDX_Text(pDX, IDC_DMD_SIZE, m_ProjectorDmdSize);
}

BEGIN_MESSAGE_MAP(CEasyProjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_PROJ_NONE, &CEasyProjDlg::OnBnClickedRadioProjNone)
	ON_BN_CLICKED(IDC_RADIO_PROJ_STAR_07, &CEasyProjDlg::OnBnClickedRadioProjStar07)
	ON_BN_CLICKED(IDC_RADIO_PROJ_STAR_07_RGB, &CEasyProjDlg::OnBnClickedRadioProjStar07RGB)
	ON_BN_CLICKED(IDC_RADIO_PROJ_V_MODULE, &CEasyProjDlg::OnBnClickedRadioProjAlpOnly)
	ON_BN_CLICKED(IDC_SEQ_LOAD, &CEasyProjDlg::OnBnClickedSeqLoad)
	ON_BN_CLICKED(IDC_SEQ_FREE, &CEasyProjDlg::OnBnClickedSeqFree)
	//newly added
	//master mode
	//slave mode
	ON_BN_CLICKED(IDC_RADIO_SET_SLAVE_MODE, &CEasyProjDlg::OnBnClickedSetSlave)
	ON_BN_CLICKED(IDC_SET_CUSTOMIZED, &CEasyProjDlg::OnBnClickedEditTiming)
	//set num repetition
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SET_SEQ_PARAM, &CEasyProjDlg::OnBnClickedSetSeqParam)
	ON_BN_CLICKED(IDC_PROJ_START, &CEasyProjDlg::OnBnClickedProjStart)
	ON_BN_CLICKED(IDC_PROJ_STOP, &CEasyProjDlg::OnBnClickedProjStop)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RADIO_LED_NONE, &CEasyProjDlg::OnBnClickedRadioLedNone)
	ON_BN_CLICKED(IDC_RADIO_LED_RED, &CEasyProjDlg::OnBnClickedRadioLedRed)
	ON_BN_CLICKED(IDC_RADIO_LED_GREEN, &CEasyProjDlg::OnBnClickedRadioLedGreen)
	ON_BN_CLICKED(IDC_RADIO_LED_BLUE_TE, &CEasyProjDlg::OnBnClickedRadioLedBlueTe)
	ON_BN_CLICKED(IDC_RADIO_LED_UV, &CEasyProjDlg::OnBnClickedRadioLedUv)
	ON_BN_CLICKED(IDC_RADIO_LED_CBT_140_WHITE, &CEasyProjDlg::OnBnClickedRadioLedCbt140White)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_PIC_TIME, &CEasyProjDlg::OnBnClickedCheckPicTime)
	ON_BN_CLICKED(IDC_CHECK_ILLU_TIME, &CEasyProjDlg::OnBnClickedCheckIlluTime)
	ON_BN_CLICKED(IDC_CHECK_FLIP, &CEasyProjDlg::OnBnClickedCheckFlip)
	ON_BN_CLICKED(IDHELP, &CEasyProjDlg::OnBnClickedHelp)
END_MESSAGE_MAP()


//newly added
void CEasyProjDlg::OnBnClickedEditTiming() {
	UpdateData(TRUE);
	if (!timing_vals.empty()) {
		record_idx = GetDlgItemInt(IDC_SET_RECORD_IDX);
		CustomizeTimingDlg timing_dlg(num_images, fnames, m_MultiplexMode.GetCheck(), record_idx, timing_vals);
		if (timing_dlg.DoModal() == IDOK) {
			std::vector<std::vector<int>> updated_timing_vals = timing_dlg.get_values();
			if (timing_vals != updated_timing_vals) {
				timing_vals = updated_timing_vals;
			}
			int record_idx = timing_dlg.get_record_index();
			SetDlgItemInt(IDC_SET_RECORD_IDX, record_idx);
			record_idx = record_idx;
		}
	}
	else {
		CustomizeTimingDlg timing_dlg(num_images, fnames, m_MultiplexMode.GetCheck(), record_idx);
		if (timing_dlg.DoModal() == IDOK) {
			std::vector<std::vector<int>> updated_timing_vals = timing_dlg.get_values();
			if (timing_vals != updated_timing_vals) {
				timing_vals = updated_timing_vals;
			}
			int record_idx = timing_dlg.get_record_index();
			SetDlgItemInt(IDC_SET_RECORD_IDX, record_idx);
			record_idx = record_idx;
		}
	}
	//change preview
	SetRecordPreview();
}
	

void CEasyProjDlg::OnBnClickedSetSlave() {
	CString exErrorMessage;
	int ret = m_Projector.SetMasterControl(&exErrorMessage);
	// set error message display, TODO
}



//end of added

// CEasyProjDlg message handlers

BOOL CEasyProjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog. The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// -----
	m_CheckPictureTime.SetCheck( BST_CHECKED );
	UpdateElements();													// update all dialog elements from data
	// -----

	m_bOnTimerIsModal = FALSE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CEasyProjDlg::OnDestroy()
{
	// free sequence and projector before the application is finished
	m_Projector.SequenceFree();
	m_Projector.Free();

	CDialogEx::OnDestroy();
}


void CEasyProjDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEasyProjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEasyProjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


////////////////////////////////////////////////////////////////////////////////


// check return codes and output error messages (not all features of the function are currently used)
void CEasyProjDlg::SetProjectorReturnCodeMsg( const int retCode, const int errorType, CString exErrorMessage)
{
	CString strReport;

	m_Projector.GetErrorMessage( retCode, strReport.GetBuffer( 512), 512);
	strReport.ReleaseBuffer();
	strReport.Format(exErrorMessage + L"\nErrorcode %d : " + strReport, retCode);

	if( ALP_DEVICE_REMOVED == retCode)
		m_Projector.Free();


	if( ALP_OK != retCode)
	{
		if( FAILURE == errorType)												// a failure will cause the programm to be reset
		{
			Reset();															// reset the programm to "no projector"
			MessageBeep( MB_ICONERROR );
			MessageBox( strReport + L"\nProgram will be reset.", L"Error",  MB_ICONSTOP);
		}
		else if (WARNING == errorType)											// in case of a warning the programm will resume
		{
			MessageBeep( MB_ICONERROR );
			MessageBox( strReport + L"\nProgram will be resumed.", L"Error",  MB_ICONEXCLAMATION);
		}
		else
			throw;
	}
}

void CEasyProjDlg::Reset()
{
	m_iProjType = CProjector::PROJECTOR_TYPE_NONE;
	UpdateData( FALSE);													// update direction: data -> dialog elements
	BnClickedRadioProjectorType();	
}

// update all dialog elements from data
void CEasyProjDlg::UpdateElements(void)
{
	BOOL const bValidProjector = m_Projector.IsConnected(),
		bValidSeqence = bValidProjector && m_Projector.IsValidSequence();
	BOOL bValidStar07 = bValidProjector && CProjector::PROJECTOR_TYPE_STAR_07 == m_Projector.GetProjectorType();

	// Always enable device selection
	m_RadioBtnProjTypeNone.EnableWindow();
	m_RadioBtnProjTypeStar07.EnableWindow();
	m_RadioBtnProjTypeStar07RGB.EnableWindow();
	m_RadioBtnProjTypeVModule.EnableWindow();
	
	// Dynamically enable LED selection
	m_RadioBtnLEDTypeNone.EnableWindow(bValidStar07 && !m_Projector.Led(1).IsValid());
	m_RadioBtnLEDTypeRed.EnableWindow(bValidStar07 && !m_Projector.Led(1).IsValid());
	m_RadioBtnLEDTypeGreen.EnableWindow(bValidStar07 && !m_Projector.Led(1).IsValid());
	m_RadioBtnLEDTypeBlueTE.EnableWindow(bValidStar07 && !m_Projector.Led(1).IsValid());
	m_RadioBtnLEDTypeUV.EnableWindow(bValidStar07 && !m_Projector.Led(1).IsValid());
	m_RadioBtnLEDTypeCBT140White.EnableWindow(bValidStar07 && !m_Projector.Led(1).IsValid());

	m_sldLedBrightness.EnableWindow( m_Projector.Led(1).IsValid() || m_Projector.Led(2).IsValid() || m_Projector.Led(3).IsValid());
	m_EditSetting.EnableWindow( num_images != 0);
	m_BtnSequenceLoad.EnableWindow( bValidProjector);
	m_BtnSeqFree.EnableWindow( bValidSeqence );

	// Dynamically enable timing setting controls
	//m_CheckPictureTime.EnableWindow( bValidSeqence );
	//m_EditPictureTime.EnableWindow( bValidSeqence && m_CheckPictureTime.GetCheck() );
	//m_CheckIlluminateTime.EnableWindow( bValidSeqence );
	//m_EditIlluminateTime.EnableWindow( bValidSeqence && m_CheckIlluminateTime.GetCheck() );
	//m_EditNumMultiplex.EnableWindow(bValidSeqence);
	//m_EditNumRepetition.EnableWindow(bValidSeqence);
	//m_EditRecordIdx.EnableWindow(bValidSeqence);
	//m_BtnProjection.EnableWindow( bValidSeqence);
	//m_BtnProjStop.EnableWindow( bValidSeqence);
	m_BtnSet.EnableWindow( FALSE );
	//m_CheckFlip.EnableWindow( bValidProjector );
	m_CheckFlip.SetCheck( m_Projector.GetFlip() );

	UpdateData( FALSE);													// update direction: data -> dialog elements
}

// get projector properties and update dialog elements
const int CEasyProjDlg::GetProjectorProperties(CString *errorMessage)
{
	CProjector::CDevProperties prop;
	int ret = m_Projector.GetDevProperties( prop, errorMessage);
	if( ALP_OK == ret)
	{
		m_ProjectorSerial.Format( _T("%d"), prop.SerialNumber);
		m_ProjectorDmdSize.Format( _T("%d x %d"), m_Projector.GetWidth(), m_Projector.GetHeight() );
	}
	return ret;
}


const int CEasyProjDlg::SetRoundRobin(CString *errorMessage)
{
	tAlpDynSynchOutGate GateConfig;
	ZeroMemory( GateConfig.Gate, sizeof GateConfig.Gate );			// all Gates are set to zero

	GateConfig.Period   = 3;
	GateConfig.Polarity = 1;

	GateConfig.Gate[0] = 1;

	int ret = m_Projector.SetSynchGate( 1, GateConfig, errorMessage);

	GateConfig.Gate[0] = 0;
	GateConfig.Gate[1] = 1;

	if(ALP_OK == ret)
		ret = m_Projector.SetSynchGate( 2, GateConfig, errorMessage);

	GateConfig.Gate[1] = 0;
	GateConfig.Gate[2] = 1;

	if(ALP_OK == ret)
		ret = m_Projector.SetSynchGate( 3, GateConfig, errorMessage);

	m_LedEnableMode = GATE_ROUND_ROBIN3;

	return ret;
}

const int CEasyProjDlg::SetConstHigh(CString *errorMessage)
{
	int ret;
	tAlpDynSynchOutGate GateConfig;
	ZeroMemory( GateConfig.Gate, sizeof GateConfig.Gate );		// all Gates are set to zero

	GateConfig.Period   = 1;
	GateConfig.Polarity = 0;

	// the Led of STAR-07 is connected to SynchGate 3
	ret = m_Projector.SetSynchGate( 3, GateConfig, errorMessage);

	m_LedEnableMode = GATE_HIGH;

	return ret;
}


void CEasyProjDlg::BnClickedRadioProjectorType()
{
	CWaitCursor WaitCursor; 

	UpdateData( TRUE);													// update direction: dialog elements -> data	
	if(m_Projector.IsConnected())
		FreeProjector();
	m_Projector.SetProjectorType(m_iProjType);
	AllocateProjector();

	if (CProjector::PROJECTOR_TYPE_STAR_07 != m_iProjType)
		m_iLEDType = 0;

	UpdateElements();													// update all dialog elements from data
}


// Sub-function
void CEasyProjDlg::BnClickedRadioLEDType()
{
	CString exErrorMessage;

	// Note: The Radio Button Index must match CProjector::GetLedTypeByIndex!

	UpdateData( TRUE);													// update direction: dialog elements -> data
	int ret = SelectLEDType( m_iLEDType);
	if( ALP_OK != ret)
		m_iLEDType = 0;
	SetProjectorReturnCodeMsg(ret, WARNING, exErrorMessage);

	m_iLedBrightness = 0;
	SetLEDBrightness( m_iLedBrightness);
	UpdateElements();													// update all dialog elements from data
}


// select the LED type
const int CEasyProjDlg::SelectLEDType( const int iLedTypeIndex, CString *errorMessage)
{
	CString exErrorMessage;
	int ret;

	if(m_Projector.Led(1).IsValid())
		{
			ret = m_Projector.Led(1).Free(&exErrorMessage);
			SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);
		}

	if( iLedTypeIndex == CProjector::LEDTYPE_0_NONE) return ALP_OK;

	ret = m_Projector.Led(1).Alloc( m_Projector.GetLedTypeByIndex( iLedTypeIndex), 0, errorMessage);

	return ret;
}


// change the LED brightness
void CEasyProjDlg::SetLEDBrightness( const int iBrightness)
{
	long ret = ALP_OK;
	CString exErrorMessage;

		if(m_Projector.Led(1).IsValid())
		{
			ret = m_Projector.Led(1).SetBrightness( iBrightness, &exErrorMessage);
			SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);
		}
		if(m_Projector.Led(2).IsValid())
		{
			ret = m_Projector.Led(2).SetBrightness( iBrightness, &exErrorMessage);
			SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);
		}
		if(m_Projector.Led(3).IsValid())
		{
			ret = m_Projector.Led(3).SetBrightness( iBrightness, &exErrorMessage);
			SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);
		}
}


// free sequence and reset dialog elements, delete all existing memories, use when need to load new images
const int CEasyProjDlg::FreeSequence(CString *errorMessage)
{
	int ret = ALP_OK;
	if( m_Projector.IsValidSequence())
	{
		ret = m_Projector.SequenceFree(errorMessage);
		if (ret != ALP_OK) {
			CString msg = _T("Sequence Freeing Exists with Error....") + *errorMessage;
			MessageBox(msg, _T("Notification"), MB_OK | MB_ICONERROR);
		}
	}
	m_SequenceLoadedImages = CString( L" ");
	SetDlgItemInt( IDC_ILLU_TIME, 1000000 );
	SetDlgItemInt( IDC_PIC_TIME, 1000000 );
	SetDlgItemInt(IDC_SET_REP, 100);
	SetDlgItemInt(IDC_SET_MULTIPLEX, 0);
	SetDlgItemInt(IDC_SET_RECORD_IDX, 0);
	SetDlgItemInt(IDC_EDIT_REPORT_BITNUM, 1);
	SetDlgItemText(IDC_ERROR_MSG, _T("NO ERROR MESSAGES NOW"));
	m_SequenceBitnum.Empty();
	fnames.clear();
	timing_vals.clear();
	num_images = 0;
	total_frames = 0;

	return ret;
}


// get sequence properties
const int CEasyProjDlg::GetSequenceProperties(CString *errorMessage)
{
	CProjector::CTimingEx timing;
	CString msg;

	int ret = m_Projector.GetSeqProperties( timing, errorMessage);
	if (ret != ALP_OK) {
		SetDlgItemText(IDC_ERROR_MSG, *errorMessage);
	}

	if( ALP_OK == ret)
	{
		SetDlgItemInt( IDC_ILLU_TIME, timing.IlluminateTime );
		SetDlgItemInt( IDC_PIC_TIME, timing.PictureTime );
		msg.Format(_T("After Get Sequence Properties, illu time %d, picture time %d"), timing.IlluminateTime, timing.PictureTime);
		MessageBox(msg, _T("Notification"), MB_OK | MB_ICONINFORMATION);
		//SetDlgItemInt( IDC_SET_REP, )
		
		// Certain timing values are required later on for LED temperature monitoring.
		m_PictureTime = timing.PictureTime;
		m_LedOnTime = timing.SynchPulseWidth;

		m_SequenceBitnum.Format( _T("%d"), timing.BitNum );
		if (timing.Uninterrupted) m_SequenceBitnum += _T(" uninterrupted");
	}
	return ret;
}




// change sequence properties
const int CEasyProjDlg::SetSequenceProperties(CString* errorMessage)
{
	UpdateData(TRUE);													// update direction: dialog elements -> data

	CProjector::CTimingEx timing;
	long image_time = 0;
	CString exErrorMessage;
	int actual_recordIdx = 0;
	int period = 0;

	// set illu = pic time by default, no dark
	if (m_CheckIlluminateTime.GetCheck()) {
		image_time = GetDlgItemInt(IDC_ILLU_TIME) > 0 ? GetDlgItemInt(IDC_ILLU_TIME) : 0;
	}
	if (m_CheckPictureTime.GetCheck()) {
		image_time = GetDlgItemInt(IDC_PIC_TIME) > 0 ? GetDlgItemInt(IDC_PIC_TIME) : 0;
	}
	timing.IlluminateTime = image_time;
	timing.PictureTime = image_time;
	timing.NumMultiplex = 0;
	timing.Repetition = GetDlgItemInt(IDC_SET_REP);

	//if multiplex mode, need to sum up all images (total_image) and set it to be the period of gate
	if (m_MultiplexMode.GetCheck()) {
		m_mode = "Multiplex";
		timing.NumMultiplex = total_frames;
		int recordIdx = GetDlgItemInt(IDC_SET_RECORD_IDX);
		record_idx = recordIdx; // 1-indexed

		// the actual record idx takes into account black frames
		for (int i = 0; i < recordIdx - 1; ++i) {
			for (int j = 0; j < 2; ++j) {
				actual_recordIdx += timing_vals[i][j];
			}
		}
		timing.RecordIdx = actual_recordIdx;

	}
	//if sequence mode, total frame is per sequence, num_multiplex not used, record index is always 0
	else {
		m_mode = "Sequential";
		_ASSERT(timing_vals.size() > 0);
		//timing.NumMultiplex = total_frames;
		int recordIdx = GetDlgItemInt(IDC_SET_RECORD_IDX);
		record_idx = recordIdx; // 1-indexed

		// the actual record idx takes into account black frames
		actual_recordIdx = 0; //record the non-black image, so it's always the first one
		timing.RecordIdx = actual_recordIdx;
		timing.NumMultiplex = total_frames * timing.Repetition;
		//m_Projector.SetReps(timing.Repetition, errorMessage);
	}

	m_Projector.SetMultiplexRecord(timing.NumMultiplex, timing.RecordIdx);
	CString message;
	message.Format(_T("Set Multiplex to %d, Record index to %d, Actual index is %d, Illuminate Time to %d, Picture time to %d"), timing.NumMultiplex, record_idx, actual_recordIdx, timing.IlluminateTime, timing.PictureTime);
	MessageBox(message, _T("Value Entered"), MB_OK | MB_ICONINFORMATION);
	
	timing.SynchDelay = 0;	//no delay

	int ret = m_Projector.SelectMaxBitnum(timing, errorMessage);
	if (ret != ALP_OK) {
		MessageBox(*errorMessage, _T("After Select Max Bitnum Notification"), MB_OK | MB_ICONINFORMATION);
	}

	if (m_SeqMode.GetCheck()) {
		period = total_frames * timing.Repetition; //only one pulse at the start, so period = length of sequence
	}
	else { //for multiplexing, period = total_frame
		period = total_frames;
	}
	CString msg;
	msg.Format(_T("Setting period = %d"), period);
	MessageBox(msg, _T("Notification"), MB_OK | MB_ICONINFORMATION);
	//synch pulse sent out at the the very first frame through GPIO, common for multiplex/sequence
	ret = m_Projector.SequenceSynchGate(period, errorMessage);
	if (ret != ALP_OK) {
		MessageBox(*errorMessage, _T("Sequence SynchGate with Error"), MB_OK | MB_ICONINFORMATION);
	}
	if (m_MultiplexMode.GetCheck()) { //in multiplex mode, need to send 2nd synch pulse at the recording frame at Gate 1
		ret = m_Projector.SetSynchGateMultiplex(errorMessage);
	}

	return ret;

}

const int CEasyProjDlg::InitializeSequenceProperties(CString* errorMessage)
{
	CProjector::CTimingEx timing; //default to 10 ms
	timing.PictureTime = 10000;
	timing.IlluminateTime = 10000;
	int ret = m_Projector.SelectMaxBitnum(timing, errorMessage);

	if (ALP_OK == ret)
		ret = GetSequenceProperties(errorMessage);

	return ret;

}

//Load images and save file names
const int CEasyProjDlg::StoreImages(CString* errorMessage) {
	const LPCTSTR filter =
		_T("All Image Files|*.tif;*.tiff;*.png;*.gif;*.bmp;*.jpg;*.jpeg|")
		_T("TIF Files for Sequence (*.tif)|*.tif|")
		_T("TIFF Files for Sequence (*.tiff)|*.tiff|");
	CFileDialog dlg(TRUE, NULL, 0, OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_NOCHANGEDIR | OFN_FILEMUSTEXIST | OFN_ENABLESIZING, filter);

	wchar_t buffer[1 << 16];
	*buffer = '\0';

	dlg.m_pOFN->lpstrFile = buffer;
	dlg.m_pOFN->nMaxFile = sizeof(buffer) / sizeof(*buffer);

	int ret = ALP_OK;
	int nImages = 0;

	if (IDOK == dlg.DoModal())											// show file open dialog
	{
		CWaitCursor WaitCursor;

		// determine the sequence length
		for (POSITION pos = dlg.GetStartPosition(); NULL != pos; )
		{
			CString fileNameLOAD = dlg.GetNextPathName(pos);
			nImages++;
		}

		if (!fnames.empty()) { //in case there are unfinished sequences or previous file names uncleared
			fnames.clear();
			if (m_Projector.IsValidSequence()) {
				m_Projector.SequenceFree(errorMessage);
			}
		}


		const int BitPlanes = 1;					

		Gdiplus::Status status;
		int k = 0;

		for (POSITION pos = dlg.GetStartPosition(); NULL != pos; )
		{
			CString fileNameLOAD = dlg.GetNextPathName(pos);

			Gdiplus::Bitmap BmpLoaded(fileNameLOAD);			// read the image from file
			
			//loaded_images.push_back(&BmpLoaded);

			fnames.push_back(fileNameLOAD);


			{	// Show progress and preview thumbnail
				m_SequenceLoadedImages.Format(_T("%d"), k + 1);	// update dialog element with current image counter

				// create a bitmap with preview dimensions
				const int thumbWidth = 176;
				const int thumbHeight = 132;
				std::auto_ptr<Gdiplus::Bitmap> pThumbBmp(new Gdiplus::Bitmap(thumbWidth, thumbHeight, PixelFormat24bppRGB));
				Gdiplus::Graphics thumbGraphics(pThumbBmp.get());	// connect the drawing area with preview


				// draw BmpLoaded in the drawing area of the preview
				status = thumbGraphics.DrawImage(&BmpLoaded, 0, 0, thumbWidth, thumbHeight);
				HBITMAP hBmp = 0;
				status = pThumbBmp->GetHBITMAP(Gdiplus::Color(0, 0, 0), &hBmp);	// get bitmap handle
				DeleteObject(m_Preview.SetBitmap(hBmp));	// draw the preview, dereference previous bitmap
				DeleteObject(hBmp);
			}
		}
		num_images = nImages;
		SetDlgItemInt(IDC_SET_MULTIPLEX, num_images);
		SetDlgItemInt(IDC_SET_RECORD_IDX, 1);
		SetDlgItemInt(IDC_SET_REP, 100);
		//bring out timing dialog
		if (m_MultiplexMode.GetCheck())
			m_mode = "Multiplex";
		else
			m_mode = "Sequential";

		if (num_images > 0) {
			CustomizeTimingDlg timing_dlg(num_images, fnames, m_MultiplexMode.GetCheck());
			if (timing_dlg.DoModal() == IDOK) {
				this->timing_vals = timing_dlg.get_values();
				record_idx = timing_dlg.get_record_index();
				SetDlgItemInt(IDC_SET_RECORD_IDX, record_idx);
				SetRecordPreview();
			}
		}
	}
	//if canceled, do nothing, maintain original files and settings
	//UpdateData(false);
	UpdateElements();
	return ret;
}

//this function draws small images as preview figure
void CEasyProjDlg::SetRecordPreview() {
	CString fname = fnames[record_idx - 1];
	Gdiplus::Bitmap BmpLoaded(fname);
	Gdiplus::Status status;
	// create a bitmap with preview dimensions
	const int thumbWidth = 176;
	const int thumbHeight = 132;
	std::auto_ptr<Gdiplus::Bitmap> pThumbBmp(new Gdiplus::Bitmap(thumbWidth, thumbHeight, PixelFormat24bppRGB));
	Gdiplus::Graphics thumbGraphics(pThumbBmp.get());	// connect the drawing area with preview

	// draw BmpLoaded in the drawing area of the preview
	status = thumbGraphics.DrawImage(&BmpLoaded, 0, 0, thumbWidth, thumbHeight);
	HBITMAP hBmp = 0;
	status = pThumbBmp->GetHBITMAP(Gdiplus::Color(0, 0, 0), &hBmp);	// get bitmap handle
	m_PreviewRecord.SetBitmap(hBmp);	// draw the preview, dereference previous bitmap
	DeleteObject(hBmp);
}

//int CEasyProjDlg::PostprocessImagesMultiSequence(CString* errorMessage)
//{
//	//int start_seq_id = 0;
//	int BitPlanes = 1;
//	int ret = 0;
//
//	for (int i = 0; i < fnames.size(); ++i) {
//		int total_frame_seq = 0;
//		total_frame_seq += timing_vals[i][0]; //number of on frames
//		total_frame_seq += timing_vals[i][1]; //number of black frames
//		
//		if (m_Projector.getAvailableSequence() > 0) {
//			CString msg;
//			msg.Format(_T("Collected in total %d frames, Available sequence: %d"), total_frames, m_Projector.getAvailableSequence());
//			MessageBox(msg, _T("Notification"), MB_OK | MB_ICONINFORMATION);
//
//			ret = m_Projector.SequenceAlloc(BitPlanes, total_frame_seq * m_ColourComponents, errorMessage);
//			MessageBox(*errorMessage, _T("Message after SequenceAlloc"), MB_OK | MB_ICONINFORMATION);
//		}
//		else {
//			CString msg = _T("No Available Memory Inside Sequence Queue...");
//			MessageBox(msg, _T("Notification"), MB_OK | MB_ICONINFORMATION);
//			return 0;
//		}
//		
//	}
//	ret = AddImageToSequence(TRUE, errorMessage);
//	//ret = AddImageBytesToSequenceV2(errorMessage);
//	CString msg = _T("After add image bytes to sequence") + *errorMessage;
//	MessageBox(msg, _T("Message after New Image Add"), MB_OK | MB_ICONINFORMATION);
//
//	return ret;
//}

//newly added, add non-black & black frames to alp sequences
int CEasyProjDlg::AddImageToSequenceV2(int repeats, CString* errorMessage) {
	Gdiplus::Status status;
	int ret = 0;

	//Gdiplus::Bitmap black_frame(L"\\.psf\\Home\\Desktop\\Desktop-jq\\Retinal\\images\\black_img.bmp");
	Gdiplus::Bitmap black_frame(L"C:\\Users\\vision\\Desktop\\alp-test\\black_img.bmp");

	//------------------------Black Frame ------------------------------------------------

	std::auto_ptr<Gdiplus::Bitmap> pProjBmpBlack(new Gdiplus::Bitmap(m_Projector.GetWidth(), m_Projector.GetHeight(), PixelFormat8bppIndexed));
	Gdiplus::Graphics projGraphicsBlack(pProjBmpBlack.get());

	if (black_frame.GetWidth() == pProjBmpBlack->GetWidth()
		&& black_frame.GetHeight() == pProjBmpBlack->GetHeight())
	{
		// resize not necessary -> clone the bitmap
		pProjBmpBlack.reset(black_frame.Clone(0, 0, m_Projector.GetWidth(), m_Projector.GetHeight(), PixelFormat8bppIndexed));
	}
	else
	{
		// draw bitmap into the drawing area of the sequence image, resize
		status = projGraphicsBlack.DrawImage(&black_frame, 0, 0, m_Projector.GetWidth(), m_Projector.GetHeight());
	}


	// lock RGB image for read access
	Gdiplus::Rect lockRect(0, 0, pProjBmpBlack->GetWidth(), pProjBmpBlack->GetHeight());
	// lock 8bpp sequence image for write access
	Gdiplus::BitmapData bitmapData8bppBlack;		// image data
	pProjBmpBlack->LockBits(&lockRect, Gdiplus::ImageLockModeWrite, PixelFormat8bppIndexed, &bitmapData8bppBlack);

	BYTE* pImageData8bppBlack = static_cast<BYTE*>(bitmapData8bppBlack.Scan0);	// pointer to the first pixel of the first line (8bpp image: target)

	for (size_t y = 0; y < pProjBmpBlack->GetHeight(); y++)
	{
		memset(pImageData8bppBlack, 0, pProjBmpBlack->GetWidth());  // Set each row to black				}
		pImageData8bppBlack += bitmapData8bppBlack.Stride;				// set pointer to the first pixel of the next line
	}

	pImageData8bppBlack = static_cast<BYTE*>(bitmapData8bppBlack.Scan0);	// set pointer back to the first pixel of the first line (RGB image: source)

	//------------------------------END of Black Frame---------------------------------

	for (int i = 0; i < fnames.size(); ++i) { //i is the sequenceID
		int on_frames = timing_vals[i][0]; //number of repeats
		int black_frames = timing_vals[i][1]; //number of repeats
		Gdiplus::Bitmap BmpLoaded(fnames[i]);

		//-----------------------Copying Image Frame -----------------------------------------
		std::auto_ptr<Gdiplus::Bitmap> pProjBmp(new Gdiplus::Bitmap(m_Projector.GetWidth(), m_Projector.GetHeight(), PixelFormat24bppRGB));
		Gdiplus::Graphics projGraphics(pProjBmp.get());
		std::auto_ptr<Gdiplus::Bitmap> pSeqImageBmp(new Gdiplus::Bitmap(m_Projector.GetWidth(), m_Projector.GetHeight(), PixelFormat8bppIndexed));
		Gdiplus::BitmapData bitmapData8bpp;		// image data
		Gdiplus::BitmapData bitmapDataProj;		// image data

		// create a 8bpp-sequence-image as bitmap with projector dimensions
		if (BmpLoaded.GetWidth() == pProjBmp->GetWidth()
			&& BmpLoaded.GetHeight() == pProjBmp->GetHeight())
		{
			// resize not necessary -> clone the bitmap
			pProjBmp.reset(BmpLoaded.Clone(0, 0, m_Projector.GetWidth(), m_Projector.GetHeight(), PixelFormat24bppRGB));
		}

		else
		{
			// draw bitmap into the drawing area of the sequence image, resize
			status = projGraphics.DrawImage(&BmpLoaded, 0, 0, m_Projector.GetWidth(), m_Projector.GetHeight());
		}

		// lock RGB image for read access
		Gdiplus::Rect lockRect(0, 0, pProjBmp->GetWidth(), pProjBmp->GetHeight());
		pProjBmp->LockBits(&lockRect, Gdiplus::ImageLockModeWrite, PixelFormat24bppRGB, &bitmapDataProj);

		// lock 8bpp sequence image for write access
		pSeqImageBmp->LockBits(&lockRect, Gdiplus::ImageLockModeWrite, PixelFormat8bppIndexed, &bitmapData8bpp);

		BYTE* pImageDataProj = static_cast<BYTE*>(bitmapDataProj.Scan0);	// pointer to the first pixel of the first line (RGB image: source)
		BYTE* pImageData8bpp = static_cast<BYTE*>(bitmapData8bpp.Scan0);	// pointer to the first pixel of the first line (8bpp image: target)


		for (size_t y = 0; y < pProjBmp->GetHeight(); y++)
		{
			for (size_t x = 0; x < pProjBmp->GetWidth(); x++)
			{
				pImageData8bpp[x] = (pImageDataProj[x * 3]		// B
					+ pImageDataProj[x * 3 + 1]	// G
					+ pImageDataProj[x * 3 + 2]	// R
					) / 3;
			}
			pImageDataProj += bitmapDataProj.Stride;				// set pointer to the first pixel of the next line
			pImageData8bpp += bitmapData8bpp.Stride;				// set pointer to the first pixel of the next line

		}

		pImageData8bpp = static_cast<BYTE*>(bitmapData8bpp.Scan0);	// set pointer back to the first pixel of the first line (RGB image: source)

		// --------------------------- END of Image Frame ------------------------------
		for (int k = 0; k < repeats; ++k) {
			for (int j = 0; j < on_frames; ++j) {
				ret = m_Projector.AddImage(pImageData8bpp, pSeqImageBmp->GetWidth(), pSeqImageBmp->GetHeight(), errorMessage);
			}
			for (int j = 0; j < black_frames; ++j) {
				ret = m_Projector.AddImage(pImageData8bppBlack, pProjBmpBlack->GetWidth(), pProjBmpBlack->GetHeight(), errorMessage);
			}
		}
		
		status = pProjBmp->UnlockBits(&bitmapDataProj);	// lock end
		status = pSeqImageBmp->UnlockBits(&bitmapData8bpp);	// lock end
	}
	status = pProjBmpBlack->UnlockBits(&bitmapData8bppBlack);

	return ret;
}

//newly added, add non-black & black frames to alp sequences
//int CEasyProjDlg::AddImageToSequence(BOOL multisequence, CString* errorMessage) {
//	Gdiplus::Status status;
//	int ret;
//
//	//Gdiplus::Bitmap black_frame(L"\\.psf\\Home\\Desktop\\Desktop-jq\\Retinal\\images\\black_img.bmp");
//	Gdiplus::Bitmap black_frame(L"C:\\Users\\vision\\Desktop\\alp-test\\black_img.bmp");
//
//	for (int i = 0; i < fnames.size(); ++i) { //i is the sequenceID
//		int on_frames = timing_vals[i][0]; //number of repeats
//		int black_frames = timing_vals[i][1]; //number of repeats
//		Gdiplus::Bitmap BmpLoaded(fnames[i]);
//
//		for (int j = 0; j < on_frames; ++j) {
//			std::auto_ptr<Gdiplus::Bitmap> pProjBmp(new Gdiplus::Bitmap(m_Projector.GetWidth(), m_Projector.GetHeight(), PixelFormat24bppRGB));
//			Gdiplus::Graphics projGraphics(pProjBmp.get());
//			std::auto_ptr<Gdiplus::Bitmap> pSeqImageBmp(new Gdiplus::Bitmap(m_Projector.GetWidth(), m_Projector.GetHeight(), PixelFormat8bppIndexed));
//			Gdiplus::BitmapData bitmapData8bpp;		// image data
//			Gdiplus::BitmapData bitmapDataProj;		// image data
//
//			for (int splitPicNum = 0; splitPicNum < m_ColourComponents; splitPicNum++) // for RGB projection, a source-picture is splited in to three target-pictures 
//			{
//				// create a 8bpp-sequence-image as bitmap with projector dimensions
//
//				int x = BmpLoaded.GetWidth();
//				int y = BmpLoaded.GetHeight();
//
//				if (BmpLoaded.GetWidth() == pProjBmp->GetWidth()
//					&& BmpLoaded.GetHeight() == pProjBmp->GetHeight())
//				{
//					// resize not necessary -> clone the bitmap
//					pProjBmp.reset(BmpLoaded.Clone(0, 0, m_Projector.GetWidth(), m_Projector.GetHeight(), PixelFormat24bppRGB));
//				}
//
//				else
//				{
//					// draw bitmap into the drawing area of the sequence image, resize
//					status = projGraphics.DrawImage(&BmpLoaded, 0, 0, m_Projector.GetWidth(), m_Projector.GetHeight());
//				}
//
//				if (pProjBmp->GetWidth() != pSeqImageBmp->GetWidth()
//					|| pProjBmp->GetHeight() != pSeqImageBmp->GetHeight())
//					break;
//
//				// lock RGB image for read access
//				Gdiplus::Rect lockRect(0, 0, pProjBmp->GetWidth(), pProjBmp->GetHeight());
//				pProjBmp->LockBits(&lockRect, Gdiplus::ImageLockModeWrite, PixelFormat24bppRGB, &bitmapDataProj);
//
//				// lock 8bpp sequence image for write access
//				pSeqImageBmp->LockBits(&lockRect, Gdiplus::ImageLockModeWrite, PixelFormat8bppIndexed, &bitmapData8bpp);
//
//				BYTE* pImageDataProj = static_cast<BYTE*>(bitmapDataProj.Scan0);	// pointer to the first pixel of the first line (RGB image: source)
//				BYTE* pImageData8bpp = static_cast<BYTE*>(bitmapData8bpp.Scan0);	// pointer to the first pixel of the first line (8bpp image: target)
//
//
//				for (size_t y = 0; y < pProjBmp->GetHeight(); y++)
//				{
//					for (size_t x = 0; x < pProjBmp->GetWidth(); x++)
//					{
//						pImageData8bpp[x] = (pImageDataProj[x * 3]		// B
//							+ pImageDataProj[x * 3 + 1]	// G
//							+ pImageDataProj[x * 3 + 2]	// R
//							) / 3;
//					}
//					pImageDataProj += bitmapDataProj.Stride;				// set pointer to the first pixel of the next line
//					pImageData8bpp += bitmapData8bpp.Stride;				// set pointer to the first pixel of the next line
//
//				}
//
//				pImageData8bpp = static_cast<BYTE*>(bitmapData8bpp.Scan0);	// set pointer back to the first pixel of the first line (RGB image: source)
//
//
//
//				if (!multisequence) {
//					ret = m_Projector.AddImage(pImageData8bpp, pSeqImageBmp->GetWidth(), pSeqImageBmp->GetHeight(), errorMessage);		// upload image to the projector an add to sequence
//					//CString msg;
//					//if (ret == 1)
//					//	msg.Format(_T("Added image %d %d to sequence 0"), i, j);
//					//else
//					//	msg.Format(_T("Added image %d %d to sequence 0 failed....???????"), i, j);
//
//					//MessageBox(msg, _T("Multiplex AddImage Notification"), MB_OK | MB_ICONINFORMATION);
//				}
//				else {
//					BOOL restart = (j == 0);
//					ret = m_Projector.AddImageToSequence(pImageData8bpp, pSeqImageBmp->GetWidth(), pSeqImageBmp->GetHeight(), i, restart, errorMessage);
//					//CString msg;
//					//if (ret == 1)
//					//	msg.Format(_T("Added image %d to sequence %d succeeded"), j, i);
//					//else
//					//	msg.Format(_T("Added image %d to sequence %d failed....???????"), j, i);
//
//					//MessageBox(msg, _T("Sequence Mode AddImage Notification"), MB_OK | MB_ICONINFORMATION);
//				}
//				status = pProjBmp->UnlockBits(&bitmapDataProj);	// lock end
//				status = pSeqImageBmp->UnlockBits(&bitmapData8bpp);	// lock end
//			}
//		}
//
//		// add black frmaes
//		for (int j = 0; j < black_frames; ++j) {
//			std::auto_ptr<Gdiplus::Bitmap> pProjBmp(new Gdiplus::Bitmap(m_Projector.GetWidth(), m_Projector.GetHeight(), PixelFormat8bppIndexed));
//			Gdiplus::Graphics projGraphics(pProjBmp.get());
//			for (int splitPicNum = 0; splitPicNum < m_ColourComponents; splitPicNum++) // for RGB projection, a source-picture is splited in to three target-pictures 
//			{
//
//				if (black_frame.GetWidth() == pProjBmp->GetWidth()
//					&& black_frame.GetHeight() == pProjBmp->GetHeight())
//				{
//					// resize not necessary -> clone the bitmap
//					pProjBmp.reset(black_frame.Clone(0, 0, m_Projector.GetWidth(), m_Projector.GetHeight(), PixelFormat8bppIndexed));
//				}
//				else
//				{
//					// draw bitmap into the drawing area of the sequence image, resize
//					status = projGraphics.DrawImage(&black_frame, 0, 0, m_Projector.GetWidth(), m_Projector.GetHeight());
//				}
//
//
//				// lock RGB image for read access
//				Gdiplus::Rect lockRect(0, 0, pProjBmp->GetWidth(), pProjBmp->GetHeight());
//				// lock 8bpp sequence image for write access
//				Gdiplus::BitmapData bitmapData8bpp;		// image data
//				pProjBmp->LockBits(&lockRect, Gdiplus::ImageLockModeWrite, PixelFormat8bppIndexed, &bitmapData8bpp);
//
//				BYTE* pImageData8bpp = static_cast<BYTE*>(bitmapData8bpp.Scan0);	// pointer to the first pixel of the first line (8bpp image: target)
//
//				for (size_t y = 0; y < pProjBmp->GetHeight(); y++)
//				{
//					memset(pImageData8bpp, 0, pProjBmp->GetWidth());  // Set each row to black				}
//					pImageData8bpp += bitmapData8bpp.Stride;				// set pointer to the first pixel of the next line
//				}
//
//				pImageData8bpp = static_cast<BYTE*>(bitmapData8bpp.Scan0);	// set pointer back to the first pixel of the first line (RGB image: source)
//				if (!multisequence) {
//					ret = m_Projector.AddImage(pImageData8bpp, pProjBmp->GetWidth(), pProjBmp->GetHeight(), errorMessage);		// upload image to the projector an add to sequence
//					/*CString msg;
//					if (ret == 1)
//						msg.Format(_T("Added black image %d %d to sequence 0"), i, j);
//					else
//						msg.Format(_T("Added black image %d %d to sequence 0 failed....???????"), i, j);
//
//					MessageBox(msg, _T("Multiplex AddImage Notification"), MB_OK | MB_ICONINFORMATION);*/
//				}
//				else {
//					ret = m_Projector.AddImageToSequence(pImageData8bpp, pProjBmp->GetWidth(), pProjBmp->GetHeight(), i, FALSE, errorMessage);
//					//CString msg;
//					//if (ret == 1)
//					//	msg.Format(_T("Added black image % d to sequence % d"), j, i);
//					//else
//					//	msg.Format(_T("Added black image %d to sequence %d failed....???????"), j, i);
//
//					//MessageBox(msg, _T("Sequence Mode AddImage black Notification"), MB_OK | MB_ICONINFORMATION);
//				}
//				status = pProjBmp->UnlockBits(&bitmapData8bpp);	// lock end
//
//			}
//		}
//	}
//
//	return ret;
//}


//BYTE* get_byte_data(CString fname) {
//	std::auto_ptr<Gdiplus::Bitmap> pProjBmp(new Gdiplus::Bitmap(m_Projector.GetWidth(), m_Projector.GetHeight(), PixelFormat8bppIndexed));
//	Gdiplus::Graphics projGraphics(pProjBmp.get());
//	// lock 8bpp sequence image for write access
//	Gdiplus::BitmapData bitmapData8bpp;		// image data
//	BYTE* pImageData8bpp;
//	for (int splitPicNum = 0; splitPicNum < m_ColourComponents; splitPicNum++) // for RGB projection, a source-picture is splited in to three target-pictures 
//	{
//		if (black_frame.GetWidth() == pProjBmp->GetWidth()
//			&& black_frame.GetHeight() == pProjBmp->GetHeight())
//		{
//			// resize not necessary -> clone the bitmap
//			pProjBmp.reset(black_frame.Clone(0, 0, m_Projector.GetWidth(), m_Projector.GetHeight(), PixelFormat8bppIndexed));
//		}
//		else
//		{
//			// draw bitmap into the drawing area of the sequence image, resize
//			status = projGraphics.DrawImage(&black_frame, 0, 0, m_Projector.GetWidth(), m_Projector.GetHeight());
//		}
//
//
//		// lock RGB image for read access
//		Gdiplus::Rect lockRect(0, 0, pProjBmp->GetWidth(), pProjBmp->GetHeight());
//		
//		pProjBmp->LockBits(&lockRect, Gdiplus::ImageLockModeWrite, PixelFormat8bppIndexed, &bitmapData8bpp);
//
//		pImageData8bpp = static_cast<BYTE*>(bitmapData8bpp.Scan0);	// pointer to the first pixel of the first line (8bpp image: target)
//
//		for (size_t y = 0; y < pProjBmp->GetHeight(); y++)
//		{
//			memset(pImageData8bpp, 0, pProjBmp->GetWidth());  // Set each row to black				}
//			pImageData8bpp += bitmapData8bpp.Stride;				// set pointer to the first pixel of the next line
//		}
//
//		pImageData8bpp = static_cast<BYTE*>(bitmapData8bpp.Scan0);	// set pointer back to the first pixel of the first line (RGB image: source)
//	}
//	return pImageData8bpp;
//}




//for multiplex mode and sequence too
int CEasyProjDlg::PostprocessImages(CString *errorMessage) {
	total_frames = 0;
	for (int i = 0; i < fnames.size(); ++i) {
		total_frames += timing_vals[i][0]; //number of on frames
		total_frames += timing_vals[i][1]; //number of black frames
	}
	//sequence allocation
	int BitPlanes = 1;
	int ret = 0;
	CString msg;
	msg.Format(_T("Collected in total %d frames from %d images"), total_frames, num_images);
	MessageBox(msg, _T("Notification"), MB_OK | MB_ICONINFORMATION);
	int repeats = m_SeqMode.GetCheck() ? GetDlgItemInt(IDC_SET_REP) : 1; //repetition = 1 for multiplex
	if (m_SeqMode.GetCheck()) {
		total_frames *= repeats;
	}
	ret = m_Projector.SequenceAlloc(BitPlanes, total_frames * m_ColourComponents, errorMessage);		// create a sequence
	if (ret == ALP_OK) {
		CString msg;
		msg.Format(_T("Sequence Allocated for %d"), total_frames);
		MessageBox(msg, _T("Notification"), MB_OK | MB_ICONINFORMATION);
	}
	
	ret = AddImageToSequenceV2(repeats, errorMessage);
	return ret;
	

}



// load images and add it to a sequence
//const int CEasyProjDlg::LoadSequence(CString *errorMessage)
//{
//	const LPCTSTR filter =
//		_T("All Image Files|*.tif;*.tiff;*.png;*.gif;*.bmp;*.jpg;*.jpeg|")
//		_T("TIF Files for Sequence (*.tif)|*.tif|")
//		_T("TIFF Files for Sequence (*.tiff)|*.tiff|");
//	CFileDialog dlg( TRUE, NULL, 0, OFN_PATHMUSTEXIST|OFN_ALLOWMULTISELECT|OFN_EXPLORER|OFN_NOCHANGEDIR|OFN_FILEMUSTEXIST|OFN_ENABLESIZING, filter);
//
//	wchar_t buffer[1<<16];
//	*buffer = '\0';
//
//	dlg.m_pOFN->lpstrFile	= buffer;
//	dlg.m_pOFN->nMaxFile	= sizeof(buffer)/sizeof(*buffer);
//
//	int ret = ALP_OK;
//	int nImages = 0;
//
//	if(IDOK == dlg.DoModal())											// show file open dialog
//	{
//		CWaitCursor WaitCursor; 
//
//		// determine the sequence length
//		for(POSITION pos = dlg.GetStartPosition(); NULL!=pos; )
//		{
//			CString fileNameLOAD = dlg.GetNextPathName(pos);
//			nImages ++;
//		}
//
//
//		const int BitPlanes = 1;									// use all bitplanes for projection
//		ret = m_Projector.SequenceAlloc( BitPlanes, nImages*m_ColourComponents, errorMessage);		// create a sequence
//		if( ALP_OK != ret)
//			return ret;
//
//		// read images from file, convert it and put it to the projector
//		Gdiplus::Status status;
//		int k = 0;	
//		for(POSITION pos = dlg.GetStartPosition(); NULL!=pos; )
//		{
//			CString fileNameLOAD = dlg.GetNextPathName(pos);
//
//			Gdiplus::Bitmap BmpLoaded( fileNameLOAD);			// read the image from file
//
//			{	// Show progress and preview thumbnail
//				m_SequenceLoadedImages.Format( _T("%d"), k+1);	// update dialog element with current image counter
//
//				// create a bitmap with preview dimensions
//				const int thumbWidth = 176;
//				const int thumbHeight = 132;
//				std::auto_ptr<Gdiplus::Bitmap> pThumbBmp(new Gdiplus::Bitmap( thumbWidth, thumbHeight, PixelFormat24bppRGB));
//				Gdiplus::Graphics thumbGraphics(pThumbBmp.get());	// connect the drawing area with preview
//
//				// draw BmpLoaded in the drawing area of the preview
//				status = thumbGraphics.DrawImage( &BmpLoaded, 0, 0, thumbWidth, thumbHeight);	
//				HBITMAP hBmp = 0;
//				status = pThumbBmp->GetHBITMAP( Gdiplus::Color(0,0,0), &hBmp);	// get bitmap handle
//				DeleteObject(m_Preview.SetBitmap( hBmp ));	// draw the preview, dereference previous bitmap
//				DeleteObject(hBmp);
//			}
//
//
//			// create a new bitmap with projector dimensions
//			std::auto_ptr<Gdiplus::Bitmap> pProjBmp(new Gdiplus::Bitmap( m_Projector.GetWidth(), m_Projector.GetHeight(), PixelFormat24bppRGB));
//			Gdiplus::Graphics projGraphics( pProjBmp.get() );
//
//			for(int splitPicNum=0; splitPicNum<m_ColourComponents; splitPicNum++) // for RGB projection, a source-picture is splited in to three target-pictures 
//			{
//				// create a 8bpp-sequence-image as bitmap with projector dimensions
//				std::auto_ptr<Gdiplus::Bitmap> pSeqImageBmp(new Gdiplus::Bitmap( m_Projector.GetWidth(), m_Projector.GetHeight(), PixelFormat8bppIndexed));
//	
//				if( BmpLoaded.GetWidth() == pProjBmp->GetWidth()
//					&&	BmpLoaded.GetHeight() == pProjBmp->GetHeight())
//				{
//					// resize not necessary -> clone the bitmap
//					pProjBmp.reset(BmpLoaded.Clone( 0, 0, m_Projector.GetWidth(), m_Projector.GetHeight(), PixelFormat24bppRGB));
//				}
//				else
//				{
//					// draw bitmap into the drawing area of the sequence image, resize
//					status = projGraphics.DrawImage( &BmpLoaded, 0, 0, m_Projector.GetWidth(), m_Projector.GetHeight());
//				}
//
//				if( pProjBmp->GetWidth() != pSeqImageBmp->GetWidth()
//					||	pProjBmp->GetHeight() != pSeqImageBmp->GetHeight())
//					break;
//
				// lock RGB image for read access
				//Gdiplus::Rect lockRect( 0, 0, pProjBmp->GetWidth(), pProjBmp->GetHeight());	
				//Gdiplus::BitmapData bitmapDataProj;		// image data
				//pProjBmp->LockBits( &lockRect, Gdiplus::ImageLockModeWrite, PixelFormat24bppRGB, &bitmapDataProj);

				//// lock 8bpp sequence image for write access
				//Gdiplus::BitmapData bitmapData8bpp;		// image data
				//pSeqImageBmp->LockBits( &lockRect, Gdiplus::ImageLockModeWrite, PixelFormat8bppIndexed, &bitmapData8bpp);

				//BYTE *pImageDataProj = static_cast<BYTE*>(bitmapDataProj.Scan0);	// pointer to the first pixel of the first line (RGB image: source)
				//BYTE *pImageData8bpp = static_cast<BYTE*>(bitmapData8bpp.Scan0);	// pointer to the first pixel of the first line (8bpp image: target)

//				// transform pixel wise: RGB -> 8bpp
//				if(3 == m_ColourComponents)						// RGB picture
//				{
//					// Byte-order of color components: B,G,R
//					// see also GdiPlusPixelFormats: BLUE_SHIFT=0, GREEN_SHIFT=8, RED_SHIFT=16
//					int const nColorIndex = 2-splitPicNum;
//					for( size_t y=0; y < pProjBmp->GetHeight(); y++)
//					{
//						for( size_t x=0; x < pProjBmp->GetWidth(); x++)
//						{
//							pImageData8bpp[x] =	( pImageDataProj[ x*3 + nColorIndex]);
//						}
//						pImageDataProj += bitmapDataProj.Stride;				// set pointer to the first pixel of the next line
//						pImageData8bpp += bitmapData8bpp.Stride;				// set pointer to the first pixel of the next line
//					}
//				} else
//				{	// monochrome
//					for( size_t y=0; y < pProjBmp->GetHeight(); y++)
//					{
//						for( size_t x=0; x < pProjBmp->GetWidth(); x++)
//						{
//							pImageData8bpp[x] =	( pImageDataProj[ x*3]		// B
//												+ pImageDataProj[ x*3+1]	// G
//												+ pImageDataProj[ x*3+2]	// R
//												) / 3;
//						}
//						pImageDataProj += bitmapDataProj.Stride;				// set pointer to the first pixel of the next line
//						pImageData8bpp += bitmapData8bpp.Stride;				// set pointer to the first pixel of the next line
//					}
//				}
//
//				pImageData8bpp = static_cast<BYTE*>(bitmapData8bpp.Scan0);	// set pointer back to the first pixel of the first line (RGB image: source)
//				ret = m_Projector.AddImage( pImageData8bpp, pSeqImageBmp->GetWidth(), pSeqImageBmp->GetHeight(), errorMessage);		// upload image to the projector an add to sequence
//
//				status = pProjBmp->UnlockBits(&bitmapDataProj);	// lock end
//				status = pSeqImageBmp->UnlockBits(&bitmapData8bpp);	// lock end
//
//				if( ALP_OK != ret)
//					return ret;
//			}
//
//			k++;
//		}
//	}
//	num_images = nImages;
//	SetDlgItemInt(IDC_SET_MULTIPLEX, num_images);
//	SetDlgItemInt(IDC_SET_RECORD_IDX, 1);
//	SetDlgItemInt(IDC_SET_REP, 0); //default to infinite repetition
//	UpdateData(false);
//	return ret;
//}

CString &CEasyProjDlg::LedTemperature(int nIndex)
{
	switch (nIndex)
	{
	default: throw;
	case 1: return m_Led1Temperature;
	case 2: return m_Led2Temperature;
	case 3: return m_Led3Temperature;
	}
}

////////////////////////////////////////////////////////////////////////////////


void CEasyProjDlg::OnBnClickedRadioProjNone()
{
	BnClickedRadioProjectorType();
}

void CEasyProjDlg::OnBnClickedRadioProjStar07()
{
	BnClickedRadioProjectorType();
}

void CEasyProjDlg::OnBnClickedRadioProjStar07RGB()
{
	BnClickedRadioProjectorType();
}

void CEasyProjDlg::OnBnClickedRadioProjAlpOnly()
{
	BnClickedRadioProjectorType();
}

void CEasyProjDlg::AllocateProjector()
{
	if(CProjector::PROJECTOR_TYPE_NONE != m_Projector.GetProjectorType())
	{
		CString exErrorMessage;
		
		int ret = m_Projector.Alloc(&exErrorMessage);
		
		SetProjectorReturnCodeMsg( ret, FAILURE, exErrorMessage);
		if(ALP_OK != ret)
			return;

		m_LedEnableMode = GATE_LOW;

		ret = GetProjectorProperties(&exErrorMessage);
		
		SetProjectorReturnCodeMsg( ret, FAILURE, exErrorMessage);
		if(ALP_OK != ret)
			return;

		switch(m_Projector.GetProjectorType())
		{
		case CProjector::PROJECTOR_TYPE_ALP_ONLY:
			m_ColourComponents = 1;
			break;
		case CProjector::PROJECTOR_TYPE_STAR_07:
			ret = SetConstHigh(&exErrorMessage);
			SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);
			m_ColourComponents = 1;
			break;
		case CProjector::PROJECTOR_TYPE_STAR_07_RGB:
			m_ColourComponents = 3;
			ret = SetRoundRobin(&exErrorMessage);
			SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);

			ret = m_Projector.Led(1).Alloc(ALP_HLD_PT120_RED, 0, &exErrorMessage);
			SetProjectorReturnCodeMsg( ret, WARNING, L"Led 1 : " + exErrorMessage);
			ret = m_Projector.Led(2).Alloc(ALP_HLD_PT120_GREEN, 1, &exErrorMessage);
			SetProjectorReturnCodeMsg( ret, WARNING, L"Led 2 : " + exErrorMessage);
			ret = m_Projector.Led(3).Alloc(ALP_HLD_PT120TE_BLUE, 2, &exErrorMessage);
			SetProjectorReturnCodeMsg( ret, WARNING, L"Led 3 : " + exErrorMessage);
			break;
		default:
			throw;
		}	
	}
	UpdateElements();													// update all dialog elements from data

	// LED Monitor Timer starts now, before LEDs are actually switched on.
	SetTimer(MONITOR, MONITOR_PERIOD, NULL);
	OnTimer(MONITOR);
}


void CEasyProjDlg::FreeProjector()
{
	CString exErrorMessage;
	m_iLedBrightness = 0;
	SetLEDBrightness( m_iLedBrightness);
	int ret = m_Projector.ProjStop(&exErrorMessage);
	SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);
	
	ret = FreeSequence(&exErrorMessage);
	SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);

	// free projector and reset dialog elements
	ret = m_Projector.Free(&exErrorMessage);
	SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);

	m_ProjectorSerial = CString( L" ");									// delete the serial number
	m_ProjectorDmdSize = CString( L" ");
	m_iLEDType = 0;
	m_iLedBrightness = 0;
	m_Led1Temperature = "";
	m_Led2Temperature = "";
	m_Led3Temperature = "";
	m_LedEnableMode = GATE_LOW;
	//also remove current fnames
	fnames.clear();
	m_OnTimerErrors.ResetErrors();
	KillTimer(MONITOR);
	UpdateElements();													// update all dialog elements from data
}


void CEasyProjDlg::OnBnClickedRadioLedNone()
{
	BnClickedRadioLEDType();
}
void CEasyProjDlg::OnBnClickedRadioLedRed()
{
	BnClickedRadioLEDType();
}
void CEasyProjDlg::OnBnClickedRadioLedGreen()
{
	BnClickedRadioLEDType();
}
void CEasyProjDlg::OnBnClickedRadioLedBlueTe()
{
	BnClickedRadioLEDType();
}
void CEasyProjDlg::OnBnClickedRadioLedUv()
{
	BnClickedRadioLEDType();
}
void CEasyProjDlg::OnBnClickedRadioLedCbt140White()
{
	BnClickedRadioLEDType();
}


void CEasyProjDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	switch (nSBCode)
	{
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
	// all other SB codes cause a subsequent SB_ENDSCROLL
	case SB_ENDSCROLL:   // End scroll.
			UpdateData( TRUE);											// update direction: dialog elements -> data
			SetLEDBrightness( m_iLedBrightness);
			break;
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CEasyProjDlg::OnBnClickedSeqLoad()
{
	CString exErrorMessage;
	int ret = StoreImages(&exErrorMessage);
	//BOOL ok = AddImageBytePointers(&exErrorMessage);

	SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);
	
	//ret = GetSequenceProperties(&exErrorMessage);

	SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);
	
	UpdateElements();													// update all dialog elements from data
}


//free sequence, clear fnames
void CEasyProjDlg::OnBnClickedSeqFree()
{
	CString exErrorMessage;
	
	int ret = FreeSequence(&exErrorMessage);

	SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);

	UpdateElements();													// update all dialog elements from data
}

BOOL check_timing(std::vector<std::vector<int>> timings) {
	const auto& firstPair = timings[0]; // Take the first pair for comparison.
	for (const auto& pair : timings) {
		if (pair != firstPair) {
			return FALSE;
		}
	}
	return TRUE;
}

//void CEasyProjDlg::OnBnClickedSetSeqParamTest() {
//	int ret = 0;
//	UpdateData(TRUE);
//	CString exErrorMessage;
//	ret = m_Projector.SetMasterControl(&exErrorMessage); // set master control
//	SetProjectorReturnCodeMsg(ret, WARNING, exErrorMessage);
//	if (ret != ALP_OK) {
//		CString msg = _T("In setseqparam, return error");
//		MessageBox(msg, _T("Notification"), MB_OK | MB_ICONINFORMATION);
//	}
//
//	int num_test = 10;
//
//	ret = m_Projector.SequenceAlloc(1, num_test * 2 * m_ColourComponents, &exErrorMessage);
//
//	for (int i = 0; i < image_bytes.size(); ++i) {
//		for (int j = 0; j < num_test; ++j) {
//			ret = m_Projector.AddImage(image_bytes[i], m_Projector.GetWidth(), m_Projector.GetHeight());
//		}
//		if (ret != ALP_OK) {
//			CString msg = _T("Add image using pointers failed");
//			MessageBox(msg, _T("Notification"), MB_OK | MB_ICONINFORMATION);
//		}
//	}
//
//	CString msg = _T("Allocated Sequence, added 10 images...");
//	MessageBox(msg, _T("Notification"), MB_OK | MB_ICONINFORMATION);
//
//	ret = SetSequenceProperties(&exErrorMessage); //do this after allocating all sequences
//
//	if (ALP_OK == ret)
//		ret = GetSequenceProperties(&exErrorMessage);
//
//}

BOOL CEasyProjDlg::ValidateProjection() {
	//check mode
	if (!(m_MultiplexMode.GetCheck() || m_SeqMode.GetCheck())) {
		CString msg = _T("Please Select a Mode!");
		MessageBox(msg, _T("Notification"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	//check timing
	if (GetDlgItemInt(IDC_PIC_TIME) == 0) {
		CString msg = _T("Please Fill in PictureTime!");
		MessageBox(msg, _T("Notification"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	return TRUE;
}

void CEasyProjDlg::OnBnClickedSetSeqParam()
{
	UpdateData(TRUE);
	CString exErrorMessage;	
	int ret = m_Projector.SetMasterControl(&exErrorMessage); // set master control
	SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);
	//if (ret != ALP_OK) {
	//	CString msg = _T("In setseqparam, return error");
	//	MessageBox(msg, _T("Notification"), MB_OK | MB_ICONINFORMATION);
	//}

	//always need to free existing sequence and do postprocessing if already allocate sequences, if no sequence has allocated then no need to re-do
	if (m_Projector.IsValidSequence()) {
		exErrorMessage = "";
		int seq_id = m_Projector.getSequenceID();
		ret = m_Projector.SequenceFree(&exErrorMessage); //in case need to change setting
		if (ret != ALP_OK) {
			CString msg;
			msg.Format(_T("Sequence Freeing Exists with Error. Seq ID: %d"), seq_id);
			MessageBox(msg, _T("Notification"), MB_OK | MB_ICONERROR);
		}
		else {
			CString msg;
			msg.Format(_T("Finished Freeing Existing Sequences. Seq ID: %d"), seq_id);
			MessageBox(msg, _T("Notification"), MB_OK | MB_ICONINFORMATION);
		}
	}

	ret = PostprocessImages(&exErrorMessage);
	ret = SetSequenceProperties(&exErrorMessage); //do this after allocating all sequences

	// In case of a running projection the changes gets effective even after Stop/Start of the projection.
	//if( ALP_OK == ret &&	m_Projector.IsProjection())
	//{
	//	ret = m_Projector.ProjStop(&exErrorMessage);
	//	SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);
	//	if (m_MultiplexMode.GetCheck())
	//		ret = m_Projector.ProjStartContinuous(&exErrorMessage);
	//	else
	//		ret = m_Projector.ProjStartSequential(&exErrorMessage);
	//	SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);
	//}

	// After successful timing setup, report effective settings. These values could
	// differ from input in case of inconsistent parameters or ALP_DEFAULT.
	// On failure the user interface parameters shall be adjustable individually, so they are not overwritten.
	if (ALP_OK==ret)
		ret = GetSequenceProperties(&exErrorMessage);
	
	SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);
	CString msg = _T("At the end of SetSeqParam!!!") + exErrorMessage;
	SetDlgItemText(IDC_ERROR_MSG, msg);

	UpdateElements();													// update all dialog elements from data
}


void CEasyProjDlg::OnBnClickedProjStart()
{
	CString exErrorMessage;
	CString msg;
	int ret;
	int seq_id = m_Projector.getSequenceID(); 
	//just in case forgot to press set parameter, i do it here too!
	if (ValidateProjection()) {
		OnBnClickedSetSeqParam();
	}
	else {
		return;
	}
	
	//also check whether images are added to sequence
	int num_pic = m_Projector.getNumPicInSequence();
	if (num_pic == 0) {
		CString msg = _T("No image found in sequence. Report this issue please! Exiting....");
		MessageBox(msg, _T("Notification"), MB_OK | MB_ICONERROR);
		return;
	}

	//check if runs in sequence mode or multiplex mode
	if (m_MultiplexMode.GetCheck()) {
		CString msg = _T("It's Multiplex Mode, Projects infinitely...");
		MessageBox(msg, _T("Notification"), MB_OK | MB_ICONINFORMATION);
		ret = m_Projector.ProjStartContinuous(&exErrorMessage);
		if (exErrorMessage != "")
			MessageBox(exErrorMessage, _T("Error Message Notification"), MB_OK | MB_ICONINFORMATION);
	}
	else {
		CString msg = _T("It's Sequential Mode, Projects infinitely...");
		MessageBox(msg, _T("Notification"), MB_OK | MB_ICONINFORMATION);
		ret = m_Projector.ProjStartContinuous(&exErrorMessage);
		if (exErrorMessage != "")
			MessageBox(exErrorMessage, _T("Message after ProjStartSequential Notification"), MB_OK | MB_ICONINFORMATION);
	}
	SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);
	
	UpdateElements();													// update all dialog elements from data
}

//stop projection, free sequence, fnames remains
void CEasyProjDlg::OnBnClickedProjStop()
{
	CString exErrorMessage;	

	int ret = m_Projector.ProjStop(&exErrorMessage); //stop projection & free sequence
	if (ret == ALP_OK) {
		CString msg = _T("Projection Stopped, Sequences Freed, Please press projection to restart");
		SetDlgItemText(IDC_ERROR_MSG, msg);
	}
	SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);
	
	UpdateElements();													// update all dialog elements from data
}


void CEasyProjDlg::OnOK()
{
	OnBnClickedSetSeqParam();
}

void CEasyProjDlg::OnCancel()
{
	if (IDYES == MessageBox( _T("Quit?"), NULL, MB_ICONQUESTION | MB_YESNOCANCEL | MB_DEFBUTTON1 ))
		CDialogEx::OnCancel();
}


void CEasyProjDlg::OnBnClickedHelp()
{
	WinHelp( 0 );
}

void CEasyProjDlg::WinHelp(DWORD dwData, UINT nCmd)
{
	UNREFERENCED_PARAMETER( (dwData, nCmd) );

	MessageBox(
		_T("An introduction to EasyProj can be found in the ALP Quick Start Guide.\r\n")
		_T("1. Select Device Type: this intiializes the V-Module or STAR-07 projector\r\n")
		_T("2. STAR-07: Select the correct LED type.\r\n")
		_T("   The wrong type could cause overload and damage.\r\n")
		_T("3. Load pictures in order to create an ALP sequence.\r\n")
		_T("   STAR-07 RGB uses colour components, other devices convert to monochrome.\r\n")
		_T("4. Start projection.\r\n")
		_T("5. Sequence Timing automatically corrects inconsistent parameters.\r\n")
		_T("Please read the source code and the ALP API description for details."),
		_T("ALP EasyProj - ViALUX GmbH")
		);
}


void CEasyProjDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString exErrorMessage;
	CString strReport;
	long Temp, TempLimit;

	switch (nIDEvent)
	{
	case MONITOR:
		
		for(int i=1; i<=3; i++)
		{
			if(m_Projector.Led(i).IsValid())
			{
				OnTimerInquiryHandler(i, Temp, TempLimit);
				// Output estimation of LED Junction Temperature:
				LedTemperature(i).Format( _T("%3.1f"), double(Temp)/256);
				
				// check for temperature exceedance 
				if (Temp > TempLimit*256)
				{
					m_Projector.Led(i).OverTempAlertsAdd1();
					LedTemperature(i) += _T(" !");
				} else
				{
					m_Projector.Led(i).RstOverTempAlerts();
				}
				// temperatur exceedance three times in a row  --> emergency stop 
				if (m_Projector.Led(i).GetOverTempAlerts() == 3)
				{
					m_iLedBrightness = 0;
					SetLEDBrightness( m_iLedBrightness);
					UpdateElements();													// update all dialog elements from data

					BOOL bHaveFocus;
					strReport.Format( _T("Led %d is overheating.\nEmergency stop."), i);
					if (OnTimerGetFocus(bHaveFocus))
						MessageBox(strReport, L"Warning", MB_ICONEXCLAMATION);
					OnTimerKillFocus( bHaveFocus );
					m_Projector.Led(i).RstOverTempAlerts();
				}
			}
			else
			{
				LedTemperature(i).Format(_T(""));
			}
		}
		UpdateData(FALSE);

		// reset time-out watchdog: shut down LEDs 0.5s - 1.5s after the next scheduled monitor event.
		// (silently ignore return value -> older ALP API DLLs do not implement this feature)
		m_Projector.RetriggerSynchOutWatchdog( (MONITOR_PERIOD+1500)/1000 );

		break;

	default:
		CDialog::OnTimer(nIDEvent);
	};
}

	BOOL m_bOnTimerIsModal;
BOOL CEasyProjDlg::OnTimerGetFocus( OUT BOOL &bHaveFocus )
{
	if (m_bOnTimerIsModal)
		bHaveFocus = FALSE;
	else
	{
		// Now I have the focus, and can run a modal message box.
		bHaveFocus =
		m_bOnTimerIsModal = TRUE;
	}
	return bHaveFocus;
}
void CEasyProjDlg::OnTimerKillFocus( IN OUT BOOL &bHaveFocus)
{
	if (bHaveFocus)
		// Reset class member only if _I_ have had the focus!
		m_bOnTimerIsModal = FALSE;
	bHaveFocus = FALSE;
}

void CEasyProjDlg::OnTimerInquiryHandler(int Indx, long &JunctionTemp, long &JunctionTempLimit)
{
	CString exErrorMessage;	
	
	// Consider actual Pulse Timing in Micro Seconds
	long OnTime = 0, PeriodTime = 0;
	switch (m_LedEnableMode)
	{
	default:
	case GATE_LOW :
		OnTime = 0; PeriodTime = 100;	// Off
		break;
	case GATE_ROUND_ROBIN3 :
		OnTime = m_Projector.IsProjection() ? m_LedOnTime : 0;
		PeriodTime = 3*m_PictureTime;
		break;
	case GATE_HIGH :
		OnTime = 100; PeriodTime = 100;	// Continuous Wave
		break;
	};
	
	long ret = m_Projector.Led(Indx).GetJunctionTemperature(JunctionTemp, &exErrorMessage, OnTime, PeriodTime);
	JunctionTempLimit = m_Projector.Led(Indx).GetJunctionTempLimit();

	if(!m_OnTimerErrors.m_LedTempError[Indx])
	{
		m_OnTimerErrors.m_LedTempError[Indx] = ret;
		exErrorMessage.Format(L"Led  %d : " + exErrorMessage, Indx);

		BOOL bHaveFocus;
		if (OnTimerGetFocus(bHaveFocus))
			SetProjectorReturnCodeMsg(ret, WARNING, exErrorMessage);
		OnTimerKillFocus(bHaveFocus);
	}

	return;
}

////////////////////////////////////////////////////////////////////////////////

void CEasyProjDlg::COnTimerErrors::ResetErrors()
{
	for(int i=0; i<3; i++)
	{
		m_LedTempError[i] = ALP_OK;
	}
}


void CEasyProjDlg::OnBnClickedCheckPicTime()
{
	UpdateElements();
}

void CEasyProjDlg::OnBnClickedCheckIlluTime()
{
	UpdateElements();
}


void CEasyProjDlg::OnBnClickedCheckFlip()
{
	CString exErrorMessage;
	long ret;
	ret = m_Projector.SetFlip( m_CheckFlip.GetCheck(), exErrorMessage );
	SetProjectorReturnCodeMsg( ret, WARNING, exErrorMessage);
}
