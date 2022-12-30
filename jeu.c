#include <stdio.h>
#include <string.h>
#include "header.h"

void debut(struct s_partisan *plateau, struct s_joueur j_1, struct s_joueur j_2)
/*
Cette fonction prends en paramètre le plateau de jeu, et les deux listes correspondants au carte des joueurs.
Elle commence une partie du jeu. Le premier joueur place une carte citoyen au premier tour.
*/
{
    int i = 0;
    do{
        printf("\033[44mTour %d\033[0m", i + 1);
        printf(" ");
        printf("\033[%dmJoueur %d\033[0m\n", 40 + i % 2 + 1, i % 2 + 1);
        aff_plateau(plateau);
        if (i != 0)
        {
            if (i % 2 + 1 == 1)
            {

                place_carte(plateau, &j_1, choix_emplacement(plateau), choix_personnage(j_1));
            }
            else
            {
                place_carte(plateau, &j_2, choix_emplacement(plateau), choix_personnage(j_2));
            }
        }
        else
        {
            printf("Le joueur 1 pose la carte citoyen.\n");
            place_carte(plateau, &j_1, choix_emplacement(plateau), 1);
        }
        i += 1;
    } while(est_plein(plateau) != 1);
}

int est_plein(struct s_partisan *plateau)
/*
Cette fonction prends en paramètre le plateau de jeu, et renvoie 1 si le plateau est plein, 0 sinon.
*/
{
    int c = 0;
    for (int i = 0; i < 9; i++)
    {
        if (plateau[i].tuile == 0)
            c += 1;
    }
    if (c == 0) return 1;
    else return 0;
}

void place_carte(struct s_partisan *plateau, struct s_joueur *joueur, int emplacement, int carte)
/*
Cette fonction prends en paramètre :
- Le plateau du jeu
- Le joueur correspondant
- L'emplacement de la carte à placer (0 à 8)
- Le numéro de la carte à placer (1 à 7)
Et fait les actions suivantes :
- Place la bonne carte sur le plateau de jeu, avec la bonne orientation
- Enlève la carte correspondante dans la liste de cartes du joueur.
- Applique le pouvoir de la carte (sauf pour citoyen et château)
*/
{
    plateau[emplacement].tuile = carte;
    plateau[emplacement].orientation = joueur->orientation;
    joueur->cartes[carte - 1] = 0;
    actions_possibles(emplacement, carte);
    switch (carte)
    {
    case 2:
        // action_roi(plateau, *joueur, emplacement);
        printf("Action du roi\n");
        break;
    case 3:
        printf("Action de la reine\n");
        break;
    case 4:
        printf("Action de la princesse\n");
        break;
    case 5:
        printf("Action du ministre\n");
        break;
    case 6:
        printf("Action du général\n");
        break;
    default:
        break;
    }
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

void action_roi(struct s_partisan *plateau, struct s_joueur joueur, int emplacement)
/*
Affiche les cases possibles pour l'action du roi.
La fonction prends en paramètre :
- Le plateau du jeu
- Le joueur qui a posé la carte
- L'emplacement sur lequel a été posé la carte
*/
{
    printf("La carte a été mise sur la place %d.\n", emplacement);
}

int demande_roi_ministre(int emplacement)
/*
Cette fonction prends en paramètre l'emplacement sur lequel a été posé la carte, et demande au joueur sur quelle case
il veut appliquer le pouvoir. La fonction renvoie l'index sous forme numérique (0 à 8).
*/
{
    int index_num;
    char index_text[255];
    do
    {
        printf("Coordonnées où vous souhaitez appliquer le pouvoir (ex : A1, B3): ");
        scanf("%s", index_text);
        index_num = convertir(index_text);
        if (index_num > 8 || strlen(index_text) > 2)
            printf("\033[1;31mLa valeur entrée est incorecte, veuillez réessayer.\033[0m\n");
    } while (index_num > 8 || strlen(index_text) > 2);
    return index_num;
}

void actions_possibles(int emplacement, int carte)
/*
Cette fonction prends en paramètre :
- L'emplacement de la carte posée
- La carte qui a été posée
Et affiche les possibilités pour l'application du pouvoir du joueur
*/
{
    int tab[17], i;
    for (i = 0; i < 17; tab[i++] = 0)
        ;
    if (carte == 4)
    {
        int v, choix;
        do
        {
            printf("Orthogonale tapez 1, diagonale tapez 2 : ");
            v = scanf("%d", &choix);
            if (v != 1 || choix < 1 || choix > 2)
            {
                printf("\033[1;31mLa valeur entrée est incorecte, veuillez réessayer.\033[0m\n");
                scanf("%*[^\n]"); // Pour initialiser la zone de saisie
            }
        } while (v != 1 || choix < 1 || choix > 2);
        if (choix == 2)
            carte = 7;
    }
    switch (emplacement)
    {
    case 0:
        if (carte == 2 || carte == 5)
        {
            tab[1] = 1;
            tab[3] = 1;
            tab[4] = 1;
        }
        if (carte == 3)
        {
            tab[11] = 1;
            tab[12] = 1;
            tab[13] = 1;
        }
        if (carte == 4)
        {
            tab[1] = 1;
            tab[3] = 1;
        }
        if (carte == 7)
        {
            tab[4] = 1;
        }
        if (carte == 6)
        {
            tab[1] = 1;
            tab[3] = 1;
        }
        break;

    case 1:
        if (carte == 2 || carte == 5)
        {
            tab[0] = 1;
            tab[2] = 1;
            tab[3] = 1;
            tab[4] = 1;
            tab[5] = 1;
        }
        if (carte == 3)
        {
            tab[11] = 1;
            tab[12] = 1;
            tab[13] = 1;
            tab[14] = 1;
            tab[15] = 1;
        }
        if (carte == 4)
        {
            tab[0] = 1;
            tab[2] = 1;
            tab[4] = 1;
        }
        if (carte == 7)
        {
            tab[3] = 1;
            tab[5] = 1;
        }
        if (carte == 6)
        {
            tab[0] = 1;
            tab[2] = 1;
            tab[4] = 1;
        }
        break;
    case 2:
        if (carte == 2 || carte == 5)
        {
            tab[1] = 1;
            tab[4] = 1;
            tab[5] = 1;
        }
        if (carte == 3)
        {
            tab[13] = 1;
            tab[14] = 1;
            tab[15] = 1;
        }
        if (carte == 4)
        {
            tab[1] = 1;
            tab[5] = 1;
        }
        if (carte == 7)
        {
            tab[4] = 1;
        }
        if (carte == 6)
        {
            tab[1] = 1;
            tab[5] = 1;
        }
        break;

    case 3:
        if (carte == 2 || carte == 5)
        {
            tab[1] = 1;
            tab[4] = 1;
            tab[6] = 1;
            tab[7] = 1;
        }
        if (carte == 3)
        {
            tab[9] = 1;
            tab[10] = 1;
            tab[11] = 1;
            tab[12] = 1;
            tab[13] = 1;
        }
        if (carte == 4)
        {
            tab[0] = 1;
            tab[4] = 1;
            tab[6] = 1;
        }
        if (carte == 7)
        {
            tab[1] = 1;
            tab[7] = 1;
        }
        if (carte == 6)
        {
            tab[0] = 1;
            tab[4] = 1;
            tab[6] = 1;
        }
        break;

    case 4:
        if (carte == 2 || carte == 5)
        {
            tab[0] = 1;
            tab[1] = 1;
            tab[2] = 1;
            tab[3] = 1;
            tab[5] = 1;
            tab[6] = 1;
            tab[7] = 1;
            tab[8] = 1;
        }
        if (carte == 3)
        {
            tab[9] = 1;
            tab[10] = 1;
            tab[11] = 1;
            tab[12] = 1;
            tab[13] = 1;
            tab[14] = 1;
            tab[15] = 1;
            tab[16] = 1;
        }
        if (carte == 4)
        {
            tab[1] = 1;
            tab[3] = 1;
            tab[5] = 1;
            tab[7] = 1;
        }
        if (carte == 7)
        {
            tab[0] = 1;
            tab[2] = 1;
            tab[6] = 1;
            tab[8] = 1;
        }
        if (carte == 6)
        {
            tab[1] = 1;
            tab[3] = 1;
            tab[5] = 1;
            tab[7] = 1;
        }
        break;

    case 5:
        if (carte == 2 || carte == 5)
        {
            tab[1] = 1;
            tab[2] = 1;
            tab[4] = 1;
            tab[7] = 1;
            tab[8] = 1;
        }
        if (carte == 3)
        {
            tab[9] = 1;
            tab[13] = 1;
            tab[14] = 1;
            tab[15] = 1;
            tab[16] = 1;
        }
        if (carte == 4)
        {
            tab[2] = 1;
            tab[4] = 1;
            tab[8] = 1;
        }
        if (carte == 7)
        {
            tab[1] = 1;
            tab[7] = 1;
        }
        if (carte == 6)
        {
            tab[2] = 1;
            tab[4] = 1;
            tab[8] = 1;
        }
        break;

    case 6:
        if (carte == 2 || carte == 5)
        {
            tab[3] = 1;
            tab[4] = 1;
            tab[7] = 1;
        }
        if (carte == 3)
        {
            tab[9] = 1;
            tab[10] = 1;
            tab[11] = 1;
        }
        if (carte == 4)
        {
            tab[3] = 1;
            tab[7] = 1;
        }
        if (carte == 7)
        {
            tab[4] = 1;
        }
        if (carte == 6)
        {
            tab[3] = 1;
            tab[7] = 1;
        }
        break;

    case 7:
        if (carte == 2 || carte == 5)
        {
            tab[3] = 1;
            tab[4] = 1;
            tab[5] = 1;
            tab[6] = 1;
            tab[8] = 1;
        }
        if (carte == 3)
        {
            tab[9] = 1;
            tab[10] = 1;
            tab[11] = 1;
            tab[15] = 1;
            tab[16] = 1;
        }
        if (carte == 4)
        {
            tab[4] = 1;
            tab[6] = 1;
            tab[8] = 1;
        }
        if (carte == 7)
        {
            tab[3] = 1;
            tab[5] = 1;
        }
        if (carte == 6)
        {
            tab[4] = 1;
            tab[6] = 1;
            tab[8] = 1;
        }
        break;

    case 8:
        if (carte == 2 || carte == 5)
        {
            tab[4] = 1;
            tab[5] = 1;
            tab[7] = 1;
        }
        if (carte == 3)
        {
            tab[9] = 1;
            tab[15] = 1;
            tab[16] = 1;
        }
        if (carte == 4)
        {
            tab[5] = 1;
            tab[7] = 1;
        }
        if (carte == 7)
        {
            tab[4] = 1;
        }
        if (carte == 6)
        {
            tab[5] = 1;
            tab[7] = 1;
        }
        break;

    default:
        break;
    }
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