bin/programa : src/main.cpp include/Foco.hpp include/EstadoFoco.hpp
	c++ src/main.cpp -o bin/programa -I include

run : bin/programa
	./bin/programa

bin/memoria : src/memoria.cpp
	c++ src/memoria.cpp -o bin/memoria

runMemoria : bin/memoria
	./bin/memoria

bin/ejemplo : src/ejemplo.cpp
	c++ src/ejemplo.cpp -o bin/ejemplo -lftxui-screen -lftxui-dom -lftxui-component

runEjemplo : bin/ejemplo
	./bin/ejemplo

bin/examen : src/examen.cpp
	mkdir -p bin
	c++ -std=c++17 -Iinclude src/examen.cpp -o bin/examen -lftxui-screen -lftxui-dom -lftxui-component -pthread
	
runExamen : bin/examen
	./bin/examen