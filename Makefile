# Compiler
cc=gcc

all: compile

compile: main.c
	    $(cc) -o main main.c

clean:
	rm main
