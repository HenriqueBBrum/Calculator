#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include<string>

namespace Useful{

    inline float pointDistance(sf::Vector2f p1, sf::Vector2f p2){
        return(std::sqrt(std::pow(p1.x-p2.x,2)+std::pow(p1.y-p2.y,2)));
    }

    class Button{
            sf::RectangleShape rect;

            sf::Color color;

            sf::Color changeColor;

            std::string information;

            void draw(sf::RenderWindow& win);

            bool inside() ;

        public:
            Button();

            Button(sf::Vector2f pos, sf::Vector2f size_, sf::Color color,sf::Color secondaryColor, std::string type);

            void update(sf::RenderWindow& win);

            bool checkMouse() ;

            inline sf::Vector2f getSize(){return rect.getSize();};

            inline void setSize(sf::Vector2f size_){ rect.setSize(size_); }

            inline void setPosition(sf::Vector2f pos){rect.setPosition(pos);}

            inline sf::Vector2f getPosition(){ return rect.getPosition();}

            inline std::string getInformation(){return information; }


    };

}

