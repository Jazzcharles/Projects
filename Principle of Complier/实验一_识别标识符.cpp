#include<bits/stdc++.h>
using namespace std;

// ±êÊ¶·û 
class symbol_Result{
	public :
		string str;
		int answer;
};



vector<symbol_Result> symbol;

void showResult(){
	int n = symbol.size();
	cout<<"The Result is:"<<endl;
	for(int i=0;i<n;++i){
		cout<<"("<<symbol[i].str<<":"<<symbol[i].answer<<")"<<endl;
	}
}
class analy_PL0{
	public : 
		map<string,string>mp;
		vector<pair<string,int> > cnt;
		
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
	

	void store2Result(){
		int n = cnt.size();
		for(int i=0;i<n;++i){
			symbol_Result temp;
			temp.str = cnt[i].first;
			temp.answer = cnt[i].second;
			symbol.push_back(temp);
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
			if(isdigit(v[i]) || isalpha(v[i])){
				if(ff==0)l = i;
				ff=1;
			}
			else if(ff == 1 && !(isdigit(v[i]) || isalpha(v[i]))){
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
					if(isdigit(tep[0]))continue;
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
}CI;

void testByChar(analy_PL0 CI)  
{  
	fstream testByCharFile;  
    char c; 
	char s[1000]; 
	vector <char>v;
    freopen("inFile1.txt","r",stdin);
    while(gets(s))  
    {  
        int L = strlen(s);	
		for(int i=0;i<L;++i){
			v.push_back(s[i]);
		}
        CI.find_symbols(v);
        v.clear(); 
    }   
    CI.store2Result();
    showResult();
}  

char s[100];

int main(){
	CI.init();
	testByChar(CI);	
	return 0;
}

