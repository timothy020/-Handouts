import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Map;


    
public class OpenAllDeviceDoor implements Runnable 
{
    private static final DataOutputStream NULL = null;

	Map<String, Object> map;
    //Device1 MAC: 008139212275,Device 2 MAC:008139961115
    
    String NeedOpenDoorDeviceMAC;
    DataOutputStream outputTest;
    
    public OpenAllDeviceDoor(Map<String, Object> map)
    {
        this.map = map;
    }   
    
    
    public static String byte2HexStr(byte[] b) 
    {  
        String hs = "";  
        String stmp = "";  	
        for (int n = 0; n < b.length; n++) 
        {  
            stmp = (Integer.toHexString(b[n] & 0XFF));  
            if (stmp.length() == 1)  
                hs = hs + "0" + stmp;  
            else  
                hs = hs + stmp;   
        }         
        return hs.toUpperCase();  
    }     
    public static void SendCommandtoDevice(DataOutputStream outtoclient,byte command[],int len) throws IOException
    {
 	   // 02 00 0B FF FF FF FF FF FF 11 45 08 00 FF 03
    	int senddatalen = 0;
    	byte[]  SendBuffer = new byte[1500];
    	
    	SendBuffer[0] = 0x02;
    	
    	SendBuffer[0] =0x02;
    	
    	SendBuffer[3] = (byte)0xFF;
    	SendBuffer[4] = (byte)0xFF;
    	SendBuffer[5] = (byte)0xFF;
    	SendBuffer[6] = (byte)0xFF;
    	SendBuffer[7] = (byte)0xFF;
    	SendBuffer[8] = (byte)0xFF;    	
    	SendBuffer[9] = (byte)0x11;
    	
    	System.arraycopy(command,0,SendBuffer,10,len);
    	
    	senddatalen = len + 8;    	
    	SendBuffer [1] = (byte) ((senddatalen >>8) & 0x00ff);
	    SendBuffer [2] = (byte) (senddatalen & 0x00ff);
	    
	    senddatalen = senddatalen + 4;
	    SendBuffer [senddatalen-2] = (byte)0xFF;
	    SendBuffer [senddatalen-1] = (byte)0x03;
	    
	    outtoclient.write(SendBuffer, 0, senddatalen);
	    
	    byte[] SendDataTmp = new byte[senddatalen];	    
	    System.arraycopy(SendBuffer,0,SendDataTmp,0,senddatalen);
	    String SendDataStr = byte2HexStr(SendDataTmp);
	       
	    Date nowTime=new Date(); 
	    SimpleDateFormat time=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");     
	    System.out.println("开门演示线程 "+time.format(nowTime)+" Send command:"+SendDataStr+"\r\n");
	    	
    }     
        
	@Override
	public void run() {
		// TODO Auto-generated method stub

		outputTest =NULL;
		byte[] SendCommand =new byte[50];
		NeedOpenDoorDeviceMAC="008139212275";
		int nCounter=0;
        while (true)
        {
        	try
        	{        
        		if((nCounter%2)==0)
        		{
        			NeedOpenDoorDeviceMAC="008139212275";        			
        		}
        		else
        		{
        			NeedOpenDoorDeviceMAC="008139961115";         			
        		}
        		outputTest =(DataOutputStream) map.get(NeedOpenDoorDeviceMAC);
        		if(outputTest!=null)
        		{
        			SendCommand[0] = (byte)0x50;
					SendCommand[1] = (byte)0x00;
					SendCommand[2] = (byte)0xFF;
					SendCommand[3] = (byte)0x01;
					SendCommandtoDevice(outputTest,SendCommand,4);
        		} 
        		nCounter++;
        		Thread.sleep(5000);
 
            } catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} 
        }

		
	}

}
