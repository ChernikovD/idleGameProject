#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    setlocale(LC_ALL, "rus");
    // ������� ����
    int window_height = 1280;
    int window_width = 720;
    
    sf::RenderWindow window(sf::VideoMode(window_height, window_width), "Idle Game");
    
    // ��������� �������� ��� ����
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("sky_background.jpg")) {
        std::cerr << "�� ������� ��������� �������� ����!" << std::endl;
        return EXIT_FAILURE;
    }

    // ������� ������������� ��� ����
    sf::RectangleShape ground(sf::Vector2f(1280, 25));
    ground.setFillColor(sf::Color(247, 200, 141));
    ground.setPosition(0, 695);

    // ������� ������ ��� ����
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setPosition(0, 0);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // ��������� �������� ��� ������
    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("oil_derrick.png")) {
        std::cerr << "�� ������� ��������� �������� ������!" << std::endl;
        return EXIT_FAILURE;
    }

    // ������� ������ ��� ������
    sf::Sprite buttonSprite(buttonTexture);
    buttonSprite.setPosition(350, 300);

    // ��������� �������� ��� ������ ��������
    sf::Texture openShopTexture;
    if (!openShopTexture.loadFromFile("shop.png")) {
        std::cerr << "�� ������� ��������� �������� ������!" << std::endl;
        return EXIT_FAILURE;
    }

    // ������� ������ ��� ������ ��������
    sf::Sprite openShopSprite(openShopTexture);
    openShopSprite.setPosition(1175, 15);

    // ��������� �������� ��� ���������� �������
    sf::Texture tempSpriteTexture;
    if (!tempSpriteTexture.loadFromFile("coin50x50.png")) {
        std::cerr << "�� ������� ��������� �������� ���������� �������!" << std::endl;
        return EXIT_FAILURE;
    }

    // ������� ������ ��� ���������� �������
    sf::Sprite tempSprite(tempSpriteTexture);
    tempSprite.setPosition(0, 0); // ��������� �������
    bool showTempSprite = false;
    sf::Clock tempSpriteClock;
    const sf::Time tempSpriteDuration = sf::seconds(1.0f); // ����� ����������� ���������� �������


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
                    if (buttonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        score++;
                        showTempSprite = true;
                        tempSpriteClock.restart();
                        tempSprite.setPosition(static_cast<float>(mousePosition.x) - 25, static_cast<float>(mousePosition.y) - 25);
                    }
                }
            }
        }

        // ��������� ����� �����
        scoreText.setString("Score: " + std::to_string(score));

        // ���������, ����� �� ���������� ��������� ������
        if (showTempSprite && tempSpriteClock.getElapsedTime() >= tempSpriteDuration) {
            showTempSprite = false;
        }

        // ������� ����
        window.clear();

        // ������ ��� 
        window.draw(backgroundSprite);

        // ������ ��� �����
        window.draw(ground);

        // ������ �������
        window.draw(openShopSprite);

        // ������ ������ � �����
        window.draw(buttonSprite);
        window.draw(scoreText);

        // ������ ��������� ������, ���� �����
        if (showTempSprite) {
            window.draw(tempSprite);
        }

        // ���������� ����
        window.display();
    }

    return 0;
}