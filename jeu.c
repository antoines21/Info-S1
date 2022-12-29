#include <stdio.h>
#include <string.h>
#include "header.h"

void debut(struct s_partisan *plateau, struct s_joueur j_1, struct s_joueur j_2)
/*
Cette fonction prends en paramètre le plateau de jeu, et les deux listes correspondants au carte des joueurs.
Elle commence une partie du jeu. Le premier joueur place une carte citoyen au premier tour.
*/
{
    printf("Plateau initial :\n");
    aff_plateau(plateau);
    printf("Le joueur 1 commence à jouer.\n");
    printf("Voici les cartes disponibles du joueur 1 : ");
    restant(j_1.cartes);
    int a = emplacement(plateau);
    place_carte(plateau, &j_1, a, 1);
    aff_plateau(plateau);
    printf("Voici les cartes disponibles du joueur 1 : ");
    restant(j_1.cartes);
    //int z = choix_personnage(joueur1);
}

void place_carte(struct s_partisan *plateau, struct s_joueur *joueur, int emplacement, int carte)
/*
Cette fonction prends en paramètre :
- Le plateau du jeu
- L joueur correspondant
- L'emplacement de la carte à placer (format numérique)
- Le numéro de la carte à placer (1 à 7)
Et fait les actions suivantes :
- Place la bonne carte sur le plateau de jeu, avec la bonne orientation
- Enlève la carte correspondante dans la liste de cartes du joueur.
*/
{
    plateau[emplacement].tuile = carte;
    plateau[emplacement].orientation = joueur->orientation;
    joueur->cartes[carte - 1] = 0;
}

int emplacement(struct s_partisan *plateau)
/*
Cette fonction prends en paramètre le tableau du plateau, et :
- Demande au joueur la case qu'il souhaite utiliser
- Converti l'index en n° de la case
- Vérifie que l'index et corect et que la case est disponible, sinon affiche un message d'erreur correspondant
La fonction redemande un index à l'utilisateur tant que ces conditions ne sont pas validées.
Le numéro des cases en fonctions des index est de cette manière :
- | A B C
---------
1 | 0 1 2
2 | 3 4 5
3 | 6 7 8
*/
{
    int index_num;
    char index_text[255];
    do
    {
        printf("Coordonnées où vous souhaitez placer la carte (ex : A1, B3): ");
        scanf("%s", index_text);
        index_num = convertir(index_text);
        if (index_num > 8 || strlen(index_text) > 2)
            printf("\033[1;31mLa valeur entrée est incorecte, veuillez réessayer.\033[0m\n");
        else if (plateau[index_num].tuile != 0)
            printf("\033[1;31mLa case est déjà utilisée, veuillez indiquer une autre case.\033[0m\n");
    } while (index_num > 8 || strlen(index_text) > 2 || plateau[index_num].tuile != 0);
    return index_num;
}

int convertir(char *index_text)
/*
Cette fonction prends en paralètre un indice sous la forme (A3, B1, etc.), et retourne cet indice sous forme numérique,
pour pouvoir l'utiliser dans le tableau qui représente le plateau de jeu. Si l'indice entré en paramètre n'est pas bon, le
programme renvoie la valeur 9.
*/
{
    int index_num = 0;
    switch (index_text[0])
    {
    case 'A':
        break;
    case 'B':
        index_num += 1;
        break;

    case 'C':
        index_num += 2;
        break;

    default:
        return 9;
    }

    switch (index_text[1])
    {
    case '1':
        break;

    case '2':
        index_num += 3;
        break;

    case '3':
        index_num += 6;
        break;

    default:
        return 9;
    }
    return index_num;
}

int choix_personnage(int *cartes_joueurs)
/*
Cette fonction permet de choisir le personnage à jouer
*/
{
    printf("Merci de choisir un personnage\n");
}

void action_roi(struct s_partisan *plateau, int joueur)
/*
Cette fonction fait ...
*/
{
    printf("\n\nTest réussi\n\n");
}