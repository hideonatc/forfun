#include<iostream>
#include<ctime>
#include<cstdlib>
#include<map>
#include<queue>
#define cps CLOCKS_PER_SEC
using namespace std;
struct nod{
	int x,y;
};
map<char,int> mov;
int stp[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
nod head,tail;
int size,score=0;
bool ed=0;
char mp[13][13];
queue<int> dir;
void set_map(){
	for(int i=0;i<13;i++)
		for(int j=0;j<13;j++)
			mp[i][j]='x';
	for(int i=0;i<=size+1;i++)
		mp[i][0]=mp[i][size+1]=mp[0][i]=mp[size+1][i]='o';
	mp[size/2][size/2+1]=mp[size/2][size/2]='o';
}
void show_map(){
	printf("score:%d\n",score);
	for(int i=1;i<=size;i++){
		for(int j=1;j<=size;j++){
			cout<<mp[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
bool eaten(){
	for(int i=1;i<=size;i++)
		for(int j=1;j<=size;j++)
			if(mp[i][j]=='A')
				return 0;
	return 1;
}
void generate_apple(){
	srand(time(NULL));
	while(1){
		int x=rand()%size+1,y=rand()%size+1;
		if(mp[x][y]=='x'){
			mp[x][y]='A';
			break;
		}
	}
	system("clear");
	show_map();
	return;
}
void debug(){
	queue<int> bk;
	while(!dir.empty()){
		bk.push(dir.front());
		cout<<dir.front()<<" ";
		dir.pop();
	}
	while(!bk.empty()){
		dir.push(bk.front());
		bk.pop();
	}
	cout<<endl;
	return;
}
void update_map(char c){
	if(eaten())
		generate_apple();
	head.x+=stp[mov[c]][0];
	head.y+=stp[mov[c]][1];
	if(mp[head.x][head.y]=='A'){
		score++;
		mp[head.x][head.y]='o';
		dir.push(mov[c]);
	}
	else{
		mp[tail.x][tail.y]='x';
		tail.x+=stp[dir.front()][0];
		tail.y+=stp[dir.front()][1];
		dir.pop();
		if(mp[head.x][head.y]=='o'){
			ed=1;
			return;
		}
		mp[head.x][head.y]='o';
		dir.push(mov[c]);
	}
	system("clear");
	show_map();
	//debug();
}
int main(){
	system("clear");
	string in;
	printf("(s) to start\n(q) to quit\n");
	cin>>in;
	if(in=="q")
		return 0;
	while(in!="s"){
		printf("Invalid\n");
		cin>>in;
		if(in=="q")
			return 0;
	}
	system("clear");
	printf("choose map size:\n<5*5~10*10> (5~10)\n");
	while(cin>>size){
		if(size>=5&&size<=10)
			break;
		printf("Invalid\n");
	}
	system("clear");
	set_map();
	show_map();
	printf("press w a s d to start and move\n");
	string mv;
	char last=mv[0];
	mov['w']=0;
	mov['a']=1;
	mov['s']=2;
	mov['d']=3;
	head.x=size/2;
	head.y=size/2;
	tail.x=size/2;
	tail.y=size/2+1;
	dir.push(1);
	clock_t start=clock();
	while(!ed){
		clock_t now=clock();
		if(double(now-start)/CLOCKS_PER_SEC>0.2){
			start=now;
			update_map(last);
		}
		else if(cin>>mv){
			update_map(mv[0]);
			last=mv[0];
		}
	}
	printf("YOU LOSE and your score is:%d\n",score);
}