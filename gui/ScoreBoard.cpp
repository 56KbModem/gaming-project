//
// Created by marcd on 29-1-2019.
//

#include "ScoreBoard.hpp"

namespace tf {


ScoreBoard::ScoreBoard(tf::TopforceWindow& window, sf::View& view):
    MoveableScreenObject(window),
    view(view)
{
    rectangles.push_back(tf::ScoreBox(window, "kaas"));
}

void ScoreBoard::draw() const {
    for (const auto& rect : rectangles) {
        rect.draw();
    }
}

void ScoreBoard::update() {
    int offset = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
        for (auto& rect : rectangles) {
            rect.setPosition(view.getCenter().x - 480, view.getCenter().y - 270 + offset);
            offset += 35;
            rect.update();
        }
        ScoreBoard::draw();
    }
}

void ScoreBoard::setScore(const std::string& playerName, const Scores& score) {
    scores[playerName] = score;
    int index = 0;
    if (rectangles.size() == 0) {
        rectangles.push_back(tf::ScoreBox(window, playerName));
        return;
    }
    for (auto& s : scores) {
        if (rectangles[index].playerName != s.first) {
            rectangles.push_back(tf::ScoreBox(window, s.first));
            rectangles[index].setScore(s.second);
        }
        else {
            rectangles[index].setScore(s.second);
        }
        index++;
    }
}
}