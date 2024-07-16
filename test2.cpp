#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>


// Функция для определения яркости пикселя
float Bribrightness(int R, int G, int B) {
    return 0.375 * R + 0.5 * G + 0.16 * B;
}

// Функция для преобразования изображения в ASCII-арт
void convertToAsciiArt(sf::Font& font, const std::string& nameFile) {
    OPENFILENAMEW ofn;
    wchar_t szFile[260]; // Буфер для имени файла

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = L'\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameW(&ofn) == TRUE) {
        sf::Image image;
        char path[260];
        wcstombs(path, ofn.lpstrFile, sizeof(path));
        if (!image.loadFromFile(path)) {
            std::cerr << "Не удалось загрузить изображение." << std::endl;
            return;
        }

        std::ofstream outFile(nameFile);
        if (!outFile.is_open()) {
            std::cerr << "Не удалось открыть файл для записи." << std::endl;
            return;
        }

        int X_MAX = image.getSize().x;
        int Y_MAX = image.getSize().y;
        float max_brightness = Bribrightness(255, 255, 255);
        char gradientChars[] = { ' ', '.', ':', '-', '=', '+', '*', '#', '%', '@' };

        for (int y = 0; y < Y_MAX; y++) {
            for (int x = 0; x < X_MAX; x++) {
                sf::Color color = image.getPixel(x, y);
                float brightness = Bribrightness(color.r, color.g, color.b);
                int pos = static_cast<int>((brightness / max_brightness) * 9); // Используем 9, так как индексация начинается с 0
                outFile << gradientChars[pos];
            }
            outFile << '\n';
        }

        outFile.close();
        std::cout << "ASCII art created successfully!" << std::endl;
    } else {
        std::cerr << "No file selected." << std::endl;
    }
}

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

void runAsciiArtText(sf::Font& font) {
    sf::RenderWindow window(sf::VideoMode(1600, 600), "ASCII Art in SFML"); // Увеличиваем размер окна

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
}

// Функция для отображения анимации ASCII-символов
void displayAsciiAnimation(sf::RenderWindow& window, sf::Font& font) {
    std::vector<std::string> frames = {
        "  @  \n @@@ \n@@@@@\n @@@ \n  @  ",
        " @@@ \n@@@@@\n @@@ \n  @  \n @@@ ",
        "@@@@@\n @@@ \n  @  \n @@@ \n@@@@@",
        " @@@ \n  @  \n @@@ \n@@@@@\n @@@ "
    };

    sf::Text asciiText("", font, 24);
    asciiText.setFillColor(sf::Color::White);
    asciiText.setPosition(50, 50);

    sf::Clock animationClock;
    int frameIndex = 0;

    while (animationClock.getElapsedTime().asSeconds() < 10) {
        window.clear(sf::Color::Black);
        asciiText.setString(frames[frameIndex]);
        window.draw(asciiText);
        window.display();

        frameIndex = (frameIndex + 1) % frames.size();
        sf::sleep(sf::milliseconds(500));
    }
}
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "ASCII Art Converter");
    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    sf::Text button1("1. Convert images to ASCII art", font, 24);
    button1.setFillColor(sf::Color::White);
    button1.setPosition(50, 300);

    sf::Text button2("2. Print words in ASCII code", font, 24);
    button2.setFillColor(sf::Color::White);
    button2.setPosition(50, 350);

    std::string nameFile = "ascii_art.txt"; // Имя файла для ASCII-арта
    sf::Clock idleClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::FloatRect button1Bounds = button1.getGlobalBounds();
                sf::FloatRect button2Bounds = button2.getGlobalBounds();

                if (button1Bounds.contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    // Создание временного окна с надписью "Loading..."
                    sf::RenderWindow loadingWindow(sf::VideoMode(200, 100), "Loading...", sf::Style::None);
                    sf::Text loadingText("Loading...", font, 24);
                    loadingText.setFillColor(sf::Color::White);
                    loadingText.setPosition(50, 40);

                    while (loadingWindow.isOpen()) {
                        loadingWindow.clear();
                        loadingWindow.draw(loadingText);
                        loadingWindow.display();

                        // Проверка на закрытие окна
                        sf::Event loadingEvent;
                        while (loadingWindow.pollEvent(loadingEvent)) {
                            if (loadingEvent.type == sf::Event::Closed) {
                                loadingWindow.close();
                            }
                        }

                        // Задержка в 2 секунды
                        sf::sleep(sf::seconds(2));
                        loadingWindow.close();
                    }

                    convertToAsciiArt(font, nameFile);
                    system(("notepad.exe " + nameFile).c_str());
                } else if (button2Bounds.contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    // Запуск функции для преобразования текста в ASCII-арт
                    sf::RenderWindow asciiWindow(sf::VideoMode(1600, 600), "ASCII Art in SFML"); // Увеличиваем размер окна

                    sf::Font asciiFont;
                    if (!asciiFont.loadFromFile("C:\\Windows\\Fonts\\cour.ttf")) { // Используем шрифт Courier New
                        std::cerr << "Ошибка загрузки шрифта" << std::endl;
                        return -1;
                    }

                    std::string inputText;
                    std::vector<std::string> asciiArt;
                    std::vector<sf::Text> textLines;

                    sf::Text prompt("enter the text: ", asciiFont, 20);
                    prompt.setFillColor(sf::Color::White);
                    prompt.setPosition(50.0f, 10.0f);

                    while (asciiWindow.isOpen()) {
                        sf::Event asciiEvent;
                        while (asciiWindow.pollEvent(asciiEvent)) {
                            if (asciiEvent.type == sf::Event::Closed)
                                asciiWindow.close();
                            else if (asciiEvent.type == sf::Event::TextEntered) {
                                if (asciiEvent.text.unicode == '\b') {
                                    if (!inputText.empty()) {
                                        inputText.pop_back();
                                    }
                                } else if (asciiEvent.text.unicode < 128) {
                                    inputText += static_cast<char>(asciiEvent.text.unicode);
                                }

                                asciiArt = stringToAsciiArt(inputText);
                                textLines.clear();
                                for (const auto& line : asciiArt) {
                                    sf::Text text(line, asciiFont, 15); // Уменьшаем размер шрифта
                                    text.setFillColor(sf::Color::White);
                                    textLines.push_back(text);
                                }
                            }
                        }

                        asciiWindow.clear();
                        asciiWindow.draw(prompt);
                        float y = 50.0f;
                        for (auto& text : textLines) {
                            text.setPosition(50.0f, y);
                            asciiWindow.draw(text);
                            y += 20.0f; // Уменьшаем расстояние между строками
                        }
                        asciiWindow.display();
                    }
                }
            }
        }
        if (idleClock.getElapsedTime().asSeconds() > 10) {
            displayAsciiAnimation(window, font);
            idleClock.restart();
        }

        window.clear(sf::Color::Black);
        window.draw(button1);
        window.draw(button2); // Отрисовка второй кнопки
        window.display();
    }

    return 0;
}