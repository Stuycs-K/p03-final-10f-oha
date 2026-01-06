.PHONY: compile run clean
compile: main.o editor.o
	@gcc -o runme main.o editor.o -lncurses
run: runme
	@./runme $(ARGS)
main.o: main.c editor.h
	@gcc -c main.c
editor.o: editor.c
	@gcc -c editor.c
clean:
	rm -f *.o
	rm -f runme
