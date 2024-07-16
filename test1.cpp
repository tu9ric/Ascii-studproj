#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

// Функция для преобразования строки в ASCII-арт
std::vector<std::string> stringToAsciiArt(const std::string& text) {
    // Маппинг символов к ASCII-арту
    std::unordered_map<char, std::vector<std::string>> asciiArtMap = {
        {'a', {"  ##  ", " #  # ", "######", "#    #", "#    #"}},
        {'b', {"##### ", "#    #", "##### ", "#    #", "##### "}},
        {'c', {" #### ", "#    #", "#     ", "#    #", " #### "}},
        {'d', {"##### ", "#    #", "#    #", "#    #", "##### "}},
        {'e', {"######", "#     ", "##### ", "#     ", "######"}},
        {'f', {"######", "#     ", "##### ", "#     ", "#     "}},
        {'g', {" #### ", "#     ", "#  ###", "#    #", " #### "}},
        {'h', {"#    #", "#    #", "######", "#    #", "#    #"}},
        {'i', {" #####", "   #  ", "   #  ", "   #  ", " #####"}},
        {'j', {"     #", "     #", "     #", "#    #", " #### "}},
        {'k', {"#    #", "#   # ", "####  ", "#   # ", "#    #"}},
        {'l', {"#     ", "#     ", "#     ", "#     ", "######"}},
        {'m', {"#    #", "##  ##", "# ## #", "#    #", "#    #"}},
        {'n', {"#    #", "##   #", "# #  #", "#  # #", "#   ##"}},
        {'o', {" #### ", "#    #", "#    #", "#    #", " #### "}},
        {'p', {"##### ", "#    #", "##### ", "#     ", "#     "}},
        {'q', {" #### ", "#    #", "#    #", "#  # #", " ### #"}},
        {'r', {"##### ", "#    #", "##### ", "#   # ", "#    #"}},
        {'s', {" #### ", "#     ", " #### ", "     #", " #### "}},
        {'t', {"######", "  #   ", "  #   ", "  #   ", "  #   "}},
        {'u', {"#    #", "#    #", "#    #", "#    #", " #### "}},
        {'v', {"#    #", "#    #", "#    #", " #  # ", "  ##  "}},
        {'w', {"#    #", "#    #", "# ## #", "##  ##", "#    #"}},
        {'x', {"#    #", " #  # ", "  ##  ", " #  # ", "#    #"}},
        {'y', {"#    #", " #  # ", "  ##  ", "  #   ", "  #   "}},
        {'z', {"######", "    # ", "   #  ", "  #   ", "######"}},
        {' ', {"     ", "     ", "     ", "     ", "     "}},
        {',', {"     ", "     ", "     ", " ##  ", " ##  "}},
        {'.', {"     ", "     ", "     ", "     ", "  ## "}},
        {'!', {"  #  ", "  #  ", "  #  ", "     ", "  #  "}},
        {'?', {" ### ", "#   #", "   # ", "  #  ", "  #  "}}
    };

    std::vector<std::string> asciiArt(5, "");

    // Проверяем, есть ли все символы в маппинге
    for (char c : text) {
        if (asciiArtMap.find(tolower(c)) == asciiArtMap.end() && c != ' ' && c != ',' && c != '.' && c != '!' && c != '?') {
            std::cerr << "Символ '" << c << "' не найден в маппинге." << std::endl;
            return {};
        }
    }

    // Создаем ASCII-арт
    for (int i = 0; i < 5; ++i) { // Предполагаем, что каждый символ состоит из 5 строк
        for (char c : text) {
            asciiArt[i] += asciiArtMap[tolower(c)][i] + "  ";
        }
    }

    return asciiArt;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 600), "ASCII Art in SFML"); // Увеличиваем размер окна

    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\cour.ttf")) { // Используем шрифт Courier New
        std::cerr << "Ошибка загрузки шрифта" << std::endl;
        return -1;
    }

    std::string inputText;
    std::vector<std::string> asciiArt;
    std::vector<sf::Text> textLines;

    sf::Text prompt("enter the text: ", font, 20);
    prompt.setFillColor(sf::Color::White);
    prompt.setPosition(50.0f, 10.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!inputText.empty()) {
                        inputText.pop_back();
                    }
                } else if (event.text.unicode < 128) {
                    inputText += static_cast<char>(event.text.unicode);
                }

                asciiArt = stringToAsciiArt(inputText);
                textLines.clear();
                for (const auto& line : asciiArt) {
                    sf::Text text(line, font, 15); // Уменьшаем размер шрифта
                    text.setFillColor(sf::Color::White);
                    textLines.push_back(text);
                }
            }
        }

        window.clear();
        window.draw(prompt);
        float y = 50.0f;
        for (auto& text : textLines) {
            text.setPosition(50.0f, y);
            window.draw(text);
            y += 20.0f; // Уменьшаем расстояние между строками
        }
        window.display();
    }

    return 0;
}