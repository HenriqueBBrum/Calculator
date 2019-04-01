#include "calculator.hpp"

using namespace Calc;


void Calculator::initializeSymbols(){
    for(int i = 0;i <10;i++)
        symbols.push_back(std::to_string(i));

    symbols.push_back("+");
    symbols.push_back("-");
    symbols.push_back("*");
    symbols.push_back("/");
    symbols.push_back("^");
    symbols.push_back(".");
    symbols.push_back("(");
    symbols.push_back(")");
    symbols.push_back("=");
    symbols.push_back("<-");
    symbols.push_back("C");

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


bool Calculator::isOperator(std::string str){
    if(str == "^" || str == "*" || str == "/" || str == "+" || str == "-")
        return true;

    return false;

}

bool Calculator::isDigit(const std::string str){
    if(str == "0" || str == "1" || str == "2" || str == "3" ||
        str == "4" || str == "5" || str == "6" || str == "7" ||
          str == "8" || str == "9")
        return true;

    return false;

}

bool Calculator::isNumber(const std::string s){
    std::istringstream iss(s);
    float f;
    iss >> std::noskipws >> f;
    return iss.eof() && !iss.fail();
}

int precedence(const std::string symbol){
	if(symbol == "^")
	{
		return(3);
	}
	else if(symbol == "*" || symbol == "/")
	{
		return(2);
	}
	else if(symbol == "+" || symbol == "-")
	{
		return(1);
	}
	else
	{
		return(0);
	}
}


void Calculator::adjustNumbers(){
    std::string aux;
    bool pointUsed;
    unsigned int j = 0;
    for(unsigned int i = 0; i<equation.size();i++){
        if(isDigit(equation[i])){
            pointUsed = false;
            j = i+1;
            aux+=equation[i];
            while(j<equation.size() && (isDigit(equation[j]) || equation[j] == ".")){
                if(pointUsed ==  true && equation[j] == ".")
                    break;
                if(equation[j] == ".")
                    pointUsed = true;

                aux+=equation[j];
                equation.erase(equation.begin()+j);


            }
            equation[i] = aux;
            aux="";
        }

    }
}

bool Calculator::infixToPostfix(){
    std::vector<std::string> infix = equation;
    std::vector<std::string> postfix;
    std::stack<std::string> inToPost;
    infix.push_back(")");
    inToPost.push("(");


    for(unsigned int  i = 0; i<infix.size();i++){
        if(isNumber(infix[i])){
            postfix.push_back(infix[i]);
            std::cout<<infix[i];
        }else if(infix[i] == "("){
            inToPost.push(infix[i]);

        }else if(isOperator(infix[i])){
            std::string x = inToPost.top();
            inToPost.pop();
			while(isOperator(x) == 1 && precedence(x)>= precedence(infix[i]))
			{
				postfix.push_back(x);
				x = inToPost.top();
				inToPost.pop();
			}
			inToPost.push(x);
			inToPost.push(infix[i]);
			std::cout<<inToPost.size();

        }else if(infix[i] == ")"){
            std::string x = inToPost.top();
            inToPost.pop();
			while(x!="(")
			{
				postfix.push_back(x);
				x = inToPost.top();
				inToPost.pop();
			}
        }else{
            return false;
        }

    }

    if(inToPost.size()>0)
        return false;

    equation = postfix;

    return true;
}

std::string operation(std::string aux1, std::string aux2, std::string op){
    float num1 = std::stof(aux1);
    float num2 = std::stof(aux2);
    float result;
    if(op == "^"){
        result =  std::pow(num1,num2);
    }else if(op == "*"){
        result = num1*num2;
    }else if(op == "/"){
        result = num1/num2;
    }else if(op == "+"){
        result = num1+num2;
    }else if(op == "-"){
        result = num1-num2;
    }

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << result;

    return stream.str();
}

bool Calculator::result(){
    std::stack<std::string> resultStack;
    for(unsigned int i = 0; i<equation.size();i++){
        if(isNumber(equation[i])){
            resultStack.push(equation[i]);
        }else if(isOperator(equation[i])){
            if(resultStack.size()<=0){
                return false;
            }

            std::string aux2 = resultStack.top();
            resultStack.pop();
            if(resultStack.size()<=0){
                return false;
            }
            std::string aux1 = resultStack.top();
            resultStack.pop();
            if(isNumber(aux1) && isNumber(aux2)){

                resultStack.push(operation(aux1,aux2,equation[i]));
            }else{
                return false;
            }

        }else{
            return false;
        }

    }

    answer = resultStack.top();
    resultStack.pop();
    if(!isNumber(answer))
        return false;
    if(resultStack.size()>0)
        return false;

    return true;

}



void Calculator::calculateResult(){

    adjustNumbers();

    if(!infixToPostfix()){
        answer = "Invalid Expression";
        return;
    }

    if(!result()){
        answer = "Invalid Expression";
        return;
    }

}



void Calculator::calculatorLogic(std::string inf){
    if(inf == "C"){
        equation.erase(equation.begin(),equation.end());
        answer.erase();
    }else if(inf == "<-" && !equation.empty()){
        equation.pop_back();
    }else if(inf == "="){
        calculateResult();
        equation.erase(equation.begin(),equation.end());
    }else {
        if(inf == "<-")
            return;

        if(!equation.empty() && equation[0] == "Invalid Expression")
            equation.erase(equation.begin(),equation.end());

        equation.push_back(inf);
        answer.erase();
    }

}

void Calculator::checkClick(sf::Event& event){
    std::string inf;
    for(auto i: buttons){
        inf = i.getInformation();
        if(i.checkMouse() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && event.type == sf::Event::MouseButtonPressed){
            calculatorLogic(inf);
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

    drawText(win,answer,{0,150},150, sf::Color::Green);

    for(unsigned int i = 0; i <equation.size();i++)
        drawText(win,equation[i],{(float)i*30,0},100, sf::Color::Black);


    win.draw(outterRect);
}
