# Ascii-studproj
1. Нужно подключить SFML 
2. Программа называется main.exe
3. Для того что запустить программу нужно создать файлы main.o и main.exe
    Необходимо создать терминал 
    Для создания файла main.o необходимо ввести команду в терминал: g++ -c main.cpp -I"C:\SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.1\include" -DSFML_STATIC
    Для создания файла main.exe необходимо ввести команду в терминал: g++ main.o -o main -L"C:\SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main
4. Для того чтобы изображение было переведено в ascii арт, нужно запустить приложение main.exe и выбрать пункт "1. Convert images to ASCII art". После этого откроется окно, где можно выбрать изображение, ascii арт данного  изображения будет помещён в эту же папку и мнгновенно открыт на экране в виде txt файла
5. Для того чтобы перевести текст в ascii art нужно нажать на кнопку "2. Print words in ASCII code" и далее откроется окно. Печатать слова нужно строго на английском языке.