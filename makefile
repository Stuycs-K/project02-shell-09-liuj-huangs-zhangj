.PHONY: compile clean run
compile: shell.o
	@gcc -o shell shell.o
shell.o: shell.c
	@gcc -c shell.c -Wall
run:
	@./shell
clean:
	@rm -f *.o shell
