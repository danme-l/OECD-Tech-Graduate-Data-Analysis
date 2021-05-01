main: main.o util.o init.o calc.o reports.o cleanUp.o
	gcc -o main main.o util.o init.o calc.o reports.o cleanUp.o

main.o: main.c defs.h
	gcc -c main.c

util.o: util.c defs.h
	gcc -c util.c

init.o: init.c defs.h
	gcc -c init.c

calc.o: calc.c defs.h
	gcc -c calc.c

reports.o: reports.c defs.h
	gcc -c reports.c 

cleanUp.o: cleanUp.c defs.h
	gcc -c cleanUp.c

clean:
	rm -f *.o main