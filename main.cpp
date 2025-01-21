#include <SFML/Graphics.hpp>
#include <iostream>
#include "MainUI.hpp"
#include "ShopUI.hpp"

int main() {
    setlocale(LC_ALL, "rus");
    // ������� ����
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Idle Game");

    // ������� UI
    MainUI mainUI(window);
    ShopUI shopUI(window);
    UI* currentUI = &mainUI;

    // �������� ���� ����
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            currentUI->handleEvent(event, window);

            // ������ ������������ ����� UI
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (currentUI == &mainUI && mainUI.getOpenShopSprite().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        currentUI = &shopUI;
                    }
                    else if (currentUI == &shopUI && shopUI.getBackButtonSprite().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        currentUI = &mainUI;
                    }
                }
            }
        }

        currentUI->update();

        // ������� ����
        window.clear();

        // ������ ������� UI
        currentUI->draw(window);

        // ���������� ����
        window.display();
    }

    return 0;
}