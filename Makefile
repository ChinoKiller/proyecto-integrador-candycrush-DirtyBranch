all:
	nasm -g -f elf64 -o ./build/MatrixFunc.o ./src/MatrixFunc.asm 
	g++ -c ./src/GameBoard.cpp -o ./build/GameBoard.o
	g++ -c ./src/Levels/PlanetLevel.cpp -o ./build/PlanetLevel.o
	g++ -c ./src/Levels/Level.cpp -o ./build/Level.o
	g++ -c ./src/Levels/SunLevel.cpp -o ./build/SunLevel.o
	g++ -c ./src/Levels/PlutonLevel.cpp -o ./build/PlutonLevel.o
	g++ -no-pie -o jugar ./src/main.cpp ./build/GameBoard.o ./build/MatrixFunc.o ./build/PlanetLevel.o ./build/Level.o ./build/SunLevel.o ./build/PlutonLevel.o -lsfml-graphics -lsfml-window -lsfml-system

run:
	nasm -g -f elf64 -o ./build/MatrixFunc.o ./src/MatrixFunc.asm 
	g++ -c ./src/GameBoard.cpp -o ./build/GameBoard.o
	g++ -c ./src/Levels/PlanetLevel.cpp -o ./build/PlanetLevel.o
	g++ -c ./src/Levels/Level.cpp -o ./build/Level.o
	g++ -c ./src/Levels/SunLevel.cpp -o ./build/SunLevel.o
	g++ -c ./src/Levels/PlutonLevel.cpp -o ./build/PlutonLevel.o
	g++ -no-pie -o ./bin/jugar ./src/main.cpp ./build/GameBoard.o ./build/MatrixFunc.o ./build/PlanetLevel.o ./build/Level.o ./build/SunLevel.o ./build/PlutonLevel.o
	./bin/jugar

gdb:
	gdb ./bin/jugar
