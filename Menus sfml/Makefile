all: compilador linker

compilador:
	g++ -c prueba.cpp

linker:
	g++ prueba.o -o a -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f prueba prueba.o a