//
// Created by marcd on 29-1-2019.
//

#include "ScoreBox.hpp"

namespace tf {


ScoreBox::ScoreBox(sf::RenderWindow & window, sf::Font & font, const std::string& playerName):
    MoveableScreenObject(window),
    playerName(playerName)
{
    for(auto & t : text){
        t.setFont(font);
        t.setCharacterSize(30);
        t.setString("0");
    }
    box.setFillColor(sf::Color(206,79,70, 150));
    box.setSize(sf::Vector2f(960, 35));
    text[0].setString(playerName);
}

void ScoreBox::setScore(const Scores& score) {
    text[1].setString(std::to_string(score.score));
    text[2].setString(std::to_string(score.kills));
    text[3].setString(std::to_string(score.deaths));
}

void ScoreBox::draw() const {
    window.draw(box);
    for(const auto & t : text){
        window.draw(t);
    }
}

void ScoreBox::setPosition(const sf::Vector2f & position){
    box.setPosition(position);
}

void ScoreBox::update() {
    sf::Vector2f location = box.getPosition();
    text[0].setPosition(sf::Vector2f(location.x + 10, location.y-5));
    text[1].setPosition(sf::Vector2f(location.x + 580, location.y-5));
    text[2].setPosition(sf::Vector2f(location.x + 730, location.y-5));
    text[3].setPosition(sf::Vector2f(location.x + 880, location.y-5));
}
}