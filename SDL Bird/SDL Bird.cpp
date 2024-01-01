#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    // константы
    const int SCREEN_HEIGHT = 800;
    const int SCREEN_WIDTH = 600;
    // создаём окно
    RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SDL Bird");
    Image imgIcon;
    imgIcon.loadFromFile("Images/mainico.png");
    window.setIcon(32, 32, imgIcon.getPixelsPtr());

    // загрузка текстур

    // фон
    Texture texBackground;
    texBackground.loadFromFile("Images/background.png");

    Sprite sBackground;
    sBackground.setTexture(texBackground);
    Vector2f windowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    sBackground.setScale(
        windowSize.x / sBackground.getLocalBounds().width,
        windowSize.y / sBackground.getLocalBounds().height);

    // земля
    Texture texGround;
    texGround.loadFromFile("Images/ground.png");

    Sprite sGround1;
    sGround1.setTexture(texGround);
    sGround1.setPosition(0, SCREEN_HEIGHT - sGround1.getLocalBounds().height);

    Sprite sGround2;
    sGround2.setTexture(texGround);
    sGround2.setPosition(sGround2.getLocalBounds().width, SCREEN_HEIGHT - sGround2.getLocalBounds().height);

    // главное меню
    Texture texMessage;
    texMessage.loadFromFile("Images/message.png");

    Sprite sMessage;
    sMessage.setTexture(texMessage);

    sMessage.setScale(
        windowSize.x / sMessage.getLocalBounds().width / 2,
        windowSize.y / sMessage.getLocalBounds().height / 2);

    sMessage.setPosition(sMessage.getGlobalBounds().width / 2, sMessage.getGlobalBounds().height / 2);


    // цикл игры
    while (window.isOpen())
    {
        // обработка событий
        Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
                window.close();
        }

        // обновление объектов

        // отрисовка
        window.clear();
        window.draw(sBackground);
        window.draw(sMessage);
        window.draw(sGround1);
        window.draw(sGround2);
        window.display();
    }

    return 0;
}