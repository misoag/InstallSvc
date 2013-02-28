
// InstallSvcDlg.h : 头文件
//

#pragma once
#include "afxwin.h"



// CInstallSvcDlg 对话框
class CInstallSvcDlg : public CDialogEx
{
// 构造
public:
	CInstallSvcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_INSTALLSVC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlSvcPath;
	CEdit m_ctrlSvcName;
	CEdit m_ctrlSvcNameTitle;
	CEdit m_ctrlMsgTitle;
	CEdit m_ctrlMsg;
	afx_msg void OnBnClickedBrowseBtn();
	afx_msg void OnBnClickedInstallBtn();
	afx_msg void OnBnClickedStartBtn();
	afx_msg void OnBnClickedStopBtn();
	afx_msg void OnBnClickedUninstallBtn();
	afx_msg void OnBnClickedAboutBtn();
	afx_msg void OnBnClickedExitBtn();
	afx_msg void OnBnClickedManuallyCheck();
private:
	void InitControl();
	bool OutputErrorMessage(LPTSTR lpszMsg);
	bool OutputSuccessMessage(LPTSTR lpszMsg);

	bool AdjustProcessTokenPrivilege();

	bool InstallSvc(LPTSTR lpszSvcName, LPTSTR lpszDisplayName, LPTSTR lpszSvcBinaryPath, DWORD dwSvcType, DWORD dwStartType);
	bool UnInstallSvc(LPTSTR lpszSvcName);
	bool StartSvc(LPTSTR lpszSvcName);
	bool StopSvc(LPTSTR lpszSvcName);
	bool InstallServiceIsOK();

private:
	CString m_strFileExt;
};
