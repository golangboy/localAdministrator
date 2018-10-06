
// AdministratorDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "Administrator.h"
#include "AdministratorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif





/*/* WinPcap SDK     */ 
//#include "pcap.h"  //�Լ��ϰٶ���!�����˻���lib




/* Smm.h            */
#include "Smm.h"





/*  �궨��   */
#define ��������� 15





/*  �ؼ�����  */
//CListBox  *cListBox = 0; //�����б�
CComboBox *cCombBox = 0; //
CListCtrl *cListLis = 0; //
CEdit     *cEdit_gw    = 0;  // ����
CEdit     *cEdit_st    = 0;  //��ʼIP�༭��
CEdit     *cEdit_ed    = 0;  //����IP�༭��
CEdit     *cEdit_ou    = 0;  //����༭��
CEdit     *cEdit_MC    = 0;  //MAC�༭��
CButton   *cButt_ap    = 0;  //ARPɨ��
/*  �ؼ�����  */






/* �ṹ���� */
struct szNet
{
	char szNetName[200]; //������
	char szNetGuid[200]; //GUID
};
/* �ṹ���� */


/* szNet����     */

szNet Net[���������] = {0};

/* szNet����     */









// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAdministratorDlg �Ի���



CAdministratorDlg::CAdministratorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdministratorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdministratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAdministratorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_SCAN, &CAdministratorDlg::OnBnClickedScan)
	ON_BN_CLICKED(IDC_BUTTON2, &CAdministratorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAdministratorDlg::OnBnClickedButton3)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CAdministratorDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON4, &CAdministratorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CAdministratorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdministratorDlg::OnBnClickedButton1)
//	ON_EN_CHANGE(IDC_EDIT3, &CAdministratorDlg::OnEnChangeEdit3)
//ON_CBN_EDITUPDATE(IDC_COMBO1, &CAdministratorDlg::OnCbnEditupdateCombo1)
//ON_CBN_DBLCLK(IDC_COMBO1, &CAdministratorDlg::OnCbnDblclkCombo1)
ON_CBN_CLOSEUP(IDC_COMBO1, &CAdministratorDlg::OnCbnCloseupCombo1)
ON_EN_CHANGE(IDC_EDIT2, &CAdministratorDlg::OnEnChangeEdit2)
ON_CBN_SELCHANGE(IDC_COMBO1, &CAdministratorDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CAdministratorDlg ��Ϣ�������

BOOL CAdministratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//cListBox = (CListBox*) GetDlgItem(IDC_LIST1);








	//=======================�ؼ�����============================
	  cCombBox = (CComboBox*)GetDlgItem(IDC_COMBO1);
	  cListLis = (CListCtrl*)GetDlgItem(IDC_LIST1);
	  cEdit_gw = (CEdit*)    GetDlgItem(IDC_EDIT4);  //����
	  cEdit_st = (CEdit*)    GetDlgItem(IDC_EDIT1);  //��ʼ
	  cEdit_ed = (CEdit*)    GetDlgItem(IDC_EDIT2);  //����
	  cEdit_ou = (CEdit*)    GetDlgItem(IDC_OUT);    //���
	  cEdit_MC = (CEdit*)    GetDlgItem(IDC_EDIT5);  //MAC
   //=======================�ؼ�����=============================

	  _InitButton((CButton*)GetDlgItem(IDC_BUTTON4),(CButton*)GetDlgItem(IDC_BUTTON5),(CButton*)GetDlgItem(IDC_BUTTON1),(CButton*)GetDlgItem(IDC_BUTTON2),(CButton*)GetDlgItem(IDC_BUTTON3));

   //=======================��ʼ���б��=========================
	  if(_InitListCtrl(cListLis)) { MessageBox(TEXT("�б��ʼ��ʧ��!"),_T("����"),MB_OK); exit(0);}  //��ʼ��ʧ��!
   //=======================��ʼ���б��=========================



  //=======================��ʼ���б��=========================
	  _List_Add(cListLis,_T("111.1.1.1"),_T("AA:AA:AA::AA::A")); //������ ��ע�͵�
  //=======================��ʼ���б��=========================



	 




	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CAdministratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAdministratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAdministratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAdministratorDlg::OnBnClickedScan()
{
		
	
	pcap_if_t *allDeves = NULL;

	int iRet = 0;
	iRet = pcap_findalldevs(&allDeves,NULL);


	if(iRet == -1 ) {MessageBox(TEXT("�Բ�!��ȡʧ��!!!���ǲ���û��װWinPcap����?"),TEXT("����"),MB_OK); exit(1);}
	
	pcap_if_t *i = allDeves;


	  int iCount = 0;

	  for (;i!=NULL && iCount<= ���������;i=i->next)
	{
        //MessageBox(TEXT("AAAA"),TEXT("1"),MB_OK);
		lstrcpyA(Net[iCount].szNetName,i->description);
		
		lstrcpyA(Net[iCount].szNetGuid,i->name);
		//����
		++iCount;
	}
	  /*��ӡ���б��*/
	  if(!cCombBox) {MessageBox(TEXT("�Բ�!��ȡ�б��ָ��ʧ��!"),TEXT("����"),MB_OK); exit(1);}


	  /* ����б�� */
	  cCombBox->ResetContent();
	  //MessageBox(TEXT("1"),TEXT("1"),MB_OK);
	  for (int i = 0; i < iCount; i++)
	  {
		//   MessageBox(TEXT("2"),TEXT("1"),MB_OK);
		  //���Ͳ�ƥ��!�Ҳ�!

		  if(0 == Net[i].szNetGuid) break;

		  /*���ش�С*/
		  size_t size =  _AtoW(Net[i].szNetName,NULL);
	
		  TCHAR *szTchar = new TCHAR[size + 1];

		  memset(szTchar,0,size+1);

		  _AtoW(Net[i].szNetName,szTchar);

	      szTchar[size]  = 0;

		  cCombBox->InsertString(-1,szTchar);  //�ں������ ���������Ϊ����

		  delete szTchar;

		 //  MessageBox(TEXT("3"),TEXT("1"),MB_OK);

	  }
	  /* ѡ�е�һ�� */
	  cCombBox->SetCurSel(0);
	
	  /* ��� */
	  pcap_freealldevs(allDeves);




}




//=========================================
/*     DDOS                             */
void CAdministratorDlg::OnBnClickedButton2()
{
	
}
//=========================================



void CAdministratorDlg::OnBnClickedButton3()
{

		if(_Arp_Scaning()){ MessageBox(TEXT("����ɨ��- - "),TEXT(" - -"),MB_OK); return ;}
	POSITION Index ;
	Index =  cListLis->GetFirstSelectedItemPosition();
	if(!Index) {MessageBox(TEXT("�㻹ûѡ��- -"),TEXT("...."),MB_OK); return ;}
	TCHAR _szTchar[200]={0};
	_List_GetHanlde(cListLis,_szTchar,(int)Index-1);

	

	TerminateThread((HANDLE)_wtoi(_szTchar),0);

	_Set_Mac_MySelf("");

	


}


void CAdministratorDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
		*pResult = 0;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}






/*     ����ɨ��   ARP           */

void CAdministratorDlg::OnBnClickedButton4()
{

	/*  Debug                          */
	/*TCHAR __szStr[255]={0};          */
	/*_List_GetMac(cListLis,__szStr,0);*/
	/*MessageBox(__szStr,NULL,MB_OK);  */

	if(cEdit_st->GetWindowTextLengthW()<=6 || cEdit_st->GetWindowTextLengthW()>15){ MessageBox(_T("����"),TEXT("- -"));return ;}

	/* �ѵ�ǰ�����������              */
	cListLis->DeleteAllItems();

	char __szSt[255]={0},__szEnd[255]={0};
	::GetWindowTextA(cEdit_st->m_hWnd,__szSt,255);
	::GetWindowTextA(cEdit_ed->m_hWnd,__szEnd,255);
	USHORT __i = lstrlenA(__szEnd);
	USHORT __q = lstrlenA(__szSt);
	while (__i--)
	{
		if('.'==__szEnd[__i]) {break;}
	}
	while (__q--)
	{
		if('.'==__szSt[__q]) {break;}
	}
	USHORT __len  = atoi(&__szEnd[__i]+1)  -  atoi(&__szSt[__q+1]);
	if(__len>255) {MessageBox(TEXT("???��ʲô"),TEXT(""),MB_OK);return ;}

	/*  ���� �������� ��Ҫ�������߳������� __len */
	
	_Arp_StartScan(__szSt,atoi(&__szSt[__q]+1),atoi(&__szEnd[__i]+1));

	/* ���뵽�������                            */
	
	_Edit_Add_W(cEdit_ou,TEXT("����ARPɨ��\r\n"));

	/* �Ѱ�Ŧ��ֹס */

	_Button_Disable((CButton*)GetDlgItem(IDC_BUTTON4),false);
	



	
}








/*     ����ɨ��    PING         */

void CAdministratorDlg::OnBnClickedButton5()
{
	MessageBox(TEXT("����ͨ��PING (ICMP) ɨ��İ취ֻ�ܻ�ȡIP Ȼ����ȥ��ȡARP �Ƚ��鷳 �Ͳ�����!��֪����ô���Ŀ��Լ���QQ1462063314",TEXT("����"),MB_OK));

}









/*     ARP����                  */
void CAdministratorDlg::OnBnClickedButton1()
{
	/* ȡ�� */
	/* ��ȡ��ǰѡ�е� */

	if(_Arp_Scaning()){ MessageBox(TEXT("����ɨ��- - "),TEXT(" - -"),MB_OK); return ;}
	POSITION Index ;
	Index =  cListLis->GetFirstSelectedItemPosition();
	if(!Index) {MessageBox(TEXT("�㻹ûѡ��- -"),TEXT("...."),MB_OK); return ;}


	/* �Ƿ�ȷ�� */
	TCHAR _Mac[200]={0},_IP[200]={0};
	_List_GetMac(cListLis,_Mac,(int)Index-1);
	_List_GetiP(cListLis,_IP,(int)Index-1);
	USHORT _ret = ::MessageBoxW(0,_Mac,TEXT("ȷ��Ҫ������MAC������ƭô???"), 1);
	//if(_ret) //ȷ��
	//{
	//��ǰѡ�ֵ�����
//	Net[cCombBox->GetCurSel()].szNetGuid;
	
	_Arp_Attack(_Mac,_IP,Net[cCombBox->GetCurSel()].szNetGuid,(int)Index-1); //ֱ�Ӱ��������ȥ��OK  \\Device\\XXXXXXXX   ֱ�Ӵ� {xx-xx-xx} ����
	//}
	

	 
	
}



/* ���û�ѡ�е�ʱ��!�ͻ����������� */
void CAdministratorDlg::OnCbnCloseupCombo1()
{
	/*
	Debug MessageBoxA(0,"","",MB_OK);
	*/


	/* ��ǰѡ���� */
	int __Index = cCombBox->GetCurSel();
	/* ��ǰѡ���� */
	
	if(__Index<0) {MessageBox(TEXT("���!�㻹ûѡ!"),NULL,MB_OK); return ;}


	CString __string;
	cCombBox->GetWindowTextW(__string);

	/* Nothing*/
	if(__string.GetString()[0]==0) {return ;}
	/* Nothing*/

	/* Debug */
	//_iP_iSok(TEXT("192.168.1.1"));

	/* Debug */
	//MessageBoxW(__string.GetString(),NULL,NULL);


	/* */
	char __szGw[255]={0};
	char __szip[255]={0};
	if(false == _iP_GetiP(Net[__Index].szNetGuid,__szip,__szGw)) MessageBox(TEXT("iP�����ػ�ȡʧ��"),TEXT("Waring!"),MB_OK);
	::SetWindowTextA(cEdit_gw->m_hWnd,__szGw);


	//ͬʱ�����¿�ʼIP
	::SetWindowTextA(cEdit_st->m_hWnd,__szip);

	//��ȡ����MAC

	/* ����� IP*/
	_Set_IP_MySelf(__szip); //������IP
	/* ����� IP*/

	/* ���������IP*/
	_Set_Gw_MySelf(__szGw);


	/* ����� MAC*/
	       /* ת����CHAR*/
	    TCHAR _sz[100]={0},_szmac[100]={0};
		char szMac[100]={0};
	   ::GetWindowTextW(cEdit_st->m_hWnd,_sz,100);  //���÷�����ת��- -
	   _Other_GetMacByIp(_sz,_szmac);
	   cEdit_MC->SetWindowTextW(_szmac);
	   ::GetWindowTextA(cEdit_MC->m_hWnd,szMac,100);
	   _Set_Mac_MySelf(szMac);
	/* ����� MAC*/
	



	

	//���ý���IP ����Ͳ�����д�������� - - 




	/* ====����ʵ��(  ����ȡ�� ǰ��Ĳ��� ���� 192.168.1.1  ȡ�� 192.168.1.   Ȼ���ӡ�� 192.168.1.255  )*/
	char __szTemp[255]={0};
	for (int i = lstrlenA(__szip); i > 0; i--)
	{
		if( '.' == __szip[i])
		{
			lstrcpynA(__szTemp,__szip,i + 1);
			break;
		
		}
	}
	lstrcatA(__szTemp,".");
	//MessageBoxA(0,__szTemp,NULL,MB_OK);
	/* ====����ʵ��(  ����ȡ�� ǰ��Ĳ��� ���� 192.168.1.1  ȡ�� 192.168.1.   Ȼ���ӡ�� 192.168.1.255  )*/
	char __sz255[20] = {0};
	_itoa_s(254,__sz255,10);

	lstrcatA(__szTemp,__sz255);


	::SetWindowTextA(cEdit_ed->m_hWnd,__szTemp);
	

	



}


void CAdministratorDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�



	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CAdministratorDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
