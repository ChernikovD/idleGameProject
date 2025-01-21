#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    setlocale(LC_ALL, "rus");
    // ������� ����
    sf::RenderWindow window(sf::VideoMode(800, 600), "Idle Game");

    // ������� ������������� ��� ������
    sf::RectangleShape button(sf::Vector2f(100, 50));
    button.setFillColor(sf::Color::Green);
    button.setPosition(350, 250);

    // ������� ����� ��� ������
    sf::Font font;
    if (!font.loadFromFile("tuffy.ttf"))
        return EXIT_FAILURE;

    // ������� ����� ��� ����������� �����
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);


    // �������������� ����
    int score = 0;

    // �������� ���� ����
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

        // ��������� ����� �����
        scoreText.setString("Score: " + std::to_string(score));

        // ������� ����
        window.clear();

        // ������ ������ � �����
        window.draw(button);
        window.draw(scoreText);

        // ���������� ����
        window.display();
    }

    return 0;
}