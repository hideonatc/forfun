#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstdio>
using namespace std;
char map[13][13];
bool block[10][3][3]={{{1,0,0},{1,0,0},{1,1,1}},{{0,0,1},{0,0,1},{1,1,1}},{{1,0,0},{1,1,0},{0,0,0}},{{0,1,0},{1,1,0},{0,0,0}},{{1,0,0},{0,0,0},{0,0,0}},{{1,1,0},{1,1,0},{0,0,0}},{{1,1,1},{1,1,1},{1,1,1}},{{1,1,0},{0,0,0},{0,0,0}},{{1,1,1},{0,0,0},{0,0,0}},{{1,1,1},{0,1,0},{0,0,0}}};
int score=0,each_score[10]={5,5,3,3,1,4,9,2,3,4};
int block_now[4],allblock[3][11];
void set_map(){
	for(int i=1;i<=12;i++)
		map[i][11]=map[i][12]=map[11][i]=map[12][i]='1';
	for(int i=0;i<=10;i++)
		for(int j=0;j<=10;j++)
			map[i][j]='x';
	return;
}
void show_map(){
	system("clear");
	printf("score:%d\n",score);
	for(int i=1;i<=10;i++)
		cout<<i<<" ";
	cout<<endl<<endl;
	for(int i=1;i<=10;i++){
		for(int j=1;j<=10;j++)
			cout<<map[i][j]<<" ";
		cout<<"  "<<i<<endl;
	}
	cout<<endl;
}
void generate_block(){
	srand(time(NULL));
	int a=rand()%10,b=rand()%10,c=rand()%10;
	block_now[1]=a;
	block_now[2]=b;
	block_now[3]=c;
	for(int i=0;i<3;i++)
		for(int j=0;j<11;j++)
			allblock[i][j]=-1;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			allblock[i][j]=block[a][i][j]?a:-1;
	for(int i=0;i<3;i++)
		for(int j=4;j<7;j++)
			allblock[i][j]=block[b][i][j-4]?b:-1;
	for(int i=0;i<3;i++)
		for(int j=8;j<11;j++)
			allblock[i][j]=block[c][i][j-8]?c:-1;
	return;
}
void show_block(){
	for(int i=0;i<3;i++){
		for(int j=0;j<11;j++){
			if(allblock[i][j]==-1)
				cout<<"  ";
			else
				cout<<allblock[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	return;
}
bool able(int n,int x,int y){
	if(n<1||n>3||x<1||x>10||y<1||y>10){
		printf("Invalid\n");
		return false;
	}
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(block[block_now[n]][i][j]&&map[i+x][j+y]!='x')
				return false;
		}
	}
	return true;
}
bool possible(){
	for(int i=1;i<=3;i++){
		if(block_now[i]==-1)
			continue;
		for(int j=1;j<=10;j++){
			for(int k=1;k<=10;k++){
				if(able(i,j,k))
					return 1;
			}
		}
	}
	return 0;
}
void update_map(int n,int x,int y){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(block[block_now[n]][i][j])
				map[i+x][j+y]=char(block_now[n]+int('0'));
		}
	}
	return;
}
void check_delete(){
	int ans[21]={0};
	for(int i=1;i<=10;i++){
		bool s=1;
		for(int j=1;j<=10;j++){
			if(map[i][j]=='x'){
				s=0;
				break;
			}
		}
		if(s)
			ans[i]=1;
	}
	for(int i=1;i<=10;i++){
		bool s=1;
		for(int j=1;j<=10;j++){
			if(map[j][i]=='x'){
				s=0;
				break;
			}
		}
		if(s)
			ans[i]=1;
	}
	for(int k=1;k<=10;k++){
		if(ans[k]==1){
			for(int i=1;i<=10;i++)
				map[k][i]='x';
		}
	}
	for(int k=11;k<=20;k++){
		if(ans[k]==1){
			for(int i=1;i<=10;i++)
				map[i][k-10]='x';
		}
	}
	return;
}
int main(){
	system("clear");
	string in;
	printf("(s) to start\n(q) to quit\n");
	while(cin>>in){
		if(in=="q")
			return 0;
		else if(in=="s")
			break;
		else
			printf("Invalid\n");
	}
	system("clear");
	set_map();
	show_map();
	generate_block();
	show_block();
	int ed=0;
	while(ed==0){
		for(int i=1;i<=3;i++){
			if(!possible()){
				ed=1;
				break;
			}
			int bk,x,y;
			cin>>bk>>x>>y;
			if(bk==1010){
				ed=1;
				break;
			}
			while(!able(bk,x,y)){
				printf("Invalid\n");
				cin>>bk>>x>>y;
			}
			score+=each_score[block_now[bk]];
			update_map(bk,x,y);
			block_now[bk]=-1;
			for(int i=0;i<3;i++)
				for(int j=(bk-1)*4;j<=(bk-1)*4+3;j++)
					allblock[i][j]=-1;
			check_delete();
			show_map();
			show_block();
		}
		if(ed==0){
			generate_block();
			show_block();
		}
	}
	FILE *fp;
	fp=fopen("1010highscore.txt","r");
	int highscore;
	while(fscanf(fp,"%d%*c",&highscore)!=EOF){}
	if(highscore>score)
		printf("high score:%d your score:%d\n",highscore,score);
	else{
		printf("new high score!! your score:%d\n",score);
		FILE *fpr=fopen("1010highscore.txt","w");
		fprintf(fpr,"%d\n",score);
		fclose(fpr);
	}
	fclose(fp);
}