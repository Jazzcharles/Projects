/**
 * 
 */
//package com.dnion.socket;

import java.awt.GridLayout;
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
import java.net.Socket;
import java.util.Scanner;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class JabberClient extends JFrame  implements ActionListener {
	/**
	 * 
	 */
	private static final long serialVersionUID = 2038378010602655211L;
	Socket socket = null;
	BufferedReader br = null;
	PrintWriter pw = null;
	Scanner in=new Scanner(System.in);
	JTextArea jta=null;
	JTextField jtf=null;
	JButton jb=null;
	JPanel jp1=null;
	JScrollPane jsp=null;
	public JabberClient(String IP) {
		if(IP.equals(null)) IP="127.0.0.1";
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
		this.setSize(400,300);
		
		this.setTitle("Chatroom-Client");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		System.out.println("SUCCESSFULLY ACTIVATED 1");
		this.setVisible(true);
		try {
			//�ͻ���socketָ���������ĵ�ַ�Ͷ˿ں�
			//socket = new Socket("127.0.0.1", JabberServer.PORT);
			socket = new Socket(IP,JabberServer.PORT);
			System.out.println("Socket=" + socket);
			br = new BufferedReader(new InputStreamReader(
					socket.getInputStream()));
			pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(
					socket.getOutputStream())));
			//System.out.println("SUCCESSFULLY ACTIVATED 2");
			//while(true){
				//System.out.println("SUCCESSFULLY ACTIVATED 555");
				String str=br.readLine();
				jta.append("Server :" + str + "\n");
				//if(str.equals("END")) break;
			//}
		} catch (Exception e) {
            if (socket != null)
            {
                try
                {
                    socket.close();
                    br.close();
                    pw.close();
                    socket = null;
                    System.out.println("SUCCESSFULLY SHUTDOWN_CLIENT");
                }
                catch (Exception ex)
                {
                    ex.printStackTrace();
                }
                 
                System.out.println("Զ�������쳣���ر�����");
                return;
            }
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.out.println(socket.isConnected());
            

		}
		this.pack();
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		validate();
	}
//	public static void main(String[] args){
//		JabberClient jc=new JabberClient("127.0.0.1");
//	}
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO �Զ���ɵķ������
		if(e.getSource()==jb){
			try{
				System.out.println("why");
				String str=jtf.getText();
				jta.append("Client :"+ str +"\n");
				jtf.setText("");
				pw.println(str);
				pw.flush();				
			}catch(Exception ee){
				ee.printStackTrace();
			}

		}
		
	}

}

