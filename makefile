.PHONY: compile clean run
compile: main.o
	@gcc -o main main.o
main.o: main.c
	@gcc -c main.c -Wall
run:
	@./main
clean:
	@rm -f *.o main
