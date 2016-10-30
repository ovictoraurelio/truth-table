/***
	*
	* @author cin.ufpe.br/~vags
	* @since 17/08/16
	*
*/
#include <bits/stdc++.h>
#define MAX_EXPR 200

using namespace std;

string header, dashed;
string exprGlobal;
int sizeOfAllExprs;
vector<pair<int,int> > exprs;
map<string, bool> resultsLine;
map<char,int > m,cs;

int m = {0,0,0,0}, cs = {0,0,0,0};

int szM(map<char,int> m){
	int t=0;
	t+=m['t'];
	for(int i=0; i<3; i++) t+=m[char('x'+i)];
	return t;
}
// This method print a string thats start at index i and goes to index l
void ps(char *s, int i, int l){
	while(i<=l)printf("%c", s[i++]);
}
// This method compare a string thats start at index i and goes to index l
bool compareStr(char *s, int la, int ra, int lb, int rb){
	if(ra-la != rb-lb) return false;
	for(int i=la; i<=ra; i++) if(s[i] != s[(i-la)+lb]) return false;	
	return true;
}
//set in a map, wich var i'm use
map<char,int> setVarsOnExprs(map<char,int> m, char *s){
	m['x'] = m['y'] = m['z'] = m['t'] = 0;	
	while(s = strpbrk(s, "xyzt")) m[*(s++)] = 1;
	return m;
}
//calc a value for a minimal logic expression
bool calcExpr(int a, int b, char c){
	switch(c){		
		case '+': return a | b;
		case '.': return a & b;		
		case '>': return (!a | b);
		default: return a;
	}
}
//checking value of a literal
bool vM(char a){	
	if(a == 48)return false;
	if(a == 49)return true;
	return cs[a];
}
bool solveMin(string e){
	if(e.size() == 1){
			return vM(e.at(0));
	}else{
		if(e.size() == 4){// (-x)			
			return !vM(e.at(2));
		}if(e.size() == 5){//(x+y)
			return calcExpr(vM(e.at(1)), vM(e.at(3)), e.at(2));// seriam as operações...
		}
	}
}
//getting all exprs inside ( ) of a expression
void getExprs(char *s, int start, int end){	
	stack<int> l;//left
	for(int i=0; i<=end; i++){
		if(s[i] == '('){			
			l.push(i);
		}else if(s[i] == ')'){			
			exprs.push_back(pair<int,int>(l.top(), i));
			l.pop();
		}
	}
}

//removing equals exprs of a expresion
void redundancyRemove(char *s){
	for(int i=exprs.size()-1; i>0; i--){		
		for(int j=0; j<i; j++){			
			if(i!=j && compareStr(s, exprs[i].first,exprs[i].second,exprs[j].first,exprs[j].second)){				
				exprs.erase(exprs.begin() + i);
			}
		}
	}
}

void solveExprs(){
	string lookingFor, current, original;
	size_t fSubExpr;	
	for(int i=0; i<exprs.size(); i++){		
		current = exprGlobal.substr(exprs[i].first, exprs[i].second - exprs[i].first + 1);
		original = current;	
		if(current.size() <= 5){// (x+y) ou -x						
			resultsLine[current] = solveMin(current.c_str());
		}else{
			/*for(int j=0; j<exprs.size(); j++){*/
				/*lookingFor = exprGlobal.substr(exprs[j].first, exprs[j].second - exprs[j].first + 1);				
				if(j < i){
					while(current.find(lookingFor) != string::npos){//buscando as subexpressões e substituindo pelos valores já conhecidos
						current.replace(current.find(lookingFor), lookingFor.size(),1,resultsLine[lookingFor] ? '1' : '0');
					}
				}*/
				/*cout << " valores: x: " << cs['x'] << " y:"  << cs['y'] << " z: " << cs['z'] << " t: " << cs['t'];*/
				/*cout << endl << endl << current << endl;*/

				int last;
				for(int k=0; k<current.size(); k++){					
					if(current.at(k) == '('){			
						last = k;
					}else if(current.at(k) == ')'){
						/*printf("inside %d-%d\n", last, k);
						cout << " vou resolver: " << current.substr(last, k-last+1) << endl;*/
						current.replace(last, k - last +1,1, solveMin(current.substr(last, k-last + 1)) ? '1':'0');
						/*cout << " new current: " << current << endl;*/
						//exprs.push_back(pair<int,int>(l.top(), k));
						last = 0;
						k=-1;
					}
				}


				resultsLine[original] = solveMin(current);
				/*cout << "Solving for " << original << " torned: " << current << " value " << resultsLine[original] << endl;*/
			/*}	*/					
		}		
	}
}

void showResults(){
	solveExprs();
	//for (std::map<string,bool>::iterator it=resultsLine.begin(); it!=resultsLine.end(); ++it)
	for(int i=0; i<exprs.size(); i++){
		string current = exprGlobal.substr(exprs[i].first, exprs[i].second - exprs[i].first + 1);
		for(int b=0; b<exprs[i].second - exprs[i].first; b++) printf(" ");
		printf("%d|",resultsLine[current]);
	}
	printf("\n");
}



void solveTable(map<char,int> m){
	int size = szM(m);	
	
	for(int x=0; x<(size>0?2:0); x++){
		for(int y=0; y<(size>1?2:0); y++){
			for(int z=0; z<(size>2?2:0); z++){
				for(int t=0; t<(size>3?2:0); t++){					
					if(size==4){
						cs['x']=x%2;cs['y']=y%2;cs['z']=z%2;cs['t']=t%2;
						cout << dashed << endl;
						//previous...						
						printf("|%d|%d|%d|%d|", m['x'], m['y'], m['z'], m['t']);						
						//... results
						showResults();
					}
				}
				if(size==3){
					cs['x']=x%2;
					cs['y']=y%2;
					if(m['y']){						
						cs['z']=z%2;					
					}else{
						cs['z']=y%2;
					}
					cs['t']=z%2;
					//previous...
					cout << dashed << endl;
					printf("|%d|%d|%d|", cs['x'], cs['y'], cs['z']);
					//... results
					showResults();					
				}
			}
			if(size==2){
				cs['x']=x%2;cs['y']=y%2;cs['z']=y%2;cs['t']=y%2;
				//previous...
				cout << dashed << endl;
				printf("|%d|%d|", cs['x'], cs['y']);		
				//... results
				showResults();				
			}
		}
		if(size==1){
			cs['x']=x%2;cs['y']=x%2;cs['z']=x%2;cs['t']=x%2;
			//previous...
			cout << dashed << endl;
			printf("|%d|", m['x']);
			//... results
			showResults();
		}
	}	
}

int main(){	
	int c=0,highlights[50];
	char expr[MAX_EXPR],*f;
	scanf("%d", &c);
	for(int k=1; k<=c; k++){
		printf("Tabela #%d\n", k);
		cin >> expr;
		exprGlobal=string(expr);
		m = setVarsOnExprs(m, expr);		

		getExprs(expr, 0, strlen(expr));
		redundancyRemove(expr);
		
		header = "|" + string() + (m['x']?"x|":"") + string() + (m['y']?"y|":"") + string() + (m['z']?"z|":"") + string() + (m['t']?"t|":"") + string();		
		for(int i=0; i<exprs.size(); i++){
			header += string(expr).substr(exprs[i].first, exprs[i].second - exprs[i].first + 1);
			header += "|";
		}			
		for(int i=0; i<header.size(); i++) dashed += "-";
		cout << dashed << endl << header << endl;

		solveTable(m);
		
		cout << dashed << endl << endl;
		exprs.clear();
		dashed.clear();
	}
	return 0;
}













/*void solveInputs(map<char,int> m, char *expr){
	string s(expr);
	vector<char> copia(s.begin(), s.end());
	bool result = false;
	int start=0, first=1, second=2, third=3;

	int sAll = strlen(s);
	stack<int> l;//left (

	for(int i=0; i<=end; i++){
		if(s[i] == '('){
			l.push(i);
		}else if(s[i] == ')'){		
			start = i;
			first = i+1;
			second = i+2;
			third = i+3;
			while(copia[start] == '('){
				if(copia[second] != '-' && copia[third] != '('){
					result = calcExpr(m[copia[first]], m[copia[third]], copia[second]);				
					copia.erase(v.begin() + start, v.begin() + second );//(-x) apago até o indice 2, no terceiro indce(4 caracter) fica o resultado..
					copia[start] = result;
				}else if(copia[first] == '-' && copia[first] != '('){
					result = calcExpr(m[copia[second]], 0,'-');
					copia.erase(v.begin() + start, v.begin() + third );//(x+y) mesma lógica.. só que aqui tem um caracter a mais...
					copia[start] = result;
				}
			}
		}
	}
	return sAll;

	for(int i=0; i<exprs.size(); i++){
		copia = vector<char>(s.begin(), s.end());

		
	}
}**/
