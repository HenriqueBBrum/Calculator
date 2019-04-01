#pragma once

#include"button.hpp"
#include<vector>
#include<stack>
#include <windows.h>
#include<sstream>
#include<iomanip>


#define NUM_BUTTONS 21

const float larg = GetDeviceCaps(GetDC(NULL), HORZRES);
const float alt = GetDeviceCaps(GetDC(NULL), VERTRES);


const std::string title = "Calculator";

namespace Calc{


    class Calculator{
            std::vector<Useful::Button> buttons;

            std::vector<std::string> equation;

            std::vector<std::string> symbols;

            std::string answer;

            sf::Font font;

            void draw(sf::RenderWindow& win);

            void checkButtonType();

            void initializeSymbols();

            void drawButtonsChar(sf::RenderWindow& win, Useful::Button button);

            void drawText(sf::RenderWindow& win, std::string str, sf::Vector2f pos,int size_, sf::Color clr);

            bool isOperator(std::string str);

            bool isDigit(const std::string str);

            bool isNumber(std::string str);

            Useful::Button createButton(sf::Vector2f pos, sf::Vector2f size_, sf::Color color,sf::Color secondaryColor, std::string type);

            void calculatorLogic(std::string inf);

            void adjustNumbers();

            bool infixToPostfix();

            bool result();

            void calculateResult();

        public:

            Calculator();

            void update(sf::RenderWindow& win, sf::Event& event);

            void checkClick(sf::Event& event);

    };


}
