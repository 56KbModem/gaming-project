
#include "Character.hpp"

    namespace tf {
        Character::Character(sf::RenderWindow &window, sf::View & view, const std::vector<sf::FloatRect> & levelHitboxes):
                MoveableScreenObject(window),
                view(view),
                levelHitboxes(levelHitboxes)

        {
        if (!stationary.loadFromFile(PLAYER)) {
            TF_ERROR("Failed to load png file {}", PLAYER);
        }
        if (!reloading.loadFromFile(RELOAD)) {
            TF_ERROR("Failed to load png file {}", RELOAD);
        }
        if(!selection_buffer.loadFromFile(WEAPONG3)){
            TF_ERROR("Failed to load audio file {}", WEAPONG3);
        }
        weapon_sound.setBuffer(selection_buffer);
        mySprite.setTexture(stationary);
        mySprite.setPosition(1700.0, 375.0);
        view.setCenter(mySprite.getPosition());
        sf::FloatRect bounds = mySprite.getGlobalBounds();
        mySprite.setOrigin(bounds.width / 2, bounds.height / 2);
        hitbox.setSize({55.0f, 55.0f});
        hitbox.setFillColor(sf::Color(0,0,0,0));
#if DEBUG
        hitbox.setFillColor(sf::Color(255,0,0,100));
#endif
    }

    void Character::draw() const {
        window.draw(mySprite);
#if DEBUG
        window.draw(hitbox);
#endif
    }

    void Character::move(const sf::Vector2f & position) {
            mySprite.move(position);
            hitbox.setPosition(mySprite.getPosition().x -25, mySprite.getPosition().y - 25);
            for(auto & hitbox : levelHitboxes){
                if(hitbox.intersects(getBounds())){
                    mySprite.move(-position);
                }
            }
            view.setCenter(mySprite.getPosition());
    }

    void Character::setTexture(const std::string & texture){
        if(texture == "RELOADING"){
            mySprite.setTexture(reloading);
        }
        if(texture == "STATIONARY"){
            mySprite.setTexture(stationary);
        }
    }

    void Character::shoot(){
            if(shoot_clock.getElapsedTime().asMilliseconds() > 100){
                weapon_sound.play();
                shoot_clock.restart();
            }
    }

    void Character::lookAtMouse() {
        sf::Vector2f curPos = mySprite.getPosition();
        sf::Vector2i position = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(position);
        float dx = curPos.x - worldPos.x;
        float dy = curPos.y - worldPos.y;
        float rotation = float((atan2(dy, dx)) * 180 / PI) + 180;
        mySprite.setRotation(rotation);
    }
    sf::FloatRect Character::getBounds() {
            return hitbox.getGlobalBounds();
    }

    sf::Vector2f Character::getPosition(){
            return mySprite.getPosition();
    }
}
