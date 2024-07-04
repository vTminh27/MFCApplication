
// MFCApplication3Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include <Aclapi.h>

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


// CMFCApplication3Dlg dialog



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CMFCApplication3Dlg::OnBnClickedButtonSearch)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RESULTS, &CMFCApplication3Dlg::OnNMDblclkListResults)
END_MESSAGE_MAP()


// CMFCApplication3Dlg message handlers
CString FormatFileSize(ULONGLONG ullBytes)
{
	const ULONGLONG KB = 1024;
	const ULONGLONG MB = 1024 * KB;
	const ULONGLONG GB = 1024 * MB;
	const ULONGLONG TB = 1024 * GB;

	CString strSize;
	if (ullBytes >= TB)
		strSize.Format(_T("%.2f TB"), static_cast<double>(ullBytes) / TB);
	else if (ullBytes >= GB)
		strSize.Format(_T("%.2f GB"), static_cast<double>(ullBytes) / GB);
	else if (ullBytes >= MB)
		strSize.Format(_T("%.2f MB"), static_cast<double>(ullBytes) / MB);
	else if (ullBytes >= KB)
		strSize.Format(_T("%.2f KB"), static_cast<double>(ullBytes) / KB);
	else
		strSize.Format(_T("%llu Bytes"), ullBytes);

	return strSize;
}

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	// Subclass controls
	m_editFolderPath.SubclassDlgItem(IDC_EDIT_FOLDER_PATH, this);
	m_editFileName.SubclassDlgItem(IDC_EDIT_FILE_NAME, this);
	m_listResults.SubclassDlgItem(IDC_LIST_RESULTS, this);

	// Set up the list control columns
	m_listResults.InsertColumn(0, _T("Tên File"), LVCFMT_LEFT, 150);
	m_listResults.InsertColumn(1, _T("Kích Thước"), LVCFMT_RIGHT, 100);
	m_listResults.InsertColumn(2, _T("Đường Dẫn"), LVCFMT_LEFT, 300);
	m_listResults.InsertColumn(3, _T("Ngày Sửa"), LVCFMT_LEFT, 150);
	m_listResults.InsertColumn(4, _T("Ngày Tạo"), LVCFMT_LEFT, 150);
	m_listResults.InsertColumn(5, _T("Chủ Sở Hữu"), LVCFMT_LEFT, 150);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication3Dlg::OnPaint()
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
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication3Dlg::OnBnClickedButtonSearch()
{
	CString folderPath;
	CString fileName;
	m_editFolderPath.GetWindowText(folderPath);
	m_editFileName.GetWindowText(fileName);

	m_listResults.DeleteAllItems();

	if (folderPath.IsEmpty() || fileName.IsEmpty())
	{
		AfxMessageBox(_T("Vui lòng nhập đường dẫn thư mục và tên file cần tìm."));
		return;
	}

	SearchFiles(folderPath, fileName);
}

void CMFCApplication3Dlg::SearchFiles(const CString& folderPath, const CString& fileName, int depth)
{
	if (depth > 5) { // Limit the search depth to prevent excessive recursion
		return;
	}

    CString searchPath = folderPath + _T("\\") + fileName + _T("*");
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(searchPath, &findFileData);

    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                CString fullPath = folderPath + _T("\\") + findFileData.cFileName;
                AddFileToList(findFileData, fullPath);
            }
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);
    }

    // Search in subdirectories
    searchPath = folderPath + _T("\\*");
    hFind = FindFirstFile(searchPath, &findFileData);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (_tcscmp(findFileData.cFileName, _T(".")) != 0 && _tcscmp(findFileData.cFileName, _T("..")) != 0)
                {
                    CString subDir = folderPath + _T("\\") + findFileData.cFileName;
                    SearchFiles(subDir, fileName, depth + 1); 
                }
            }
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);
    }
}

void CMFCApplication3Dlg::AddFileToList(const WIN32_FIND_DATA& findFileData, const CString& filePath)
{
    ULONGLONG ullFileSize = ((ULONGLONG)findFileData.nFileSizeHigh << 32) + findFileData.nFileSizeLow;
    CString fileSize = FormatFileSize(ullFileSize);

    FILETIME ftCreate, ftWrite;
    SYSTEMTIME stUTC;
    FileTimeToLocalFileTime(&findFileData.ftCreationTime, &ftCreate);
    FileTimeToLocalFileTime(&findFileData.ftLastWriteTime, &ftWrite);

    FileTimeToSystemTime(&ftCreate, &stUTC);
    CString createTime;
    createTime.Format(_T("%02d/%02d/%d %02d:%02d"), stUTC.wDay, stUTC.wMonth, stUTC.wYear, stUTC.wHour, stUTC.wMinute);

    FileTimeToSystemTime(&ftWrite, &stUTC);
    CString modifyTime;
    modifyTime.Format(_T("%02d/%02d/%d %02d:%02d"), stUTC.wDay, stUTC.wMonth, stUTC.wYear, stUTC.wHour, stUTC.wMinute);

    int nItem = m_listResults.InsertItem(0, findFileData.cFileName);
    m_listResults.SetItemText(nItem, 1, fileSize); // Now displays size in KB, MB, etc.
    m_listResults.SetItemText(nItem, 2, filePath);
    m_listResults.SetItemText(nItem, 3, modifyTime);
    m_listResults.SetItemText(nItem, 4, createTime);
}

void CMFCApplication3Dlg::OnNMDblclkListResults(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nIndex = pNMItemActivate->iItem;
	if (nIndex != -1) // Ensure an item was clicked
	{
		CString filePath = m_listResults.GetItemText(nIndex, 2); // Column 2 has the file path
		if (!filePath.IsEmpty())
		{
			ShellExecute(NULL, _T("open"), filePath, NULL, NULL, SW_SHOW);
		}
	}
	*pResult = 0;
}


