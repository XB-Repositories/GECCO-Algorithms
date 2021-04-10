all: VFS

VFS: main.o EvaluateQAP.o list.o VFS.o RandomPerm.o
	gcc -O2 main.o EvaluateQAP.o list.o VFS.o RandomPerm.o -o VFS -lm

main.o: main.c
	gcc -c main.c

EvaluateQAP.o: EvaluateQAP.c
	gcc -c EvaluateQAP.c

list.o: list.c
	gcc -c list.c

VFS.o: VFS.c
	gcc -c VFS.c

RandomPerm.o: RandomPerm.c
	gcc -c RandomPerm.c

clean:
	rm -rf *o VFS
