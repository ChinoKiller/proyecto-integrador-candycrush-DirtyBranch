all:
	nasm -g -f elf64 -o ./build/MatrixFunc.o ./src/MatrixFunc.asm 
	g++ -c ./src/GameBoard.cpp -o ./build/GameBoard.o
	g++ -c ./src/Levels/Level.cpp -o ./build/Level.o
	g++ -c ./src/Controlador.cpp -o ./build/Controlador.o
	g++ -no-pie -o ./bin/jugar ./build/Controlador.o ./src/main.cpp ./build/GameBoard.o ./build/MatrixFunc.o ./build/Level.o -lsfml-graphics -lsfml-window -lsfml-system

run:
	nasm -g -f elf64 -o ./build/MatrixFunc.o ./src/MatrixFunc.asm 
	g++ -c ./src/GameBoard.cpp -o ./build/GameBoard.o
	g++ -c ./src/Levels/Level.cpp -o ./build/Level.o
	g++ -c ./src/Controlador.cpp -o ./build/Controlador.o
	g++ -no-pie -o ./bin/jugar ./build/Controlador.o ./src/main.cpp ./build/GameBoard.o ./build/MatrixFunc.o ./build/Level.o -lsfml-graphics -lsfml-window -lsfml-system
	./bin/jugar
