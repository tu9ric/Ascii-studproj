#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <cstring>

float Bribrightness(int R, int G, int B);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "File Loader");

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

    if (GetOpenFileNameW(&ofn) == TRUE)
    {
        // Имя выбранного файла находится в ofn.lpstrFile
        std::wstring filenameWStr = ofn.lpstrFile;
        std::string filename(filenameWStr.begin(), filenameWStr.end());
        std::cout << "Selected file: " << filename << std::endl;

        // Здесь можно продолжить обработку выбранного файла
        sf::Image image;
        char path[260];
        wcstombs(path, ofn.lpstrFile, sizeof(path));
        image.loadFromFile(path);

        char nameFile[260] = "";
        strcat(nameFile, path);
        strcat(nameFile, ".txt");
        FILE* file = fopen(nameFile, "w");

        int X_MAX = image.getSize().x;
        int Y_MAX = image.getSize().y;

        float max_brightness = Bribrightness(255, 255, 255);

        fseek(file, 0, SEEK_SET);

        // Определение массива символов градиента
char gradientChars[] = { ' ', '.', ':', '-', '=', '+', '*', '#', '%', '@', '$' };

for (int y = 0; y < Y_MAX; y++)
{
    for (int x = 0; x < X_MAX; x++)
    {
        sf::Color color = image.getPixel(x, y);

        int R = color.r;
        int G = color.g;
        int B = color.b;

        float brightness = Bribrightness(R, G, B);

        int pos = (brightness / max_brightness) * 10; // Диапазон от 0 до 10

        char asciiChar = gradientChars[pos]; // Выбор символа из массива

        fputc(asciiChar, file); // Запись символа в файл
    }

    fputc('\n', file);
}

        fclose(file);
        printf("OK");
        getchar();
    }
    else
    {
        std::cout << "No file selected." << std::endl;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}

float Bribrightness(int R, int G, int B)
{
    float brightness = 0.375 * R + 0.5 * G + 0.16 * B;

    return brightness;
} 