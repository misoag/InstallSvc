// AboutDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "InstallSvc.h"
#include "AboutDialog.h"
#include "afxdialogex.h"


// CAboutDialog 对话框

IMPLEMENT_DYNAMIC(CAboutDialog, CDialogEx)

CAboutDialog::CAboutDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAboutDialog::IDD, pParent)
{
	this->m_brush.CreateSolidBrush(RGB(200, 245, 142)); 
}

CAboutDialog::~CAboutDialog()
{

}

void CAboutDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDialog, CDialogEx)
	ON_BN_CLICKED(IDC_LOG_BTN, &CAboutDialog::OnBnClickedLogBtn)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON4, &CAboutDialog::OnBnClickedButton4)
END_MESSAGE_MAP()


BOOL CAboutDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//设置 Log 字体
	CFont * pMajorLogFont = new CFont;
	pMajorLogFont->CreateFont(33, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH, _T("微软雅黑"));
	((CStatic *)GetDlgItem(IDC_MAJORLOG_STATIC))->SetFont(pMajorLogFont, FALSE);

	//设置 Button 大小，其用来容纳图片，并且将图片绑定到 Button 控件上
	CWnd * pTmpCwnd = GetDlgItem(IDC_LOG_BTN);
	pTmpCwnd->SetWindowPos( NULL, 0, 0, 100, 100, SWP_NOZORDER | SWP_NOMOVE);
	SetResourceImageToCtrl(TEXT("PNG"), IDC_LOG_BTN, IDB_PNG1);

	//设置窗体透明度，120 是透明度，范围是 0～255
	::SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);  
	::SetLayeredWindowAttributes(m_hWnd, 0, 215, LWA_ALPHA);

	//设置窗体上的窗口图标为 IDI_ICON1
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_ICON1);
	SetIcon(hIcon, FALSE);

	return TRUE;
}


//从资源文件中读取出 PNG 格式的图片，并且将该图片转换为 Bitmap，然后显示在指定 ID 的控件上
void CAboutDialog::SetResourceImageToCtrl(LPCTSTR lpszImgType, int nCtrlCode, int nImgResourceID)
{
	CImage cImg;
	HRSRC hRsrc = FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nImgResourceID), lpszImgType);
	if(NULL != hRsrc)
	{
		HGLOBAL hImgData = LoadResource(AfxGetResourceHandle(), hRsrc);
		if(NULL != hImgData)
		{
			LPSTREAM lpStream = NULL;
			LPVOID lpVoid = LockResource(hImgData);
			DWORD dwSize = SizeofResource(AfxGetResourceHandle(), hRsrc);

			HGLOBAL hAllocate = GlobalAlloc(GHND, dwSize);
			LPBYTE lpByte = (LPBYTE)GlobalLock(hAllocate);
			memcpy(lpByte, lpVoid, dwSize);
			GlobalUnlock(hAllocate);

			HRESULT hResult = CreateStreamOnHGlobal(hAllocate, TRUE, &lpStream);
			if(S_OK == hResult)
			{
				cImg.Load(lpStream);

				HBITMAP hBitmap = cImg.Detach();

				((CButton *)GetDlgItem(nCtrlCode))->SetBitmap(hBitmap);				
			}

			GlobalFree(hAllocate);
			FreeResource(hImgData);
		}
	}
}


void CAboutDialog::OnBnClickedLogBtn()
{
	//在浏览器中打开我的主页
	ShellExecute(this->m_hWnd, NULL, TEXT("www.cnblogs.com/boyxiao"), NULL, NULL, SW_SHOWNORMAL);
}


HBRUSH CAboutDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	//只有当是对话框窗体时，才将画刷设置为 m_brush
	//对于一些其他的控件之类的则不操作，即使用预定义背景色
	if(nCtlColor == CTLCOLOR_DLG)
	{  
		//return this->m_brush;
	} 

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CAboutDialog::OnBnClickedButton4()
{
	SendMessage(WM_CLOSE, NULL, NULL);
}
