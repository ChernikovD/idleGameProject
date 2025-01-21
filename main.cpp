#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    setlocale(LC_ALL, "rus");
    // Создаем окно
    int window_height = 1280;
    int window_width = 720;
    
    sf::RenderWindow window(sf::VideoMode(window_height, window_width), "Idle Game");
    
    // Загружаем текстуру для фона
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("sky_background.jpg")) {
        std::cerr << "Не удалось загрузить текстуру фона!" << std::endl;
        return EXIT_FAILURE;
    }

    // Создаем прямоугольник для фона
    sf::RectangleShape ground(sf::Vector2f(1280, 25));
    ground.setFillColor(sf::Color(247, 200, 141));
    ground.setPosition(0, 695);

    // Создаем спрайт для фона
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setPosition(0, 0);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Загружаем текстуру для кнопки
    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("oil_derrick.png")) {
        std::cerr << "Не удалось загрузить текстуру кнопки!" << std::endl;
        return EXIT_FAILURE;
    }

    // Создаем спрайт для кнопки
    sf::Sprite buttonSprite(buttonTexture);
    buttonSprite.setPosition(350, 300);

    // Загружаем текстуру для кнопки магазина
    sf::Texture openShopTexture;
    if (!openShopTexture.loadFromFile("shop.png")) {
        std::cerr << "Не удалось загрузить текстуру кнопки!" << std::endl;
        return EXIT_FAILURE;
    }

    // Создаем спрайт для кнопки магазина
    sf::Sprite openShopSprite(openShopTexture);
    openShopSprite.setPosition(1175, 15);

    // Загружаем текстуру для временного спрайта
    sf::Texture tempSpriteTexture;
    if (!tempSpriteTexture.loadFromFile("coin50x50.png")) {
        std::cerr << "Не удалось загрузить текстуру временного спрайта!" << std::endl;
        return EXIT_FAILURE;
    }

    // Создаем спрайт для временного спрайта
    sf::Sprite tempSprite(tempSpriteTexture);
    tempSprite.setPosition(0, 0); // Начальная позиция
    bool showTempSprite = false;
    sf::Clock tempSpriteClock;
    const sf::Time tempSpriteDuration = sf::seconds(1.0f); // Время отображения временного спрайта


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
                    if (buttonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        score++;
                        showTempSprite = true;
                        tempSpriteClock.restart();
                        tempSprite.setPosition(static_cast<float>(mousePosition.x) - 25, static_cast<float>(mousePosition.y) - 25);
                    }
                }
            }
        }

        // Обновляем текст счета
        scoreText.setString("Score: " + std::to_string(score));

        // Проверяем, нужно ли отображать временный спрайт
        if (showTempSprite && tempSpriteClock.getElapsedTime() >= tempSpriteDuration) {
            showTempSprite = false;
        }

        // Очищаем окно
        window.clear();

        // Рисуем фон 
        window.draw(backgroundSprite);

        // Рисуем фон земли
        window.draw(ground);

        // Рисуем магазин
        window.draw(openShopSprite);

        // Рисуем кнопку и текст
        window.draw(buttonSprite);
        window.draw(scoreText);

        // Рисуем временный спрайт, если нужно
        if (showTempSprite) {
            window.draw(tempSprite);
        }

        // Отображаем окно
        window.display();
    }

    return 0;
}