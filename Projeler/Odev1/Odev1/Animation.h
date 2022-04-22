#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation();
    ~Animation();
private:
    // Vector2i yerine Vector2u kullanmamızın sebebi 
    sf::Vector2u image_count_;
    sf::Vector2u current_image_;
    
};