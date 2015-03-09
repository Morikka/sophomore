#pragma once
#include"stdafx.h"
#include"Theroad.h"
#include"ans.h"
#include"Road.h"

// TicketDlg.h : header file
//

#pragma once


// CTicketDlg dialog
class CTicketDlg : public CDialogEx
{
// Construction
public:
	CTicketDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TICKET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString ftime;//the start state
	CString ttime;//the end state
	CString stime;//the begin time of the user
	CString chway;//choose plane or train
	CString chtegy;//choose money or time

	Theroad *t;

	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton2();
};
