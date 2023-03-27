all: compile
compile:
	gcc -o kmeans ./src/main.c -lm
	./kmeans
