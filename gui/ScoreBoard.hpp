//
// Created by marcd on 29-1-2019.
//

#ifndef TOPFORCE_SCOREBOARD_HPP
#define TOPFORCE_SCOREBOARD_HPP

#define FONT "assets/fonts/BankGothicMediumBT.ttf"

#include "../Topforce.hpp"
#include "../abstracts/MoveableScreenObject.hpp"
#include "TopforceWindow.hpp"
#include "ScoreBox.hpp"

namespace tf {
class ScoreBoard : public tf::MoveableScreenObject {
    std::vector<tf::ScoreBox> rectangles;
    sf::View& view;
    std::map<std::string, Scores> scores;
    sf::Font font;
    sf::Text text[3];
    void draw() const override;
public:
    ScoreBoard(tf::TopforceWindow& window, sf::View& view);
    void update() override;
    void setScore(const std::string& playerName, const Scores& score);
};
}

#endif //TOPFORCE_SCOREBOARD_HPP
