//
// Created by Nathan Hoekstra on 23/11/2018.
//

#ifndef WEEK02_ACTION_HPP
#define WEEK02_ACTION_HPP

#include <functional>
#include <SFML/Graphics.hpp>

class Action {
private:
    std::function< bool() > condition;
    std::function< void() > work;
public:
    Action(std::function<bool()> condition, std::function<void()> work):
        condition(condition),
        work(work)
    {}

    Action(sf::Keyboard::Key key, std::function<void()> work):
            condition([ key ]()->bool { return sf::Keyboard::isKeyPressed( key ); }),
            work(work)
    {}

    Action(sf::Mouse::Button button, std::function<void()> work):
            condition([ button ]()->bool { return sf::Mouse::isButtonPressed( button ); }),
            work(work)
    {}

    Action(std::function<void()> work, std::function<bool()> condition = nullptr):
        condition(condition),
        work(work)
    {}
        
    void operator()(){
        if (condition == nullptr || condition()) {
            work();
        }
    }
};
#endif //WEEK02_ACTION_HPP
