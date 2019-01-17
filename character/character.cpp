
#include "character.hpp"

    namespace tf {
        character::character(sf::RenderWindow &window, sf::View & view):
                moveable_screen_object(window),
                view(view)
        {
        if (!stationary.loadFromFile(PLAYER)) {
            TF_ERROR("Failed to load png file {}", PLAYER);
        }
        if (!reloading.loadFromFile(RELOAD)) {
            TF_ERROR("Failed to load png file {}", RELOAD);
        }
        if(!selection_buffer.loadFromFile(WEAPONG3)){
            TF_ERROR("Failed to load audio file {}",WEAPONG3);
        }
        weapon_sound.setBuffer(selection_buffer);
        mySprite.setTexture(stationary);
        mySprite.setPosition(400.0, 400.0);
        sf::FloatRect bounds = mySprite.getGlobalBounds();
        mySprite.setOrigin(bounds.width / 2, bounds.height / 2);
    }

    void character::draw() const {
        window.draw(mySprite);
    }

    void character::move(const sf::Vector2f & position) {
        mySprite.move(position);
        view.setCenter(mySprite.getPosition());
    }

    void character::setTexture(const std::string & texture){
        if(texture == "RELOADING"){
            mySprite.setTexture(reloading);
        }
        if(texture == "STATIONARY"){
            mySprite.setTexture(stationary);
        }
    }

    void character::shoot(){
            if(shoot_clock.getElapsedTime().asMilliseconds() > 100){
                weapon_sound.play();
                shoot_clock.restart();
            }
    }

    void character::lookAtMouse() {
        sf::Vector2f curPos = mySprite.getPosition();
        sf::Vector2i position = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(position);
        float dx = curPos.x - worldPos.x;
        float dy = curPos.y - worldPos.y;
        float rotation = float((atan2(dy, dx)) * 180 / PI) + 180;
        mySprite.setRotation(rotation);
    }
    sf::FloatRect character::get_bounds() {
        return mySprite.getGlobalBounds();
    }

    sf::Vector2f character::getPosition(){
            return mySprite.getPosition();
    }
}
