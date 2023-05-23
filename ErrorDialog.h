#pragma once
#include "afxdialogex.h"


// ErrorDialog 对话框

class ErrorDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ErrorDialog)

public:
	ErrorDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ErrorDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = ERROR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CStatic m_Err;
	CFont err_Font;
public:
	afx_msg void OnBnClickedButton1();
};
