#ifndef _DL_NET_SDK_H_
#define _DL_NET_SDK_H_


#ifdef UDP_EXPORTS
#define NET_CARD_API extern "C"__declspec(dllexport)
#else

#define NET_CARD_API extern "C"__declspec(dllimport)

#endif

/*******************Maximum packet communication **********************/
#define MAX_BUFFER_SIZE		(1024 * 2)
/*******************Equipment Identity **********************/
#define	DEVICE_NET_ACCESS			0x11    /* Access Controller */
#define	DEVICE_NET_ELEVATOR			0x21    /* Elevator controller */
#define	DEVICE_NET_ELEVATOR_EX		0x22    /* Floors interface expansion board */
#define	DEVICE_NET_ELEVATOR_TALK	0x23    /* Talk linkage signal acquisition */
#define	DEVICE_NET_CARPARK			0x31    /* Park Controller */
#define	DEVICE_NET_CARPARK_LED		0x37    /* Park Controller's LED */
#define	DEVICE_NET_CARPARK_GUIDE	0x38    /* Park Guide Controller  */
#define	DEVICE_NET_CONSUMER			0x41    /* Consumer Controller */
#define	DEVICE_NET_DATA_COLLECTOT   0x61    /* Data Gather */
#define	DEVICE_NET_READERV			0x91    /* Serial Reader */
#define	DEVICE_NET_ISSUING_DEV		0xA1    /* ID,IC Sender */
#define	DEVICE_NET_ISSUING_RWDEV    0xA2    /* IC Read and write Reader */

/*******************Communication status return code **********************/
#define COM_STATUS_OK				0    /* The command was successful */
#define	COM_STATUS_INVALID			1    /* Command is invalid */
#define	COM_STATUS_PARA_INVALID     2    /* Invalid parameter */
#define	COM_STATUS_NEED_CLEARCARD   3    /* the sorting of the download card information cannot be allowed. Please try again after cleaning the space */
#define	COM_STATUS_UNKNOW_COMMAND   4    /* Unknown command.. */
#define	COM_STATUS_NO_AUTHORITY	    5    /* Unauthorized*/
#define	COM_STATUS_DEVICE_DAMAGE    6    /* Equipment trouble */
#define	COM_STATUS_OPERATE_FAIL     7    /* The failed command operation */
#define	COM_STATUS_RECEIVE_FAIL	    8    /* The unsuccessful acceptance of the command*/
#define	COM_STATUS_FLASH_FULL       9    /* The insufficient FLASH for the controller */
#define	COM_STATUS_NO_RECORD        10   /* No record in the controller */
#define	COM_STATUS_NO_THECARD       11   /* None of the card information */
#define	COM_STATUS_RECORD_END       12   /* All the records in the controller have been read */ 


/*******************设置多门互锁码 **********************/
#define	INTER_LOCK_NULL                 0x00000000    /* NO Interlock */
#define	INTER_LOCK_DOOR1_DOOR2          0x01010000    /* Door1,Door2 Interlock */
#define	INTER_LOCK_DOOR1_DOOR3          0x01000100    /* Door1,Door3 Interlock */
#define	INTER_LOCK_DOOR1_DOOR4          0x01000001    /* Door1,Door4 Interlock */
#define	INTER_LOCK_DOOR2_DOOR3          0x00010100    /* Door2,Door3 Interlock */
#define	INTER_LOCK_DOOR2_DOOR4          0x00010001    /* Door2,Door4 Interlock */
#define	INTER_LOCK_DOOR3_DOOR4          0x00000101    /* Door3,Door4 Interlock */
#define	INTER_LOCK_DOOR1_DOOR2_DOOR3	0x01010100    /* Door1,Door2,Door3 Interlock */
#define	INTER_LOCK_DOOR1_DOOR2_DOOR4	0x01010001    /* Door1,Door2,Door4 Interlock */
#define	INTER_LOCK_DOOR1_DOOR3_DOOR4	0x01000101    /* Door1,Door3,Door4 Interlock */
#define	INTER_LOCK_DOOR2_DOOR3_DOOR4	0x00010101    /* Door2,Door3,Door4 Interlock */
#define	INTER_LOCK_ALL                  0x01010101    /* Door1,Door2,Door3,Door4 Interlock */


/*******************struct Year month day hour minute second **********************/
typedef struct tagNET_DVR_TIME_EX
{
	unsigned char wYear;    //Note: Year only one byte,2013 ==>13  2014==>14
	unsigned char byMonth;
	unsigned char byDay;
	unsigned char byHour;
	unsigned char byMinute;
	unsigned char bySecond;

}NET_CARD_TIME,*LPNET_CARD_TIME;

/*******************struct Run State **********************/
typedef struct{
 
	unsigned char       m_iDoorCi;		 //Magnetic status
	unsigned char       m_iOpenBtn;		 //Exit button status
	unsigned char       m_iInput;		 //Input status
	unsigned short      m_iDisOnlineCardNums;//2Bytes Offline recording 2Bytes
	unsigned short      m_iRealCardNums;	 //2Bytes real recording 2Bytes
	unsigned short	    m_iCardNumTemp;		 //2Bytes Temporary number of cards
	unsigned short      m_iCardNumSort;		 //2Bytes Sort number of cards
	unsigned short      m_iCardRepeat;		 //2Bytes Repeat card number
	unsigned short      m_iCardNumSortBAK;   //2Bytes The number of Bakup card

}NET_CARD_DOORSTATUS,*LPNET_CARD_IPADDR;

/*******************struct Network parameters **********************/
typedef struct{

	unsigned char   m_sNetIP[4];	    //IP 
	unsigned char   m_sNetMAC[6];       //MAC
	unsigned char   m_sNetGate[4];	    //Gate  
	unsigned char   m_sNetMask[4];	    //MASK
	unsigned char   m_nNetPort[2];      //PORT
	unsigned char   Reserve[3];			//1102
	unsigned char   m_nDoorNum;			//Door num
	unsigned char   m_sVersion[16];     //Version

}NET_CARD_DEVICENETPARA,*LPNET_CARD_DEVICENETPARA;

/**********struct Door password **********/
typedef struct{

	unsigned char   Door01Password1[2];		//Door1  password 1 
	unsigned char   Door01Password2[2];		//Door1  password 2    
	unsigned char   Door01Password3[2];		//Door1  password 3    
	unsigned char   Door01Password4[2];		//Door1  password 4   

	unsigned char   Door02Password1[2];		//Door2  password 1    
	unsigned char   Door02Password2[2];		//Door2  password 2   
	unsigned char   Door02Password3[2];		//Door2  password 3     
	unsigned char   Door02Password4[2];		//Door2  password 4   
	
	unsigned char   Door03Password1[2];		//Door3  password 1   
	unsigned char   Door03Password2[2];		//Door3  password 2 
	unsigned char   Door03Password3[2];		//Door3  password 3   
	unsigned char   Door03Password4[2];		//Door3  password 4  

	unsigned char   Door04Password1[2];		//Door4  password 1   
	unsigned char   Door04Password2[2];		//Door4  password 2  
	unsigned char   Door04Password3[2];		//Door4  password 3  
	unsigned char   Door04Password4[2];		//Door4  password 4 


}NET_CARD_DOORPASSWORD,*LPNET_DOORPASSWORD;

/*******************struct Stress password*******************/
typedef struct{

	unsigned char   Door01Password[2];		//Doo1 Stress password
	unsigned char   Door02Password[2];		//Doo2 Stress password
	unsigned char   Door03Password[2];		//Doo3 Stress password 
	unsigned char   Door04Password[2];		//Doo4 Stress password  

}NET_CARD_DOORDURESSWORD,*LPNET_CARD_DOORDURESSWORD;




/*******************struct Open delay*******************/
typedef struct{

	unsigned char   Door01DelayTime;		//Door1 Open delay  1-255S
	unsigned char   Door02DelayTime;		//Door2 Open delay  1-255S
	unsigned char   Door03DelayTime;		//Door3 Open delay  1-255S
	unsigned char   Door04DelayTime;		//Door4 Open delay  1-255S 

}NET_CARD_OPEN_DELAY,*LPNET_CARD_OPEN_DELAY;

/*******************struct Alarm Out Delay*******************/
typedef struct{

	unsigned short   Alarm01DelayTime;		//Alarm Out1 Delay 0-65535s 2B
	unsigned short   Alarm02DelayTime;		//Alarm Out2 Delay 0-65535s 2B
	unsigned short   Alarm03DelayTime;		//Alarm Out3 Delay 0-65535s 2B
	unsigned short   Alarm04DelayTime;		//Alarm Out4 Delay 0-65535s 2B

}NET_CARD_ALARM_DELAY,*LPNET_CARD_ALARM_DELAY;

/*******************struct Magnetic,Stress Out Delay****************/
typedef struct{

	unsigned short   LightOpenDelayTime;	//Magnetic  Delay 0-65535s 2B
	unsigned short   DruessDelayTime;		//Stress    Delay 0-65535s 2B

}NET_CARD_LIGHT_DELAY,*LPNET_LIGHT_DELAY;

/*******************struct One Card Information 33Bytes *****************/
typedef struct{

	unsigned char   CardID[4];				//Card Series 
	unsigned char   OpenType;				//pass type:card(0) or card+password(1)
	unsigned char   Door01Password[2];		//Door1 password1 default: 0xff,0xff
	unsigned char   Door02Password[2];		//Door2 password1 default: 0xff,0xff 
	unsigned char   Door03Password[2];		//Door3 password1 default: 0xff,0xff   
	unsigned char   Door04Password[2];		//Door4 password1 default: 0xff,0xff  
	unsigned char   EndYear;				//Validity Year		default:0xff,  
	unsigned char   EndMonth;				//Validity Month	default:0xff,  
	unsigned char   EndDay;					//Validity Day		default:0xff,   
	unsigned char   Reserve1[3];			//default: 0xff,0xff,0xff,保留字节
	unsigned char   MultiCardType;			//default: 0x00, 0x01 3cards;0x02 4cards;0x03 5cards (5 cards open the door)
	                                        //01 10 00 01 door4 3cards,door2 4cards,door1 3cards 
	unsigned char   RemoteOpenType;			//default: 0x00,Confirm door remote mode (high 4b),Different groups or same group to open the door (low 4b)										    
	unsigned char   OpenDoorType;		    //default: 0x00,
											//00 General group,01 Dual card,02first card,03By the first card limit
	unsigned char   Reserve2;				//default: 0x00
	unsigned char   CardStatus;				//default: 0x00, //00 Normal Cards,01 Loss card,02 Validity Card 03Delete card
	unsigned char   OpenWhichDoor;			//default: 0xff,Four doors cannot to open; 0xf0 Four doors can open											
	unsigned char   WeekAndHolidayCode[4];	//默认0x00 No holiday,
											//week program no. and holiday num.  The first one byte is  door1 weekly programming and holiday programming Number...										
 	unsigned char   Reserve3[3];			//default: 0xff
	unsigned char   Reserve4;				//default: 0xff


}NET_CARD_ONECARDINFO,*LPNET_CARD_ONECARDINFO;


/*******************struct Record information 17Bytes*****************/
typedef struct{
	unsigned char   Record_CardID[4];		//card series  
	unsigned char   Record_Time[6];			//Year month day hour minute second
	unsigned char   Record_EventNum;		//recoder ID:0-255
	unsigned char   Record_DevMAC[5];		//5 bytes of the MAC address	
	unsigned char   Record_DoorNum;			//Door num (1-8)  Low 3bit ,Hight 5 bit Does not require 

}NET_CARD_RECORDINFO,*LPNET_CARD_RECORDINFO;

/*******************struct Record information 17Bytes*****************/
typedef struct{
	 char   IDCard_Name[31];		//Name
	 char    IDCard_NameLength;
	 char   IDCard_Sex;			//1 Male 2 Female 3 other ==1 男，2 女，3 其它
	 char   IDCard_National;		//National ==民族 0-55
	 char   IDCard_Birthday[9];		//birthday ==生日 19801020
	 char   IDCard_Address[71];     //address ==住址
	 char    IDCard_AddressLength;    
	 char   IDCard_IDNumber[19];     //IDNumber ==身份证号码
	 char   IDCard_Issuing[30];     //Issuing authority ==签发机关
	 char    IDCard_IssuingLength;
	 char   IDCard_Validity_StartDate[9];    //Validity_Start ==有效开始日期
	 char   IDCard_Validity_EndDate[9];      //Validity_Start ==有效结束日期

}NET_CARD_IDCARDINFO,*LPNET_CARD_IDCARDINFO;

typedef int (__stdcall *_PRequstCallback)(char *Buff,int nLen);
typedef int (__stdcall *_PProcessCallback)(NET_CARD_RECORDINFO *pRecordInfo,char *pReturnIP,int *ReturnIPLen,char *pReturnDevMAC);
typedef int (__stdcall *_PBroadcastSearchCallback)(NET_CARD_DEVICENETPARA *pNetParameter,char *pReturnIP,int *ReturnIPLen,char *pReturnDevMAC);

typedef int (__stdcall *_PProcessCallbackEx)(char *pData,int *DataLength,int nDataType,char *pReturnIP,int *ReturnIPLen,char *pReturnDevMAC,char *pIDBuffer,int *ReturnIDBufferLen,int ReaderNo);

//Real-time monitoring callback function
NET_CARD_API void  __stdcall NET_CARD_RealTimeDataCallback(_PProcessCallback pProcessCallback );

NET_CARD_API void  __stdcall NET_CARD_RealTimeDataCallbackEx(_PProcessCallbackEx pProcessCallbackEx );

//Broadcast Search  callback function
NET_CARD_API void  __stdcall NET_CARD_BroadcastSerachDevice(_PBroadcastSearchCallback pProcessCallback );
 
//DLL init
NET_CARD_API int   __stdcall  NET_CARD_InitEx(char  *szLocalIP,int nLocalPort=9000,int WaitTimout = 3000);
//DLL Exit
NET_CARD_API void  __stdcall  NET_CARD_Cleanup(void);

/**********************Device Operation****************************************/
//Get Run state
NET_CARD_API  int  __stdcall NET_CARD_GetRunStatus(int DevType,char *szRemoteIP, int nRemotePort,NET_CARD_DOORSTATUS *pReturnStatus=NULL,char *pReturnDevMAC=NULL);
//Get device's time
NET_CARD_API  int  __stdcall NET_CARD_DetectDeviceOnline(int DevType,char *szRemoteIP, int nRemotePort,char *pReturnDevMAC=NULL,NET_CARD_TIME *pReturnDeviceTime=NULL);
//Remote Open
NET_CARD_API  int  __stdcall NET_CARD_RemoteOpen(int DevType,char *szRemoteIP, int nRemotePort,int nReaderNo,char *pReturnDevMAC=NULL);
//Remote Close
NET_CARD_API  int  __stdcall NET_CARD_RemoteClose(int DevType,char *szRemoteIP, int nRemotePort,int nReaderNo,char *pReturnDevMAC=NULL);

//Door always Open
NET_CARD_API  int  __stdcall NET_CARD_AlwayOpen(int DevType,char *szRemoteIP, int nRemotePort,int nReaderNo,char *pReturnDevMAC=NULL);
//Door RecoveryState
NET_CARD_API  int  __stdcall NET_CARD_RecoveryState(int DevType,char *szRemoteIP, int nRemotePort,int nReaderNo,char *pReturnDevMAC=NULL);

//Enable the door opened out alarm
NET_CARD_API  int  __stdcall NET_CARD_EnableTimeOutAlarm(int DevType,char *szRemoteIP, int nRemotePort,int nEnable,char *pReturnDevMAC=NULL);
//Device init
NET_CARD_API  int  __stdcall NET_CARD_DeviceInit(int DevType,char *szRemoteIP, int nRemotePort,char *pReturnDevMAC=NULL);
//Read Version
NET_CARD_API  int  __stdcall NET_CARD_ReadDeviceVersion(int DevType,char *szRemoteIP, int nRemotePort,char *pReturnDevMAC=NULL,char *pReturnVersion=NULL);
//Setting Device's Time
NET_CARD_API  int  __stdcall NET_CARD_SetDeviceTime(int DevType,char *szRemoteIP, int nRemotePort,NET_CARD_TIME *pDevTime,char *pReturnDevMAC=NULL);
//Setting Server IP and Port
NET_CARD_API  int  __stdcall NET_CARD_SetServerIPandPort(int DevType,char *szRemoteIP, int nRemotePort,char *pServerIP=NULL,int nServerPort=9000,char *pReturnDevMAC=NULL);
//Clear Server IP and Port
NET_CARD_API  int  __stdcall NET_CARD_ClearServerIPandPort(int DevType,char *szRemoteIP, int nRemotePort,char *pReturnDevMAC);
//Search device by device's IP
NET_CARD_API  int  __stdcall NET_CARD_SearchDeviceByIP(int DevType,char *szRemoteIP, int nRemotePort,NET_CARD_DEVICENETPARA *pNetParameter,char *pReturnDevMAC=NULL);
//Broadcast Search all devices
NET_CARD_API  int  __stdcall NET_CARD_BroadCastSearchDevice(int DevType,char *szRemoteIP,int nRemotePort=9998);
//Broadcast Search all devices
NET_CARD_API  int  __stdcall NET_CARD_BroadCastSearchDeviceEx(int DevType,char *szRemoteIP,int nRemotePort=9998);

//Setting lock delay
NET_CARD_API  int  __stdcall NET_CARD_SetOpenDelayTime(int DevType,char *szRemoteIP, int nRemotePort,NET_CARD_OPEN_DELAY *pDelayTime,char *pReturnDevMAC=NULL);
//Setting Alarm out delay 
NET_CARD_API  int  __stdcall NET_CARD_SetAlarmDelayTime(int DevType,char *szRemoteIP, int nRemotePort,NET_CARD_ALARM_DELAY *pDelayTime,char *pReturnDevMAC=NULL);
//Setting magnic and stress out delay
NET_CARD_API  int  __stdcall NET_CARD_SetDuressAlarmDelayTime(int DevType,char *szRemoteIP, int nRemotePort,NET_CARD_LIGHT_DELAY *pDelayTime,char *pDevMAC=NULL);
//Setting lock type
NET_CARD_API  int  __stdcall NET_CARD_SetLockType(int DevType,char *szRemoteIP, int nRemotePort,unsigned char nLockType,char *pDevMAC=NULL);
//Setting network parameter
NET_CARD_API  int  __stdcall NET_CARD_SetNetWorkParameter(int DevType,char *szRemoteIP, int nRemotePort,char *pOldNetMAC,NET_CARD_DEVICENETPARA *pNetParameter,char *pReturnDevMAC=NULL);
//Start realtime monitor
NET_CARD_API  int  __stdcall NET_CARD_EnableRealTimeMonitor(int DevType,char *szRemoteIP, int nRemotePort,char *pReturnDevMAC=NULL);
//Stop realtime monitor
NET_CARD_API  int  __stdcall NET_CARD_DisbleRealTimeMonitor(int DevType,char *szRemoteIP, int nRemotePort,char *pReturnDevMAC=NULL);
//Setting interlock
NET_CARD_API  int  __stdcall NET_CARD_SetInterLock(int DevType,char *szRemoteIP, int nRemotePort,char *pInterLock,char *pReturnDevMAC=NULL);
//Setting password password open door
NET_CARD_API  int  __stdcall NET_CARD_SetDoorPassWord(int DevType,char *szRemoteIP, int nRemotePort,NET_CARD_DOORPASSWORD *pPassword,char *pReturnDevMAC=NULL);
//Setting Stress password
NET_CARD_API  int  __stdcall NET_CARD_SetDoorDuressPassWord(int DevType,char *szRemoteIP, int nRemotePort,NET_CARD_DOORDURESSWORD *pPassword,char *pReturnDevMAC=NULL);

//Set Magnetic input level
NET_CARD_API  int  __stdcall NET_CARD_SetMagneticInputHL(int DevType,char *szRemoteIP, int nRemotePort,unsigned char nMagType,char *pReturnDevMAC=NULL);
//Read Magnetic input level
NET_CARD_API  int  __stdcall NET_CARD_ReadMagneticInputHL(int DevType,char *szRemoteIP, int nRemotePort,unsigned char *nMagType,char *pReturnDevMAC=NULL);

//QR and 2RD Function //20150706
//Setting Server TCP  IP and Port
NET_CARD_API  int  __stdcall NET_CARD_Set_QR_ServerTCPIPAndPort(int DevType,char *szRemoteIP, int nRemotePort,char *pServerIP=NULL,int nServerPort=9000,char *pReturnDevMAC=NULL);

//Setting Server UDP  IP and Port
NET_CARD_API  int  __stdcall NET_CARD_Set_QR_ServerUDPIPAndPort(int DevType,char *szRemoteIP, int nRemotePort,char *pServerIP=NULL,int nServerPort=9000,char *pReturnDevMAC=NULL);

//Setting Server Record UDP  IP and Port
NET_CARD_API  int  __stdcall NET_CARD_Set_RecordUpLoad_UDPIPAndPort(int DevType,char *szRemoteIP, int nRemotePort,char *pServerIP=NULL,int nServerPort=9000,char *pReturnDevMAC=NULL);

//Get ALLServerIPandPort
//Server TCP  IP and Port 6B(IP 4B,Port 2B)
//Server UDP  IP and Port 6B(IP 4B,Port 2B)
//Server Record UDP  IP and Port 6B(IP 4B,Port 2B)
NET_CARD_API  int  __stdcall NET_CARD_Get_ALLServerIPandPort(int DevType,char *szRemoteIP, int nRemotePort,char *pReturnChar=NULL,int *ReturnBufLen=NULL,char *pReturnDevMAC=NULL);


//Voice Function
//VoiceCode Voice code for Example:B1 欢迎光临
//VoiceCodeLength  1
//nbOpenDoor if open door or not  1:open 0 No Open
//nReaderNo if nbOpenDoor=1 which door or somedoors
NET_CARD_API  int  __stdcall NET_CARD_VoiceAndOpen(int DevType,char *szRemoteIP, int nRemotePort,char * VoiceCode,int VoiceCodeLength,int nbOpenDoor=0,int nReaderNo=0,char *pReturnDevMAC=NULL);

//蓝牙参数，通过网络设置
//bluetooth parameter
NET_CARD_API  int  __stdcall NET_CARD_Set_BTName(int DevType,char *szRemoteIP, int nRemotePort,unsigned char * NameByte,int nLength,char *pReturnDevMAC=NULL);
NET_CARD_API  int  __stdcall NET_CARD_Set_BTPassword(int DevType,char *szRemoteIP, int nRemotePort,unsigned char * NameByte,int nLength,char *pReturnDevMAC=NULL);

/**********************************Card Operation***************************/
//Clear all cards 
NET_CARD_API  int  __stdcall NET_CARD_ClearAllCardInfo(int DevType,char *szRemoteIP, int nRemotePort,char *pReturnDevMAC);
//Login a card
NET_CARD_API  int  __stdcall NET_CARD_DownOneCardInfo(int DevType,char *szRemoteIP, int nRemotePort,NET_CARD_ONECARDINFO *pOneCardInfo,int OneCardInfoLength=33, char *pReturnDevMAC=NULL);
//Read a card infomation
NET_CARD_API  int  __stdcall NET_CARD_GetOneCardInfo(int DevType,char *szRemoteIP, int nRemotePort,char *CardID,NET_CARD_ONECARDINFO *pReturnOneCardInfo,char *pReturnDevMAC=NULL);
//Get history record
NET_CARD_API  int  __stdcall NET_CARD_GetHistroyRecord(int DevType,char *szRemoteIP, int nRemotePort,int nRecordNumber,int *ReturnNumber,NET_CARD_RECORDINFO *pReturnRecordInfo,char *pReturnDevMAC=NULL);
//Batch login cards  16cards,32cards(8cards)
NET_CARD_API  int  __stdcall NET_CARD_BatchDownCardInfo(int DevType,char *szRemoteIP, int nRemotePort,NET_CARD_ONECARDINFO *pALLCardInfo,int ALLCardInfoLength, int nCardNo, int Totalcards,char *pReturnDevMAC=NULL);
//Enable the controller to Get the card Series
NET_CARD_API  int  __stdcall NET_CARD_EnableReadCardIDFromDevice(int DevType,char *szRemoteIP, int nRemotePort,char *pReturnDevMAC=NULL);
//Get the card Series from the controller card
NET_CARD_API  int  __stdcall NET_CARD_ReadCardIDFromDevice(int DevType,char *szRemoteIP, int nRemotePort,char *pCardID,char *pReturnDevMAC=NULL);

//Login a QR  card
NET_CARD_API  int  __stdcall NET_CARD_Down_QR_CardInfo(int DevType,char *szRemoteIP, int nRemotePort,NET_CARD_ONECARDINFO *pOneCardInfo,int OneCardInfoLength=33, char *pReturnDevMAC=NULL);
//Get QR Card Number
NET_CARD_API  int  __stdcall NET_CARD_Read_QR_CardNumber(int DevType,char *szRemoteIP, int nRemotePort,int * QRCardNum, char *pReturnDevMAC=NULL);
//Get QR Card Number
NET_CARD_API  int  __stdcall NET_CARD_Clear_QR_CardNumber(int DevType,char *szRemoteIP, int nRemotePort,char *pReturnDevMAC=NULL);

NET_CARD_API  int  __stdcall NET_CARD_EnableTCPServerMode(char *TCPServerIP,int nTCPServerUDPPort,int nEnable);

#endif
