#include<bits/stdc++.h>
using namespace std;

class analy_PL0{
	public : 
		map<string,string>mp;
		vector<pair<string,int> > cnt;
		vector<pair<string,string> > cnt_word;
		vector<string> L;
		int right = 1;
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
		mp["//"] = "slash";
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
			L.push_back(cnt_word[i].first);
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
	
	int check_S(int pos){
		if(right != 1)return pos;
		if(L[pos] == "plus" || L[pos] == "minus"){
			pos = check_item(pos+1);
		}else pos = check_item(pos);
		while(pos<L.size() && (L[pos] == "plus" || L[pos] == "minus")){
			pos = check_item(pos+1);
		}
		
		return pos;
	}
	
	int check_item(int pos){
		if(right != 1)return pos;
		pos = check_fac(pos);
		while(pos<L.size() && (L[pos] == "times" || L[pos] == "slash")){
			pos = check_fac(pos+1);
		}

		return pos;
	}
	
	int check_fac(int pos){
		if(right != 1)return pos;
		if(L[pos] == "ident" || L[pos] == "number")return pos+1;
		else if(L[pos] == "lparen"){
			pos = check_S(pos+1);
			if(pos>=L.size() || L[pos]!="rparen"){
				right = min(right,0);
				return pos;
			}
			else {
				return pos+1;
			}
		}
		else {
			right = -1;
			cout<<"This pos : "<<pos<< " is wrong!"<<endl;
			return 0;
		}
	}
	
	int judge(){
		right = 1;
		int end = check_T(0);
		if(end < L.size() || right == 0){
			cout<<right<<endl;
			if(right != -1)cout<<"This pos : "<<end<< " is wrong!"<<endl;	
			right = 0;
		}
		return right;
	}
	
	// 
	int check_T(int pos){
		if(right != 1) return pos;
		pos = check_S(pos);
		if((L[pos] == "eql" || L[pos] == "neq" || L[pos] == "lss" 
			|| L[pos] == "leq" || L[pos] == "gtr" || L[pos] == "geq")){
			pos = check_S(pos+1);		
		}
		return pos;
	} 
	
	
}CI;

void testByChar(analy_PL0 CI)  
{  
	fstream testByCharFile;  
    char c; 
	char s[1000]; 
	vector <char>v;
    freopen("ex3_1.in","r",stdin);
    while(gets(s))  
    {  
    	v.clear();
        int L = strlen(s);	
		for(int i=0;i<L;++i){
			v.push_back(s[i]);
		}
        CI.DFA(v);
        //v.clear(); 
        CI.shoWord();
	    CI.transWord();
	    if(CI.judge() == 1){
	    	cout << "语法正确" <<endl;
	    	//CI.cal(v); 
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

