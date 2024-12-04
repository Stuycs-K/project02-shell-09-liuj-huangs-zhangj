.PHONY: compile clean run
compile: shell.o execute.o input.o path.o
	@gcc -o shell shell.o execute.o input.o path.o
shell.o: shell.c
	@gcc -c shell.c -Wall
execute.o: execute.c
	@gcc -c execute.c -Wall
input.o: input.c
	@gcc -c input.c -Wall
path.o: path.c
	@gcc -c path.c -Wall
run:
	@./shell
clean:
	@rm -f *.o shell
