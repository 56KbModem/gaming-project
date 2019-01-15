//
// Created by crisv on 15-1-2019.
//

#ifndef TOPFORCE_CHARACTER_HPP
#define TOPFORCE_CHARACTER_HPP

#define PLAYER "assets/images/soldier1_machine.png"
#define PI 3.14159265

namespace tf{namespace character{
    class character{
    private:
        sf::Vector2f curPos;
        sf::Vector2i position;
        sf::Sprite mySprite;
        sf::Texture myTexture;
    public:
        character()
        {
            if(!myTexture.loadFromFile(PLAYER)){
                TF_ERROR("Failed to load png file {}",PLAYER);
            }
            mySprite.setTexture(myTexture);
            mySprite.setPosition(400.0, 400.0);
            sf::FloatRect bounds = mySprite.getGlobalBounds();
            mySprite.setOrigin(bounds.width / 2, bounds.height / 2);
            #if DEBUG
            TF_INFO("Character created");
            #endif
        }

        void draw(sf::RenderWindow& window) {
            lookAtMouse(window);
            window.draw(mySprite);
            #if DEBUG
            TF_INFO("Character drawn");
            #endif
        }
        void lookAtMouse(sf::RenderWindow & window){
            sf::Vector2f curPos = mySprite.getPosition();
            sf::Vector2i position = sf::Mouse::getPosition(window);
            float dx = curPos.x - position.x;
            float dy = curPos.y - position.y;
            float rotation = float((atan2(dy, dx)) * 180 / PI) + 180;
            mySprite.setRotation(rotation);
        }
    };

}}



#endif //TOPFORCE_CHARACTER_HPP
