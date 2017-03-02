
//package com.dnion.socket;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class JabberServer extends JFrame  implements ActionListener{
	/**
	 * 
	 */
	private static final long serialVersionUID = -1934546549199947949L;
	public static int PORT = 8080;
	Socket socket=null;
	BufferedReader br = null;
	PrintWriter pw = null;
	JTextArea jta=null;
	JTextField jtf=null;
	JButton jb=null;
	JPanel jp1=null;
	JScrollPane jsp=null;
//	static String []str;
//	static int len ;
	public JabberServer()  {
		
		jta=new JTextArea();
		jsp=new JScrollPane(jta);
		jtf=new JTextField(20);
		jb=new JButton("Send");
		jp1=new JPanel();
		
		
		jb.addActionListener(this);
		jp1.add(jtf);
		jp1.add(jb);
		this.add(jsp,"Center");
		this.add(jp1,"South");
		this.setSize(700,500);
		
		//this.setVisible(false);
		this.setTitle("Chatroom-Server");
		//this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);			
			try {
					//�趨����˵Ķ˿ں�
					ServerSocket s = new ServerSocket(PORT);
					System.out.println("ServerSocket Start:"+s);
					//�ȴ�����,�˷�����һֱ����,ֱ����������������
					socket = s.accept();
					System.out.println("Connection accept socket:"+socket);
					//���ڽ��տͻ��˷���������
					br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
					//���ڷ��ͷ�����Ϣ,���Բ���Ҫװ����ô��io��ʹ�û�����ʱ�������Ҫע�����.flush()����
					pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())),true);
					//while(true){
						String str=br.readLine();
						jta.append("Client :" + str + "\n");
						//if(str.equals("EMD")) break;
					//}
					
				} catch (Exception e) {
	                 
	                if (socket != null)
	                {
	                    try
	                    {
	                    	br.close();
	                    	pw.close();
	                        socket.close();
	                        socket = null;
	                        System.out.println("SUCCESSFULLY SHUTDOWN_SERVER");
	                    }
	                    catch (Exception ex)
	                    {
	                        ex.printStackTrace();
	                    }
	                     
	                    System.out.println("Զ�������쳣���ر�����");
	                    return;
	                }
					// TODO Auto-generated catch block
					System.out.println("ERROR");
					e.printStackTrace();
					//System.out.println(socket.isConnected());

				}
			this.pack();
			this.setVisible(true);
			this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			validate();
	}

		

	//}
		
		
		
		
//		public static void main(String[] args) {
//	//		Scanner in=new Scanner(System.in);
//	//		int a=in.nextInt();
//	//		str=new String[100];
//	//		len = 0;
//	//		read("D:/Charles/java code/client.txt");
//	//		for(int i=0;i<len;i++){
//	//			System.out.println(str[i]);
//	//		}	
//	//		System.out.println(len);
//			JabberServer js=new JabberServer();
//		}
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO �Զ���ɵķ������
		if(e.getSource()==jb){
			try{
				System.out.println("whynothing?");
				String str=jtf.getText();
				jta.append("Server :"+ str +"\n");
				pw.println(str);
				pw.flush();
				jtf.setText("");				
			}catch(Exception ee){
				ee.printStackTrace();
			}
		
		}
	}
}
/*	
 * 	//	
	//	public static void read(String filename){
	//		File file = new File(filename);
	//		BufferedReader br=null;
	//		int i=0;
	//		if(file.isFile() && file.exists())
	//			System.out.println("Exists");
	//		else
	//			System.out.println("NOT");
	//		try{
	//			br=new BufferedReader(new FileReader(file));
	//			while((str[i]=br.readLine())!=null){
	//				i++;
	//			}
	//			len=i;
	//		}catch(Exception e){}
	//		finally{
	//			if(br!=null){
	//				try{
	//					br.close();
	//				}catch(IOException e1){
	//				}
	//			}
	//		}
	//	}
	//	
	//		finally{
	//			System.out.println("Close.....");
	//			try {
	//				br.close();
	//				pw.close();
	//				socket.close();
	//				s.close();
	//			} catch (Exception e2) {
	//				e2.printStackTrace();
	//			}
	//		}
 * */
