#pragma once

#include"button.hpp"
#include<vector>
#include<stack>
#include <windows.h>


#define NUM_BUTTONS 18

const float larg = GetDeviceCaps(GetDC(NULL), HORZRES);
const float alt = GetDeviceCaps(GetDC(NULL), VERTRES);


const std::string title = "Calculator";

namespace Calc{


    class Calculator{
            std::vector<Useful::Button> buttons;

            std::stack<std::string> infixToPostfix;

            std::stack<std::string> parsePostfix;

            std::vector<std::string> symbols;

            sf::Font font;

            void draw(sf::RenderWindow& win);

            void checkButtonType();

            void initializeSymbols();

            void drawText(sf::RenderWindow& win, Useful::Button button);

            Useful::Button createButton(sf::Vector2f pos, sf::Vector2f size_, sf::Color color,sf::Color secondaryColor, std::string type);

        public:

            Calculator();

            void update(sf::RenderWindow& win);

    };


}
