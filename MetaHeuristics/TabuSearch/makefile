all: TS

TS: main.o EvaluateQAP.o list.o tabu_search.o RandomPerm.o
	gcc -O2 main.o EvaluateQAP.o list.o tabu_search.o RandomPerm.o -o TS -lm

main.o: main.c
	gcc -c main.c

EvaluateQAP.o: EvaluateQAP.c
	gcc -c EvaluateQAP.c

list.o: list.c
	gcc -c list.c

tabu_search.o: tabu_search.c
	gcc -c tabu_search.c

RandomPerm.o: RandomPerm.c
	gcc -c RandomPerm.c

clean:
	rm -rf *o TS
