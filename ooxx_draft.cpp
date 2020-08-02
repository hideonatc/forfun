#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int a_score=0,b_score=0;
int line[8][3]={{0,3,6},{1,4,7},{2,5,8},{0,1,2},{3,4,5},{6,7,8},{0,4,8},{2,4,6}};
char map[3][3];
void setmap(){
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			map[i][j]=' ';
	return;
}
void print_window(){
	system("clear");
	printf("%dvs%d\n\n",a_score,b_score);
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++)
			cout<<map[i][j];
		cout<<endl;
	}
	return;
}
bool end(int t){
	char c=(t==0)?'o':'x';
	bool ans;
	for(int i=0;i<8;i++){
		ans=1;
		for(int j=0;j<3;j++){
			if(map[line[i][j]/3][line[i][j]%3]!=c){
				ans=0;
				break;
			}
		}
		if(ans)
			return 1;
	}
}
bool full(){
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(map[i][j]==' ')
				return 0;
	return 1;
}
int main(){
	srand(time(NULL));
	int turn=0,x,y;
	while(a_score<2&&b_score<2){
		setmap();
		print_window();
		turn=rand()%2;
		while(!end(turn)){
			if(full())
				break;
			cin>>x>>y;
			if(turn==0){
				map[x][y]='x';
				turn=1;
			}
			else{
				map[x][y]='o';
				turn=0;
			}
			print_window();
		}
		if(!full()&&turn==0)
			b_score++;
		else if(!full()&&turn==1)
			a_score++;
	}
}