all: compile link

compile: 
	g++ -c main.cpp -I"C:\SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.1\include" -DSFML_STATIC

link:
	g++ main.o -o main -L"C:\SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

clean:
	rm -f main *.o
