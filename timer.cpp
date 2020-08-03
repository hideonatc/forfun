#include<iostream>
#include<SFML/Graphics.hpp>
#define mousepos sf::Mouse::getPosition()
using namespace std;
string int_to_str(int k){
	string str="";
	while(k>0){
		str=char(k%10+int('0'))+str;
		k/=10;
	}
	return str;
}
int main(){
	sf::Font font;
	font.loadFromFile("BebasNeue-Regular.ttf");
	sf::RenderWindow window(sf::VideoMode(1000,1000),"my window");
	sf::Clock clock;
	sf::Time start;
	sf::Text sec;
	sec.setString("0");
	sec.setFont(font);
	sec.setFillColor(sf::Color::Red);
	sec.setCharacterSize(40);
	sf::RectangleShape button(sf::Vector2f(200,70));
	button.setFillColor(sf::Color(100,100,100,255));
	button.setPosition(370,500);
	sf::Text hint("PRESS TO START",font);
	hint.setFillColor(sf::Color::White);
	hint.setCharacterSize(40);
	hint.setPosition(370,500);
	while(1){
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&mousepos.x>=830&&mousepos.x<=1030&&mousepos.y>=570&&mousepos.y<=635){
			//printf("x:%d y:%d\n",mousepos.x,mousepos.y);
			break;
			while(sf::Mouse::isButtonPressed(sf::Mouse::Left)){}
		}
		window.clear(sf::Color::Black);
		window.draw(sec);
		window.draw(button);
		window.draw(hint);
		window.display();
	}
	start=clock.getElapsedTime();
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type==sf::Event::Closed)
				window.close();
		}
		sf::Time now=clock.getElapsedTime();
		int sc=now.asSeconds()-start.asSeconds();
		sec.setString(int_to_str(sc));
		window.clear(sf::Color::Black);
		window.draw(sec);
		window.draw(button);
		window.draw(hint);
		window.display();
	}
}