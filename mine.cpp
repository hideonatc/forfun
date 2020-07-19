#include<iostream>
#include<cstdio>
#include<ctime>
#include<cstdlib>
using namespace std;
int size,mines=0;
bool lose=0;
char public_map[13][13],private_map[13][13];
int dir[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
char set_num(int x,int y){
	int r=0;
	for(int i=0;i<8;i++)
		if(private_map[x+dir[i][0]][y+dir[i][1]]=='*')
			r++;
	if(r==0)
		return 'n';
	return char(r+int('0'));
}
void generate_map(){
	srand(time(NULL));
	for(int i=0;i<13;i++)
		for(int j=0;j<13;j++)
			private_map[i][j]='1';
	for(int i=1;i<=size;i++){
		for(int j=1;j<=size;j++){
			if(rand()%10==0){
				private_map[i][j]='*';
				mines++;
			}
			else
				private_map[i][j]='0';
		}
	}
	for(int i=1;i<=size;i++){
		for(int j=1;j<=size;j++){
			if(private_map[i][j]=='0')
				private_map[i][j]=set_num(i,j);
		}
	}
	for(int i=1;i<=size;i++)
		for(int j=1;j<=size;j++)
			public_map[i][j]='o';
}
void print_map(){
	printf("mines left:%d\n",mines);
	for(int i=1;i<=size;i++){
		for(int j=1;j<=size;j++){
			cout<<public_map[i][j]<<"   ";
		}
		cout<<endl<<endl;
	}
	printf("<flag> (f)\n<unflag> (u)\n<step> (s)\n");
	return;
}
void extend(int x,int y){
	printf("extend(%d,%d)\n",x,y);
	if(x<=0||x>size||y<=0||y>size)
		return;
	if(private_map[x][y]!='n'){
		public_map[x][y]=private_map[x][y];
		return;
	}
	if(private_map[x][y]=='n'){
		private_map[x][y]=public_map[x][y]='0';
		if(x+1<=size)
			extend(x+1,y);
		if(x-1>0)
			extend(x-1,y);
		if(y+1<=size)
			extend(x,y+1);
		if(y-1>0)
			extend(x,y-1);
	}
	return;
}
void flag(int x,int y){
	mines--;
	if(x<=0||x>size||y<=0||y>size||mines<0){
		printf("Invalid!!\n");
		return;
	}
	public_map[x][y]='f';
	system("clear");
	print_map();
}
void unflag(int x,int y){
	mines++;
	if(x<=0||x>size||y<=0||y>size||public_map[x][y]!='f'){
		printf("Invalid!!\n");
		return;
	}
	public_map[x][y]='o';
	system("clear");
	print_map();
}
void step(int x,int y){
	if(x<=0||x>size||y<=0||y>size||isdigit(public_map[x][y])){
		printf("Invalid!!\n");
		return;
	}
	if(private_map[x][y]=='*'){
		system("clear");
		lose=1;
		printf("YOU LOSE\n");
		return;
	}
	else if(private_map[x][y]!='n'){
		public_map[x][y]=private_map[x][y];
		system("clear");
		print_map();
		return;
	}
	else{
		extend(x,y);
		system("clear");
		print_map();
		return;
	}
}
bool end(){
	for(int i=1;i<=size;i++)
		for(int j=1;j<=size;j++)
			if(public_map[i][j]=='o')
				return 0;
	system("clear");
	printf("YOU WIN!!!!\n");
	return 1;
}
void print_private_map(){
	for(int i=1;i<=size;i++){
		for(int j=1;j<=size;j++){
			cout<<private_map[i][j]<<"   ";
		}
		cout<<endl<<endl;
	}
	string s;
	cin>>s;
	system("clear");
	return;
}
int main(){
	system("clear");
	string in;
	printf("<start a new game> (s)\n<quit> (q)\n");
	cin>>in;
	if(in=="q")
		return 0;
	else{
		system("clear");
		printf("choose size:\n<5*5> (5)\n<6*6> (6)\n<7*7> (7)\n<8*8> (8)\n<9*9> (9)\n<10*10> (10)\n");
		cin>>size;
		system("clear");
	}
	generate_map();
	//print_private_map();
	print_map();
	int x,y;
	while(cin>>in&&!end()&&!lose){
		cin>>x>>y;
		if(in=="f")
			flag(x,y);
		else if(in=="u")
			unflag(x,y);
		else if(in=="s")
			step(x,y);
		if(lose)
			break;
	}
	return 0;
}