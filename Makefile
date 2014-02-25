CC=gcc

main: main.c init_shader.h
	${CC} $< -lGL -lGLEW -lglut -g -o $@
