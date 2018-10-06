
// AdministratorDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "Administrator.h"
#include "AdministratorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif





/*/* WinPcap SDK     */ 
//#include "pcap.h"  //自己上百度找!别忘了还有lib




/* Smm.h            */
#include "Smm.h"





/*  宏定义   */
#define 最大网卡数 15





/*  控件变量  */
//CListBox  *cListBox = 0; //网卡列表
CComboBox *cCombBox = 0; //
CListCtrl *cListLis = 0; //
CEdit     *cEdit_gw    = 0;  // 网关
CEdit     *cEdit_st    = 0;  //开始IP编辑框
CEdit     *cEdit_ed    = 0;  //结束IP编辑框
CEdit     *cEdit_ou    = 0;  //输出编辑框
CEdit     *cEdit_MC    = 0;  //MAC编辑框
CButton   *cButt_ap    = 0;  //ARP扫描
/*  控件变量  */






/* 结构定义 */
struct szNet
{
	char szNetName[200]; //网卡名
	char szNetGuid[200]; //GUID
};
/* 结构定义 */


/* szNet变量     */

szNet Net[最大网卡数] = {0};

/* szNet变量     */









// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CAdministratorDlg 对话框



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


// CAdministratorDlg 消息处理程序

BOOL CAdministratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	//cListBox = (CListBox*) GetDlgItem(IDC_LIST1);








	//=======================控件变量============================
	  cCombBox = (CComboBox*)GetDlgItem(IDC_COMBO1);
	  cListLis = (CListCtrl*)GetDlgItem(IDC_LIST1);
	  cEdit_gw = (CEdit*)    GetDlgItem(IDC_EDIT4);  //网关
	  cEdit_st = (CEdit*)    GetDlgItem(IDC_EDIT1);  //开始
	  cEdit_ed = (CEdit*)    GetDlgItem(IDC_EDIT2);  //结束
	  cEdit_ou = (CEdit*)    GetDlgItem(IDC_OUT);    //输出
	  cEdit_MC = (CEdit*)    GetDlgItem(IDC_EDIT5);  //MAC
   //=======================控件变量=============================

	  _InitButton((CButton*)GetDlgItem(IDC_BUTTON4),(CButton*)GetDlgItem(IDC_BUTTON5),(CButton*)GetDlgItem(IDC_BUTTON1),(CButton*)GetDlgItem(IDC_BUTTON2),(CButton*)GetDlgItem(IDC_BUTTON3));

   //=======================初始化列表框=========================
	  if(_InitListCtrl(cListLis)) { MessageBox(TEXT("列表初始化失败!"),_T("悲剧"),MB_OK); exit(0);}  //初始化失败!
   //=======================初始化列表框=========================



  //=======================初始化列表框=========================
	  _List_Add(cListLis,_T("111.1.1.1"),_T("AA:AA:AA::AA::A")); //测试用 请注释掉
  //=======================初始化列表框=========================



	 




	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAdministratorDlg::OnPaint()
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
HCURSOR CAdministratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAdministratorDlg::OnBnClickedScan()
{
		
	
	pcap_if_t *allDeves = NULL;

	int iRet = 0;
	iRet = pcap_findalldevs(&allDeves,NULL);


	if(iRet == -1 ) {MessageBox(TEXT("卧槽!获取失败!!!你是不是没安装WinPcap驱动?"),TEXT("悲剧"),MB_OK); exit(1);}
	
	pcap_if_t *i = allDeves;


	  int iCount = 0;

	  for (;i!=NULL && iCount<= 最大网卡数;i=i->next)
	{
        //MessageBox(TEXT("AAAA"),TEXT("1"),MB_OK);
		lstrcpyA(Net[iCount].szNetName,i->description);
		
		lstrcpyA(Net[iCount].szNetGuid,i->name);
		//自增
		++iCount;
	}
	  /*打印到列表框*/
	  if(!cCombBox) {MessageBox(TEXT("卧槽!获取列表框指针失败!"),TEXT("悲剧"),MB_OK); exit(1);}


	  /* 清空列表框 */
	  cCombBox->ResetContent();
	  //MessageBox(TEXT("1"),TEXT("1"),MB_OK);
	  for (int i = 0; i < iCount; i++)
	  {
		//   MessageBox(TEXT("2"),TEXT("1"),MB_OK);
		  //类型不匹配!我草!

		  if(0 == Net[i].szNetGuid) break;

		  /*返回大小*/
		  size_t size =  _AtoW(Net[i].szNetName,NULL);
	
		  TCHAR *szTchar = new TCHAR[size + 1];

		  memset(szTchar,0,size+1);

		  _AtoW(Net[i].szNetName,szTchar);

	      szTchar[size]  = 0;

		  cCombBox->InsertString(-1,szTchar);  //在后面插入 方便查找作为索引

		  delete szTchar;

		 //  MessageBox(TEXT("3"),TEXT("1"),MB_OK);

	  }
	  /* 选中第一个 */
	  cCombBox->SetCurSel(0);
	
	  /* 清除 */
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

		if(_Arp_Scaning()){ MessageBox(TEXT("正在扫描- - "),TEXT(" - -"),MB_OK); return ;}
	POSITION Index ;
	Index =  cListLis->GetFirstSelectedItemPosition();
	if(!Index) {MessageBox(TEXT("你还没选呢- -"),TEXT("...."),MB_OK); return ;}
	TCHAR _szTchar[200]={0};
	_List_GetHanlde(cListLis,_szTchar,(int)Index-1);

	

	TerminateThread((HANDLE)_wtoi(_szTchar),0);

	_Set_Mac_MySelf("");

	


}


void CAdministratorDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
		*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}






/*     主机扫描   ARP           */

void CAdministratorDlg::OnBnClickedButton4()
{

	/*  Debug                          */
	/*TCHAR __szStr[255]={0};          */
	/*_List_GetMac(cListLis,__szStr,0);*/
	/*MessageBox(__szStr,NULL,MB_OK);  */

	if(cEdit_st->GetWindowTextLengthW()<=6 || cEdit_st->GetWindowTextLengthW()>15){ MessageBox(_T("无语"),TEXT("- -"));return ;}

	/* 把当前的所有清除掉              */
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
	if(__len>255) {MessageBox(TEXT("???搞什么"),TEXT(""),MB_OK);return ;}

	/*  好了 经过计算 需要启动的线程数就在 __len */
	
	_Arp_StartScan(__szSt,atoi(&__szSt[__q]+1),atoi(&__szEnd[__i]+1));

	/* 加入到输出窗口                            */
	
	_Edit_Add_W(cEdit_ou,TEXT("开启ARP扫描\r\n"));

	/* 把按纽禁止住 */

	_Button_Disable((CButton*)GetDlgItem(IDC_BUTTON4),false);
	



	
}








/*     主机扫描    PING         */

void CAdministratorDlg::OnBnClickedButton5()
{
	MessageBox(TEXT("由于通过PING (ICMP) 扫描的办法只能获取IP 然后又去获取ARP 比较麻烦 就不做了!想知道怎么做的可以加我QQ1462063314",TEXT("迷雾"),MB_OK));

}









/*     ARP断网                  */
void CAdministratorDlg::OnBnClickedButton1()
{
	/* 取出 */
	/* 获取当前选中的 */

	if(_Arp_Scaning()){ MessageBox(TEXT("正在扫描- - "),TEXT(" - -"),MB_OK); return ;}
	POSITION Index ;
	Index =  cListLis->GetFirstSelectedItemPosition();
	if(!Index) {MessageBox(TEXT("你还没选呢- -"),TEXT("...."),MB_OK); return ;}


	/* 是否确定 */
	TCHAR _Mac[200]={0},_IP[200]={0};
	_List_GetMac(cListLis,_Mac,(int)Index-1);
	_List_GetiP(cListLis,_IP,(int)Index-1);
	USHORT _ret = ::MessageBoxW(0,_Mac,TEXT("确定要对以下MAC进行欺骗么???"), 1);
	//if(_ret) //确定
	//{
	//当前选种的网卡
//	Net[cCombBox->GetCurSel()].szNetGuid;
	
	_Arp_Attack(_Mac,_IP,Net[cCombBox->GetCurSel()].szNetGuid,(int)Index-1); //直接把这个传过去就OK  \\Device\\XXXXXXXX   直接传 {xx-xx-xx} 不行
	//}
	

	 
	
}



/* 当用户选中的时候!就会调用这个函数 */
void CAdministratorDlg::OnCbnCloseupCombo1()
{
	/*
	Debug MessageBoxA(0,"","",MB_OK);
	*/


	/* 当前选中行 */
	int __Index = cCombBox->GetCurSel();
	/* 当前选中行 */
	
	if(__Index<0) {MessageBox(TEXT("大哥!你还没选!"),NULL,MB_OK); return ;}


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
	if(false == _iP_GetiP(Net[__Index].szNetGuid,__szip,__szGw)) MessageBox(TEXT("iP和网关获取失败"),TEXT("Waring!"),MB_OK);
	::SetWindowTextA(cEdit_gw->m_hWnd,__szGw);


	//同时设置下开始IP
	::SetWindowTextA(cEdit_st->m_hWnd,__szip);

	//获取本机MAC

	/* 保存好 IP*/
	_Set_IP_MySelf(__szip); //设置下IP
	/* 保存好 IP*/

	/* 保存好网关IP*/
	_Set_Gw_MySelf(__szGw);


	/* 保存好 MAC*/
	       /* 转换到CHAR*/
	    TCHAR _sz[100]={0},_szmac[100]={0};
		char szMac[100]={0};
	   ::GetWindowTextW(cEdit_st->m_hWnd,_sz,100);  //不用费力气转了- -
	   _Other_GetMacByIp(_sz,_szmac);
	   cEdit_MC->SetWindowTextW(_szmac);
	   ::GetWindowTextA(cEdit_MC->m_hWnd,szMac,100);
	   _Set_Mac_MySelf(szMac);
	/* 保存好 MAC*/
	



	

	//设置结束IP 这里就不单独写出函数了 - - 




	/* ====功能实现(  首先取出 前面的部分 比如 192.168.1.1  取出 192.168.1.   然后打印上 192.168.1.255  )*/
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
	/* ====功能实现(  首先取出 前面的部分 比如 192.168.1.1  取出 192.168.1.   然后打印上 192.168.1.255  )*/
	char __sz255[20] = {0};
	_itoa_s(254,__sz255,10);

	lstrcatA(__szTemp,__sz255);


	::SetWindowTextA(cEdit_ed->m_hWnd,__szTemp);
	

	



}


void CAdministratorDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。



	// TODO:  在此添加控件通知处理程序代码
}


void CAdministratorDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}
