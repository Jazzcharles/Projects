#include<bits/stdc++.h>
using namespace std;

class analy_PL0{
	public : 
		map<string,string>mp;
		vector<pair<string,int> > cnt;
		vector<pair<string,string> > cnt_word;
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

	void showSymbols(){
		int n = cnt.size();
		for(int i=0;i<n;++i){
			cout<<cnt[i].first<<" "<<cnt[i].second<<endl;
			
		}
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
		×´Ì¬×ª»» 
*/
	void transfer(int state,string t){
		if(t.size() == 0)return ;
		if(state == 1){
			if(mp.count(t))cnt_word.push_back(make_pair(mp[t],t));
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
		v.push_back(' '); 
		int L = v.size();
		for(int i=0;i<L;++i){
			if(v[i]>='A' && v[i]<='Z')v[i] = v[i]-'A'+'a';
		}
		int current = 0; // µ±Ç°×´Ì¬
		int i = 0;
		string temp = "";
		while(i<L){
			//cout<<i<<endl;
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
}CI;

void testByChar(analy_PL0 CI)  
{  
	fstream testByCharFile;  
    char c; 
	char s[1000]; 
	vector <char>v;
    freopen("inFile3.txt","r",stdin);
    while(gets(s))  
    {  
        int L = strlen(s);	
		for(int i=0;i<L;++i){
			v.push_back(s[i]);
		}
        CI.DFA(v);
        v.clear(); 
    }   
    CI.shoWord();
}  

char s[100];

int main(){
	CI.init();
	testByChar(CI);	
	return 0;
}

