#include "windows.h"




int _AtoW(char *a,TCHAR* w);             //多字节转宽字节 = =
int _WtoA(char *a,TCHAR* w);             //相反





//================列表框操作函数==============================
int _InitListCtrl(CListCtrl *cListCtrl);                     //初始化列表框
int _List_Add    (CListCtrl *,TCHAR *,TCHAR *);                  //添加一个表项
int _List_GetiP  (CListCtrl *,TCHAR*,int);                            //获取IP
int _List_GetMac (CListCtrl *,TCHAR*,int);                            //获取MAC
int _ListSetMac  (CListCtrl*,TCHAR *,int);                                //设置MAC
int _List_GetHanlde  (CListCtrl *,TCHAR*,int );

//================列表框操作函数==============================






//================按纽操作函数==============================
int _InitButton(CButton*,CButton*,CButton*,CButton*,CButton*);
int _Button_Disable(CButton*,bool);
//================按钮操作函数==============================








//=============ARP扫描线程====================================
void   _Arp_StartScan(char *,int,int);
void   _Arp_Scan      (int);
void   _Arp_Watch     (int);
bool   _Arp_Scaning   ();
//=============ARP扫描线程====================================








//=============IP处理函数=====================================
bool _iP_iSok (TCHAR *);
bool _iP_GetiP(char *,char *,char *);
//=============IP处理函数=====================================










//=============编辑框处理函数=================================
bool _Edit_Add_W(CEdit*,TCHAR* );
bool _Edit_Add_A(CEdit* ,char *); //..........
//=============编辑框处理函数=================================









//=============ARP攻击函数====================================

bool _Arp_Attack(TCHAR *,TCHAR *,char *,int);
bool _Arp_Attack_All_Stop();


//=============ARP攻击函数====================================





//============================================================
/* 获取MAC*/
bool _Other_GetMacByIp(TCHAR *IP,TCHAR *MAC);
bool _Set_IP_MySelf (char *);
bool _Set_Mac_MySelf(char *);
bool _Set_Gw_MySelf (char *);
//============================================================




/*

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
unsigned char  eh_dst[6];  //目的 MAC
unsigned char  eh_src[6];  //源   MAC
unsigned short eh_type;    //协议类型 - -ARP = = 0x0806
}ETHDR,*PETHDR;
*/









