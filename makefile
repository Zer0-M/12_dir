all: main.o
	gcc -o ls_test  main.o

main.o: main.c
	gcc -c -g main.c

run: 
	./ls_test

clean:
	rm *.o
	rm ./ls_test
