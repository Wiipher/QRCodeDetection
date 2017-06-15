
// Problem_2Dlg.h : header file
#include <string>
#include <map>

#include <opencv2/opencv.hpp>

#include "CUser.h"
#include "CImageMat.h"
#include "CImageProcess.h"

#pragma once
#include "afxwin.h"

using namespace cv;

// CProblem_2Dlg dialog
class CProblem_2Dlg : public CDialogEx
{
// Construction
public:
	CProblem_2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROBLEM_2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// User Define
public:
	int		GetExePath();
	void	ShowPic(cv::Mat& src, int nID, bool fresh = TRUE);
	void	ShowMsg(const string str, bool clean = FALSE);

protected:
	CUser				cUser;
	CImageProcess		cimageProcess;
	CImageMat			cimageMat;

	string				exeDir;
	string				openFilePath;
	cv::Mat				srcPic;
	map<int, cv::Mat>	showMap;


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
	CEdit m_msgBox;
	CStatic m_picTarget;
	CStatic m_picPiece;
	CListBox m_listBox;
	afx_msg void OnOpenTarget();
};
