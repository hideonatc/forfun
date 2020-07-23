#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
char cube[12][9],bkcube[12][9];
int first[7][2]={{0,0},{0,3},{3,0},{3,3},{9,3},{3,6},{6,3}};
char color[7]={'0','w','p','b','g','o','y'};
void backup(){
	for(int i=0;i<12;i++)
		for(int j=0;j<9;j++)
			bkcube[i][j]=cube[i][j];
}
void set_cube(){
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			cube[i][j]=cube[i][j+6]=cube[i+6][j]=cube[i+6][j+6]=cube[i+9][j]=cube[i+9][j+6]='0';
	for(int i=1;i<=6;i++){
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++){
				cube[first[i][0]+j][first[i][1]+k]=color[i];
			}
		}
	}
	backup();
}
void show_cube(){
	system("clear");
	for(int i=0;i<12;i++){
		for(int j=0;j<9;j++){
			if(cube[i][j]=='0')
				cout<<"   ";
			else
				cout<<cube[i][j]<<"  ";
		}
		cout<<endl;
	}
	return;
}
void rev(int s,int arg){
	if(arg==2){	
		char m[3][3];
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				m[i][j]=cube[j+first[s][0]][2-i+first[s][1]];
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				cube[i+first[s][0]][j+first[s][1]]=m[i][j];
	}
	else{
		char m[3][3];
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				m[i][j]=cube[2-j+first[s][0]][i+first[s][1]];
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				cube[i+first[s][0]][j+first[s][1]]=m[i][j];
	}
	return;
}
void move(int arg){
	if(arg==1){	//順
		rev(1,1);
		char mem[12]={cube[3][0],cube[3][1],cube[3][2],cube[3][3],cube[3][4],cube[3][5],cube[3][6],cube[3][7],cube[3][8],cube[11][5],cube[11][4],cube[11][3]};
		for(int i=0;i<3;i++){
			cube[3][i]=mem[i+3];
			cube[3][3+i]=mem[i+6];
			cube[3][6+i]=mem[i+9];
			cube[11][5-i]=mem[i];
		}
	}
	else if(arg==2){
		rev(1,2);
		char mem[12]={cube[3][0],cube[3][1],cube[3][2],cube[3][3],cube[3][4],cube[3][5],cube[3][6],cube[3][7],cube[3][8],cube[11][5],cube[11][4],cube[11][3]};
		for(int i=0;i<3;i++){
			cube[3][i]=mem[i+9];
			cube[3][i+3]=mem[i];
			cube[3][i+6]=mem[i+3];
			cube[11][5-i]=mem[i+6];
		}
	}
	else if(arg==3){
		rev(2,1);
		char mem[12]={cube[0][3],cube[1][3],cube[2][3],cube[3][3],cube[4][3],cube[5][3],cube[6][3],cube[7][3],cube[8][3],cube[9][3],cube[10][3],cube[11][3]};
		for(int i=0;i<3;i++){
			cube[i][3]=mem[i+9];
			cube[i+3][3]=mem[i];
			cube[i+6][3]=mem[i+3];
			cube[i+9][3]=mem[i+6];
		}
	}
	else if(arg==4){
		rev(2,2);
		char mem[12]={cube[0][3],cube[1][3],cube[2][3],cube[3][3],cube[4][3],cube[5][3],cube[6][3],cube[7][3],cube[8][3],cube[9][3],cube[10][3],cube[11][3]};
		for(int i=0;i<3;i++){
			cube[i][3]=mem[i+3];
			cube[i+3][3]=mem[i+6];
			cube[i+6][3]=mem[i+9];
			cube[i+9][3]=mem[i];
		}
	}
	else if(arg==5){
		rev(3,1);
		char mem[12]={cube[2][5],cube[2][4],cube[2][3],cube[3][2],cube[4][2],cube[5][2],cube[6][3],cube[6][4],cube[6][5],cube[5][6],cube[4][6],cube[3][6]};
		for(int i=0;i<3;i++){
			cube[2][i+3]=mem[5-i];
			cube[i+3][2]=mem[i+6];
			cube[6][3+i]=mem[9+i];
			cube[5-i][6]=mem[i];
		}
	}
	else if(arg==6){
		rev(3,2);
		char mem[12]={cube[2][5],cube[2][4],cube[2][3],cube[3][2],cube[4][2],cube[5][2],cube[6][3],cube[6][4],cube[6][5],cube[5][6],cube[4][6],cube[3][6]};
		for(int i=0;i<3;i++){
			cube[2][i+3]=mem[11-i];
			cube[i+3][2]=mem[i];
			cube[6][3+i]=mem[i+3];
			cube[5-i][6]=mem[i+6];
		}
	}
	else if(arg==7){
		rev(4,1);
		char mem[12]={cube[8][3],cube[8][4],cube[8][5],cube[5][8],cube[4][8],cube[3][8],cube[0][5],cube[0][4],cube[0][3],cube[3][0],cube[4][0],cube[5][0]};
		for(int i=0;i<3;i++){
			cube[8][i+3]=mem[i+9];
			cube[5-i][8]=mem[i];
			cube[0][5-i]=mem[i+3];
			cube[3+i][0]=mem[i+6];
		}
	}
	else if(arg==8){
		rev(4,2);
		char mem[12]={cube[8][3],cube[8][4],cube[8][5],cube[5][8],cube[4][8],cube[3][8],cube[0][5],cube[0][4],cube[0][3],cube[3][0],cube[4][0],cube[5][0]};
		for(int i=0;i<3;i++){
			cube[8][i+3]=mem[i+3];
			cube[5-i][8]=mem[i+6];
			cube[0][5-i]=mem[i+9];
			cube[3+i][0]=mem[i];
		}
	}
	else if(arg==9){
		rev(5,1);
		char mem[12]={cube[0][5],cube[1][5],cube[2][5],cube[3][5],cube[4][5],cube[5][5],cube[6][5],cube[7][5],cube[8][5],cube[9][5],cube[10][5],cube[11][5]};
		for(int i=0;i<3;i++){
			cube[i][5]=mem[i+3];
			cube[i+3][5]=mem[i+6];
			cube[i+6][5]=mem[i+9];
			cube[i+9][5]=mem[i];
		}
	}
	else if(arg==10){
		rev(5,2);
		char mem[12]={cube[0][5],cube[1][5],cube[2][5],cube[3][5],cube[4][5],cube[5][5],cube[6][5],cube[7][5],cube[8][5],cube[9][5],cube[10][5],cube[11][5]};
		for(int i=0;i<3;i++){
			cube[i][5]=mem[i+9];
			cube[i+3][5]=mem[i];
			cube[i+6][5]=mem[i+3];
			cube[i+9][5]=mem[i+6];
		}
	}
	else if(arg==11){
		rev(6,1);
		char mem[12]={cube[5][0],cube[5][1],cube[5][2],cube[5][3],cube[5][4],cube[5][5],cube[5][6],cube[5][7],cube[5][8],cube[9][5],cube[9][4],cube[9][3]};
		for(int i=0;i<3;i++){
			cube[5][i]=mem[i+9];
			cube[5][i+3]=mem[i];
			cube[5][i+6]=mem[i+3];
			cube[9][5-i]=mem[i+6];
		}
	}
	else if(arg==12){
		rev(6,2);
		char mem[12]={cube[5][0],cube[5][1],cube[5][2],cube[5][3],cube[5][4],cube[5][5],cube[5][6],cube[5][7],cube[5][8],cube[9][5],cube[9][4],cube[9][3]};
		for(int i=0;i<3;i++){
			cube[5][i]=mem[i+3];
			cube[5][i+3]=mem[i+6];
			cube[5][i+6]=mem[i+9];
			cube[9][5-i]=mem[i];
		}
	}
	else if(arg==13){
		char mem[12]={cube[4][0],cube[4][1],cube[4][2],cube[4][3],cube[4][4],cube[4][5],cube[4][6],cube[4][7],cube[4][8],cube[10][5],cube[10][4],cube[10][3]};
		for(int i=0;i<3;i++){
			cube[4][i]=mem[i+3];
			cube[4][i+3]=mem[i+6];
			cube[4][i+6]=mem[i+9];
			cube[10][5-i]=mem[i];
		}
	}
	else if(arg==14){
		char mem[12]={cube[4][0],cube[4][1],cube[4][2],cube[4][3],cube[4][4],cube[4][5],cube[4][6],cube[4][7],cube[4][8],cube[10][5],cube[10][4],cube[10][3]};
		for(int i=0;i<3;i++){
			cube[4][i]=mem[i+9];
			cube[4][i+3]=mem[i];
			cube[4][i+6]=mem[i+3];
			cube[10][5-i]=mem[i+6];
		}
	}
	else if(arg==15){
		char mem[12]={cube[0][4],cube[1][4],cube[2][4],cube[3][4],cube[4][4],cube[5][4],cube[6][4],cube[7][4],cube[8][4],cube[9][4],cube[10][4],cube[11][4]};
		for(int i=0;i<3;i++){
			cube[i][4]=mem[i+9];
			cube[i+3][4]=mem[i];
			cube[i+6][4]=mem[i+3];
			cube[i+9][4]=mem[i+6];
		}
	}
	else if(arg==16){
		char mem[12]={cube[0][4],cube[1][4],cube[2][4],cube[3][4],cube[4][4],cube[5][4],cube[6][4],cube[7][4],cube[8][4],cube[9][4],cube[10][4],cube[11][4]};
		for(int i=0;i<3;i++){
			cube[i][4]=mem[i+3];
			cube[i+3][4]=mem[i+6];
			cube[i+6][4]=mem[i+9];
			cube[i+9][4]=mem[i];
		}
	}
	else if(arg==17){
		char mem[12]={cube[1][5],cube[1][4],cube[1][3],cube[3][1],cube[4][1],cube[5][1],cube[7][3],cube[7][4],cube[7][5],cube[5][7],cube[4][7],cube[3][7]};
		for(int i=0;i<3;i++){
			cube[1][5-i]=mem[i+3];
			cube[i+3][1]=mem[i+6];
			cube[7][3+i]=mem[i+9];
			cube[5-i][7]=mem[i];
		}
	}
	else if(arg==18){
		char mem[12]={cube[1][5],cube[1][4],cube[1][3],cube[3][1],cube[4][1],cube[5][1],cube[7][3],cube[7][4],cube[7][5],cube[5][7],cube[4][7],cube[3][7]};
		for(int i=0;i<3;i++){
			cube[1][5-i]=mem[i+9];
			cube[i+3][1]=mem[i];
			cube[7][3+i]=mem[i+3];
			cube[5-i][7]=mem[i+6];
		}
	}
	else
		printf("Invalid\n");
}
void mess(){
	srand(time(NULL));
	for(int i=1;i<=10;i++){
		move((rand()%18)+1);
	}
	return;
}
bool solve(){
	for(int i=0;i<12;i++)
		for(int j=0;j<9;j++)
			if(cube[i][j]!=bkcube[i][j])
				return 0;
	return 1;
}
void input(){
	for(int i=1;i<=6;i++){
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++){
				cin>>cube[j+first[i][0]][k+first[i][1]];
			}
		}
	}
	return;
}
int main(){
	system("clear");
	char c;
	printf("solve mode (s)\nsimulate mode (m)\nnormal mode (n)\n");
	cin>>c;
	set_cube();
	system("clear");
	if(c=='s')
		mess();
	else if(c=='m')
		input();
	else{
		int k;
		show_cube();
		while(1){
			cin>>k;
			move(k);
			show_cube();
		}
	}
	int k;
	show_cube();
	while(!solve()){
		cin>>k;
		move(k);
		show_cube();
	}
	system("clear");
	printf("you solved it!\n");
}
/*else if(arg==){
		rev(,);
		int mem[12]={cube[][],cube[][],cube[][],cube[][],cube[][],cube[][],cube[][],cube[][],cube[][],cube[][],cube[][],cube[][]};
		for(int i=0;i<3;i++){
			cube[][]=mem[];
			cube[][]=mem[];
			cube[][]=mem[];
			cube[][]=mem[];
		}
}*/