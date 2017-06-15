
// Problem_1Dlg.h : header file
#include <Windows.h>
#include <string>
#include <map>

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

#include "CUser.h"
#include "CImageMat.h"
#include "CImageProcess.h"

using namespace cv;

#pragma once


// CProblem_1Dlg dialog
class CProblem_1Dlg : public CDialogEx
{
// Construction
public:
	CProblem_1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROBLEM_1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// User Define
public:
	int		GetExePath();
	void	ShowPic(cv::Mat& src, int nID, bool fresh = TRUE);
	void	ShowMsg(const string str, bool clean = FALSE);

protected:
	CEdit			m_msgBox;
	CUser			cUser;
	CImageProcess	cimageProcess;
	CImageMat		cimageMat;

	string		exeDir;
	string		openFilePath;
	cv::Mat		srcPic;
	map<int, cv::Mat> showMap;

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
	afx_msg void OnBnClickedOk();
	afx_msg void OnFileOpen();
};
