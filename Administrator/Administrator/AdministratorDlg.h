
// AdministratorDlg.h : ͷ�ļ�
//

#pragma once


// CAdministratorDlg �Ի���
class CAdministratorDlg : public CDialogEx
{
// ����
public:
	CAdministratorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ADMINISTRATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
