#include "header.h"
#include <stdio.h>

int main(void)
{
    int i;
    struct s_joueur joueur_1, joueur_2;            // Création des 2 joueurs
    joueur_1.orientation = 1;
    joueur_2.orientation = 2;
    for (i = 0; i < 7; joueur_1.cartes[i++] = 1); // Remplissage des paquets de carte
    for (i = 0; i < 7; joueur_2.cartes[i++] = 1); // Remplissage des paquets de carte
    struct s_partisan plateau[8];                 // Représente le plateau de 9 cases
    for (i = 0; i < 9; i ++){
        plateau[i].orientation = 0;
        plateau[i].personnage = 0;
        }
    
    // Début du jeu

    printf("┌───────────────────┐\n│    \033[1;5mDÉBUT DU JEU\033[0m   │▒\n│ \033[3mLuttes de pouvoir\033[0m │▒\n└───────────────────┘▒\n ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n");

    i = 0;
    do
    {
        printf("\n\033[44mTour %d\033[0m \033[%dmJoueur %d\033[0m\n", i + 1, 40 + i % 2 + 1, i % 2 + 1); // Affichage n°tour et n°joueur
        aff_plateau(plateau);
        if (i != 0)
        {
            i % 2 + 1 == 1 ? place_carte(plateau, &joueur_1, choix_emplacement(plateau), choix_personnage(joueur_1)) : place_carte(plateau, &joueur_2, choix_emplacement(plateau), choix_personnage(joueur_2));
        }
        else
        {
            printf("Le joueur 1 pose la carte citoyen (le citoyen n'a pas de pouvoir).\n");
            place_carte(plateau, &joueur_1, choix_emplacement(plateau), 1);
        }
        i++;
    } while (est_plein(plateau) != 1);
    aff_plateau(plateau);
    int gagnant = joueur_gagnant(plateau);
    printf("┌───────────────────┐\n│      \033[1;5mGAGNANT\033[0m      │▒\n│     \033[%dmJoueur %d\033[0m      │▒\n└───────────────────┘▒\n ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n", 40 + gagnant, gagnant);

    return 0;
}