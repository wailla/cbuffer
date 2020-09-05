main.exe: main.o exeption.o
	g++ main.o exeption.o -o main.exe

main.o: main.cpp cbufferlist.h exeptionBuffer.h
	g++ -c -std=c++0x main.cpp -o main.o

exeption.o: exeption.cpp exeptionBuffer.h
	g++ -c -std=c++0x exeption.cpp -o exeption.o

.PHONY: clean

clean:
	rm *.exe *.o
