// ErrorDialog.cpp: 实现文件
//

#include "pch.h"
#include "Calculator.h"
#include "afxdialogex.h"
#include "ErrorDialog.h"


// ErrorDialog 对话框

IMPLEMENT_DYNAMIC(ErrorDialog, CDialogEx)

ErrorDialog::ErrorDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ERROR_DIALOG, pParent)
{

}

ErrorDialog::~ErrorDialog()
{
}

void ErrorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ErrorDialog, CDialogEx)
	ON_BN_CLICKED(ENTER_BTN, &ErrorDialog::OnBnClickedButton1)
END_MESSAGE_MAP()


// ErrorDialog 消息处理程序

void ErrorDialog::OnBnClickedButton1()
{
	CDialog::OnOK();
}
