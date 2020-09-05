
main.exe: main.o
	g++ main.o -o main.exe

main.o: main.cpp cbufferlist.h exeptionBuffer.h
	g++ -c -std=c++0x main.cpp -o main.o

exeptionBuffer.o: exeption.cpp exeptionBuffer.h
	g++ -c -std=c++0x exeption.cpp -o exeptionBuffer.o

.PHONY: clean

clean:
	rm *.exe *.o
