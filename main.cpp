#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    setlocale(LC_ALL, "rus");
    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(800, 600), "Idle Game");

    // Создаем прямоугольник для кнопки
    sf::RectangleShape button(sf::Vector2f(100, 50));
    button.setFillColor(sf::Color::Green);
    button.setPosition(350, 250);

    // Создаем шрифт для текста
    sf::Font font;
    if (!font.loadFromFile("tuffy.ttf"))
        return EXIT_FAILURE;

    // Создаем текст для отображения счета
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);


    // Инициализируем счет
    int score = 0;

    // Основной цикл игры
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (button.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        score++;
                    }
                }
            }
        }

        // Обновляем текст счета
        scoreText.setString("Score: " + std::to_string(score));

        // Очищаем окно
        window.clear();

        // Рисуем кнопку и текст
        window.draw(button);
        window.draw(scoreText);

        // Отображаем окно
        window.display();
    }

    return 0;
}