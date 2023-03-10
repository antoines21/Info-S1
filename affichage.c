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
    printf("\n        A         B         C\n   ┌─────────┬─────────┬─────────┐\n 1 ");
    for (int i = 0; i < 9; i++)
    {
        printf("│");
        if (plateau[i].orientation == 1 || plateau[i].orientation == 2)
            printf("\033[%dm", plateau[i].orientation + 40);
        switch (plateau[i].personnage)
        {
        case 1:
            printf(" Citoyen ");
            break;

        case 2:
            printf("   Roi   ");
            break;

        case 3:
            printf("  Reine  ");
            break;

        case 4:
            printf("Princesse");
            break;

        case 5:
            printf("Ministre ");
            break;

        case 6:
            printf(" Général ");
            break;

        case 7:
            printf(" Château ");
            break;

        default:
            printf("         ");
            break;
        }
        printf("\033[0m");
        if ((i + 1) % 3 == 0 && i != 8)
            printf("│▒\n   ├─────────┼─────────┼─────────┤▒\n %d ", i % 2 + 2);
    }
    printf("│▒\n   └─────────┴─────────┴─────────┘▒\n    ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n\n");
}

void restant_demande(struct s_joueur j)
/*
Cette fonction prends en paramètre une structure joueur, et affiche les cartes qui sont disponibles pour ce joueur.
La fonction regarde chaque case de la liste des cartes, et affiche en conséquence le nom de la carte correspondante.
Les 7 cartes ont leur place définies (index 0 à 6 dans la liste). Si la carte est disponible la case vaut 1, 0 sinon.
*/
{
    printf("Cartes disponibles pour le joueur %d : \n\n", j.orientation);
    for (int i = 0; i < 7; i++)
    {
        if (j.cartes[i] == 1)
        {
            printf("\033[1;%dm[%d] ", i == 0 ? 37 : 30 + i, i + 1);
            switch (i)
            {
            case 0:
                printf("Citoyen : Aucun pouvoir\n");
                break;

            case 1:
                printf("Roi : Détruit une des tuiles orthogonales ou diagonalement adjacentes\n");
                break;

            case 2:
                printf("Reine : Pivote toutes les cartes présentes dans l'une des directions autour d'elle\n");
                break;

            case 3:
                printf("Princesse : Pivote les 4 tuiles orthogonalement ou diagonalement adjacentes\n");
                break;

            case 4:
                printf("Ministre : Pivote une des tuiles orthogonales ou diagonalement adjacentes\n");
                break;

            case 5:
                printf("Général : Détruit l'une des 4 tuiles qui lui sont orthogonalement adjacentes\n");
                break;

            case 6:
                printf("Château : Immunisé contre les autres effets\n");
                break;

            default:
                break;
            }
            printf("\033[0m");
        }
    }
    printf("\n");
}

void affichage_actions_possibles(int *tab, int carte)
/*
Cette fonction affiche les zones d'application possibles pour les pouvoirs des personnages.
Les personnages qui demandent une une case ou une direction en fonction de la case sur lequels ils ont été posé sont :
2 - Roi
3 - Reine
5 - Ministre
6 - Général
*/
{

    int i;
    printf("Vous pouvez appliquer votre pouvoir sur l'une des cases suivantes : ");
    printf("\n");
    for (i = 0; i < 17; i++)
    {
        if (tab[i] == 1)
        {
            printf("\033[1;37m[");
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
                printf("%d ↑", i - 8);
                break;

            case 10:
                printf("%d ↗", i - 8);
                break;

            case 11:
                printf("%d →", i - 8);
                break;

            case 12:
                printf("%d ↘", i - 8);
                break;

            case 13:
                printf("%d ↓", i - 8);
                break;

            case 14:
                printf("%d ↙", i - 8);
                break;

            case 15:
                printf("%d ←", i - 8);
                break;

            case 16:
                printf("%d ↖", i - 8);
                break;

            default:
                break;
            }
            printf("]\033[0m ");
        }
    }

    printf("\n");
}