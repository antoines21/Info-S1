#include "header.h"
#include <stdio.h>

int main(void)
{
    int i;
    struct s_joueur joueur_1, joueur_2;                // Création des 2 joueurs
    joueur_1.orientation = 1;
    joueur_2.orientation = 2;
    for (i = 0; i < 7; joueur_1.cartes[i++] = 1); // Remplissage des paquets de carte
    for (i = 0; i < 7; joueur_2.cartes[i++] = 1); // Remplissage des paquets de carte
    struct s_partisan plateau[8];            // Représente le plateau de 9 cases

    
    debut(plateau, joueur_1, joueur_2);
    // aff_plateau(plateau);

    /* Pour avoir toutes les couleurs (carctère d'échapement)
    int i, j, n;

    for (i = 0; i < 11; i++)
    {
        for (j = 0; j < 10; j++)
        {
            n = 10 * i + j;
            if (n > 108)
                break;
            printf("\033[%dm %3d\033[m", n, n);
        }
        printf("\n");
    }
    */

    // plateau[1].tuile = 6;
    // plateau[5].tuile = 4;
    // aff_tableau(plateau);

    // plateau[1].orientation = 1;

    // printf("La valeur est %d\n", plateau[1].tuile);
    // int a = emplacement(plateau);
    // printf("Le nombres est : %d\n", a);
    return 0;
}