#include"button.hpp"



using namespace Useful;





///Button FUCTIONS

void Button::update(sf::RenderWindow& win){
    draw(win);
}

void Button::draw(sf::RenderWindow& win){
    if(checkMouse())
        rect.setFillColor(changeColor);
    else
        rect.setFillColor(color);

    win.draw(rect);

}

bool Button::inside(){
    float mouseX = sf::Mouse::getPosition().x;
    float mouseY = sf::Mouse::getPosition().y;
    float objX = rect.getPosition().x;
    float objY = rect.getPosition().y;
    sf::Vector2f dim = rect.getSize();

    if((mouseX>=objX && mouseX<=objX+dim.x) && (mouseY-30>=objY && mouseY<=objY+dim.y+30))
        return true;

    return false;
}

 bool Button::checkMouse(){
    bool answer = false;
    if(inside())
        answer = true;

    return answer;
 }

Button::Button(){
    rect.setPosition({0,0});
    rect.setSize({0,0});
    rect.setFillColor(sf::Color::Black);
    information = "#";
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(5);
}

Button::Button(sf::Vector2f pos, sf::Vector2f size_, sf::Color mainColor,sf::Color secondaryColor, std::string type){
    rect.setPosition(pos);
    this->color = mainColor;
    rect.setFillColor(color);
    rect.setSize(size_);
    changeColor = secondaryColor;
    information = type;
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(5);
}



