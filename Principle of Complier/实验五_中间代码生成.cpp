#include<bits/stdc++.h>
using namespace std;

class analy_PL0{
	public : 
		map<string,string>mp;
		vector<pair<string,int> > cnt;
		vector<pair<string,string> > cnt_word;
		vector<pair<string,string> > L;
		int right = 1;
		int cnt_T = 1;
		stack<pair<string,string> > numstack;
		stack<char> opstack;
		int result;
		int ptr;//指向当前式子处理到的位置 
		vector<char> vec;
		
	void init(){
		mp["begin"]="beginsym";
		mp["call"]="callsym";
		mp["const"]="constsym";
		mp["do"]="dosym";
		mp["end"]="endsym";
		mp["if"]="ifsym";
		mp["odd"]="oddsym";
		mp["procedure"]="proceduresym";
		mp["read"]="readsym";
		mp["then"]="thensym";
		mp["var"]="varsym";
		mp["while"]="whilesym";
		mp["write"]="writesym";
		mp["+"] = "plus";
		mp["-"] = "minus";
		mp["*"] = "times";
		mp["/"] = "slash";
		mp["="] = "eql";
		mp["#"] = "neq";
		mp["<"] = "lss";
		mp["<="] = "leq";
		mp[">"] = "gtr";
		mp[">="] = "geq";
		mp[":="] = "becomes";	
		mp["("] = "lparen";	
		mp[")"] = "rparen";	
		mp[","] = "comma";	
		mp[";"] = "semicolon";	
		mp["."] = "period";		
	} 
	void shoWord(){
		int n = cnt_word.size();
		cout<<"The Result is:"<<endl;
		for(int i=0;i<n;++i){
			cout<<"("<<cnt_word[i].first<<",";
			int L = 2 + cnt_word[i].first.size();
			L = 17-L;
			cout.setf(ios::right);
			cout.fill(' ');
			cout.width(L);
			string tep = cnt_word[i].second + ")";
			cout<<tep<<endl;
		}
	}
	
	bool separator_one(char s){
		string S = "";S.push_back(s);
		if(s == ' ' || mp.count(S))return true;
		return false;
	}
	bool separator_two(char s,char s2){
		string S = "";S.push_back(s);
		S.push_back(s2);
		if(mp.count(S))return true;
		return false;
	}
	
	void transWord(){
		L.clear();
		int n = cnt_word.size();
		for(int i=0;i<n;++i){
			L.push_back(cnt_word[i]);
		}
	}
	
	void find_symbols(vector<char> v){
		int L = v.size();
		char temp[100];
		for(int i=0;i<L;++i){
			if(v[i]>='A' && v[i]<='Z')v[i] = v[i]-'A'+'a';
		}
		int l = L, r = -1;
		string tep;
		int ff = 0;
		int ct = 0 ;
		for(int i=0;i<L;++i){
			ct = 0;
			if(v[i]>='a' && v[i]<='z'){
				if(ff==0)l = i;
				ff=1;
			}
			else if(ff == 1 && !(v[i]>='a' && v[i]<='z') && !(v[i]>='0' && v[i]<='9')){
				ff=0; 
				r = i-1;
				ct = 0; 
				for(int j=l;j<=r;++j){
					temp[ct++] = v[j];
				}	
				temp[ct++] = '\0';
				tep = temp;
				if(ct == 1)continue;		
				if(mp.count(tep)) continue;
				else {
					int fff = 0;
					int N = cnt.size();
					for(int j=0;j<N;++j){
						if(cnt[j].first == tep){
							cnt[j].second++;
							fff = 1;
						}
					}
					if(fff==0)cnt.push_back(make_pair(tep,1));
				}
			}
		}
	}
	
	
/*
	DFA
		state1: sym or ident
		state2: number
		state3: separator
		
		state4: unknown
		state5: sym
		state6: ident
		 
	transfer
		状态转换 
*/
	void transfer(int state,string t){
		if(t.size() == 0)return ;
		if(state == 1){
			if(mp.count(t)) cnt_word.push_back(make_pair(mp[t],t));
			else cnt_word.push_back(make_pair("ident",t));
		}
		else if(state == 2){
			cnt_word.push_back(make_pair("number",t));
		}
		else if(state == 3 || state == 5){
			cnt_word.push_back(make_pair(mp[t],t));
		}
		else if(state == 6){
			cnt_word.push_back(make_pair("ident",t));
		}
		else cnt_word.push_back(make_pair("unknown",t));
	}
	void DFA(vector<char> v)
	{
		cnt_word.clear();
		v.push_back(' '); 
		int L = v.size();
		for(int i=0;i<L;++i){
			if(v[i]>='A' && v[i]<='Z')v[i] = v[i]-'A'+'a';
		}
		int current = 0; // 当前状态
		int i = 0;
		string temp = "";
		while(i<L){
			char s = v[i];
			char s2 = ' ';
			if(i+1<L)s2 = v[i+1];
			if(isdigit(s)){
				if(current == 0)current = 2;
				else if(current == 1)current = 6;
				temp.push_back(s);
				i++;
			}else if(isalpha(s)){
				if(current == 0)current = 1;
				else if(current == 2)current = 4;
				temp.push_back(s);
				i++;
			}else if(i+1<L && separator_two(s,s2)){
				transfer(current,temp);
				temp.clear();
				temp.push_back(s);
				temp.push_back(s2);
				current = 3;
				transfer(current,temp);
				temp.clear();
				current = 0;
				i = i+2;		
			}else if(separator_one(s)){
				transfer(current,temp);
				temp.clear();
				
				if(s!=' '){
					temp.push_back(s);
					current = 3;
					transfer(current,temp);
					temp.clear();
				}
				current = 0;
				i++;
			}else {
				current = 4 ;
				temp.push_back(s);
				i++;
			}	
		}	
	}
	
	
	/*
	*****************************************
	根据两个栈利用产生式计算相应的值 
	*/
	void calculate(){
		char oper = opstack.top();
		opstack.pop();
		/*if(oper == '+'){
			int num1 = numstack.top();
			numstack.pop();
			int num2 = numstack.top();
			numstack.pop();
			numstack.push(num1+num2);
		}
		if(oper == '-'){
			int num1 = numstack.top();
			numstack.pop();
			int num2 = numstack.top();
			numstack.pop();
			numstack.push(num2-num1);
		}
		if(oper == '*'){
			int num1 = numstack.top();
			numstack.pop();
			int num2 = numstack.top();
			numstack.pop();
			numstack.push(num1*num2);
		}
		if(oper == '/'){
			int num1 = numstack.top();
			numstack.pop();
			int num2 = numstack.top();
			numstack.pop();
			numstack.push(num2/num1);
		}
		if(oper == '_'){
			int num = numstack.top();
			numstack.pop();
			numstack.push(-num);
		}*/
		if(oper == '_'){
			string temp = numstack.top().first;
			string s = numstack.top().second;
			numstack.pop();
			cout<<"("<<'-'<<")"<<endl;
		}
		else {
			string temp1 = numstack.top().first;
			string s1 = numstack.top().second;
			numstack.pop();
			string t1 = s1;
			
			if(temp1 == "number"){
				char num[10];
				sprintf(num,"%d",cnt_T++);
				string T= "T";
				for(int i=0;i<strlen(num);++i)T.push_back(num[i]);
				t1 = T;
				cout<<"("<<":=,"<<s1<<","<<T<<")"<<endl;	
			}
			string temp2 = numstack.top().first;
			string s2 = numstack.top().second;
			string t2 = s2;
			numstack.pop();
			if(temp2 == "number"){
				char num[10];
				sprintf(num,"%d",cnt_T++);
				string T= "T";
				for(int i=0;i<strlen(num);++i)T.push_back(num[i]);
				t2 = T;
				cout<<"("<<":=,"<<s2<<","<<T<<")"<<endl;
			}
			char num[10];
			sprintf(num,"%d",cnt_T++);
			string T= "T";
			for(int i=0;i<strlen(num);++i)T.push_back(num[i]);
			cout<<"("<<oper<<","<<t2<<","<<t1<<","<<T<<")"<<endl;
			numstack.push(make_pair("ident",T));
		}
	} 
	
	
	/*
	******检查表达式 
	*/
	int check_S(int pos){ 
		if(right != 1) return pos;
		if(L[pos].first == "plus" || L[pos].first == "minus"){
			string tempplus = L[pos].first;
			ptr++;
			pos = check_item(pos+1);
			
			if(tempplus == "minus"){
				opstack.push('_');
				calculate();
				//cout<<"_";
			}
		}
		else pos = check_item(pos);
		while(pos<L.size() && (L[pos].first == "plus" || L[pos].first == "minus")){
			string tempplus = L[pos].first;
			ptr++;
			pos = check_item(pos+1);
			if(right != 1)return pos;
			if(tempplus == "plus"){
				opstack.push('+');
				calculate();
				//cout<<"+";
			}
			else if(tempplus == "minus"){
				opstack.push('-');
				calculate();
				//cout<<"-";
			}
		}
		return pos;
	}

	/*
	******检查项 
	*/
	int check_item(int pos){  
		if(right != 1) return pos;
		pos = check_fac(pos);
		while(pos<L.size() && (L[pos].first == "times" || L[pos].first == "slash")){
			string tempmult = L[pos].first;
			ptr++;
			pos = check_fac(pos+1);
			if(right != 1)return pos;
			if(tempmult == "times"){
				opstack.push('*');
				calculate();
				//cout<<"*";
			}
			else if(tempmult == "slash"){
				opstack.push('/');
				calculate();
				//cout<<"/";
			}
		}

		return pos;
	}

	
	
	
	/*
	******检查因子 
	*/
	int check_fac(int pos){ 
		if(right != 1) return pos;
		if(L[pos].first == "ident") {
			
			numstack.push(L[pos]);
			//ptr+=vec.size();
			return pos+1;
		}
		if(L[pos].first == "number"){
			
			//cout<<"2222222222222"<<' '<<//ptr<<endl;
			numstack.push(L[pos]);
			ptr += vec.size();
			//cout<<6666666666<<' '<<temp<<endl;
			return pos+1;
		} 
		else if(L[pos].first == "lparen"){
			ptr++;
			pos = check_S(pos+1);
			if(pos>=L.size() || L[pos].first!="rparen"){
				right = min(right, 0);
				return pos;
			}
			else {
				ptr++;
				return pos+1;
			}
		}
		else {
			right = -1;
			cout<<"This pos : "<<pos<< " is wrong!"<<endl;
			return 0;
		}
	}
	
	
	void debug(){
		for(int i=0;i<L.size();i++){
			cout<<L[i].first<<endl;
		}
	}
	
	
	int judge(){
		cnt_T = 1;
		right = 1;
		debug(); 
		int end = check_S(0);
		if(end < L.size() || right == 0){
			cout<<right<<endl;
			if(right != -1) cout<<"This pos : "<<end<< " is wrong!"<<endl;	
			right = 0;
		}
		//if(right == 1) result = numstack.top();
		return right;
	}
	
	
	
	void pre_init(vector<char> v){
		vec.clear();
		result = 0;
		ptr = 0;
		for(int i=0;i<v.size();i++){
			vec.push_back(v[i]);
			//cout<<vec[i];
		}
	}
	
	
	
}CI;

void testByChar(analy_PL0 CI)  
{  
	fstream testByCharFile;  
    char c; 
	char s[1000]; 
	vector <char>v;
    freopen("ex5.in","r",stdin);
    while(gets(s))  
    {  
    	//cout<<s<<endl;
    	v.clear();
        int L = strlen(s);	
		for(int i=0;i<L;++i){
			v.push_back(s[i]);
		}
		CI.pre_init(v);
        CI.DFA(v);
        //v.clear(); 
        //CI.shoWord();
	    CI.transWord();
	    if(CI.judge() == 1){
	    	cout << "语法正确" <<endl;
	    	//cout << "结果为: "<<CI.result<<endl;
		}
		else {
			cout << "语法错误" <<endl;
		}
    }   
    
}  

char s[100];

int main(){
	CI.init();
	testByChar(CI);	
	return 0;
}
/*
2+4-(3-2)/1*5
2+4+(3-2)/1*5
2+4+(3-2)*1*5
2+4+(2-(-2))/2*5
11+2*(13-11)+2
*/
