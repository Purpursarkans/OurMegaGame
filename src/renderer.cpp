#include "renderer.hpp"

std::map<std::string, sf::Texture> Renderer::loadImagesFromFolder(const std::string& folderPath)
{
    std::map<std::string, sf::Texture> textures;
    
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            sf::Texture texture;
            
            if (!texture.loadFromFile(entry.path().string())) {
                std::cerr << entry.path().string() << " is not valid @ ImageLoader" << std::endl;             
                continue;
            }
            fs::path filePath(entry.path());
            std::string filename = filePath.filename().string();
            
            textures[filename] = texture;
        }
    }
    
    return textures;
}


Renderer::Renderer(sf::RenderWindow& w) : window(w) {}

void Renderer::render()
{
    for (const auto& sprite : this->pool) {
        this->window.draw(*sprite);
    }
}

sf::Sprite Renderer::newSprite(sf::Texture* texture)
{
    sf::Sprite sprite;
    sprite.setTexture(*texture);
    this->pool.insert(this->pool.begin(), &sprite);
    return sprite;
}