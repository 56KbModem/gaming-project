
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
        mySprite.setTexture(stationary);
        mySprite.setPosition(400.0, 400.0);
        sf::FloatRect bounds = mySprite.getGlobalBounds();
        mySprite.setOrigin(bounds.width / 2, bounds.height / 2);
#if DEBUG
        TF_INFO("Character created");
#endif
    }

    void character::draw() const {
        window.draw(mySprite);
    }

    void character::setTexture(const std::string & texture){
        if(texture == "RELOADING"){
#if DEBUG
            TF_INFO("texture = reloading.");
#endif
            mySprite.setTexture(reloading);
        }
        if(texture == "STATIONARY"){
#if DEBUG
            TF_INFO("texture = stationary.");
#endif
            mySprite.setTexture(stationary);
        }
    }

    void character::move(const sf::Vector2f & position) {
        mySprite.move(position);
        view.setCenter(mySprite.getPosition());
    }

    sf::Vector2f character::getPosition(){
        return mySprite.getPosition();
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
}