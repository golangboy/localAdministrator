#include "windows.h"




int _AtoW(char *a,TCHAR* w);             //���ֽ�ת���ֽ� = =
int _WtoA(char *a,TCHAR* w);             //�෴





//================�б���������==============================
int _InitListCtrl(CListCtrl *cListCtrl);                     //��ʼ���б��
int _List_Add    (CListCtrl *,TCHAR *,TCHAR *);                  //���һ������
int _List_GetiP  (CListCtrl *,TCHAR*,int);                            //��ȡIP
int _List_GetMac (CListCtrl *,TCHAR*,int);                            //��ȡMAC
int _ListSetMac  (CListCtrl*,TCHAR *,int);                                //����MAC
int _List_GetHanlde  (CListCtrl *,TCHAR*,int );

//================�б���������==============================






//================��Ŧ��������==============================
int _InitButton(CButton*,CButton*,CButton*,CButton*,CButton*);
int _Button_Disable(CButton*,bool);
//================��ť��������==============================








//=============ARPɨ���߳�====================================
void   _Arp_StartScan(char *,int,int);
void   _Arp_Scan      (int);
void   _Arp_Watch     (int);
bool   _Arp_Scaning   ();
//=============ARPɨ���߳�====================================








//=============IP������=====================================
bool _iP_iSok (TCHAR *);
bool _iP_GetiP(char *,char *,char *);
//=============IP������=====================================










//=============�༭������=================================
bool _Edit_Add_W(CEdit*,TCHAR* );
bool _Edit_Add_A(CEdit* ,char *); //..........
//=============�༭������=================================









//=============ARP��������====================================

bool _Arp_Attack(TCHAR *,TCHAR *,char *,int);
bool _Arp_Attack_All_Stop();


//=============ARP��������====================================





//============================================================
/* ��ȡMAC*/
bool _Other_GetMacByIp(TCHAR *IP,TCHAR *MAC);
bool _Set_IP_MySelf (char *);
bool _Set_Mac_MySelf(char *);
bool _Set_Gw_MySelf (char *);
//============================================================




/*

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
unsigned char  eh_dst[6];  //Ŀ�� MAC
unsigned char  eh_src[6];  //Դ   MAC
unsigned short eh_type;    //Э������ - -ARP = = 0x0806
}ETHDR,*PETHDR;
*/









