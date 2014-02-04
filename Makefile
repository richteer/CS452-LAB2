CC=gcc

main: main.c
	${CC} $< -lGL -lGLEW -lglut -g -o $@
