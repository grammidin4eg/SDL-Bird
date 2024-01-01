#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window(sf::VideoMode(1024, 768), "SDL Bird");
    Image imgIcon;
    imgIcon.loadFromFile("Images/mainico.png");
    window.setIcon(32, 32, imgIcon.getPixelsPtr());

    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}