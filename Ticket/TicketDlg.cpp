
// TicketDlg.cpp : implementation file
#pragma once
#include "stdafx.h"
#include "Ticket.h"
#include "TicketDlg.h"
#include "afxdialogex.h"
#include "Theroad.h"
#include "Road.h"
#include "ans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTicketDlg dialog



CTicketDlg::CTicketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTicketDlg::IDD, pParent)
	, ftime(_T(""))
	, ttime(_T(""))
	, stime(_T(""))
	, chway(_T(""))
	, chtegy(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTicketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ftime);//ftime means the start state
	DDX_Text(pDX, IDC_EDIT2, ttime);//ttime means the end state
	DDX_Text(pDX, IDC_EDIT3, stime);//stime means the start time for the user
	DDX_CBString(pDX, IDC_COMBO1, chway);//chway to choose the train or the plane
	DDX_CBString(pDX, IDC_COMBO2, chtegy);//chtegy to choose the money or time to search the shortest way
}

BEGIN_MESSAGE_MAP(CTicketDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTicketDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CTicketDlg::OnEnChangeEdit1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTicketDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTicketDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTicketDlg message handlers

BOOL CTicketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization£®≥ı ºªØ£© here

	t = new Theroad;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTicketDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTicketDlg::OnPaint()
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
HCURSOR CTicketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTicketDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	//convert CString to std::string
	t = new Theroad;
	UpdateData();
	CT2CA fs(ftime);
	CT2CA ts(ttime);
	CT2CA ss(stime);
	CT2CA cs(chway);
	CT2CA gs(chtegy);

	string fSta(fs); //starting station name
	string tSta(ts); //destination station name
	string sTim(ss); //The begin time
	string cWay(cs);//The way to search
	string gTgy(gs);//The strategy to choose
	string theans;
	int thenum;
	char ssn[l], dsn[l], bn[l];//to convert string to char array

	strncpy_s(ssn,fSta.c_str(), sizeof(ssn));//convert string to char array
	strncpy_s(dsn, tSta.c_str(), sizeof(dsn));
	strncpy_s(bn, sTim.c_str(), sizeof(bn));

	//MessageBox(chway, 0, MB_ICONINFORMATION);
	//if ((!t->findcity("AA"))|| (!t->findcity("AB")))
	if ((!t->findcity(fSta)) || (!t->findcity(tSta)))
		MessageBox(L"No such city!", 0, MB_ICONINFORMATION);
	else{
		if (cWay == "plane" && gTgy == "money"){
			//MessageBox(L"1!", 0, MB_ICONINFORMATION);
			thenum=t->findroadpm(ssn,dsn,bn);
			if (thenum == 0)MessageBox(L"No way!", 0, MB_ICONINFORMATION);
			else{
				theans = t->printans(thenum);
				MessageBox(CString(theans.c_str()), 0, MB_ICONINFORMATION);
			}
		}
		else if (cWay == "plane" && gTgy == "time"){
			//MessageBox(L"2!", 0, MB_ICONINFORMATION);
			thenum = t->findroadpt(ssn, dsn, bn);
			if (thenum == 0)MessageBox(L"No way!", 0, MB_ICONINFORMATION);
			else {
				theans = t->printans(thenum);
				MessageBox(CString(theans.c_str()), 0, MB_ICONINFORMATION);
			}
		}
		else if (cWay == "train" && gTgy == "money"){
			thenum = t->findroadtm(ssn, dsn, bn);
			if (thenum == 0)MessageBox(L"No way!", 0, MB_ICONINFORMATION);
			else{
				theans = t->printans(thenum);
				MessageBox(CString(theans.c_str()), 0, MB_ICONINFORMATION);
			}
		}
		else if (cWay == "train" && gTgy == "time"){
			//MessageBox(L"4!", 0, MB_ICONINFORMATION);
			thenum = t->findroadtt(ssn, dsn, bn);
			if (thenum == 0)MessageBox(L"No way!", 0, MB_ICONINFORMATION);
			else{
				theans = t->printans(thenum);
				MessageBox(CString(theans.c_str()), 0, MB_ICONINFORMATION);
			}
		}
	}
}


void CTicketDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

}


void CTicketDlg::OnCbnSelchangeCombo1()
{
	
}


void CTicketDlg::OnBnClickedButton2()//to change the text of the notepad
{
	UpdateData();
	system("notepad.exe in.txt");
}
