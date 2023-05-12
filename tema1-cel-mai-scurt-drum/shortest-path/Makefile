CC = g++
CFLAGS = -WALL

build: dijkstra.o bellman-ford.o floyd-warshall.o 

p1: dijkstra.cpp tester.cpp utils.h
	$(CC) dijkstra.cpp tester.cpp -o dijkstra
	
p2: bellman-ford.cpp tester.cpp utils.h
	$(CC) bellman-ford.cpp tester.cpp -o bellman-ford
	
p3: floyd-warshall.cpp tester.cpp utils.h
	$(CC) floyd-warshall.cpp tester.cpp -o floyd-warshall

best: dijkstra.cpp tester.cpp utils.h
	$(CC) dijkstra.cpp tester.cpp -o dijkstra
	
run-p1:
	./dijkstra

run-p2:
	./bellman-ford
	
run-p3:
	./floyd-warshall
	
run-best:
	./dijkstra
	
generator: generator.cpp floyd-warshall.cpp utils.h
	$(CC) generator.cpp floyd-warshall.cpp -o generator
	
.PHONY: clean
clean:
	rm -rf *.o dijkstra bellman-ford floyd-warshall generator
