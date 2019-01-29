//
// Created by marcd on 29-1-2019.
//

#ifndef TOPFORCE_SCOREBOX_HPP
#define TOPFORCE_SCOREBOX_HPP
#define FONT "assets/fonts/BankGothicMediumBT.ttf"

#include "../Topforce.hpp"
#include "../abstracts/MoveableScreenObject.hpp"
#include "TopforceWindow.hpp"

namespace tf {

struct Scores {
    int score, kills, deaths;
};

class ScoreBox : public sf::RectangleShape, public tf::MoveableScreenObject {
private:
    sf::Font font;
    sf::Text text[4];
public:
    const std::string playerName;
    ScoreBox(sf::RenderWindow & window, const std::string& playerName);
    void setScore(const Scores& score);
    void draw() const override;
    void update() override;

};
}


#endif //TOPFORCE_SCOREBOX_HPP
