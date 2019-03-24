#include "calculator.hpp"

using namespace Calc;


void Calculator::initializeSymbols(){
    for(int i = 0;i <10;i++)
        symbols.push_back(std::to_string(i));

    symbols.push_back("+");
    symbols.push_back("-");
    symbols.push_back("*");
    symbols.push_back("/");
    symbols.push_back(".");
    symbols.push_back("=");
    symbols.push_back("C");
    symbols.push_back("<-");

}

Calculator::Calculator(){
    if(!font.loadFromFile("Font.ttf"))
        std::abort();

    initializeSymbols();
    sf::Vector2f size_ = {(larg)/(NUM_BUTTONS/3),(alt)/(NUM_BUTTONS/4)};
    float y = alt;
    float x = 0;
    for(int i = 0; i<10 ;i++){
        x = x+size_.x;
        if(i % (int)(NUM_BUTTONS/3) == 0){
            x = 0;
            y = y-size_.y;
        }
         Useful::Button aux({x,y}, size_, sf::Color(77,136,255,150), sf::Color(128,128,128,100), symbols[i]);
        buttons.push_back(aux);


    }

    for(int i = 10; i<NUM_BUTTONS;i++){
        x = x+size_.x;
        if(i % (int)(NUM_BUTTONS/3) == 0){
            x = 0;
            y = y-size_.y;
        }
        Useful::Button aux({x,y}, size_, sf::Color(255,195,77,150), sf::Color(128,128,128,100), symbols[i]);
        buttons.push_back(aux);

    }

}

void Calculator::update(sf::RenderWindow& win){
    draw(win);


}

void Calculator::drawText(sf::RenderWindow& win, Useful::Button button){
    sf::Text text;
    text.setFont(font);
    text.setString(button.getInformation());
    text.setPosition({button.getPosition().x + 50, button.getPosition().y + 50});
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(100);
    win.draw(text);

}

void Calculator::draw(sf::RenderWindow& win){
    sf::RectangleShape outterRect({0,0});
    outterRect.setFillColor(sf::Color::Transparent);
    outterRect.setOutlineColor(sf::Color::Black);
    outterRect.setOutlineThickness(-5);
    outterRect.setSize({larg,alt});


    for(auto i: buttons){
        i.update(win);
        drawText(win, i);
    }

    win.draw(outterRect);
}
