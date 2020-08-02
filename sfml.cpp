#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600),"My window",sf::Style::Default);
    sf::Font font;
    font.loadFromFile("BebasNeue-Regular.ttf");
    sf::Text text;
    text.setString("Hello");
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(350,350);
    while(window.isOpen()){
    	sf::Event event;
    	while(window.pollEvent(event))
    		if(event.type==sf::Event::Closed)
    			window.close();
    	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
    		if(text.getPosition().x>0)
    			text.move(-0.5,0);
    		text.setString("Noice");
    	}
    	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
    		if(text.getPosition().x<600)
    			text.move(0.5,0);
    		text.setString("Cool Cool Cool");
    	}
    	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
    		if(text.getPosition().y<500)
    			text.move(0,0.5);
    		text.setString("Title of your sex tape");
    	}
    	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
    		if(text.getPosition().y>0)
    			text.move(0,-0.5);
    		text.setString("B99");
    	}
    	window.clear(sf::Color::Green);
    	window.draw(text);
    	window.display();
    }
    return 0;
}