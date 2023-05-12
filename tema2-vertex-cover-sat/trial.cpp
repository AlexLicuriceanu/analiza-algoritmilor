#include <stdio.h>
#include "task.h"

int calculate_third_parameter_for_sat(int M) {

   int param = 1;

   for (int i = 0; i < M; i++) {
      param *= (param + 1);
      param ++;
   }

   return param;
}

int main( ) {

   int N, M, K;
   int *size_of_packet;
   int **packets;
      
   /* Citim inputul si alocam un vector in care retinem dimensiunile pachetelor
   si o matrice in care memoram fiecare pachet */ 
   
   scanf("%d %d %d\n", &N, &M, &K);

   packets = (int **) calloc(M, sizeof(int *));
   size_of_packet = (int *) calloc(M, sizeof(int));

   for (int i = 0; i < M; i++) {

      scanf("%d", &size_of_packet[i]);
      packets[i] = (int *) calloc(size_of_packet[i], sizeof(int));

      for (int j = 0; j < size_of_packet[i]; j++) {

         scanf("%d",  &packets[i][j]);
      }
   }   

   /* Deschidem fisierul in care pregatim inputul pentru oracol */

   FILE *fin;
   fin = fopen("sat.cnf","w");

   fprintf(fin, "p cnf %d %d\n", M*K, calculate_third_parameter_for_sat(M) + M);
   
   /* Primele clauze ce reprezinta M*K numere crescatoare impartite in K linii */

   int i = 0;

   while (i < K) {

      for (int j = 1; j <= M; j++) {
         fprintf(fin, "%d ", i*M + j);
      }
      fprintf(fin, "0\n");
      i++;
   }

   /* Urmatoarele sunt grupuri de cate 2 numere negate ce reies din combinatiile de pe liniile
   matricei anterioare formate de clauzele enumerate mai sus */

   for (int i = 0; i < K; i++) {

      for (int j = 0; j < M - 1; j++) {

         for (int k = j + 1; k < M; k++) {

            fprintf(fin, "%d %d 0\n", -(i*M + j + 1), -(i*M + k + 1));
            
         }
      }
   }

   /* Se trece prin fiecare nod si se verifica in care dintre pachete se afla
   Cand este gasit indicele pachetului corespunzator se printeaza coloane reprezentativa matricei
   initiale formate din clauzele enumerate primele */

   int node = 1;
   
   while (node <= N) {

      for (int line = 0; line < M; line++) {

         for (int column = 0; column < size_of_packet[line]; column++) {

            if (node == packets[line][column]) {

               for(int i = line + 1; i <= M*K; i+= M) {
                  fprintf(fin, "%d ", i);
               }
            }
         }
      }
      fprintf(fin, "0\n");
      node ++;
   }

   fclose(fin);

   /* Apelam oracolul pentru a primi rezultatul de la sat solver */

   Task o;
   o.ask_oracle();

   FILE *fout;
   fout = fopen("sat.sol","r");

   char response[5];
   int response_sat;

   fscanf(fout, "%s", response);
   printf("%s\n", response);

   /* Pentru un raspuns "True" al oracolului verificam care dintre numerele intoarse nu este negat
   In acest caz se gaseste indicele coloanei pe care se afla in matricea initiala, astfel ca el
   reprezinta, de fapt, numarul pachetului de care avem nevoie */

   if(strcmp(response, "True") == 0) {
      
      printf("%d\n", K);
      fscanf(fout, "%d", &N);

      for (int i = 0; i < M*K; i++) {

         fscanf(fout, "%d", &response_sat);

         if (response_sat > 0) {
            printf("%d ", (i % M) + 1);
         }
      }
   }

   fclose(fout);

   /* Eliberam memoria alocata dinamic */

   for (int i = 0; i < M; i++) {
      free (packets[i]);
   }
   free (packets);
   free (size_of_packet);

   return 0;
}