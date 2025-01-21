#include <SFML/Graphics.hpp>
#include <iostream>
#include "MainUI.hpp"
#include "ShopUI.hpp"

int main() {
    setlocale(LC_ALL, "rus");
    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Idle Game");

    // Создаем UI
    MainUI mainUI(window);
    ShopUI shopUI(window);
    UI* currentUI = &mainUI;

    // Основной цикл игры
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            currentUI->handleEvent(event, window);

            // Логика переключения между UI
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

        // Очищаем окно
        window.clear();

        // Рисуем текущий UI
        currentUI->draw(window);

        // Отображаем окно
        window.display();
    }

    return 0;
}