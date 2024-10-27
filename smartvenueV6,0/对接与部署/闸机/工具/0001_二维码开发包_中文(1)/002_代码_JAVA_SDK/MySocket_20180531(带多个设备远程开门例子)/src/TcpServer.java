import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;


public class TcpServer {

    public static void main(String[] args)
    {
    	final Object object = new Object();
    	final Object objectClearAllCard = new Object();
    	    	
    	final Map<String, Object> map = new HashMap<String, Object>();
    	
    	
        ServerSocket server;
        try
        {
        	//建立一个控制线程，演示如何控制多个设备可以远程开门；通过Map建立MAC地址与TCP控制输出的DataOutputStream变量关系，
        	//在这个线程中，列举了二个设备的MAC，通过MAC地址找到设备与软件建立的TCP控制输出控制变量output = new DataOutputStream(client.getOutputStream())变量，
        	//通过output就可以控制对应的设备进入相应操作，如远程开门
        	
        	//new Thread(new OpenAllDeviceDoor(map)).start();   
        	
        	//建立一个TCP SERVER，端口为18887
            server = new ServerSocket(Integer.parseInt("18887"));
            while (true)
            {
                Socket client = server.accept();//等待设备连接进来
                //如有设备连接进来，则开一个线程处理与这个设备的相关操作
                new Thread(new SocketServer(client,object,objectClearAllCard,map)).start();
                
                //下载卡线程演示
               // new Thread(new DownLoadSortCards(client,object,objectClearAllCard)).start();
            }
        } catch (IOException e)
        {
            e.printStackTrace();
        }
        
    }

}
