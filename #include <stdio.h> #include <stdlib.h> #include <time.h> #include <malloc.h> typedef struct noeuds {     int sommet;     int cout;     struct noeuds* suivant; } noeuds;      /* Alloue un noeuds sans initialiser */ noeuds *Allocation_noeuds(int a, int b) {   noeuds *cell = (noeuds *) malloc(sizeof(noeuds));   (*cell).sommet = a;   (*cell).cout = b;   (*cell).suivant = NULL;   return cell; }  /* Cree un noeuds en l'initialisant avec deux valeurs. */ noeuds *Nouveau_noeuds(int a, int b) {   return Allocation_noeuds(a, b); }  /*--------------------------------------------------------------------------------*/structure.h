#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
typedef struct noeuds {
    int sommet;
    int cout;
    struct noeuds* suivant;
} noeuds;





/* Alloue un noeuds sans initialiser */
noeuds *Allocation_noeuds(int a, int b)
{
  noeuds *cell = (noeuds *) malloc(sizeof(noeuds));
  (*cell).sommet = a;
  (*cell).cout = b;
  (*cell).suivant = NULL;
  return cell;
}

/* Cree un noeuds en l'initialisant avec deux valeurs. */
noeuds *Nouveau_noeuds(int a, int b)
{
  return Allocation_noeuds(a, b);
}

/*--------------------------------------------------------------------------------*/

struct noeuds* init(int size) {
    struct noeuds* graphe = malloc(size * sizeof(struct noeuds));
    int i;
    for (i = 0; i < size; i++) {
        graphe[i].sommet = i;
        graphe[i].cout = 0;
        graphe[i].suivant = NULL;
    }
    return graphe;
}

void insertion(struct noeuds* graphe, int sommet, int adjacent, int cout) {
    struct noeuds* new_node = malloc(sizeof(struct noeuds));
    new_node->sommet = adjacent;
    new_node->cout = cout;
    new_node->suivant = graphe[sommet].suivant;
    graphe[sommet].suivant = new_node;
}

void afficherListe(struct noeuds* graphe, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d -> ", i);
        struct noeuds* c = graphe[i].suivant;
        while (c != NULL) {
            printf("%d -> ", c->sommet);
            c = c->suivant;
        }
        printf("NULL\n");
    }
}
