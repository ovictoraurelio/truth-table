/***
	*
	* @author victoraurelio.com
	* @since 22/10/16
	*
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>

#include <algorithm>
#include <fstream>

#define MAX_SUB_EXPR 9999999

using namespace std;

// file to output results
ofstream outFile;
// header is a string to show in header of table
// dashed is ------ of table
// expr is a string scanned from keyboard or from file
string header, dashed, expr;
// a pair if index of start and ends of a expr in string
vector<pair<int,int> > exprs;
// results of each subexpr
bool results[MAX_SUB_EXPR];
// counter to trues and counter to falses at expr
int cT=0,cF=0;
// 		    x,y,z,t    		  x,y,z,t
int m[4] = {0,0,0,0}, v[4] = {0,0,0,0};

//Retornar true se o primeiro for menor.
//Isso tá gigante, porque fiz várias tentativas para descobrir qual os critérios para ordenar as subexpressões no header e não consegui acertar.
bool firstLessThenNext(pair<int, int> i, pair<int, int> j){
	vector<int> iL, jL;
	if(i.second - i.first > j.second - j.first) return false;
	if(i.second - i.first < j.second - j.first) return true;
	for(int k=i.first,l=j.first; k<i.second; k++,l++){		
		 if(expr.at(k) != '.' && expr.at(k) != '+' && expr.at(k) != '>')
		 	iL.push_back(k);
		 if(expr.at(l) != '.' && expr.at(l) != '+' && expr.at(l) != '>')
		 	jL.push_back(l);	
	}
	for(int k=0; k<iL.size(); k++){
		if(expr.at(iL[k]) > expr.at(jL[k])){
			return false;
		}
	}
	return true;
}

int szM(){
	int t=0;	
	for(int i=0; i<4; i++) t += m[i];
	return t;
}
bool compareStr(string s, int la, int ra, int lb, int rb){
	if(ra-la != rb-lb) return false;
	for(int i=la; i<=ra; i++) if(s.at(i) != s.at((i-la)+lb)) return false;	
	return true;
}
char itl(int i){//Int To Letter
	switch(i){
		case 0: return 'x';
		case 1: return 'y';
		case 2: return 'z';
		case 3: return 't';
		default: return -1;
	};
}
int lti(char i){//Letter T oInt
	switch(i){
		case 'x': return 0;
		case 'y': return 1;
		case 'z': return 2;
		case 't': return 3;
		default: return -1;
	};
}
//set in a vector, wich vars i'm use
void setVarsOnExprs(string s){
	m[0] = m[1] = m[2] = m[3] = 0;
	for(int i=0; i<s.size(); i++)
		if(lti(s.at(i)) != -1){
			m[lti(s.at(i))] = 1;
		}		
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
	return v[lti(a)];
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
void getExprs(string s){
	vector<int> l;//left
	for(int i=0; i<s.size(); i++){
		if(s.at(i) == '('){			
			l.push_back(i);
		}else if(s.at(i) == ')'){			
			exprs.push_back(pair<int,int>(l.back(), i));
			l.pop_back();
		}
	}
}

//removing equals exprs of a expresion
void redundancyRemove(string s){	
	for(int i=exprs.size()-1; i>=0; i--){
		for(int j=0; j<i; j++){
			if(i!=j && compareStr(s, exprs[i].first,exprs[i].second,exprs[j].first,exprs[j].second)){				
				exprs.erase(exprs.begin() + i);
			}
		}
	}
}

void solveExprs(){
	string current;	
	for(int i=0; i<exprs.size(); i++){		
		current = expr.substr(exprs[i].first, exprs[i].second - exprs[i].first + 1);		
		if(current.size() <= 5){// (x+y) ou -x						
			results[i] = solveMin(current.c_str());
		}else{
			int last;
			for(int k=0; k<current.size(); k++){			
				if(current.at(k) == '('){			
					last = k;
				}else if(current.at(k) == ')'){
					current.replace(last, k - last +1,1, solveMin(current.substr(last, k-last + 1)) ? '1':'0');					
					last = 0;
					k=-1;
				}
			}
			results[i] = solveMin(current);				
		}		
	}
}

void showResults(){	
	solveExprs();	
	for(int i=0; i<exprs.size(); i++){		
		for(int b=0; b<exprs[i].second - exprs[i].first; b++) outFile << " ";		
		outFile << (results[i]?1:0) << "|";
	}
	results[exprs.size()-1] ? cT++ : cF++;//just consider last column of table
	outFile << endl;
}

void setValuesFromLine(int ind[4]){
	for(int i=0,j=0; i<4; i++){
		if(m[i] == 1){
			v[i] = ind[j]%2;
			j++;
		}
	}
}
void solveTable(){
	int ind[4], size = szM();	
	
	for(ind[0]=0; ind[0]<(size>0?2:0); ind[0]++){		
		for(ind[1]=0; ind[1]<(size>1?2:0); ind[1]++){			
			for(ind[2]=0; ind[2]<(size>2?2:0); ind[2]++){				
				for(ind[3]=0; ind[3]<(size>3?2:0); ind[3]++){
						setValuesFromLine(ind);					
						outFile << dashed << endl;						
						outFile << "|" << ind[0]%2 << "|" << ind[1]%2 << "|" << ind[2]%2 << "|" << ind[3]%2 << "|";
						showResults();					
				}
				if(size==3){
					setValuesFromLine(ind);					
					outFile << dashed << endl;					
					outFile << "|" << ind[0]%2 << "|" << ind[1]%2 << "|" << ind[2]%2 << "|";
					showResults();					
				}
			}
			if(size==2){
				setValuesFromLine(ind);				
				outFile << dashed << endl;				
				outFile << "|" << ind[0]%2 << "|" << ind[1]%2 << "|";
				showResults();				
			}
		}
		if(size==1){
			setValuesFromLine(ind);			
			outFile << dashed << endl;			
			outFile << "|" << ind[0]%2 << "|";
			if(expr.size()<=2){				
				cT++;cF++;
			}
			showResults();
		}
	}
}	

int main(){	
	int c=0,highlights[50];
	char *f;
	ifstream inFile ("Expressoes.in", ios::in);
	outFile.open("Expressoes.out", ios::out);

	if(inFile.is_open() && outFile.is_open()){
		inFile >> c;
		for(int k=1; k<=c; k++){
			outFile << "Tabela #" << k << endl;
			inFile >> expr;

			setVarsOnExprs(expr);		
			getExprs(expr);		
			
			redundancyRemove(expr);
			sort(exprs.begin(), exprs.end(), firstLessThenNext);
			
			header = "|" + string() + (m[0]?"x|":"") + string() + (m[1]?"y|":"") + string() + (m[2]?"z|":"") + string() + (m[3]?"t|":"") + string();
			for(int i=0; i<exprs.size(); i++){
				header += expr.substr(exprs[i].first, exprs[i].second - exprs[i].first + 1);
				header += "|";
			}			
			for(int i=0; i<header.size(); i++) dashed += "-";
			outFile << dashed << endl << header << endl;

			solveTable();
		
			outFile << dashed << endl;		

			if(cT > 0 && cF > 0 ){
				outFile << "satisfativel e refutavel";
			}else if(cT > 0 and cF == 0){
				outFile << "satisfativel e tautologia";
			}else{
				outFile << "insatisfativel e refutavel";
			}
			outFile << endl << endl;

			exprs.clear();
			dashed.clear();
			cT = cF = 0;			
		}
		inFile.close();
		outFile.close();
	}else{
		cout << "Nao consegui abrir o arquivo";
	}
	return 0;
}