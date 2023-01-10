all:
		gcc client.c -o client.o
		gcc server.c -o server.o

server:
		gcc server.c -o server.o

client:
		gcc client.c -o client.o