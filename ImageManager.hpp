//
// Created by Nathan Hoekstra on 2019-01-23.
//

#ifndef TOPFORCE_IMAGEMANAGER_HPP
#define TOPFORCE_IMAGEMANAGER_HPP

#include <string>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <array>

namespace tf {
enum class Animation {
	MenuBG = 0,
    Stationary = 1,
    Walking = 2,
    EnemyStationary = 3,
    EnemyWalking = 4
};

class ImageManager {
private:
    ImageManager();
    const std::string PATH =  "assets/images/";
    std::array<sf::Texture, 5> textures;

    static constexpr const char* fileNames[] = {
		    "main_menu_bg.jpg",
		    "soldier1_machine.png",
		    "soldier1_reload.png",
		    "hitman1_machine.png",
		    "hitman1_reload.png"
    };

    sf::Image icon;
public:
    static ImageManager & getInstance();
    const sf::Texture& getTexture(Animation animation);
    const sf::Uint8* getWindowIcon();
};
}


#endif //TOPFORCE_IMAGEMANAGER_HPP
