import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingConstants;

//import com.mysql.jdbc.Connection;

public class login extends JFrame implements ActionListener{
	/**
	 * 
	 */
	private static final long serialVersionUID = -7263187670874952445L;
	//JTextArea jta=null;
	JTextField jtf=null;
	JTextField jtf2=null;
	JTextField jtf3=null;
	JLabel jl1=null;
	JLabel jl2=null;
	JLabel jl3=null;
	
	JButton jb=null;
	JPanel jp=null;
	//JFrame f=null;
	static String str[];
	static int len;
	static int flagc,flags;
	//static JabberClient jc;
	public login(){
		jtf=new JTextField();
		jtf2=new JTextField();
		jtf3=new JTextField();
		jl1 = new JLabel("Username:", SwingConstants.CENTER);// ���־���
		jl2 = new JLabel("Password:", SwingConstants.CENTER);// ���־���
		jl3 = new JLabel("IP:", SwingConstants.CENTER);// ���־���
		jb=new JButton("Login");
		jp=new JPanel();
		jp.setLayout(new GridLayout(3,1));
		jp.add(jl1);
		jp.add(jtf);
		jp.add(jl2);
		jp.add(jtf2);
		jp.add(jl3);
		jp.add(jtf3);
		
		
	
		this.add(jp);
		this.add(jb,"South");
		this.setSize(250,150);
		this.setVisible(true);
		this.setTitle("Login");
		//f=new JFrame("Username");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		jb.addActionListener(this);
	}
	public void ConnSQL(){
		String driver="com.mysql.jdbc.Driver";
		String url = "jdbc:mysql://127.0.0.1:3306/network";
		String user = "root";
		String password = "charles54363608";
		try{
			Class.forName(driver);
			Connection conn = DriverManager.getConnection(url, user, password);
			if(!conn.isClosed()){
				 System.out.println("Succeeded connecting to the Database!");
			}
			Statement statement = conn.createStatement();
			String sql = "select * from info";
			ResultSet rs = statement.executeQuery(sql);
			
			while(rs.next()){
				System.out.println(rs.getString("username") + ' ' + rs.getString("passwd") + ' ' + rs.getString("id"));
				if((rs.getString("username").equals(jtf.getText())) 
				&& (rs.getString("passwd").equals(jtf2.getText()))
				&& (rs.getString("id").equals("1"))	){
					System.out.println(123);
					rs.close();
					conn.close();
					this.dispose();
					//flagc=1;
					JabberClient jc=new JabberClient(jtf3.getText());
				}
				else if((rs.getString("username").equals(jtf.getText())) 
				&& (rs.getString("passwd").equals(jtf2.getText()))
				&& (rs.getString("id").equals("2"))){
					System.out.println(456);
					rs.close();
					conn.close();
					this.dispose();
					//flags=1;
					this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
					JabberServer js=new JabberServer();
					//js.setVisible(true);
					//js.cal();
					//js.setVisible(true);
					System.out.println(789);
				}
			}
		}catch(Exception e){
			e.printStackTrace();
		}
	}
/*	
	public static void read(String filename){
		File file = new File(filename);
		BufferedReader br=null;
		int i=0;
		if(file.isFile() && file.exists())
			System.out.println("Exists");
		else
			System.out.println("NOT");
		try{
			br=new BufferedReader(new FileReader(file));
			while((str[i]=br.readLine())!=null){
				i++;
			}
			len=i;
		}catch(Exception e){}
		finally{
			if(br!=null){
				try{
					br.close();
				}catch(IOException e1){
				}
			}
		}
	}
	
	public void check(){
		//jc=new JabberClient();
		String user=jtf.getText();
		String pasw=jtf2.getText();
		String res = user + pasw;
		System.out.println(res);
		try{
			int flag=0;
			for (int i=0; i<len;i++){
				System.out.println(str[i]);
				if(res.equals(str[i])) {
					flag = 1;
					System.out.println("FOUND");
					break;
				}
			}
			if(flag==1){
				System.out.println("YES");
				this.dispose();
				JabberClient jc= new JabberClient();
			}
			else{
				System.out.println("NOT FOUND");
			}			
		}catch(Exception e){
			e.printStackTrace();
		}
	}
*/	
	public static void main(String[] args) {
		// TODO �Զ���ɵķ������	
//		str=new String[100];
//		read("D:/Charles/java code/client.txt");
		System.out.println("44444444444444444444444444444444");
		login lg=new login();
//		if(flags==1) {
//			JabberServer js=new JabberServer();	
//		}
//		if(flagc==1){
//			JabberClient jc=new JabberClient();
//		}
	}
	@Override
	public void actionPerformed(ActionEvent arg0) {
		// TODO �Զ���ɵķ������
		if(arg0.getSource()==jb){
			try{
				ConnSQL();				
			}catch(Exception e){
				e.printStackTrace();
			}
			//check();
			//JabberServer jc=new JabberServer();
		}
	}

}
