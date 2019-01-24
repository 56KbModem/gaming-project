//
// Created by Nathan Hoekstra on 2019-01-02.
//

#ifndef TOPFORCE_TEST_MAIN_MENU_HPP
#define TOPFORCE_TEST_MAIN_MENU_HPP

#define SELECTED_COLOR sf::Color(206,79,70)
#define UNSELECTED_COLOR sf::Color::White

#define FONT "assets/fonts/BankGothicMediumBT.ttf"

#include "../Topforce.hpp"

template<size_t items>
class Menu {
private:
    int selectedItemIndex;
    sf::Sprite background;
    sf::Font font;
    sf::Text textItems[items];
    tf::SoundManager & soundManager = tf::SoundManager::getInstance();
    tf::ImageManager & imageManager = tf::ImageManager::getInstance();
public:
    Menu(const sf::Vector2u & windowSize, const std::array<std::string,items> & menuItems){
        if(!font.loadFromFile(FONT)){
            TF_ERROR("Failed to load audio file {}", FONT);
        }
        //Load and set position of background
        background.setTexture(imageManager.getMenuBackground());
        background.setPosition(0,0);

        // Keep track on wich index we are
        int index = 0;
        // Set parameters to every MainMenu item
        for(auto & item : textItems){
            item.setFont(font);
            item.setCharacterSize(80);
            item.setFillColor(UNSELECTED_COLOR);
            item.setString(menuItems[index]);
            item.setPosition(sf::Vector2f(windowSize.x / 20, windowSize.y / (items + 1) * (index + 1)));
            index++; //Set index one position higher
        }
        // Set first MainMenu item to be selected first (Different colour)
        textItems[0].setFillColor(SELECTED_COLOR);
        // Set selected item to the first one
        selectedItemIndex = 0;
    }
    void draw(sf::RenderWindow & window){
        window.draw(background);
        for(const auto & item : textItems){
            window.draw(item);
        }
    }
    void moveUp(){
        if(selectedItemIndex - 1 >= 0){
            textItems[selectedItemIndex].setFillColor(UNSELECTED_COLOR);
            selectedItemIndex--;
            soundManager.play(tf::Sounds::UIHover);
            textItems[selectedItemIndex].setFillColor(SELECTED_COLOR);
        }
    }
    void moveDown(){
        if(selectedItemIndex + 1 < int(items)){
            textItems[selectedItemIndex].setFillColor(UNSELECTED_COLOR);
            selectedItemIndex++;
            soundManager.play(tf::Sounds::UIHover);
            textItems[selectedItemIndex].setFillColor(SELECTED_COLOR);
        }
    }
    int getPressedItem(){
        return selectedItemIndex;
    }
    void reset(){
        textItems[selectedItemIndex].setFillColor(UNSELECTED_COLOR);
        selectedItemIndex = 0;
        textItems[0].setFillColor(SELECTED_COLOR);
    }
};


#endif //TOPFORCE_TEST_MAIN_MENU_HPP
