#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> // for gettimeofday
#include <malloc.h>
#include "structures.h"

#define ERR_MALLOC 1
#define MAXINT 1000
#define STARTING_VERTEX -1


int* Distance;
int* queue;
int* ordre;
int* explore;
int* C;
FILE *output_file;

void initialisation(int *Tableau, int M) {
    int i;
    for (i = 0; i < M; i++) {
        Tableau[i] = 0;
    }
}

void saisie(int *Tableau, int M, int val) {
    int i;
    for (i = 0; i < M; i++) {
        Tableau[i] = val;
       }
}

void saisir(int *Tableau, int M) {
    int i;
    for (i = 0; i < M; i++) {
        Tableau[i] = i;
    }
}

void Inversion(int i, int j, int *Distance, int *ordre, int *explore, int *queue, int *C) {
	int tmp;
	  ordre[queue[i]] = j; ordre[queue[j]] = i;
	  tmp = queue[i];
	  queue[i] = queue[j];
	  queue[j] = tmp;
 }

void Inversion_fils(int longueur, int i, int M, int *Distance, int *ordre, int *explore, int *queue, int *C) {
    int fils = 2 * i + 1;
    if (fils >= longueur) {
        return;
    }
    if ((fils < longueur - 1) && (Distance[queue[fils]] > Distance[queue[fils + 1]])) {
        fils = fils + 1;
    }
    if (Distance[queue[i]] > Distance[queue[fils]]) {
        Inversion(i, fils, Distance, ordre, explore, queue, C);
        Inversion_fils(longueur, fils, M, Distance, ordre, explore, queue, C);
    }
   
}

void Inversion_pere(int longueur, int i, int M, int *Distance, int *ordre, int *explore, int *queue, int *C) {
    int pere = (i - 1) / 2;
    if (Distance[queue[i]] < Distance[queue[pere]]) {
        Inversion(pere, i, Distance, ordre, explore, queue, C);
        Inversion_pere(longueur, pere, M, Distance, ordre, explore, queue, C);
    }

}

int minimum(int longueur, int M, int *Distance, int *ordre, int *explore, int *queue, int *C) {
    int tmp = queue[0];
    explore[tmp] = 1;

    if (longueur > 1) {
        Inversion(0, longueur - 1, Distance, ordre, explore, queue, C);
        Inversion_fils(longueur - 1, 0, M, Distance, ordre, explore, queue, C);
    }

    return tmp;
}

int prim_iteration(int longueur, int M, int *Distance, int *ordre, int *explore, int *queue, int *C, struct noeuds *graphe) {
	int i;
    int tmp = minimum(longueur, M, Distance, ordre, explore, queue, C);
    int j;
    struct noeuds *c;
    for (c = graphe[tmp].suivant; c != NULL; c = c->suivant) {
    j = c->sommet;
    if ((explore[j] == 0) && (c->cout < Distance[j])) {
        Distance[j] = c->cout;
        C[j] = tmp;
        Inversion_pere(longueur - 1, ordre[j], M, Distance, ordre, explore, queue, C);
    }
  
}


    return 0;
}

int prim(int M, int *Distance, int *ordre, int *explore, int *queue, int *C, struct noeuds *graphe) {
    int i;
    for (i = M; i > 0; i--) {
        prim_iteration(i, M, Distance, ordre, explore, queue, C, graphe);
    }
    return 0;
}


void Symetrie_graphe(int M, struct noeuds *graphe) {
    int i, j;
    struct noeuds *u, *c;

    for (i = M - 1; i >= 0; i--) {
        for (c = graphe[i].suivant; c != NULL; c = c->suivant) {
            j = c->sommet;
            u = Nouveau_noeuds(i, c->cout);
            u->suivant = graphe[j].suivant;
            graphe[j].suivant = u;
        }
    }
}

int main(int argc, char *argv[])  {
int i;

if (argc != 2) {
   printf("Usage: %s <size>\n", argv[0]);
   return 1;
}

int num_executions=5; // Nombre d'exécutions à effectuer
int *execution_times = malloc(num_executions * sizeof(int));
if (execution_times == NULL) {
    exit(EXIT_FAILURE);}
initialisation(execution_times, num_executions);
output_file = fopen("execution_times.txt", "a");

if (output_file == NULL) {
    printf("Erreur lors de l'ouverture du fichier.\n");
    return 1;
}
int size = atoi(argv[1]);
printf("le problème va tourner sur %d execution\n ",num_executions);
for (int k = 0; k < num_executions; k++) {
	struct timeval start, end;
    
    // Start time
    	gettimeofday(&start, NULL);// Enregistre le temps au début de l'exécution
	int cout_total = 0;
	Distance = malloc(size * sizeof(int));
	queue = malloc(size * sizeof(int));
	ordre = malloc(size * sizeof(int));
	explore = malloc(size * sizeof(int));
	C = malloc(size * sizeof(int));
	if (Distance == NULL || queue == NULL || ordre == NULL || explore == NULL || C == NULL) {
		exit(EXIT_FAILURE);
	 }
	initialisation(Distance, size);
	initialisation(queue, size);
	initialisation(ordre, size);
	initialisation(explore, size);
	initialisation(C, size);
	saisie(Distance, size, MAXINT);
	saisir(queue, size);
	saisir(ordre, size);
        saisie(explore, size, 0);
	saisie(C, size, 0);
        Distance[0] = 0;
	C[0] = -1;
		struct noeuds* graphe = init(size);
	for (i = 0; i < size; i++) {
		insertion(graphe, i, (i + 1) % size, rand() % 11); // Ajoute une arête entre i et (i + 1) % size avec un coût aléatoire entre 0 et 10
	}


	afficherListe(graphe, size);




	
	if (C == NULL) {
	    exit(EXIT_FAILURE);
	}



	
	 Symetrie_graphe(size, graphe);
	 
	 prim(size, Distance, ordre, explore, queue, C, graphe);
	

	 for (i = 0; i < size; i++) {
		printf("%d\n", Distance[i]);
		cout_total = cout_total + Distance[i];
		printf("arete %d %d, cout %d\n", i, C[i], Distance[i]);
	 }
	 printf("cout total %d\n", cout_total);

	    free(Distance);
	    free(queue);
	    free(ordre);
	    free(explore);
	    free(C);
	    
          gettimeofday(&end, NULL);
    
	    // Calculate execution time in microseconds
	    long seconds = end.tv_sec - start.tv_sec;
	    long microseconds = end.tv_usec - start.tv_usec;
	    double execution_time = seconds + microseconds / 1000000.0;

	    // Print execution time
	    printf("Temps d'exécution : %.6f secondes\n", execution_time);
	    execution_times[k] = execution_time;
           fprintf(output_file, "%.6f\n", execution_time);
           fclose(output_file);
           
          
}

output_file = fopen("execution_times.txt", "a");
if (output_file == NULL) {
    printf("Erreur lors de l'ouverture du fichier.\n");
    return 1;
}

free(execution_times);
    return 0;
}
