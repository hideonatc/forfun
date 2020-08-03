#include<iostream>
#include<SFML/Graphics.hpp>
#include<ctime>
using namespace std;
struct tm* ptm;
struct mytime{int hours,minutes,seconds;};
int num_pos[12][2]={{350,42},{424,119},{470,230},{423,341},{343,415},{240,457},{124,415},{34,338},{10,230},{28,119},{110,34},{233,7}};
string int_to_str(int k){
	string str="";
	while(k>0){
		str=char(k%10+int('0'))+str;
		k/=10;
	}
	return str;
}
mytime gettime(){
	time_t rawtime;
	time(&rawtime);
	ptm=gmtime(&rawtime);
	mytime mt;
	mt.hours=(ptm->tm_hour+8)%12;
	mt.minutes=(ptm->tm_min);
	mt.seconds=(ptm->tm_sec);
	return mt;
}
void print_num(sf::RenderWindow& win,sf::Font& f){
	sf::Text num;
	num.setFont(f);
	num.setFillColor(sf::Color::Red);
	num.setCharacterSize(40);
	for(int i=1;i<=12;i++){
		num.setString(int_to_str(i));
		num.setPosition(num_pos[i-1][0],num_pos[i-1][1]);
		win.draw(num);
	}
	return;
}
void change_color(sf::RenderWindow& win,sf::CircleShape& cir,int secd,int minu,int hour){
	cir.setFillColor(sf::Color(int(float(secd*255/60)),int(float(minu*255/60)),int(hour*255/12),255));
	win.draw(cir);
	return;
}
void test_pos(){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		printf("x:%d y:%d\n",sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);
		while(sf::Mouse::isButtonPressed(sf::Mouse::Left)){}
	}
	return;
}
int main(){
	sf::RenderWindow window(sf::VideoMode(500,500),"Clock");
	sf::CircleShape circle(250);
	sf::Font font;
	font.loadFromFile("BebasNeue-Regular.ttf");
	sf::Text dot(".",font);
	dot.setFillColor(sf::Color::Red);
	dot.setPosition(235,95);
	dot.setCharacterSize(170);
	mytime getit=gettime();
	sf::RectangleShape sec(sf::Vector2f(3,-220)),min(sf::Vector2f(5,-190)),hr(sf::Vector2f(7,-170));
	hr.setPosition(248,250);
	hr.setFillColor(sf::Color::Blue);
	hr.setRotation((float(getit.minutes)/2+getit.hours*30));
	min.setPosition(249,250);
	min.setFillColor(sf::Color::Black);
	min.setRotation(getit.minutes*6);
	sec.setPosition(250,250);
	sec.setRotation(getit.seconds*6);
	circle.setFillColor(sf::Color::Green);
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event))
			if(event.type==sf::Event::Closed)
				window.close();
		//test_pos();
		time_t rawtime;
		time(&rawtime);
		ptm=gmtime(&rawtime);
		sec.setRotation(ptm->tm_sec*6);
		min.setRotation(ptm->tm_min*6);
		hr.setRotation((float(ptm->tm_min)/2+((ptm->tm_hour+8)%12)*30));
		window.clear(sf::Color::Black);
		//window.draw(circle);
		change_color(window,circle,ptm->tm_sec,ptm->tm_min,(ptm->tm_hour+8)%12);
		window.draw(sec);
		window.draw(min);
		window.draw(hr);
		window.draw(dot);
		print_num(window,font);
		window.display();
	}
}