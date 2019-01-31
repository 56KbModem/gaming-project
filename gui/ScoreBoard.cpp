//
// Created by marcd on 29-1-2019.
//

#include "ScoreBoard.hpp"

namespace tf {


ScoreBoard::ScoreBoard(tf::TopforceWindow& window, sf::View& view):
    MoveableScreenObject(window),
    view(view)
{
    if(!font.loadFromFile(FONT)){
        TF_INFO("Unable to load font: {}",FONT);
    }
    for (auto & t : text){
        t.setFont(font);
        t.setCharacterSize(20);
    }
    text[0].setString("Score");
    text[1].setString("Kills");
    text[2].setString("Deaths");
}

void ScoreBoard::draw() const {
    for (const auto& t : text){
        window.draw(t);
    }
    for (const auto& rect : rectangles) {
        rect.draw();
    }
}

void ScoreBoard::update() {
    int offset = 0;
    int textOffset = 0;
    for (auto& t : text){
        t.setPosition(sf::Vector2f(view.getCenter().x + 100 + textOffset, view.getCenter().y - 300));
        textOffset += 145;
    }
    for (auto& rect : rectangles) {
        rect.setPosition(sf::Vector2f(view.getCenter().x - 480, view.getCenter().y - 270 + offset));
        offset += 45;
        rect.update();
    }
    ScoreBoard::draw();
}

void ScoreBoard::setScore(const std::string& playerName, const Scores& score) {
    // updating scoreboard.
    if (scores.find(playerName) == scores.end() ){
        scores[playerName] = Scores{0,0,0};
    }

    scores[playerName].kills += score.kills;
    scores[playerName].deaths += score.deaths;
    scores[playerName].score += score.score;
    rectangles.clear();
    int index = 0;
    for(const auto s : scores){
        rectangles.push_back(tf::ScoreBox(window,font,s.first));
        rectangles[index].setScore(s.second);
        index++;
    }
}
}