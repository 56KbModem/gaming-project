//
// Created by Nathan Hoekstra on 2019-01-02.
//

#ifndef TOPFORCE_TEST_MAIN_MENU_HPP
#define TOPFORCE_TEST_MAIN_MENU_HPP

#define SELECTED_COLOR sf::Color(206,79,70)
#define UNSELECTED_COLOR sf::Color::White

#define BACKGROUND "assets/images/MainMenuBackground.jpg"
#define FONT "assets/fonts/BankGothicMediumBT.ttf"
#define HOVER_SOUND "assets/sounds/ui_hover.wav"

#include "../topforce.hpp"

template<size_t items>
class Menu {
public:
    Menu(const sf::Vector2u & windowSize, const std::array<std::string,items> & menuItems){
        if(!backgroundTexture.loadFromFile(BACKGROUND)){
            TF_ERROR("Failed to load audio file {}", BACKGROUND);
        }
        if(!font.loadFromFile(FONT)){
            TF_ERROR("Failed to load audio file {}", FONT);
        }
        if(!selectionBuff.loadFromFile(HOVER_SOUND)){
            TF_ERROR("Failed to load audio file {}", HOVER_SOUND);
        }
        //Load and set position of background
        background.setTexture(backgroundTexture);
        background.setPosition(0,0);

        // Load selection buffer
        selectionSound.setBuffer(selectionBuff);
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
            selectionSound.play();
            textItems[selectedItemIndex].setFillColor(SELECTED_COLOR);
        }
    }
    void moveDown(){
        if(selectedItemIndex + 1 < int(items)){
            textItems[selectedItemIndex].setFillColor(UNSELECTED_COLOR);
            selectedItemIndex++;
            selectionSound.play();
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

private:
    int selectedItemIndex;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Font font;
    sf::Text textItems[items];
    sf::SoundBuffer selectionBuff;
    sf::Sound selectionSound;
};


#endif //TOPFORCE_TEST_MAIN_MENU_HPP
