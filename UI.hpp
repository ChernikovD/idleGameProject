#pragma once
#include <SFML/Graphics.hpp>

class UI {
public:
    virtual ~UI() = default;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;
    virtual void update() = 0;
};