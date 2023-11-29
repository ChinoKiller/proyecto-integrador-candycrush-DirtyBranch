all: compilador linker

compilador:
	g++ -c main.cpp

linker:
	g++ main.o -o a -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f main main.o a