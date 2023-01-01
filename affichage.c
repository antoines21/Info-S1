#include <stdio.h>
#include "header.h"

void aff_plateau(struct s_partisan *plateau)
/*
Cette fonction affiche le tableau du jeu, la couleur change en fonction de l'orientation de la carte (en développement).
Pour la couleur :
- Joueur 1 (clan du haut) : Rouge
- Joueur 2 (clan du bas) : Vert
*/
{
    printf("\n");
    for (int i = 0; i < 9; i++)
    {
        printf("\033[%dm%d\033[0m", plateau[i].orientation + 40, plateau[i].personnage);
        if ((i + 1) % 3 == 0)
            printf("\n");
    }
    printf("\n");
}

void restant(struct s_joueur j)
/*
Cette fonction prends en paramètre une structure joueur, et affiche les cartes qui sont disponibles pour ce joueur.
La fonction regarde chaque case de la liste des cartes, et affiche en conséquence le nom de la carte correspondante.
Les 7 cartes ont leur place définies (index 0 à 6 dans la liste). Si la carte est disponible la case vaut 1, 0 sinon.
*/
{
    printf("Cartes disponibles pour le joueur %d : ", j.orientation);
    for (int i = 0; i < 7; i++)
    {
        if (j.cartes[i] == 1)
        {
            printf("\033[1;%dm", 30+i);
            switch (i)
            {
            case 0:
                printf("Citoyen ");
                break;

            case 1:
                printf("Roi ");
                break;

            case 2:
                printf("Reine ");
                break;

            case 3:
                printf("Princesse ");
                break;

            case 4:
                printf("Ministre ");
                break;

            case 5:
                printf("Général ");
                break;

            case 6:
                printf("Château ");
                break;

            default:
                break;
            }
            printf("\033[0m");
        }
    }
    printf("\n");
}

void restant_demande(struct s_joueur j)
/*
Cette fonction prends en paramètre une structure joueur, et affiche les cartes qui sont disponibles pour ce joueur.
La fonction regarde chaque case de la liste des cartes, et affiche en conséquence le nom de la carte correspondante.
Les 7 cartes ont leur place définies (index 0 à 6 dans la liste). Si la carte est disponible la case vaut 1, 0 sinon.
*/
{
    printf("Cartes disponibles pour le joueur %d : ", j.orientation);
    for (int i = 0; i < 7; i++)
    {
        if (j.cartes[i] == 1)
        {
            printf("\033[1;%dm%d ", 30+i,i+1);
            switch (i)
            {
            case 0:
                printf("Citoyen ");
                break;

            case 1:
                printf("Roi ");
                break;

            case 2:
                printf("Reine ");
                break;

            case 3:
                printf("Princesse ");
                break;

            case 4:
                printf("Ministre ");
                break;

            case 5:
                printf("Général ");
                break;

            case 6:
                printf("Château ");
                break;

            default:
                break;
            }
            printf("\033[0m");
        }
    }
    printf("\n");
}

void affichage_actions_possibles(int* tab, int carte)
/*
Cette fonction affiche les zones d'application possibles pour les pouvoirs des personnages.
*/
{
    int i;
    if (carte > 1 && carte < 9 && carte != 7)
    printf("Vous pouvez faire : ");
    for (i = 0; i < 17; i++)
    {
        if (tab[i] == 1)
        {
            switch (i)
            {
            case 0:
                printf("A1");
                break;

            case 1:
                printf("B1");
                break;

            case 2:
                printf("C1");
                break;

            case 3:
                printf("A2");
                break;

            case 4:
                printf("B2");
                break;

            case 5:
                printf("C2");
                break;

            case 6:
                printf("A3");
                break;

            case 7:
                printf("B3");
                break;

            case 8:
                printf("C3");
                break;

            case 9:
                printf("↑");
                break;

            case 10:
                printf("↗");
                break;

            case 11:
                printf("→");
                break;

            case 12:
                printf("↘");
                break;

            case 13:
                printf("↓");
                break;

            case 14:
                printf("↙");
                break;

            case 15:
                printf("←");
                break;

            case 16:
                printf("↖");
                break;

            default:
                break;
            }
            printf(" ");
        }
    }
    printf("\n");
}