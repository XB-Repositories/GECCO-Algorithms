all: CalculateLO

CalculateLO: main.o EvaluateQAP.o local_search.o RandomPerm.o
	gcc -O2 main.o EvaluateQAP.o local_search.o RandomPerm.o -o CalculateLO -lm

main.o: main.c
	gcc -c main.c

EvaluateQAP.o: EvaluateQAP.c
	gcc -c EvaluateQAP.c

local_search.o: local_search.c
	gcc -c local_search.c

RandomPerm.o: RandomPerm.c
	gcc -c RandomPerm.c

clean:
	rm -rf *o CalculateLO
