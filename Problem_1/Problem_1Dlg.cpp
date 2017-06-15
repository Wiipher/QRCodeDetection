
// Problem_1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Problem_1.h"
#include "Problem_1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProblem_1Dlg dialog



CProblem_1Dlg::CProblem_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PROBLEM_1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProblem_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_msgBox);
}

BEGIN_MESSAGE_MAP(CProblem_1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CProblem_1Dlg::OnBnClickedOk)
	ON_COMMAND(ID_FILE_OPEN32771, &CProblem_1Dlg::OnFileOpen)
END_MESSAGE_MAP()


// CProblem_1Dlg message handlers

BOOL CProblem_1Dlg::OnInitDialog()
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

	// TODO: Add extra initialization here
	GetExePath();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProblem_1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProblem_1Dlg::OnPaint()
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

		// User Define
		map<int, cv::Mat>::iterator iter;
		for (iter = showMap.begin(); iter != showMap.end(); iter++)
			ShowPic(iter->second, iter->first, FALSE);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProblem_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CProblem_1Dlg::GetExePath()
{
	TCHAR _szPath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, _szPath, MAX_PATH);
	(_tcsrchr(_szPath, _T('\\')))[1] = 0;//删除文件名，只获得路径字串
	CString strPath;
	for (int n = 0; _szPath[n]; n++)
	{
		if (_szPath[n] != _T('\\'))
		{
			strPath += _szPath[n];
		}
		else
		{
			strPath += _T("\\");
		}
	}

	exeDir = CStringA(strPath);
	return 1;
}

void CProblem_1Dlg::ShowPic(cv::Mat& src, int nID, bool fresh) // default = TRUE
{
	if (src.total() == 0)
		return;
	if (fresh)
	{
		if (showMap.find(nID) == showMap.end())
			showMap.insert(pair<int, cv::Mat>(nID, src));
		else
			showMap[nID] = src;
		this->RedrawWindow();
	}

	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(nID);

	CRect rect, showRect;
	pWnd->GetClientRect(&rect);
	CDC *pDc = pWnd->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	int width = rect.Width();
	int height = rect.Height();
	cv::Mat img = cimageProcess.PicResize(src, width, height);
	CImage cimg;
	cimageMat.MatToCImage(img, cimg);
	int img_w, img_h;
	img_w = cimg.GetWidth();
	img_h = cimg.GetHeight();
	CPoint topleft = CPoint(rect.CenterPoint().x - img_w / 2, rect.CenterPoint().y - img_h / 2);
	showRect = CRect(topleft, CSize(img_w, img_h));
	cimg.StretchBlt(pDc->m_hDC, showRect, SRCCOPY);

	ReleaseDC(pDc);
}

void CProblem_1Dlg::ShowMsg(const string str, bool clean) // default = FALSE
{
	wchar_t* ss = cUser.StringToWchar(str);
	if (clean)
	{
		m_msgBox.SetWindowText(ss);	
		return;
	}	
	m_msgBox.SetSel(-1, -1);
	m_msgBox.ReplaceSel(ss);
}

void CProblem_1Dlg::OnFileOpen()
{
	// 设置过滤器   
	TCHAR szFilter[] = _T("Image file(*.jpg)|*.jpg|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("Open File"), NULL, 0, szFilter, this);
	fileDlg.m_ofn.lpstrInitialDir = cUser.StringToWchar(exeDir);

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		openFilePath = cUser.WstringToString(fileDlg.GetPathName().GetBuffer());
		fileDlg.GetPathName().ReleaseBuffer();
		ShowMsg(openFilePath + "\r\n", TRUE);
	}

	//显示图片
	srcPic = cv::imread(openFilePath);
	ShowPic(srcPic, IDC_STATIC_PIC);
}

void CProblem_1Dlg::OnBnClickedOk()
{
	cv::Mat rectPic;
	srcPic.copyTo(rectPic);
	vector<vector<Point>> landmarks;
	Rect QRrect;
	landmarks = cimageProcess.GetQRCodeLandmark(rectPic);
	QRrect = cimageProcess.GetQRCodeRect(landmarks);

	drawContours(rectPic, landmarks, -1, CV_RGB(250, 211, 31), 3);
	rectangle(rectPic, QRrect, CV_RGB(88, 194, 194), 3);

	Rect avatarCnt;
	avatarCnt = cimageProcess.GetQRCodeAvatar(srcPic, QRrect);
	rectangle(rectPic, avatarCnt, CV_RGB(250, 211, 31), 3);
	ShowPic(rectPic, IDC_STATIC_PIC);

	cv::Mat binarImg = cv::Mat::zeros(srcPic.size(), CV_8UC1);
	binarImg(avatarCnt).setTo(255);
	for (int i = 0; i < landmarks.size(); i++)
	{
		vector<Point> cntPoints = cimageProcess.GetContourRect(landmarks[i]);
		binarImg(Rect(cntPoints[0], cntPoints[2])).setTo(255);
	}

	ShowPic(binarImg, IDC_STATIC_PIC_RESULT);
}
