#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;
string int_to_string(int k){
	string str="";
	while(k>0){
		str=char(k%10+int('0'))+str;
		k/=10;
	}
	return str;
}
int main(){
	sf::RenderWindow window(sf::VideoMode(500,500),"OOXX Game");
	sf::Font font;
	font.loadFromFile("BebasNeue-Regular.ttf");
	int s=0;
	sf::Text score;
	score.setFont(font);
	score.setString(char(s+int('0')));
	score.setCharacterSize(40);
    score.setFillColor(sf::Color::Red);
	sf::Text hint("press up",font);
	hint.setCharacterSize(40);
    hint.setFillColor(sf::Color::Green);
    hint.setPosition(100,100);
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event))
			if(event.type==sf::Event::Closed)
				window.close();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			s++;
			score.setString(int_to_string(s));
			while(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){}
		}
		window.clear(sf::Color::Blue);
		window.draw(hint);
		window.draw(score);
		window.display();
	}
}