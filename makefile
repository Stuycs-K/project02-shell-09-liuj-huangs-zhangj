.PHONY: compile clean run
compile: shell.o execute.o input.o path.o redirect.o
	@gcc -o shell shell.o execute.o input.o path.o redirect.o
shell.o: shell.c
	@gcc -c shell.c -Wall
execute.o: execute.c redirect.o
	@gcc -c execute.c -Wall
redirect.o: redirect.c
	@gcc -c redirect.c -Wall
input.o: input.c
	@gcc -c input.c -Wall
path.o: path.c
	@gcc -c path.c -Wall
run:
	@./shell
clean:
	@rm -f *.o shell
