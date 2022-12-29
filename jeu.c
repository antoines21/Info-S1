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
    restant(j_1);
    int a = choix_emplacement(plateau);
    place_carte(plateau, &j_1, a, 1);
    aff_plateau(plateau);
    int z = choix_personnage(j_1);
    printf("Vous avez choisi le personnage %d \n", z);
    int c = choix_emplacement(plateau);
    place_carte(plateau, &j_2, c, z);
    applique_pouvoir(plateau, j_2, z);
    aff_plateau(plateau);
    /*
    for (int i = 1; i< 10; i++){
        printf("\033[%dmJoueur %d\033[0m\n", 40+ i%2+1, i%2+1);
    }
    */
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

int choix_emplacement(struct s_partisan *plateau)
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

int choix_personnage(struct s_joueur j)
/*
Cette fonction permet de choisir le personnage à jouer. Elle prends en paramètre la structure d'un joueur, et renvoie
le numéro de la carte choisir (entre 1 et 7). La fonction remdemande un nombre si la carte n'est plus disponible ou si la
valeur rentrée est incorecte.
*/
{
    int p, v;
    restant_demande(j);
    do
    {
        printf("Numéro de la carte : ");
        v = scanf("%d", &p);
        if (v != 1 || p < 1 || p > 7)
        {
            printf("\033[1;31mLa valeur entrée est incorecte, veuillez réessayer.\033[0m\n");
            scanf("%*[^\n]"); // Pour initialiser la zone de saisie
        }
        else if (j.cartes[p - 1] != 1)
        {
            printf("\033[1;31mLe personnage n'est plus disponible, veuillez choisir un autre personnage.\033[0m\n");
            scanf("%*[^\n]"); // Pour initialiser la zone de saisie
        }
    } while (v != 1 || p < 1 || p > 7 || j.cartes[p - 1] != 1);
    return p;
}

void applique_pouvoir(struct s_partisan *plateau, struct s_joueur j, int p)
/*
Cette fonction applique le pouvoir du personnage que le joueur vient de poser.
Elle prends en paramètre :
- Le plateau de jeu
- Le joueur qui a posé la carte
- La carte posée
*/
{
    if (p > 1 && p < 8)
    {
        switch (p-1)
        {
        case 1:
            action_roi();
            break;

        case 2:
            printf("Action reine ");
            break;

        case 3:
            printf("Action princesse ");
            break;

        case 4:
            printf("Action ministre ");
            break;

        case 5:
            printf("Action général ");
            break;
        }
    }
}

void action_roi(void)
/*
Affiche les cases possibles pour l'action du roi
*/
{
    printf("Je vais afficher plein de cases.\n");
}