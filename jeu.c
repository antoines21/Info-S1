#include <stdio.h>
#include <string.h>
#include "header.h"

int est_plein(struct s_partisan *plateau)
/*
Cette fonction prends en paramètre le plateau de jeu, et renvoie 1 si le plateau est plein, 0 sinon.
*/
{
    int c = 0;
    for (int i = 0; i < 9; i++)
    {
        if (plateau[i].personnage == 0)
            c += 1;
    }
    if (c == 0)
        return 1;
    else
        return 0;
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
    plateau[emplacement].personnage = carte;
    plateau[emplacement].orientation = joueur->orientation;
    joueur->cartes[carte - 1] = 0;
    action(plateau, *joueur, emplacement, carte);
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
        else if (plateau[index_num].personnage != 0)
            printf("\033[1;31mLa case est déjà utilisée, veuillez indiquer une autre case.\033[0m\n");
    } while (index_num > 8 || strlen(index_text) > 2 || plateau[index_num].personnage != 0);
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
le numéro de la carte choisie (entre 1 et 7). La fonction remdemande un nombre si la carte n'est plus disponible ou si la
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

void action(struct s_partisan *plateau, struct s_joueur joueur, int emplacement, int carte)
/*
Cette fonction prends en paramètre :
- Le plateau de jeu
- Le joueur qui l'a posée
- L'emplacement de la carte posée
- La carte qui a été posée
Et affiche les possibilités pour l'application du pouvoir du joueur
*/
{
    int tab[17], i;
    for (i = 0; i < 17; tab[i++] = 0);
    /*
    Cartes :
    1 - Citoyen
    2 - Roi
    3 - Reine
    4 - Princesse - 1 : Orthogonal - 2 : Diagonal
    5 - Ministre
    6 - Général
    7 - Château
    */

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
            tab[4] = 2;
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
            tab[3] = 2;
            tab[5] = 2;
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
            tab[4] = 2;
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
            tab[0] = 1;
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
            tab[1] = 2;
            tab[7] = 2;
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
            tab[0] = 2;
            tab[2] = 2;
            tab[6] = 2;
            tab[8] = 2;
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
            tab[1] = 2;
            tab[7] = 2;
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
            tab[4] = 2;
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
            tab[3] = 2;
            tab[5] = 2;
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
            tab[4] = 2;
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
    if (carte > 1 && carte < 7 && carte != 4)
        affichage_actions_possibles(tab, carte);

    switch (carte)
    {
    case 2: // Roi
        action_detruire(plateau, choix_roi_ministre_general(tab));
        break;

    case 3:;                              // Reine
        int direction = choix_reine(tab); // Retourne une valeur entre 1 et 8
        switch (direction)
        {
        case 1:
            if (emplacement == 3 || emplacement == 4 || emplacement == 5)
                action_pivoter(plateau, emplacement - 3);
            else if (emplacement == 6 || emplacement == 7 || emplacement == 8)
            {
                action_pivoter(plateau, emplacement - 3);
                action_pivoter(plateau, emplacement - 6);
            }
            break;

        case 2:
            if (emplacement == 3 || emplacement == 4 || emplacement == 7)
                action_pivoter(plateau, emplacement - 2);
            else if (emplacement == 6)
            {
                action_pivoter(plateau, emplacement - 2);
                action_pivoter(plateau, emplacement - 4);
            }
            break;

        case 3:
            if (emplacement == 1 || emplacement == 4 || emplacement == 7)
                action_pivoter(plateau, emplacement + 1);
            else if (emplacement == 0 || emplacement == 3 || emplacement == 6)
            {
                action_pivoter(plateau, emplacement + 1);
                action_pivoter(plateau, emplacement + 2);
            }
            break;

        case 4:
            if (emplacement == 3 || emplacement == 4 || emplacement == 1)
                action_pivoter(plateau, emplacement + 4);
            else if (emplacement == 0)
            {
                action_pivoter(plateau, emplacement + 4);
                action_pivoter(plateau, emplacement + 8);
            }
            break;

        case 5:
            if (emplacement == 3 || emplacement == 4 || emplacement == 5)
                action_pivoter(plateau, emplacement + 3);
            else if (emplacement == 0 || emplacement == 1 || emplacement == 2)
            {
                action_pivoter(plateau, emplacement + 3);
                action_pivoter(plateau, emplacement + 6);
            }
            break;

        case 6:
            if (emplacement == 1 || emplacement == 4 || emplacement == 5)
                action_pivoter(plateau, emplacement + 2);
            else if (emplacement == 2)
            {
                action_pivoter(plateau, emplacement + 2);
                action_pivoter(plateau, emplacement + 4);
            }
            break;

        case 7:
            if (emplacement == 1 || emplacement == 4 || emplacement == 7)
                action_pivoter(plateau, emplacement - 1);
            else if (emplacement == 2 || emplacement == 5 || emplacement == 8)
            {
                action_pivoter(plateau, emplacement - 1);
                action_pivoter(plateau, emplacement - 2);
            }
            break;

        case 8:
            if (emplacement == 4 || emplacement == 5 || emplacement == 7)
                action_pivoter(plateau, emplacement - 4);
            else if (emplacement == 8)
            {
                action_pivoter(plateau, emplacement - 4);
                action_pivoter(plateau, emplacement - 8);
            }
            break;

        default:
            break;
        }
        break;

    case 4:; // Princesse

        int v, choix;
        do
        {
            printf("Pivoter les tuiles orthogonales tapez 1, diagonales tapez 2 : ");
            v = scanf("%d", &choix);
            if (v != 1 || choix < 1 || choix > 2)
            {
                printf("\033[1;31mLa valeur entrée est incorecte, veuillez réessayer.\033[0m\n");
                scanf("%*[^\n]"); // Pour initialiser la zone de saisie
            }
        } while (v != 1 || choix < 1 || choix > 2);

        for (i = 0; i < 9; i++)
        {
            if (tab[i] == choix)
            {
                action_pivoter(plateau, i);
            }
        }
        break;

    case 5: // Ministre
        action_pivoter(plateau, choix_roi_ministre_general(tab));
        break;

    case 6: // Général
        action_detruire(plateau, choix_roi_ministre_general(tab));
        break;

    default:
        break;
    }
}

int choix_roi_ministre_general(int *tab)
/*
Cette fonction prends en paramètre :
- Le tableau des cases possibles (tableau de 17 cases, mais uniquement les cases 0 à 8 nous interessent)
Et renvoie :
- L'index numérique de la case sur laquelle nous allons appliquer le pouvoir (valeur entre 0 et 8)
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
        else if (tab[index_num] != 1)
            printf("\033[1;31mVous ne pouvez pas appliquer le pouvoir sur cette case. Veuillez indiquer une autre case.\033[0m\n");
    } while (index_num > 8 || strlen(index_text) > 2 || tab[index_num] != 1);
    return index_num;
}

int choix_reine(int *tab)
/*
Cette fonction prends en paramètre :
- Le tableau des cases possibles (tableau de 17 cases, mais uniquement les cases 9 à 16 nous interessent)
Et renvoie :
- Le numéro de la direction choisie (une valeur entre 1 et 8)
Directions :
1 - Haut
2 - Haut droite
3 - Droite
4 - Bas droite
5 - Bas
6 - Bas gauche
7 - Gauche
8 - Haut gauche
*/
{

    int direction, v;
    do

    {
        printf("Numéro de la direction choisie : ");
        v = scanf("%d", &direction);
        if (v != 1 || direction < 1 || direction > 8)
        {
            printf("\033[1;31mLa valeur entrée est incorecte, veuillez réessayer.\033[0m\n");
            scanf("%*[^\n]"); // Pour initialiser la zone de saisie
        }
        else if (tab[direction + 8] != 1)
        {
            printf("\033[1;31mVous ne pouvez pas choisir cette direction. Veuillez choisir une autre direction.\033[0m\n");
            scanf("%*[^\n]"); // Pour initialiser la zone de saisie
        }
    } while (v != 1 || direction < 1 || direction > 8 || tab[direction + 8] != 1);
    return direction;
}

void action_detruire(struct s_partisan *plateau, int emplacement)
/*
La fonction prends en paramètre :
- Le plateau du jeu
- La case d'application du pouvoir, choisie par le joueur qui a posé la carte
*/
{
    if (plateau[emplacement].personnage != 7) // Si la case n'est pas un château
    {
        plateau[emplacement].orientation = 0;
        plateau[emplacement].personnage = 0;
    }
}

void action_pivoter(struct s_partisan *plateau, int emplacement)
/*
La fonction prends en paramètre :
- Le plateau du jeu
- La case d'application du pouvoir, choisie par le joueur qui a posé la carte
*/
{
    if (plateau[emplacement].personnage != 7 && plateau[emplacement].orientation != 0) // Si la case n'est pas vide et n'est pas un château
    {

        plateau[emplacement].orientation = plateau[emplacement].orientation % 2 + 1;
    }
}

int joueur_gagnant(struct s_partisan *plateau)
/*
Cette fonction prends en paramètre la grille de jeu, et renvoie le numéro du joueur qui a gagné (1 ou 2). Il ne peux pas
y avoir égalité (car 9 n'est pas divisible par 2).
*/
{
    int compteur_1 = 0, compteur_2 = 0, i;
    for (i = 0; i < 8; i++)
    {
        plateau[i].orientation == 1 ? compteur_1++ : compteur_2++;
    }
    return compteur_1 > compteur_2 ? 1 : 2;
}