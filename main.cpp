#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{ 
    setlocale(LC_ALL, "Russian");
    sf::RenderWindow window(sf::VideoMode(800, 600), "ASCII Art Converter");

    // Шрифт для текста кнопок
    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    // Создание текстов кнопок
    sf::Text mode1Text, mode2Text;
    mode1Text.setFont(font);
    mode1Text.setString("Convert images to ASCII art");
    mode1Text.setCharacterSize(24);
    mode1Text.setFillColor(sf::Color::White);
    mode1Text.setPosition(100, 200);

    mode2Text.setFont(font);
    mode2Text.setString("Print words in ASCII code");
    mode2Text.setCharacterSize(24);
    mode2Text.setFillColor(sf::Color::White);
    mode2Text.setPosition(100, 300);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Получаем позицию окна на экране
                    sf::Vector2i windowPosition = window.getPosition();

                    // Получаем позицию нажатия относительно окна
                    sf::Vector2i mousePosition = sf::Mouse::getPosition();

                    // Корректируем позицию нажатия относительно окна
                    mousePosition.x -= windowPosition.x;
                    mousePosition.y -= windowPosition.y;

                    // Проверяем, на какую кнопку нажали
                    if (mode1Text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        std::cout << "Selected mode 1: Convert images to ASCII art" << std::endl;
                        // Здесь нужно вызвать функцию для загрузки изображения и конвертации в ASCII-арт
                    }
                    else if (mode2Text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        std::cout << "Selected mode 2: Print words in ASCII code" << std::endl;
                        // Здесь нужно вызвать функцию для печати слов в ASCII коде
                    }
                }
            }
        }

        window.clear();
        window.draw(mode1Text);
        window.draw(mode2Text);
        window.display();
    }

    return 0;
}