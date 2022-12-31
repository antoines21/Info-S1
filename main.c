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
    debut(plateau, joueur_1, joueur_2);
    return 0;
}