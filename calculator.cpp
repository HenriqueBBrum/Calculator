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
    isAnswer = false;

}


bool Calculator::isOperator(std::string str){
    if(str == "*" || str == "/" || str == "+" || str == "-")
        return true;

    return false;

}

bool Calculator::isNumber(std::string str){
    if(str == "0" || str == "1" || str == "2" || str == "3" ||
       str == "4" || str == "5" || str == "6" || str == "7" ||
       str == "8" || str =="9")
        return true;

    return false;

}

void Calculator::calculateResult(){
    std::string::size_type sz;
    float aux1 = std::stof(nextInformation, &sz);
    float result, result1;
    if(answer.empty()){
        answer = nextInformation;
        return;
    }else{
        result = std::stof(answer, &sz);
        result1 = result;
    }

    if(lastOperator == "+"){
        result+=aux1;
        equation+="+";
    }else if(lastOperator == "-"){
        result-=aux1;
        equation+="-";
    }else if(lastOperator == "*"){
        result1*=aux1;
        equation+="*";
    }else if(lastOperator == "/"){
        result1/=aux1;
        equation+="/";
    }else
        result = aux1;

    lastOperator = "";

    bool soHaZero = true;;
    std::string str_aux = std::to_string(result);
    std::size_t found = str_aux.find(".");

    for(int i = found+1 ;i <str_aux.size();i++){
        if(str_aux[i]!=0)
            soHaZero = false;
    }

    if(soHaZero){
        answer = std::to_string((int)result);
    }

    answer = str_aux;


}

void Calculator::showLogic(std::string inf){
    if(inf  == "C"){
        equation.erase();
        nextInformation.erase();
        answer.erase();
        isAnswer = false;
    }else if(inf  == "<-"){
        isAnswer = false;
        if(nextInformation.size()!=0)
            nextInformation.pop_back();
    }else if(inf  == "=" && !nextInformation.empty() && isOperator(lastOperator) && isAnswer == false){
        calculateResult();
        equation += nextInformation;
        nextInformation = answer;
        isAnswer = true;
    }else if(nextInformation.size()<20 && equation.size()<40){
        if(!isOperator(inf)){
            isAnswer = false;
            if(lastInformation == "=" && inf != "."){
                nextInformation.erase();
                nextInformation+=inf;
            }else if(inf  == "." &&  !nextInformation.empty()){
                if(isNumber(lastInformation))
                    nextInformation+=inf;
                else if(isOperator(lastInformation)){
                    nextInformation.erase();
                    nextInformation+="0"+inf;
                }
            }else if(isNumber(inf) && isOperator(lastInformation)){
                nextInformation.erase();
                nextInformation+=inf;
            }else if(isNumber(inf))
                nextInformation+=inf;

        }else if(isOperator(inf) && isAnswer == false){
            lastOperator = inf;
            if(isOperator(lastInformation) && !equation.empty()){
                equation.pop_back();
                equation+=inf;
            }else if(!nextInformation.empty()){
                equation+=inf;
                equation+=nextInformation;
                calculateResult();
                nextInformation = answer;
                isAnswer = true;
            }

        }

    }
    lastInformation = inf;

}

void Calculator::checkClick(sf::Event& event){
    std::string inf;
    for(auto i: buttons){
        inf = i.getInformation();
        if(i.checkMouse() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && event.type == sf::Event::MouseButtonPressed){
            showLogic(inf);
        }

    }

}
void Calculator::update(sf::RenderWindow& win, sf::Event& event){
    draw(win);



}



void Calculator::drawText(sf::RenderWindow& win, std::string str, sf::Vector2f pos,int size_, sf::Color clr){
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setPosition(pos);
    text.setFillColor(clr);
    text.setCharacterSize(size_);
    win.draw(text);
}

void Calculator::drawButtonsChar(sf::RenderWindow& win, Useful::Button button){
    sf::Vector2f pos({button.getPosition().x + 50, button.getPosition().y + 50});

    drawText(win,button.getInformation(),pos, 100,sf::Color::Black);

}

void Calculator::draw(sf::RenderWindow& win){

    sf::RectangleShape outterRect({0,0});
    outterRect.setFillColor(sf::Color::Transparent);
    outterRect.setOutlineColor(sf::Color::Black);
    outterRect.setOutlineThickness(-5);
    outterRect.setSize({larg,alt});


    for(auto i: buttons){
        i.update(win);
        drawButtonsChar(win, i);
    }

    drawText(win,equation,{0,10},50, sf::Color(128,128,128,100));

    drawText(win,nextInformation,{0,50},100, sf::Color::Black);


    win.draw(outterRect);
}
