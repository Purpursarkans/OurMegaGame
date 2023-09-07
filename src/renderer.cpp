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


Renderer::Renderer(sf::RenderWindow& w) : window(w)
{
    // auto ws = w.getSize();
    viewport.setSize(1280.f, 720.f);
    viewport.zoom(0.5f);
    viewport.setCenter(0.5f, 0.5f);
    w.setView(viewport);
}

void Renderer::render()
{
    for (const auto& sprite : pool) {
        window.draw(*sprite);
    }
    window.setView(viewport);
}

sf::Sprite Renderer::newSprite(sf::Texture* texture)
{
    sf::Sprite sprite;
    sprite.setTexture(*texture);
    pool.insert(pool.begin(), &sprite);
    return sprite;
}