
public class Course {
	String kh;
	String km;
	String jsh;
	int xf;
	
	String js;
	String sksj;
	String skdd;
	int edrs;
	int xkrs;
	int index;
	
	boolean vis;//是否被选过
	
	
	Course(){
		
	}
	Course(String KH){
		kh=KH;
	}
	public String get_km(){
		return km;
	}
	
	public String get_kh(){
		return kh;
	}
	
	public String get_js(){
		return js;
	}
	
	public String get_sksj(){
		return sksj;
	}
	
	public String get_skdd(){
		return skdd;
	}
	
	public int get_kf(){
		return xf;
	}
	
	public int get_edrs(){
		return edrs;
	}
	
	public int get_xkrs(){
		return xkrs;
	}
}
