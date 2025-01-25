#include <SFML/Graphics.hpp>
#include "UI.hpp"
#include "GameState.hpp"
#include "Price.hpp"

class ShopUI : public UI {
public:
    ShopUI(sf::RenderWindow& window)
        : window(window) {
        // Загружаем текстуру для фона
        if (!backgroundTexture.loadFromFile("shopbackground.jpg")) {
            std::cerr << "Не удалось загрузить текстуру фона!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setPosition(0, 0);
        backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        );

        // Загружаем текстуру для кнопки назад
        if (!closeShopTexture.loadFromFile("backarrow.png")) {
            std::cerr << "Не удалось загрузить текстуру кнопки!" << std::endl;
        }
        closeShopSprite.setTexture(closeShopTexture);
        closeShopSprite.setPosition(1175, 15);

        // Загружаем текстуры для предметов
        if (!itemTextures[0].loadFromFile("shov1.png")) {
            std::cerr << "Не удалось загрузить текстуру предмета 1!" << std::endl;
        }
        if (!itemTextures[1].loadFromFile("worker2.png")) {
            std::cerr << "Не удалось загрузить текстуру предмета 2!" << std::endl;
        }
        if (!itemTextures[2].loadFromFile("oilwell3.png")) {
            std::cerr << "Не удалось загрузить текстуру предмета 3!" << std::endl;
        }

        // Устанавливаем текстуры для спрайтов предметов
        itemSprites[0].setTexture(itemTextures[0]);
        itemSprites[1].setTexture(itemTextures[1]);
        itemSprites[2].setTexture(itemTextures[2]);

        // Устанавливаем позиции для спрайтов предметов
        itemSprites[0].setPosition(100, 200);
        itemSprites[1].setPosition(500, 200);
        itemSprites[2].setPosition(900, 200);

        // Загружаем текстуру для кнопки покупки
        if (!buyButtonTexture.loadFromFile("buy.png")) {
            std::cerr << "Не удалось загрузить текстуру кнопки покупки!" << std::endl;
        }   

        // Устанавливаем текстуры для спрайтов кнопок покупки
        buyButtonSprites[0].setTexture(buyButtonTexture);
        buyButtonSprites[1].setTexture(buyButtonTexture);
        buyButtonSprites[2].setTexture(buyButtonTexture);

        // Устанавливаем позиции для спрайтов кнопок покупки
        buyButtonSprites[0].setPosition(100, 350);
        buyButtonSprites[1].setPosition(500, 350);
        buyButtonSprites[2].setPosition(900, 350);

        // Создаем шрифт для текста
        if (!font.loadFromFile("tuffy.ttf")) {
            std::cerr << "Не удалось загрузить шрифт!" << std::endl;
        }

        // Устанавливаем шрифт для текста количества предметов
        for (int i = 0; i < 3; ++i) {
            itemCountTexts[i].setFont(font);
            itemCountTexts[i].setCharacterSize(24);
            itemCountTexts[i].setFillColor(sf::Color::White);
            itemCountTexts[i].setPosition(100 + i * 400, 250);
        }

        // Устанавливаем шрифт для текста стоимости предметов
        for (int i = 0; i < 3; ++i) {
            itemPriceTexts[i].setFont(font);
            itemPriceTexts[i].setCharacterSize(24);
            itemPriceTexts[i].setFillColor(sf::Color::White);
            itemPriceTexts[i].setPosition(100 + i * 400, 450);
        }
        
        // Устанавливаем шрифт для текста описания предметов
        item1Description.setFont(font);
        item1Description.setCharacterSize(24);
        item1Description.setFillColor(sf::Color::White);
        item1Description.setPosition(100, 150);
        item1Description.setString("+1 GOLD per click");

        item2Description.setFont(font);
        item2Description.setCharacterSize(24);
        item2Description.setFillColor(sf::Color::White);
        item2Description.setPosition(500, 150);
        item2Description.setString("+25 GOLD per 10 clicks");

        item3Description.setFont(font);
        item3Description.setCharacterSize(24);
        item3Description.setFillColor(sf::Color::White);
        item3Description.setPosition(900, 150);
        item3Description.setString("+5 GOLD per second");

        // Устанавливаем шрифт для текста счета
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);

        // Устанавливаем начальные цены предметов
        itemPrices[0] = Price(10.0f);
        itemPrices[1] = Price(20.0f);
        itemPrices[2] = Price(30.0f);
        
        // Устанавливаем начальное количество предметов
        itemCounts[0] = 0;
        itemCounts[1] = 0;
        itemCounts[2] = 0;
    }
    

    void draw(sf::RenderWindow& window) override {
        window.draw(backgroundSprite);
        window.draw(closeShopSprite);
        window.draw(scoreText);
        window.draw(item1Description);
        window.draw(item2Description);
        window.draw(item3Description);
        for (int i = 0; i < 3; ++i) {
            window.draw(itemSprites[i]);
            window.draw(buyButtonSprites[i]);
            window.draw(itemCountTexts[i]);
            window.draw(itemPriceTexts[i]);
        }
    }

    void handleEvent(sf::Event& event, sf::RenderWindow& window) override {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                for (int i = 0; i < 3; ++i) {
                    if (buyButtonSprites[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        // Логика для покупки предмета
                        if (GameState::getInstance().getScore() >= itemPrices[i].getPrice()) { 
                            GameState::getInstance().incrementScore(-1 * itemPrices[i].getPrice());
                            itemCounts[i]++;
                            itemPrices[i].increasePrice();
                            applyItemBenefit(i);
                        }
                    }
                }
            }
        }
    }

    void update() override {
        scoreText.setString("GOLD: " + std::to_string(GameState::getInstance().getScore()));
        for (int i = 0; i < 3; ++i) {
            itemCountTexts[i].setString("Count: " + std::to_string(itemCounts[i]));
            itemPriceTexts[i].setString("Price: " + std::to_string(itemPrices[i].getPrice()));
        }
    }

    const sf::Sprite& getBackButtonSprite() const {
        return closeShopSprite;
    }

private:
    void applyItemBenefit(int itemIndex) {
        switch (itemIndex) {
        case 0:
            // Первый товар: +1 к счету за каждый клик
            GameState::getInstance().increase_score_bonus_per_click(1);
            break;
        case 1:
            // Второй товар: +25 к счету за каждые 10 кликов
            GameState::getInstance().increase_score_bonus_per_10_clicks(25);
            break;
        case 2:
            // Третий товар: +5 к счету в секунду
            GameState::getInstance().increase_score_bonus_per_second(5);
            break;
        }
    }

private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture closeShopTexture;
    sf::Sprite closeShopSprite;
    sf::Texture itemTextures[3];
    sf::Sprite itemSprites[3];
    sf::Texture buyButtonTexture;
    sf::Sprite buyButtonSprites[3];
    sf::Font font;
    sf::Text itemCountTexts[3];
    sf::Text itemPriceTexts[3];
    sf::Text scoreText;
    sf::Text item1Description;
    sf::Text item2Description;
    sf::Text item3Description;
    int itemCounts[3];
    Price itemPrices[3];
};
