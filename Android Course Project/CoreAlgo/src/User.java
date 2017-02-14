

public class User {
	final String zero="00000000";
	final int MAX=15000;
	String xm;
	int xh;
	Course course[][];
	
	User(){
		
	}
	
	User(int id){
		xh=id;
		course=new Course[100][200];
		for(int i=0;i<13;i++){
			//course[i]=new Course[20];
			for(int j=0;j<5;j++){
				course[i][j]=new Course();
				course[i][j].vis=false;
				course[i][j].kh=zero;
			}
		}
	}
	
	//是否有该课程
	public boolean existcourse(String kh){
		for(int i = 0; i < MAX ; i++){
		//	if() return true;
		}
		return false;
	}
		
		
		
	public boolean selectcourse(String kh){
		//如果输入的课号有误，数据库中不存在此课
//		if() return false;
//		如果选课人数未满，但时间冲突，day周几，st起始上课时间，ed结束上课时间
		int st=0,ed=0,day=0;
//		for(int i = 0 ; i < MAX ; i++ ){
			//如果找到该课号,找出上课时间
//			if(){
//				st=...;
//				ed=...;
//				day=...;		
//				for(int time = st; time <= ed; time++){
//					 if(course[time][day].vis==true){
//						 return false;
//					 }
//				 }
//			}
//		}		
		//标记该时间选该课程
//		for(int time = st; time <= ed; time++){
//			
//		}		
		return true;
	}
	
	
	//删除所选课程
	public boolean removecourse(String kh){
		return true;
	}
	
	public void showcourse(){
		for(int i=0;i<13;i++){
			for(int j=0;j<5;j++){
				System.out.printf("%s ",course[i][j].kh);
			}
			System.out.println();
		}
	}
	
}
