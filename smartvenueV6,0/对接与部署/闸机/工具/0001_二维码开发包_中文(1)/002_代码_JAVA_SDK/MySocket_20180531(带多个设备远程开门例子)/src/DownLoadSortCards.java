import java.lang.*;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

import java.net.Socket;
import java.net.SocketException;
import java.net.SocketTimeoutException; 

class DownLoadSortCards implements Runnable
{
    Socket client;
    int secieveLen=0;
    Object object;
    Object objectClearAllCard;
    int nPos =0;
    
    public DownLoadSortCards(Socket client,Object object,Object objectClearAllCard)
    {
        this.client = client;
        this.object = object;
        this.objectClearAllCard = objectClearAllCard;
    }  
	//1批量下载前清除设备所有卡号
    //2下载前将所有卡号从小到大排序
    //3 一张卡33个字节，16张或32张卡到打包组合在一起
    //下载格式 (数据部分): 4203ff+ 下载卡序号2字节，高字节在前（如0000 0010 ）+ 一次下载多少张卡（16张或32张，建议网络不好一次下载16张卡）+16张卡的数据（一张卡33字节*16）
    //说明：
    //1)下载卡序号，是告诉设备 这个包下载的卡序号是第几张卡，如果下载中途失败，上位机没有收到下载正确的返回指令，不需要从头开始下载，直接将当前下载数据，重新下载一次，
        //设备存储卡时，是根据卡序号来安排存储空间的，这样即使当前下载包重新下载，也中会打乱设备的存储顺序。
    //2)批量下载一次必须是16张卡或32张卡，如果批量下载最后一个包卡数量不受此限制，
 /* 连续二个下载包的数据示范：
02 02 1E FF FF FF FF FF FF 11 42 03 FF 00 00 10 
15 20 79 E9 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 EA 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 EB 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 EC 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 ED 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 EE 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 EF 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 F0 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 F1 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 F2 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 F3 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 F4 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 F5 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 F6 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 F7 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 F8 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
FF 03 

02 02 1E FF FF FF FF FF FF 11 42 03 FF 00 10 10 
15 20 79 F9 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 FA 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 FB 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 FC 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 FD 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 FE 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 79 FF 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 7A 00 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 7A 01 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 7A 02 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 7A 03 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 7A 04 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 7A 05 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 7A 06 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 7A 07 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
15 20 7A 08 00 12 34 12 34 12 34 12 34 FF FF FF FF FF FF FF FF 00 FF 00 F0 00 00 00 00 FF FF FF FF 
FF 03 
 */
	public void run()
    {    	  
 		int nMaxCardNum=32;//10000;
  		byte[] AllCard16 =new byte[50+33*16];  		  		
  		DataOutputStream output;  		
        try
        {
            output = new DataOutputStream(client.getOutputStream());	            
            //清除设备内的卡片            
  			synchronized(objectClearAllCard){
  				try
  				{
  				   SocketServer.NET_CARD_ClearAllCard(output);//发送到设备
  				   objectClearAllCard.wait();	  				    
  				}catch(InterruptedException e){
  					e.printStackTrace();
  				}
  			}
	  		String cardIdStartStr  	=  new String("077DA36D"); 	  		
	  	    int StartCardint = SocketServer.StrToInt(cardIdStartStr);
	  		for(int ii=0;ii<nMaxCardNum/16;ii++)
	  		{  			
	  			AllCard16[0] = (byte)0x42;
	  			AllCard16[1] = (byte)0x03;
	  			AllCard16[2] = (byte)0xFF;
	  			
	  			short CardNo =0;  			
	  			CardNo = (short) (ii*16);  			
	  			AllCard16[3] = (byte) (CardNo>>8);
	  			AllCard16[4] = (byte) (CardNo&0x00ff);
	  			
	  			AllCard16[5] = 16;  //16或32
	  			nPos = 6;
	  	  	    
	  			//把16张卡放到一个AllCard16里面
	  			for(int kk=0;kk<16;kk++)
	  			{
	  				//单张卡的赋值	
	  				for(int jj=0;jj<33;jj++)
	  				{
	  					AllCard16[kk*33+nPos+jj] =(byte)0xff;
	  				} 				
	  				AllCard16[kk*33+nPos+0] = (byte) (StartCardint>>24);
	  				AllCard16[kk*33+nPos+1] = (byte) (StartCardint>>16);
	  				AllCard16[kk*33+nPos+2] = (byte) (StartCardint>>8);
	  				AllCard16[kk*33+nPos+3] = (byte) (StartCardint&0x00ff);
	  				AllCard16[kk*33+nPos+4] = (byte) 0x00;
					AllCard16[kk*33+nPos+16] = (byte) 0x00;
					AllCard16[kk*33+nPos+17] = (byte) 0x00;
					AllCard16[kk*33+nPos+18] = (byte) 0x00;
					AllCard16[kk*33+nPos+19] = (byte) 0x00;					  				
	  				AllCard16[kk*33+nPos+20] = (byte) 0x00;
	  				AllCard16[kk*33+nPos+21] = (byte) 0x00;
	  				AllCard16[kk*33+nPos+22] = (byte) 0x00;
	  				AllCard16[kk*33+nPos+23] = (byte) 0x00;
	  				AllCard16[kk*33+nPos+24] = (byte) 0x00;
	  				AllCard16[kk*33+nPos+25] = (byte) 0x00;
	  				AllCard16[kk*33+nPos+26] = (byte) 0x00;
	  				AllCard16[kk*33+nPos+27] = (byte) 0x00;
	  				AllCard16[kk*33+nPos+28] = (byte) 0x00;
				  				
	  				StartCardint++;
	  			}  	
	  			synchronized(object){
	  				try
	  				{
	  				    SocketServer.SendCommandtoDevice(output,AllCard16,33*16+6);//发送到设备
	  				    object.wait();	  				    
	  				}catch(InterruptedException e){
	  					e.printStackTrace();
	  				}
	  			}
	  				
	  		}
	  		
	  		int nRestcards=nMaxCardNum%16;
  			if(nRestcards>0)
  			{	  		
				AllCard16[0] = (byte)0x42;
				AllCard16[1] = (byte)0x03;
				AllCard16[2] = (byte)0xFF;
				
	  			short CardNo =0;  			
	  			CardNo = (short) ((short) (nMaxCardNum/16)*16);  			
	  			AllCard16[3] = (byte) (CardNo>>8);
	  			AllCard16[4] = (byte) (CardNo&0x00ff);
	  			
	  			AllCard16[5] = (byte)nRestcards;  //16或32
	  			nPos = 6;
	
				//把剩下的不足16张卡放到一起下载	
				for(int kk=0;kk<nRestcards;kk++)
				{			   
					//单张卡的赋值	
					for(int jj=0;jj<33;jj++)
					{
						AllCard16[kk*33+nPos+jj] =(byte)0xff;
					} 				
					AllCard16[kk*33+nPos+0] = (byte) (StartCardint>>24);
					AllCard16[kk*33+nPos+1] = (byte) (StartCardint>>16);
					AllCard16[kk*33+nPos+2] = (byte) (StartCardint>>8);
					AllCard16[kk*33+nPos+3] = (byte) (StartCardint&0x00ff);
					AllCard16[kk*33+nPos+4] = (byte) 0x00;
					AllCard16[kk*33+nPos+16] = (byte) 0x00;
					AllCard16[kk*33+nPos+17] = (byte) 0x00;
					AllCard16[kk*33+nPos+18] = (byte) 0x00;
					AllCard16[kk*33+nPos+19] = (byte) 0x00;					
					AllCard16[kk*33+nPos+20] = (byte) 0x00;
					AllCard16[kk*33+nPos+21] = (byte) 0x00;
					AllCard16[kk*33+nPos+22] = (byte) 0x00;
					AllCard16[kk*33+nPos+23] = (byte) 0x00;
					AllCard16[kk*33+nPos+24] = (byte) 0x00;
					AllCard16[kk*33+nPos+25] = (byte) 0x00;
					AllCard16[kk*33+nPos+26] = (byte) 0x00;
					AllCard16[kk*33+nPos+27] = (byte) 0x00;
					AllCard16[kk*33+nPos+28] = (byte) 0x00;		
					StartCardint++;				  				
		
				}		
	  			synchronized(object){
	  				try
	  				{
	  					SocketServer.SendCommandtoDevice(output,AllCard16,33*nRestcards+6);//发送到设备  	
	  				    object.wait();	  				    
	  				}catch(InterruptedException e){
	  					e.printStackTrace();
	  				}	  				
	  			}	
  			}//if(nRestcards>0)
			
	    }
	    catch (IOException e)
	    {
	        e.printStackTrace();
	    }	
    }

}

