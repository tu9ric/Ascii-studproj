#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

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
                int pos = (brightness / max_brightness) * 9; // Используем 9, так как индексация начинается с 0
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
                    // Отображение сообщения "This feature will be working soon"
                    sf::Text comingSoonText("This feature will be working soon", font, 24);
                    comingSoonText.setFillColor(sf::Color::Red);
                    comingSoonText.setPosition(50, 400);

                    window.clear(sf::Color::Black); // Очистка окна перед отрисовкой текста
                    window.draw(button1);
                    window.draw(button2);
                    window.draw(comingSoonText);
                    window.display();

                    // Задержка в 2 секунды перед закрытием сообщения
                    sf::sleep(sf::seconds(2));
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(button1);
        window.draw(button2); // Отрисовка второй кнопки
        window.display();
    }

    return 0;
}