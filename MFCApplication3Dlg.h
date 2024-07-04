
// MFCApplication3Dlg.h : header file
//

#pragma once


// CMFCApplication3Dlg dialog
class CMFCApplication3Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication3Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };
#endif

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
	CEdit m_editFolderPath;
	CEdit m_editFileName;
	CListCtrl m_listResults;

	void SearchFiles(const CString& folderPath, const CString& fileName, int depth = 0);
	void AddFileToList(const WIN32_FIND_DATA& findFileData, const CString& filePath);

public:
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnNMDblclkListResults(NMHDR *pNMHDR, LRESULT *pResult);
	

	
};


