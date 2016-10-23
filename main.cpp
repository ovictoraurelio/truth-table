/***
	*
	* @author cin.ufpe.br/~vags
	* @since 17/08/16
	*
*/
#include <bits/stdc++.h>

using namespace std;

queue<pair<int,int> > exprs;


int szM(map<char,int> m){
	int t=0;
	t+=m['t'];
	for(int i=0; i<3; i++) t+=m[char('x'+i)];
	return t;
}

void ps(char *s, int i, int l){	
	while(i<=l)printf("%c", s[i++]);
}

void buildInputs(map<char,int> m){
	int size = szM(m);	
	
	for(int i=0; i<(size>0?2:0); i++){
		for(int j=0; j<(size>1?2:0); j++){
			for(int k=0; k<(size>2?2:0); k++){
				for(int l=0; l<(size>3?2:0); l++){
					if(size==4)printf("%d | %d | %d | %d\n", i%2,j%2,k%2,l%2);
				}
				if(size==3)printf("%d | %d | %d \n", i%2,j%2,k%2);
			}
			if(size==2)printf("%d | %d \n", i%2,j%2);
		}
		if(size==1)printf("%d \n", i%2);
	}
	printf("-------------\n");
}

map<char,int> setVarsOnExprs(map<char,int> m, char *s){
	m['x'] = m['y'] = m['z'] = m['t'] = 0;	
	while(s = strpbrk(s, "xyzt")) m[*(s++)] = 1;
	return m;
}

int getExprs(char *s, int start, int end){	
	stack<int> l;//left (
	for(int i=0; i<=end; i++){
		if(s[i] == '('){
			l.push(i);
		}else if(s[i] == ')'){
			exprs.push(pair<int,int>(l.top(), i));
			l.pop();
		}
	}
}


int main(){
	map<char,int > m;	
	int highlights[50];
	char expr[50], *f;
	while(scanf(" %s",expr) != EOF){
		m = setVarsOnExprs(m, expr);		
		printf("\n\tAll expr: %s\nPresent values x:%d, y:%d, z:%d, t:%d \t Lenght of truth table: %d\n",expr, m['x'], m['y'], m['z'], m['t'],szM(m));	

		getExprs(expr, 0, strlen(expr));

		printf("%s%s%s%s",m['x']?"x |":"", m['y']?"y |":"", m['z']?"z |":"", m['t']?"t |":"");
		while(!exprs.empty()){
			printf(" | ");
			ps(expr, exprs.front().first, exprs.front().second);			
			exprs.pop();
		}
		printf("\n");
		buildInputs(m);	
		printf("------------------------------------\n");
		printf("------------------------------------\n");
	}
	return 0;
}
