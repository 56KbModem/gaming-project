//
// Created by marcd on 29-1-2019.
//

#include "ScoreBox.hpp"

namespace tf {


ScoreBox::ScoreBox(sf::RenderWindow & window, const std::string& playerName):
    MoveableScreenObject(window),
    playerName(playerName)
{
    if (!font.loadFromFile(FONT)) {
        TF_ERROR("Failed to load from file");
    }
    for (auto& t : text) {
        t.setFont(font);
        t.setCharacterSize(30);
        t.setString("0");
    }

    sf::RectangleShape::setFillColor(sf::Color(206,79,70, 150));
    sf::RectangleShape::setSize(sf::Vector2f(960, 25));
    text[0].setString(playerName);
}

void ScoreBox::setScore(const Scores& score) {
    text[1].setString(std::to_string(score.score));
    text[2].setString(std::to_string(score.kills));
    text[3].setString(std::to_string(score.deaths));
}

void ScoreBox::draw() const {
    window.draw(*this);

}

void ScoreBox::update() {
    sf::Vector2f location = sf::RectangleShape::getPosition();
    text[0].setPosition(sf::Vector2f(location.x, location.y));
    text[1].setPosition(sf::Vector2f(location.x + 150, location.y));
    text[2].setPosition(sf::Vector2f(location.x + 200, location.y));
    text[3].setPosition(sf::Vector2f(location.x + 250, location.y));
}
}