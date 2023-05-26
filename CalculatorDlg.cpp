
// CalculatorDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"
#include <cctype>
#include <stack>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCalculatorDlg 对话框



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, TEXT_EDIT, m_Edit);
	DDX_Control(pDX, HISTORY, m_HisEdit);
	DDX_Text(pDX, TEXT_EDIT, m_Exp);
	DDX_Text(pDX, HISTORY, m_His);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(SYMBOL, &CCalculatorDlg::OnBnClickedSymbol)
	ON_BN_CLICKED(NUM_1, &CCalculatorDlg::OnBnClicked1)
	ON_BN_CLICKED(NUM_2, &CCalculatorDlg::OnBnClicked2)
	ON_BN_CLICKED(NUM_3, &CCalculatorDlg::OnBnClicked3)
	ON_BN_CLICKED(NUM_4, &CCalculatorDlg::OnBnClicked4)
	ON_BN_CLICKED(NUM_5, &CCalculatorDlg::OnBnClicked5)
	ON_BN_CLICKED(NUM_6, &CCalculatorDlg::OnBnClicked6)
	ON_BN_CLICKED(NUM_7, &CCalculatorDlg::OnBnClicked7)
	ON_BN_CLICKED(NUM8, &CCalculatorDlg::OnBnClickedNum8)
	ON_BN_CLICKED(NUM_9, &CCalculatorDlg::OnBnClicked9)
	ON_BN_CLICKED(NUM_0, &CCalculatorDlg::OnBnClicked0)
	ON_BN_CLICKED(POINT, &CCalculatorDlg::OnBnClickedPoint)
	ON_BN_CLICKED(MOD_BTN, &CCalculatorDlg::OnBnClickedModBtn)
	ON_BN_CLICKED(ADD_BTN, &CCalculatorDlg::OnBnClickedAddBtn)
	ON_BN_CLICKED(SUB_BTN, &CCalculatorDlg::OnBnClickedSubBtn)
	ON_BN_CLICKED(MUL_BTN, &CCalculatorDlg::OnBnClickedMulBtn)
	ON_BN_CLICKED(DIV_BTN, &CCalculatorDlg::OnBnClickedDivBtn)
	ON_BN_CLICKED(RES_BTN, &CCalculatorDlg::OnBnClickedCountBtn)
	ON_BN_CLICKED(BACK_BTN, &CCalculatorDlg::OnBnClickedBackBtn)
	ON_BN_CLICKED(DELETE_BTN, &CCalculatorDlg::OnBnClickedEmptyBtn)
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CCalculatorDlg 消息处理程序

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 设置文本框字体
	m_Font.CreatePointFont(320, _T("宋体"));
	m_Edit.SetFont(&m_Font);
	m_HisFont.CreatePointFont(180, _T("宋体"));
	m_HisEdit.SetFont(&m_HisFont);

	CString Path = L"./res/bg.png"; // 图片路径
	CImage img;
	img.Load(Path);
	HBITMAP hbmp = img.Detach();
	CBitmap bmp;
	bmp.Attach(hbmp);
	m_bgBrush.CreatePatternBrush(&bmp);
	m_hBitmap = (HBITMAP)LoadImage(NULL, Path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 正负号
void CCalculatorDlg::OnBnClickedSymbol()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"-";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		if (m_Exp == L"")
			m_Exp += "-";
		else {
			if (m_Exp != L"" && m_Exp[m_Exp.GetLength() - 1] != '.')
				if ((m_Exp.GetLength() == 1 && m_Exp[0] != '-') || !(m_Exp.GetLength() >= 2 && m_Exp[m_Exp.GetLength() - 1] == '-' && m_Exp[m_Exp.GetLength() - 2] == '-'))
					m_Exp += "-";
		}
		UpdateData(FALSE);
	}
}

// 数字1
void CCalculatorDlg::OnBnClicked1()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"1";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		m_Exp += "1";
		UpdateData(FALSE);
	}
}

// 数字2
void CCalculatorDlg::OnBnClicked2()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"2";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		m_Exp += "2";
		UpdateData(FALSE);
	}
}

// 数字3
void CCalculatorDlg::OnBnClicked3()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"3";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		m_Exp += "3";
		UpdateData(FALSE);
	}
}

// 数字4
void CCalculatorDlg::OnBnClicked4()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"4";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		m_Exp += "4";
		UpdateData(FALSE);
	}
}

// 数字5
void CCalculatorDlg::OnBnClicked5()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"5";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		m_Exp += "5";
		UpdateData(FALSE);
	}
}

// 数字6
void CCalculatorDlg::OnBnClicked6()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"6";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		m_Exp += "6";
		UpdateData(FALSE);
	}
}

// 数字7
void CCalculatorDlg::OnBnClicked7()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"7";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		m_Exp += "7";
		UpdateData(FALSE);
	}
}

// 数字8
void CCalculatorDlg::OnBnClickedNum8()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"8";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		m_Exp += "8";
		UpdateData(FALSE);
	}
}

// 数字9
void CCalculatorDlg::OnBnClicked9()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"9";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		m_Exp += "9";
		UpdateData(FALSE);
	}
}

// 数字0
void CCalculatorDlg::OnBnClicked0()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"0";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		m_Exp += "0";
		UpdateData(FALSE);
	}
}

// 小数点
void CCalculatorDlg::OnBnClickedPoint()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		if (m_Exp != L"" && m_Exp[m_Exp.GetLength() - 1] != '+' && m_Exp[m_Exp.GetLength() - 1] != '-' && m_Exp[m_Exp.GetLength() - 1] != '*' && m_Exp[m_Exp.GetLength() - 1] != '/' && m_Exp[m_Exp.GetLength() - 1] != '.')
			m_Exp += ".";
		UpdateData(FALSE);
	}
}

// 展示当前时间
void CCalculatorDlg::OnBnClickedModBtn()
{
	ClickTime = true;
	UpdateData(TRUE);
	CTime t = CTime::GetCurrentTime();
	m_Exp.Format(L"%d.%d.%d %d:%d", t.GetYear(), t.GetMonth(), t.GetDay(), t.GetHour(), t.GetMinute());
	UpdateData(FALSE);
}

// "+"符号
void CCalculatorDlg::OnBnClickedAddBtn()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		if (m_Exp != L"" && m_Exp[m_Exp.GetLength() - 1] != '+' && m_Exp[m_Exp.GetLength() - 1] != '-' && m_Exp[m_Exp.GetLength() - 1] != '*' && m_Exp[m_Exp.GetLength() - 1] != '/' && m_Exp[m_Exp.GetLength() - 1] != '.')
			m_Exp += "+";
		UpdateData(FALSE);
	}
}

// "-"符号
void CCalculatorDlg::OnBnClickedSubBtn()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		if (m_Exp != L"" && m_Exp[m_Exp.GetLength() - 1] != '.')
			if ((m_Exp.GetLength() == 1 && m_Exp[0] != '-') || (m_Exp.GetLength() >= 2 && m_Exp[m_Exp.GetLength() - 1] != '-'))
				m_Exp += "-";
		UpdateData(FALSE);
	}
}

// "*"符号
void CCalculatorDlg::OnBnClickedMulBtn()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		if (m_Exp != L"" && m_Exp[m_Exp.GetLength() - 1] != '+' && m_Exp[m_Exp.GetLength() - 1] != '-' && m_Exp[m_Exp.GetLength() - 1] != '*' && m_Exp[m_Exp.GetLength() - 1] != '/' && m_Exp[m_Exp.GetLength() - 1] != '.')
			m_Exp += "*";
		UpdateData(FALSE);
	}
}

// "/"符号
void CCalculatorDlg::OnBnClickedDivBtn()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		if (m_Exp != L"" && m_Exp[m_Exp.GetLength() - 1] != '+' && m_Exp[m_Exp.GetLength() - 1] != '-' && m_Exp[m_Exp.GetLength() - 1] != '*' && m_Exp[m_Exp.GetLength() - 1] != '/' && m_Exp[m_Exp.GetLength() - 1] != '.')
			m_Exp += "/";
		UpdateData(FALSE);
	}
}

// 结果求解及展示Funtion
void CCalculatorDlg::OnBnClickedCountBtn()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"";
		UpdateData(FALSE);
	}
	else {
		// 判断式子末末位是否为数字（否则式子不合法）
		if (m_Exp == L"" || !isalnum(m_Exp[m_Exp.GetLength() - 1]))
			m_Err.DoModal();
		else if (m_Exp.GetLength() >= 2 && m_Exp[0] == '-' && m_Exp[1] == '-')
			m_Err.DoModal();
		else {
			// 计算前清空存储数字和符号的容器
			numbers.clear();
			operators.clear();
			SeparateStr(m_Exp);
			UpdateData(TRUE);
			double res = CountRes();
			m_His.Format(m_Exp + L" = " + L"%.3f", res);
			m_Exp = L"";
			UpdateData(FALSE);
		}
	}
}

// 退格
void CCalculatorDlg::OnBnClickedBackBtn()
{
	if (ClickTime) {
		ClickTime = false;
		UpdateData(TRUE);
		m_Exp = L"";
		UpdateData(FALSE);
	}
	else {
		UpdateData(TRUE);
		m_Exp = m_Exp.Left(m_Exp.GetLength() - 1);
		UpdateData(FALSE);
	}
}

// 清空式子
void CCalculatorDlg::OnBnClickedEmptyBtn()
{
	UpdateData(TRUE);
	m_Exp = _T("");
	UpdateData(FALSE);
}

// 拆分式子的字符串为数字和符号并分别存储
void CCalculatorDlg::SeparateStr(CString str)
{
	str += L"=";
	while (str != L"") {
		double number = 0.0f;
		int i = 1;
		while (isdigit(str[i]) || str[i] == '.')
			++i;
		number = _ttof(str.Left(i));
		numbers.push_back(number);
		operators.push_back(str[i]);
		str = str.Right(str.GetLength() - i - 1);
	}
}

// 判断符号优先级（如果将入栈的符号r优先级低或者相等，则返回true）
bool CompareSymbol(char f, char r) {
	if ((f == '+' && r == '+') || (f == '-' && r == '-') || (f == '*' && r == '*') || (f == '/' && r == '/') || (f == '+' && r == '-') || (f == '-' && r == '+') || (f == '*' && r == '+') || (f == '*' && r == '-') || (f == '*' && r == '/') || (f == '/' && r == '+') || (f == '/' && r == '-') || (f == '/' && r == '*'))
		return true;
	else
		return false;
}

// 进行相邻两个数的运算
double CalculateNearNum(double l, char ops, double r) {
	if (ops == '+') return l + r;
	else if (ops == '-') return l - r;
	else if (ops == '*') return l * r;
	else return l / r;
}

// 利用栈求解式子结果
double CCalculatorDlg::CountRes() 
{
	stack<double> stkD;
	stack<char> stkC;
	double res = 0.0f;
	int len = numbers.size();
	bool mark;
	for (int i = 0; i < len; ++i) {
		stkD.push(numbers[i]);
		if (operators[i] != '=') {
			mark = false;
			while (!mark) {
				if (stkC.empty()) {
					stkC.push(operators[i]);
					mark = true;
				}
				else if (CompareSymbol(stkC.top(), operators[i])) {
					double n1 = stkD.top();
					stkD.pop();
					double n2 = stkD.top();
					stkD.pop();
					stkD.push(CalculateNearNum(n2, stkC.top(), n1));
					stkC.pop();
				}
				else {
					stkC.push(operators[i]);
					mark = true;
				}
			}
		}
	}
	while (!stkC.empty())
	{
		double n1 = stkD.top();
		stkD.pop();
		double n2 = stkD.top();
		stkD.pop();
		stkD.push(CalculateNearNum(n2, stkC.top(), n1));
		stkC.pop();
	}
	return stkD.top();
}


HBRUSH CCalculatorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (pWnd == this) {
		return m_bgBrush;
	}
	return hbr;
}


LRESULT CCalculatorDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CDialogEx::OnNcHitTest(point);
}
