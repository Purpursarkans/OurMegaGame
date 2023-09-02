#pragma once
#include "main.hpp"
#include <vector>
#include <map>
#include <filesystem>
namespace fs = std::filesystem;




class Renderer
{
    public:
    std::vector<sf::Sprite*> pool;
    sf::RenderWindow& window;

    Renderer(sf::RenderWindow& w);

    void render();
    sf::Sprite newSprite(sf::Texture* texture);
    std::map<std::string, sf::Texture> loadImagesFromFolder(const std::string& folderPath);

};