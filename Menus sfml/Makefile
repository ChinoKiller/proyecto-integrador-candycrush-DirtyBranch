all: compilador linker

compilador:
	g++ -c Menus.cpp

linker:
	g++ Menus.o -o a -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f Menus Menus.o a