//
// Created by Nathan Hoekstra on 2019-01-23.
//

#include "ImageManager.hpp"

namespace tf {
constexpr const char* ImageManager::fileNames[];

ImageManager::ImageManager() {
	for (unsigned i = 0 ; i < textures.size(); i++) {
		textures[i].loadFromFile(fileNames[i]);
	}

    icon.loadFromFile(PATH + "topforce_icon.png");
}

ImageManager& ImageManager::getInstance() {
    static ImageManager Instance;
    return Instance;
}

const sf::Texture& ImageManager::getTexture(Animation animation) {
	return textures[static_cast<unsigned>(animation)];
}

const sf::Uint8* ImageManager::getWindowIcon() {
    return icon.getPixelsPtr();
}
}