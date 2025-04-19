using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using System.Runtime.InteropServices;

namespace CSharpDemo
{
    public class NET_CARD
    {
        public NET_CARD()
        {
            //
            // TODO: 在此处添加构造函数逻辑
            //
        }
        public const int    MAX_BUFFER_SIZE	= 2048;
        /*******************Equipment Identity **********************/
        public const int	DEVICE_NET_ACCESS		=	0x11;    // Access Controller 
        public const int	DEVICE_NET_ELEVATOR		=	0x21;    // Elevator controller 
        public const int	DEVICE_NET_ELEVATOR_EX	=	0x22;    /* Floors interface expansion board */
        public const int	DEVICE_NET_ELEVATOR_TALK=	0x23;    /* Talk linkage signal acquisition */
        public const int	DEVICE_NET_CARPARK		=	0x31;    /* Park Controller */
        public const int	DEVICE_NET_CARPARK_LED	=	0x37;    /* Park Controller's LED */
        public const int	DEVICE_NET_CARPARK_GUIDE=	0x38;    /* Park Guide Controller  */
        public const int	DEVICE_NET_CONSUMER		=	0x41;    /* Consumer Controller */
        public const int	DEVICE_NET_DATA_COLLECTOT=  0x61;   /* Data Gather */
        public const int	DEVICE_NET_READERV		=	0x91;   /* Serial Reader */
        public const int	DEVICE_NET_ISSUING_DEV	=	0xA1;    /* ID,IC Sender */
        public const int	DEVICE_NET_ISSUING_RWDEV=   0xA2;    /* IC Read and write Reader */

        /*******************Communication status return code **********************/
        public const int    COM_STATUS_OK			  =	 0;    /* The command was successful */
        public const int	COM_STATUS_INVALID	      =	 1;    /* Command is invalid */
        public const int	COM_STATUS_PARA_INVALID   =  2;    /* Invalid parameter */
        public const int	COM_STATUS_NEED_CLEARCARD =  3;    /* the sorting of the download card information cannot be allowed. Please try again after cleaning the space */
        public const int	COM_STATUS_UNKNOW_COMMAND =  4;    /* Unknown command.. */
        public const int	COM_STATUS_NO_AUTHORITY	  =  5;    /* Unauthorized*/
        public const int	COM_STATUS_DEVICE_DAMAGE  =  6;   /* Equipment trouble */
        public const int	COM_STATUS_OPERATE_FAIL   =  7;    /* The failed command operation */
        public const int	COM_STATUS_RECEIVE_FAIL	  =  8;    /* The unsuccessful acceptance of the command*/
        public const int	COM_STATUS_FLASH_FULL     =  9;    /* The insufficient FLASH for the controller */
        public const int	COM_STATUS_NO_RECORD      =  10;   /* No record in the controller */
        public const int	COM_STATUS_NO_THECARD     =  11;   /* None of the card information */
        public const int	COM_STATUS_RECORD_END     =  12;   /* All the records in the controller have been read */ 


        /*******************设置多门互锁码 **********************/
        public const int	INTER_LOCK_NULL                = 0x00000000;    /* NO Interlock */
        public const int	INTER_LOCK_DOOR1_DOOR2         = 0x01010000;    /* Door1,Door2 Interlock */
        public const int	INTER_LOCK_DOOR1_DOOR3         = 0x01000100;    /* Door1,Door3 Interlock */
        public const int	INTER_LOCK_DOOR1_DOOR4         = 0x01000001;    /* Door1,Door4 Interlock */
        public const int	INTER_LOCK_DOOR2_DOOR3         = 0x00010100;    /* Door2,Door3 Interlock */
        public const int	INTER_LOCK_DOOR2_DOOR4         = 0x00010001;    /* Door2,Door4 Interlock */
        public const int	INTER_LOCK_DOOR3_DOOR4         = 0x00000101;    /* Door3,Door4 Interlock */
        public const int	INTER_LOCK_DOOR1_DOOR2_DOOR3   = 0x01010100;    /* Door1,Door2,Door3 Interlock */
        public const int	INTER_LOCK_DOOR1_DOOR2_DOOR4   = 0x01010001;    /* Door1,Door2,Door4 Interlock */
        public const int	INTER_LOCK_DOOR1_DOOR3_DOOR4   = 0x01000101;    /* Door1,Door3,Door4 Interlock */
        public const int	INTER_LOCK_DOOR2_DOOR3_DOOR4   = 0x00010101;    /* Door2,Door3,Door4 Interlock */
        public const int	INTER_LOCK_ALL                 = 0x01010101;    /* Door1,Door2,Door3,Door4 Interlock */




        /*******************struct Year month day hour minute second **********************/
        [StructLayoutAttribute(LayoutKind.Sequential)]
        public struct NET_CARD_TIME
        {
	        public byte wYear;    //Note: Year only one byte,2013 ==>13  2014==>14
	        public byte byMonth;
	        public byte byDay;
	        public byte byHour;
	        public byte byMinute;
	        public byte bySecond;
        }

        /*******************struct Run State **********************/
         [StructLayoutAttribute(LayoutKind.Sequential)]
        public struct NET_CARD_DOORSTATUS
        {
	        public byte        m_iDoorCi;		 //Magnetic status
	        public byte        m_iOpenBtn;		 //Exit button status
	        public byte        m_iInput;		 //Input status
	        public ushort      m_iDisOnlineCardNums;//2Bytes Offline recording 2Bytes
	        public ushort      m_iRealCardNums;	 //2Bytes real recording 2Bytes
	        public ushort	   m_iCardNumTemp;		 //2Bytes Temporary number of cards
	        public ushort      m_iCardNumSort;		 //2Bytes Sort number of cards
	        public ushort      m_iCardRepeat;		 //2Bytes Repeat card number
	        public ushort      m_iCardNumSortBAK;   //2Bytes The number of Bakup card
        }

        /*******************struct Network parameters **********************/

        //[StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        [StructLayoutAttribute(LayoutKind.Sequential)]
        public struct NET_CARD_DEVICENETPARA
        {

            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 4, ArraySubType = UnmanagedType.I1)]
            public byte[] m_sNetIP;
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 6, ArraySubType = UnmanagedType.I1)]
            public byte[] m_sNetMAC;
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 4, ArraySubType = UnmanagedType.I1)]
            public byte[] m_sNetGate;
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 4, ArraySubType = UnmanagedType.I1)]
            public byte[] m_sNetMask;
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
            public byte[] m_nNetPort;
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 3, ArraySubType = UnmanagedType.I1)]
            public byte[] Reserve;
            public byte m_nDoorNum;
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 16, ArraySubType = UnmanagedType.I1)]
            public byte[] m_sVersion;
        }

        /**********struct Door password **********/
       [StructLayoutAttribute(LayoutKind.Sequential)]
        public struct NET_CARD_DOORPASSWORD
        {
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door01Password1;		//Door1  password 1 
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door01Password2;		//Door1  password 2    
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door01Password3;		//Door1  password 3    
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door01Password4;		//Door1  password 4   
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door02Password1;		//Door2  password 1    
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door02Password2;		//Door2  password 2   
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door02Password3;		//Door2  password 3     
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door02Password4;		//Door2  password 4   
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]	
	        public byte[]   Door03Password1;		//Door3  password 1   
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door03Password2;		//Door3  password 2 
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door03Password3;		//Door3  password 3   
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door03Password4;		//Door3  password 4  
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door04Password1;		//Door4  password 1   
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door04Password2;		//Door4  password 2  
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door04Password3;		//Door4  password 3  
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door04Password4;		//Door4  password 4 
        }

        /*******************struct Stress password*******************/
        [StructLayoutAttribute(LayoutKind.Sequential)]
        public struct NET_CARD_DOORDURESSWORD
        {
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door01Password;		//Doo1 Stress password
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door02Password;		//Doo2 Stress password
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door03Password;		//Doo3 Stress password 
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door04Password;		//Doo4 Stress password  
        }

        /*******************struct Open delay*******************/
         [StructLayoutAttribute(LayoutKind.Sequential)]
        public struct NET_CARD_OPEN_DELAY
        {
	        public byte   Door01DelayTime;		//Door1 Open delay  1-255S
	        public byte   Door02DelayTime;		//Door2 Open delay  1-255S
	        public byte   Door03DelayTime;		//Door3 Open delay  1-255S
	        public byte   Door04DelayTime;		//Door4 Open delay  1-255S 
        }

        /*******************struct Alarm Out Delay*******************/
         [StructLayoutAttribute(LayoutKind.Sequential)]
        public struct NET_CARD_ALARM_DELAY
        {
	        public ushort   Alarm01DelayTime;		//Alarm Out1 Delay 0-65535s 2B
	        public ushort   Alarm02DelayTime;		//Alarm Out2 Delay 0-65535s 2B
	        public ushort   Alarm03DelayTime;		//Alarm Out3 Delay 0-65535s 2B
	        public ushort   Alarm04DelayTime;		//Alarm Out4 Delay 0-65535s 2B
        }

        /*******************struct Magnetic,Stress Out Delay****************/
         [StructLayoutAttribute(LayoutKind.Sequential)]
        public struct NET_CARD_LIGHT_DELAY
        {
	        public short   LightOpenDelayTime;	//Magnetic  Delay 0-65535s 2B
	        public short   DruessDelayTime;		//Stress    Delay 0-65535s 2B
        }

        /*******************struct One Card Information 33Bytes *****************/
       [StructLayoutAttribute(LayoutKind.Sequential)]
        public struct NET_CARD_ONECARDINFO
        {
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 4, ArraySubType = UnmanagedType.I1)]
	        public byte[]   CardID;				//Card Series 
	        public byte     OpenType;				//pass type:card(0) or card+password(1)
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door01Password;		//Door1 password1 default: 0xff,0xff
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door02Password;		//Door2 password1 default: 0xff,0xff 
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door03Password;		//Door3 password1 default: 0xff,0xff   
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Door04Password;		//Door4 password1 default: 0xff,0xff  

	        public byte     EndYear;				//Validity Year		default:0xff,  
	        public byte     EndMonth;				//Validity Month	default:0xff,  
	        public byte     EndDay;					//Validity Day		default:0xff,  
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 3, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Reserve1;			//default: 0xff,0xff,0xff,保留字节
	        public byte     MultiCardType;			//default: 0x00, 0x01 3cards;0x02 4cards;0x03 5cards (5 cards open the door)
	                                                //01 10 00 01 door4 3cards,door2 4cards,door1 3cards 
	        public byte     RemoteOpenType;			//default: 0x00,Confirm door remote mode (high 4b),Different groups or same group to open the door (low 4b)										    
	        public byte     OpenDoorType;		    //default: 0x00,
											        //00 General group,01 Dual card,02first card,03By the first card limit
	        public byte     Reserve2;				//default: 0x00
	        public byte     CardStatus;				//default: 0x00, //00 Normal Cards,01 Loss card,02 Validity Card 03Delete card
	        public byte     OpenWhichDoor;			//default: 0xff,Four doors cannot to open; 0xf0 Four doors can open											
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 4, ArraySubType = UnmanagedType.I1)]
	        public byte[]   WeekAndHolidayCode;	//默认0x00 No holiday,
											        //week program no. and holiday num.  The first one byte is  door1 weekly programming and holiday programming Number...										
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 3, ArraySubType = UnmanagedType.I1)]
 	        public byte[]   Reserve3;			//default: 0xff
	        public byte     Reserve4;				//default: 0xff
        }


        /*******************struct Record information 17Bytes*****************/
       [StructLayoutAttribute(LayoutKind.Sequential)]
        public struct NET_CARD_RECORDINFO
        {
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 4, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Record_CardID;		//card series  
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 6, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Record_Time;		//Year month day hour minute second
	        public byte     Record_EventNum;	//recoder ID:0-255
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 5, ArraySubType = UnmanagedType.I1)]
	        public byte[]   Record_DevMAC;		//5 bytes of the MAC address	
	        public byte     Record_DoorNum;		//Door num (1-8)  Low 3bit ,Hight 5 bit Does not require 
        }

        /*******************struct Record information 17Bytes*****************/
       [StructLayoutAttribute(LayoutKind.Sequential)]
        public struct NET_CARD_IDCARDINFO
        {
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 31, ArraySubType = UnmanagedType.I1)]
	         public byte[]   IDCard_Name;		//Name
	         public byte     IDCard_NameLength;
	         public byte     IDCard_Sex;			//1 Male 2 Female 3 other ==1 男，2 女，3 其它
	         public byte     IDCard_National;		//National ==民族 0-55
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 9, ArraySubType = UnmanagedType.I1)]
	         public byte[]   IDCard_Birthday;		//birthday ==生日 19801020
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 71, ArraySubType = UnmanagedType.I1)]
	         public byte[]   IDCard_Address;     //address ==住址
	         public byte     IDCard_AddressLength; 
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 19, ArraySubType = UnmanagedType.I1)]
	         public byte[]   IDCard_IDNumber;     //IDNumber ==身份证号码
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 30, ArraySubType = UnmanagedType.I1)]
	         public byte[]   IDCard_Issuing;     //Issuing authority ==签发机关
	         public byte     IDCard_IssuingLength;
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 9, ArraySubType = UnmanagedType.I1)]
	         public byte[]   IDCard_Validity_StartDate;    //Validity_Start ==有效开始日期
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 9, ArraySubType = UnmanagedType.I1)]
	         public byte[]   IDCard_Validity_EndDate;      //Validity_Start ==有效结束日期

        }

   /*
        public enum SCENE_MODE
        {
            UNKOWN_SCENE_MODE = 0,            //未知场景模式
            HIGHWAY_SCENE_MODE = 1,            //高速场景模式
            SUBURBAN_SCENE_MODE = 2,            //郊区场景模式(保留)
            URBAN_SCENE_MODE = 3,            //市区场景模式
            TUNNEL_SCENE_MODE = 4             //隧道场景模式(保留)
        }
    */


    //callback function

    public delegate int _PRequstCallback(string Buff,int nLen);

    public delegate int _PProcessCallback(ref NET_CARD.NET_CARD_RECORDINFO pRecordInfo, IntPtr pReturnIP ,ref int nIPLength, IntPtr pReturnMAC);

   // public delegate void MSGCallBack(int lCommand, ref NET_DVR_ALARMER pAlarmer, IntPtr pAlarmInfo, uint dwBufLen, IntPtr pUser);


    public delegate int _PBroadcastSearchCallback(ref NET_CARD_DEVICENETPARA pNetParameter,  IntPtr pReturnIP,ref int ReturnIPLen,IntPtr pReturnDevMAC);

    public delegate int _PProcessCallbackEx(IntPtr pData, ref int DataLength, int nType, IntPtr pReturnIP,ref int ReturnIPLen,IntPtr pReturnDevMAC,IntPtr pIDBuffer,ref int ReturnIDBufferLen,int ReaderNo);


    //Real-time monitoring callback function
    [DllImport(@"DLNetSDK.dll")]
    public static extern  void NET_CARD_RealTimeDataCallback(_PProcessCallback pProcessCallback );

    [DllImport(@"DLNetSDK.dll")]
    public static extern  void NET_CARD_RealTimeDataCallbackEx(_PProcessCallbackEx pProcessCallbackEx );

    //Broadcast Search  callback function
    [DllImport(@"DLNetSDK.dll")]
    public static extern  void NET_CARD_BroadcastSerachDevice(_PBroadcastSearchCallback pProcessCallback );

     //DLL init
     [DllImport(@"DLNetSDK.dll")]
     public static extern int NET_CARD_InitEx(string szLocalIP,int nLocalPort,int WaitTimout);

     //DLL Exit
     [DllImport(@"DLNetSDK.dll")]
     public static extern void NET_CARD_Cleanup();

    /**********************Device Operation****************************************/
        
    //Get Run state
    [DllImport(@"DLNetSDK.dll")]        
    public static extern int NET_CARD_GetRunStatus(int DevType,string szRemoteIP, int nRemotePort,ref NET_CARD_DOORSTATUS pReturnStatus,ref byte pReturnDevMAC);
    //Get device's time
    [DllImport(@"DLNetSDK.dll")] 
    //public static extern int NET_CARD_DetectDeviceOnline(int DevType,string szRemoteIP, int nRemotePort,ref  byte[] pReturnDevMAC,ref NET_CARD_TIME pReturnDeviceTime);
    public static extern int NET_CARD_DetectDeviceOnline(int DevType, string szRemoteIP, int nRemotePort, ref byte pReturnDevMAC, IntPtr pReturnDeviceTime);
 
    //Remote Open
    [DllImport(@"DLNetSDK.dll")]
 
    public static extern  int NET_CARD_RemoteOpen(int DevType, string szRemoteIP, int nRemotePort, int nReaderNo,ref byte pReturnDevMAC );
    //Remote Close
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_RemoteClose(int DevType,string szRemoteIP, int nRemotePort,int nReaderNo,ref byte pReturnDevMAC);

    //Door always Open
    [DllImport(@"DLNetSDK.dll")]
    public static extern  int NET_CARD_AlwayOpen(int DevType, string szRemoteIP, int nRemotePort, int nReaderNo,ref byte pReturnDevMAC );
    //Door RecoveryState
    [DllImport(@"DLNetSDK.dll")]
    public static extern  int NET_CARD_RecoveryState(int DevType, string szRemoteIP, int nRemotePort, int nReaderNo,ref byte pReturnDevMAC );


    //Enable the door opened out alarm
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_EnableTimeOutAlarm(int DevType,string szRemoteIP, int nRemotePort,int nEnable,ref byte pReturnDevMAC);
    //Device init
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_DeviceInit(int DevType,string szRemoteIP, int nRemotePort,ref byte pReturnDevMAC);
    //Read Version
    [DllImport(@"DLNetSDK.dll")]
    public static extern int NET_CARD_ReadDeviceVersion(int DevType, string szRemoteIP, int nRemotePort, ref byte pReturnDevMAC,ref byte pReturnVersion );
    //Setting Device's Time
    [DllImport(@"DLNetSDK.dll")]
    public static extern int NET_CARD_SetDeviceTime(int DevType, string szRemoteIP, int nRemotePort, ref NET_CARD_TIME pDevTime, ref byte pReturnDevMAC);

    //Setting Server IP and Port
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_SetServerIPandPort(int DevType,string szRemoteIP, int nRemotePort,byte[] pServerIP,int nServerPort,ref byte pReturnDevMAC);
    //Clear Server IP and Port
    [DllImport(@"DLNetSDK.dll")]
    public static extern int NET_CARD_ClearServerIPandPort(int DevType, string szRemoteIP, int nRemotePort, ref byte  pReturnDevMAC);
    //Search device by device's IP
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_SearchDeviceByIP(int DevType,string szRemoteIP, int nRemotePort,ref NET_CARD_DEVICENETPARA pNetParameter,ref byte pReturnDevMAC);
    //Broadcast Search all devices
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_BroadCastSearchDevice(int DevType,string szRemoteIP,int nRemotePort=9998);
    //Setting lock delay
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_SetOpenDelayTime(int DevType,string szRemoteIP, int nRemotePort,ref NET_CARD_OPEN_DELAY pDelayTime,ref byte pReturnDevMAC);
    //Setting Alarm out delay 
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_SetAlarmDelayTime(int DevType,string szRemoteIP, int nRemotePort,ref NET_CARD_ALARM_DELAY pDelayTime,ref byte pReturnDevMAC);
    //Setting magnic and stress out delay
    [DllImport(@"DLNetSDK.dll")]
    public static extern int NET_CARD_SetDuressAlarmDelayTime(int DevType, string szRemoteIP, int nRemotePort, ref NET_CARD_LIGHT_DELAY pDelayTime, ref byte pDevMAC );
    //Setting lock type
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_SetLockType(int DevType,string szRemoteIP, int nRemotePort,byte nLockType,ref byte pDevMAC);
    //Setting network parameter
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_SetNetWorkParameter(int DevType,string szRemoteIP, int nRemotePort,byte[] pOldNetMAC,ref NET_CARD_DEVICENETPARA pNetParameter,ref byte pReturnDevMAC);
    //Start realtime monitor
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_EnableRealTimeMonitor(int DevType,string szRemoteIP, int nRemotePort,ref byte pReturnDevMAC);
    //Stop realtime monitor
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_DisbleRealTimeMonitor(int DevType,string szRemoteIP, int nRemotePort,ref byte pReturnDevMAC);
    //Setting interlock
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_SetInterLock(int DevType,string szRemoteIP, int nRemotePort,ref byte pInterLock,ref byte pReturnDevMAC);
    //Setting password password open door
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_SetDoorPassWord(int DevType,string szRemoteIP, int nRemotePort,ref NET_CARD_DOORPASSWORD pPassword,ref byte pReturnDevMAC);
    //Setting Stress password
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_SetDoorDuressPassWord(int DevType,string szRemoteIP, int nRemotePort,ref NET_CARD_DOORDURESSWORD pPassword,ref byte pReturnDevMAC);

    //Set Magnetic input level
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_SetMagneticInputHL(int DevType,string szRemoteIP, int nRemotePort,ref byte nMagType,ref byte pReturnDevMAC);
    //Read Magnetic input level
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_ReadMagneticInputHL(int DevType,string szRemoteIP, int nRemotePort,ref byte nMagType,ref byte pReturnDevMAC);

    //QR and 2RD Function //20150706
    //Setting Server TCP  IP and Port
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_Set_QR_ServerTCPIPAndPort(int DevType,string szRemoteIP, int nRemotePort,byte[] pServerIP,int nServerPort,ref byte pReturnDevMAC);

    //Setting Server UDP  IP and Port
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_Set_QR_ServerUDPIPAndPort(int DevType,string szRemoteIP, int nRemotePort,byte[] pServerIP,int nServerPort,ref byte pReturnDevMAC);

    //Setting Server Record UDP  IP and Port
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_Set_RecordUpLoad_UDPIPAndPort(int DevType,string szRemoteIP, int nRemotePort,byte[] pServerIP,int nServerPort,ref byte pReturnDevMAC);

    //Get ALLServerIPandPort
    //Server TCP  IP and Port 6B(IP 4B,Port 2B)
    //Server UDP  IP and Port 6B(IP 4B,Port 2B)
    //Server Record UDP  IP and Port 6B(IP 4B,Port 2B)
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_Get_ALLServerIPandPort(int DevType,string szRemoteIP, int nRemotePort,ref byte pReturnChar,ref int ReturnBufLen,ref byte pReturnDevMAC);


    //Voice Function
    //VoiceCode Voice code for Example:B1 欢迎光临
    //VoiceCodeLength  1
    //nbOpenDoor if open door or not  1:open 0 No Open
    //nReaderNo if nbOpenDoor=1 which door or somedoors
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_VoiceAndOpen(int DevType,string szRemoteIP, int nRemotePort,byte[] VoiceCode,int VoiceCodeLength,int nbOpenDoor,int nReaderNo,ref byte pReturnDevMAC);

    /**********************************Card Operation***************************/
    //Clear all cards 
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_ClearAllCardInfo(int DevType,string szRemoteIP, int nRemotePort,ref byte pReturnDevMAC);
    //Login a card
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_DownOneCardInfo(int DevType,string szRemoteIP, int nRemotePort,ref NET_CARD_ONECARDINFO pOneCardInfo,int OneCardInfoLength, ref byte pReturnDevMAC);
    //Read a card infomation
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_GetOneCardInfo(int DevType,string szRemoteIP, int nRemotePort,ref byte CardID,ref NET_CARD_ONECARDINFO pReturnOneCardInfo,ref byte pReturnDevMAC);
    //Get history record
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_GetHistroyRecord(int DevType,string szRemoteIP, int nRemotePort,int nRecordNumber,ref int ReturnNumber,ref NET_CARD_RECORDINFO pReturnRecordInfo,ref byte pReturnDevMAC);
    //Batch login cards  16cards,32cards(8cards)
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_BatchDownCardInfo(int DevType,string szRemoteIP, int nRemotePort,ref NET_CARD_ONECARDINFO pALLCardInfo,int ALLCardInfoLength, int nCardNo, int Totalcards,ref byte pReturnDevMAC);
    //Enable the controller to Get the card Series
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_EnableReadCardIDFromDevice(int DevType,string szRemoteIP, int nRemotePort,ref byte pReturnDevMAC);
    //Get the card Series from the controller card
    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_ReadCardIDFromDevice(int DevType,string szRemoteIP, int nRemotePort,ref byte pCardID,ref byte pReturnDevMAC);

    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_SendCommandToDevice(int DevTyp,string szRemoteIP, int nRemotePort,ref byte pSendData,int Sendlength,ref byte RevData,ref int nLength);

    [DllImport(@"DLNetSDK.dll")] 
    public static extern int NET_CARD_EventConfirm(int DevTyp,string szRemoteIP, int nRemotePort,ref byte pReturnDevMAC);


   }
}
