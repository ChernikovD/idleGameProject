#include <SFML/Graphics.hpp>
#include "UI.hpp"
#include "GameState.hpp"

class MainUI : public UI {
public:
    MainUI(sf::RenderWindow& window)
        : window(window), showTempSprite(false), ground(sf::Vector2f(1280, 25)) {
        // Загружаем текстуру для фона
        if (!backgroundTexture.loadFromFile("sky_background.jpg")) {
            std::cerr << "Не удалось загрузить текстуру фона!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setPosition(0, 0);
        backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        );

        // Создаем прямоугольник для фона
        ground.setFillColor(sf::Color(247, 200, 141));
        ground.setPosition(0, 695);

        // Загружаем текстуру для кнопки
        if (!buttonTexture.loadFromFile("oil_derrick.png")) {
            std::cerr << "Не удалось загрузить текстуру кнопки!" << std::endl;
        }
        buttonSprite.setTexture(buttonTexture);
        buttonSprite.setPosition(350, 300);

        // Загружаем текстуру для кнопки магазина
        if (!openShopTexture.loadFromFile("shop.png")) {
            std::cerr << "Не удалось загрузить текстуру кнопки!" << std::endl;
        }
        openShopSprite.setTexture(openShopTexture);
        openShopSprite.setPosition(1175, 15);

        // Загружаем текстуру для временного спрайта
        if (!tempSpriteTexture.loadFromFile("coin50x50.png")) {
            std::cerr << "Не удалось загрузить текстуру временного спрайта!" << std::endl;
        }
        tempSprite.setTexture(tempSpriteTexture);

        // Создаем шрифт для текста
        if (!font.loadFromFile("tuffy.ttf")) {
            std::cerr << "Не удалось загрузить шрифт!" << std::endl;
        }
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(backgroundSprite);
        window.draw(ground);
        window.draw(openShopSprite);
        window.draw(buttonSprite);
        window.draw(scoreText);
        if (showTempSprite) {
            window.draw(tempSprite);
        }
    }

    void handleEvent(sf::Event& event, sf::RenderWindow& window) override {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (buttonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    clickCount++;
                    GameState::getInstance().incrementScore(1 + GameState::getInstance().get_score_bonus_per_click());
                    if (clickCount % 10 == 0) {
                        GameState::getInstance().incrementScore(GameState::getInstance().get_score_bonus_per_10_clicks());
                    }
                    showTempSprite = true;
                    tempSpriteClock.restart();
                    tempSprite.setPosition(static_cast<float>(mousePosition.x) - 25, static_cast<float>(mousePosition.y) - 25);
                }
            }
        }
    }

    void update() override {
        scoreText.setString("GOLD: " + std::to_string(GameState::getInstance().getScore()));
        if (showTempSprite && tempSpriteClock.getElapsedTime() >= tempSpriteDuration) {
            showTempSprite = false;
        }
        // Добавляем бонус к счету каждые 10 секунд
        if (scoreBonusClock.getElapsedTime() >= sf::seconds(1.0f)) {
            GameState::getInstance().incrementScore(GameState::getInstance().get_score_bonus_per_second());
            scoreBonusClock.restart();
        }
    }
    
    const sf::Sprite& getOpenShopSprite() const {
        return openShopSprite;
    }

private:
    int clickCount = 0;
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape ground;
    sf::Texture openShopTexture;
    sf::Sprite openShopSprite;
    sf::Texture buttonTexture;
    sf::Sprite buttonSprite;
    sf::Texture tempSpriteTexture;
    sf::Sprite tempSprite;
    sf::Font font;
    sf::Text scoreText;
    bool showTempSprite;
    sf::Clock tempSpriteClock;
    const sf::Time tempSpriteDuration = sf::seconds(0.5f); // Время отображения временного спрайта
    sf::Clock scoreBonusClock;
};
