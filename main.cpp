#include "calculator.hpp"


int main(){




    sf::RenderWindow win(sf::VideoMode(larg,alt), title);

    sf::Event event;

    Calc::Calculator calculator;

    while(win.isOpen()){

        while(win.pollEvent(event)){

            if(event.type == sf::Event::Closed)
                win.close();

            calculator.checkClick(event);
        }

        win.clear(sf::Color::White);
        calculator.update(win, event);
        win.display();

    }
}
