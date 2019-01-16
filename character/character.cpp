
#include "character.hpp"

namespace tf {
    character::character(sf::RenderWindow &window):
    moveable_screen_object(window)
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

    void character::move(sf::View &view) {
        auto currentPosition = mySprite.getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            mySprite.setTexture(reloading);
            mySprite.move(0.0f, -5.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            mySprite.setTexture(reloading);
            mySprite.move(-5.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            mySprite.setTexture(reloading);
            mySprite.move(5.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            mySprite.setTexture(reloading);
            mySprite.move(0.0f, 5.0f);
        }
        if (currentPosition == mySprite.getPosition()) {
            mySprite.setTexture(stationary);
        }
        view.setCenter(mySprite.getPosition());
        lookAtMouse(view);
    }

    void character::lookAtMouse(sf::View &view) {
        sf::Vector2f curPos = mySprite.getPosition();
        sf::Vector2i position = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(position);
        float dx = curPos.x - worldPos.x;
        float dy = curPos.y - worldPos.y;
        float rotation = float((atan2(dy, dx)) * 180 / PI) + 180;
        mySprite.setRotation(rotation);
    }

    sf::Vector2f character::get_position() {
        return mySprite.getPosition();
    }
}