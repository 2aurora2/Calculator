
// CalculatorDlg.h: 头文件
//

#pragma once
#include "ErrorDialog.h"
#include <vector>
using namespace std;


// CCalculatorDlg 对话框
class CCalculatorDlg : public CDialogEx
{
// 构造
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CFont m_Font;  // 字体
	CEdit m_Edit;  // 编辑文本框
	CFont m_HisFont; // 历史文本字体
	CEdit m_HisEdit; // 历史文本框
	CString m_Exp; // 存储用户的输入
	CString m_His; // 存储上一次计算的式子及结果
	ErrorDialog m_Err; // 模态弹出错误信息窗口
	vector<double> numbers; // 存储数码
	vector<char> operators; // 存储操作符号
	bool ClickTime = false; // 当前是否显示时间
	HBITMAP m_hBitmap;
	CBrush m_bgBrush;
public:
	afx_msg void OnBnClickedSymbol();
	afx_msg void OnBnClicked1();
	afx_msg void OnBnClicked2();
	afx_msg void OnBnClicked3();
	afx_msg void OnBnClicked4();
	afx_msg void OnBnClicked5();
	afx_msg void OnBnClicked6();
	afx_msg void OnBnClicked7();
	afx_msg void OnBnClickedNum8();
	afx_msg void OnBnClicked9();
	afx_msg void OnBnClicked0();
	afx_msg void OnBnClickedPoint();
	afx_msg void OnBnClickedModBtn();
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedSubBtn();
	afx_msg void OnBnClickedMulBtn();
	afx_msg void OnBnClickedDivBtn();
	afx_msg void OnBnClickedCountBtn();
	afx_msg void OnBnClickedBackBtn();
	afx_msg void OnBnClickedEmptyBtn();
	void SeparateStr(CString str); // 分离字符串式子
	double CountRes(); // 计算式子结果
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
