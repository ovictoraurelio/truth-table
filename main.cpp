/***
	*
	* @author cin.ufpe.br/~vags
	* @since 17/08/16
	*
*/
#include <bits/stdc++.h>
#define MAX_EXPR 200

using namespace std;

string exprGlobal;
int sizeOfAllExprs;
vector<pair<int,int> > exprs;
map<string, bool> resultsLine;
map<char,int > m,cs;

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

map<char,int> setVarsOnExprs(map<char,int> m, char *s){
	m['x'] = m['y'] = m['z'] = m['t'] = 0;	
	while(s = strpbrk(s, "xyzt")) m[*(s++)] = 1;
	return m;
}

int getExprs(char *s, int start, int end){
	int sAll = strlen(s);
	stack<int> l;//left (
	for(int i=0; i<=end; i++){
		if(s[i] == '('){
			l.push(i);
		}else if(s[i] == ')'){
			sAll += (i - l.top() - 1);//talvez tenha um -1 aqui..
			exprs.push_back(pair<int,int>(l.top(), i));
			l.pop();
		}
	}
	return sAll;
}

void redundancyRemove(char *s){
	for(int i=exprs.size()-1; i>0; i--){		
		for(int j=0; j<i; j++){			
			if(i!=j && compareStr(s, exprs[i].first,exprs[i].second,exprs[j].first,exprs[j].second)){				
				exprs.erase(exprs.begin() + i);
			}
		}
	}
}

bool calcExpr(int a, int b, char c){
	switch(c){		
		case '+': return a | b;
		case '.': return a & b;		
		case '>': return (!a | b);
		default: return a;
	}
}

bool vM(char a){	
	if(int(a) == 0)return false;
	if(int(a) == 1) return true;
	//printf("::%c::\n", a);
	return cs[a];
}

bool solveMin(string e){
	if(e.size() == 1){
			return vM(e.at(0));
	}else{
		if(e.size() == 4){// (-x)
			//printf("\naqui %c - %d-%d\n", e.at(2),vM(e.at(2)),!vM(e.at(2)));
			return !vM(e.at(2));
		}if(e.size() == 5){// (x+y)
			return calcExpr(vM(e.at(1)), vM(e.at(3)), e.at(2));// seriam as operações...
		}
	}
}

bool solveExpr(){
	string lookingFor, current;
	size_t fSubExpr;
	//printf("I will lookingFor %d exprs\n", exprs.size());
	for(int i=0; i<exprs.size(); i++){		
		current = exprGlobal.substr(exprs[i].first, exprs[i].second - exprs[i].first + 1);
	//	cout << "The expr: " << current;
		if(current.size() <= 5){// (x+y) ou -x			
			//printf("inside her %d\n",solveMin(current.c_str());
			resultsLine[current] = solveMin(current.c_str());
		}else{
			for(int j=0; j<exprs.size(); j++){
				lookingFor = exprGlobal.substr(exprs[j].first, exprs[j].second - exprs[j].first + 1);
				if(j < i){//ordem crescente das expressões..
					fSubExpr = current.find(lookingFor);
					if(fSubExpr != string::npos){//buscando as subexpressões e substituindo pelos valores já conhecidos
						current.replace(current.begin() + fSubExpr, current.begin() + lookingFor.size(),1, resultsLine[lookingFor]);
					}
				}
				resultsLine[current] = solveMin(current);
			}
		}		
		//printf("\tThe boolean %d\n", resultsLine[current]);
	}
}



void calcInputs(map<char,int> m){
	int size = szM(m);	
	
	for(int x=0; x<(size>0?2:0); x++){
		for(int y=0; y<(size>1?2:0); y++){
			for(int z=0; z<(size>2?2:0); z++){
				for(int t=0; t<(size>3?2:0); t++){					
					if(size==4){
						m['x']=x%2;m['y']=y%2;m['z']=z%2;m['t']=t%2;
						for(int i=0; i<sizeOfAllExprs; i++)printf("-");printf("\n");
						//previous...						
						printf("|%d|%d|%d|%d|", m['x'], m['y'], m['z'], m['t']);						
						//... results
						solveExpr();
						for (std::map<string,bool>::iterator it=resultsLine.begin(); it!=resultsLine.end(); ++it)
    						std::cout << it->first << " => " << it->second << '\n';

						printf("|\n");
					}
				}
				if(size==3){
					m['x']=x%2;m['y']=y%2;m['z']=z%2;m['t']=z%2;
					//previous...
					for(int i=0; i<sizeOfAllExprs; i++)printf("-");printf("\n");
					printf("|%d|%d|%d|", m['x'], m['y'], m['z']);
					//... results
					printf("\n");
				}
			}
			if(size==2){
				cs['x']=x%2;cs['y']=y%2;cs['z']=y%2;cs['t']=y%2;
				//previous...
				for(int i=0; i<sizeOfAllExprs; i++)printf("-");printf("\n");
				printf("|%d|%d|", cs['x'], cs['y']);

				solveExpr();
				//for (std::map<string,bool>::iterator it=resultsLine.begin(); it!=resultsLine.end(); ++it)
				for(int i=0; i<exprs.size(); i++){
					string current = exprGlobal.substr(exprs[i].first, exprs[i].second - exprs[i].first + 1);
					printf("%d|",resultsLine[current]);
				}
				//... results
				printf("\n");
			}
		}
		if(size==1){
			m['x']=x%2;m['y']=x%2;m['z']=x%2;m['t']=x%2;
			//previous...
			for(int i=0; i<sizeOfAllExprs; i++)printf("-");printf("\n");
			printf("|%d|", m['x']);
			//... results
			printf("\n");
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
		//printf("\n\tAll expr: %s\nPresent values x:%d, y:%d, z:%d, t:%d \t Lenght of truth table: %d\n",expr, m['x'], m['y'], m['z'], m['t'],szM(m));	

		sizeOfAllExprs = getExprs(expr, 0, strlen(expr));
		redundancyRemove(expr);
		for(int i=0; i<sizeOfAllExprs; i++)printf("-");printf("\n");		
		printf("|%s%s%s%s",m['x']?"x|":"", m['y']?"y|":"", m['z']?"z|":"", m['t']?"t|":"");
		for(int i=0; i<exprs.size(); i++){
			printf("|");
			ps(expr, exprs[i].first, exprs[i].second);
			//exprs.pop();
		}
		/*for(vector<pair<int, int> >::iterator it = exprs.begin(); it != exprs.end(); it++){
			printf(" | ");
			ps(expr, it->first, it->second);			
		}*/
		printf("\n");
		calcInputs(m);
		for(int i=0; i<sizeOfAllExprs; i++) printf("-");
		printf("\n\n");
		exprs.clear();
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
