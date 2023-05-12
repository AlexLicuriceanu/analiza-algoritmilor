Nume: Alexandru Licuriceanu
Grupa: 325CD

# Tema 1 - Cel mai scurt drum intr-un graf (2)

Organizarea fisierelor
-

* ./in: \
	Folder cu fisierele de test.

* ./out: \
	Folder cu fisierele de referinta.
	
* ./tester-out \
	Folder in care se vor afla fisiere rezultate dupa rularea unei comenzi de run:
	`make run-p1`, `make run-p2`, `make run-p3` sau `make run-best`.

* generator.cpp:  \
	Un program care genereaza seturi de test pentru grafuri care au diferite proprietati.
	Se poate specifica daca sa se genereze si costuri negative, daca graful este orientat
	sau neorientat si se poate alege numarul minim si maxim de noduri, de muchii si
	intervalul in care sa se genereze costurile. 
	
* tester.cpp: \
	Un program cu care se testeaza viteza algoritmilor de gasire a costului minim. Fiecare
	dintre cei 3 algoritmi se pot rula fie cu un argument care reprezinta un nume de fisier
	din directorul din care se ruleaza, fie fara argumente, caz in care se ruleaza toate
	testele din directorul ./in, cu rezultatele in directorul ./out. Cand se ruleaza cu un
	singur fisier de test, rezultatul se va afla intr-un fisier numit "test.out" in radacina
	directorului din care se ruleaza algoritmul.
	
* dijkstra.cpp[^1] \
	O implementare a algoritmului lui Dijkstra folosind o matrice de adiacenta. Se putea de
	asemenea implementa folosind o coada de prioritati minime, insa nu ar fi influentat cu
	mult timpul de rulare, iar tinand cont ca este mai rapid decat ceilalti algoritmi chiar
	si asa, cu matricea de adiacenta, am hotarat sa aleg aceasta implementare pentru simplitate.
	
* bellman-ford.cpp[^2] \
	Implementarea algoritmului Bellman-Ford, usor modificata pentru a putea functiona cu numere
	mai mari decat maximul unui int.
	
* floyd-warshall.cpp[^3] \
	Implementarea algoritmului Floyd-Warshall, usor modificata pentru a putea functiona cu numere
	mai mari decat maximul unui int.
	
* Makefile \
	Makefile-ul proiectului, are mai multe reguli, dintre care:
	* `build` - genereaza fisierele obiect.
	* `p1, p2, p3` - genereaza executabilele pentru Dijkstra, Bellman-Ford sau Floyd-Warshall.
	* `best` - genereaza executabilul pentru Dijkstra.
	* `run-p1` - ruleaza Dijkstra pentru toate seturile de test din ./in
	* `run-p2` - ruleaza Bellman-Ford pentru toate seturile de test din ./in
	* `run-p3` - ruleaza Floyd-Warshall pentru toate seturile de test din ./in
	* `generator` - genereaza executabilul pentru generator.
	* `clean` - sterge toate fisierle generate anterior.
	Atunci cand sunt rulate `make run-p1`, `make run-p2` sau `make run-p3`, fisierele cu rezultatele
	se vor gasi in directorul ./tester-out.
	
Utilizare
-

* p1: Dijsktra
* p2: Bellman-Ford
* p3: Floyd-Warshall
* best: Dijkstra

Fiecarui program ii este asociata o regula de run in makefile. Cand se executa o comanda de tipul
`make run`, se va rula algoritmul specificat pe toate seturile de test. Pentru a rula doar pentru
un fisier de test, se ruleaze `make <p1/p2/p3>` in functie de ce algoritm se testeaza. Comanda va
genera un executabil cu algoritmul dorit. Pentru a rula un singur fisier de test, se executa comanda
`./<nume-algoritm> <nume-fisier>`. Daca nu este primit niciun argument in locul numelui de fisier,
vor rula toate testele. De exmplu am un fisier test5.in in directorul principal si vreau sa rulez
algoritmul Dijkstra pe acesta. Trebuie sa execut urmatoarele comenzi:
	
	make clean
	make p1
	./dijkstra test5.in
	
Output-ul algoritmului se va gasi intr-un fisier numit test.out din radacina directorului din care
s-a executat comanda.

Referinte

[^1]: Algoritmul Dijkstra: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/

[^2]: Algoritmul Bellman-Ford:
https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/

[^3]: Algoritmul Floyd-Warshall
https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/
	
