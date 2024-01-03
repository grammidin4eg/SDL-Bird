#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    // константы
    const int SCREEN_HEIGHT = 800;
    const int SCREEN_WIDTH = 600;

    const float GROUND_SPEED = 100;
    const float GRAVITY = 100;
    const float JUMP_POWER = 10 * GRAVITY;

    // Состояние игры (тип)
    enum class EGameState { Menu, Game, GameOver};

    // создаём окно
    RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SDL Bird");
    Image imgIcon;
    imgIcon.loadFromFile("Images/mainico.png");
    window.setIcon(32, 32, imgIcon.getPixelsPtr());

    // размер окна
    Vector2f windowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    // -------------------------------  загрузка текстур -----------------------------------------------------

    // фон
    Texture texBackground;
    texBackground.loadFromFile("Images/background.png");

    RectangleShape shapeBackground(windowSize);
    shapeBackground.setTexture(&texBackground);

    // земля
    Texture texGround;
    texGround.loadFromFile("Images/ground.png");

    Sprite sGround1;
    sGround1.setTexture(texGround);
    sGround1.setScale(windowSize.x / sGround1.getLocalBounds().width, 1);

    Sprite sGround2;
    sGround2.setTexture(texGround);
    sGround2.setScale(windowSize.x / sGround2.getLocalBounds().width, 1);

    // главное меню
    Texture texMessage;
    texMessage.loadFromFile("Images/message.png");

    RectangleShape shapeMenuMessage(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    shapeMenuMessage.setPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
    shapeMenuMessage.setTexture(&texMessage);

    // Птица
    Texture texBirdMid;
    texBirdMid.loadFromFile("Images/yellowbird-midflap.png");

    Sprite sBird;
    sBird.setTexture(texBirdMid);
    sBird.setPosition(200, SCREEN_HEIGHT / 2);


    // сообщение Игра окончена
    Texture texGameOver;
    texGameOver.loadFromFile("Images/gameover.png");

    Sprite sGameOver;
    sGameOver.setTexture(texGameOver);
    sGameOver.setScale(windowSize.x / sGameOver.getLocalBounds().width / 2, 1);
    sGameOver.setPosition(SCREEN_WIDTH / 2 - sGameOver.getGlobalBounds().width / 2, SCREEN_HEIGHT / 3);
    


    EGameState curState = EGameState::Menu;

    // смещение скролла
    float scrollingOffset = 0;

    // Расчет времени
    Clock clock;

    // -------------------------------  цикл игры -----------------------------------------------------------
    while (window.isOpen())
    {
        // Перезапускаем таймер и записываем отмеренное время в dt
        Time deltaTime = clock.restart();

        float deltaTimeSec = deltaTime.asSeconds();
        
        // -------------------------------  обработка событий -----------------------------------------------
        Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
                window.close();

            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                switch (curState)
                {
                case EGameState::Menu:
                    curState = EGameState::Game;
                    break;
                case EGameState::Game:
                    break;
                case EGameState::GameOver:
                    break;
                default:
                    break;
                }
            }
        }

        // ------------------------------- обновление объектов ---------------------------------------------
        if (curState == EGameState::Game)
        {
            scrollingOffset-=GROUND_SPEED * deltaTimeSec;
            if (scrollingOffset < -sGround1.getGlobalBounds().width)
            {
                scrollingOffset = 0;
            }
            sGround1.setPosition(scrollingOffset, SCREEN_HEIGHT - sGround1.getGlobalBounds().height);
            sGround2.setPosition(scrollingOffset + sGround2.getGlobalBounds().width, SCREEN_HEIGHT - sGround2.getGlobalBounds().height);

            sBird.move(0, GRAVITY * deltaTimeSec);

            if (sBird.getPosition().y > (SCREEN_HEIGHT - sGround1.getGlobalBounds().height - sBird.getGlobalBounds().height))
            {
                curState = EGameState::GameOver;
            }
        }

        // -------------------------------  отрисовка ---------------------------------------------------------
        window.clear();
        // window.draw(sBackground);
        window.draw(shapeBackground);
        switch (curState)
        {
        case EGameState::Menu:
            window.draw(shapeMenuMessage);
            break;
        case EGameState::Game:
            window.draw(sBird);
            window.draw(sGround1);
            window.draw(sGround2);
            break;
        case EGameState::GameOver:
            window.draw(sBird);
            window.draw(sGround1);
            window.draw(sGround2);
            window.draw(sGameOver);
            break;
        default:
            break;
        }
        window.display();
    }

    return 0;
}