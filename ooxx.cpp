#include<SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<cstdlib>
#define sfrec sf::RectangleShape
using namespace std;
int line[8][3]={{0,3,6},{1,4,7},{2,5,8},{0,1,2},{3,4,5},{6,7,8},{0,4,8},{2,4,6}};
int position[9][2]={{110,30},{210,30},{310,30},{110,130},{210,130},{310,130},{110,230},{210,230},{310,230}};
char mp[3][3];
void setmap(){
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			mp[i][j]=' ';
	return;
}
bool end(int t){
	char c=(t==0)?'o':'x';
	bool ans;
	for(int i=0;i<8;i++){
		ans=1;
		for(int j=0;j<3;j++){
			if(mp[line[i][j]/3][line[i][j]%3]!=c){
				ans=0;
				break;
			}
		}
		if(ans)
			return 1;
	}
	return 0;
}
bool full(){
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(mp[i][j]==' ')
				return 0;
	return 1;
}
string int_to_string(int k){
	string str="";
	while(k>0){
		str=char(k%10+int('0'))+str;
		k/=10;
	}
	return str;
}
void print_basic(sf::RenderWindow& win,sfrec& u,sfrec& d,sfrec& r,sfrec& l,sf::Text& a,sf::Text& b){
	win.draw(u);win.draw(d);win.draw(r);win.draw(l);
	win.draw(a);win.draw(b);
}
void print_mp(sf::RenderWindow& win,sf::Font& f){
	sf::Text X("x",f);
	sf::Text O("o",f);
	X.setFillColor(sf::Color::Red);
	X.setCharacterSize(120);
	O.setFillColor(sf::Color::Black);
	O.setCharacterSize(120);
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(mp[i][j]!=' '){
				if(mp[i][j]=='x'){
					X.setPosition(position[i*3+j][0]+20,position[i*3+j][1]+40);
					win.draw(X);
				}
				if(mp[i][j]=='o'){
					O.setPosition(position[i*3+j][0]+20,position[i*3+j][1]+40);
					win.draw(O);
				}
			}
	return;
}
int main(){
	srand(time(NULL));
	setmap();
	sf::RenderWindow window(sf::VideoMode(500,500),"OOXX Game");
	sf::Font font;
	font.loadFromFile("BebasNeue-Regular.ttf");
	sf::Text a_score("0",font);
	a_score.setFillColor(sf::Color::Black);
	a_score.setCharacterSize(40);
	sf::Text b_score("0",font);
	b_score.setFillColor(sf::Color::Red);
	b_score.setCharacterSize(40);
	b_score.setPosition(480,0);
	sfrec upline(sf::Vector2f(300,5));
	upline.setFillColor(sf::Color::White);
	upline.setPosition(100,200);
	sfrec downline(sf::Vector2f(300,5));
	downline.setFillColor(sf::Color::White);
	downline.setPosition(100,300);
	sfrec rightline(sf::Vector2f(5,300));
	rightline.setFillColor(sf::Color::White);
	rightline.setPosition(300,100);
	sfrec leftline(sf::Vector2f(5,300));
	leftline.setFillColor(sf::Color::White);
	leftline.setPosition(200,100);	
	sf::Text ch("+",font);
	ch.setFillColor(sf::Color::Yellow);
	ch.setCharacterSize(200);
	ch.setPosition(100,30);
	sf::Text a_turn("<-",font);
	sf::Text b_turn("->",font);
	a_turn.setFillColor(sf::Color::Green);
	b_turn.setFillColor(sf::Color::Green);
	a_turn.setCharacterSize(40);
	b_turn.setCharacterSize(40);
	a_turn.setPosition(50,0);
	b_turn.setPosition(430,0);
	int as=0,bs=0,turn=rand()%2,posx=0,posy=0;
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event))
			if(event.type==sf::Event::Closed)
				window.close();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			if(posy>0)
				posy--;
			while(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){}
			ch.setPosition(position[posx*3+posy][0],position[posx*3+posy][1]);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			if(posy<2)
				posy++;
			while(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){}
			ch.setPosition(position[posx*3+posy][0],position[posx*3+posy][1]);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			if(posx>0)
				posx--;
			while(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){}
			ch.setPosition(position[posx*3+posy][0],position[posx*3+posy][1]);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			if(posx<2)
				posx++;
			while(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){}
			ch.setPosition(position[posx*3+posy][0],position[posx*3+posy][1]);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
			if(mp[posx][posy]==' '){
				mp[posx][posy]=(turn==1)?'o':'x';
				if(turn)
					turn=0;
				else
					turn=1;
			}
			while(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){}
		}
		if(end(turn)){
			if(turn==1){
				bs++;
				b_score.setString(int_to_string(bs));
			}
			else{
				as++;
				a_score.setString(int_to_string(as));
			}
			setmap();
			turn=rand()%2;
		}
		else if(full()){
			setmap();
			turn=rand()%2;
		}
		window.clear(sf::Color::Blue);
		print_basic(window,upline,downline,rightline,leftline,a_score,b_score);
		if(turn)
			window.draw(a_turn);
		else
			window.draw(b_turn);
		window.draw(ch);
		print_mp(window,font);
		window.display();
	}
}