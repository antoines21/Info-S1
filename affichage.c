#include <stdio.h>
#include "header.h"

void grille(int *tab, int *a)
{
    /*
    for (int i = 0; i < 18; i++)
    {
        printf("%d\n", tab[i]);
    }
    */
   *a = 2;

}

void gril(struct s_partisan x)
{
    printf("L'all est : %d\n", x.orientation);
}

void aff_plateau(struct s_partisan *plateau)
/*
Cette fonction affiche le tableau du jeu, la couleur change en fonction de l'orientation de la carte (en développement).
Pour la couleur :
- Joueur 1 (clan du haut) : Rouge
- Joueur 2 (clan du bas) : Vert
*/
{

    for (int i = 0; i < 9; i++)
    {
        printf("\033[%dm%d\033[0m", plateau[i].orientation + 40, plateau[i].tuile);
        if ((i + 1) % 3 == 0)
            printf("\n");
    }
}

void restant(int *liste)
/*
Cette prends en paramètre la liste des cartes du joueur, et indique lesquelles sont disponibles.
La fonction regarde chaque case de la liste, et affiche en conséquence le nom de la carte correspondante.
Les 7 cartes ont leur place (index 0 à 6 dans la liste). Si la carte est disponible la case vaut 1, 0 sinon.
*/
{
    for (int i = 0; i < 7; i++)
    {
        if (liste[i] == 1)
        {
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
        }
    }
    printf("\n");
}