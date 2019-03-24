#include "calculator.hpp"


int main(){




    sf::RenderWindow win(sf::VideoMode(larg,alt), title);

    sf::Event event;

    Calc::Calculator calculator;

    while(win.isOpen()){

        while(win.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                win.close();
        }

        win.clear(sf::Color::White);
        calculator.update(win);
        win.display();

    }
}
