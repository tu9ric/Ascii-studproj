#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

bool isButtonHover(sf::FloatRect button, sf::Vector2f mp)
{
    if (button.contains(mp))
    {
        return true;
    }
    return false;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My first Visual Studio window!");

    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
    {
        return 1;
    }

    sf::Text button1("1.Convert images to ASCII art", font, 24);
    button1.setFillColor(sf::Color::White);
    button1.setPosition(50, 300);

    sf::Text button2("2.Print words in ASCII code", font, 24);
    button2.setFillColor(sf::Color::White);
    button2.setPosition(50, 350);

    while (window.isOpen())
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f mp = window.mapPixelToCoords(mousePosition);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (isButtonHover(button1.getGlobalBounds(), mp))
            {
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::RenderWindow newWindow(sf::VideoMode(400, 200), "Convert images to ASCII art!");
                    sf::Text text("it works! I'm shocked!1", font, 24);
                    text.setFillColor(sf::Color::White);
                    text.setPosition(150, 100);
                    newWindow.draw(text);
                    newWindow.display();

                    while (newWindow.isOpen())
                    {
                        sf::Event newEvent;
                        while (newWindow.pollEvent(newEvent))
                        {
                            if (newEvent.type == sf::Event::Closed)
                            {
                                newWindow.close();
                            }
                        }
                    }
                }
            }

            if (isButtonHover(button2.getGlobalBounds(), mp))
            {
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::RenderWindow newWindow(sf::VideoMode(400, 200), "Print words in ASCII code");
                    sf::Text text("it works! I'm shocked!2", font, 24);
                    text.setFillColor(sf::Color::White);
                    text.setPosition(150, 100);
                    newWindow.draw(text);
                    newWindow.display();

                    while (newWindow.isOpen())
                    {
                        sf::Event newEvent;
                        while (newWindow.pollEvent(newEvent))
                        {
                            if (newEvent.type == sf::Event::Closed)
                            {
                                newWindow.close();
                            }
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        window.draw(button1);
        window.draw(button2);

        window.display();
    }

    return 0;
}