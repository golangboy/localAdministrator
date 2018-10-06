
// AdministratorDlg.h : 头文件
//

#pragma once


// CAdministratorDlg 对话框
class CAdministratorDlg : public CDialogEx
{
// 构造
public:
	CAdministratorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ADMINISTRATOR_DIALOG };

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
public:
	afx_msg void OnBnClickedScan();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnEnChangeEdit3();
//	afx_msg void OnCbnEditupdateCombo1();
//	afx_msg void OnCbnDblclkCombo1();
	afx_msg void OnCbnCloseupCombo1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnCbnSelchangeCombo1();
};
