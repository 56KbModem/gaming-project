//
// Created by Nathan Hoekstra on 2019-01-02.
//

#ifndef TOPFORCE_TEST_MAIN_MENU_HPP
#define TOPFORCE_TEST_MAIN_MENU_HPP

#include "../topforce.hpp"

template<size_t items>
class menu {
public:
    menu(const sf::Vector2u & window_size, const std::array<std::string,items> & menu_items){
        if(!background_texture.loadFromFile("assets/images/MainMenuBackground.jpg")){
            spdlog::get("stderr")->error("Failed to load audio file \"images/MainMenuBackground.jpg\"");
        }
        if(!font.loadFromFile("assets/fonts/BankGothicMediumBT.ttf")){
            spdlog::get("stderr")->error("Failed to load audio file \"BankGothicMediumBT.ttf\"");
        }
        if(!selection_buff.loadFromFile("assets/sounds/ui_hover.wav")){
            spdlog::get("stderr")->error("Failed to load audio file \"sounds/ui_hover.wav\"");
        }
        //Load and set position of background
        background.setTexture(background_texture);
        background.setPosition(0,0);

        // Load selection buffer
        selection_sound.setBuffer(selection_buff);
        // Keep track on wich index we are
        int index = 0;
        // Set parameters to every main_menu item
        for(auto & item : text_items){
            item.setFont(font);
            item.setCharacterSize(80);
            item.setFillColor(sf::Color::White);
            item.setString(menu_items[index]);
            item.setPosition(sf::Vector2f(window_size.x / 20, window_size.y / (items + 1) * (index + 1)));
            index++; //Set index one position higher
        }
        // Set first main_menu item to be selected first (Different colour)
        text_items[0].setFillColor(sf::Color::Green);
        // Set selected item to the first one
        selected_item_index = 0;
    }
    void draw(sf::RenderWindow & window){
        window.draw(background);
        for(const auto & item : text_items){
            window.draw(item);
        }
    };
    void move_up(){
        if(selected_item_index - 1 >= 0){
            text_items[selected_item_index].setFillColor(sf::Color::White);
            selected_item_index--;
            selection_sound.play();
            text_items[selected_item_index].setFillColor(sf::Color::Green);
        }
    };
    void move_down(){
        if(selected_item_index + 1 < int(items)){
            text_items[selected_item_index].setFillColor(sf::Color::White);
            selected_item_index++;
            selection_sound.play();
            text_items[selected_item_index].setFillColor(sf::Color::Green);
        }
    };
    int get_pressed_item(){
        return selected_item_index;
    };
    void reset(){
        text_items[selected_item_index].setFillColor(sf::Color::White);
        selected_item_index = 0;
        text_items[0].setFillColor(sf::Color::Green);
    }

private:
    int selected_item_index;
    sf::Texture background_texture;
    sf::Sprite background;
    sf::Font font;
    sf::Text text_items[items];
    sf::SoundBuffer selection_buff;
    sf::Sound selection_sound;
};


#endif //TOPFORCE_TEST_MAIN_MENU_HPP
